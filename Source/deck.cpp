#include <deck.h>

bool Deck::Open(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QTextStream in(&file);
    while(!in.atEnd()){
        Flashcard* newcard = new Flashcard;
        deck_.append(newcard);

        QString question = in.readLine();
        newcard->SetQuestion(question);

        QString answer = in.readLine();
        newcard->SetAnswer(answer);
    }
    return true;
}

/* TODO: Implement Save
bool Deck::Save(const QString &fileName) {
}
*/

