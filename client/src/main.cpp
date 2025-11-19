#include <QtWidgets/qmainwindow.h>
#include <iostream>
#include <qapplication.h>


int main(int argc, char* argv[]){
    
    QApplication app(argc, argv);

    QMainWindow window;
    window.resize(500,500);

    window.show();


    return app.exec();
}