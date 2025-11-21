#pragma once
#include <QtWidgets/qwidget.h>

// declare classes of all windows/pages here instead of #include
class LoginWindow;

class ApplicationController
{
private:
    // add all windows/widgets here
    LoginWindow* login_window;
    
public:
    ApplicationController();  // start the app
    ~ApplicationController(); // cleanup

    void start(bool loggedIn=true);  // show login screen
    void onLogout();                 // called by main window
    void hideWidget(QWidget* widget);
    void showWidget(QWidget* widget);
};
