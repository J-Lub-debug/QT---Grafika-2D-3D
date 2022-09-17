// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"
#include <cmath>
// Dolaczamy plik naglowkowy zawierajacy definicje GUI
// Plik ten jest generowany automatycznie
// z pliku XML "mywindow.ui"
#include "ui_mywindow.h"

// Definicja konstruktora, wywolujemy najpierw
// konstruktor klasy nadrzednej, nastepnie tworzymy
// obiekt klasy Ui_MyWindow reprezentujacy GUI
MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    // Wywolujemy funkcje tworzaca elementy GUI
    // Jej definicja znajduje sie w pliku "ui_mywindow.h"
    ui->setupUi(this);

    // Pobieramy wymiary i wspolrzedne lewego gornego naroznika ramki
    // i ustawiamy wartosci odpowiednich pol
    // Uwaga: ramke "rysujFrame" wykorzystujemy tylko do
    // wygodnego ustaiwenia tych wymiarow. Rysunek bedziemy wyswietlac
    // bezposrednio w glownym oknie aplikacji.
    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();

    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    img = new QImage(szer,wys,QImage::Format_RGB32);

}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete ui;
}

// Funkcja (slot) wywolywana po nacisnieciu przycisku "Wyjscie" (exitButton)
// Uwaga: polaczenie tej funkcji z sygnalem "clicked"
// emitowanym przez przycisk jest realizowane
// za pomoca funkcji QMetaObject::connectSlotsByName(MyWindow)
// znajdujacej sie w automatycznie generowanym pliku "ui_mywindow.h"
// Nie musimy wiec sami wywolywac funkcji "connect"
void MyWindow::on_exitButton_clicked()
{
    // qApp to globalny wskaznik do obiektu reprezentujacego aplikacje
    // quit() to funkcja (slot) powodujaca zakonczenie aplikacji z kodem 0 (brak bledu)
    qApp->quit();
}


// Funkcja "odmalowujaca" komponent
void MyWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy gorny naroznik)
    p.drawImage(poczX,poczY,*img);
}


// Funkcja (slot) wywolywana po nacisnieciu przycisku "Czysc" (cleanButton)
void MyWindow::on_cleanButton_clicked()
{
    // Funkcja czysci (zamalowuje na bialo) obszar rysowania
    // definicja znajduje sie ponizej
    czysc();

    // Funkcja "update()" powoduje ponowne "namalowanie" calego komponentu
    // Wywoluje funkcje "paintEvent"
    update();
}


// Funkcja (slot) wywolywana po nacisnieciu przycisku "Rysuj 1" (draw1Button)
void MyWindow::on_draw1Button_clicked()
{
    rysuj1();
    update();
}

// Funkcja (slot) wywolywana po nacisnieciu przycisku "Rysuj 2" (draw2Button)
void MyWindow::on_draw2Button_clicked()
{
    rysuj2();
    update();
}

// Funkcja powoduje wyczyszczenie (zamalowanie na bialo)
// obszaru rysowania
void MyWindow::czysc()
{
    // Wskaznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr;

    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr = img->bits();

    int i,j;

    // Przechodzimy po wszystkich wierszach obrazu
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


// Funkcja powoduje zamalowanie obszaru rysowania pewnym wzorem
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

// Funkcja powoduje zamalowanie obszaru rysowania pewnym wzorem
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

// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    midx = event->x();
    midy = event->y();
    //pix(midx, midy);
    //update();
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    edgex = event->x();
    edgey = event->y();
    pix(edgex, edgey);

    /*float r = sqrt(pow(edgex - midx,2) + pow(edgey - midy,2));
    float point;
    int y;

    midx -= poczX;
    edgex -= poczX;
    midy -= poczY;
    edgey -= poczY;

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
    /*if(line_bx == line_ex)
    {
        a = line_bx;

        if(line_by > line_ey){
            float temp = line_by;
            line_by = line_ey;
            line_ey = temp;
        }

        for(int i = line_by;i <= line_ey;i++){
            ptr[szer*4*i + 4*(int)a] = 255;
            ptr[szer*4*i + 4*(int)a + 1] = 255;
            ptr[szer*4*i + 4*(int)a + 2] = 255;
        }

    }
    else
    {
        a = 1.0 * (line_ey - line_by) / (line_ex - line_bx);

        float b = line_by - a * line_bx;


        if(line_bx > line_ex){
            int temp = line_bx;
            line_bx = line_ex;
            line_ex = temp;
        }

        for(int i = line_bx;i < line_ex;i++){
            y = (i * a + b);
            y_int = floor(y + 0.5);
            ptr[szer*4*y_int + 4*i] = 255;
            ptr[szer*4*y_int + 4*i + 1] = 255;
            ptr[szer*4*y_int + 4*i + 2] = 255;

            next_y_int = floor(( (i+1) * a + b) + 0.5);

            if(y_int > next_y_int){
                int temp = y_int;
                y_int = next_y_int;
                next_y_int = temp;
            }

            for(int j = y_int;j < next_y_int;j++){
                ptr[szer*4*j + 4*i] = 255;
                ptr[szer*4*j + 4*i + 1] = 255;
                ptr[szer*4*j + 4*i + 2] = 255;
            }
        }
    }*/
    update();
}


