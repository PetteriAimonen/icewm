#ifndef __WMAPP_H
#define __WMAPP_H

#include "yapp.h"
#include "ymenu.h"
#include "ymsgbox.h"
#ifdef CONFIG_GUIEVENTS
#include "guievent.h"
#endif

enum PhaseType {
    phaseStartup,
    phaseShutdown,
    phaseRunning,
    phaseRestart
};

class YWindowManager;

class YWMApp: public YApplication, public YActionListener, public YMsgBoxListener {
public:
    YWMApp(int *argc, char ***argv, const char *displayName = 0);
    ~YWMApp();
#ifdef CONFIG_GUIEVENTS
    void signalGuiEvent(GUIEvent ge);
#endif

    virtual void afterWindowEvent(XEvent &xev);
    virtual void handleSignal(int sig);
    virtual void handleIdle();
    virtual void actionPerformed(YAction *action, unsigned int modifiers);

    virtual void handleMsgBox(YMsgBox *msgbox, int operation);

    void logout();
    void cancelLogout();

#ifdef SM
    virtual void smSaveYourself(bool shutdown, bool fast);
    virtual void smSaveYourselfPhase2();
    virtual void smShutdownCancelled();
    virtual void smDie();
#endif

    void restartClient(const char *str, char **args);
    void runOnce(const char *resource, const char *str, char **args);

    static YCursor sizeRightPointer;
    static YCursor sizeTopRightPointer;
    static YCursor sizeTopPointer;
    static YCursor sizeTopLeftPointer;
    static YCursor sizeLeftPointer;
    static YCursor sizeBottomLeftPointer;
    static YCursor sizeBottomPointer;
    static YCursor sizeBottomRightPointer;

private:
    YWindowManager *fWindowManager;
    YMsgBox *fLogoutMsgBox;
};

extern YWMApp * wmapp;
extern PhaseType phase;

extern YMenu *windowMenu;
extern YMenu *occupyMenu;
extern YMenu *layerMenu;
extern YMenu *moveMenu;
#ifdef CONFIG_WINMENU
extern YMenu *windowListMenu;
#endif
#ifdef CONFIG_WINLIST
extern YMenu *windowListPopup;
extern YMenu *windowListAllPopup;
#endif
extern YMenu *maximizeMenu;
extern YMenu *logoutMenu;

#ifndef NO_CONFIGURE_MENUS
class ObjectMenu;
extern ObjectMenu *rootMenu;
#endif
class CtrlAltDelete;
extern CtrlAltDelete *ctrlAltDelete;
extern int rebootOrShutdown;

#endif
