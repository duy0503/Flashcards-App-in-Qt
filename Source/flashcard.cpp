#include "flashcard.h"
#include "ui_flashcard.h"
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QDialogButtonBox>
#include <QMessageBox>
#include "deck.h"

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
    keywordsButton->setText(keywords);
    keywordsButton->setFixedSize(432, 270);
    // QFont font = keywordsButton->font();
    // font.setPointSize(15);
    // keywordsButton->setFont(font);

    keywordsButton->setStyleSheet("font-size: 24pt; border-image: url(:/index.png);");
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

        /**
         * Update question, answer, and keywords if user modified them.
         * Then signal contextChanged() to let the Deck knows that it has been modified
         */
        bool isContextChanged = false;
        if (questionField->toPlainText() != this->getQuestion()) {
            this->setQuestion(questionField->toPlainText());
            isContextChanged = true;
        }

        if (answerField->toPlainText() != this->getAnswer()) {
            this->setAnswer(answerField->toPlainText());
            isContextChanged = true;
        }

        if (keywordsField->text() != this->getKeywords()) {
            this->setKeywords(keywordsField->text());
            isContextChanged = true;
        }

        if (isContextChanged) {
            emit contextChanged(true);
        }
    }
    this->show();
}

void Flashcard::on_deleteButton_clicked()
{
    int r = QMessageBox::warning(this, tr("Warning!"),
                                 tr("Are you sure you wish to delete this flashcard?"),
                                 QMessageBox::Ok | QMessageBox::Cancel);
    if (r == QMessageBox::Cancel)
    {
        return;
    }
    else if (r == QMessageBox::Ok)
    {
        delete this;
    }
}
