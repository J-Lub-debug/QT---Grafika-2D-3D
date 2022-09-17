#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <stack>
#include <vector>

namespace Ui {
    class MyWindow;
}

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = 0);
    ~MyWindow();

private:
    Ui::MyWindow *ui;

    QImage img, img4;
    //QImage *img;
    std::vector<QImage> zdjecia;

    int szer;
    int wys;
    int poczX;
    int poczY;

    double r,g,b;


    void czysc();
    void rysuj1();
    void rysuj2();
    void pix(int x,int y);
    void alpaBlend(float alfa, QImage IMG0, QImage IMG1);
    void Multiply(float alfa, QImage IMG0, QImage IMG1);
    void ScreenMode(float alfa, QImage IMG0, QImage IMG1);
    std::vector<double> RgbNaHsv(double r, double g, double b);

private slots:
    void on_draw2Button_clicked();
    void on_draw1Button_clicked();
    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);
};

#endif
