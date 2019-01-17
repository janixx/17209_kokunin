#ifndef CONTROL_H
#define CONTROL_H

#include <QColor>
#include <QTimer>
#include <QWidget>
#include <QVector>


class ControlWidget {
    Q_OBJECT

public:
    ControlWidget(QWidget * parent = nullptr);
    virtual ~ControlWidget() {}

public slots:
    void startGame(const int &number = -1); // start
    void stopGame(); // finish
    void clear(); // clear

    //int cellNumber(); // number of the cells in one row
    void setCellNumber(const int &s); // set number of the cells in one row

    //int interval(); // interval between generations
    void setInterval(int msec); // set interval between generations

    QColor masterColor(); // color of the cells
    void setMasterColor(const QColor &color); // set color of the cells

    QString dump(); // dump of current universe
    void setDump(const QString &data); // set current universe from it's dump

private:
    QColor myMasterColor;
    std::pair<int, int> fieldSize;
    QTimer timer;
    QVector<bool> map;
    QVector<bool> generation;
};


#endif // CONTROL_H
