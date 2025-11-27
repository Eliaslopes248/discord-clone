#include <QtCore/qnamespace.h>
#include <QtCore/qobjectdefs.h>
#include <QtCore/qtimer.h>
#include <QtGui/qpalette.h>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qsplashscreen.h>
#include <cstdlib>
#include <cstring>
#include <qapplication.h>
#include <QFile>
#include <QString>
#include "../include/lib/controllers/ApplicationController.h"
#include <QSplashScreen>
#include <QTimer>
#include <QPixmap>
#include <iostream>
#include <fstream>
#include "../include/lib/secrets/secrets.h"
#include "../include/lib/api/restapi.h"

#define PROD_ENV_FILE   "../client/src/env/.env.production"
#define DEV_ENV_FILE    "../client/src/env/.env.developement"


QSplashScreen* showSplashScreen(QApplication& app) {
    // Load splash screen image
    QPixmap pixmap("../client/include/styles/assets/discord-bg1.jpg");
    if (pixmap.isNull()) {
        std::cerr << "Failed to load splash screen image!" << std::endl;
        return nullptr;
    }
    
    // Scale pixmap to exactly 600x300
    pixmap = pixmap.scaled(600, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    
    // Create and configure splash screen
    QSplashScreen* splash_screen = new QSplashScreen(pixmap);
    splash_screen->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::SplashScreen);
    splash_screen->resize(600, 300);
    splash_screen->show();
    splash_screen->raise();
    splash_screen->activateWindow();
    
    // Process events to ensure splash screen is displayed
    app.processEvents();
    
    return splash_screen;
}

int main(int argc, char* argv[]){

    //----------------------- Load environment variables ---------------------
    char* ENV_TYPE = getenv("ENV_TYPE");
    // debug check env file
    if (!ENV_TYPE){
        std::cout << "No ENV_TYPE given, defaulting to dev" << std::endl;
    }else {
        std::cout << "ENV_TYPE: " << ENV_TYPE << std::endl;
    }
    
    std::ifstream env_file;
    const char* env_file_path = nullptr;
    bool file_opened = false;

    // load prod variables
    if (ENV_TYPE && (std::strcmp(ENV_TYPE, "prod") == 0 || 
        std::strcmp(ENV_TYPE, "production") == 0))
    {
        env_file_path = PROD_ENV_FILE;
        env_file.open(PROD_ENV_FILE);
        file_opened = env_file.is_open();
    }
    // load dev variables
    else if (ENV_TYPE && (std::strcmp(ENV_TYPE, "dev") == 0 || 
        std::strcmp(ENV_TYPE, "developement") == 0))
    {
        env_file_path = DEV_ENV_FILE;
        env_file.open(DEV_ENV_FILE);
        file_opened = env_file.is_open();
    }
    else{
        // default point to the dev env file
        env_file_path = DEV_ENV_FILE;
        env_file.open(DEV_ENV_FILE);
        file_opened = env_file.is_open();
    }

    if (file_opened) {
        std::cout << "Successfully opened env file: " << env_file_path << std::endl;
        load_env(env_file);
        env_file.close();
        std::cout << "Variables loaded!" << std::endl;
    } else {
        std::cerr << "ERROR: Failed to open env file: " << env_file_path << std::endl;
        std::cerr << "Make sure the file exists and the path is correct." << std::endl;
    }

    // ----------------------create rest api client test ---------------------
    rest_client client;

    //----------------------- Load GUI ---------------------------------------

    // application instance
    QApplication app(argc, argv);

    // set style sheet for the application
    QFile f("../client/include/styles/styles.qss");
    if (f.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QString::fromUtf8(f.readAll());
        app.setStyleSheet(styleSheet);
        f.close();
    }

    // show splash screen
    QSplashScreen* splash_screen = showSplashScreen(app);
    
    // Close splash screen after 2.5 seconds
    ApplicationController* controller = nullptr;
    QTimer::singleShot(2500, [splash_screen, &controller]() {
        if (splash_screen) {
            splash_screen->close();
            delete splash_screen;
        }
        // Wait 2 seconds after splash closes, then create controller
        QTimer::singleShot(1000, [&controller]() {
            controller = new ApplicationController();
        });
    });
    
    // render 
    int result = app.exec();
    
    // Cleanup
    if (controller) {
        delete controller;
    }
    
    return result;
}