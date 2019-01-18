#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QTimer>
#include <QWidget>

#include "game.h"

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget() {}

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);

signals:
    //when one of the cell has been changed,emit this signal to lock the universeSize
    void environmentChanged(bool ok);
    //when game is over or clear is called,emit it to unlock the universeSize
    void gameEnds(bool ok);

public slots:
    void startGame(); // start
    void stopGame(); // finish
    void clear(); // clear

    int fieldHeight();
    int fieldWidth();
    void setFieldHeight(int height);
    void setFieldWidth(int width);

    int interval();
    void setInterval(int msec); // set interval between generations

    QColor masterColor();
    void setMasterColor(const QColor &color);

protected slots:
    void selectMasterColor();
    void paintGrid(QPainter & p);
    void paintUniverse(QPainter & p);
    void newGeneration();

private:
    QTimer * timer;
    QColor myMasterColor;
    QColor currentColor;
    Game game;
    Ui::MainWindow * ui;
};

#endif // GAMEWIDGET_H
