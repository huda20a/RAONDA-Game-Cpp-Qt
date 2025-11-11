#include "deck.h"
#include <iterator>
#include <vector>
#include <qstring.h>
#include <algorithm>
#include <QRandomGenerator>

Deck::Deck(Scene *sc)
{
    scene = sc;
    setPixmap(QPixmap(":/new/prefix1/images/back.jpg").scaled(scene->width()*0.09625,scene->height()*0.193,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));


    for(int i=0 ; i<4 ; i++) //all signs
    {
        for(int j=0 ; j<10 ; j++) //all numbers
        {
            Card *addingcard = new Card(QString::number(j),QString::number(i),0,scene);
            cardsDeck.push_back(addingcard);//adding cards to the vector
        }
    }
}

void Deck::shuffle(){
    srand(time(0));
    for(int i=1 ; i< rand() ; i++){ //shuffle vector a random number of times
        std::random_shuffle(cardsDeck.begin(),cardsDeck.end());
    }
}


Card *Deck::drawCard()
{
    std::vector<Card*>::reverse_iterator it = cardsDeck.rbegin();
    cardsDeck.pop_back();
    return(*it);
}

