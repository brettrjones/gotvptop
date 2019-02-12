#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qttestsharedlib3.h"
#include "qtteststaticlib3.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QtTestSharedLib sharedLib;
    QtTestStaticLib staticLib;


    char textBuf[16000];
    sprintf( textBuf, "sizeof void * %d\n, int %d\n long %d\n longlong %d\n float %d\n double %d shared value %d static value %d\n",
             sizeof(void *), sizeof(int), sizeof(long), sizeof(long long), sizeof(float), sizeof(double),
             staticLib.getStaticValue(),
             sharedLib.getSharedValue()
             );
    ui->labelTextOut->setText(textBuf);
}

MainWindow::~MainWindow()
{
    delete ui;
}
