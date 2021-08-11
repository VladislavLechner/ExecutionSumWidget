#include "executionsumwidget.h"

static ExecutionSumWidget* m_instance = nullptr;

ExecutionSumWidget::ExecutionSumWidget(QWidget *parent, std::string pathForScan)
    : AbstractExecutionWidget(parent), m_pathForScan(pathForScan)
{
    setMinimumSize(460,280);
    setMaximumSize(460,280);

    memoryAllocation();
    setUpWidgets();

    connect(m_timer, &QTimer::timeout      ,
            this   , &ExecutionSumWidget::updateProgress);

    connect(m_checkBox, &QCheckBox::clicked,
            this, &ExecutionSumWidget::showConnection);

}

ExecutionSumWidget::~ExecutionSumWidget()
{
    qDebug() << "ExecutionSumWidget Destructor";
//    releaseWidgetInstance(m_instance);
}

void ExecutionSumWidget::updateProgress()
{
    m_progressBar->setValue(m_progressBar->value() + 1);
    if (m_progressBar->value() == m_progressBar->maximum())
    {
        m_label->setText("Done!");
        m_label->setGeometry(220, 80, 100,30);
        m_timer->stop();
    }
}

void ExecutionSumWidget::showConnection()
{
    if (m_checkBox->isChecked())
        m_continue->show();
    else
        m_continue->hide();
}

void ExecutionSumWidget::memoryAllocation()
{
    m_label = new QLabel("          You need to\n         transfer data\n via the input widget", this);
    m_progressBar = new QProgressBar(this);
    m_timer = new QTimer(this);
    m_checkBox = new QCheckBox("Connect to the next stage", this);
    m_continue = new QPushButton("Continue", this);
}

void ExecutionSumWidget::setUpWidgets()
{
    m_label->setGeometry(170, 50, 140,60);
    m_progressBar->setGeometry(180,110,120,30);
    m_checkBox->setGeometry(140,140,200,30);
    m_continue->setGeometry(180,170,120,30);

    m_continue->hide();
}

void ExecutionSumWidget::startExecution()
{
    try {
        std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;
        m_label->setText("Execution...");
        m_label->setGeometry(200, 80, 100,30);

        std::thread th(&ReadDirectory::checkInputData, &m_readDirectory, m_path, m_format, m_operation);

        setUpProgress();
        th.join();

    }  catch (...) {
        std::exception_ptr ex;
        if (m_readDirectory.exception_ptr() == nullptr)
             ex = std::current_exception();
        else
             ex = m_readDirectory.exception_ptr();
        handle_eptr(ex);
        std::cout << "EXCEPTION!!!" << std::endl;
    }
}

void ExecutionSumWidget::setUpProgress()
{
    m_progressBar->setMaximum(0);
    m_progressBar->setMaximum(100);

    m_timer->start(50);
}

QVariant ExecutionSumWidget::resultOfExecution()
{
    return {};
}


void *getWidgetInstance(std::string pathForScan)
{
    if(m_instance == nullptr)
    {
        qDebug() << m_instance;
        m_instance = new ExecutionSumWidget(nullptr, pathForScan);
    }
    return m_instance;
}



void releaseWidgetInstance(QWidget* instance)
{
    instance = reinterpret_cast<ExecutionSumWidget *>(instance);
//    instance->close();
    if(instance != nullptr)
        {
//            qDebug() << instance << m_instance;
            delete instance;
            m_instance = nullptr;
        }
}

std::string *getInfo()
{
    return (new std::string("Это библиотека предназначена для вычисления входных данных, которые будут переданы пользователем через входное приложение"));
}
