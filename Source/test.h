#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <deck.h>
#include <flashcard.h>
#include <QList>
#include <QMouseEvent>
#include <QPropertyAnimation>

enum viewState{
    question,
    answer
};

namespace Ui {
class Test;
}

typedef class Test : public QWidget
{
    Q_OBJECT

public:
    Deck *testDeck_;
    Flashcard* currentCard_;
    QList<int> shuffledSequence_;
    int currentSequenceIndex_;
    int rightCards_;
    int wrongCards_;
    viewState state_;
    QPropertyAnimation flipAnimation;
    QPropertyAnimation slideAnimation;

    explicit Test(QWidget *parent = 0);
    void setDeck(Deck* deck);
    void startTest();
    void advanceTest();
    void updateCardAppearance();
    void playFlipAnimation();
    void updateWindowTitle(QString title);
    ~Test();

    void mousePressEvent(QMouseEvent* event);

private:
    Ui::Test *ui;

signals:
    void progressUpdate();
    void testFinished();
private slots:
    void animationFinished();
    void on_rightButton_clicked();
    void on_wrongButton_clicked();
} Test;

#endif // TEST_H
