#ifndef DECK1_H
#define DECK1_H

#include <QFile>        // QFile
#include <QTextStream>  // QTextStream
#include <QString>      // QString
#include <QList>        // QList
#include <QObject>
#include <flashcard.h>  // Flashcard class

class Deck : public QObject
{
    Q_OBJECT
public:
    explicit Deck(QObject *parent = 0);
    /**
     * @brief A QList which stores pointers to Flashcards.
     * @todo Make this private.
     */
    QList<Flashcard*> deck_;

    /**
     * @brief Unused.
     */
    //QList<Flashcard*> newdeck;

    bool isDeckModified();
    /**
     * @brief Opens a deck from fileName and stores it in deck_.
     * @param fileName is a QString that points toward the location of the file.
     * @return A bool that is true if the operation is successful, or false otherwise.
     */
    bool Open(const QString &fileName); // Opens a deck from fileName and stores it in memory

    /**
     * @brief Saves the contents of deck_ into a file called fileName.
     * @param fileName is a QString that points towards the location of the file.
     * @return A bool that is true if the operation is successful, or false otherwise.
     */
    bool Save(const QString &fileName); // writes the deck to fileName

    /**
     * @brief Clears the deck_ of all its contents.
     */
    void Clear();

private:
    bool deckModified_;
signals:

public slots:
    void setDeckModified();
};

#endif // DECK1_H
