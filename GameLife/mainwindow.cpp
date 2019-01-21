#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QTextStream>

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


    connect(ui->game, SIGNAL(gameStart(bool)), ui->applyButton, SLOT(setDisabled(bool)));
    connect(ui->game, SIGNAL(gameEnds(bool)), ui->applyButton, SLOT(setEnabled(bool)));

    connect(ui->customButton,SIGNAL(toggled(bool)), ui->game, SLOT(setCustomField(bool)));
    connect(ui->squareButton,SIGNAL(toggled(bool)), ui->game, SLOT(setSquareField(bool)));
    connect(ui->game, SIGNAL(heightChanged(int)), ui->heightSlider, SLOT(setValue(int)));
    connect(ui->game, SIGNAL(widthChanged(int)), ui->widthSlider, SLOT(setValue(int)));

    connect(ui->colorButton, SIGNAL(clicked()), this, SLOT(selectMasterColor()));

    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveGame()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadGame()));

    //ui->mainLayout->setStretchFactor(ui->setLayout, 2);
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

void MainWindow::saveGame()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save current game"),
                                            QDir::homePath(), tr("Conway's Game *.life Files (*.life)"));
    if(filename.length() < 1)
        return;

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;



    QString buf = QString::number(ui->game->square())+"\n";
    file.write(buf.toUtf8());

    buf.clear();
    buf = QString::number(ui->game->fieldWidth())+"\n";
    file.write(buf.toUtf8());

    buf.clear();
    buf = QString::number(ui->game->fieldHeight())+"\n";
    file.write(buf.toUtf8());

    file.write(ui->game->dump().toUtf8());

    buf.clear();
    QColor color = ui->game->masterColor();
    buf = QString::number(color.red())+" "+
          QString::number(color.green())+" "+
          QString::number(color.blue())+"\n";
    file.write(buf.toUtf8());

    buf.clear();
    buf = QString::number(ui->intervalSlider->value())+"\n";
    file.write(buf.toUtf8());

    file.close();
}

void MainWindow::loadGame()
{
    QString filename =
                    QFileDialog::getOpenFileName(this,
                                tr("Open saved game "),
                                    QDir::homePath(),
                                tr("Conway's Game of Life file (*.life)"));
    if(filename.length() < 1)
        return;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);

    int qv;
    in >> qv;

    int wv;
    in >> wv;
    ui->game->setFieldWidth(wv);

    int hv;
    in >> hv;
    ui->game->setFieldHeight(hv);

    QString dump="";
    for(int k=0; k < hv ; k++) {
        QString t;
        in >> t;
        dump.append(t+"\n");
    }

    if(qv == 1 && wv == hv)
        ui->squareButton->click();
    else
        ui->customButton->click();

    ui->game->setParametrs();
    ui->game->setDump(dump);

    if(qv == 1 && wv != hv)
        ui->squareButton->click();

    int r = 0, g = 0, b = 0;
    in >> r >> g >> b;
    currentColor = QColor(r,g,b);
    ui->game->setMasterColor(currentColor);
    QPixmap icon(16, 16);
    icon.fill(currentColor);
    ui->colorButton->setIcon( QIcon(icon) );

    in >> r;
    ui->intervalSlider->setValue(r);
    ui->game->setInterval(r);

    file.close();
}
