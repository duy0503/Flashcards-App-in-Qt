#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <QWidget>

namespace Ui {
class Flashcard;
}

typedef class Flashcard : public QWidget {
    Q_OBJECT

  public:
    QString GetQuestion();              // getter function for question_.
    void SetQuestion(QString question); // setter function for question_. Side effect: changes QuestionLabel
    QString GetAnswer();                // getter gunction for answer_.
    void SetAnswer(QString answer);     // setter function for answer_. Side effect: changes AnswerLabel
    explicit Flashcard(QWidget *parent = 0);
    ~Flashcard();

  private:
    QString question_;
    QString answer_;
    Ui::Flashcard *ui;
} Flashcard;

#endif // FLASHCARD_H
