#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Context.h"
#include "ApplicationInfo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CJNIContext::getJniContext().mainWindowInialized();
    std::string strExecutablePath = CJNIContext::getJniContext().getApplicationInfo().nativeLibraryDir;
    char textBuf[16000];
    sprintf( textBuf, "nativeLib dir %s sizeof void * %d\n, int %d\n long %d\n longlong %d\n float %d\n double %d\n",
             strExecutablePath.c_str(),
             sizeof(void *),
             sizeof(int),
             sizeof(long),
             sizeof(long long),
             sizeof(float),
             sizeof(double)
             );
    ui->labelTextOut->setText(textBuf);
}

MainWindow::~MainWindow()
{
    delete ui;
}
