#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include "deck.h"
#include "hand.h"
#include "scene.h"
#include "table.h"
#include "score.h"
#include "info.h"


namespace Ui {
class PlayWindow;
}

class PlayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PlayWindow(QWidget *parent = nullptr);
    ~PlayWindow();
    void startgame();
    void round(Deck *deck, Hand *hand, Hand *op);
    void playerturn(Hand *playingHand, int isPlayerturn);
    void selectcard(int isPlayerturn);
    int x;
    int y;
    int difficulty;
    int lastcolledted;
    bool muted;


private:
    Ui::PlayWindow *ui;
    Scene *scene;
    Deck *deck;
    Hand *hand;
    Hand *op;
    Table *table;
    Score *playerScore;
    Score *opScore;
    Info *gameoverText;

};

#endif // PLAYWINDOW_H
