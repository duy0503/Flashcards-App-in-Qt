#include "flashcard.h"
#include "ui_flashcard.h"

QString Flashcard::getQuestion() {
    return question_;
}

void Flashcard::setQuestion(QString question) {
    question_ = question;
    ui->QuestionLabel->setText(question);
}

QString Flashcard::getAnswer() {
    return answer_;
}

void Flashcard::setAnswer(QString answer) {
    answer_ = answer;
    ui->AnswerLabel->setText(answer);
}

void Flashcard::setKeywords(QString keywords){
    keywords_ = keywords;
    keywordsButton->setMinimumWidth(300);
    keywordsButton->setMinimumHeight(100);
    keywordsButton->setText(keywords);
    QFont font = keywordsButton->font();
    font.setPointSize(12);
    keywordsButton->setFont(font);
    keywordsButton->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffff99, stop: 1 #ffff00)");
    QObject::connect(keywordsButton, SIGNAL(clicked(bool)), this, SLOT(ShowCard()));
}

QString Flashcard::getKeywords(){
    return keywords_;
}


Flashcard::Flashcard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Flashcard)
{
    ui->setupUi(this);
    keywordsButton = new QPushButton(this);
}

Flashcard::~Flashcard()
{
    //delete ui;
}

void Flashcard::ShowCard()
{
    this->show();
}
