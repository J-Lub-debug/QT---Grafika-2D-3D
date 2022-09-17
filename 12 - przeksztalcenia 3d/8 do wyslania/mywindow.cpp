#include "mywindow.h"
#include <cmath>
#include "ui_mywindow.h"
#include <iostream>
#include <QFileDialog>
#include <QDebug>
#include <vector>

#define PI 3.14159265


MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);

    szer = 600;
    wys = 600;
    poczX = 0;
    poczY = 0;

    img = QImage(szer,wys,QImage::Format_RGB32);
    bits = img.bits();

    zeruj();
    odleglosc = 150;

    tx = ty = tz = alfa = alfaX = alfaY = alfaZ = Shx = Shy = Shz = 0;
    Scx = Scy = Scz = 1; // Rysuje od srodka 50

    v1 = {0,0,0,0};

    v2 = {0,0,0,0};

    Translacja = {{1, 0, 0, tx},
                        {0, 1, 0, ty},
                        {0, 0, 1, tz},
                        {0, 0, 0, 1}};

    Skalowanie = {{Scx, 0, 0, 0},
                        {0, Scy, 0, 0},
                        {0, 0, Scz, 0},
                        {0, 0, 0, 1}};

    ObrotX = {{1, 0, 0, 0},
              {0, cos(alfa), -sin(alfa), 0},
              {0, sin(alfa), cos(alfa), tz},
              {0, 0, 0, 1}};

    ObrotY = {{cos(alfa), 0, sin(alfa), 0},
              {0, 1, 0, 0},
              {-sin(alfa), 0, cos(alfa), 0},
              {0, 0, 0, 1}};

    ObrotZ = {{cos(alfa), -sin(alfa), 0 , 0},
              {sin(alfa), cos(alfa), 0, 0},
              {0, 0, 1, 0},
              {0, 0, 0, 1}};

    PochylenieX = {{1, 0, 0 , 0},
                  {Shy, 1, 0, 0},
                  {Shz, 0, 1, 0},
                  {0, 0, 0, 1}};

    PochylenieY = {{1, Shx, 0, 0},
                  {0, 1, 0, 0},
                  {0, Shz, 1, 0},
                  {0, 0, 0, 1}};

    PochylenieZ = {{1, 0, Shx , 0},
                  {0, 1, Shy, 0},
                  {0, 0, 1, 0},
                  {0, 0, 0, 1}};

    for(int i=0; i<8; i++) {
        konwertujNa2D(x[i],y[i],z[i],i);
    }
    rysujKreski();



}
void MyWindow::rysujKreski()
{
    Kreska(px[3], py[3], px[2], py[2]);
    Kreska(px[0], py[0], px[1], py[1]);
    Kreska(px[0], py[0], px[3], py[3]);
    Kreska(px[1], py[1], px[2], py[2]);
    Kreska(px[7], py[7], px[6], py[6]);
    Kreska(px[4], py[4], px[5], py[5]);
    Kreska(px[4], py[4], px[7], py[7]);
    Kreska(px[5], py[5], px[6], py[6]);
    Kreska(px[0], py[0], px[4], py[4]);
    Kreska(px[2], py[2], px[6], py[6]);
    Kreska(px[1], py[1], px[5], py[5]);
    Kreska(px[3], py[3], px[7], py[7]);
}

void MyWindow::konwertujNa2D(double x, double y, double z, int i)
{
    pp.clear();
    pp.push_back(x);
    pp.push_back(y);
    pp.push_back(0);
    pp.push_back(z*(1/odleglosc)+1);
    for(int j = 0; j < 4; ++j) pp[j] = pp[j]/pp[3];
    punktx.push_back((int)pp[0]+300);
    punkty.push_back((int)pp[1]+300);
    px[i]=pp[0]+300;
    py[i]=pp[1]+300;
    rysujPunkt(pp[0]+300,pp[1]+300);
}

