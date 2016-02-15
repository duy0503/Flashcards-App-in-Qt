#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <QWidget>
#include <QPushButton>

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
    QString GetKeywords();
    void SetKeywords(QString keywords);
    explicit Flashcard(QWidget *parent = 0);
    ~Flashcard();
    QPushButton *button;


  private:
    QString question_;
    QString answer_;
    QString keywords_;
    Ui::Flashcard *ui;
private slots:
    void ShowCard();


} Flashcard;

#endif // FLASHCARD_H
