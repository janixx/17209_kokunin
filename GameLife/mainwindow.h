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

private slots:
    void on_StartButton_clicked();

    void on_HorizCountSlider_valueChanged(int value);

    void on_TimeSlider_valueChanged(int value);

    void on_VerticalCountSlider_valueChanged(int value);

    void on_StopButton_clicked();

    void on_ClearButton_clicked();

private:
    Ui::MainWindow * ui;
    QColor currentColor;
    std::unique_ptr<GameWidget> gui;
};

#endif // MAINWINDOW_H
