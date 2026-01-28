/*----------------------------------------------------------*/
/*                                                          */
/*   capplication.cpp - C builder API for TApplication     */
/*                                                          */
/*   Implementation of C interface for TApplication        */
/*                                                          */
/*----------------------------------------------------------*/

#define Uses_TApplication
#define Uses_TMenuBar
#define Uses_TStatusLine
#define Uses_TRect
#define Uses_TSubMenu
#define Uses_TStatusDef
#define Uses_TCommandSet
#define Uses_TEvent
#define Uses_TFileDialog
#define Uses_TChDirDialog
#define Uses_TDeskTop
#include <tvision/tv.h>

#include "capplication.h"
#include "../cmenuitem/cmenuitem.h"
#include "../cstatusline/cstatusline.h"

#include <map>
#include <string.h>

/*
 * Custom TApplication subclass that can be configured from C
 */
class CApplication : public TApplication
{
public:
    CApplication();
    virtual ~CApplication();
    
    // Set menu and status line
    void setMenuBar(TSubMenu* menu);
    void setStatusLine(TStatusDef* statusDef);
    
    // Command handlers
    void registerHandler(ushort command, CEventHandler handler, void* userData);
    virtual void handleEvent(TEvent& event) override;
    
    // Command enable/disable
    void enableCommand(ushort command);
    void disableCommand(ushort command);
    void enableCommands(const ushort* commands, int count);
    void disableCommands(const ushort* commands, int count);
    
protected:
    virtual TMenuBar* initMenuBar(TRect r) override;
    virtual TStatusLine* initStatusLine(TRect r) override;
    
private:
    TSubMenu* customMenu;
    TStatusDef* customStatusDef;
    
    struct HandlerInfo {
        CEventHandler handler;
        void* userData;
    };
    std::map<ushort, HandlerInfo> handlers;
};

CApplication::CApplication() :
    TProgInit(CApplication::initStatusLine,
              CApplication::initMenuBar,
              CApplication::initDeskTop),
    TApplication(),
    customMenu(nullptr),
    customStatusDef(nullptr)
{
}

CApplication::~CApplication()
{
    // Note: TApplication destructor will clean up menu and status line
}

void CApplication::setMenuBar(TSubMenu* menu)
{
    customMenu = menu;
}

void CApplication::setStatusLine(TStatusDef* statusDef)
{
    customStatusDef = statusDef;
}

TMenuBar* CApplication::initMenuBar(TRect r)
{
    if (customMenu) {
        r.b.y = r.a.y + 1;
        return new TMenuBar(r, *customMenu);
    }
    return nullptr;
}

TStatusLine* CApplication::initStatusLine(TRect r)
{
    if (customStatusDef) {
        r.a.y = r.b.y - 1;
        return new TStatusLine(r, *customStatusDef);
    }
    return nullptr;
}

void CApplication::registerHandler(ushort command, CEventHandler handler, void* userData)
{
    HandlerInfo info;
    info.handler = handler;
    info.userData = userData;
    handlers[command] = info;
}

void CApplication::handleEvent(TEvent& event)
{
    TApplication::handleEvent(event);
    
    if (event.what == evCommand) {
        ushort cmd = event.message.command;
        auto it = handlers.find(cmd);
        if (it != handlers.end()) {
            // Call the C handler
            it->second.handler(this, cmd, it->second.userData);
            clearEvent(event);
        }
    }
}

void CApplication::enableCommand(ushort command)
{
    TCommandSet ts;
    ts.enableCmd(command);
    enableCommands(ts);
}

void CApplication::disableCommand(ushort command)
{
    TCommandSet ts;
    ts.enableCmd(command);
    disableCommands(ts);
}

void CApplication::enableCommands(const ushort* commands, int count)
{
    TCommandSet ts;
    for (int i = 0; i < count; i++) {
        ts.enableCmd(commands[i]);
    }
    enableCommands(ts);
}

void CApplication::disableCommands(const ushort* commands, int count)
{
    TCommandSet ts;
    for (int i = 0; i < count; i++) {
        ts.enableCmd(commands[i]);
    }
    disableCommands(ts);
}

