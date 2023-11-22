#ifndef PLANETA_H
#define PLANETA_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "particula.h"

#define h_lim 1000
#define v_lim 500

class Planeta: public QGraphicsItem
{

public:
    Planeta(float posX=0, float posY=0,float masa=0,float radio = 0, float velX=0, float velY=0, float AcX=0, float AcY=0);
    ~Planeta();

    void asignarEscala(float s);
    void actualizar(float dt);
    Particula *obtenerCuerpo();

    QRectF boundingRect() const;    //necesario definirla, devuelve el rectangulo que encierra el objeto
    void paint(QPainter *pintar, const QStyleOptionGraphicsItem *opcion, QWidget *widget); //define como se pintara el objeto
    void setColor(const QColor &newColor);

private:
    Particula *planeta;
    float escala;
    QColor color; // Agrega la variable de color
};

#endif // PLANETA_H
