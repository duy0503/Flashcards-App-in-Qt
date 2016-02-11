#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <flashcard.h>
#include <QList>

class QAction;
class QLabel;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<cardType*> deck;

    void createActions();
    void createToolbar();
    void createMenu();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    bool okToContinue();
    void display();   //display the flashcards

    QMenu *fileMenu;

    QAction *openAction;
    QAction *newAction;
protected:
    //void closeEvent(QCloseEvent *event);

private slots:
    //void newFile();
    void openFile();
    //bool saveFile();
};

#endif // MAINWINDOW_H
