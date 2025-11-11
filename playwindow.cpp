#include "playwindow.h"
#include "ui_playwindow.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

#include <iterator>
#include <vector>

#include <QTime>

#include "scene.h"
#include "deck.h"
#include "table.h"
#include "hand.h"
#include "card.h"
#include "score.h"
#include "info.h"

void delay(qreal delay)
{
    QTime dieTime= QTime::currentTime().addMSecs(delay);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,10000);
}

PlayWindow::PlayWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayWindow)
{
    ui->setupUi(this);
    x=width();
    y=height();

    scene = new Scene();
    scene->waiting=false;
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(-x/2,-y/2,x,y);

    //set up the background
    QGraphicsPixmapItem * background = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/images/playBoard.png").scaled(scene->width(),scene->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    scene->addItem(background);
    background->setPos(QPointF(-background->boundingRect().width()/2,-background->boundingRect().height()/2)); //set up the position of the background

    //set up info (text to give information)
    gameoverText = new Info(scene,"");
    setFont(QFont("Segoe UI Black",scene->width()*0.03));
    scene->addItem(gameoverText);
}

PlayWindow::~PlayWindow()
{
    delete ui;
}

//function to call to start the game
void PlayWindow::startgame()
{
    qInfo("Game started"); //game started info

    //set up deck
    Deck *deck = new Deck(scene);
    deck->setPos(QPointF(-x*0.425,0)+QPointF(-deck->boundingRect().width()/2,-deck->boundingRect().height()/2));//set position of the deck
    scene->addItem(deck);

    //set up player score ui
    playerScore=new Score(scene,1);
    opScore=new Score(scene,0);
    scene->addItem(playerScore);
    scene->addItem(opScore);
    playerScore->setPos(QPointF(-x*0.35,y*0.4)+QPointF(-playerScore->boundingRect().width()/2,-playerScore->boundingRect().height()/2));
    opScore->setPos(QPointF(-x*0.35,-y*0.4)+QPointF(-opScore->boundingRect().width()/2,-opScore->boundingRect().height()/2));

    //set up player/op hand and table
    hand = new Hand(scene);
    op= new Hand(scene);
    table = new Table(scene);
    deck->shuffle(); //shuffle cards vector in deck


    for(int i=0;i<5;i++) round(deck,hand,op); //start rounds (5 round in the game)

    delay(500);//delay between last round end and clearing the table

    //collecting romaining cards
    if(!table->cardsHand.isEmpty())
    {
        if(lastcolledted){ //by the player
            for (int k=1;k<=table->cardsHand.size();k++)
                table->cardsHand[k-1]->startAnim(QPointF(-x/3,y/2),k*50 +600);
            playerScore->value += table->cardsHand.size(); //adding romaining cards to the player score
        }
        else { //by the op
            for (int k=1;k<=table->cardsHand.size();k++)
                table->cardsHand[k-1]->startAnim(QPointF(-x/3,-y*0.7 ),k*50 +600);
            opScore->value += table->cardsHand.size();//adding romaining cards to the player score
        }

        //updating scores
        playerScore->updateScore();
        opScore->updateScore();
    }

    //setting up game end texts
    if(playerScore->value>20) gameoverText->setText("GREAT JOB , YOU WON !!");
    else if(playerScore->value<20) gameoverText->setText("GAME OVER ! YOU LOST , GOODLUCK NEXT TIME...");
    else if(playerScore->value==20) gameoverText->setText("GAME OVER , IT'S A DRAW !!");
    gameoverText->setPos(QPointF(-gameoverText->boundingRect().width()/2,-gameoverText->boundingRect().height()/2));
    gameoverText->startAnimation();

}

void PlayWindow::round(Deck *deck, Hand *hand, Hand *op){

    for(int i=0;i<4;i++){

        hand->addCard(deck->drawCard());

        hand->cardsHand[i]->posAnimation->setStartValue(QPointF(-x*0.425,0)+QPointF(-hand->cardsHand[i]->boundingRect().width()/2,-hand->cardsHand[i]->boundingRect().height()/2)); //start card animation from deck position
        hand->cardsHand[i]->posAnimation->setEndValue(QPointF(-x*0.175 + i*x*0.116, y*0.4)+QPointF(-hand->cardsHand[i]->boundingRect().width()/2,-hand->cardsHand[i]->boundingRect().height()/2)); //end card animation in the free positon in hand
        hand->cardsHand[i]->posAnimation->setDuration(500); //duration of animation

        hand->cardsHand[i]->setHand(1);

        scene->addItem(hand->cardsHand[i]);

        hand->cardsHand[i]->posAnimation->start();


    }


    for(int i=0;i<4;i++){

        op->addCard(deck->drawCard());

        op->cardsHand[i]->posAnimation->setStartValue(QPointF(-x*0.425,0)+QPointF(-op->cardsHand[i]->boundingRect().width()/2,-op->cardsHand[i]->boundingRect().height()/2));
        op->cardsHand[i]->posAnimation->setEndValue(QPointF(-x*0.175 + i*x*0.116, -y*0.4)+QPointF(-op->cardsHand[i]->boundingRect().width()/2,-op->cardsHand[i]->boundingRect().height()/2));
        op->cardsHand[i]->posAnimation->setDuration(500);

        scene->addItem(op->cardsHand[i]);

        op->cardsHand[i]->posAnimation->start();

    }



    delay(700);

    for(int i=0;i<4;i++)
    {
        hand->cardsHand[i]->flip();

    }

    for (int i = 0; i < 4; i++){
        playerturn(hand,1);
        playerturn(op,0);
    }
}

