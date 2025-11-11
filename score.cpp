#include "score.h"

Score::Score(Scene *scene, int hand):
    scene(scene),
    hand(hand)
{
    value = 0;
    text = new QGraphicsSimpleTextItem("0");
    text->setBrush(Qt::white);
    text->setFont(QFont("Segoe UI Black",scene->width()*0.015));
    addToGroup(text);






}

void Score::updateScore()
{

    text->setText(QString::number(value));
}
