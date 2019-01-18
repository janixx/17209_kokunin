#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColor>
#include <QMainWindow>

class GameWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

public slots:
    void selectMasterColor();

private:
    Ui::MainWindow * ui;
    QColor currentColor;
    std::unique_ptr<GameWidget> gui;
};

#endif // MAINWINDOW_H
