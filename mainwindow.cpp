#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStatistics(const QList<Applicant> &unCountedApplicants, const QList<FacultyCell> &faculties) {
    
    QBarSet* set1 = new QBarSet("Name1");
    *set1 << 1 << 2;
    QBarSet* set2 = new QBarSet("Name1");
    *set2 << 2 << 4;
    QBarSeries *series = new QBarSeries();
    series->append(set1);
    series->append(set2);
    
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Статистика");
    chart->axes(Qt::Vertical).first()->setRange(0, 10);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    
    QStringList list;
    list << "first" << "second";
    QBarCategoryAxis* bca = new QBarCategoryAxis;
    bca->append(list);
    
    chart->addAxis(bca, Qt::AlignBottom);
    series->attachAxis(bca);
    
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    
    QVBoxLayout* lauout = new QVBoxLayout;
    lauout->addWidget(chartView);
    lauout->setContentsMargins(0,0,0,0);
    ui->mathPlacesWgt->setLayout(lauout);
    
    //chartView->resize(ui->mathPlacesWgt->size());
    //chartView->setBackgroundBrush(QBrush(QColor(30,30,30)));
    //chart->setBackgroundBrush(QBrush(QColor(30,30,30)));
    //chart->setTitleBrush(QBrush(QColor(255,255,255)));
    
    // chart->axes(Qt::Horizontal).first()->setLinePenColor(QColor(60,60,60));
    // chart->axes(Qt::Horizontal).first()->setGridLineColor(QColor(60,60,60));
    // chart->axes(Qt::Vertical).first()->setLinePenColor(QColor(60,60,60));
    // chart->axes(Qt::Vertical).first()->setGridLineColor(QColor(60,60,60));
    
}
