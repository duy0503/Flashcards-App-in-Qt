#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <ui_flashcard.h>
#include "deck.h"

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
