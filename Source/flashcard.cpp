#include "flashcard.h"
#include "ui_flashcard.h"

QString Flashcard::GetQuestion() {
    return question_;
}

void Flashcard::SetQuestion(QString question) {
    question_ = question;
    ui->QuestionLabel->setText(question);
}

QString Flashcard::GetAnswer() {
    return answer_;
}

void Flashcard::SetAnswer(QString answer) {
    answer_ = answer;
    ui->AnswerLabel->setText(answer);
}

Flashcard::Flashcard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Flashcard)
{
    ui->setupUi(this);
}

Flashcard::~Flashcard()
{
    //delete ui;
}
