#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>

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

    QImage img,img2;

    int szer;
    int wys;
    int poczX;
    int poczY;

    float tx, ty, Scx, Scy, alfa, Shx, Shy;

    void czysc();
    void rysuj1();
    void rysuj2();
    void pix(int X1,int Y1);
    void przeksztalcenie();

private slots:
    void on_draw2Button_clicked();
    void on_draw1Button_clicked();
    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

    void on_horizontalSlider_sliderMoved(int position);
    void on_horizontalSlider_2_sliderMoved(int position);
    void on_horizontalSlider_3_sliderMoved(int position);
    void on_horizontalSlider_4_sliderMoved(int position);
    void on_horizontalSlider_5_sliderMoved(int position);
    void on_horizontalSlider_6_sliderMoved(int position);
    void on_horizontalSlider_7_sliderMoved(int position);
};

#endif
