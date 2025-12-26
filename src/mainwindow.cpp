#include "src/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    
    ui->setupUi(this);

    // QFile file(":/styles/white_style.qss");
    // if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    //     qDebug() << "Не удалось открыть файл: :/styles/white_style.qss \n Ошибка: " << file.errorString();
    // }

    // this->setStyleSheet(file.readAll());

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setFaculties(const QList<FacultyCell> &faculties) {
    m_faculties = faculties;
}

