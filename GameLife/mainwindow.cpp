#include <QColorDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentColor(QColor("#000"))
{
    ui->setupUi(this);

    QPixmap icon(16, 16);
    icon.fill(currentColor);
    ui->colorButton->setIcon( QIcon(icon) );

    ui->colorButton->setIcon(QIcon(icon));
    ui->widthSlider->setRange(ui->game->minWidth(), ui->game->maxWidth());
    ui->heightSlider->setRange(ui->game->minHeight(), ui->game->maxHeight());
    ui->intervalSlider->setRange(50, 1000);
    ui->widthSlider->setValue(ui->game->minWidth());
    ui->heightSlider->setValue(ui->game->minHeight());
    ui->intervalSlider->setValue(ui->game->interval());
    ui->squareButton->click();

    connect(ui->StartButton, SIGNAL(clicked()), ui->game, SLOT(startGame()));
    connect(ui->StopButton, SIGNAL(clicked()), ui->game,SLOT(stopGame()));
    connect(ui->ClearButton, SIGNAL(clicked()), ui->game,SLOT(clear()));
    connect(ui->applyButton, SIGNAL(clicked()), ui->game, SLOT(setParametrs()));

    connect(ui->widthSlider, SIGNAL(valueChanged(int)), ui->game, SLOT(setFieldWidth(int)));
    connect(ui->heightSlider, SIGNAL(valueChanged(int)), ui->game, SLOT(setFieldHeight(int)));
    connect(ui->intervalSlider, SIGNAL(valueChanged(int)), ui->game, SLOT(setInterval(int)));


    connect(ui->game, SIGNAL(gameStart(bool)),ui->applyButton,SLOT(setDisabled(bool)));
    connect(ui->game,SIGNAL(gameEnds(bool)),ui->applyButton,SLOT(setEnabled(bool)));
    //connect(ui->game,SIGNAL(environmentChanged(bool)),ui->widthSlider,SLOT(setDisabled(bool)));
    //connect(ui->game,SIGNAL(gameEnds(bool)),ui->widthSlider,SLOT(setEnabled(bool)));
    //connect(ui->game,SIGNAL(environmentChanged(bool)),ui->heightSlider,SLOT(setDisabled(bool)));
    //connect(ui->game,SIGNAL(gameEnds(bool)),ui->heightSlider,SLOT(setEnabled(bool)));
    connect(ui->colorButton, SIGNAL(clicked()), this, SLOT(selectMasterColor()));

    //ui->Control->activate();
    //ui->mainLayout->setStretchFactor(ui->fieldLayout, 8);
    ui->mainLayout->setStretchFactor(ui->setLayout, 2);
    //ui->fieldLayout->addWidget(ui->game);
    //ui->game->show();
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
    ui->game->setMasterColor(color);
    QPixmap icon(16, 16);
    icon.fill(color);
    ui->colorButton->setIcon( QIcon(icon) );
}
