#include "square.h"

Square::Square(QWidget *parent){
    customizeSquare(parent);
    initializeVariables();
}

bool Square::getIsBomb(){
    return isBomb;
}

int Square::getBombArroundCount(){
    return bombCountArround;
}

int Square::getX(){
    return x;
}

int Square::getY(){
    return y;
}

void Square::clean(){
    setText("");
    bombCountArround = 0;
    isBomb = false;
    isBombExplosedToEmit = true;
    isNotBombToEmit = true;
    setStyleSheet(cssInitialSquare);
    isChecked = false;
}

void Square::customizeSquare(QWidget *parent){
    setParent(parent);
    setFixedHeight(20);
    setFixedWidth(20);

    setAlignment(Qt::AlignHCenter);
}

void Square::incrementBombArround(){
    bombCountArround++;
}

void Square::initializeVariables(){
    colorsNumber.append("rgb(64, 80, 190)");
    colorsNumber.append("rgb(30, 103, 1)");
    colorsNumber.append("rgb(170, 19, 23)");
    colorsNumber.append("rgb(9, 8, 129)");
    colorsNumber.append("rgb(120, 3, 1)");
    colorsNumber.append("rgb(4, 122, 24)");
    colorsNumber.append("rgb(170, 6, 3)");
    colorsNumber.append("rgb(173, 70, 79)");

    cssBombExplosed = "background-color:rgb(222, 16, 35); font-weight:bold";
    cssBombNotExplosed = "background-color:rgb(100, 100, 100); font-weight:bold; text-align:center";
    cssInitialSquare = "background-color:rgb(76, 96, 202); border-width:1px; border-color:rgb(45, 60, 143); border-style:outset";
    cssChecked1 = "background-color:rgb(240, 240, 240); color:";
    cssChecked2 = "; font-weight:bold; border-width:1px; border-color:rgb(160, 160, 160); border-style:inset";
    defaultTextColor = "black";

    clean();
}

void Square::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton){
        updateFlag();
    } else if (event->button() == Qt::LeftButton){
        pressSquare();
    }
    event->accept();
}

void Square::pressSquare(){
    if (isChecked) return;
    if (text().size() != 0) return;

    setChecked(true);

    if (isBomb){
        setText("@");

        if (isBombExplosedToEmit){
            setStyleSheet(cssBombExplosed);
            emit bombExplosed();
        } else
            setStyleSheet(cssBombNotExplosed);

        return;
    }

    QString color = defaultTextColor;
    if (bombCountArround > 0 && bombCountArround < 9)
        color = colorsNumber.at(bombCountArround - 1);

    setStyleSheet(cssChecked1 + color + cssChecked2);

    if (bombCountArround == 0)
        setText("");
    else {
        QVariant number = bombCountArround;
        setText(number.toString());
    }

    if (isNotBombToEmit)
        emit notBombCliked();
}

void Square::setChecked(bool isChecked){
    this->isChecked = isChecked;
}

void Square::setIsBomb(bool isBomb){
    this->isBomb = isBomb;
}

void Square::setIsBombExplosedToEmit(bool toEmit){
    isBombExplosedToEmit = toEmit;
}

void Square::setIsNotBombToEmit(bool toEmit){
    isNotBombToEmit = toEmit;
}

void Square::setX(int x){
    this->x = x;
}

void Square::setY(int y){
    this->y = y;
}

void Square::showContent(){
    if (isBomb){
        setText("");
        return;
    }

    if (bombCountArround > 0){
        QVariant variant = bombCountArround;
        setText(variant.toString());
        return;
    }

    setText("");
}

void Square::updateFlag(){
    if (isChecked) return;

    QString value = text();
    if (value == "l"){
        setText("?");
    } else if (value == "?"){
        setText("");
    } else {
        setText("l");
    }
}
