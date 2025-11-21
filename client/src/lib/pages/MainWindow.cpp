#include "../../../include/lib/ui/MainWindow.h"
#include <QtCore/qsize.h>
#include <QtGui/qwindowdefs.h>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qwidget.h>
#include "../../../include/lib/ui/Dimensions.h"

#define MW MainWindow


//=========================================
// constructor
//=========================================
MW::MainWindow(QWidget* parent)
: QMainWindow(parent){

    // set up simple window properties
    this->setWindowTitle("MAIN WINDOW");

    // set dimensions of the window
    QSize *min_size = new QSize(MIN_WINDOW_WIDTH,MIN_WINDOW_HEIGHT);
    this->setMinimumSize(*min_size);

    QSize *max_size = new QSize(MAX_WINDOW_WIDTH,MAX_WINDOW_HEIGHT);
    this->setMaximumSize(*max_size);

    QSize *init_size = new QSize(INIT_WINDOW_WIDTH,INIT_WINDOW_HEIGHT);
    this->resize(*init_size);



    this->show();

}



