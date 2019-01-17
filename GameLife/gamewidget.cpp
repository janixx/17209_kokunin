#include <QMessageBox>

#include "gamewidget.h"

int GameWidget::interval()
{
    return timer->interval();
}

void GameWidget::setInterval(int msec)
{
    timer->setInterval(msec);
}

GameWidget::GameWidget(QWidget * parent) :
    QWidget(parent),
    timer(new QTimer(this)),
    myMasterColor("#000")
{
    timer->setInterval(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
}

void GameWidget::newGeneration()
{
    if (game.newGenerate() == true)
        QMessageBox::information(this,
                                 tr("Game lost sense"),
                                 tr("The End. Now game finished because all the next generations will be the same."),
                                 QMessageBox::Ok);
    update();
}

int GameWidget::fieldHeight()
{
    return static_cast<int>(game.getSize().first);
}

int GameWidget::fieldWidth()
{
    return static_cast<int>(game.getSize().second);
}

void GameWidget::setFieldHeight(int height)
{
    game.setWidth(static_cast<size_t>(height));
}

void GameWidget::setFieldWidth(int width)//fix it!
{
    game.setWidth(static_cast<size_t>(width));
}

void GameWidget::startGame()
{
    timer->start();
}

void GameWidget::stopGame()
{
    timer->stop();
}

void GameWidget::clear()
{
    game.clear();
    gameEnds(true);
    update();
}

QColor GameWidget::masterColor()
{
    return myMasterColor;
}

void GameWidget::setMasterColor(const QColor &color)
{
    myMasterColor = color;
    update();
}
