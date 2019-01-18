#include <QColorDialog>

#include "gamewidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentColor(QColor("#000")),
    gui(new GameWidget(this))
{
    ui->setupUi(this);

    QPixmap icon(16, 16);
    icon.fill(currentColor);

    ui->ColourButton->setIcon(QIcon(icon));
    ui->HorizCountSlider->setRange(50, 1000);
    ui->VerticalCountSlider->setRange(36, 750);
    ui->HorizCountSlider->setValue(50);
    ui->VerticalCountSlider->setValue(36);

    connect(ui->StartButton, SIGNAL(on_StartButton_clicked()), gui.get(), SLOT(startGame()));
    connect(ui->StopButton, SIGNAL(on_StopButton_clicked()), gui.get(),SLOT(stopGame()));
    connect(ui->ClearButton, SIGNAL(on_ClearButton_clicked()), gui.get(),SLOT(clear()));

    connect(ui->TimeSlider, SIGNAL(on_TimeSlider_valueChanged(int)), gui.get(), SLOT(setInterval(int)));
    connect(ui->HorizCountSlider, SIGNAL(on_HorizCountSlider_valueChanged(int)), gui.get(), SLOT(setCellRow(int)));
    connect(ui->VerticalCountSlider, SIGNAL(on_VerticalCountSlider_valueChanged(int)), gui.get(), SLOT(setCellColumn(int)));

    connect(gui.get(),SIGNAL(environmentChanged(bool)),ui->HorizCountSlider,SLOT(setDisabled(bool)));
    connect(gui.get(),SIGNAL(gameEnds(bool)),ui->HorizCountSlider,SLOT(setEnabled(bool)));
    connect(gui.get(),SIGNAL(environmentChanged(bool)),ui->VerticalCountSlider,SLOT(setDisabled(bool)));
    connect(gui.get(),SIGNAL(gameEnds(bool)),ui->VerticalCountSlider,SLOT(setEnabled(bool)));
    connect(ui->ColourButton, SIGNAL(clicked()), gui.get(), SLOT(selectMasterColor()));

    ui->Control->activate();
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_StartButton_clicked()
{

}

void MainWindow::on_HorizCountSlider_valueChanged(int value)
{

}

void MainWindow::on_TimeSlider_valueChanged(int value)
{

}

void MainWindow::on_VerticalCountSlider_valueChanged(int value)
{

}

void MainWindow::on_StopButton_clicked()
{

}

void MainWindow::on_ClearButton_clicked()
{

}

void MainWindow::setColorButton(QIcon icon)
{
    ui->ColourButton->setIcon(QIcon(icon));
}
