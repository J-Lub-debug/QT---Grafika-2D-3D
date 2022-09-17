#include "mywindow.h"
#include <cmath>
#include "ui_mywindow.h"

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

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    midx = event->x();
    midy = event->y();
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    edgex = event->x();
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
    }
    update();
}


