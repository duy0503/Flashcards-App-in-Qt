#include "flashcard.h"
#include "ui_flashcard.h"
#include <QDialog>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QDebug>
#include "deck.h"

Flashcard::Flashcard(QWidget *parent) :
    QWidget(parent),
    flashcardUi(new Ui::Flashcard){
    flashcardUi->setupUi(this);

    keywordsButton = new QPushButton(this);
    keywordsButton->setObjectName("keywordsButton");
    keywordsButton->setStyleSheet("#keywordsButton {border-image: url(:/index.png);}");

    QVBoxLayout* layout = new QVBoxLayout(keywordsButton);
    keywordsButton->setLayout(layout);

    keywordsLabel = new QLabel(keywordsButton);
    layout->addWidget(keywordsLabel);
    keywordsLabel->setObjectName("keywordsLabel");
    keywordsLabel->setStyleSheet("#keywordsLabel {font-size: 24pt;}");
    keywordsLabel->setWordWrap(true);
    keywordsLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}


Flashcard::~Flashcard(){

    delete keywordsButton;
    delete flashcardUi;
}

void Flashcard::on_editButton_clicked(){

    this->hide();

    // if question, or answer, or keywords gets modified
    if ( createFormToEditCard() == true){
        emit contextChanged(true);  // this will trigger function setDeckModified in deck.cpp
    }

    this->show();
}

void Flashcard::on_deleteButton_clicked(){

    int r = QMessageBox::warning(this, tr("Warning!"),
                                 tr("Are you sure you wish to delete this flashcard?"),
                                 QMessageBox::Ok | QMessageBox::Cancel);

    if (r == QMessageBox::Ok){
        // Trigger function deleteCardInDeck in deck.cpp to delete the card from deck
        emit deleteCard(this);
    }
}

QString Flashcard::getQuestion(){

    return question_;
}

void Flashcard::setQuestion(QString question){

    question_ = question;
    flashcardUi->QuestionLabel->setText(question);
}

QString Flashcard::getAnswer(){

    return answer_;
}

void Flashcard::setAnswer(QString answer){

    answer_ = answer;
    flashcardUi->AnswerLabel->setText(answer);
}

void Flashcard::setKeywords(QString keywords){

    keywords_ = keywords;
    this->setWindowTitle(keywords_);
    keywordsButton->setFixedSize(432, 270);
    keywordsLabel->setText(keywords);
    QObject::connect(keywordsButton, SIGNAL(clicked(bool)), this, SLOT(showCard()));
}

QString Flashcard::getKeywords(){

    return keywords_;
}

void Flashcard::setKeywordsList(const QStringList &list){

    keywordsList_ = list;
    QString keywords = "";
    for ( int index = 0; index < list.size()-1; index++){
        keywords.append(list[index]);
        keywords.append(", ");
    }
    keywords.append(list[list.size()-1]);
    setKeywords(keywords);
}

QStringList Flashcard::getKeywordsList(){

    return keywordsList_;
}

void Flashcard::updateKeywordsList(QString keywords){

    QStringList list = keywords.split(',', QString::KeepEmptyParts);
    keywordsList_.empty();
    foreach(QString keyword, list){
        keyword = keyword.trimmed();
        keywordsList_.append(keyword);
    }
}

void Flashcard::showCard(){

    this->show();
}

bool Flashcard::createFormToEditCard(){

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

    bool isContextChanged = false;
    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {

        /**
         * Update question, answer, and keywords if user modified them.
         */
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
            this->updateKeywordsList(keywordsField->text());
            isContextChanged = true;
        }

    }
    return isContextChanged;

}


