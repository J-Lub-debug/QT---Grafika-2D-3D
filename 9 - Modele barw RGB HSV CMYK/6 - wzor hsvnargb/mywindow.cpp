#include "mywindow.h"
#include <cmath>
#include "ui_mywindow.h"
#include <iostream>
#include <QFileDialog>
#include <QDebug>
#include <math.h>


MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);

    szer = 500;
    wys = 500;
    poczX = 0;
    poczY = 0;

    G = B = R = H = S = V = 0;

    img = QImage(szer,wys,QImage::Format_RGB32);

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

void MyWindow::pix(int x, int y, int r, int g, int b)
{
    if(x < 0 || y < 0 || x>=600 || y>=600) return;
    unsigned char* ptr = img.bits();

    ptr[szer*4*y + 4*x]= b;
    ptr[szer*4*y + 4*x + 1] = g;
    ptr[szer*4*y + 4*x + 2] = r;
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
        // Pobieramy wspolrzedne punktu klikniecia
        if(event->button() == Qt::RightButton)
        {

        }
    }
    else
    {
        return;
    }
}

void MyWindow::Red()
{
    float z1, z2 = 0;
    for(int y = 0; y < wys; y++)
    {
        z1 = 0;
        for(int x=0; x<szer; x++)
        {
            pix(x,y,r,z1,z2);
            z1 = z1 +0.5;
        }
        z2 = z2 + 0.5;
    }
}
void MyWindow::Green()
{
    float z1, z2 = 0;
    for(int y = 0; y < wys; y++)
    {
        z1 = 0;
        for(int x=0; x<szer; x++)
        {
            pix(x,y,z1,g,z2);
            z1 = z1 +0.5;
        }
        z2 = z2 + 0.5;
    }
}
void MyWindow::Blue()
{
    float z1, z2 = 0;
    for(int y = 0; y < wys; y++)
    {
        z1 = 0;
        for(int x=0; x<szer; x++)
        {
            pix(x,y,z1,z2,b);
            z1 = z1 +0.5;
        }
        z2 = z2 + 0.5;
    }
}
void MyWindow::Hue()
{
    for(int y = 0; y < wys; y++)
    {
        for(int x=0; x<szer; x++)
        {
            HsvNaRgb(y/600.0,y/600.0,H);//
            pix(x,y,R,G,B);
        }
    }
}
void MyWindow::Saturation()
{
    for(int y = 0; y < wys; y++)
    {
        for(int x=0; x<szer; x++)
        {
            HsvNaRgb(y/600.0,S,x*0.6);//
            pix(x,y,R,G,B);
        }
    }
}
void MyWindow::Value()
{
    for(int y=0; y<wys; y++)
    {
        for(int x=0; x<szer; x++)
        {
            HsvNaRgb(V, y/600.0, x*0.6);
            pix(x,y,R,G,B);
        }
    }
}

void MyWindow::HsvNaRgb(float V, float S, float H)
{
    float r1 = 0;
    float g1 = 0;
    float b1 = 0;
    float c = V * S;
    float h1 = H / 60;
    float x = c * (1 - fabs(fmod(h1,2) - 1));
    float m = V - c;

    switch ((int)h1)
    {
        case 0:
            r1 = c;
            g1 = x;
            break;
        case 1:
            r1 = x;
            g1 = c;
            break;
        case 2:
            g1 = c;
            b1 = x;
            break;
        case 3:
            g1 = x;
            b1 = c;
            break;
        case 4:
            r1 = x;
            b1 = c;
            break;
        case 5:
            r1 = c;
            b1 = x;
            break;
    }
            R = (r1 + m)*255;
            G = (g1 + m)*255;
            B = (b1 + m)*255;
}


void MyWindow::on_horizontalSlider_valueChanged(int value)
{
    b = value;
    Blue();
    update();
}


void MyWindow::on_horizontalSlider_2_valueChanged(int value)
{
    r = value;
    Red();
    update();
}

void MyWindow::on_horizontalSlider_3_valueChanged(int value)
{
    g = value;
    Green();
    update();
}

void MyWindow::on_horizontalSlider_4_valueChanged(int value)
{
    H = value;
    Hue();
    update();
}

void MyWindow::on_horizontalSlider_5_valueChanged(int value)
{
    S = value/100.0;
    Saturation();
    update();
}

void MyWindow::on_horizontalSlider_6_valueChanged(int value)
{
    V = value/100.0;
    Value();
    update();
}