void MyWindow::rysujPunkt(double x, double y)
{
    for (int i=-5; i<=5; i++)
    {
        for (int j=-5; j<=5; j++)
        {
            pix(x+i,y+j);
        }
    }
    update();
}

void MyWindow::zeruj()
{
    x[0]=-50;
    y[0]=-50;
    z[0]=0;

    x[1]=50;
    y[1]=-50;
    z[1]=0;

    x[2]=50;
    y[2]=50;
    z[2]=0;

    x[3]=-50;
    y[3]=50;
    z[3]=0;

    x[4]=-50;
    y[4]=-50;
    z[4]=100;

    x[5]=50;
    y[5]=-50;
    z[5]=100;

    x[6]=50;
    y[6]=50;
    z[6]=100;

    x[7]=-50;
    y[7]=50;
    z[7]=100;
}

MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::on_exitButton_clicked()
{
    qApp->quit();
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,img);
}

void MyWindow::on_cleanButton_clicked()
{
    czysc();

    update();
}

void MyWindow::on_draw1Button_clicked()
{
    rysuj1();
    update();
}

void MyWindow::on_draw2Button_clicked()
{
    rysuj2();
    update();
}

void MyWindow::czysc()
{
    unsigned char *ptr;

    ptr = img.bits();

    int i,j;

    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]=0; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 0; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 0; // Skladowa RED
        }
    }
}

void MyWindow::rysuj1()
{
        unsigned char *ptr;
        ptr = img.bits();
        int szer = img.width();
        int wys = img.height();

        int i,j;
        for(i=0;i<wys;i++)
        {
                for(j=0;j<szer ;j++)
                {
                        ptr[szer*4*i + 4*j]=i;
                        ptr[szer*4*i + 4*j + 1] = j;
                        ptr[szer*4*i + 4*j + 2] = i*j;
                }
        }
}

void MyWindow::rysuj2()
{
        unsigned char *ptr;
        ptr = img.bits();
        int szer = img.width();
        int wys = img.height();

        int i,j;
        for(i=0;i<wys;i++)
        {
                for(j=0;j<szer ;j++)
                {
                        ptr[szer*4*i + 4*j]=i;
                        ptr[szer*4*i + 4*j + 1] = j;
                        ptr[szer*4*i + 4*j + 2] = i+j;
                }
        }
}

void MyWindow::pix(int x, int y)
{
    if(x < 0 || y < 0 || x>=600 || y>=600) return;
    unsigned char* ptr = img.bits();

    ptr[szer*4*y + 4*x]= 255;
    ptr[szer*4*y + 4*x + 1] = 255;
    ptr[szer*4*y + 4*x + 2] = 255;

}

void MyWindow::Kreska(int x0, int y0, int x1, int y1)
{
    a = (float)(y1-y0)/(x1-x0); // m
    b = (y0) - a * x0;

    if(x0 == x1)
    {
        if(y0 > y1)
        {
            for (int y = y1 ; y != y0; y++)
            {
                pix(x0, y);
            }
        }
        if(y0 <= y1)
        {
            for (int y = y0; y != y1; y++)
            {
                pix(x0, y);
            }

        }
    }
    if(x0 != x1)
    {
        if(y0 > y1)
        {
            for (int y = y1 ; y != y0; y++)
            {
                int x = (y-b)/a;
                pix(x, y);
            }
        }
        if(y0 <= y1)
        {
            for (int y = y0; y != y1; y++)
            {
                int x = (y-b)/a;
                pix(x, y);
            }

        }
    }
    if(x0 < x1)
    {
        for (int x=x0; x<x1; x++)
        {
            int y=a*x+b;
            pix(x,y);
        }
    }
    if(x0 > x1)
    {
        for (int x=x1; x<x0; x++)
        {
            int y=a*x+b;
            pix(x,y);
        }
    }
    update();

}

