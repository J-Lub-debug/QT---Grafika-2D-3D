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

    zeruj();
    odleglosc = 150;

    tx = ty = tz = alfa = alfaX = alfaY = alfaZ = Shx = Shy = Shz = 0;
    Scx = Scy = Scz = 1;
    //PrzedniaWidoczna = PrawaWidoczna = LewaWidoczna = GornaWidoczna = DolnaWidoczna = TylnaWidoczna = false;

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
    WidocznoscScianyISwiatlo();

}

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
    pz[i]=z;

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
void MyWindow::pix2(int x, int y, int r, int g, int b)
{
    if(x < 0 || y < 0 || x>=600 || y>=600) return;
    unsigned char* ptr = img.bits();

    ptr[szer*4*y + 4*x]= b;
    ptr[szer*4*y + 4*x + 1] = g;
    ptr[szer*4*y + 4*x + 2] = r;
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
    srodekx = 0;
    srodeky = 0;
    srodekz = 0;
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
    for(int i = 0; i < 8; i++) {
        v1 = {x[i], y[i], z[i], 1};
        v2 = Translacja*Skalowanie*ObrotZ*ObrotY*ObrotX * PochylenieZ* PochylenieY*PochylenieX* v1;//Translacja*Skalowanie*ObrotZ*ObrotY*ObrotX * v1;


        xx[i] = v2[0]+srodekx;
        yy[i] = v2[1]+0.5+srodeky;
        zz[i] = v2[2]+0.5+srodekz;
        konwertujNa2D(v2[0]+srodekx,v2[1]+0.5+srodeky,v2[2]+0.5+srodekz,i);
    }
    WidocznoscScianyISwiatlo();

}
void MyWindow::teksturuj(int px0, int py0, int px1, int py1, int px2, int py2, int px3, int py3, double kat ) // (u,v,w,W) px[0]->px[1]->px[2]
{
        double u,v,w, u2, v2, w2;
        double W = (300 - 0) * (0 - 0) - (300 - 0) * (300 - 0); //L
        double W2 = (0 - 0) * (300 - 0) - (300 - 0) * (300 - 0);
        for(int x = 0; x<300; x++)
        {
            for(int y = 0; y<300; y++)
            {
                v = ((x - 0) * (0 - 0) - (300 - 0) * (y - 0)) / (1.0*W); //L //
                w = ((300 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W); //L
                u = 1 - v - w;


                if ((u >= 0 && u <= 1) && (v >= 0 && v <= 1) && (w >= 0 && w <= 1)) {
                    double X, Y;
                    X = (u * px0 + v * px2 + w * px1); //P
                    Y = (u * py0 + v * py2 + w * py1); //P
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red()*cos(kat),Kolor.green()*cos(kat),Kolor.blue()*cos(kat)); //X,Y,Kolor.red()*kat,Kolor.green()*kat,Kolor.blue()*kat


                }
                v2 = ((x - 0) * (300 - 0) - (300 - 0) * (y - 0)) / (1.0*W2);
                w2 = ((0 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W2);
                u2 = 1 - v2 - w2;


                if ((u2 >= 0 && u2 <= 1) && (v2 >= 0 && v2 <= 1) && (w2 >= 0 && w2 <= 1)) {
                    double X, Y;
                    X = (u2 * px0 + v2 * px3 + w2 * px2); //P
                    Y = (u2 * py0 + v2 * py3 + w2 * py2); //P
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red()*cos(kat),Kolor.green()*cos(kat),Kolor.blue()*cos(kat));

                }

            }
        }

    update();

}
void MyWindow::WidocznoscScianyISwiatlo()
{
    arma::vec vertex = {srodekx, srodeky, srodekz, 0};

    arma::vec lightPosition = {0.0,0.0,1.0,1.0};

    arma::vec lightDirection = lightPosition - vertex;
    lightDirection = normalise(lightDirection);

    arma::vec vv0={xx[0], yy[0], zz[0]}; //1-8
    arma::vec vv1={xx[1], yy[1], zz[1]};
    arma::vec vv2={xx[2], yy[2], zz[2]};
    arma::vec vv3={xx[3], yy[3], zz[3]};
    arma::vec vv4={xx[4], yy[4], zz[4]};
    arma::vec vv5={xx[5], yy[5], zz[5]};
    arma::vec vv6={xx[6], yy[6], zz[6]};
    arma::vec vv7={xx[7], yy[7], zz[7]};

    arma::vec nor1 = cross(vv3-vv0, vv2-vv0); // vv2-vv1, vv3-vv1
    arma::vec nor2 = cross(vv2-vv1, vv6-vv1); //vv6-vv1, vv2-vv1
    arma::vec nor3 = cross(vv6-vv5, vv7-vv5); //vv6-vv4, vv7-vv4
    arma::vec nor4 = cross(vv7-vv4, vv3-vv4); //vv3-vv0, vv7-vv0
    arma::vec nor5 = cross(vv7-vv3, vv6-vv3); //vv3-vv7, vv2-vv7
    arma::vec nor6 = cross(vv0-vv4, vv1-vv4); //vv4-vv1, vv0-vv1

    normalise(nor1);
    normalise(nor2);
    normalise(nor3);
    normalise(nor4);
    normalise(nor5);
    normalise(nor6);

    arma::vec normal;
    arma::vec normal2 ;




    double Przednia, Prawa, Lewa, Gorna, Dolna, Tylna;
    Przednia = ((px[1]-px[0])*(py[1]+py[0]))+((px[2]-px[1])*(py[2]+py[1]))+((px[3]-px[2])*(py[3]+py[2]))+((px[0]-px[3])*(py[0]+py[3]));
    std::cout << "px[0]: " << px[0] << " py[0]: " << py[0] << std::endl << "px[1]: " << px[1] << " py[1]: " << py[1] << std::endl << "px[2]: " << px[2] << " py[2]: " << py[2] << std::endl << "px[3]: " << px[3] << " py[3]: " << py[3] << std::endl;
    std::cout << std::endl << "Pole: " << Przednia << std::endl;
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
        std::cout << "Widac!" << std::endl << std::endl;
        PrzedniaWidoczna = true;
        normal = nor1;//

        normal = normalise(normal);

        normal2 = {normal[0], normal[1], normal[2], 0};

        cosinus = fmax(0, dot(normal2, lightDirection));

        teksturuj(px[0], py[0], px[1], py[1], px[2], py[2], px[3], py[3], cosinus);


    }
    if(Prawa > 0)
    {
        PrawaWidoczna = false;
    }
    else if(Prawa < 0)
    {
        PrawaWidoczna = true;
        normal = nor2;//

        normal = normalise(normal);

        normal2 = {normal[0], normal[1], normal[2], 0};

        cosinus = fmax(0, dot(normal2, lightDirection));

        teksturuj(px[1], py[1], px[5], py[5], px[6], py[6], px[2], py[2], cosinus);
    }
    if(Lewa > 0)
    {
        LewaWidoczna = false;
    }
    else if(Lewa < 0)
    {
        LewaWidoczna = true;

        normal = nor3;//

        normal = normalise(normal);

        normal2 = {normal[0], normal[1], normal[2], 0};

        cosinus = fmax(0, dot(normal2, lightDirection));

        teksturuj(px[4], py[4], px[0], py[0], px[3], py[3], px[7], py[7], cosinus);
    }
    if(Gorna > 0)
    {
        GornaWidoczna = false;
    }
    else if(Gorna < 0)
    {
        GornaWidoczna = true;

        normal = nor4;//

        normal = normalise(normal);

        normal2 = {normal[0], normal[1], normal[2], 0};

        cosinus = fmax(0, dot(normal2, lightDirection));


        teksturuj(px[4], py[4], px[5], py[5], px[1], py[1], px[0], py[0], cosinus);
    }
    if(Dolna > 0)
    {
        DolnaWidoczna = false;
    }
    else if(Dolna < 0)
    {
        DolnaWidoczna = true;

        normal = nor5;//

        normal = normalise(normal);

        normal2 = {normal[0], normal[1], normal[2], 0};

        cosinus = fmax(0, dot(normal2, lightDirection));

        teksturuj(px[7], py[7], px[6], py[6], px[2], py[2], px[3], py[3], cosinus);
    }
    if(Tylna > 0)
    {
        TylnaWidoczna = false;
    }
    else if(Tylna < 0)
    {
        TylnaWidoczna = true;

        normal = nor6;//

        normal = normalise(normal);

        normal2 = {normal[0], normal[1], normal[2], 0};

        cosinus = fmax(0, dot(normal2, lightDirection));

        teksturuj(px[5], py[5], px[4], py[4], px[7], py[7], px[6], py[6], cosinus);
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
