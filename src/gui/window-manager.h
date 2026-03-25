#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QThread>

#include "../applicants-faculty-data/applicant.h"
#include "../data-processing/support-system.h"
#include "../data-processing/table-manager.h"
#include "main-widget.h"

class WindowManager : public QMainWindow {
    Q_OBJECT
public:
    WindowManager();
    ~WindowManager() override;

signals:
    void initTableManager();

private:
    MainWidget* mainWidget;
    QWidget* centralWidget;
    QStackedLayout* stackedLayout;

    SupportSystem* supportSystem;
    TableManager* tableManager;
    QThread* thread;
};

#endif  // MAINWINDOW_H
