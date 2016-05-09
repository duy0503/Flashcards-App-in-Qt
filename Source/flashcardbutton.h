#ifndef FLASHCARDBUTTON_H
#define FLASHCARDBUTTON_H

#include <QWidget>
#include <QPushButton>

class Flashcard;

namespace Ui {
class FlashcardButton;
}

class FlashcardButton : public QPushButton
{
    Q_OBJECT

public:
    Flashcard* card_;
    explicit FlashcardButton(QPushButton *parent = 0);
    ~FlashcardButton();

    void setLabel(QString keyword);
    void setFlashcard(Flashcard* card);

signals:
    bool clicked();

private slots:
    void on_editButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::FlashcardButton *ui;
};

#endif // FLASHCARDBUTTON_H
