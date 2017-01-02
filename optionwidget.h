#ifndef OPTIONWIDGET_H
#define OPTIONWIDGET_H

#include <QCloseEvent>
#include <QFormLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

#include "board.h"

class OptionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OptionWidget(QWidget *parent = NULL);

    int getBombCount();
    int getHorizontalSquares();
    int getVerticalSquares();

    void setBombCount(int bombCount);
    void setHorizontalSquares(int size);
    void setVerticalSquares(int size);

signals:
    void newGameToRun(int horizontalSquares, int verticalSquares, int bombCount);
    void optionWidgetIsClosed();

private slots:
    void runNewGame();

private:
    QPushButton *pbCancel;
    QPushButton *pbNewGame;

    QSpinBox *sbBombCount;
    QSpinBox *sbHorizontalSquares;
    QSpinBox *sbVerticalSquares;

    QFormLayout *flLayout;
    QHBoxLayout *hblLayout;
    QVBoxLayout *vblLayout;

    void customizeWindow();
    void generateComponent();
    void manageComponent();
    void manageEvent();
    void manageLayout();

    virtual void closeEvent(QCloseEvent *event);
};

#endif // OPTIONWIDGET_H
