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

void Flashcard::SetKeywords(QString keywords){
    keywords_ = keywords;
    button->setMinimumWidth(300);
    button->setMinimumHeight(100);
    button->setText(keywords);
    QFont font = button->font();
    font.setPointSize(12);
    button->setFont(font);
    button->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffff99, stop: 1 #ffff00)");
    QObject::connect(button, SIGNAL(clicked(bool)), this, SLOT(ShowCard()));
}

QString Flashcard::GetKeywords(){
    return keywords_;
}

Flashcard::Flashcard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Flashcard)
{
    ui->setupUi(this);
    button = new QPushButton(this);
}

Flashcard::~Flashcard()
{
    //delete ui;
}

void Flashcard::ShowCard()
{
    this->show();
}
