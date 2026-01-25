#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QThread>

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
    
signals:
    void initTableManager();
    
private:
    MainWidget mainWidget;
    QWidget centralWidget;
    QStackedLayout stackedLayout;

    SupportSystem supportSystem;
    TableManager tableManager;
    QThread thread; 

};

#endif // MAINWINDOW_H
