// rules.cpp
#include "rules.h"
#include "ui_rules.h"

Rules::Rules(QWidget *parent) : QWidget(parent), ui(new Ui::Rules)
{
    ui->setupUi(this);
    setWindowTitle("Ronda Beta V0.4");

    connect(ui->pushButton, &QPushButton::clicked, this, &Rules::on_pushButton_clicked);

    // Set the rules text
    setRulesText("RONDA:\n"
                 "Ronda is a popular card game in Morocco designed for 2 players. It uses a special deck of 40 cards with 4 suits (Clubs, Cups, Swords, Coins). The cards range from 1-7 and 10-12, where 7 is adjacent to 10. Cards with rank 8 and 9 are not used.\n"
                 "\n"
                 "Game Setup:\n"
                 "    - The dealer deals four cards to each player.\n"
                 "    - The objective is to capture cards during the game.\n"
                 "    - The player in front of the dealer starts each round.\n"
                 "\n"
                 "Gameplay:\n"
                 "    - Each turn involves playing one card face up to the table, possibly capturing some cards.\n"
                 "    - If your card matches a card on the table, you capture it, along with all higher cards in sequence. For example, playing a 6 with 6, 7, 10 captures 6, 7, 10.\n"
                 "    - Unmatched cards remain on the table for future turns.\n"
                 "    - After both players play four cards, the dealer deals another batch of four cards to each player.\n"
                 "    - The dealer continues dealing four cards until all undealt cards are used. The player with the highest score wins.\n");

    // Set the stylesheet for the QPushButton
    ui->pushButton->setStyleSheet("QPushButton {"
                                  "   color: white;"
                                  "   background-image: url(:/new/prefix1/images/button.png);"
                                  "   background-position: center;"
                                  "   background-repeat: no-repeat;"
                                  "   border: none;"
                                  "   padding: 15px 30px;"  // Adjust padding to control button size
                                  "   font-size: 18px;"     // Adjust font size if needed
                                  "}");
}

Rules::~Rules()
{
    delete ui;
}

void Rules::on_pushButton_clicked()
{
    this->close();
}

void Rules::setRulesText(const QString &rules)
{
    ui->textEdit->setPlainText(rules);
}
