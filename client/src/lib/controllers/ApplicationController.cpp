#include "../../../include/lib/controllers/ApplicationController.h"
#include "../../../include/lib/pages/LoginWindow.h"

#define AC ApplicationController

// constructors
AC::ApplicationController()
    : login_window(nullptr)
{
    // FIXME: check for jwt user info in local storage
    bool logged_in = false;
    // start application
    start(logged_in);
}

// =====================================================================

void AC::start(bool loggedIn)
{
    // show login window
    if (!loggedIn)
    {
        login_window = new LoginWindow();
    }
}


// clean up
AC::~ApplicationController(){
    if (login_window) {
        delete login_window;
        login_window = nullptr;
    }
}


