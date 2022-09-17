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

    int x0, y0, x1, y1, m;

    int tabx[100];
    int taby[100];
    int i;
    int licznik;
    int X[100];
    int Y[100];
    int d;
    double t, x, y;

    std::stack<int> stosx;
    std::stack<int> stosy;
    int zm;
    float a, b;
    bool TRAFIONY;




    void czysc();
    void rysuj1();
    void rysuj2();
    void pix(int x,int y);
    bool czyJestzamalowany(int x, int y);
    void Bezier();
    void Kreska(int x0, int y0, int x1, int y1);

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
