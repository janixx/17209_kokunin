#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QTimer>
#include <QWidget>

class GameWidget : public QWidget
{
    Q_OBJECT
private:
    bool isAlive(int x, int y); // return true if universe[x][y] accept rules
    void resetUniverse();// reset the size of universe

public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

signals:
    //when one of the cell has been changed,emit this signal to lock the universeSize
    void environmentChanged(bool ok);
    //when game is over or clear is called,emit it to unlock the universeSize
    void gameEnds(bool ok);

public slots:
    void startGame(); // start
    void stopGame(); // finish
    void clear(); // clear

    int cellColumn();
    int cellRow();  // number of the cells in one row
    void setCellColumn(int c);
    void setCellRow(int s); // set number of the cells in one row

    int interval(); // interval between generations
    void setInterval(int msec); // set interval between generations

    QColor masterColor(); // color of the cells
    void setMasterColor(const QColor &color); // set color of the cells

protected slots:

    void paintGrid(QPainter & p);
    void paintUniverse(QPainter & p);
    void newGeneration();

private:
    QTimer * timer;
    QVector<bool> universe;
    QVector<bool> nextGen;
    std::pair<int,int> size;
    QColor myMasterColor;
};

#endif // GAMEWIDGET_H
