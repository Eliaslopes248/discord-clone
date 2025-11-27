#include "../../../include/lib/pages/LoginWindow.h"
#include <QtCore/qnamespace.h>
#include <QtCore/qobject.h>
#include <QtGui/qcolor.h>
#include <QtGui/qguiapplication.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qwidget.h>
#include "../../../include/lib/ui/Dimensions.h"
#include <QGuiApplication>
#include <QScreen>
#include <cstddef>
#include <QSizePolicy>
#include "../../../include/lib/ui/GlobalQSS.h"
#include <iostream>

#define LW LoginWindow

// constructor
LW::LoginWindow(QWidget* parent)
: QWidget(parent), 
  login_window_layout(NULL), login_form(NULL), 
  username_input(NULL), password_input(NULL),
  login_in_btn(NULL), register_btn(NULL)
{
    this->setWindowTitle("LOGIN");
    // create basic window dimensions
    QSize* min_size = new QSize(MIN_LOGIN_WINDOW_SIZE);
    this->setMinimumSize(*min_size);

    QSize* max_size = new QSize(MAX_LOGIN_WINDOW_SIZE);
    this->setMaximumSize(*max_size);

    QSize* init_size = new QSize(INIT_LOGIN_WINDOW_SIZE);
    this->resize(*init_size);

    // center in middle of the screen
    QRect screen = QGuiApplication::primaryScreen()->availableGeometry();
    this->move(screen.center() - this->rect().center());

    // add widget components
    this->setUp();

    this->show();
}

// build window
void LW::setUp()
{
    // create background
    createBackground();
    // add VBox layout to the widget
    createLayout(new QVBoxLayout());
    // add form
    createLoginForm();
    // add form content
    insertFormContent();
}

// layout
void LW::createLayout(QLayout* layout)
{
    // catch NULL layout passed
    if (!layout) layout = new QVBoxLayout();
    login_window_layout = layout;
    // center x center alignment
    layout->setAlignment(Qt::AlignCenter);

    // add layout to the widget
    this->setLayout(layout);
}

// background
void LW::createBackground()
{
    // set style
    this->setProperty("class", "LoginWindowBg");
}

// login form
void LW::createLoginForm()
{
    // create box like widget
    login_form = new QWidget(this);
    login_form->setLayout(new QVBoxLayout());
    login_form->layout()->setAlignment(Qt::AlignCenter);

    // set form dimensions 
    login_form->setMinimumSize(MIN_LOGIN_FORM_SIZE);
    login_form->setMaximumSize(MAX_LOGIN_FORM_SIZE);
    login_form->resize(INIT_LOGIN_FORM_SIZE);
    
    // add styles
    login_form->setObjectName("loginform");
    setBoxShadow(
        login_form,
        QColor(0, 0, 0, 150),
        40,
        0,
        4
    );

    // add form to the layout (works with any QBoxLayout - VBox or HBox)
    if (login_window_layout) {
        QBoxLayout* boxLayout = qobject_cast<QBoxLayout*>(login_window_layout);
        if (boxLayout) { 
            boxLayout->addWidget(login_form);
        } else {
            // For non-box layouts (Grid, etc.), use addWidget on base QLayout
            login_window_layout->addWidget(login_form);
        }
    }
    
    // Make sure widget is visible
    login_form->show();
}

// form content
void LW::insertFormContent()
{
    // get form layout
    QLayout*    form_layout = login_form->layout();

    // create header for form
    QLabel*     form_header = new QLabel("Log in");
    form_header->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    form_header->setAlignment(Qt::AlignCenter);
    form_header->setObjectName("login_form_header");
    // insert header
    form_layout->addWidget(form_header);

    // create vbox for username and password
    // create input box widget
    QWidget*        input_widget = new QWidget(login_form);
    // add dimensions
    input_widget->setMinimumSize(MIN_LOGIN_INPUT_SIZE);
    input_widget->setMaximumSize(MAX_LOGIN_INPUT_SIZE);
    input_widget->resize(INIT_LOGIN_INPUT_SIZE);

    // create layout for input widget
    QVBoxLayout*    input_layout = new QVBoxLayout();
    input_layout->setSpacing(20);

    // add input widget styles
    input_widget->setObjectName("login_form_input_widget");
    // set the layout
    input_widget->setLayout(input_layout);

    // add widget to the form_layout
    form_layout->addWidget(input_widget);

    // add QLineEdit widgets
    username_input = new QLineEdit();
    username_input->setPlaceholderText("Enter Username");

    password_input = new QLineEdit();
    password_input->setPlaceholderText("Enter Password");

    // add styling
    username_input->setProperty("class", "authInput");
    password_input->setProperty("class", "authInput");

    // add input to the widget layout
    input_layout->addWidget(username_input);
    input_layout->addWidget(password_input);

    // Get line edit size to match buttons
    username_input->adjustSize();
    QSize line_edit_size = username_input->sizeHint();
    // Use input widget width (line edits will fill this width)
    QSize input_widget_size(INIT_LOGIN_INPUT_SIZE);
    int button_width    = input_widget_size.width();
    int button_height   = line_edit_size.height();

    // create vbox for login btn and create new account option
    QWidget*        button_widget = new QWidget();
    button_widget->setMinimumSize(MIN_LOGIN_BTN_WIDGET_SIZE);
    button_widget->setMaximumSize(MAX_LOGIN_BTN_WIDGET_SIZE);
    button_widget->resize(INIT_LOGIN_BTN_WIDGET_SIZE);
    // add widget to layout
    form_layout->addWidget(button_widget);

    // create layout for the widget
    QVBoxLayout* button_widget_layout = new QVBoxLayout();
    button_widget_layout->setSpacing(20);
    button_widget_layout->setAlignment(Qt::AlignCenter);
    // set the layout
    button_widget->setLayout(button_widget_layout);
    // apply style
    button_widget->setObjectName("login_form_btn_widget");
    
    // create push btns
    login_in_btn = new QPushButton("Sign in");
    login_in_btn->setObjectName("login_btn");
    login_in_btn->setProperty("class", "authButton");
    login_in_btn->setFixedSize(INIT_AUTH_BTN_SIZE);

    // register btn
    register_btn = new QPushButton("Register");
    register_btn->setObjectName("register_btn");
    register_btn->setProperty("class", "authButton");
    register_btn->setFixedSize(INIT_AUTH_BTN_SIZE);

    // add buttons to the widget/layout
    button_widget_layout->addWidget(login_in_btn);
    button_widget_layout->addWidget(register_btn);
    
    // add slots and actions
    connect(
        login_in_btn,
        &QPushButton::clicked,
        this,
        &LoginWindow::handleSubmit
    );
}

//---------------------------------------------------------------

void LW::setInputValues()
{
    // get the values
    std::string username = username_input->text().toStdString();
    std::string password = password_input->text().toStdString();
    // set credentials struct values
    login_crednetials.username = username;
    login_crednetials.password = password;
}

void LW::handleSubmit()
{
    // set struct with values for credentials
    setInputValues();
}


void LW::printFormFields()
{
    std::cout << "\n----- INPUT VALUES ------" << std::endl;
    std::cout << "USERNAME: " << login_crednetials.username << std::endl;
    std::cout << "PASSWORD: " << login_crednetials.password << std::endl;
}

// clean up
LW::~LoginWindow(){}