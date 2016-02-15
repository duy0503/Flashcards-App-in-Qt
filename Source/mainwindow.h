#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGridLayout>
#include <flashcard.h>
#include <deck.h>
//#include <carddisplay.h>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private:
    Ui::MainWindow *ui;
    QString currentFileName;
    Deck deck;
    QGridLayout *ScrollAreaLayout;

    bool okToContinue();
    void setCurrentFile(const QString &fileName);
    void openFile();
    void Display();
    void updateDisplayWindow();
    void clearScrollArea();

  protected:
    //void closeEvent(QCloseEvent *event);

  private slots:
    void on_actionNew_triggered();      // triggered whenver the new button is clicked
    void on_actionOpen_triggered();     // triggered whenever the open button is clicked
    void on_actionSave_triggered();     // triggered whenever the save button is clicked
    void on_actionClose_triggered();    // triggered whenever the close button is clicked
};

#endif // MAINWINDOW_H
