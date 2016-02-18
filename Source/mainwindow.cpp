#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle(tr("Flashcards"));
    ScrollAreaLayout = new QGridLayout();
    ui->TestYourselfButton->hide();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionOpen_triggered() {
    openFile();
}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionClose_triggered()
{

}

bool MainWindow::okToContinue() {
    if (isWindowModified())
    {
        int r = QMessageBox::warning(this, tr("&Deck"),
                                     tr("The deck has been modified.\n"
                                        "Do you want to save your changes?"),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (r == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName) {
    currentFileName = fileName;
}

void MainWindow::openFile() {
    if (okToContinue() == false) {
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a deck"), ".", tr("*.txt"));
    if (!fileName.isEmpty()) {
        bool success = deck.Open(fileName);
        if (success) {
            updateDisplayWindow();
        }
    }
}

/* Function to update the list of cards on Main Window
   after loading a deck
*/
void MainWindow::updateDisplayWindow(){
    clearScrollArea();
    display();
}

/* Function to display the list of cards on Main Window */
void MainWindow::display() {
    int columns = qMax(this->size().width(), 600) / 600;
    Flashcard* card;
    int total = 0;

    foreach (card, deck.deck_) {
        int row = total / columns;
        int column = total % columns;
        card->keywordsButton->setMinimumHeight(columns*50 + 50);
        ScrollAreaLayout->addWidget(card->keywordsButton, row, column);
        total++;
    }

    ui->scrollAreaWidgetContents->setLayout(ScrollAreaLayout);
    ui->TestYourselfButton->show();
}

/* Function to clear the old list of cards' widgets in the Main Window */
void MainWindow::clearScrollArea(){

    if ( ScrollAreaLayout->layout() != NULL ){
        QLayoutItem* item;
        while ( ( item = ScrollAreaLayout->layout()->takeAt( 0 ) ) != NULL ){
            delete item->widget();
            delete item;
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    display();
}
