#include "board.h"

Board::Board(QWidget *parent) :
        QWidget(parent)
{
    initializeVariables();
    manageLayout();
    buildAllSquares();
}

int Board::getBombCount(){
    return bombCount;
}

int Board::getHorizontalSize(){
    return hSize;
}

int Board::getRandomNumber(){
    return (int) (qrand() * (totalSquareCount - 1) / RAND_MAX);
}

int Board::getVerticalSize(){
    return vSize;
}

bool Board::areNearSquares(Square *square1, Square *square2){
    int x1 = square1->getX();
    int y1 = square1->getY();

    int x2 = square2->getX();
    int y2 = square2->getY();

    int distanceX = x1 - x2;
    if (distanceX < 0)
        distanceX = -distanceX;

    int distanceY = y1 - y2;
    if (distanceY < 0)
        distanceY = -distanceY;

    return distanceX <= 1 && distanceY <= 1;
}

void Board::buildAllSquares(){
    for(int i = 0; i < MAX_HORIZONTAL_SIZE; i++){
        for(int j = 0; j < MAX_VERTICAL_SIZE; j++){
            Square *square = new Square;
            allSquares.append(square);
            connect(square, SIGNAL(bombExplosed()), this, SLOT(terminateGame()));
            connect(square, SIGNAL(notBombCliked()), this, SLOT(incrementeNotBomb()));
        }
    }
}

void Board::buildCurrentSquares(){
    int index = 0;
    for (int i = 0; i < hSize; i++){
        for (int j = 0; j < vSize; j++){
            Square *square = allSquares.at(index);
            square->clean();
            square->setX(i);
            square->setY(j);
            squares.append(square);
            index++;
        }
    }

    qsrand(time(NULL));
    for (int i = 0; i < totalSquareCount; i++){
        int rand1 = getRandomNumber();
        int rand2 = getRandomNumber();

        squares.swap(rand1, rand2);
    }

    QList<Square*> squaresBomb;
    for (int i = 0; i < bombCount; i++){
        Square *square = squares.at(i);
        square->setIsBomb(true);
        squaresBomb.append(square);
    }

    QList<Square*> squaresNotBomb;
    for (int i = bombCount; i < totalSquareCount; i++){
        Square *square = squares.at(i);
        squaresNotBomb.append(square);
    }

    int squaresNotBombSize = squaresNotBomb.size();
    for (int i = 0; i < bombCount; i++){
        Square *squareBomb = squaresBomb.at(i);
        int nearSquaresCount = 0;
        for (int j = 0; j < squaresNotBombSize; j++){
            Square *squareNotBomb = squaresNotBomb.at(j);
            if (areNearSquares(squareBomb, squareNotBomb)){
                squareNotBomb->incrementBombArround();
                nearSquaresCount++;
            }
            if (nearSquaresCount == 8)
                continue;
        }
    }
}

void Board::clearSquares(){
    notBombFound = 0;
    if (squares.isEmpty())
        return;

    int size = MAX_HORIZONTAL_SIZE * MAX_VERTICAL_SIZE;
    for (int i = 0; i < size; i++){
        Square *square = allSquares.at(i);
        square->setVisible(false);
    }

    squares.clear();
}

void Board::correctBombCount(){
    totalSquareCount = hSize * vSize;
    if (bombCount > totalSquareCount)
        bombCount = totalSquareCount;
}

void Board::displaySquares(){
    for (int i = 0; i < totalSquareCount; i++){
        Square *square = squares.at(i);
        int row = square->getY();
        int column = square->getX();
        glLayout->addWidget(square, row, column);
        square->setVisible(true);
    }
}

void Board::doGamerDecision(int response){
    if (response == QMessageBox::Yes)
        emit newGameToRun(hSize, vSize, bombCount);
    else
        showAllCasesContent();
}

bool Board::hasEnoughSquarePlace(){
    return hSize > 0 && vSize > 0;
}

void Board::initializeVariables(){
    congratulationMessage = "Félicitation, vous-avez gagner. :)\nVoulez-vous jouer de nouveau?";
    gameOverMessage = "Vous-avez perdu! :(\nVoulez-vous jouer de nouveau?";
    gameOverTitle = "Partie finie";

    hSize = 0;
    vSize = 0;
    bombCount = 0;
    notBombFound = 0;
}

void Board::incrementeNotBomb(){
    notBombFound++;
    if (totalSquareCount - notBombFound != bombCount)
        return;
    doGamerDecision(QMessageBox::information(this, gameOverTitle, congratulationMessage, QMessageBox::Yes, QMessageBox::No));
}

void Board::manageLayout(){
    glLayout = new QGridLayout(this);
    glLayout->setVerticalSpacing(0);
    glLayout->setHorizontalSpacing(0);
}

void Board::runGame(){
    clearSquares();
    correctBombCount();

    if (!hasEnoughSquarePlace())
        return;

    buildCurrentSquares();

    displaySquares();
}

void Board::setBombCount(int bombCount){
    this->bombCount = bombCount;
}

void Board::setHorizontalSize(int hSize){
    if (hSize > MAX_HORIZONTAL_SIZE)
        this->hSize = MAX_HORIZONTAL_SIZE;
    else if (hSize < 0)
        this->hSize = 0;
    else
        this->hSize = hSize;
}

void Board::setVerticalSize(int vSize){
    if (vSize > MAX_VERTICAL_SIZE)
        this->vSize = MAX_VERTICAL_SIZE;
    else if (vSize < 0)
        this->vSize = 0;
    else
        this->vSize = vSize;
}

void Board::showAllCasesContent(){
    for (int i = 0; i < totalSquareCount; i++){
        Square *square = squares.at(i);
        square->setIsBombExplosedToEmit(false);
        square->setIsNotBombToEmit(false);
        square->pressSquare();
    }
}

void Board::terminateGame(){
    doGamerDecision(QMessageBox::warning(this, gameOverTitle, gameOverMessage, QMessageBox::Yes, QMessageBox::No));
}

Board::~Board(){
    if (squares.isEmpty()) return;

    int size = squares.size();
    for (int i = 0; i < size; i++){
        Square *square = squares.at(i);
        if (square == NULL) continue;
        square->deleteLater();
    }
}
