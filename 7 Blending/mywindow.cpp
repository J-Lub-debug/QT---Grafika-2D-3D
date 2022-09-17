#include "mywindow.h"
#include <cmath>
#include "ui_mywindow.h"
#include <iostream>
#include <QFileDialog>
#include <QDebug>


MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);

    szer = 300;
    wys = 300;
    poczX = 0;
    poczY = 0;


    img = QImage(szer,wys,QImage::Format_RGB32);

    img4 = QImage(szer,wys,QImage::Format_RGB32);

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

    p.drawImage(poczX,poczY,img4);
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
    }
    }
    else
    {



    }
    update();
}
void MyWindow::alpaBlend(float alfa, QImage IMG0, QImage IMG1)
{
    for(int i = 0; i < szer; i++)
    {
        for(int j = 0; j < wys; j++)
        {
            unsigned char* ptr0 = IMG0.bits();
            unsigned char* ptr1 = IMG1.bits();
            unsigned char* ptr4 = img4.bits();
            ptr4[szer*4*i+4*j] = alfa * ptr1[szer*4*i+4*j]+(1-alfa)*ptr0[szer*4*i+4*j];
            ptr4[szer*4*i+4*j+1] = alfa * ptr1[szer*4*i+4*j+1]+(1-alfa)*ptr0[szer*4*i+4*j + 1];
            ptr4[szer*4*i+4*j+2] = alfa * ptr1[szer*4*i+4*j+2]+(1-alfa)*ptr0[szer*4*i+4*j +2];

        }
    }
    update();

}
void MyWindow::Multiply(float alfa, QImage IMG0, QImage IMG1)
{
    for(int i = 0; i < szer; i++)
    {
        for(int j = 0; j < wys; j++)
        {
            unsigned char* ptr0 = IMG0.bits();
            unsigned char* ptr1 = IMG1.bits();
            unsigned char* ptr4 = img4.bits();
            ptr4[szer*4*i+4*j] =  (ptr1[szer*4*i+4*j]*ptr0[szer*4*i+4*j]) >> 8;
            ptr4[szer*4*i+4*j+1] =  (ptr1[szer*4*i+4*j+1]*ptr0[szer*4*i+4*j + 1]) >> 8;
            ptr4[szer*4*i+4*j+2] =  (ptr1[szer*4*i+4*j+2]*ptr0[szer*4*i+4*j +2]) >> 8;

        }
    }
    alpaBlend(alfa,img4, IMG0);

}

void MyWindow::ScreenMode(float alfa, QImage IMG0, QImage IMG1)
{
    for(int i = 0; i < szer; i++)
    {
        for(int j = 0; j < wys; j++)
        {
            unsigned char* ptr0 = IMG0.bits();
            unsigned char* ptr1 = IMG1.bits();
            unsigned char* ptr4 = img4.bits();
            ptr4[szer*4*i+4*j] =  255 - ((255 - ptr1[szer*4*i+4*j])*(255-ptr0[szer*4*i+4*j]) >> 8);
            ptr4[szer*4*i+4*j+1] = 255 - ((255 - ptr1[szer*4*i+4*j+1])*(255-ptr0[szer*4*i+4*j + 1]) >> 8);
            ptr4[szer*4*i+4*j+2] = 255 - ((255 -ptr1[szer*4*i+4*j+2])*(255-ptr0[szer*4*i+4*j +2]) >> 8);

        }
    }
    alpaBlend(alfa,img4, IMG0);

}



void MyWindow::on_horizontalSlider_valueChanged(int value)
{
    if(zdjecia.size() >= 2)
    {
        for(int i = 0; i<zdjecia.size()-1; i++)
        {
            if(ui->comboBox->currentText() == "Alpa")
            {
                alpaBlend(value/100.0, zdjecia[i], zdjecia[ i+1]);
            }
            else if(ui->comboBox->currentText() == "Multiply")
            {
                Multiply(value/100.0, zdjecia[i], zdjecia[i+1]);
            }
            else if(ui->comboBox->currentText() == "ScreenMode")
            {
                ScreenMode(value/100.0, zdjecia[i], zdjecia[i+1]);
            }
        }
    }
}


void MyWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this);
    QImage zdj = QImage(filename);
    zdjecia.push_back(zdj);
    ui->listWidget->addItem(filename);
}
