#ifndef SQUARE_H
#define SQUARE_H

#include <QLabel>
#include <QVariant>
#include <QMouseEvent>
#include <QStringList>
#include <QWidget>

class Square : public QLabel
{
    Q_OBJECT

public:
    explicit Square(QWidget *parent = NULL);

    bool getIsBomb();

    int getBombArroundCount();
    int getX();
    int getY();

    void clean();
    void incrementBombArround();
    void setIsBomb(bool isBomb);
    void setIsBombExplosedToEmit(bool toEmit);
    void setIsNotBombToEmit(bool toEmit);
    void setX(int x);
    void setY(int y);
    void showContent();

signals:
    void bombExplosed();
    void notBombCliked();

public slots:
    void pressSquare();

private:
    bool isBomb;
    bool isBombExplosedToEmit;
    bool isChecked;
    bool isNotBombToEmit;

    int bombCountArround;
    int x;
    int y;

    QString cssBombExplosed;
    QString cssBombNotExplosed;
    QString cssChecked1;
    QString cssChecked2;
    QString cssInitialSquare;
    QString defaultTextColor;

    QStringList colorsNumber;

    void customizeSquare(QWidget *parent);
    void initializeVariables();
    void setChecked(bool isChecked);
    void updateFlag();

    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // SQUARE_H
