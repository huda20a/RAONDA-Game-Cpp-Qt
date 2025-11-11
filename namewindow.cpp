// namewindow.cpp

#include "namewindow.h"
#include "ui_namewindow.h"

QString NameWindow::name;

NameWindow::NameWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::NameWindow) {
    ui->setupUi(this);
    name = ui->user_name->toPlainText();
    setWindowTitle("RONDA GAME V0.1");

    ui->pushButton->setStyleSheet("QPushButton {"
                                  "   color: white;"
                                  "   border-image: url(:/new/prefix1/images/button.png) 5 15 5 15;"
                                  "   border-top: 5px transparent;"
                                  "   border-bottom: 5px transparent;"
                                  "   border-right: 15px transparent;"
                                  "   border-left: 15px transparent;"
                                  "   min-width: 150px;"
                                  "   min-height: 50px;"
                                  "}");

    ui->groupBox->setStyleSheet("QGroupBox {"
                                "   border: 2px solid gray;"
                                "   border-radius: 5px;"
                                "   margin-top: 20px;"
                                "   background-color: #ecf0f1;"
                                "   background-image: url(:/new/prefix1/images/backgroundname.png);"
                                "}");

    ui->groupBox->setTitle("");

    ui->label->setStyleSheet("QLabel { color: white; }");
}

NameWindow::~NameWindow() {
    delete ui;
}

void NameWindow::on_pushButton_clicked() {
    name = ui->user_name->toPlainText();

    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { background-color: lightblue; }"
                         "QMessageBox QLabel { color: black; }"
                         "QMessageBox QPushButton { color: white; background-color: blue; }");

    msgBox.about(this, " ", "Enjoy your game " + name + " ^_^");

    this->close();
    playwwindow = new PlayWindow;
    playwwindow->show();
    playwwindow->startgame();
}

