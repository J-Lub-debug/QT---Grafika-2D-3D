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

void MyWindow::on_draw1Button_clicked() //otwarcie
{
    erozja();
    dylacja();
    update();
}

void MyWindow::on_draw2Button_clicked() //zamkniecie
{
    dylacja();
    erozja();
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
void MyWindow::pix2(int x, int y)
{
    unsigned char* ptr = img->bits();

    ptr[szer*4*y + 4*x]= 0;
    ptr[szer*4*y + 4*x + 1] = 0;
    ptr[szer*4*y + 4*x + 2] = 0;
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
void MyWindow::dylacja()
{
    for(int Y1 = 0; Y1 < wys; Y1++)
    {

        for(int X1 = 0; X1<szer; X1++)
        {
            if(czyJestzamalowany(X1, Y1))
            {
                stosx.push(X1);
                stosy.push(Y1);
            }
        }
    }
    while(!(stosx.empty() && stosy.empty()))
    {
        a = stosx.top();
        b = stosy.top();
        stosx.pop();
        stosy.pop();

        if(!(czyJestzamalowany(a+1, b)))
        {
            pix(a+1, b);
        }
        if(!(czyJestzamalowany(a-1, b)))
        {
            pix(a-1, b);
        }
        if(!(czyJestzamalowany(a, b+1)))
        {
            pix(a, b+1);
        }
        if(!(czyJestzamalowany(a, b-1)))
        {
            pix(a, b-1);
        }
    }
    update();
}
void MyWindow::erozja()
{
    for(int Y1 = 0; Y1 < wys; Y1++)
    {

        for(int X1 = 0; X1<szer; X1++)
        {
            if(czyJestzamalowany(X1, Y1))
            {
                stosx.push(X1);
                stosy.push(Y1);
                break;
            }
        }
    }
    for(int Y1 = 0; Y1 < wys; Y1++)
    {

        for(int X1 = szer; X1>0; X1--)
        {
            if(czyJestzamalowany(X1, Y1))
            {
                stosx.push(X1);
                stosy.push(Y1);
                break;
            }
        }
    }
    for(int X1 = 0; X1<szer; X1++)
    {

        for(int Y1 = 0; Y1 < wys; Y1++)
        {
            if(czyJestzamalowany(X1, Y1))
            {
                stosx.push(X1);
                stosy.push(Y1);
                break;
            }
        }
    }
    for(int X1 = 0; X1<szer; X1++)
    {

        for(int Y1 = wys; Y1 > 0; Y1--)
        {
            if(czyJestzamalowany(X1, Y1))
            {
                stosx.push(X1);
                stosy.push(Y1);
                break;
            }
        }
    }
    int licznik = 0;
    while(!(stosx.empty() && stosy.empty()))
    {
        a = stosx.top();
        b = stosy.top();
        stosx.pop();
        stosy.pop();
        if(licznik < 4)
        {
            std::cout << a << " " << b << std::endl; //Bez względu na miejsce obiektu
                                                    //458 600 | 457 600 | 456 600 | 455 600 ?????
        }

        if(licznik > 4)
        {

            pix2(a,b);

        }
        licznik++;
    }
    update();
}

// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->modifiers() == Qt::AltModifier)
    {
        erozja();
    }
    else if(event->button() == Qt::RightButton)
    {
        dylacja();
    }

    else
    {
    midx = event->x();
    midy = event->y();
    x0 = event->x();
    y0 = event->y();
    }
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->modifiers() == Qt::AltModifier)
    {

    }
    else if(event->button() == Qt::RightButton)
    {

        return;
    }
    else
    {
        for(int i = x0; i<x0+50; i++)
        {
            pix(i,y0);
            pix(i,y0+50);
        }
        for(int i = y0; i<y0+50; i++)
        {
            pix(x0,i);
            pix(x0+50,i);
        }
    }
    update();
}


