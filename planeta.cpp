#include "planeta.h"

Planeta::Planeta(float posX, float posY, float masa, float radio, float velX, float velY, float AcX, float AcY)
{
    planeta = new Particula(posX, posY, masa, radio, velX, velY, AcX, AcY);
    // Asigna un color inicial, por ejemplo, rojo
    color = QColor(Qt::red);
}

Planeta::~Planeta()
{
    delete planeta;
}

void Planeta::asignarEscala(float s)
{
    escala = s;
}

void Planeta::actualizar(float dt)
{
    planeta->calcularPosicion(dt);
    planeta->asignarAceleracion();
    setPos(planeta->getX()*escala, v_lim - planeta->getY() * escala);
}

Particula *Planeta::obtenerCuerpo()
{
    return planeta;
}

QRectF Planeta::boundingRect() const
{
    return QRectF( -1*escala*planeta->getRadio() , -1*escala*planeta->getRadio() , 2*escala*planeta->getRadio() , 2*escala*planeta->getRadio() );
}


void Planeta::paint(QPainter *pintar, const QStyleOptionGraphicsItem *opcion, QWidget *widget)
{
    pintar->setBrush(color); // Usa el color en lugar de Qt::black
    pintar->drawEllipse(boundingRect());
    Q_UNUSED(opcion);
    Q_UNUSED(widget);
}
void Planeta::setColor(const QColor &newColor)
{
    color = newColor;
    update(); // Esto asegura que la vista se actualice para reflejar el nuevo color
}


