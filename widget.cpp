#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Démineur");
    generateComponent();
    manageComponent();
    manageLayout();
    manageEvent();
}

void Widget::activateOptionButton(){
    pbOption->setEnabled(true);
}

void Widget::generateComponent(){
    board = new Board;
    pbOption = new QPushButton("Option");
    hblLayout1 = new QHBoxLayout;
    hblLayout2 = new QHBoxLayout;
    vblLayout = new QVBoxLayout(this);
}

void Widget::manageComponent(){
    board->setHorizontalSize(10);
    board->setVerticalSize(10);
    board->setBombCount(10);
    board->runGame();
}

void Widget::manageEvent(){
    connect(pbOption, SIGNAL(clicked()), this, SLOT(runOptionWidget()));
}

void Widget::manageLayout(){
    vblLayout->addLayout(hblLayout1);
    hblLayout1->addStretch(50);
    hblLayout1->addWidget(board);
    hblLayout1->addStretch(50);
    vblLayout->addStretch(50);

    vblLayout->addLayout(hblLayout2);
    hblLayout2->addStretch(50);
    hblLayout2->addWidget(pbOption);
}

void Widget::runNewGame(int horizontalSquares, int verticalSquares, int bombCount){
    setEnabled(false);
    board->setVisible(false);
    board->setHorizontalSize(horizontalSquares);
    board->setVerticalSize(verticalSquares);
    board->setBombCount(bombCount);
    board->runGame();
    board->setVisible(true);
    setEnabled(true);
}

void Widget::runOptionWidget(){
    pbOption->setEnabled(false);

    OptionWidget *optionWidget = new OptionWidget;
    optionWidget->setHorizontalSquares(board->getHorizontalSize());
    optionWidget->setVerticalSquares(board->getVerticalSize());
    optionWidget->setBombCount(board->getBombCount());
    optionWidget->show();

    connect(optionWidget, SIGNAL(optionWidgetIsClosed()), this, SLOT(activateOptionButton()));
    connect(optionWidget, SIGNAL(newGameToRun(int,int,int)), this, SLOT(runNewGame(int, int, int)));
    connect(board, SIGNAL(newGameToRun(int,int,int)), this, SLOT(runNewGame(int, int, int)));
}
