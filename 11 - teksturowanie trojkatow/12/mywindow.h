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
    QImage obraz1, obrazpom, obraz2;
    //QImage *img;
    std::vector<QImage> zdjecia;

    int szer;
    int wys;
    int poczX;
    int poczY;


    int x0, y0, x1, y1, x, y, licznik, licznik2, x3,y3,x4,y4;
    float a, b;
    std::vector<int>vectorx;
    std::vector<int>vectory;
    std::vector<int>vectorx2;
    std::vector<int>vectory2;


    void czysc();
    void rysuj1();
    void rysuj2();
    void pix(int x,int y);
    void pix2(int X, int Y);
    void pix3(int x, int y, int r, int g, int b);
    void Kreska(int x0, int y0, int x1, int y1);
    void Kreska2(int x3, int y3, int x4, int y4);
    void teksturuj();

private slots:
    void on_draw2Button_clicked();
    void on_draw1Button_clicked();
    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void on_pushButton_clicked();
};

#endif
