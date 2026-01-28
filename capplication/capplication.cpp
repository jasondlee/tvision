/*----------------------------------------------------------*/
/*                                                          */
/*   capplication.cpp - C wrappers for TApplication        */
/*                                                          */
/*   Implementation of C interface for Turbo Vision apps   */
/*                                                          */
/*----------------------------------------------------------*/

#define Uses_TApplication
#define Uses_TProgInit
#define Uses_TMenuBar
#define Uses_TStatusLine
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TStatusDef
#define Uses_TRect
#define Uses_TDeskTop
#define Uses_TCommandSet
#include <tvision/tv.h>

#include "capplication.h"
#include "cmenuitem.h"
#include "cstatusline.h"

#include <vector>

/*
 * Internal builder structure
 */
struct TApplicationBuilder_C {
    TSubMenu *menuBar;
    TStatusDef *statusLine;
    std::vector<unsigned short> enabledCommands;
    std::vector<unsigned short> disabledCommands;

    TApplicationBuilder_C()
        : menuBar(nullptr), statusLine(nullptr) {
    }

    ~TApplicationBuilder_C() {
        // Note: menuBar and statusLine will be owned by TApplication
        // so we don't delete them here
    }
};

/*
 * Custom TApplication subclass that uses builder-provided components
 */
class CApplication : public TApplication {
private:
    TSubMenu *customMenuBar;
    TStatusDef *customStatusLine;

    static TMenuBar *initMenuBarStatic(TRect r);

    static TStatusLine *initStatusLineStatic(TRect r);

    static CApplication *currentInstance;

public:
    CApplication(TSubMenu *menuBar,
                 TStatusDef *statusLine
                 // const std::vector<unsigned short>& enabledCmds,
                 // const std::vector<unsigned short>& disabledCmds
    );

    virtual ~CApplication();
};

// Static member initialization
CApplication *CApplication::currentInstance = nullptr;

CApplication::CApplication(TSubMenu *menuBar,
                           TStatusDef *statusLine
                           // const std::vector<unsigned short>& enabledCmds,
                           // const std::vector<unsigned short>& disabledCmds
)
    : TProgInit(CApplication::initStatusLineStatic,
                CApplication::initMenuBarStatic,
                TApplication::initDeskTop),
      TApplication(),
      customMenuBar(menuBar),
      customStatusLine(statusLine) {
    currentInstance = this;

    // Enable/disable commands as specified
    /*
    if (!enabledCmds.empty() || !disabledCmds.empty()) {
        TCommandSet ts;

        for (unsigned short cmd : enabledCmds) {
            ts.enableCmd(cmd);
        }
        for (unsigned short cmd : disabledCmds) {
            ts.enableCmd(cmd);
        }

        if (!disabledCmds.empty()) {
            disableCommands(ts);
        }
    }
*/
}

CApplication::~CApplication() {
    currentInstance = nullptr;
    // TApplication destructor will clean up menuBar and statusLine
}

TMenuBar *CApplication::initMenuBarStatic(TRect r) {
    if (currentInstance && currentInstance->customMenuBar) {
        r.b.y = r.a.y + 1;
        return new TMenuBar(r, *currentInstance->customMenuBar);
    }
    return nullptr;
}

TStatusLine *CApplication::initStatusLineStatic(TRect r) {
    if (currentInstance && currentInstance->customStatusLine) {
        r.a.y = r.b.y - 1;
        return new TStatusLine(r, *currentInstance->customStatusLine);
    }
    return nullptr;
}

/*
 * C API implementation
 */

extern "C" {
TApplicationBuilder_C *c_application_builder_new(void) {
    return new TApplicationBuilder_C();
}

TApplicationBuilder_C *c_application_builder_set_menubar(
    TApplicationBuilder_C *builder,
    TSubMenu_C *menu) {
    if (builder && menu) {
        builder->menuBar = reinterpret_cast<TSubMenu *>(menu);
    }
    return builder;
}

TApplicationBuilder_C *c_application_builder_set_statusline(
    TApplicationBuilder_C *builder,
    TStatusDef_C *statusDef) {
    if (builder && statusDef) {
        builder->statusLine = reinterpret_cast<TStatusDef *>(statusDef);
    }
    return builder;
}

TApplicationBuilder_C *c_application_builder_enable_command(
    TApplicationBuilder_C *builder,
    unsigned short command) {
    if (builder) {
        builder->enabledCommands.push_back(command);
    }
    return builder;
}

TApplicationBuilder_C *c_application_builder_disable_command(
    TApplicationBuilder_C *builder,
    unsigned short command) {
    if (builder) {
        builder->disabledCommands.push_back(command);
    }
    return builder;
}

TApplication_C *c_application_builder_build(TApplicationBuilder_C *builder) {
    if (!builder) {
        return nullptr;
    }

    CApplication *app = new CApplication(
        builder->menuBar,
        builder->statusLine
        // ,
        // builder->enabledCommands,
        // builder->disabledCommands
    );

    // Clean up builder
    delete builder;

    return reinterpret_cast<TApplication_C *>(app);
}

void c_application_builder_destroy(TApplicationBuilder_C *builder) {
    if (builder) {
        delete builder;
    }
}

void c_application_run(TApplication_C *app) {
    if (app) {
        TApplication *application = reinterpret_cast<TApplication *>(app);
        application->run();
    }
}

void c_application_shutdown(TApplication_C *app) {
    if (app) {
        TApplication *application = reinterpret_cast<TApplication *>(app);
        application->shutDown();
    }
}

void c_application_destroy(TApplication_C *app) {
    if (app) {
        CApplication *application = reinterpret_cast<CApplication *>(app);
        delete application;
    }
}

void *c_application_get_ptr(TApplication_C *app) {
    return reinterpret_cast<void *>(app);
}
} // extern "C"

// Made with Bob
