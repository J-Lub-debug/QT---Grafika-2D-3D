#include "mywindow.h"
#include <cmath>
#include "ui_mywindow.h"
#include <iostream>
#include <QFileDialog>
#include <QDebug>
#include <vector>


MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);

    szer = 300;
    wys = 300;
    poczX = 0;
    poczY = 0;

    x0 = y0 = x1 = y1 = x = y = a = b = licznik = licznik2 = x3 = y3 = x4 = y4 = 0; // do kreski

    obraz1 = QImage(":/jeden.jpg"); // Teksutra

    obraz2 = QImage(szer,wys,QImage::Format_RGB32); //Teksturowany

}




//SYF
MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::on_exitButton_clicked()
{
    qApp->quit();
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
        ptr = obraz1.bits();
        int szer = obraz1.width();
        int wys = obraz1.height();

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
//SYF





void MyWindow::paintEvent(QPaintEvent*)
{
    //1.Rysowanie obrazka:
    QPainter p(this);
    p.drawImage(poczX,poczY,obraz1); //<----
    p.drawImage(300,0,obraz2); //<-----
}


void MyWindow::pix(int x, int y) // na lewym obrazku
{
    if(x < 0 || y < 0 || x>=600 || y>=600) return;
    unsigned char* ptr = obraz1.bits(); //<----

    ptr[szer*4*y + 4*x]= 255;
    ptr[szer*4*y + 4*x + 1] = 255;
    ptr[szer*4*y + 4*x + 2] = 255;

}
void MyWindow::pix2(int X, int Y) //3.Na prawym obrazku
{
    if(X < 0 || Y < 0 || X>=600 || Y>=600) return;

    unsigned char* ptr2 = obraz2.bits();

    ptr2[300*4*Y + 4*X]= 255;
    ptr2[300*4*Y + 4*X + 1] = 255;
    ptr2[300*4*Y + 4*X + 2] = 255;
}
void MyWindow::pix3(int x, int y, int r, int g, int b)
{
    if(x < 0 || y < 0 || x>=600 || y>=600) return;
    unsigned char* ptr = obraz2.bits();

    ptr[szer*4*y + 4*x]= b;
    ptr[szer*4*y + 4*x + 1] = g;
    ptr[szer*4*y + 4*x + 2] = r;
}
//2.Rysowanie dwoch Trojkatow
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
void MyWindow::Kreska2(int x3, int y3, int x4, int y4) // bo inny pix
{
    a = (float)(y4-y3)/(x4-x3); // m
    b = (y3) - a * x3;
    if(x3 == x4)
    {
        if(y3 > y4)
        {
            for (int x = x3 ; x != y3; x++)
            {
                pix2(x3, x);
            }
        }
        if(y3 < y4)
        {
            for (int x = x3 ; x != y4; x++)
            {
                pix2(x3, x);
            }

        }
    }
    if(y3 == y4)
    {

    }

    if(x3 < x4)
    {
        for (int x = x3 ; x != x4; x++)
        {
            int y = a * x + b;
            pix2(x, y);
        }
    }
    else
    {
        for (int x = x3 ; x != x4; x--)
        {
            int y = a * x + b;
            pix2(x, y);
        }
    }
    if(y3 == y4)
    {
        pix2(y3, b);
    }


    if(y3 < y4)
    {
        for (int y = y3 ; y != y4; y++)
        {
            int x = (y-b)/a;
            pix2(x, y);
        }
    }
    else
    {
        for (int y = y3; y != y4; y--)
        {
            int x = (y-b)/a;
            pix2(x,y);
        }
    }
    update();

}
//Rysowanie Trojkata
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    if(event->button() == Qt::RightButton)
    {
        x3 = event->x();
        y3 = event->y();

        vectorx2.push_back(x3);
        vectory2.push_back(y3);
        pix2(x3, y3);
        licznik2++;

        if(licznik2 == 3)
        {
            while(licznik2!=1)
            {
                Kreska2(vectorx2[licznik2-1],vectory2[licznik2-1],vectorx2[licznik2-2],vectory2[licznik2-2]);
                licznik2--;

            }
                Kreska2(vectorx2.front(),vectory2.front(),vectorx2.back(),vectory2.back());
        }

        update();
    }
    else
    {
        x0 = event->x();
        y0 = event->y();

        vectorx.push_back(x0);
        vectory.push_back(y0);
        pix(x0, y0);
        licznik++;

        if(licznik == 3)
        {
            while(licznik!=1)
            {
                Kreska(vectorx[licznik-1],vectory[licznik-1],vectorx[licznik-2],vectory[licznik-2]);
                licznik--;

            }
                Kreska(vectorx.front(),vectory.front(),vectorx.back(),vectory.back());
        }

        update();
    }
}
//
void MyWindow::teksturuj()
{ //To W tylko po to zeby ladniej wygladalo i sie zmiescilo w linijce xDD a normalnie by caly wzor byl
    //wspolrzedne barycentryczne trojkata1 (tekstury) u v w
    double u,v,w;
    double W = (vectorx[1] - vectorx[0]) * (vectory[2] - vectory[0]) - (vectorx[2] - vectorx[0]) * (vectory[1] - vectory[0]);
    for(int x = 0; x<szer; x++)
    {
        for(int y = 0; y<wys; y++)
        {
            v = ((x - vectorx[0]) * (vectory[2] - vectory[0]) - (vectorx[2] - vectorx[0]) * (y - vectory[0])) / W; //(1.0*W)
            w = ((vectorx[1] - vectorx[0]) * (y - vectory[0]) - (x - vectorx[0]) * (vectory[1] - vectory[0])) / W; //(1.0*W)
            u = 1 - v - w;

            if ((u >= 0 && u <= 1) && (v >= 0 && v <= 1) && (w >= 0 && w <= 1)) {
                //mnozymy przez wspolrzedne trojkata2 (teksturowanego)
                double X, Y;
                X = (u * vectorx2[0] + v * vectorx2[1] + w * vectorx2[2]);
                Y = (u * vectory2[0] + v * vectory2[1]+ w * vectory2[2]);
                //uint kolor = pobierzKolor(x, y);
                //obraz2->setPixel(x, y, kolor);
                QColor Kolor(obraz1.pixel(x,y));
                pix3(X,Y,Kolor.red(),Kolor.green(),Kolor.blue());

            }
        }
    }
    update();

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


//Wywolanie funkcji te liczniki to chcialem zeby dalo sie wywowac tylko po narysowaniu obu trojkatow
void MyWindow::on_pushButton_clicked()
{
    //if(licznik + licznik2 == 6)
    //{
        teksturuj();
   // }
}
//
