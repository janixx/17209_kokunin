#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "control.h"

MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentColor(QColor("#000")),
    ControlWidget control(new ControlWidget(this))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
