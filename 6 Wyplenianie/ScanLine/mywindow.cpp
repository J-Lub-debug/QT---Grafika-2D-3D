#include "mywindow.h"
#include <cmath>
#include "ui_mywindow.h"
#include <iostream>

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);

    szer = 600;
    wys = 600;
    poczX = 0;
    poczY = 0;

    x0 = y0 = x1 = y1 = m = x = y = a = b = 0;

    img = new QImage(szer,wys,QImage::Format_RGB32);

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

    p.drawImage(poczX,poczY,*img);
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

    ptr = img->bits();

    int i,j;

    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]=255; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 255; // Skladowa RED
        }
    }
}


void MyWindow::rysuj1()
{
        unsigned char *ptr;
        ptr = img->bits();
        int szer = img->width();
        int wys = img->height();

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
        ptr = img->bits();
        int szer = img->width();
        int wys = img->height();

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
    unsigned char* ptr = img->bits();

    ptr[szer*4*y + 4*x]= 255;
    ptr[szer*4*y + 4*x + 1] = 255;
    ptr[szer*4*y + 4*x + 2] = 255;
}

bool MyWindow::czyJestzamalowany(int x, int y)
{
    unsigned char* ptr = img->bits();
    if(ptr[szer*4*y + 4*x] == 255){

        return true;
    }
    else{

        return false;
    }
}

void MyWindow::Kreska(int x0, int y0, int x1, int y1) // II Bezier
{
    a = (float)(y1-y0)/(x1-x0); // m
    b = (y0) - a * x0;
    if(x0 < x1)
    {
        for (int x = x0 ; x != x1; x++)
        {
            int y = a * x + b;
            pix(x, y);
        }
    }
    else
    {
        for (int x = x0 ; x != x1; x--)
        {
            int y = a * x + b;
            pix(x, y);
        }
    }
    if(y0 < y1)
    {
        for (int y = y0 ; y != y1; y++)
        {
            int x = (y-b)/a;
            pix(x, y);
        }
    }
    else
    {
        for (int y = y0; y != y1; y--)
        {
            int x = (y-b)/a;
            pix(x,y);
        }
    }
    update();
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    if(event->button() == Qt::RightButton)
    {
        int licznik = 0;
        for(int j = 0; j<600; j++)
        {
            for(int i = 0; i < 600; i++)
            {
                tabxy[i][j] = 0;
            }
        }

        for(int Y1 = 0; Y1 < wys; Y1++)
        {
            licznik = 0;
            vectorx.clear(); //
            vectory.clear();

            for(int X1 = 0; X1<szer; X1++)
            {
                if(czyJestzamalowany(X1, Y1))
                {
                    vectorx.push_back(X1);
                    vectory.push_back(Y1);
                    if(licznik >= 1)
                    {
                        for(int i = vectorx[licznik-1]; i != vectorx[licznik]; i++)
                        {
                            //pix(i, vectory[licznik]);
                            tabxy[i][vectory[licznik]] = tabxy[i][vectory[licznik]]+1;

                        }
                    }
                    licznik++;
                }
            }
        }
        for(int Y1 = 0; Y1 < wys; Y1++)
        {
            licznik = 0;
            vectorx.clear(); //
            vectory.clear();

            for(int X1 = szer; X1>0; X1--)
            {
                if(czyJestzamalowany(X1, Y1))
                {
                    vectorx.push_back(X1);
                    vectory.push_back(Y1);
                    if(licznik >= 1)
                    {
                        for(int i = vectorx[licznik-1]; i != vectorx[licznik]; i--)
                        {
                            //pix(i, vectory[licznik]);
                            tabxy[i][vectory[licznik]] = tabxy[i][vectory[licznik]]+1;
                        }
                    }
                    licznik++;
                }
            }
        }
        for(int X1 = 0; X1<szer; X1++)
        {
            licznik = 0;
            vectorx.clear(); //
            vectory.clear();

            for(int Y1 = 0; Y1 < wys; Y1++)
            {
                if(czyJestzamalowany(X1, Y1))
                {
                    vectorx.push_back(X1);
                    vectory.push_back(Y1);
                    if(licznik >= 1)
                    {
                        for(int i = vectory[licznik-1]; i != vectory[licznik]; i++)
                        {
                            //pix(vectorx[licznik], i);
                            tabxy[vectorx[licznik]][i] = tabxy[vectorx[licznik]][i]+1;
                        }
                    }
                    licznik++;
                }
            }
        }

        for(int X1 = 0; X1<szer; X1++)
        {
            licznik = 0;
            vectorx.clear(); //
            vectory.clear();

            for(int Y1 = wys; Y1 > 0; Y1--)
            {
                if(czyJestzamalowany(X1, Y1))
                {
                    vectorx.push_back(X1);
                    vectory.push_back(Y1);
                    if(licznik >= 1)
                    {
                        for(int i = vectory[licznik-1]; i != vectory[licznik]; i--)
                        {
                            tabxy[vectorx[licznik]][i] = tabxy[vectorx[licznik]][i]+1;
                        }
                    }
                    licznik++;
                }
            }
        }

        //Malowanie

        for(int i = 0; i<600; i++)
        {
            for(int j = 0; j<600; j++)
            {
                //std::cout << "x: " << j << " y: " << i << " trafienia: " << tabxy[i][j] << std::endl;
                if(tabxy[i][j] >= 3)
                {
                    pix(i,j);
                }
            }
        }

        update();
    }

    else
    {
    x0 = event->x();
    y0 = event->y();
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
    Kreska(100,200,150,250);
    Kreska(100,200,150,150);
    Kreska(150,250,200,225);
    Kreska(150,150,200,200);
    Kreska(200,200,250,150);
    Kreska(250,150,300,200);
    Kreska(200,225,250,300);
    Kreska(250,300,300,200);

    }
    update();
}


