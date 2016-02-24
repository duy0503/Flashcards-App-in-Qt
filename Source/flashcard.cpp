#include "flashcard.h"
#include "ui_flashcard.h"
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QDialogButtonBox>
QString Flashcard::getQuestion() {
    return question_;
}

void Flashcard::setQuestion(QString question) {
    question_ = question;
    flashcardUi->QuestionLabel->setText(question);
}

QString Flashcard::getAnswer() {
    return answer_;
}

void Flashcard::setAnswer(QString answer) {
    answer_ = answer;
    flashcardUi->AnswerLabel->setText(answer);
}

void Flashcard::setKeywords(QString keywords){
    keywords_ = keywords;
    this->setWindowTitle(keywords_);
    keywordsButton->setMinimumWidth(200);
    keywordsButton->setMinimumHeight(100);
    keywordsButton->setText(keywords);
    QFont font = keywordsButton->font();
    font.setPointSize(15);
    keywordsButton->setFont(font);
    keywordsButton->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffff99, stop: 1 #ffff00)");
    QObject::connect(keywordsButton, SIGNAL(clicked(bool)), this, SLOT(showCard()));
}

QString Flashcard::getKeywords(){
    return keywords_;
}


Flashcard::Flashcard(QWidget *parent) :
    QWidget(parent),
    flashcardUi(new Ui::Flashcard)
{
    flashcardUi->setupUi(this);
    keywordsButton = new QPushButton(this);
}

Flashcard::~Flashcard() {
    delete keywordsButton;
    delete flashcardUi;
}

void Flashcard::showCard() {
    this->show();
}


void Flashcard::on_editButton_clicked() {

    this->hide();
    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("Question"));
    QPlainTextEdit* questionField = new QPlainTextEdit(question_);
    form.addRow(questionField);

    form.addRow(new QLabel("Answer"));
    QPlainTextEdit* answerField = new QPlainTextEdit(answer_);
    form.addRow(answerField);

    form.addRow(new QLabel("Keywords"));
    QLineEdit* keywordsField = new QLineEdit(keywords_);
    form.addRow(keywordsField);



    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        this->setQuestion(questionField->toPlainText());
        this->setAnswer(answerField->toPlainText());
        this->setKeywords(keywordsField->text());
    }
    this->show();
}
