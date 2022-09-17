#include "mywindow.h"
#include <cmath>
#include "ui_mywindow.h"
#include <iostream>

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    szer = 600;
    wys = 600;
    poczX = 0;
    poczY = 0;

    x0 = y0 = x1 = y1 = m = x = y = a = b = 0;
    i = licznik = -1;

    img = new QImage(szer,wys,QImage::Format_RGB32);
    ui->setupUi(this);

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
        /*for(i=0;i<4;i++)
        {
            std::cout << tabx[i] << "\n";
            std::cout << taby[i] << "\n";
        }*/
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
    ptr[szer*4*y + 4*x + 3] = 255;
}
bool MyWindow::czyJestzamalowany(int x, int y)
{
    unsigned char* ptr = img->bits();
    if(ptr[szer*4*y + 4*x] == 255){
        std::cout << "Jest\n";
        return true;
    }
    else{
        std::cout <<"nie jest\n";
        return false;
    }
}

// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) // sprawdzanie czy punkt trafiony
    {
        int a1;
        int b2;
        a1 = event->x();
        b2 = event->y();
        int j = 0;
        bool trafiony = true;

        std::cout << "Punkt wybrany:" << a1 << " " << b2 << std::endl;
        for(int j = 0; j < 50; j++)
        {
            trafiony = true;
            for(int q = 0; q < 5 && trafiony == true; q++)
            {
                for(int w = 0; w < 5 && trafiony == true; w++)
                {
                    if(((a1 == tabx[j]-w || a1 == tabx[j]+w) && (b2 == taby[j]-q) || b2 == taby[j]+q))
                    {
                        std:: cout << "trafiony";
                        trafiony = false;
                    }
                }
            }
        }



        /*stosx.push(event->x());
        stosy.push(event->y());
        pix(stosx.top(), stosy.top());
        while(!(stosx.empty() && stosy.empty()))
        {
            a = stosx.top();
            b = stosy.top();
            stosx.pop();
            stosy.pop();

            if(!(czyJestzamalowany(a+1, b)))
            {
                pix(a+1, b);
                stosx.push(a+1);
                stosy.push(b);
            }
            if(!(czyJestzamalowany(a-1, b)))
            {
                pix(a-1, b);
                stosx.push(a-1);
                stosy.push(b);
            }
            if(!(czyJestzamalowany(a, b+1)))
            {
                pix(a, b+1);
                stosx.push(a);
                stosy.push(b+1);
            }
            if(!(czyJestzamalowany(a, b-1)))
            {
                pix(a, b-1);
                stosx.push(a);
                stosy.push(b-1);
            }
        }
        update();*/

    }

    else
    {
   /* midx = event->x();
    midy = event->y();*/

    Bezier(event->x(), event->y());
    }
}
void MyWindow::Bezier(int a, int b)
{
    i++; // i = -1
    tabx[i] = a; // krzywa Beziera
    taby[i] = b;
    pix(a,b);
    update();

    //std::cout << "Punkt wybrany Bezier: " << tabx[0] << " " << taby[0] << " Koniec";
   for(int q = 0; q < 5; q++) // kwadracik
    {
        for(int w = 0; w < 5; w++)
        {
            pix(tabx[i]-w , taby[i]-q);
            pix(tabx[i]+w , taby[i]-q);
            pix(tabx[i]+w , taby[i]+q);
            pix(tabx[i]-w , taby[i]+q);
            if(i == 0)
            {
                std::cout << tabx[i] + w << " " << taby[i]-q << std::endl;
                update();
            }
        }
    }

    if((i%3 == 0) && i != 0)
    {
        for(t = 0; t<1.0; t+=0.10)
        {
            licznik++; //*laczenia linia
            x = pow(1-t,3)*tabx[i-3] + 3*pow(1-t,2)*t*tabx[i-2] + 3*(1-t)*pow(t,2)*tabx[i-1] + pow(t,3) * tabx[i];
            y = pow(1-t,3)*taby[i-3] + 3*pow(1-t,2)*t*taby[i-2] + 3*(1-t)*pow(t,2)*taby[i-1] + pow(t,3) * taby[i];
            pix(x,y);

            X[licznik] = x; // laczenie linia
            Y[licznik] = y;
            if(licznik >= 1)
            {
                Kreska(X[licznik-1], Y[licznik-1], X[licznik], Y[licznik]);
            }
        }
        update();
    }
}

void MyWindow::Kreska(int x0, int y0, int x1, int y1)
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

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {

        return;
    }
    else
    {
        return;

    /*edgex = event->x();
    edgey = event->y();

    float r = sqrt(pow(edgex - midx,2) + pow(edgey - midy,2));
    float point;
    int y;


    for(int x = 0; x <= floor(r/sqrt(2) + 0.5); x++){
        point = sqrt(pow(r,2) - pow(x,2));
        y = floor(point + 0.5);

        pix(x + midx,y + midy);
        pix(-x + midx,y + midy);
        pix(x + midx,-y + midy);
        pix(-x + midx,-y + midy);

        pix(y + midx,x + midy);
        pix(-y + midx,x + midy);
        pix(y + midx,-x + midy);
        pix(-y + midx,-x + midy);
    }*/
    }
    //update();
}


