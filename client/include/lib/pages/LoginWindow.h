#pragma once
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QVBoxLayout>
#include <QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>


class LoginWindow : public QWidget 
{
private:
    
    QLayout*    login_window_layout;
    QWidget*    login_form;

    // input widgets that hold user login credentials
    QLineEdit*  username_input;
    QLineEdit*  password_input;

    // log in and register buttons
    QPushButton* login_in_btn;
    QPushButton* register_btn;

    // data struct for login credentials
    struct {
        std::string username;
        std::string password;
    }login_crednetials;

    //---------------------------------------------------
    // build window
    void setUp();
    // layout
    void createLayout(QLayout* layout=new QVBoxLayout());
    // background
    void createBackground();
    // login form
    void createLoginForm();
    // form content
    void insertFormContent();

    //---------------------------------------------------
    void setInputValues();
    void printFormFields();

    
public:
    // event slots
    void handleSubmit();

    explicit LoginWindow(QWidget* parent=NULL);
    ~LoginWindow();
};