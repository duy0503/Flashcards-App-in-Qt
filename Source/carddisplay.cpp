#include <carddisplay.h>

void CardDisplay::Set(QWidget* display, Deck* deck) {
    display_ = display;
    deck_ = deck;
    layout_ = new QGridLayout(display);
}

void CardDisplay::Update() {
    int pos = 0;
    Flashcard* card;
    foreach (card, deck_->deck_) { // confusing, will need to be refactored
        layout_->addWidget(card, pos, 0);
        card->show();
        pos++;
    }
}

void CardDisplay::SetColumns(int c){
    columns_ = c;
}
