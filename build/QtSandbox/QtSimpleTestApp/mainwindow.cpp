#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qttestsharedlib2.h"
#include "qtteststaticlib2.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if defined(TEST_SHARED_LIB)
    QtTestStaticLib staticLib;
    QtTestSharedLib sharedLib;
    staticLib.printStuff();
    sharedLib.printStuff();

    char textBuf[16000];
    sprintf( textBuf, "sizeof void * %d\n, int %d\n long %d\n longlong %d\n float %d\n double %d\n staticlib value %d sharedlib value %d\n",
             sizeof(void *), sizeof(int), sizeof(long), sizeof(long long), sizeof(float), sizeof(double),
             staticLib.getStaticValue(),
             sharedLib.getSharedValue() );
#else
    QtTestStaticLib staticLib;
    //staticLib.printStuff();

    char textBuf[16000];
    sprintf( textBuf, "sizeof void * %d\n, int %d\n long %d\n longlong %d\n float %d\n double %d\n staticlib value %d\n",
             sizeof(void *), sizeof(int), sizeof(long), sizeof(long long), sizeof(float), sizeof(double),
             staticLib.getStaticValue() );
#endif // defined(TEST_SHARED_LIB)

    ui->labelTextOut->setText(textBuf);
}

MainWindow::~MainWindow()
{
    delete ui;
}
