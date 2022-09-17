#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <stack>

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

    QImage *img;

    int szer;
    int wys;
    int poczX;
    int poczY;
    int midx;
    int midy;
    int edgex;
    int edgey;

    int x0, y0, x1, y1, m, x, y;

    std::stack<int> stosx;
    std::stack<int> stosy;

    float a, b;

    void czysc();
    void rysuj1();
    void rysuj2();
    void pix(int x,int y);
    void pix2(int x, int y);
    bool czyJestzamalowany(int x, int y);
    void dylacja();
    void erozja();

private slots:
    void on_draw2Button_clicked();
    void on_draw1Button_clicked();
    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

};

#endif
