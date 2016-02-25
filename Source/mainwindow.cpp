#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_flashcard.h"
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QGridLayout>
#include <QResizeEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle(tr("Flashcards"));
    ScrollAreaLayout = new QGridLayout();
    ui->TestYourselfButton->hide();
    currentFileName = "";
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
    saveFile();
}

void MainWindow::on_actionClose_triggered()
{
    QWidget::close();
}

void MainWindow::on_actionSave_As_triggered()
{
    saveAsFile();
}

bool MainWindow::okToClose() {
    if (deck.isDeckModified())
    {
        int r = QMessageBox::warning(this, tr("Warning!"),
                                     tr("The deck has been modified.\n"
                                        "Do you want to save your changes?"),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (r == QMessageBox::Cancel)
        {
            return false;
        }
        else if (r == QMessageBox::Yes)
        {
            if(saveFile()) return true;
            else return false;
        }
    }
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName) {
    currentFileName = fileName;
}

void MainWindow::openFile() {
    if (!okToClose()) {
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a deck"), ".", tr("*.fc"));
    if (!fileName.isEmpty()) {
        if (!fileName.endsWith(".fc")){
            QMessageBox::warning(this, tr("Warning!"),
                                 tr("Incorrect file format\n"), QMessageBox::Ok);

        }
        bool success = deck.Open(fileName);
        if (success) {
            setCurrentFile(fileName);
            updateDisplayWindow();
        }
    }
}

bool MainWindow::saveFile() {

    bool success = true;
    if (!currentFileName.isEmpty()){
        if (!deck.Save(currentFileName)){
            QMessageBox::warning(this, tr("Save"),
                                 tr("Deck could not be saved.\n"
                                    "Please try again later"), QMessageBox::Ok);
            success = false;
        }
    }
    else {
        success = saveAsFile();
    }
    return success;
}

bool MainWindow::saveAsFile(){

    bool success = true;
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Deck"), ".",
                                                    tr("flashcards (*.fc)"));
    if (!fileName.isEmpty()){
        if (!fileName.endsWith(".fc")){
            fileName.append(".fc");
        }
        if (deck.Save(fileName)){
            setCurrentFile(fileName);
        }
        else{
            QMessageBox::warning(this, tr("Save"),
                                 tr("Deck could not be saved.\n"
                                    "Please try again later"), QMessageBox::Ok);
            success = false;
        }
    }
    updateWindowTitle();
    return success;
}

/* Function to update the list of cards on Main Window
   after loading a deck
*/
void MainWindow::updateDisplayWindow(){
    updateWindowTitle();
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
        int column = total % columns;;
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

void MainWindow::closeEvent (QCloseEvent *event){
    if (okToClose()) {
        event->accept();
    }
    else event->ignore();
}

void MainWindow::updateWindowTitle(){
    QString windowTitle = currentFileName + " - Flashcards";
    this->setWindowTitle(windowTitle);
}
