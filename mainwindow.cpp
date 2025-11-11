// mainwindow.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("RONDA GAME V0.1");

    this->setStyleSheet("QPushButton {"
                        "   color: white;"
                        "   border-image: url(:/new/prefix1/images/button.png) 5 15 5 15;"
                        "   border-top: 5px transparent;"
                        "   border-bottom: 5px transparent;"
                        "   border-right: 15px transparent;"
                        "   border-left: 15px transparent;"
                        "   min-width: 150px;"
                        "   min-height: 50px;"
                        "}");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_1_clicked() {
    namewindow = new NameWindow();
    namewindow->show();
    this->hide();
}

void MainWindow::on_pushButton_2_clicked() {
    rules = new Rules();
    rules->show();
}

void MainWindow::on_pushButton_3_clicked() {

}

