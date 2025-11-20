#include <QtCore/qnamespace.h>
#include <QtGui/qpalette.h>
#include <QtWidgets/qmainwindow.h>
#include <iostream>
#include <qapplication.h>


int main(int argc, char* argv[]){
    
    QApplication app(argc, argv);

    QMainWindow window;
    window.resize(500,500);


    // testing palletes
    QPalette pal = window.palette();
    pal.setColor(QPalette::Window, Qt::darkCyan);

    window.setPalette(pal);


    window.show();
    return app.exec();
}