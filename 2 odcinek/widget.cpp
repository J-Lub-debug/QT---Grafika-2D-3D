#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <stdio.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    img=new QImage(800,600,QImage::Format_RGB32);
    x1 = x2 = y1 = y2 = x3 = y3 = x4 = y4 = 0;
    Draw();
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event){

    x1 = event->x();
    y1 = event->y();
    uchar * v = img->bits();
    SetPixel(v,x1, y1, 255);
    update();

}

void Widget::mouseReleaseEvent(QMouseEvent *event){


    x2 = event->x();
    y2 = event->y();

    Draw();
    this->repaint();

}

void Widget::mousePressEvent2(QMouseEvent *event){

    x3 = event->x();
    y3 = event->y();

}

void Widget::mouseReleaseEvent2(QMouseEvent *event){

    x4 = event->x();
    y4 = event->y();

    Draw();
    this->repaint();

}

void Widget::paintEvent(QPaintEvent *event){

    QPainter p(this);
    p.drawImage(0,0,*img);

}

void Widget::Draw(){

    uchar * v = img->bits();

    float a = (float)(y2-y1)/(x2-x1); // m
    float b = (y1) - a * x1;

    for (int x = x1 ; x != x2; (x < x2) ? x++ : x--){

        int y = a * x + b;

        //if (x > 0 && x < 800 && y > 0 && y < 600)
            SetPixel(v,x, y, 255);

    }

    for (int y = y1 ; y != y2; (y < y2) ? y++ : y--){

        int x = (y-b)/a;

       //if (x > 0 && x < 800 && y > 0 && y < 600)
           SetPixel(v,x, y, 255);

    }

}

void Widget::SetPixel(uchar * bits, int x, int y , uchar c){

    int p = x * 4 + y * 800 * 4;

    bits[p] = c;
    bits[p+1] = c;
    bits[p+2] = c;
    bits[p+3] = c;

}
