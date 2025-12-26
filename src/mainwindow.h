#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QBarSeries>
#include <QBarSet>
#include <QtCharts/QChartView>
#include <QVBoxLayout>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QFile>

#include "src/applicant.h"
#include "src/facultycell.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    void setFaculties(const QList<FacultyCell>& faculties);
    
private:
    Ui::MainWindow *ui;
    QList<FacultyCell> m_faculties;
};

#endif // MAINWINDOW_H