/*
 * C API implementation
 */

extern "C" {

TApplication_C* c_application_new(void)
{
    CApplication* app = new CApplication();
    return reinterpret_cast<TApplication_C*>(app);
}

void c_application_set_menubar(TApplication_C* app, TSubMenu_C* menu)
{
    if (!app || !menu) return;
    
    CApplication* capp = reinterpret_cast<CApplication*>(app);
    TSubMenu* submenu = reinterpret_cast<TSubMenu*>(menu);
    capp->setMenuBar(submenu);
}

void c_application_set_statusline(TApplication_C* app, TStatusDef_C* statusDef)
{
    if (!app || !statusDef) return;
    
    CApplication* capp = reinterpret_cast<CApplication*>(app);
    TStatusDef* def = reinterpret_cast<TStatusDef*>(statusDef);
    capp->setStatusLine(def);
}

void c_application_register_handler(
    TApplication_C* app,
    unsigned short command,
    CEventHandler handler,
    void* userData
)
{
    if (!app || !handler) return;
    
    CApplication* capp = reinterpret_cast<CApplication*>(app);
    capp->registerHandler(command, handler, userData);
}

void c_application_enable_command(TApplication_C* app, unsigned short command)
{
    if (!app) return;
    
    CApplication* capp = reinterpret_cast<CApplication*>(app);
    capp->enableCommand(command);
}

void c_application_disable_command(TApplication_C* app, unsigned short command)
{
    if (!app) return;
    
    CApplication* capp = reinterpret_cast<CApplication*>(app);
    capp->disableCommand(command);
}

void c_application_enable_commands(TApplication_C* app, const unsigned short* commands, int count)
{
    if (!app || !commands) return;
    
    CApplication* capp = reinterpret_cast<CApplication*>(app);
    capp->enableCommands(commands, count);
}

void c_application_disable_commands(TApplication_C* app, const unsigned short* commands, int count)
{
    if (!app || !commands) return;
    
    CApplication* capp = reinterpret_cast<CApplication*>(app);
    capp->disableCommands(commands, count);
}

void c_application_run(TApplication_C* app)
{
    if (!app) return;
    
    CApplication* capp = reinterpret_cast<CApplication*>(app);
    capp->run();
}

void c_application_destroy(TApplication_C* app)
{
    if (!app) return;
    
    CApplication* capp = reinterpret_cast<CApplication*>(app);
    capp->shutDown();
    delete capp;
}

void* c_application_get_ptr(TApplication_C* app)
{
    return reinterpret_cast<void*>(app);
}

void c_application_cascade(TApplication_C* app)
{
    if (!app) return;
    
    CApplication* capp = reinterpret_cast<CApplication*>(app);
    capp->cascade();
}

void c_application_tile(TApplication_C* app)
{
    if (!app) return;
    
    CApplication* capp = reinterpret_cast<CApplication*>(app);
    capp->tile();
}

unsigned short c_application_exec_file_dialog(
    TApplication_C* app,
    const char* wildcard,
    const char* title,
    char* resultBuffer,
    int bufferSize
)
{
    if (!app || !wildcard || !title || !resultBuffer || bufferSize <= 0) {
        return cmCancel;
    }
    
    CApplication* capp = reinterpret_cast<CApplication*>(app);
    
    // Initialize result buffer with wildcard
    strncpy(resultBuffer, wildcard, bufferSize - 1);
    resultBuffer[bufferSize - 1] = '\0';
    
    // Execute the file dialog
    ushort result = capp->execDialog(
        new TFileDialog(wildcard, title, "~N~ame", fdOpenButton, 100),
        resultBuffer
    );
    
    return result;
}

void c_application_exec_chdir_dialog(TApplication_C* app)
{
    if (!app) return;
    
    CApplication* capp = reinterpret_cast<CApplication*>(app);
    capp->execDialog(new TChDirDialog(cdNormal, 0), nullptr);
}

} // extern "C"

// Made with Bob
