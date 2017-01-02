#ifndef WIDGET_H
#define WIDGET_H

#include <QHBoxLayout>
#include <QtGui/QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "board.h"
#include "optionwidget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);

private slots:
    void activateOptionButton();
    void runNewGame(int horizontalSquares, int verticalSquares, int bombCount);
    void runOptionWidget();

private:
    Board *board;

    QPushButton *pbOption;

    QHBoxLayout *hblLayout1;
    QHBoxLayout *hblLayout2;
    QVBoxLayout *vblLayout;

    void generateComponent();
    void manageComponent();
    void manageEvent();
    void manageLayout();
};

#endif // WIDGET_H
