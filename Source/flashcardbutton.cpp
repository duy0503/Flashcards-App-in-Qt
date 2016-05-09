#include "flashcardbutton.h"
#include "ui_flashcardbutton.h"
#include <flashcard.h>

FlashcardButton::FlashcardButton(QPushButton *parent) :
    QPushButton(parent),
    ui(new Ui::FlashcardButton)
{
    ui->setupUi(this);
}

void FlashcardButton::setLabel(QString keyword) {
    ui->keywordsLabel->setText(keyword);
}

void FlashcardButton::setFlashcard(Flashcard* card){
    card_ = card;
}

void FlashcardButton::on_editButton_clicked()
{
    card_->createFormToEditCard();
}

void FlashcardButton::on_deleteButton_clicked()
{
    card_->createFormToDeleteCard();
}

FlashcardButton::~FlashcardButton()
{
    delete ui;
}
