#ifndef BOARD_H
#define BOARD_H

#include <cstdlib>
#include <ctime>
#include <QGridLayout>
#include <QList>
#include <QMessageBox>
#include <QWidget>

#include "square.h"

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = NULL);

    static const int MAX_HORIZONTAL_SIZE = 30;
    static const int MAX_VERTICAL_SIZE = 30;

    int getBombCount();
    int getHorizontalSize();
    int getVerticalSize();

    void runGame();
    void setBombCount(int bombCount);
    void setHorizontalSize(int hSize);
    void setVerticalSize(int vSize);

signals:
    void newGameToRun(int horizontalSquares, int verticalSquares, int bombCount);

private slots:
    void incrementeNotBomb();
    void terminateGame();

private:
    bool hasEnoughSquarePlace();

    int bombCount;
    int hSize;
    int notBombFound;
    int totalSquareCount;
    int vSize;

    QGridLayout *glLayout;

    QList<Square*> allSquares;
    QList<Square*> squares;

    QString congratulationMessage;
    QString gameOverMessage;
    QString gameOverTitle;

    bool areNearSquares(Square *square1, Square *square2);

    int countSquareBomb();
    int getRandomNumber();

    void buildAllSquares();
    void buildCurrentSquares();
    void clearSquares();
    void correctBombCount();
    void displaySquares();
    void doGamerDecision(int response);
    void initializeVariables();
    void manageLayout();
    void showAllCasesContent();
};

#endif // BOARD_H
