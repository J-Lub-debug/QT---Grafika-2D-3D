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
            ptr[szer*4*i + 4*j]=0; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 0; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 0; // Skladowa RED
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
/*bool MyWindow::czyJestzamalowany(int x, int y)
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
}*/

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->modifiers() == Qt::AltModifier) // Usuwanie punktu
    {
        int a1;
        int b2;
        a1 = event->x();
        b2 = event->y();
        bool trafiony = true;

        for(int j = 0; j < 50; j++)
        {
            for(int q = 0; q < 5 && trafiony == true; q++)
            {
                for(int w = 0; w < 5 && trafiony == true; w++)
                {
                    if(((a1 == tabx[j]-w || a1 == tabx[j]+w) && (b2 == taby[j]-q) || b2 == taby[j]+q))
                    {
                        std:: cout << "trafiony";
                        trafiony = false;
                        for(int c = j; c < 50; c++) // przesuniecie tablicy, usuniecie elementu
                        {
                            tabx[c] = tabx[c+1];
                            taby[c] = taby[c+1];
                        }
                        int c = i;
                        c--; // bo jest jeden mniej element niz bylo
                        i = 0;
                        licznik = -1;
                        czysc();
                        update();
                        for(; i < c; i++)
                        {
                            if((i%3 == 0) && i != 0)
                            {
                                Bezier();
                            }

                            std::cout << "Modyfikacja:" << std::endl;
                            std::cout << tabx[i] << std::endl << taby[i] << std::endl;
                        }
                        for(int i = 0; i < 10; i++)
                        {
                            std::cout << "Modyfikacja:" << std::endl;
                            std::cout << tabx[i] << std::endl << taby[i] << std::endl;
                        }
                    }
                }
            }
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        TRAFIONY = true;
        int a1;
        int b2;
        a1 = event->x();
        b2 = event->y();
        bool trafiony = true;

        for(int j = 0; j < 50; j++)
        {
            for(int q = 0; q < 5 && trafiony == true; q++)
            {
                for(int w = 0; w < 5 && trafiony == true; w++)
                {
                    if(((a1 == tabx[j]-w || a1 == tabx[j]+w) && (b2 == taby[j]-q) || b2 == taby[j]+q))
                    {
                        std:: cout << "trafiony";
                        trafiony = false;
                        zm = j;
                        TRAFIONY = false;
                    }
                }
            }
        }
    }

    else
    {

        i++; // i = -1
        tabx[i] = event->x();
        taby[i] = event->y();
        pix(tabx[i],taby[i]);
        update();

       for(int q = 0; q < 5; q++) // kwadracik
        {
            for(int w = 0; w < 5; w++)
            {
                pix(tabx[i]-w , taby[i]-q);
                pix(tabx[i]+w , taby[i]-q);
                pix(tabx[i]+w , taby[i]+q);
                pix(tabx[i]-w , taby[i]+q);
            }
        }
       if((i%3 == 0) && i != 0)
       {
       Bezier();
       }
       std::cout << std::endl;
       std::cout << tabx[i] << std::endl << taby[i] << std::endl;
    }
}
void MyWindow::Bezier() // I Bspline
{
        for(t = 0; t<1.0; t+=0.10)
        {
            licznik++; //*laczenia linia
            x = ((pow(-t,3) + 3*pow(t,2) - 3*t + 1)/6)*tabx[i-3] + ((3*pow(t,3) - 6*pow(t,2) + 4)/6)*tabx[i-2] + ((-3*pow(t,2)+3*pow(t,2)+3*t+1)/6)*tabx[i-1] + ((pow(t,3))/6) * tabx[i];
            y = ((pow(-t,3) + 3*pow(t,2) - 3*t + 1)/6)*taby[i-3] + ((3*pow(t,3) - 6*pow(t,2) + 4)/6)*taby[i-2] + ((-3*pow(t,2)+3*pow(t,2)+3*t+1)/6)*taby[i-1] + ((pow(t,3))/6) * taby[i];
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

void MyWindow::Kreska(int x0, int y0, int x1, int y1) // II BSpline
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
    if(event->button() == Qt::RightButton) // II przesuwanie pkt
    {
        if(TRAFIONY == false)
        {
            tabx[zm] = event->x();
            taby[zm] = event->y();
            int c = i;
            i = 0;
            licznik = -1;
            czysc();
            update();
            for(; i <= c; i++)
            {
                if((i%3 == 0) && i != 0)
                {
                    Bezier();
                }
            }
        }
        else
        {
            return;
        }
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


