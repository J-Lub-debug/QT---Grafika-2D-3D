#include "mywindow.h"
#include <cmath>
#include "ui_mywindow.h"
#include <iostream>
#include <math.h>

#define PI 3.14159265

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);

    szer = 300;
    wys = 300;
    poczX = 0;
    poczY = 0;


    tx = ty =  alfa = Shx = Shy = 0;
    Scx=50; //Musi byc jakas przypisana liczba na poczatek bo potem /50 zeby wychodzilo 1, przy skalowaniu przez
    Scy=50; //X, Y musi pozostac 1 i na odwrót bo inaczej wyszłoby 0 i cały wzór by się wyzerował. Dlatego potem przy ruszeniu slidera jest skalowany w dół o 1/50, 2/50 az nie dojdzie do 50 gdzie osiagnie swoja oryginalna wielkosc i dopiero od teog momentu rosnie.
    img= QImage(":/jeden.jpg");
    img2= QImage(":/jeden.jpg");

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

    p.drawImage(poczX,poczY,img2);
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
    ptr = img2.bits();
    int i,j;
    for(i=0; i<wys; i++)
    {
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

void MyWindow::przeksztalcenie()
{
    unsigned char* ptr = img.bits();
    unsigned char* pom = img2.bits();

    for(int Y1 = 0; Y1 < wys; Y1++)
    {

        for(int X1 = 0; X1<szer; X1++)
        {
            float X=X1-szer/2; // - srodeky
            float Y=Y1-wys/2; // - srodekx

            float Xp=cos(alfa)*Scx/50*X + (cos(alfa)*Shx/20-sin(alfa))*Scx/50*Y+tx; //przez 50 i przez 20 bo musi wyjsc
            float Yp=sin(alfa)*Scy/50*X + (cos(alfa)*Shy/20+cos(alfa))*Scy/50*Y+ty; // liczba <1 i >0 dlatego jak suwak jest na 100 to od 50/50 w gore sie zaczyna psuc 60/50 itd.

            float X2=Xp+szer/2; // + srodekx
            float Y2=Yp+wys/2; // + srodeky

            if(X2<szer && Y2<wys && X2>0 && Y2>0)
            {
                pom[(int)Y2*szer*4+(int)X2*4]=ptr[szer*4*Y1 + 4*X1];
                pom[(int)Y2*szer*4+(int)X2*4+1]=ptr[szer*4*Y1 + 4*X1 + 1];
                pom[(int)Y2*szer*4+(int)X2*4+2]=ptr[szer*4*Y1 + 4*X1 + 2];
            }
        }
    }
    update();
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
        //x0 = event->x();
       // y0 = event->y();
    }
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
    }
    else
    {
    }
}



void MyWindow::on_horizontalSlider_sliderMoved(int position)
{
    tx = position;
    czysc();
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    ty = position;
    czysc();
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_3_sliderMoved(int position)
{
    Scx = position;
    czysc();
    przeksztalcenie();
    std::cout << Scx << std::endl;
}

void MyWindow::on_horizontalSlider_4_sliderMoved(int position)
{
    Scy = position;
    czysc();
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_5_sliderMoved(int position)
{
    alfa = position*PI/180;
    czysc();
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_6_sliderMoved(int position)
{
    Shx = position;
    czysc();
    przeksztalcenie();
}

void MyWindow::on_horizontalSlider_7_sliderMoved(int position)
{
    Shy = position;
    czysc();
    przeksztalcenie();
}
