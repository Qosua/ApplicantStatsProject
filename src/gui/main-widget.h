#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDesktopServices>
#include <QDragEnterEvent>
#include <QListWidgetItem>
#include <QMimeData>
#include <QPushButton>
#include <QTabWidget>
#include <QWidget>

#include "../applicants-faculty-data/applicant.h"
#include "../data-processing/table-manager.h"

struct uiCell {
    QPushButton* btn;
    QTabWidget* tabWidget;
};

const QString facultiesNamesList[] = {"Факультет биологии и экологии",
                                      "Факультет информатики и вычислительной техники",
                                      "Исторический факультет",
                                      "Математический факультет",
                                      "Факультет психологии",
                                      "Физико-технический факультет",
                                      "Факультет иностранных языков",
                                      "Факультет филологии и коммуникации",
                                      "Факультет социально-политических наук",
                                      "Экономический факультет",
                                      "Юридический факультет"};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget {
    Q_OBJECT
public:
    MainWidget();
    ~MainWidget() override;

    void getProceededTable(QList<FacultyDirection>* data);
    void loadTablesToUi(QList<QString> list) const;

    void stopWaiting() const;
    void wait() const;

signals:
    void sendTablePathToProcess(const QString& tableName);

private:
    void updateUi();

    static void saveTable(const QString& path);
    static void openDataFolder();
    void sortTables();
    void chooseTable(const QListWidgetItem* item);

    void resetButtonsColor(int exception) const;

    bool sortOrder = true;
    QList<FacultyDirection> m_faculties;
    QHash<QString, uiCell> uiCells;

    Ui::MainWidget* ui = nullptr;
    QList<FacultyDirection>* currentData = nullptr;

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
};

#endif  // MAINWIDGET_H
