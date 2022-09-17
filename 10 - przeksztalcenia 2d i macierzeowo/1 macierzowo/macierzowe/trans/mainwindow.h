#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QPainter>
#include <QLabel>
#define PI 3.14159265
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QImage *img;
    QImage *temp;
    QSlider *slider[7];
    QLabel *label[7];
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Draw();
    void paintEvent(QPaintEvent*);

private:
    Ui::MainWindow *ui;
private slots:
    void transformuj();
    void reset();
};

#endif // MAINWINDOW_H
