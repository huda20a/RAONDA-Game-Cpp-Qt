#include "hand.h"
#include "card.h"
#include <vector>

Hand::Hand(Scene *sc)
{
    scene = sc;
}
void Hand::addCard(Card *addingCard){
    cardsHand.push_back(addingCard);
}

Card *Hand::checkCard(Card * checkingCard){

    if(cardsHand.empty()) return nullptr;

    for(int i = 0; i < cardsHand.size();i++)
    {
        if(cardsHand[i]->getNumber() == checkingCard->getNumber())
            return cardsHand[i];
    }
    return nullptr;
}

void Hand::dropCard(Card *checkingCard)
{
    if(checkCard(checkingCard)!=nullptr){
        for(int i = 0; i < cardsHand.size();i++)
        {
            if( cardsHand[i] == checkingCard ){
                cardsHand[i]->setHand(0);
                cardsHand.removeAt(i);
                cardsHand.squeeze();
                return;
            }

        }
    }
}
