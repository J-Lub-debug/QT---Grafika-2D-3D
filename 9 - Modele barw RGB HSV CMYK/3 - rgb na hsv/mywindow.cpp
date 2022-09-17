#include "mywindow.h"
#include <cmath>
#include "ui_mywindow.h"
#include <iostream>
#include <QFileDialog>
#include <QDebug>
#include <math.h>
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

    g = b = r = 0;

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

void MyWindow::pix(int x, int y)
{
    if(x < 0 || y < 0 || x>=600 || y>=600) return;
    unsigned char* ptr = img.bits();

    ptr[szer*4*y + 4*x]= 255;
    ptr[szer*4*y + 4*x + 1] = 255;
    ptr[szer*4*y + 4*x + 2] = 255;
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
            //test rgb na hsv
            double R,G,B;
            R = 145;
            G = 100;
            B = 125;

            std::vector<double> tab;
            tab = RgbNaHsv(R, G, B);
            std::cout << "H: " <<  tab[0] << " S: " << tab[1] << " V: " << tab[2] << std::endl;
        }
    }
    else
    {
        unsigned char* ptr = img.bits();
        //r == 255

        for(int x = 0; x<wys; x++)
        {
            for(int y = 0; y < szer; y++)
            {
                if(r == 255 && g != 255 && b==0) // r == 255 g == 0
                {
                    g++;
                }
                else if(g == 255 && r !=0) // r == 255 g == 255
                {
                    r--;
                }
                else if(g == 255 && r == 0 && b!= 255) // r == 0 g == 255
                {
                    b++;
                }
                else if(b == 255 && r == 0 && g!=0) //r = 0 b = 255 g == 255
                {
                    g--;
                }
                else if(b == 255 && g == 0 && r!=255) // r == 0 b == 255 g == 0
                {
                    r++;
                }
                else if(g == 0 && r == 255 && b!=0) // r == 255 b == 255 g == 0
                {
                    b--;
                }
                //std::cout << "x" << x << " y: " << y << " r:" << r << " g : " << g  << " b: " << b << std::endl;

                ptr[szer*4*y + 4*x]= b;
                ptr[szer*4*y + 4*x + 1] = g;
                ptr[szer*4*y + 4*x + 2] = r;

            }
        }

        update();



    }
    update();
}

std::vector<double> MyWindow::RgbNaHsv(double r, double g, double b)
{
    double H, S ,V;
    r = r/255;
    g = g/255;
    b = b/255;
    double minRGB = fmin(r, fmin(g,b));
    double maxRGB = fmax(r,fmax(g,b));
    if(maxRGB == minRGB)
    {
        V = minRGB;
        std::vector<double> pom = {0,0,V};
        return pom; // zwraca tablice elementow
    }
    else
    {
        double d = (r==minRGB) ? g-b : ((b==minRGB) ? r-g : b-r); // T/(N)----->T/N
        double h = (r==minRGB) ? 3 : ((b==minRGB) ? 1 : 5);
        H = 60*(h - d/(maxRGB - minRGB));
        S = (maxRGB - minRGB)/maxRGB;
        V = maxRGB;
        std::vector<double> pom = {H,S,V};
        return pom; // zwraca tablice elementow
    }


}


void MyWindow::on_horizontalSlider_valueChanged(int value)
{
    unsigned char* ptr = img.bits();
    b = value;

    for(int y = 0; y < szer; y++)
    {
        for(int x = 0; x<wys; x++)
        {

            ptr[szer*4*y + 4*x]= b;
            ptr[szer*4*y + 4*x + 1] = g;
            ptr[szer*4*y + 4*x + 2] = r;
        }
    }

    update();

}


void MyWindow::on_horizontalSlider_2_valueChanged(int value)
{
    unsigned char* ptr = img.bits();
    r = value;

    for(int y = 0; y < szer; y++)
    {
        for(int x = 0; x<wys; x++)
        {

            ptr[szer*4*y + 4*x]= b;
            ptr[szer*4*y + 4*x + 1] = g;
            ptr[szer*4*y + 4*x + 2] = r;
        }
    }

    update();
}

void MyWindow::on_horizontalSlider_3_valueChanged(int value)
{
    unsigned char* ptr = img.bits();
    g = value;

    for(int y = 0; y < szer; y++)
    {
        for(int x = 0; x<wys; x++)
        {

            ptr[szer*4*y + 4*x]= b;
            ptr[szer*4*y + 4*x + 1] = g;
            ptr[szer*4*y + 4*x + 2] = r;
        }
    }

    update();

}
