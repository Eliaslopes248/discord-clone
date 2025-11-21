#include "../../../include/lib/pages/LoginWindow.h"
#include <QtCore/qnamespace.h>
#include <QtGui/qguiapplication.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qwidget.h>
#include "../../../include/lib/ui/Dimensions.h"
#include <QGuiApplication>
#include <QScreen>
#include <cstddef>


#define LW LoginWindow

// constructor
LW::LoginWindow(QWidget* parent)
: QWidget(parent), login_window_layout(NULL), login_form(NULL)
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
    login_form->layout()->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    // set dimensions 
    login_form->setMinimumSize(INIT_LOGIN_FORM_SIZE);
    login_form->setObjectName("loginform");

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
    form_header->setObjectName("login_form_header");
    // insert header
    form_layout->addWidget(form_header);


    // create vbox for username and password
    // FIXME: add correct macros to dimensions, fix styling on input widgets, then organize qss file
    QWidget*    input_widget = new QWidget(login_form);
    input_widget->setObjectName("login_form_input_widget");
    QVBoxLayout* input_layout = new QVBoxLayout();
    input_widget->setLayout(input_layout);

    // add to layout
    form_layout->addWidget(input_widget);

    // create vbox for login btn and create new account option
    


}

// clean up
LW::~LoginWindow(){}