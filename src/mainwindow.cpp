#include "src/mainwindow.h"
#include "ui_mainwidget.h"


MainWindow::MainWindow() {
    
    stackedLayout.addWidget(&mainWidget);
    
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(&stackedLayout);
    this->setCentralWidget(centralWidget);
    
    supportSystem.init();
    tableManager.init();
    
    QObject::connect(&mainWidget, &MainWidget::sendTable,
                     &tableManager, &TableManager::processTable);
    
    QObject::connect(&tableManager, &TableManager::sendFaculties,
                     &mainWidget, &MainWidget::processFaculties);
    
    
}

MainWindow::~MainWindow() {
    
    
    
}