void PlayWindow::playerturn(Hand *playingHand,int isPlayerturn){

    scene->selectedCard=nullptr;
    selectcard(isPlayerturn);

    if(table->checkCard(scene->selectedCard)!=nullptr){

        lastcolledted = isPlayerturn;

        Card*foundCard = table->checkCard(scene->selectedCard);
        scene->selectedCard->setZValue(2);
        foundCard->setZValue(1);

        scene->selectedCard->startAnim(foundCard->pos(),500);


        table->freePos(foundCard->pos() + QPointF(foundCard->boundingRect().width()/2,foundCard->boundingRect().height()/2));
        playingHand->dropCard(scene->selectedCard);
        table->dropCard(foundCard);

        Hand *playerCollected = new Hand(scene);
        playerCollected->addCard(scene->selectedCard);
        playerCollected->addCard(foundCard);

        delay(600);


        delay(300);


        delay(350);

        for (int i=scene->selectedCard->getNumber()+1; i<10 ; i++)
        {
            if(table->cardsHand.size() == 0) break; //table is empty = no more cards to collect

            bool found=false;
            for(int j=0;j<table->cardsHand.size();j++)
            {
                if(table->cardsHand[j]->getNumber() == i){

                    found = true;
                    for (int k=0;k<playerCollected->cardsHand.size();k++) {
                        playerCollected->cardsHand[k]->setZValue(40-k);
                        playerCollected->cardsHand[k]->startAnim(table->cardsHand[j]->pos(),500);
                    }



                    table->cardsHand[j]->setZValue(40-playerCollected->cardsHand.size());
                    delay(600);
                    playerCollected->addCard(table->cardsHand[j]);
                    table->freePos(table->cardsHand[j]->pos() + QPointF(table->cardsHand[j]->boundingRect().width()/2,table->cardsHand[j]->boundingRect().height()/2));
                    table->dropCard(table->cardsHand[j]);

                    delay(1000);


                    break;
                }
            }
            if(!found) break;
        }

        if(isPlayerturn)
            for (int k=1;k<=playerCollected->cardsHand.size();k++) {
                playerCollected->cardsHand[k-1]->startAnim(QPointF(-x/3,y/2),600);

            }
        else
            for (int k=1;k<=playerCollected->cardsHand.size();k++) {
                playerCollected->cardsHand[k-1]->startAnim(QPointF(-x/3,-y*0.7 ),600);

            }

        lastcolledted = isPlayerturn;

        if(isPlayerturn) {
            playerScore->value += playerCollected->cardsHand.size();
        }
        else
            opScore->value += playerCollected->cardsHand.size();

        playerScore->updateScore();
        opScore->updateScore();


    }

    else {
        table->addCard(scene->selectedCard);
        playingHand->dropCard(scene->selectedCard);

        //animation to the free position in table
        scene->selectedCard->startAnim(table->emptyPos[0]+QPointF(-scene->selectedCard->boundingRect().width()/2,-scene->selectedCard->boundingRect().height()/2),500);



        table->fillPos(table->emptyPos[0]);

        delay(550);
    }
}

void PlayWindow::selectcard(int isPlayerturn)
{
    if(isPlayerturn){

        scene->waiting=true;

        while (scene->selectedCard==nullptr)
            QCoreApplication::processEvents(QEventLoop::AllEvents,10000);

        scene->waiting=false; //stop waiting for the player to pick a card
    }
    else{

        scene->selectedCard=nullptr;

        if(difficulty==0){
            srand(time(0));
            scene->selectedCard = op->cardsHand[rand() % op->cardsHand.size()];//select a random card
        }

        else if(difficulty == 1){

            for(int i=0;i<op->cardsHand.size();i++){
                bool isSelected = false;
                for(int j=0;j<table->cardsHand.size();j++){
                    if(op->cardsHand[i]->getNumber() == table->cardsHand[j]->getNumber())
                    {
                        scene->selectedCard = op->cardsHand[i];
                        isSelected = true;
                        break;
                    }
                }
                if(isSelected) break;

                srand(time(0));
                scene->selectedCard = op->cardsHand[rand() % op->cardsHand.size()];//select a random card
            }
        }

        scene->selectedCard->flip();
        delay(300);
    }
}
