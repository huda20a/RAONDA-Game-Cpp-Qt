
// #ifndef RULES_H
// #define RULES_H

// #include <QString>
// #include <QWidget>
// #include <QGraphicsScene>

// namespace Ui {
// class Rules;
// }

// class Rules : public QWidget
// {
//     Q_OBJECT

// public:
//     explicit Rules(QWidget *parent = nullptr);
//     ~Rules();

//     // Function to set rules text
//     void setRulesText(const QString &rules);

// private slots:
//     void on_pushButton_clicked();

// private:
//     Ui::Rules *ui;
// };

// #endif // RULES_H

// rules.h
#ifndef RULES_H
#define RULES_H

#include <QString>
#include <QWidget>
#include <QGraphicsScene>

namespace Ui {
class Rules;
}

class Rules : public QWidget
{
    Q_OBJECT

public:
    explicit Rules(QWidget *parent = nullptr);
    ~Rules();

    // Function to set rules text
    void setRulesText(const QString &rules);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Rules *ui;
};

#endif // RULES_H

