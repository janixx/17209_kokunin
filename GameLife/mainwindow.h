#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColor>
#include <QMainWindow>

class ControlWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow * ui;
    QColor currentColor;
    ControlWidget * control;
};

#endif // MAINWINDOW_H
