#pragma once
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QVBoxLayout>
#include <QLineEdit>
#include <QtWidgets/QLabel>


class LoginWindow : QWidget 
{
private:
    QLayout* login_window_layout;
    QWidget* login_form;

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

    

public:
    explicit LoginWindow(QWidget* parent=NULL);
    ~LoginWindow();
};