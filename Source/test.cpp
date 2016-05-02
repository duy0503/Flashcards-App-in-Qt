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
    rightCards_ = 0;
    wrongCards_ = 0;
    ui->buttonWidget->setVisible(false);
    currentCard_ = testDeck_->deck_[ shuffledSequence_[currentSequenceIndex_] ];
    state_ = question;
    updateWindowTitle("Question ");

    flipAnimation.setParent(ui->cardWidget);
    flipAnimation.setTargetObject(ui->cardWidget);
    flipAnimation.setPropertyName("maximumSize");
    flipAnimation.setStartValue(QSize(800, 600));
    flipAnimation.setEndValue(QSize(0, 600));
    flipAnimation.setDuration(100);
    connect(&flipAnimation, SIGNAL(finished()), this, SLOT(animationFinished()) );
    updateCardAppearance();
}

void Test::updateCardAppearance() {
    if (state_ == question) {
        ui->cardWidget->setStyleSheet("#cardWidget {background-color: white; border-image: url(:/index.png)}");
        ui->promptLabel->setText(currentCard_->getQuestion());
    }
    else {
        ui->cardWidget->setStyleSheet("#cardWidget {background-color: white; border-image: none}");
        ui->promptLabel->setText(currentCard_->getAnswer());
    }
}

void Test::playFlipAnimation() {
    flipAnimation.setEasingCurve(QEasingCurve::OutCubic);
    flipAnimation.setDirection(QPropertyAnimation::Forward);
    ui->promptLabel->setVisible(false);
    ui->buttonWidget->setVisible(false);
    flipAnimation.start();
}

void Test::animationFinished() {
    if (flipAnimation.direction() == QPropertyAnimation::Forward) {
        flipAnimation.setEasingCurve(QEasingCurve::InCubic);
        flipAnimation.setDirection(QPropertyAnimation::Backward);
        updateCardAppearance();
        flipAnimation.start();
    }
    else if (flipAnimation.direction() == QPropertyAnimation::Backward) {
        ui->promptLabel->setVisible(true);
        if (state_ == question) {
            ui->buttonWidget->setVisible(false);
        }
        else {
            ui->buttonWidget->setVisible(true);
        }
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
        emit testFinished();
    }

    emit progressUpdate();
}

void Test::mousePressEvent(QMouseEvent* event) {
    if (state_ == question) {
        advanceTest();
    }
    else { // if (state_ == answer) // must click one of the two buttons to advance
        return;
    }
}

void Test::on_rightButton_clicked() {
    rightCards_++;
    advanceTest();
}

void Test::on_wrongButton_clicked() {
    wrongCards_++;
    advanceTest();
}

void Test::updateWindowTitle(QString title) {
    this->setWindowTitle(title + QString::number(currentSequenceIndex_+1));
}
