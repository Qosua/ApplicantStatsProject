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
#include <QHash>
#include <QSet>
#include <QPushButton>
#include <QTabWidget>
#include <QDropEvent>
#include <QMimeData>
#include <QListWidgetItem>
#include <QDesktopServices>

#include "src/applicant.h"
#include "src/facultycell.h"
#include "src/supportsystem.h"

// I know that direction is a wrong word
struct DirectionInfo {
    
    int size = 0;
    int studentsCount = 0;
    int minScore = 500;
    int maxScore = 0;
    QString name;
    QList<QPair<PriorityInfo, Applicant>> pool;
};

struct uiCell {
    
    QPushButton* btn;
    QTabWidget* tabWidget;
};

const QString facultiesNamesList[] = {
    "Факультет биологии и экологии",
    "Факультет информатики и вычислительной техники",
    "Исторический факультет",
    "Математический факультет",
    "Факультет психологии",
    "Физико-технический факультет",
    "Факультет иностранных языков",
    "Факультет филологии и коммуникации",
    "Факультет социально-политических наук",
    "Экономический факультет",
    "Юридический факультет"
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    void setFaculties(const QList<FacultyCell>& faculties);
    
private:
    void processFaculties();
    void updateUi();
    void setInfoToWidget(QWidget* widget,const QList<DirectionInfo>& directionInfo);
    
    void saveTable(QString path);
    void loadTables();
    void openDataFolder();
    void sortTables();
    
    bool sortOrder = true;
    Ui::MainWindow *ui;
    QList<FacultyCell> m_faculties;
    
    // ha ha ha
    QHash<QString,
          QHash<QString,
                QHash<StudyForm,
                      DirectionInfo>>>  database;
    QHash<QString, uiCell> uiCells;
    
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
};

#endif // MAINWINDOW_H
