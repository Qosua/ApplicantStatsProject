#include "src/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    
    ui->setupUi(this);
    this->setAcceptDrops(true);
    
    this->ui->splitter->setSizes(QList<int>() << 100 << 400);
    this->ui->splitter->setStyleSheet("QSplitter::handle{background-color:#21a366;}");
    
    this->ui->bottomWidget->setStyleSheet("background-color: #181818");
    this->ui->versionLabel->setStyleSheet("color: #888888");
    this->ui->currentFileLabel->setStyleSheet("color: #888888");
    
    // ui cells initialization
    {
        uiCells[facultiesNamesList[0]].btn = ui->bioBtn;
        uiCells[facultiesNamesList[0]].tabWidget = ui->tabWidgetbio;
        
        uiCells[facultiesNamesList[1]].btn = ui->ivtBtn;
        uiCells[facultiesNamesList[1]].tabWidget = ui->tabWidgetivt;
        
        uiCells[facultiesNamesList[2]].btn = ui->histBtn;
        uiCells[facultiesNamesList[2]].tabWidget = ui->tabWidgehist;
        
        uiCells[facultiesNamesList[3]].btn = ui->mathBtn;
        uiCells[facultiesNamesList[3]].tabWidget = ui->tabWidgemath;
        
        uiCells[facultiesNamesList[4]].btn = ui->psyBtn;
        uiCells[facultiesNamesList[4]].tabWidget = ui->tabWidgetpsy;
        
        uiCells[facultiesNamesList[5]].btn = ui->physBtn;
        uiCells[facultiesNamesList[5]].tabWidget = ui->tabWidgephys;
        
        uiCells[facultiesNamesList[6]].btn = ui->inyazBtn;
        uiCells[facultiesNamesList[6]].tabWidget = ui->tabWidgeinyaz;
        
        uiCells[facultiesNamesList[7]].btn = ui->filoBtn;
        uiCells[facultiesNamesList[7]].tabWidget = ui->tabWidgetfilo;
        
        uiCells[facultiesNamesList[8]].btn = ui->fspnBtn;
        uiCells[facultiesNamesList[8]].tabWidget = ui->tabWidgetfspn;
        
        uiCells[facultiesNamesList[9]].btn = ui->economBtn;
        uiCells[facultiesNamesList[9]].tabWidget = ui->tabWidgeteconom;
        
        uiCells[facultiesNamesList[10]].btn = ui->urBtn;
        uiCells[facultiesNamesList[10]].tabWidget = ui->tabWidgetur;
    }
    
    // connections
    {
        connect(ui->bioBtn, &QPushButton::clicked,
                this->ui->pagesWidget, [this](bool var)
                {
                    this->resetButtonsColor(0);
                    this->ui->pagesWidget->setCurrentWidget(this->ui->bio);
                }
                );
        
        connect(ui->ivtBtn, &QPushButton::clicked,
                this->ui->pagesWidget, [this](bool var)
                {
                    this->resetButtonsColor(1);
                    this->ui->pagesWidget->setCurrentWidget(this->ui->ivt);
                }
                );
        connect(ui->histBtn, &QPushButton::clicked,
                this->ui->pagesWidget, [this](bool var)
                {
                    this->resetButtonsColor(2);
                    this->ui->pagesWidget->setCurrentWidget(this->ui->hist);
                }
                );
        connect(ui->mathBtn, &QPushButton::clicked,
                this->ui->pagesWidget, [this](bool var)
                {
                    this->resetButtonsColor(3);
                    this->ui->pagesWidget->setCurrentWidget(this->ui->math);
                }
                );
        connect(ui->psyBtn, &QPushButton::clicked,
                this->ui->pagesWidget, [this](bool var)
                {
                    this->resetButtonsColor(4);
                    this->ui->pagesWidget->setCurrentWidget(this->ui->psy);
                }
                );
        connect(ui->physBtn, &QPushButton::clicked,
                this->ui->pagesWidget, [this](bool var)
                {
                    this->resetButtonsColor(5);
                    this->ui->pagesWidget->setCurrentWidget(this->ui->phys);
                }
                );
        connect(ui->inyazBtn, &QPushButton::clicked,
                this->ui->pagesWidget, [this](bool var)
                {
                    this->resetButtonsColor(6);
                    this->ui->pagesWidget->setCurrentWidget(this->ui->inyaz);
                }
                );
        connect(ui->filoBtn, &QPushButton::clicked,
                this->ui->pagesWidget, [this](bool var)
                {
                    this->resetButtonsColor(7);
                    this->ui->pagesWidget->setCurrentWidget(this->ui->filo);
                }
                );
        connect(ui->fspnBtn, &QPushButton::clicked,
                this->ui->pagesWidget, [this](bool var)
                {
                    this->resetButtonsColor(8);
                    this->ui->pagesWidget->setCurrentWidget(this->ui->fspn);
                }
                );
        connect(ui->economBtn, &QPushButton::clicked,
                this->ui->pagesWidget, [this](bool var)
                {
                    this->resetButtonsColor(9);
                    this->ui->pagesWidget->setCurrentWidget(this->ui->econom);
                }
                );
        connect(ui->urBtn, &QPushButton::clicked,
                this->ui->pagesWidget, [this](bool var)
                {
                    this->resetButtonsColor(10);
                    this->ui->pagesWidget->setCurrentWidget(this->ui->ur);
                }
                );
        connect(ui->generalBtn, &QPushButton::clicked,
                this->ui->pagesWidget, [this](bool var)
                {
                    this->resetButtonsColor(11);
                    this->ui->pagesWidget->setCurrentWidget(this->ui->generalStat);
                }
                );
    }
    
    
    for(const QString& name : facultiesNamesList) 
        uiCells[name].tabWidget->setTabText(0, "Общие (" + name + ")");
    
    loadTables();
    
    connect(this->ui->folderButton, &QPushButton::clicked,
            this, &MainWindow::openDataFolder);

    connect(this->ui->updateButton, &QPushButton::clicked,
            this, &MainWindow::loadTables);
    
    connect(this->ui->sortButton, &QPushButton::clicked,
            this, &MainWindow::sortTables);
    
    this->ui->versionLabel->setText("Версия: 0.8.0");
    this->ui->currentFileLabel->setText("Текущая открытая таблица: Пусто");
    
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setFaculties(const QList<FacultyCell> &faculties) {
    
    m_faculties = faculties;
    
    updateUi();
}

