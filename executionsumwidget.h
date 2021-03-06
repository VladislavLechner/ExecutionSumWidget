#ifndef EXECUTIONSUMWIDGET_H
#define EXECUTIONSUMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QCheckBox>
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>
#include <QDir>

#include <dlfcn.h>

#include "/home/semen/qtProjects/QtProjects/AbstractClasses/abstractclasses.h"
#include "readdirectory.h"

class ExecutionSumWidget : public AbstractExecutionWidget
{
    Q_OBJECT

public:
    ExecutionSumWidget(QWidget *parent = nullptr, std::string pathForScan = "");
    ~ExecutionSumWidget() override;

public slots:
    void updateProgress() override;
    void showConnection() override;
    void startExecution() override;

private:
    QLabel       * m_label;
    QProgressBar * m_progressBar;
    QTimer       * m_timer;
    QCheckBox    * m_checkBox;
    QPushButton  * m_continue;

    ReadDirectory m_readDirectory;

    std::string m_pathForScan;
    void * m_lib;


private:
    void memoryAllocation() override;
    void setUpWidgets() override;
    void setUpProgress() override;
//    void callback(const std::string& path, const std::string& format, const std::string& operation);
//    void releaseWidgetInstance(AbstractExecutionWidget *instance);

};

extern "C" void *getWidgetInstance(std::string pathForScan = "");
extern "C" void  releaseWidgetInstance(QWidget* instance);
extern "C" std::string *getInfo();
#endif // EXECUTIONSUMWIDGET_H
