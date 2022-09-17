#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <stdio.h>
#include <QDir>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   // img=new QImage("/users/stud/inf/zethius/Pobrane/trans/obrazek","jpg");
    img=new QImage("C:/Users/Lubie/Documents/100/dobre/grafika/trans/obrazek.png");

    ui->setupUi(this);
    this->setFixedSize(600,400);
    QWidget * wdg = new QWidget(this);
    QGridLayout *vlay=new QGridLayout(wdg);
    QPushButton *btn = new QPushButton("Reset");
    //QComboBox combo=new QComboBox();
    vlay->setColumnMinimumWidth(0,img->width()+10);
    vlay->addWidget(btn,0,2,0);
    for(int i=0; i<7; i++){
        slider[i]=new QSlider(Qt::Horizontal);
        vlay->addWidget(slider[i],i+1,3,0);
    }

    slider[0]->setRange(-500,500);
     label[0] = new QLabel(tr("t_x: "));

    slider[1]->setRange(-50,50);
     label[1] = new QLabel(tr("t_y: "));

    slider[2]->setRange(-10,20);
    slider[2]->setValue(10);
     label[2] = new QLabel(tr("sc_x: "));

    slider[3]->setRange(-10,20);
    slider[3]->setValue(10);
     label[3] = new QLabel(tr("sc_y: "));

    slider[4]->setRange(0,20);
    slider[4]->setValue(0);
     label[4] = new QLabel(tr("sh_x: "));

    slider[5]->setRange(0,20);
    slider[5]->setValue(0);
     label[5] = new QLabel(tr("sh_y: "));

    slider[6]->setRange(0,359);
     label[6] = new QLabel(tr("a: "));

    for(int i=0; i<7; i++){
        vlay->addWidget(label[i],i+1,2,0);
     }
    wdg->setLayout(vlay);
    setCentralWidget(wdg);
    connect(btn, SIGNAL (clicked()), this, SLOT (reset()));
    for(int i=0; i<7; i++){
        connect(slider[i], SIGNAL (valueChanged(int)), this, SLOT (transformuj()));

    }
    transformuj();
}

MainWindow::~MainWindow()
{
    delete ui;
    img=NULL;
    temp=NULL;
}
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(10,10,*temp);
}
void MainWindow::reset(){
    slider[0]->setValue(0);
    slider[1]->setValue(0);
    slider[2]->setValue(10);
    slider[3]->setValue(10);
    slider[4]->setValue(0);
    slider[5]->setValue(0);
    slider[6]->setValue(0);
}
void MainWindow::transformuj(){
    unsigned char *ptr;//=img->bits();
    unsigned char *tmp=NULL;
    int tx=slider[0]->value();
    int ty=slider[1]->value();
    double scx=(double)slider[2]->value()/10;
    double scy=(double)slider[3]->value()/10;
    double shx=(double)slider[4]->value()/50;
    double shy=(double)slider[5]->value()/50;
    double a=(double)slider[6]->value()*PI/180;
    int x[6];
    int y[6];
    printf("\nTranslacja: \t%d\t%d\n",tx,ty);
    printf("Skalowanie: \t%f\t%f\n",scx,scy);
    printf("Pochylenie: \t%f\t%f\n",shx,shy);
    printf("Rotacja: \t\t%f\n",a);
    temp=new QImage(img->width(),img->height(),QImage::Format_RGB32);
    ptr=img->bits();
    tmp=temp->bits();
    for(int i=0; i<img->height(); i++){
            for(int j=0; j<img->width();j++){

                x[0]=j-img->width()/2;
                y[0]=i-img->height()/2;

                x[1]=x[0]+tx;
                y[1]=y[0]+ty;

                x[2]=x[1]*scx;
                y[2]=y[1]*scy;


                x[3]=x[2]+y[2]*shx;
                y[3]=y[2]+x[2]*shy;

                x[4]=x[3]*cos(a)-y[3]*sin(a);
                y[4]=x[3]*sin(a)+y[3]*cos(a);

                x[5]=x[4]+img->width()/2;
                y[5]=y[4]+img->height()/2;

                if((x[5]<img->width()) & (y[5]<img->height()) & (x[5]>0) & (y[5]>0)){
                    tmp[i*img->width()*4+j*4]=ptr[y[5]*img->width()*4+x[5]*4];
                    tmp[i*img->width()*4+j*4+1]=ptr[y[5]*img->width()*4+x[5]*4+1];
                    tmp[i*img->width()*4+j*4+2]=ptr[y[5]*img->width()*4+x[5]*4+2];
                }
            }
    }
    update();
}
void MainWindow::Draw()
{
    int i,j;
    unsigned char *ptr;

    for (j=0;j<img->height();j++)
    {
        ptr=img->scanLine(j);
        for (i=0;i<img->width();i++)
        {
            ptr[i*4]=255;
            ptr[i*4+1]=0;
            ptr[i*4+2]=0;
        }
    }
}
