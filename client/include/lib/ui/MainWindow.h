#include <QMainWindow>
#include <QtCore/qtmetamacros.h>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qwidget.h>
#include <cstddef>
#pragma once


class MainWindow : public QMainWindow {

    Q_OBJECT

    public:
    explicit MainWindow(QWidget* parent=NULL);

    private:
    


};
