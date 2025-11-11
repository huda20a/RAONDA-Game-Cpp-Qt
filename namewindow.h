// namewindow.h

#ifndef NAMEWINDOW_H
#define NAMEWINDOW_H

#include <QMainWindow>
#include "playwindow.h"
#include <QWidget>
#include <QString>
#include <QMessageBox>

namespace Ui {
class NameWindow;
}

class NameWindow : public QMainWindow {
    Q_OBJECT

public:
    // Constructor and Destructor
    explicit NameWindow(QWidget *parent = nullptr);
    ~NameWindow();

    // Static variable to store the entered name
    static QString name;

private slots:
    // Slot function for the button click
    void on_pushButton_clicked();

private:
    Ui::NameWindow *ui;
    PlayWindow *playwwindow;
};

#endif // NAMEWINDOW_H
