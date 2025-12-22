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

void MainWindow::setMathStatistics(const QList<Applicant> &unCountedApplicants, const QList<FacultyCell> &faculties) {
    
    // int pmiKcp = 0;
    // int pmiPlaces = 0;
    
    // int mknKcp = 0;
    // int mknPlaces = 0;
    
    // int ibKcp = 0;
    // int ibPlaces = 0;
    
    // int kbKcp = 0;
    // int kbPlaces = 0;
    
    // QFile input(":/programInfo/kcpBachelors.txt");
    // QTextStream stream(&input);
    
    // if(!input.open(QIODevice::ReadOnly | QIODevice::Text)) {
    //     qDebug() << "Не удалось открыть файл " << ":/programInfo/kcpBachelors.txt" << "\n Ошибка: " << input.errorString();
    // }
    
    // QString line = stream.readLine(); //read title line
    // line = stream.readLine();         //read first line
    
    // while(line.isEmpty() or line[0] != "/") {
    
    //     if(!line.isEmpty()) {
    
    //         QList<QString> arr = line.split("\"");
    
    //         for(int i = 0; i < arr.size(); ++i)
    //             if(arr[i].isEmpty() or arr[i] == " ") {
    //                 arr.removeAt(i);
    //                 --i;
    //             }
    
    //         QString name = arr[1];
    //         QString kcp = arr[4];
    
    //         if(name == "Прикладное программирование и информационные технологии") {
    //             pmiKcp += kcp.toInt();
    //         }
    //         if(name == "Программирование, алгоритмы и анализ данных"){
    //             mknKcp += kcp.toInt();
    //         }
    //         if(name == "Безопасность компьютерных систем"){
    //             ibKcp += kcp.toInt();
    //         }
    //         if(name == "Математические методы защиты информации"){
    //             kbKcp += kcp.toInt();
    //         }
    
    //     }
    
    //     line = stream.readLine();
    
    // }
    
    // for(int i = 0; i < faculties.size(); ++i){
    
    //     if(faculties[i].name() == "Прикладное программирование и информационные технологии") {
    //         pmiPlaces += faculties[i].pool().size();
    //     }
    //     if(faculties[i].name() == "Программирование, алгоритмы и анализ данных"){
    //         mknPlaces += faculties[i].pool().size();
    //     }
    //     if(faculties[i].name() == "Безопасность компьютерных систем"){
    //         ibPlaces += faculties[i].pool().size();
    //     }
    //     if(faculties[i].name() == "Математические методы защиты информации"){
    //         kbPlaces += faculties[i].pool().size();
    //     }
    
    // }
    
    // ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // QBarSet* places = new QBarSet("Занятые места");
    // *places << pmiPlaces << mknPlaces << ibPlaces << kbPlaces;
    // QBarSet* maxPlaces = new QBarSet("Количество бюджетных мест");
    // *maxPlaces << pmiKcp << mknKcp << ibKcp << kbKcp;
    
    // QBarSeries *series1 = new QBarSeries();
    // series1->append(places);
    // series1->append(maxPlaces);
    
    // QChart *chart1 = new QChart();
    // chart1->addSeries(series1);
    // chart1->createDefaultAxes();
    // chart1->setTitle("Статистика бюджетных мест");
    // chart1->axes(Qt::Vertical).first()->setRange(0, std::max(std::max(pmiKcp, mknKcp), std::max(ibKcp, kbKcp)) + 5);
    // chart1->setAnimationOptions(QChart::SeriesAnimations);
    
    // QStringList list1;
    // list1 << "ПМИ_01.03.02" << "МКН_02.03.01" << "ИБ_10.03.01" << "КБ_10.05.01";
    // QBarCategoryAxis* axisX1 = new QBarCategoryAxis;
    // axisX1->append(list1);
    
    // chart1->addAxis(axisX1, Qt::AlignBottom);
    // series1->attachAxis(axisX1);
    
    // QChartView *chartView1 = new QChartView(chart1);
    // chartView1->setRenderHint(QPainter::Antialiasing);
    
    // QVBoxLayout* lauout1 = new QVBoxLayout;
    // lauout1->addWidget(chartView1);
    // lauout1->setContentsMargins(0,0,0,0);
    // ui->mathPlacesWgt->setLayout(lauout1);
    // ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // QBarSet* scores = new QBarSet("Проходные балы");
    
    // QList<int> scoresList= {0,0,0,0};
    
    // for(int i = 0; i < faculties.size(); ++i){
    
    //     if(faculties[i].name() == "Прикладное программирование и информационные технологии") {
    //         if(faculties[i].type() == "Бюджет")
    //             scoresList[0] = faculties[i].pool()[0].first.egeScore();
    //     }
    //     if(faculties[i].name() == "Программирование, алгоритмы и анализ данных"){
    //         if(faculties[i].type() == "Бюджет")
    //             scoresList[1] = faculties[i].pool()[0].first.egeScore();
    //     }
    //     if(faculties[i].name() == "Безопасность компьютерных систем"){
    //         if(faculties[i].type() == "Бюджет")
    //             scoresList[2] = faculties[i].pool()[0].first.egeScore();
    //     }
    //     if(faculties[i].name() == "Математические методы защиты информации"){
    //         if(faculties[i].type() == "Бюджет")
    //             scoresList[3] = faculties[i].pool()[0].first.egeScore();
    //     }
    
    // }
    
    // *scores << scoresList[0] << scoresList[1] << scoresList[2] << scoresList[3];
    
    // QBarSeries *series2 = new QBarSeries();
    // series2->append(scores);
    
    // QChart *chart2 = new QChart();
    // chart2->addSeries(series2);
    // chart2->createDefaultAxes();
    // chart2->setTitle("Проходные балы");
    // chart2->axes(Qt::Vertical).first()->setRange(0, std::max(std::max(scoresList[0], scoresList[1]), std::max(scoresList[2], scoresList[3])) + 10);
    // chart2->setAnimationOptions(QChart::SeriesAnimations);
    
    // QStringList list2;
    // list2 << "ПМИ_01.03.02" << "МКН_02.03.01" << "ИБ_10.03.01" << "КБ_10.05.01";
    // QBarCategoryAxis* axisX2 = new QBarCategoryAxis;
    // axisX2->append(list2);
    
    // chart2->addAxis(axisX2, Qt::AlignBottom);
    // series2->attachAxis(axisX2);
    
    // QChartView *chartView = new QChartView(chart2);
    // chartView->setRenderHint(QPainter::Antialiasing);
    
    // QVBoxLayout* lauout2 = new QVBoxLayout;
    // lauout2->addWidget(chartView);
    // lauout2->setContentsMargins(0,0,0,0);
    // ui->mathScoreWgt->setLayout(lauout2);
    
}
