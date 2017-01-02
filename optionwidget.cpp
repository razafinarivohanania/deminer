#include "optionwidget.h"

OptionWidget::OptionWidget(QWidget *parent) :
    QWidget(parent)
{
    generateComponent();
    manageComponent();
    manageLayout();
    manageEvent();
    customizeWindow();
}

int OptionWidget::getBombCount(){
    return sbBombCount->value();
}

int OptionWidget::getHorizontalSquares(){
    return sbHorizontalSquares->value();
}

int OptionWidget::getVerticalSquares(){
    return sbVerticalSquares->value();
}

void OptionWidget::closeEvent(QCloseEvent *event){
    emit optionWidgetIsClosed();
    event->accept();
}

void OptionWidget::customizeWindow(){
    setWindowFlags(Qt::Tool | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Option");
}

void OptionWidget::generateComponent(){
    sbHorizontalSquares = new QSpinBox;
    sbVerticalSquares = new QSpinBox;
    sbBombCount = new QSpinBox;

    pbNewGame = new QPushButton("Nouveau jeux");
    pbCancel = new QPushButton("Annuler");

    flLayout = new QFormLayout;
    hblLayout = new QHBoxLayout;
    vblLayout = new QVBoxLayout(this);
}

void OptionWidget::manageComponent(){
    sbHorizontalSquares->setMinimum(1);
    sbHorizontalSquares->setMaximum(Board::MAX_HORIZONTAL_SIZE);

    sbVerticalSquares->setMinimum(1);
    sbVerticalSquares->setMaximum(Board::MAX_HORIZONTAL_SIZE);

    sbBombCount->setMinimum(1);
    sbBombCount->setMaximum(Board::MAX_HORIZONTAL_SIZE * Board::MAX_HORIZONTAL_SIZE);
}

void OptionWidget::manageEvent(){
    connect(pbCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(pbNewGame, SIGNAL(clicked()), this, SLOT(runNewGame()));
}

void OptionWidget::manageLayout(){
    vblLayout->addLayout(flLayout);

    flLayout->addRow("Cases horizontales", sbHorizontalSquares);
    flLayout->addRow("Cases verticales", sbVerticalSquares);
    flLayout->addRow("Nombre de bombes", sbBombCount);

    vblLayout->addLayout(hblLayout);

    hblLayout->addWidget(pbNewGame);
    hblLayout->addWidget(pbCancel);
}

void OptionWidget::runNewGame(){
    setEnabled(false);
    emit newGameToRun(sbHorizontalSquares->value(), sbVerticalSquares->value(), sbBombCount->value());
    close();
}

void OptionWidget::setBombCount(int bombCount){
    sbBombCount->setValue(bombCount);
}

void OptionWidget::setHorizontalSquares(int size){
    sbHorizontalSquares->setValue(size);
}

void OptionWidget::setVerticalSquares(int size){
    sbVerticalSquares->setValue(size);
}
