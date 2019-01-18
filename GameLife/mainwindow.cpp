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

    connect(ui->StartButton, SIGNAL(clicked()), gui.get(), SLOT(startGame()));
    connect(ui->StopButton, SIGNAL(clicked()), gui.get(),SLOT(stopGame()));
    connect(ui->ClearButton, SIGNAL(clicked()), gui.get(),SLOT(clear()));

    connect(ui->TimeSlider, SIGNAL(valueChanged(int)), gui.get(), SLOT(setInterval(int)));
    connect(ui->HorizCountSlider, SIGNAL(valueChanged(int)), gui.get(), SLOT(setFieldWidth(int)));
    connect(ui->VerticalCountSlider, SIGNAL(valueChanged(int)), gui.get(), SLOT(setFieldHeight(int)));

    connect(gui.get(),SIGNAL(environmentChanged(bool)),ui->HorizCountSlider,SLOT(setDisabled(bool)));
    connect(gui.get(),SIGNAL(gameEnds(bool)),ui->HorizCountSlider,SLOT(setEnabled(bool)));
    connect(gui.get(),SIGNAL(environmentChanged(bool)),ui->VerticalCountSlider,SLOT(setDisabled(bool)));
    connect(gui.get(),SIGNAL(gameEnds(bool)),ui->VerticalCountSlider,SLOT(setEnabled(bool)));
    connect(ui->ColourButton, SIGNAL(clicked()), this, SLOT(selectMasterColor()));

    ui->Control->activate();
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::selectMasterColor()
{
    QColor color = QColorDialog::getColor(currentColor, this, tr("Select color of figures"));
    if(!color.isValid())
        return;
    currentColor = color;
    gui->setMasterColor(color);
    QPixmap icon(16, 16);
    icon.fill(color);
    ui->ColourButton->setIcon( QIcon(icon) );
}
