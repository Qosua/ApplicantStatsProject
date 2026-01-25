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
#include "src/tablemanager.h"

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

    void loadTablesToUi(QList<QString> list);
    void stopWaiting(UniversityData* data);
    void wait();
    
signals:
    void sendTable(const QString& tableName);
    
private:
    void updateUi();
    void setInfoToWidget(QWidget* widget,const QList<DirectionInfo>& directionInfo);
    
    void saveTable(QString path);
    void openDataFolder();
    void sortTables();
    void chooseTable(QListWidgetItem* item);
    
    void resetButtonsColor(int execption);
    
    bool sortOrder = true;
    QList<FacultyCell> m_faculties;
    QHash<QString, uiCell> uiCells;

    Ui::MainWidget* ui = nullptr;
    UniversityData* currentData = nullptr;
    
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    
};

#endif // MAINWIDGET_H