void MainWindow::processFaculties() {
    
    for(const auto& faculty : m_faculties) {
        
        auto& currentElem = database[faculty.division()]
                                    [faculty.name()]
                                    [faculty.studyForm()];
        
        if(faculty.studyType() != StudyType::Budget) {
            
           currentElem.size += faculty.pool().size();
            currentElem.studentsCount += faculty.pool().size();
        }
        else {
            
            currentElem.name = faculty.name();
            currentElem.size += faculty.pool().size();
            currentElem.studentsCount += faculty.capacity();
        }
        
        currentElem.pool = faculty.pool();
        
        if(faculty.pool().isEmpty() or faculty.studyType() != StudyType::Budget)
            continue;
        
        currentElem.maxScore = std::max(
            faculty.pool().last().first.egeScore(),
            currentElem.maxScore
        );
        
        currentElem.minScore = std::min(
            faculty.pool().first().first.egeScore(),
            currentElem.minScore
        );
    }
    
    return;
    
}

void MainWindow::updateUi() {
    
    processFaculties();
    
    for(const QString& name : facultiesNamesList) {
        
        QList<QString> directionsNames = database[name].keys();
        
        for(const QString& directionName : directionsNames) {
            
            QWidget* widget = new QWidget;
            uiCells[name].tabWidget->addTab(widget, directionName);
        }
    }
    
}

void MainWindow::saveTable(QString path) {
    
    QString name = path.split('/').last();
    
    QFile file(path);
    file.copy(APP_DATA_PATH + "/" + name);
    
    loadTables();
    
}

void MainWindow::loadTables() {
    
    disconnect(this->ui->tablesWidget, &QListWidget::itemClicked,
               this, &MainWindow::chooseTable);
    
    this->ui->tablesWidget->clear();
    
    QDir dataDir(APP_DATA_PATH);
    QStringList entries = dataDir.entryList(QStringList() << "*.xlsx", QDir::Files);
    
    for (const QString &entry : entries) {
        
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(entry);
        item->setIcon(QIcon(":/icons/exelicon.png"));
        item->setBackground(QBrush(QColor("#212121")));
        
        this->ui->tablesWidget->addItem(item);
        
    }
    
    connect(this->ui->tablesWidget, &QListWidget::itemClicked,
            this, &MainWindow::chooseTable);
    
    if(!this->sortOrder) 
        this->ui->tablesWidget->sortItems();
    else 
        this->ui->tablesWidget->sortItems(Qt::DescendingOrder);
    
}

