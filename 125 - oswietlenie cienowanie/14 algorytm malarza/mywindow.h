#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <stack>
#include <vector>
#include <armadillo>

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

    QImage img, tekstura, wynik;
    unsigned char *bits;

    bool PrzedniaWidoczna, PrawaWidoczna, LewaWidoczna, GornaWidoczna, DolnaWidoczna, TylnaWidoczna;
    int szer;
    int wys;
    int poczX;
    int poczY;
    float a,b;

    double odleglosc;
    double x[8];
    double y[8];
    double z[8];
    double srodekx, srodeky, srodekz;

    double xx[8];
    double yy[8];
    double zz[8];
    double cosinus;

    std::vector <double> punktx;
    std::vector <double> punkty;
    double px[8];
    double py[8];
    double pz[8];
    std::vector <double> pp;

    float tx, ty, tz, Scx, Scy, Scz, alfa, alfaX, alfaY, alfaZ, Shx, Shy, Shz;

    arma::mat Translacja, Skalowanie, ObrotX, ObrotY, ObrotZ, PochylenieX, PochylenieY, PochylenieZ;
    arma::vec v1, v2;
    std::vector<int>vectorx;
    std::vector<int>vectory;
    std::vector<int>vectorx2;
    std::vector<int>vectory2;

    void czysc();
    void rysuj1();
    void rysuj2();
    void pix(int x,int y);
    void Kreska(int x0, int y0, int x1, int y1);
    void konwertujNa2D(double x, double y, double z, int i);
    void czyscEkran();
    void zeruj();
    void przeksztalcenie();
    void teksturuj(int px0, int py0, int px1, int py1, int px2, int py2, int px3, int py3, double kat);
    void pix2(int x, int y, int r, int g, int b);
    void WidocznoscScianyISwiatlo();

private slots:
    void on_draw2Button_clicked();
    void on_draw1Button_clicked();
    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void on_pushButton_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);
    void on_horizontalSlider_4_valueChanged(int value);
    void on_horizontalSlider_5_valueChanged(int value);
    void on_horizontalSlider_6_valueChanged(int value);
    void on_horizontalSlider_7_valueChanged(int value);
    void on_horizontalSlider_8_valueChanged(int value);
    void on_horizontalSlider_9_valueChanged(int value);
    void on_horizontalSlider_10_valueChanged(int value);
    void on_horizontalSlider_11_valueChanged(int value);
    void on_horizontalSlider_12_valueChanged(int value);
};

#endif
