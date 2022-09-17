#include "mywindow.h"
#include <cmath>
#include "ui_mywindow.h"
#include <iostream>
#include <QFileDialog>
#include <QDebug>
#include <vector>
#include <algorithm>

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
    tekstura2 = QImage(":dwa.jpg");
    bits = img.bits();

    zeruj();
    odleglosc = 300;

    tx = ty = tz = alfa = alfaX = alfaY = alfaZ = Shx = Shy = Shz = 0;
    Scx = Scy = Scz = 1;
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



    for(int i=0; i<5; i++) {
        konwertujNa2D(x[i],y[i],z[i],i);
    }
   // rysujKreski();
    WidocznoscSciany();

}

void MyWindow::zeruj()
{
    //Przod podstawy
    x[0]=100;
    y[0]=100;
    z[0]=0;
    // Przod podstway
    x[1]=-100;
    y[1]=100;
    z[1]=0;
    //Tyl podstawy
    x[2]=100;
    y[2]=100;
    z[2]=200;
    //Tyl podstawy
    x[3]=-100;
    y[3]=100;
    z[3]=200;
    //Srodek
    x[4]=0;
    y[4]=-200;
    z[4]=100;
}


void MyWindow::rysujKreski()
{
    Kreska(px[0], py[0], px[1], py[1]);
    Kreska(px[2], py[2], px[3], py[3]);

    Kreska(px[0], py[0], px[2], py[2]);
    Kreska(px[1], py[1], px[3], py[3]);

    Kreska(px[0], py[0], px[4], py[4]);
    Kreska(px[1], py[1], px[4], py[4]);
    Kreska(px[2], py[2], px[4], py[4]);
    Kreska(px[3], py[3], px[4], py[4]);
}

void MyWindow::konwertujNa2D(double x, double y, double z, int i)
{
    pp.clear();
    pp.push_back(x);
    pp.push_back(y);
    pp.push_back(0);
    pp.push_back(z*(1/odleglosc)+1);
    for(int j = 0; j < 4; ++j) pp[j] = pp[j]/pp[3];
    px[i]=pp[0]+300;
    py[i]=pp[1]+300;
    pz[i]=z;

    //z wtedy nie dziala
    //px[i]=x+300;
    //py[i]=y+300;

    //px[i]=(x/(z*(1/300.0)+1))+300.0;
    //    py[i]=(y/(z*(1/300.0)+1))+300.0;
    //    pz[i]=z;
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
    for(int i = 0; i < 5; i++) {
        srodekx = srodekx + x[i];
        srodeky = srodeky + y[i];
        srodekz = srodekz + z[i];

    }
    srodekx = srodekx/5;
    srodeky = srodeky/5;
    srodekz = srodekz/5;

    for(int i = 0; i < 5; i++) {
        x[i] = x[i] - srodekx;
        y[i] = y[i] -  srodeky;
        z[i] = z[i] - srodekz;
    }
    for(int i = 0; i < 5; i++) {
        v1 = {x[i], y[i], z[i], 1};
        v2 = Translacja*Skalowanie*ObrotZ*ObrotY*ObrotX * PochylenieZ* PochylenieY*PochylenieX* v1;//Translacja*Skalowanie*ObrotZ*ObrotY*ObrotX * v1;


        xx[i] = v2[0]+srodekx;
        yy[i] = v2[1]+0.5+srodeky;
        zz[i] = v2[2]+0.5+srodekz;
        konwertujNa2D(v2[0]+srodekx,v2[1]+0.5+srodeky,v2[2]+0.5+srodekz,i);
    }
   WidocznoscSciany();

}

void MyWindow::teksturujTrojkat(int px0, int py0, int px1, int py1, int px2, int py2, double kat)
{
    double u,v,w;
    double W = (300 - 0) * (0 - 0) - (300 - 0) * (300 - 0);
    for(int x = 0; x<300; x++)
    {
        for(int y = 0; y<300; y++)
        {
            v = ((x - 0) * (0 - 0) - (300 - 0) * (y - 0)) / (1.0*W);
            w = ((300 - 0) * (y - 0) - (x - 0) * (300 - 0)) / (1.0*W);
            u = 1 - v - w;

            if ((u >= 0 && u <= 1) && (v >= 0 && v <= 1) && (w >= 0 && w <= 1)) {
                double X, Y;
                X = (u * px0 + v * px2 + w * px1);
                Y = (u * py0 + v * py2 + w * py1);
                QColor Kolor(tekstura.pixel(x,y));
                pix2(X,Y,Kolor.red()*kat,Kolor.green()*kat,Kolor.blue()*kat);


            }
        }
    }
    update();

}


