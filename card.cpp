#include "card.h"
#include "scene.h"


Card::Card(QString n,QString s,int wh,Scene *sc):
    number(n),
    sign(s),
    whichhand(wh),
    isShown(false),
    scene(sc)
{
    setAcceptHoverEvents(true);

    QString link = "";
    link.append(":/new/prefix1/images/").append(s).append(n).append(".gif"); //select the right image
    image = QPixmap(link).scaled(scene->width()*0.09625,scene->height()*0.193,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    backImg = QPixmap(":/new/prefix1/images/back.jpg").scaled(scene->width()*0.09625,scene->height()*0.193,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    setPixmap(backImg);

    posAnimation = new QPropertyAnimation(this,"pos",this);
    posAnimation->setEasingCurve(QEasingCurve::InQuad); //animation easing cruve type


}

Card::Card(Card *card):Card(card->number,card->sign,card->whichhand,card->scene)
{
}

void Card::flip(){
    if(isShown) {
        setPixmap(backImg);
        isShown = false;
    }
    else {
        setPixmap(image);
        isShown = true;
    }
}



void  Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(scene->waiting && whichhand == 1)
        scene->selectedCard=this;
    QGraphicsPixmapItem::mousePressEvent(event);
}

void Card::setHand(int newHand){
    whichhand = newHand;
}

int Card::getNumber()
{
    return number.toInt();
}

QPointF Card::pos() const
{
    return m_pos;
}

void Card::startAnim(QPointF addingPos, int duration)
{
    posAnimation->setStartValue(this->pos());
    posAnimation->setEndValue(addingPos);
    posAnimation->setDuration(duration);
    posAnimation->start();

}

void Card::startAnim(QPointF addingPos)
{
    startAnim(addingPos,posAnimation->duration());
}


void Card::setpos(QPointF newPOS)
{
    m_pos = newPOS;
    setPos(newPOS);
}


