#ifndef CARDDISPLAY_H
#define CARDDISPLAY_H

#include <QWidget>
#include <QLayout>
#include <flashcard.h>
#include <deck.h>
#include <QResizeEvent>

typedef class CardDisplay {
  private:
    int columns_;           // the number of columns of flashcards the window can fit. TODO: implement
    Deck* deck_;            // the deck to be displayed
    QWidget* display_;      // the widget where the cards are displayed
    QGridLayout* layout_;   // the grid layout

  public:
    void Set(QWidget* display, Deck* deck); // setter function for card display. side effect: makes layout_. Update() should be called immediately after.
    void Update();                          // updates how the cards look
    void SetColumns(int c);                 // setter function for columns. TODO: implement
} CardDisplay;

#endif // CARDDISPLAY_H
