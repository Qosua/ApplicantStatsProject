#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QObject>
#include <QWidget>

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
#include <QStackedLayout>

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
class MainWidget;
}

class MainWidget : public QWidget {
    Q_OBJECT
    
public:
    MainWidget();
    ~MainWidget();
    
    void processFaculties(QList<FacultyCell> faculties);
    void loadTablesToUi(QList<QString> list);
    void wait();
    void soptWait(QList<FacultyCell>* faculties);
    
signals:
    void sendTable(const QString& tableName);
    
private:
    void parseFaculties();
    void updateUi();
    void setInfoToWidget(QWidget* widget,const QList<DirectionInfo>& directionInfo);
    
    void saveTable(QString path);
    void openDataFolder();
    void sortTables();
    void chooseTable(QListWidgetItem* item);
    
    void resetButtonsColor(int execption);
    
    bool sortOrder = true;
    Ui::MainWidget* ui;
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

#endif // MAINWIDGET_H
