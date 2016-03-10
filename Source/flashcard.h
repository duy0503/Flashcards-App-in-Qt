#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <QWidget>
#include <QPushButton>
#include <QString>

namespace Ui {
class Flashcard;
}


typedef class Flashcard : public QWidget {
    Q_OBJECT

public:

    /**
     * @brief The flashcard's graphical components.
     */
    Ui::Flashcard *flashcardUi;
    /**
     * @brief getter function for question_
     * @return A Qstring which is a copy of question_
     */
    QString getQuestion();

    /**
     * @brief Setter function for question_.
     * @param question is a QString containing the new question.
     * @warning Mutates QuestionLabel so that it mirrors the new question.
     */
    void setQuestion(QString question);

    /**
     * @brief Getter function for answer_.
     * @return A QString which is a copy of answer_.
     */
    QString getAnswer();

    /**
     * @brief Setter function for answer_.
     * @param answer is a QString containing the new answer.
     * @warning Mutates AnswerLabel so that it mirrors the new question.
     */
    void setAnswer(QString answer);

    /**
     * @brief Getter function for keywords_.
     * @return A QString which contains each keyword as a comma-seperated list.
     * @todo Make this return a QList which holds each keyword.
     */
    QString getKeywords();

    /**
     * @brief Setter function for keywords_.
     * @param keywords is a comma-seperated list of keywords.
     * @todo Make this accept a QList of keywords.
     */
    void setKeywords(QString keywords);

    /**
     * @brief Constructor for Flashcard
     * @param parent is a pointer to the flashcard's parent.
     */
    explicit Flashcard(QWidget *parent = 0);

    /**
     * @brief A pointer to QPushButton which is displayed in the main window.
     * @todo Make this private.
     */
    QPushButton *keywordsButton;

    /**
     * @brief Destructor for Flashcard.
     */
    ~Flashcard();

private:
    /**
     * @brief A QString which holds the flashcard's question.
     */
    QString question_;

    /**
     * @brief A QString which holds the flashcard's answer.
     */
    QString answer_;

    /**
     * @brief A QString which holds the flashcard's keywords, separated by commas.
     * @todo Make this a QList of QStrings
     */
    QString keywords_;
signals:
    void contextChanged();
private slots:
    void showCard();
    void on_editButton_clicked();
    void on_deleteButton_clicked();
} Flashcard;

#endif // FLASHCARD_H
