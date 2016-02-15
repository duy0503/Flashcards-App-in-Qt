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
    QString getQuestion();              // getter function for question_.
    void setQuestion(QString question); // setter function for question_. Side effect: changes QuestionLabel
    QString getAnswer();                // getter gunction for answer_.
    void setAnswer(QString answer);     // setter function for answer_. Side effect: changes AnswerLabel
    QString getKeywords();
    void setKeywords(QString keywords);
    explicit Flashcard(QWidget *parent = 0);
    QPushButton *keywordsButton;  // Todo: Need to make this private
    ~Flashcard();

  private:
    QString question_;
    QString answer_;
    QString keywords_;
    Ui::Flashcard *ui;

private slots:
    void ShowCard();


} Flashcard;

#endif // FLASHCARD_H
