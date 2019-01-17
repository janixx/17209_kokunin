#ifndef CONTROL_H
#define CONTROL_H

#include <QColor>
#include <QTimer>
#include <QVector>

#include "gamewidget.h"
#include "mainwindow.h"

class ControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControlWidget(QWidget * parent = nullptr);
    virtual ~ControlWidget() {}

public slots:
    void startGame(const int &number = -1); // start
    void stopGame(); // finish
    void clear(); // clear

    int cellRow();
    void setCellRow(int y);

    int cellColumn();
    void setCellColumn(int x);

    int interval();
    void setInterval(int msec);

    QColor masterColor();
    void setMasterColor(const QColor &color);

signals:
    void countRowChanged(bool ok);
    void countColumnChanged(bool ok);
    void intervalChanged(bool ok);
    void resetGame(bool ok);

private:
    QColor myMasterColor;
    std::unique_ptr<GameWidget> game;
    std::pair<int, int> fieldSize;
};


#endif // CONTROL_H
