#include <QColorDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>

#include "gamewidget.h"

int GameWidget::interval()
{
    return timer->interval();
}

void GameWidget::setInterval(int msec)
{
    _interval = msec;
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
    if (game.newGenerate() == false) {
        QMessageBox::information(this,
                                 tr("Game lost sense"),
                                 tr("The End. Now game finished because all the next generations will be the same."),
                                 QMessageBox::Ok);
        stopGame();
        emit gameEnds(true);
    }

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
    _height = static_cast<size_t>(height);
}

void GameWidget::setFieldWidth(int width)//fix it!
{
    _width = static_cast<size_t>(width);
}

void GameWidget::setParametrs()
{

}

void GameWidget::startGame()
{
    timer->start();
    environmentChanged(true);
}

void GameWidget::stopGame()
{
    timer->stop();
    emit gameEnds(true);
}

void GameWidget::clear()
{
    game.reset();
    emit gameEnds(true);
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

void GameWidget::paintGrid(QPainter & p)
{
    QColor gridColor = ("#000");
    QRect borders(0, 0, width()-1, height()-1); // borders of the universe
    //QColor gridColor = myMasterColor; // color of the grid
    gridColor.setAlpha(10); // must be lighter than main color
    p.setPen(gridColor);

    double cellWidth = static_cast<double>(width()) / game.getSize().first; // width of the widget / number of cells at one row
    for(double k = cellWidth; k <= width(); k += cellWidth)
        p.drawLine(k, 0, k, height());

    double cellHeight = static_cast<double>(height()) / game.getSize().second; // height of the widget / number of cells at one row
    for(double k = cellHeight; k <= height(); k += cellHeight)
        p.drawLine(0, k, width(), k);

    p.drawRect(borders);
}

void GameWidget::paintUniverse(QPainter & p)
{
    size_t x = 0u, y = 0u;
    double cellWidth = static_cast<double>(width()) / game.getSize().first;
    double cellHeight = static_cast<double>(height()) / game.getSize().second;
    for(y = 1u; y <= game.getSize().second; y++) {
        for(x = 1u; x <= game.getSize().first; x++) {
            if(game.isAlive(x,y) == true) { // if there is any sense to paint it
                qreal left = static_cast<qreal>(cellWidth * x - cellWidth); // margin from left
                qreal top  = static_cast<qreal>(cellHeight * y - cellHeight); // margin from top
                QRectF r(left, top, static_cast<qreal>(cellWidth),
                                    static_cast<qreal>(cellHeight));
                p.fillRect(r, QBrush(myMasterColor)); // fill cell with brush of main color
            }
        }
    }
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
}

void GameWidget::mousePressEvent(QMouseEvent *e)
{
    emit environmentChanged(true);
    double cellWidth = static_cast<double>(width()) / game.getSize().first;
    double cellHeight = static_cast<double>(height()) / game.getSize().second;
    size_t y = static_cast<size_t>(e->y() / cellHeight) + 1;
    size_t x = static_cast<size_t>(e->x() / cellWidth) + 1;

    game.setCellReverse(x, y);
    update();
}

void GameWidget::mouseMoveEvent(QMouseEvent * e)
{
    double cellWidth = static_cast<double>(width()) / game.getSize().first;
    double cellHeight = static_cast<double>(height()) / game.getSize().second;
    size_t y = static_cast<size_t>(e->y() / cellHeight) + 1;
    size_t x = static_cast<size_t>(e->x() / cellWidth) + 1;
    if(!game.willAlive(x, y)){                //if current cell is empty,fill in it
        game.setCellDead(x, y);
        update();
    }
}
