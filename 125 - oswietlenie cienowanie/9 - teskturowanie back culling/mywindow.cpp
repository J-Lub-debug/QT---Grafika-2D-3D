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
    tekstura = QImage(":/jeden.jpg");
    bits = img.bits();
    odleglosc = 300;

    tx = ty = tz = alfa = alfaX = alfaY = alfaZ = Shx = Shy = Shz = 0;
    Scx = Scy = Scz = 1; // Rysuje od srodka 50
    PrzedniaWidoczna = PrawaWidoczna = LewaWidoczna = GornaWidoczna = DolnaWidoczna = TylnaWidoczna = false;

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


    /* PUNKT 1 */
    x[0]=-100;
    y[0]=-100;
    z[0]=0;
    /* PUNKT 2 */
    x[1]=100;
    y[1]=-100;
    z[1]=0;
    /* PUNKT 3 */
    x[2]=100;
    y[2]=100;
    z[2]=0;
    /* PUNKT 4 */
    x[3]=-100;
    y[3]=100;
    z[3]=0;
    /* PUNKT 5 */
    x[4]=-100;
    y[4]=-100;
    z[4]=200;
    /* PUNKT 6 */
    x[5]=100;
    y[5]=-100;
    z[5]=200;
    /* PUNKT 7 */
    x[6]=100;
    y[6]=100;
    z[6]=200;
    /* PUNKT 8 */
    x[7]=-100;
    y[7]=100;
    z[7]=200;


    for(int i=0; i<8; i++) {
        konwertujNa2D(x[i],y[i],z[i],i);
    }
    //rysujKreski();
    WidocznoscSciany();
    teksturuj();

}
/*void MyWindow::rysujKreski()
{
    Kreska(px[3], py[3], px[2], py[2]); //d
    Kreska(px[0], py[0], px[1], py[1]); //g G d
    Kreska(px[0], py[0], px[3], py[3]); //l  L p
    Kreska(px[1], py[1], px[2], py[2]); //p   P l

    Kreska(px[7], py[7], px[6], py[6]); // D g           T d
    Kreska(px[4], py[4], px[5], py[5]); // G g         T g
    Kreska(px[4], py[4], px[7], py[7]); // L l       T l

    Kreska(px[5], py[5], px[6], py[6]); //P p      T p
    Kreska(px[0], py[0], px[4], py[4]); // L g
    Kreska(px[2], py[2], px[6], py[6]);//P d D p
    Kreska(px[1], py[1], px[5], py[5]);//P g G p
    Kreska(px[3], py[3], px[7], py[7]);//L d
}*/

void MyWindow::konwertujNa2D(double x, double y, double z, int i) // ???
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
    //rysujPunkt(pp[0]+300,pp[1]+300);
    //zeruj();
}

/*void MyWindow::rysujPunkt(double x, double y)
{
    for (int i=-5; i<=5; i++)
    {
        for (int j=-5; j<=5; j++)
        {
            pix(x+i,y+j);
        }
    }
    update();
}*/

