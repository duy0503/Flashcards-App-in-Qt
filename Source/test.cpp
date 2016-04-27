#include "test.h"
#include "ui_test.h"
#include <algorithm>
#include <QDebug>
#include <QEasingCurve>


Test::Test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);
}

void Test::setDeck(Deck* deck) {
    testDeck_ = deck;
    shuffledSequence_.clear();
    return;
}

Test::~Test()
{
    delete ui;
}

void Test::startTest() {
    // Populates the list with integers of 0 to <size of deck>
    for (int i = 0; i < testDeck_->deck_.length(); i++) {
        shuffledSequence_.append(i);
    }
    // Randomizes the elements of the list. This will be the shuffled order of the cards.
    std::random_shuffle(shuffledSequence_.begin(), shuffledSequence_.end());

    currentSequenceIndex_ = 0;
    currentCard_ = testDeck_->deck_[ shuffledSequence_[currentSequenceIndex_] ];
    state_ = question;
    updateWindowTitle("Question ");

    flipAnimation.setParent(ui->cardWidget);
    flipAnimation.setTargetObject(ui->cardWidget);
    flipAnimation.setPropertyName("maximumSize");
    flipAnimation.setStartValue(QSize(800, 600));
    flipAnimation.setEndValue(QSize(0, 600));
    flipAnimation.setDuration(250);
    connect(&flipAnimation, SIGNAL(finished()), this, SLOT(animationFinished()) );
    updatePromptLabel();

}

void Test::updatePromptLabel() {
    if (state_ == question) {
        ui->promptLabel->setStyleSheet("QWidget {background-color: white; border-image: url(:/index.png)}");
        ui->promptLabel->setText(currentCard_->getQuestion());
    } else {
        ui->promptLabel->setStyleSheet("QWidget {background-color: white; border-image: none}");
        ui->promptLabel->setText(currentCard_->getAnswer());
    }
}

void Test::playFlipAnimation() {
    flipAnimation.setEasingCurve(QEasingCurve::OutCubic);
    flipAnimation.setDirection(QPropertyAnimation::Forward);
    flipAnimation.start();
}

void Test::animationFinished() {
    if (flipAnimation.direction() == QPropertyAnimation::Forward) {
        flipAnimation.setEasingCurve(QEasingCurve::InCubic);
        flipAnimation.setDirection(QPropertyAnimation::Backward);
        updatePromptLabel();
        flipAnimation.start();
    }
}

void Test::advanceTest() {
    if (state_ == question) {
        state_ = answer;
        playFlipAnimation();
        updateWindowTitle("Answer ");
    }
    else if (state_ == answer && currentSequenceIndex_ < shuffledSequence_.length()-1) {
        currentSequenceIndex_++;
        state_ = question;
        currentCard_ = testDeck_->deck_[ shuffledSequence_[currentSequenceIndex_] ];
        playFlipAnimation();
        updateWindowTitle("Question ");
    }
    else {
        close();
        emit testFinished();
    }
}

void Test::mousePressEvent(QMouseEvent* event) {
    advanceTest();
}
void Test::updateWindowTitle(QString title){
    this->setWindowTitle(title + QString::number(currentSequenceIndex_ + 1));
}
