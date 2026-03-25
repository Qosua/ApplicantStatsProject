#include "window-manager.h"

WindowManager::WindowManager() {

    mainWidget = new MainWidget();
    centralWidget = new QWidget();
    stackedLayout = new QStackedLayout();
    supportSystem = new SupportSystem();
    tableManager = new TableManager();
    thread = new QThread();

    mainWidget->setAcceptDrops(true);
    stackedLayout->addWidget(mainWidget);
    centralWidget->setLayout(stackedLayout);
    this->setCentralWidget(centralWidget);

    QObject::connect(mainWidget, &MainWidget::sendTablePathToProcess,
                     tableManager,&TableManager::processTable);

    QObject::connect(tableManager,   &TableManager::sendProceededData,
                     mainWidget, &MainWidget::getProceededTable);

    QObject::connect(tableManager, &TableManager::sendTableList,
                     mainWidget,&MainWidget::loadTablesToUi);

    QObject::connect(tableManager, &TableManager::waitForFinish,
                     mainWidget, &MainWidget::wait);

    QObject::connect(tableManager, &TableManager::finished,
                     mainWidget, &MainWidget::stopWaiting);

    QObject::connect(this, &WindowManager::initTableManager,
                     tableManager, &TableManager::init, Qt::SingleShotConnection);

    tableManager->moveToThread(thread);
    thread->start();

    supportSystem->init();
    emit initTableManager();
}

WindowManager::~WindowManager() {

    delete mainWidget;
    delete centralWidget;
    delete stackedLayout;
    delete supportSystem;
    delete tableManager;
    delete thread;
}
