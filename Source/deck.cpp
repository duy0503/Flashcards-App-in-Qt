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
#include <QDebug>
#include <QRegExp>
#include "flashcard.h"

Deck::Deck(QObject *parent) : QObject(parent){
    deckModified_ = false;
}

bool Deck::Open(const QString &fileName){

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)){
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

        // get keywords
        QJsonArray keywords = obj["keywords"].toArray();
        QStringList keywordsList;
        for (int index = 0; index < keywords.size(); ++index){
            keywordsList.append(keywords[index].toString());
        }
        newcard->setKeywordsList(keywordsList);
        newcard->setQuestion(obj["question"].toString());
        newcard->setAnswer(obj["answer"].toString());    
        QObject::connect(newcard, SIGNAL(contextChanged(bool)), this, SLOT(setDeckModified(bool)));
        QObject::connect(newcard, SIGNAL(deleteCard(Flashcard*)), this, SLOT(deleteCardInDeck(Flashcard*)));

    }
    setDeckModified(false);
    return true;
}

bool Deck::Save(const QString &fileName){

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)){
        return false;
    }

    QJsonArray cardsList;
    foreach(Flashcard *card, deck_)
    {
        QJsonObject obj;
        QJsonArray keywords;
        QStringList keywordsList = card->getKeywordsList();
        foreach(QString keyword, keywordsList){
            keywords.append(keyword);
        }

        obj["question"] = card->getQuestion();
        obj["answer"] = card->getAnswer();
        obj["keywords"] = keywords;
        cardsList.append(obj);
    }
    QJsonObject deckObj;
    deckObj["Deck"] = cardsList;
    QJsonDocument saveDeck(deckObj);
    file.write(saveDeck.toJson());
    file.close();
    setDeckModified(false);
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

void Deck::setDeckModified(bool modified){

    deckModified_ = modified;
}

void Deck::addNewCard(){

    Flashcard* newcard = new Flashcard;
    newcard->setKeywords("");

    // if a new card is created
    if ( newcard->createFormToEditCard() == true ){
        deck_.append(newcard);
        QObject::connect(newcard, SIGNAL(deleteCard(Flashcard*)), this, SLOT(deleteCardInDeck(Flashcard*)));
        QObject::connect(newcard, SIGNAL(contextChanged(bool)), this, SLOT(setDeckModified(bool)));
        setDeckModified(true);
    }

}

void Deck::runSearchFeature(QString key){
    if ( key != ""){
        foreach(Flashcard* card, deck_){
            card->keywordsButton->hide();
            QStringList keywords = card->getKeywordsList();
            QString full = keywords.join(" ");
            QRegExp matcher = QRegExp(key, Qt::CaseInsensitive);
            if (matcher.indexIn(full) > -1) {
                  card->keywordsButton->show();
            }
        }
    }
    else showAllCards();
}

void Deck::showAllCards(){

    foreach(Flashcard* card, deck_){
        card->keywordsButton->show();
    }
}

void Deck::deleteCardInDeck(Flashcard *card){

    // Remove the card from deck_
    deck_.removeOne(card);
    delete card;

    // Update the display after the card is deleted
    emit updateDisplayAfterDeletingCard();

    // Let the deck know that it has been modified
    setDeckModified(true);
}
