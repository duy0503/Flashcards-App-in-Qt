#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>      // QMainWindow
#include <QGridLayout>      // QGridLayout
#include <QResizeEvent>     // QResizeEvent
#include <QSize>            // QSize
#include <flashcard.h>      // Flashcard class
#include <deck.h>           // Deck class


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructor for MainWindow.
     * @param parent is a pointer to MainWindow's parent.
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow();

private:
    /**
     * @brief MainWindow's graphical components.
     */
    Ui::MainWindow *ui;

    /**
     * @brief A QString which holds the file name of the file that's currently open.
     */
    QString currentFileName;

    /**
     * @brief A Deck that holds the flashcards in memory.
     */
    Deck deck;

    /**
     * @brief A pointer to the QGridLayout which holds the display for the cards.
     */
    QGridLayout *ScrollAreaLayout;

    /**
     * @brief Checks if the file is modified. If it returns true, we should prompt the user to save.
     * @returns A bool that is true if there are any unsaved changes, or false otherwise.
     */
    bool okToClose();

    /**
     * @brief Setter function for currentFileName.
     */
    void setCurrentFile(const QString &fileName);

    void newFile();
    void openFile();
    bool saveFile();
    bool saveAsFile();
    void display();
    void updateDisplayWindow();
    void updateWindowTitle();
    void clearScrollArea();
    void resizeEvent(QResizeEvent* event);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionNew_triggered();      // triggered whenever the new button is clicked
    void on_actionOpen_triggered();     // triggered whenever the open button is clicked
    void on_actionSave_triggered();     // triggered whenever the save button is clicked
    void on_actionClose_triggered();    // triggered whenever the close button is clicked
    void on_actionSave_As_triggered();  // triggered whenever the save as button is clicked
    void on_AddNewCardButton_clicked(); // triggered whenever the add new card button is clicked
    void on_searchButton_clicked();     // triggered whenever the search button is clicked
    void on_searchEdit_editingFinished(); // triggerd whenever user presses Enter after putting in a search key into the searchEdit
    //void on_searchEdit_textChanged(const QString &arg1); // trigger whenever the search key is changed in the searchEdit
};

#endif // MAINWINDOW_H
