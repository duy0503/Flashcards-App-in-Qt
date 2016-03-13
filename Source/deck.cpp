#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <ui_flashcard.h>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QDialogButtonBox>
#include "deck.h"
#include "flashcard.h"

Deck::Deck(QObject *parent) : QObject(parent){
    deckModified_ = false;
}

bool Deck::Open(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    Clear();

    // Read the file and parse it
    QString saveData = (QString)file.readAll();
    QJsonDocument loadData = QJsonDocument::fromJson(saveData.toUtf8());
    QJsonObject newDeck = loadData.object();
    QJsonArray cards = newDeck["Deck"].toArray();

    foreach(const QJsonValue &card, cards)
    {
        QJsonObject obj = card.toObject();
        Flashcard* newcard = new Flashcard;
        deck_.append(newcard);

        newcard->setQuestion(obj["question"].toString());
        newcard->setAnswer(obj["answer"].toString());
        newcard->setKeywords(obj["keywords"].toString());
        QObject::connect(newcard, SIGNAL(contextChanged()), this, SLOT(setDeckModified()));

    }
    deckModified_ = false;
    return true;
}

void Deck::Clear(){

    foreach(Flashcard *card, deck_)
    {
        delete card;
    }
    deck_.clear();
}

bool Deck::isDeckModified(){
    return deckModified_;
}


bool Deck::Save(const QString &fileName) {

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QJsonArray cardsList;
    foreach(Flashcard *card, deck_)
    {
        QJsonObject obj;
        obj["question"] = card->getQuestion();
        obj["answer"] = card->getAnswer();
        obj["keywords"] = card->getKeywords();
        cardsList.append(obj);
    }
    QJsonObject deckObj;
    deckObj["Deck"] = cardsList;
    QJsonDocument saveDeck(deckObj);
    file.write(saveDeck.toJson());
    file.close();
    deckModified_ = false;
    return true;
}

void Deck::setDeckModified(){
    deckModified_ = true;
}
void Deck::addnewcard(){

    Flashcard* newcard = new Flashcard;
    newcard->setKeywords("");


    QDialog dialog(newcard);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("Question"));
    QPlainTextEdit* questionField = new QPlainTextEdit();
    form.addRow(questionField);

    form.addRow(new QLabel("Answer"));
    QPlainTextEdit* answerField = new QPlainTextEdit();
    form.addRow(answerField);

    form.addRow(new QLabel("Keywords"));
    QLineEdit* keywordsField = new QLineEdit();
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
         * Update question, answer, and keywords
         * Then add the new card to deck and set deckModified_ to true
         */
        bool isContextChanged = false;
        if (questionField->toPlainText() != newcard->getQuestion()) {
            newcard->setQuestion(questionField->toPlainText());
            isContextChanged = true;
        }

        if (answerField->toPlainText() != newcard->getAnswer()) {
            newcard->setAnswer(answerField->toPlainText());
            isContextChanged = true;
        }

        if (keywordsField->text() != newcard->getKeywords()) {
            newcard->setKeywords(keywordsField->text());
            isContextChanged = true;
        }

        if ( isContextChanged ){
            deck_.push_front(newcard);
            deckModified_ = true;
        }

    }
}