void MyWindow::czyscEkran()
{
    for(int i = 0; i < 600; i++) {
        for(int j = 0; j < 600; j++) {
            bits[600*4*i + 4*j]     = 0;
            bits[600*4*i + 4*j + 1] = 0;
            bits[600*4*i + 4*j + 2] = 0;
        }
    }
}
// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    if(event->button() == Qt::RightButton)
    {
    }
    else
    {
    }
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        return;
    }
    else
    {
        return;
    }
    update();
}

void MyWindow::on_pushButton_clicked()
{
}

void MyWindow::przeksztalcenie()
{
    czyscEkran();
    zeruj();
    double srodekx = 0;
    double srodeky = 0;
    double srodekz = 0;
    for(int i = 0; i < 8; i++) {
        srodekx = srodekx + x[i];
        srodeky = srodeky + y[i];
        srodekz = srodekz + z[i];
    }
    srodekx = srodekx/8;
    srodeky = srodeky/8;
    srodekz = srodekz/8;

    for(int i = 0; i < 8; i++) {
        x[i] = x[i] - srodekx;
        y[i] = y[i] -  srodeky;
        z[i] = z[i] - srodekz;
    }
    for(int i=0; i<8; i++) {
        v1 = {x[i], y[i], z[i], 1};
        v2 = Translacja*Skalowanie*ObrotZ*ObrotY*ObrotX * PochylenieZ* PochylenieY*PochylenieX* v1;//Translacja*Skalowanie*ObrotZ*ObrotY*ObrotX * v1;

        v1.print();
        v2.print();

        konwertujNa2D(v2[0]+srodekx,v2[1]+0.5+srodeky,v2[2]+0.5+srodekz,i);
        rysujKreski();
    }
}

void MyWindow::on_horizontalSlider_valueChanged(int value)
{
    alfaX = value*PI/180;
    ObrotX(1,1) = cos(alfaX);
    ObrotX(1,2) = -sin(alfaX);
    ObrotX(2,1) = sin(alfaX);
    ObrotX(2,2) = cos(alfaX);
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_2_valueChanged(int value)
{
    tx = value;
    Translacja(0,3) = tx;
    //std::cout << Translacja << std::endl;
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_3_valueChanged(int value)
{
    ty = value;
    Translacja(1,3) = ty;
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_4_valueChanged(int value)
{
    tz = value;
    Translacja(2,3) = tz;
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_5_valueChanged(int value)
{
    Scx = value/10.0;
    Skalowanie(0,0) = Scx;
    przeksztalcenie();

}

void MyWindow::on_horizontalSlider_6_valueChanged(int value)
{
    Scy = value/10.0;
    Skalowanie(1,1) = Scy;
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_7_valueChanged(int value)
{
    Scz = value/10.0;
    Skalowanie(2,2) = Scz;
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_8_valueChanged(int value)
{
    alfaY = value*PI/180;
    ObrotY(0,0) = cos(alfaY);
    ObrotY(0,2) = sin(alfaY);
    ObrotY(2,0) = -sin(alfaY);
    ObrotY(2,2) = cos(alfaY);
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_9_valueChanged(int value)
{
    alfaZ = value*PI/180;
    ObrotZ(0,0) = cos(alfaZ);
    ObrotZ(0,1) = -sin(alfaZ);
    ObrotZ(1,0) = sin(alfaZ);
    ObrotZ(1,1) = cos(alfaZ);
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_10_valueChanged(int value)
{
    Shx = value;
    PochylenieY(0,1) = Shx;
    PochylenieZ(0,2) = Shx;
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_11_valueChanged(int value)
{
    Shy = value;
    PochylenieX(1,0) = Shy;
    PochylenieZ(1,2) = Shy;
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_12_valueChanged(int value)
{
    Shz = value;
    PochylenieX(2,0) = Shz;
    PochylenieY(2,1) = Shz;
    przeksztalcenie();
}