void MyWindow::teksturujKwadrat(int px0, int py0, int px1, int py1, int px2, int py2, int px3, int py3, double kat)
{
        double u,v,w, u2, v2, w2;
        double W = (300 - 0) * (0 - 0) - (300 - 0) * (300 - 0);
        double W2 = (0 - 0) * (300 - 0) - (300 - 0) * (300 - 0);
        for(int x = 0; x<300; x++)
        {
            for(int y = 0; y<300; y++)
            {
                v = ((x - 0) * (0 - 0) - (300 - 0) * (y - 0)) / W;
                w = ((300 - 0) * (y - 0) - (x - 0) * (300 - 0)) / W;
                u = 1 - v - w;


                if ((u >= 0 && u <= 1) && (v >= 0 && v <= 1) && (w >= 0 && w <= 1)) {
                    double X, Y;
                    X = (u * px0 + v * px2 + w * px1);
                    Y = (u * py0 + v * py2 + w * py1);
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red()*kat,Kolor.green()*kat,Kolor.blue()*kat); //sam kat zamiast cos(kat)


                }
                v2 = ((x - 0) * (300 - 0) - (300 - 0) * (y - 0)) / W2;
                w2 = ((0 - 0) * (y - 0) - (x - 0) * (300 - 0)) / W2;
                u2 = 1 - v2 - w2;


                if ((u2 >= 0 && u2 <= 1) && (v2 >= 0 && v2 <= 1) && (w2 >= 0 && w2 <= 1)) {
                    double X, Y;
                    X = (u2 * px0 + v2 * px3 + w2 * px2);
                    Y = (u2 * py0 + v2 * py3 + w2 * py2);
                    QColor Kolor(tekstura.pixel(x,y));
                    pix2(X,Y,Kolor.red()*kat,Kolor.green()*kat,Kolor.blue()*kat);

                }

            }
        }

    update();

}
void MyWindow::WidocznoscSciany() //kat miedzy wektorem swiatla a plaszczyzny
{
    //OŚWIETLENIE
    arma::vec vertex = {srodekx, srodeky, srodekz, 0}; //odejmujemy to w lightDir zeby padalo na srodek bryly

    arma::vec lightPosition = {0.0,0.0,1.0,1.0}; //1. Definuje Polozenie oświetlenia(źródło światła)

    /*czerwony*/ arma::vec lightDirection = lightPosition - vertex; //2.przesuwam zrodlo swiatla do srodka bryły ukwsp
    lightDirection = normalise(lightDirection); //i normalizuje (wektor normalny dla swiatla)

    arma::vec vv0={xx[0], yy[0], zz[0]}; //3.Tworze wektory dla kazdego wierzcholka
    arma::vec vv1={xx[1], yy[1], zz[1]};
    arma::vec vv2={xx[2], yy[2], zz[2]};
    arma::vec vv3={xx[3], yy[3], zz[3]};
    arma::vec vv4={xx[4], yy[4], zz[4]};


    //Iloczyny vektorowe
    arma::vec nor1 = cross(vv1-vv4, vv0-vv4); //4.Licze iloczyn wektorowy dla kazdej sciany
    arma::vec nor2 = cross(vv0-vv4, vv2-vv4);
    arma::vec nor3 = cross(vv2-vv4, vv3-vv4);
    arma::vec nor4 = cross(vv3-vv4, vv1-vv4);
    arma::vec nor5 = cross(vv0-vv2, vv1-vv2);

    normalise(nor1);
    normalise(nor2);
    normalise(nor3);
    normalise(nor4);
    normalise(nor5);

    arma::vec normal;
    arma::vec normal2 ;


    //Algorytm Malarza
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
    double Przednia, Prawa, Lewa, Dolna, Tylna;
    double glebokosc[5];

    glebokosc[0] = Przednia = (pz[0]+pz[4]+pz[1])/3;
    glebokosc[1] = Prawa = (pz[1]+pz[4]+pz[3])/3;
    glebokosc[2] = Lewa = (pz[2]+pz[4]+pz[0])/3;
    glebokosc[3] = Tylna = (pz[3]+pz[4]+pz[2])/3;
    glebokosc[4] = Dolna = (pz[0]+pz[2]+pz[3]+pz[1])/4;

    bool PrzedZamalowana, PrawaZamalowana, LewaZamalowana, TylnaZamalowana, DolnaZamalaowana;
    PrzedZamalowana = PrawaZamalowana = LewaZamalowana = TylnaZamalowana = DolnaZamalaowana = false;

    std::sort(glebokosc, glebokosc+5);

    for(int i = 4; i>=0; i--)
    {
        if(glebokosc[i] == Przednia && PrzedZamalowana == false)
        {
            PrzedZamalowana = true;

            normal = nor1;//

            normal = normalise(normal); //5. Normalizuje wektor ( po prostu dzielimy przez dlugosc wektora)
                                        //Efektem normalizacji jest wektor biegnacy w tym samym kierunku ale o dlugosci 1

            normal2 = {normal[0], normal[1], normal[2], 0};

            cosinus = fmax(0.1, dot(normal2, lightDirection)); //6. Licze iloczyn skalarny (dot) wynikiem jest iloczyn długości
           // dwóch wektorów i cosinus kąta między nimi z wziązku z czym muszę podzielić przez długość wektorów = 1

            //dot iloczyn skalarny ktory jest tak naprawde cosinusem kąta miedzy dwoma wektorami
            //Wynikiem iloczynu skalarnego jest liczba (skalar) równa iloczynowi długości dwóch wektorów i cosinusa kąta między nimi.

            teksturujTrojkat(px[4], py[4], px[1], py[1], px[0], py[0], cosinus);

        }
        else if(glebokosc[i] == Prawa && PrawaZamalowana == false)
        {
            PrawaZamalowana = true;

            normal = nor2;//

            normal = normalise(normal);

            normal2 = {normal[0], normal[1], normal[2], 0};

            cosinus = fmax(0.1, dot(normal2, lightDirection));

            teksturujTrojkat(px[4], py[4], px[3], py[3], px[1], py[1], cosinus);

        }
        else if(glebokosc[i] == Lewa && LewaZamalowana == false)
        {
            LewaZamalowana = true;

            normal = nor3;//

            normal = normalise(normal);

            normal2 = {normal[0], normal[1], normal[2], 0};

            cosinus = fmax(0.1, dot(normal2, lightDirection));

            teksturujTrojkat(px[4], py[4], px[0], py[0], px[2], py[2], cosinus);
        }
        else if(glebokosc[i] == Tylna && TylnaZamalowana == false)
        {
            TylnaZamalowana = true;

            normal = nor4;//

            normal = normalise(normal);

            normal2 = {normal[0], normal[1], normal[2], 0};

            cosinus = fmax(0.1, dot(normal2, lightDirection));

            teksturujTrojkat(px[4], py[4], px[2], py[2], px[3], py[3], cosinus);
        }
        else if(glebokosc[i] == Dolna && DolnaZamalaowana == false)
        {
            DolnaZamalaowana = true;

            normal = nor5;//

            normal = normalise(normal);

            normal2 = {normal[0], normal[1], normal[2], 0};

            cosinus = fmax(0.1, dot(normal2, lightDirection));

            //teksturuj(px[7], py[7], px[6], py[6], px[2], py[2], px[3], py[3], cosinus);


            teksturujKwadrat(px[0], py[0], px[1], py[1], px[3], py[3], px[2], py[2], cosinus);

        }
    }

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */


    /*double Przednia, Prawa, Lewa, Dolna, Tylna;
    Przednia = ((px[1]-px[4])*(py[1]+py[4]))+((px[0]-px[1])*(py[0]+py[1]))+((px[4]-px[0])*(py[4]+py[0])); //((px[1]-px[0])*(py[1]+py[0]))+((px[2]-px[1])*(py[2]+py[1]))+((px[3]-px[2])*(py[3]+py[2]))+((px[0]-px[3])*(py[0]+py[3]));
    Prawa = ((px[3]-px[4])*(py[3]+py[4]))+((px[1]-px[3])*(py[1]+py[3]))+((px[4]-px[1])*(py[4]+py[1])); //((px[5]-px[1])*(py[5]+py[1]))+((px[6]-px[5])*(py[6]+py[5]))+((px[2]-px[6])*(py[2]+py[6]))+((px[1]-px[2])*(py[1]+py[2]));
    Lewa = ((px[0]-px[4])*(py[0]+py[4]))+((px[2]-px[0])*(py[2]+py[0]))+((px[4]-px[2])*(py[4]+py[2])); //((px[0]-px[4])*(py[0]+py[4]))+((px[3]-px[0])*(py[3]+py[0]))+((px[7]-px[3])*(py[7]+py[3]))+((px[4]-px[7])*(py[4]+py[7]));
    Tylna = ((px[2]-px[4])*(py[2]+py[4]))+((px[3]-px[2])*(py[3]+py[2]))+((px[4]-px[3])*(py[4]+py[3])); //((px[4]-px[5])*(py[4]+py[5]))+((px[7]-px[4])*(py[7]+py[4]))+((px[6]-px[7])*(py[6]+py[7]))+((px[5]-px[6])*(py[5]+py[6]));
    Dolna = ((px[1]-px[0])*(py[1]+py[0]))+((px[3]-px[1])*(py[3]+py[1]))+((px[2]-px[3])*(py[2]+py[3]))+((px[0]-px[2])*(py[0]+py[2])); //((px[2]-px[3])*(py[2]+py[3]))+((px[6]-px[2])*(py[6]+py[2]))+((px[7]-px[6])*(py[7]+py[6]))+((px[3]-px[7])*(py[3]+py[7]));
    std::cout << "px[1]: " << px[1] << " py[1]: " << py[1] << "px[2]: " << px[2] << " py[2]: " << py[2] << "px[3]: " << px[3] << " py[3]: " << py[3] << "px[4]: " << px[4] << " py[4]: " << py[4] << std::endl;
    std::cout << std::endl << "Pole: " << Przednia << std::endl;
    if(Przednia > 0)
    {
        std::cout << "Widać!" << std::endl;
        PrzedniaWidoczna = false;
        //OŚWIETLENIE
        normal = nor1;//

        normal = normalise(normal); //5. Normalizuje wektor ( po prostu dzielimy przez dlugosc wektora)
                                    //Efektem normalizacji jest wektor biegnacy w tym samym kierunku ale o dlugosci 1

        normal2 = {normal[0], normal[1], normal[2], 0};

        cosinus = fmax(0.1, dot(normal2, lightDirection)); //6. Licze iloczyn skalarny (dot) wynikiem jest iloczyn długości
       // dwóch wektorów i cosinus kąta między nimi z wziązku z czym muszę podzielić przez długość wektorów = 1

        //dot iloczyn skalarny ktory jest tak naprawde cosinusem kąta miedzy dwoma wektorami
        //Wynikiem iloczynu skalarnego jest liczba (skalar) równa iloczynowi długości dwóch wektorów i cosinusa kąta między nimi.

        teksturujTrojkat(px[4], py[4], px[1], py[1], px[0], py[0], cosinus);
    }
    else if(Przednia< 0)
    {
        PrzedniaWidoczna = true;
    }
    if(Prawa > 0)
    {
        PrawaWidoczna = false;

        normal = nor2;//

        normal = normalise(normal);

        normal2 = {normal[0], normal[1], normal[2], 0};

        cosinus = fmax(0.1, dot(normal2, lightDirection));

        teksturujTrojkat(px[4], py[4], px[3], py[3], px[1], py[1], cosinus);
    }
    else if(Prawa < 0)
    {
        PrawaWidoczna = true;

    }
    if(Lewa > 0)
    {
        LewaWidoczna = false;

        normal = nor3;//

        normal = normalise(normal);

        normal2 = {normal[0], normal[1], normal[2], 0};

        cosinus = fmax(0.1, dot(normal2, lightDirection));

        teksturujTrojkat(px[4], py[4], px[0], py[0], px[2], py[2], cosinus);
    }
    else if(Lewa < 0)
    {
        LewaWidoczna = true;
    }
    if(Dolna > 0)
    {
        DolnaWidoczna = false;

        normal = nor5;//

        normal = normalise(normal);

        normal2 = {normal[0], normal[1], normal[2], 0};

        cosinus = fmax(0.1, dot(normal2, lightDirection));

        //teksturuj(px[7], py[7], px[6], py[6], px[2], py[2], px[3], py[3], cosinus);


        teksturujKwadrat(px[0], py[0], px[1], py[1], px[3], py[3], px[2], py[2], cosinus);
    }
    else if(Dolna < 0)
    {
        DolnaWidoczna = true;

    }

    if(Tylna > 0)
    {
        TylnaWidoczna = false;
        normal = nor4;//

        normal = normalise(normal);

        normal2 = {normal[0], normal[1], normal[2], 0};

        cosinus = fmax(0.1, dot(normal2, lightDirection));

        teksturujTrojkat(px[4], py[4], px[2], py[2], px[3], py[3], cosinus);
    }
    else if(Tylna < 0)
    {
        TylnaWidoczna = true;
    }*/
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
