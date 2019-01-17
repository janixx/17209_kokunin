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
    size(std::make_pair(50,50)),
    myMasterColor("#000")
{
    timer->setInterval(300);
    //myMasterColor = "#000";
    universe.resize((size.first + 2) * (size.second + 2));
    nextGen.resize((size.first + 2) * (size.second + 2));
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
}

int GameWidget::cellColumn()
{
    return size.first;
}

int GameWidget::cellRow()
{
    return size.second;
}

void GameWidget::setCellColumn(int column)
{
    if (column > 5 && column < 100)
        size.first = column;
}

void GameWidget::setCellRow(int row)
{
    if (row > 5 && row < 100)
        size.second = row;
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
    universe.clear();
    gameEnds(true);
    update();
}

void GameWidget::resetUniverse() // а это надо?
{
    universe.clear();
    nextGen.clear();
    universe.resize(size.first * size.second);
    nextGen.resize(size.first * size.second);
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

bool GameWidget::isAlive(int x, int y)
{
    int power = 0;
    power += universe[(y + 1) * size.first +  x];
    power += universe[(y - 1) * size.first +  x];
    power += universe[y * size.first +  x + 1];
    power += universe[y * size.first +  x - 1];
    power += universe[(y - 1) * size.first +  x - 1];
    power += universe[(y - 1) * size.first +  x + 1];
    power += universe[(y + 1) * size.first +  x - 1];
    power += universe[(y + 1) * size.first +  x + 1];
    if (((universe[y * size.first +  x] == true) && (power == 2)) || (power == 3))
           return true;
    return false;
}

void GameWidget::newGeneration()
{
    int notChanged=0;
    for(int x=1; x <= size.first; x++) {
        for(int y=1; y <= size.second; y++) {
            nextGen[y * size.first + x] = isAlive(x,y);
            if(nextGen[y * size.first + x] == universe[y * size.first + x])
                notChanged++;
        }
    }
    if(notChanged == size.first * size.second) {
        QMessageBox::information(this,
                                 tr("Game lost sense"),
                                 tr("The End. Now game finished because all the next generations will be the same."),
                                 QMessageBox::Ok);
        stopGame();
        gameEnds(true);
        return;
    }

    universe = nextGen;

    update();
}

