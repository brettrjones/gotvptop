#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    char textBuf[16000];
    sprintf( textBuf, "sizeof void * %d\n, int %d\n long %d\n longlong %d\n float %d\n double %d\n",
             sizeof(void *), sizeof(int), sizeof(long), sizeof(long long), sizeof(float), sizeof(double)
             );
    ui->labelTextOut->setText(textBuf);
}

MainWindow::~MainWindow()
{
    delete ui;
}