void MyWindow::zeruj()
{
    /* PUNKT 1 */
    x[0]=-100;
    y[0]=-100;
    z[0]=0;
    /* PUNKT 2 */
    x[1]=100;
    y[1]=-100;
    z[1]=0;
    /* PUNKT 3 */
    x[2]=100;
    y[2]=100;
    z[2]=0;
    /* PUNKT 4 */
    x[3]=-100;
    y[3]=100;
    z[3]=0;
    /* PUNKT 5 */
    x[4]=-100;
    y[4]=-100;
    z[4]=200;
    /* PUNKT 6 */
    x[5]=100;
    y[5]=-100;
    z[5]=200;
    /* PUNKT 7 */
    x[6]=100;
    y[6]=100;
    z[6]=200;
    /* PUNKT 8 */
    x[7]=-100;
    y[7]=100;
    z[7]=200;
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
    //1.Rysowanie obrazka:
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
void MyWindow::pix2(int x, int y, int r, int g, int b)
{
    if(x < 0 || y < 0 || x>=600 || y>=600) return;
    unsigned char* ptr = img.bits();

    ptr[szer*4*y + 4*x]= b;
    ptr[szer*4*y + 4*x + 1] = g;
    ptr[szer*4*y + 4*x + 2] = r;
}

void MyWindow::Kreska(int x0, int y0, int x1, int y1) // Kreska zle mo?
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
    WidocznoscSciany();
    double srodekx=0;
    double srodeky=0;
    double srodekz=0;
    for(int i=0; i<8; i++) {
        srodekx+=x[i];
        srodeky+=y[i];
        srodekz+=z[i];
    }
    srodekx/=8; // srednia punktow to srodek
    srodeky/=8;
    srodekz/=8;

    for(int i=0; i<8; i++) {
        x[i] -= srodekx;
        y[i] -= srodeky;
        z[i] -= srodekz;
    }
    for(int i=0; i<8; i++) {
        v1 = {x[i], y[i], z[i], 1};
        v2 = Translacja*Skalowanie*ObrotZ*ObrotY*ObrotX * PochylenieZ* PochylenieY*PochylenieX* v1;//Translacja*Skalowanie*ObrotZ*ObrotY*ObrotX * v1;

       // v1.print();
        //v2.print();

        konwertujNa2D(v2[0]+srodekx,v2[1]+0.5+srodeky,v2[2]+0.5+srodekz,i);
        //rysujKreski();
        teksturuj();
    }

}
void MyWindow::teksturuj() // ! pierwszy gorny trojkat krzywo (u,v,w,W) px[0]->px[1]->px[2]
//pixel out of range (194,300) ? (300,300)/(300,cokolwiek) itd. out of range
{
    //Przednia sciana
    if(PrzedniaWidoczna == true)
    {
        double u,v,w, u2, v2, w2;
        double W = (300 - 0) * (0 - 0) - (300 - 0) * (300 - 0); //L //(vectorx[1] - vectorx[0]) * (vectory[2] - vectory[0]) - (vectorx[2] - vectorx[0]) * (vectory[1] - vectory[0]);
        double W2 = (0 - 0) * (300 - 0) - (300 - 0) * (300 - 0);
        for(int x = 0; x<300; x++) //600 out of range bo tekstura 300x300
        {
            for(int y = 0; y<300; y++)
            {
                v = ((x - 0) * (0 - 0) - (300 - 0) * (y - 0)) / (1.0*W); //L // ((x - vectorx[0]) * (vectory[2] - vectory[0]) - (vectorx[2] - vectorx[0]) * (y - vectory[0])) / (1.0*W);
                w = ((300 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W); //L //((vectorx[1] - vectorx[0]) * (y - vectory[0]) - (x - vectorx[0]) * (vectory[1] - vectory[0])) / (1.0*W);
                u = 1 - v - w;

                //std::cout << "U: " << u << " V: " << v << " W: " << w << std::endl;

                if ((u >= 0 && u <= 1) && (v >= 0 && v <= 1) && (w >= 0 && w <= 1)) {
                    double X, Y;
                    X = (u * px[0] + v * px[2] + w * px[1]); //P
                    Y = (u * py[0] + v * py[2]+ w * py[1]); //P
                    //uint kolor = pobierzKolor(x, y);
                    //obraz2->setPixel(x, y, kolor);
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red(),Kolor.green(),Kolor.blue());

                }
                v2 = ((x - 0) * (300 - 0) - (300 - 0) * (y - 0)) / (1.0*W2);
                w2 = ((0 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W2);
                u2 = 1 - v2 - w2;


                if ((u2 >= 0 && u2 <= 1) && (v2 >= 0 && v2 <= 1) && (w2 >= 0 && w2 <= 1)) {
                    double X, Y;
                    X = (u2 * px[0] + v2 * px[3] + w2 * px[2]); //P
                    Y = (u2 * py[0] + v2 * py[3]+ w2 * py[2]); //P
                    //uint kolor = pobierzKolor(x, y);
                    //obraz2->setPixel(x, y, kolor);
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red(),Kolor.green(),Kolor.blue());

                }

            }
        }

    }
    if(PrawaWidoczna == true)
    {
        double u,v,w, u2, v2, w2;
        double W = (300 - 0) * (0 - 0) - (300 - 0) * (300 - 0);
        double W2 = (0 - 0) * (300 - 0) - (300 - 0) * (300 - 0);
        for(int x = 0; x<300; x++)
        {
            for(int y = 0; y<300; y++)
            {
                v = ((x - 0) * (0 - 0) - (300 - 0) * (y - 0)) / (1.0*W);
                w = ((300 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W);
                u = 1 - v - w;

                //std::cout << "U: " << u << " V: " << v << " W: " << w << std::endl;

                if ((u >= 0 && u <= 1) && (v >= 0 && v <= 1) && (w >= 0 && w <= 1)) {
                    double X, Y;
                    X = (u * px[1] + v * px[6] + w * px[5]); //P
                    Y = (u * py[1] + v * py[6]+ w * py[5]); //P
                    //uint kolor = pobierzKolor(x, y);
                    //obraz2->setPixel(x, y, kolor);
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red(),Kolor.green(),Kolor.blue());

                }
                v2 = ((x - 0) * (300 - 0) - (300 - 0) * (y - 0)) / (1.0*W2);
                w2 = ((0 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W2);
                u2 = 1 - v2 - w2;


                if ((u2 >= 0 && u2 <= 1) && (v2 >= 0 && v2 <= 1) && (w2 >= 0 && w2 <= 1)) {
                    double X, Y;
                    X = (u2 * px[1] + v2 * px[2] + w2 * px[6]); //P
                    Y = (u2 * py[1] + v2 * py[2]+ w2 * py[6]); //P
                    //uint kolor = pobierzKolor(x, y);
                    //obraz2->setPixel(x, y, kolor);
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red(),Kolor.green(),Kolor.blue());

                }

            }
        }

    }
    if(LewaWidoczna == true)
    {
        double u,v,w, u2, v2, w2;
        double W = (300 - 0) * (0 - 0) - (300 - 0) * (300 - 0);
        double W2 = (0 - 0) * (300 - 0) - (300 - 0) * (300 - 0);
        for(int x = 0; x<300; x++)
        {
            for(int y = 0; y<300; y++)
            {
                v = ((x - 0) * (0 - 0) - (300 - 0) * (y - 0)) / (1.0*W);
                w = ((300 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W);
                u = 1 - v - w;

                //std::cout << "U: " << u << " V: " << v << " W: " << w << std::endl;

                if ((u >= 0 && u <= 1) && (v >= 0 && v <= 1) && (w >= 0 && w <= 1)) {
                    double X, Y;
                    X = (u * px[4] + v * px[3] + w * px[0]); //P
                    Y = (u * py[4] + v * py[3]+ w * py[0]); //P
                    //uint kolor = pobierzKolor(x, y);
                    //obraz2->setPixel(x, y, kolor);
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red(),Kolor.green(),Kolor.blue());

                }
                v2 = ((x - 0) * (300 - 0) - (300 - 0) * (y - 0)) / (1.0*W2);
                w2 = ((0 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W2);
                u2 = 1 - v2 - w2;


                if ((u2 >= 0 && u2 <= 1) && (v2 >= 0 && v2 <= 1) && (w2 >= 0 && w2 <= 1)) {
                    double X, Y;
                    X = (u2 * px[4] + v2 * px[7] + w2 * px[3]); //P
                    Y = (u2 * py[4] + v2 * py[7]+ w2 * py[3]); //P
                    //uint kolor = pobierzKolor(x, y);
                    //obraz2->setPixel(x, y, kolor);
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red(),Kolor.green(),Kolor.blue());

                }

            }
        }

    }
    if(GornaWidoczna == true)
    {
        double u,v,w, u2, v2, w2;
        double W = (300 - 0) * (0 - 0) - (300 - 0) * (300 - 0);
        double W2 = (0 - 0) * (300 - 0) - (300 - 0) * (300 - 0);
        for(int x = 0; x<300; x++)
        {
            for(int y = 0; y<300; y++)
            {
                v = ((x - 0) * (0 - 0) - (300 - 0) * (y - 0)) / (1.0*W);
                w = ((300 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W);
                u = 1 - v - w;

                //std::cout << "U: " << u << " V: " << v << " W: " << w << std::endl;

                if ((u >= 0 && u <= 1) && (v >= 0 && v <= 1) && (w >= 0 && w <= 1)) {
                    double X, Y;
                    X = (u * px[4] + v * px[1] + w * px[5]); //P
                    Y = (u * py[4] + v * py[1]+ w * py[5]); //P
                    //uint kolor = pobierzKolor(x, y);
                    //obraz2->setPixel(x, y, kolor);
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red(),Kolor.green(),Kolor.blue());

                }
                v2 = ((x - 0) * (300 - 0) - (300 - 0) * (y - 0)) / (1.0*W2);
                w2 = ((0 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W2);
                u2 = 1 - v2 - w2;


                if ((u2 >= 0 && u2 <= 1) && (v2 >= 0 && v2 <= 1) && (w2 >= 0 && w2 <= 1)) {
                    double X, Y;
                    X = (u2 * px[4] + v2 * px[0] + w2 * px[1]); //P
                    Y = (u2 * py[4] + v2 * py[0]+ w2 * py[1]); //P
                    //uint kolor = pobierzKolor(x, y);
                    //obraz2->setPixel(x, y, kolor);
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red(),Kolor.green(),Kolor.blue());

                }

            }
        }

    }
    if(DolnaWidoczna == true)
    {
        double u,v,w, u2, v2, w2;
        double W = (300 - 0) * (0 - 0) - (300 - 0) * (300 - 0);
        double W2 = (0 - 0) * (300 - 0) - (300 - 0) * (300 - 0);
        for(int x = 0; x<300; x++)
        {
            for(int y = 0; y<300; y++)
            {
                v = ((x - 0) * (0 - 0) - (300 - 0) * (y - 0)) / (1.0*W);
                w = ((300 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W);
                u = 1 - v - w;

                //std::cout << "U: " << u << " V: " << v << " W: " << w << std::endl;

                if ((u >= 0 && u <= 1) && (v >= 0 && v <= 1) && (w >= 0 && w <= 1)) {
                    double X, Y;
                    X = (u * px[7] + v * px[2] + w * px[6]); //P
                    Y = (u * py[7] + v * py[2]+ w * py[6]); //P
                    //uint kolor = pobierzKolor(x, y);
                    //obraz2->setPixel(x, y, kolor);
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red(),Kolor.green(),Kolor.blue());

                }
                v2 = ((x - 0) * (300 - 0) - (300 - 0) * (y - 0)) / (1.0*W2);
                w2 = ((0 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W2);
                u2 = 1 - v2 - w2;


                if ((u2 >= 0 && u2 <= 1) && (v2 >= 0 && v2 <= 1) && (w2 >= 0 && w2 <= 1)) {
                    double X, Y;
                    X = (u2 * px[7] + v2 * px[3] + w2 * px[2]); //P
                    Y = (u2 * py[7] + v2 * py[3] + w2 * py[2]); //P
                    //uint kolor = pobierzKolor(x, y);
                    //obraz2->setPixel(x, y, kolor);
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red(),Kolor.green(),Kolor.blue());

                }

            }
        }

    }
    if(TylnaWidoczna == true) // nie dziala
    {
        double u,v,w, u2, v2, w2;
        double W = (300 - 0) * (0 - 0) - (300 - 0) * (300 - 0);
        double W2 = (0 - 0) * (300 - 0) - (300 - 0) * (300 - 0);
        for(int x = 0; x<300; x++)
        {
            for(int y = 0; y<300; y++)
            {
                v = ((x - 0) * (0 - 0) - (300 - 0) * (y - 0)) / (1.0*W);
                w = ((300 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W);
                u = 1 - v - w;

                //std::cout << "U: " << u << " V: " << v << " W: " << w << std::endl;

                if ((u >= 0 && u <= 1) && (v >= 0 && v <= 1) && (w >= 0 && w <= 1)) {
                    double X, Y;
                    X = (u * px[5] + v * px[7] + w * px[4]); //P
                    Y = (u * py[5] + v * py[7]+ w * py[4]); //P
                    //uint kolor = pobierzKolor(x, y);
                    //obraz2->setPixel(x, y, kolor);
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red(),Kolor.green(),Kolor.blue());

                }
                v2 = ((x - 0) * (300 - 0) - (300 - 0) * (y - 0)) / (1.0*W2);
                w2 = ((0 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W2);
                u2 = 1 - v2 - w2;


                if ((u2 >= 0 && u2 <= 1) && (v2 >= 0 && v2 <= 1) && (w2 >= 0 && w2 <= 1)) {
                    double X, Y;
                    X = (u2 * px[5] + v2 * px[6] + w2 * px[7]); //P
                    Y = (u2 * py[5] + v2 * py[6]+ w2 * py[7]); //P
                    //uint kolor = pobierzKolor(x, y);
                    //obraz2->setPixel(x, y, kolor);
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red(),Kolor.green(),Kolor.blue());

                }

            }
        }

    }
    update();

}
void MyWindow::WidocznoscSciany()
{
    double Przednia, Prawa, Lewa, Gorna, Dolna, Tylna;
    Przednia = ((px[1]-px[0])*(py[1]+py[0]))+((px[2]-px[1])*(py[2]+py[1]))+((px[3]-px[2])*(py[3]+py[2]))+((px[0]-px[3])*(py[0]+py[3]));
    Prawa = ((px[5]-px[1])*(py[5]+py[1]))+((px[6]-px[5])*(py[6]+py[5]))+((px[2]-px[6])*(py[2]+py[6]))+((px[1]-px[2])*(py[1]+py[2]));
    Lewa = ((px[0]-px[4])*(py[0]+py[4]))+((px[3]-px[0])*(py[3]+py[0]))+((px[7]-px[3])*(py[7]+py[3]))+((px[4]-px[7])*(py[4]+py[7]));
    Gorna = ((px[5]-px[4])*(py[5]+py[4]))+((px[1]-px[5])*(py[1]+py[5]))+((px[0]-px[1])*(py[0]+py[1]))+((px[4]-px[0])*(py[4]+py[0]));
    Dolna = ((px[2]-px[3])*(py[2]+py[3]))+((px[6]-px[2])*(py[6]+py[2]))+((px[7]-px[6])*(py[7]+py[6]))+((px[3]-px[7])*(py[3]+py[7]));
    Tylna = ((px[4]-px[5])*(py[4]+py[5]))+((px[7]-px[4])*(py[7]+py[4]))+((px[6]-px[7])*(py[6]+py[7]))+((px[5]-px[6])*(py[5]+py[6]));


    if(Przednia > 0)
    {
        PrzedniaWidoczna = false;
    }
    else if(Przednia< 0)
    {
        PrzedniaWidoczna = true;
    }
    if(Prawa > 0)
    {
        PrawaWidoczna = false;
    }
    else if(Prawa < 0)
    {
        PrawaWidoczna = true;
    }
    if(Lewa > 0)
    {
        LewaWidoczna = false;
    }
    else if(Lewa < 0)
    {
        LewaWidoczna = true;
    }
    if(Gorna > 0)
    {
        GornaWidoczna = false;
    }
    else if(Gorna < 0)
    {
        GornaWidoczna = true;
    }
    if(Dolna > 0)
    {
        DolnaWidoczna = false;
    }
    else if(Dolna < 0)
    {
        DolnaWidoczna = true;
    }
    if(Tylna > 0)
    {
        TylnaWidoczna = false;
    }
    else if(Tylna < 0)
    {
        TylnaWidoczna = true;
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
