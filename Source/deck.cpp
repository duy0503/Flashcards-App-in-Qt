#include <deck.h>

bool Deck::Open(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QTextStream in(&file);
    Clear();
    while(!in.atEnd()){
        Flashcard* newcard = new Flashcard;
        deck_.append(newcard);

        QString question = in.readLine();
        newcard->setQuestion(question);

        QString answer = in.readLine();
        newcard->setAnswer(answer);

        QString keywords = in.readLine();
        newcard->setKeywords(keywords);
    }
    return true;
}

void Deck::Clear()
{
    foreach(Flashcard *card, deck_)
    {
        delete card;
    }
    deck_.clear();
}

/* TODO: Implement Save
bool Deck::Save(const QString &fileName) {
}
*/

