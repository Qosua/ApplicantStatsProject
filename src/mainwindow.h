#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>

#include "src/applicant.h"
#include "src/facultycell.h"
#include "src/supportsystem.h"
#include "src/mainwidget.h"
#include "src/tablemanager.h"

class MainWindow : public QMainWindow {
    
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    
private:
    MainWidget mainWidget;
    SupportSystem supportSystem;
    TableManager tableManager;
    
    QStackedLayout stackedLayout;
};

#endif // MAINWINDOW_H
