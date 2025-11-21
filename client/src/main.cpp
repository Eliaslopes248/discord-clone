#include <QtCore/qnamespace.h>
#include <QtGui/qpalette.h>
#include <QtWidgets/qmainwindow.h>
#include <qapplication.h>
#include <QFile>
#include <QString>
#include "../include/lib/controllers/ApplicationController.h"

int main(int argc, char* argv[]){
    // application instance
    QApplication app(argc, argv);

    // set style sheet for the application
    QFile f("../client/include/styles/styles.qss");
    if (f.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QString::fromUtf8(f.readAll());
        app.setStyleSheet(styleSheet);
        f.close();
    }


    // create app controller
    ApplicationController controller;
    // render 
    return app.exec();
}