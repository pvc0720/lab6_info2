#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , pantalla(new Ui::MainWindow)
{
    pantalla->setupUi(this);
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0,0,h_lim,v_lim);
    pantalla->graphicsView->setScene(escena);
    tiempo = new QTimer(this);
    connect(tiempo,SIGNAL(timeout()),this,SLOT(actualizar()));
    tiempo->start(10);

//    //Sistema 1
    sistema.append(new Planeta(0,-7000,70,120,2,0));
    sistema.append(new Planeta(0,0,70000,300,0,0));
    sistema.append(new Planeta(4000,5000,25,100,-1.6,1.2));

//    //sistema 2
//    sistema.append(new Planeta(0,0,50000,200,0,0));
//    sistema.append(new Planeta(-5000,0,70,70,0,-2));
//    sistema.append(new Planeta(5000,0,70,70,2,-2));
//    sistema.append(new Planeta(0,-5000,70,70,2,0));
//    sistema.append(new Planeta(0,5000,70,70,-2,0));

    // Cambia el color del planeta a verde
//    sistema.at(1)->setColor(QColor(Qt::green));
//    sistema.at(2)->setColor(QColor(Qt::blue));
//    sistema.at(3)->setColor(QColor(Qt::yellow));
//    sistema.at(4)->setColor(QColor(Qt::red));



    //Calculos
    origen = calculoCentroMasas(sistema);
    s = calculoEscala();
    inception();
    for(int i=0 ; i<sistema.size() ; i++){
        sistema.at(i)->asignarEscala(s);
        escena->addItem(sistema.at(i));
    }
}

MainWindow::~MainWindow()
{
    delete pantalla;
}

float MainWindow::calculoEscala()
{
    float max =0, dx=0, dy=0;

    for(int i = 0; i<sistema.size(); i++) {
        dx = origen.at(0) - sistema.at(i)->obtenerCuerpo()->getX();
        dy = origen.at(1) - sistema.at(i)->obtenerCuerpo()->getY();
        if(sqrt(dx*dx + dy*dy) > max){
            max = sqrt(dx*dx + dy*dy);
        }
    }
    max = v_lim/(2*max);
    return max;
}

QList<float> MainWindow::calculoCentroMasas(QList<Planeta *> planetas)
{
    float Mx=0, My=0, Mt=0;
    QList<float> punto;
    for(int i = 0; i<planetas.size(); i++)
    {
        Mx += planetas.at(i)->obtenerCuerpo()->getMasa() * planetas.at(i)->obtenerCuerpo()->getY();
        My += planetas.at(i)->obtenerCuerpo()->getMasa() * planetas.at(i)->obtenerCuerpo()->getX();
        Mt += planetas.at(i)->obtenerCuerpo()->getMasa();
    }
    punto.append(My/Mt);
    punto.append(Mx/Mt);
    return punto;
}

void MainWindow::calculoAceleracion()
{
    float ax = 0, ay = 0;
    int n = sistema.size();
    for(int i = 0; i<n; i++){
        for(int j = i+1; j<n; j++){
            ax= sistema.at(i)->obtenerCuerpo()->calcularAcX(*sistema.at(j)->obtenerCuerpo());
            ay= sistema.at(i)->obtenerCuerpo()->calcularAcY(*sistema.at(j)->obtenerCuerpo());
            sistema.at(i)->obtenerCuerpo()->sumarAceleracion(ax,ay);

            ax= sistema.at(j)->obtenerCuerpo()->calcularAcX(*sistema.at(i)->obtenerCuerpo());
            ay= sistema.at(j)->obtenerCuerpo()->calcularAcY(*sistema.at(i)->obtenerCuerpo());
            sistema.at(j)->obtenerCuerpo()->sumarAceleracion(ax,ay);
        }
    }
}

void MainWindow::inception()
{
    float dx = h_lim/(2*s) - origen.at(0);
    float dy = v_lim/(2*s) - origen.at(1);
    for(int i = 0; i<sistema.size(); i++)
    {
        sistema.at(i)->obtenerCuerpo()->asignarPosicion(dx,dy);
    }
}

void MainWindow::actualizar()
{
    calculoAceleracion();   //actualiza las aceleraciones de todos los cuerpos
    for(int i = 0; i<sistema.size(); i++)
        sistema.at(i)->actualizar(dt);
}