void MainWindow::openDataFolder() {
        
    QDesktopServices::openUrl(APP_DATA_PATH);
    
}

void MainWindow::sortTables() {
    
    if(this->sortOrder) 
        this->ui->tablesWidget->sortItems();
    else 
        this->ui->tablesWidget->sortItems(Qt::DescendingOrder);
    
    this->sortOrder = !this->sortOrder;
    
    loadTables();
}

void MainWindow::chooseTable(QListWidgetItem *item) {
    
    if(!QFile::exists(APP_DATA_PATH + "/" + item->text()))
        return;
    
    this->ui->currentFileLabel->setText("Текущая открытая таблица: " + APP_DATA_PATH + "/" + item->text());
    
    emit tableChosen(APP_DATA_PATH + "/" + item->text());
    
}

void MainWindow::resetButtonsColor(int execption) {
    
    ui->bioBtn->setStyleSheet("background-color: 2d2d2d; color: #ffffff;");
    ui->ivtBtn->setStyleSheet("background-color: 2d2d2d; color: #ffffff;");
    ui->histBtn->setStyleSheet("background-color: 2d2d2d; color: #ffffff;");
    ui->mathBtn->setStyleSheet("background-color: 2d2d2d; color: #ffffff;");
    ui->psyBtn->setStyleSheet("background-color: 2d2d2d; color: #ffffff;");
    ui->physBtn->setStyleSheet("background-color: 2d2d2d; color: #ffffff;");
    ui->inyazBtn->setStyleSheet("background-color: 2d2d2d; color: #ffffff;");
    ui->filoBtn->setStyleSheet("background-color: 2d2d2d; color: #ffffff;");
    ui->fspnBtn->setStyleSheet("background-color: 2d2d2d; color: #ffffff;");
    ui->economBtn->setStyleSheet("background-color: 2d2d2d; color: #ffffff;");
    ui->urBtn->setStyleSheet("background-color: 2d2d2d; color: #ffffff;");
    ui->generalBtn->setStyleSheet("background-color: 2d2d2d; color: #ffffff;");
    
    switch(execption){
    case 0: ui->bioBtn->setStyleSheet("background-color: #252525; color: #999999;"); break;
    case 1: ui->ivtBtn->setStyleSheet("background-color: #252525; color: #999999;"); break;
    case 2: ui->histBtn->setStyleSheet("background-color: #252525; color: #999999;"); break;
    case 3: ui->mathBtn->setStyleSheet("background-color: #252525; color: #999999;"); break;
    case 4: ui->psyBtn->setStyleSheet("background-color: #252525; color: #999999;"); break;
    case 5: ui->physBtn->setStyleSheet("background-color: #252525; color: #999999;"); break;
    case 6: ui->inyazBtn->setStyleSheet("background-color: #252525; color: #999999;"); break;
    case 7: ui->filoBtn->setStyleSheet("background-color: #252525; color: #999999;"); break;
    case 8: ui->fspnBtn->setStyleSheet("background-color: #252525; color: #999999;"); break;
    case 9: ui->economBtn->setStyleSheet("background-color: #252525; color: #999999;"); break;
    case 10: ui->urBtn->setStyleSheet("background-color: #252525; color: #999999;"); break;
    case 11: ui->generalBtn->setStyleSheet("background-color: #252525; color: #999999;"); break;
    }
    
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    
    if (event->mimeData()->hasUrls()) 
        event->acceptProposedAction();
    else 
        event->ignore(); 
}

void MainWindow::dropEvent(QDropEvent *event) {
    
    const QMimeData *mimeData = event->mimeData();
    
    if (mimeData->hasUrls()) {
        
        QList<QUrl> urlList = mimeData->urls();
        
        for (const QUrl &url : urlList) {
            
            QString filePath = url.toLocalFile();
            QStringList partialUrl = filePath.split('.');
            
            if(partialUrl.last() == "xlsx")
                saveTable(filePath);
            
        }
        event->acceptProposedAction();
    }
    else {
        event->ignore();
    }
    
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event) {
    
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else 
        event->ignore();
}

