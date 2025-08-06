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

#include "applicant.h"
#include "facultycell.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    void setMathStatistics(const QList<Applicant>& unCountedApplicants, const QList<FacultyCell>& faculties);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
