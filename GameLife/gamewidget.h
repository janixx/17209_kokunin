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

    int maxWidth();
    int maxHeight();
    int minWidth();
    int minHeight();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);

signals:
    //when one of the cell has been changed,emit this signal to lock the applyButton
    void environmentChanged(bool ok);
    //when game is over or clear is called,emit it to unlock the universeSize
    void gameEnds(bool ok);
    //when one of the config has been changed, emit this signal
    void gameStart(bool ok);
    void heightChanged(int x);

public slots:
    void startGame(); // start
    void stopGame(); // finish
    void clear(); // clear

    int fieldHeight();
    int fieldWidth();
    void setFieldHeight(int height);
    void setFieldWidth(int width);
    void setParametrs();

    void setSquareField(bool ok);
    void setCustomField(bool ok);
    int square();

    int interval();
    void setInterval(int msec); // set interval between generations

    QColor masterColor();
    void setMasterColor(const QColor &color);

    QString dump();
    void setDump(const QString &data);

protected slots:
    void paintGrid(QPainter & p);
    void paintUniverse(QPainter & p);
    void newGeneration();

private:
    QTimer * timer;
    QColor myMasterColor;
    QColor currentColor;
    Game game;
    size_t _width;
    size_t _height;
    int _interval;
    bool _changed;
    bool _square;
};

#endif // GAMEWIDGET_H
