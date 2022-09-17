#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    QImage *img;

    int x1,y1,x2,y2,x3,y3,x4,y4;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mousePressEvent2(QMouseEvent * event);
    void mouseReleaseEvent2(QMouseEvent * event);
    void paintEvent(QPaintEvent * event);
    void Draw();
    void SetPixel(uchar * bits, int x, int y, uchar color);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
