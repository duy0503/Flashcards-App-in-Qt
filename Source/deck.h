#ifndef DECK_H
#define DECK_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QList>
#include <flashcard.h>

typedef struct Deck {
  public:
    QList<Flashcard*> deck_;            // A QList storing the deck. TODO: make this private
    QList<Flashcard*> newdeck;
    bool Open(const QString &fileName); // opens a deck from fileName and stores it in memory
    bool Save(const QString &fileName); // writes the deck to fileName
    void Clear();
} Deck;

#endif // DECK_H
