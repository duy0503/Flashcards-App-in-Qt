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
#include <QHBoxLayout>

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    this->setWindowTitle(tr("Flashcards"));

    // Create a layout to display flashcards
    ScrollAreaLayout = new QGridLayout();

    // Create a layout for Test Yourself
    testDisplay = new Test();
    testDisplayWidget = new QWidget();
    testDisplayLayout = new QHBoxLayout();
    testDisplayLayout->addWidget(testDisplay);
    testDisplayWidget->setLayout(testDisplayLayout);
    ui->displayStackedWidget->addWidget(testDisplayWidget);

    // Set the main display to displayFlashcards
    ui->displayStackedWidget->setCurrentWidget(ui->displayFlashcards);
    ui->bottomStackedWidget->setCurrentWidget(ui->bottomStackedWidgetPage1);
    ui->topStackedWidget->setCurrentWidget(ui->topStackedWidgetPage1);

    currentFileName = "";
    QObject::connect(&deck, SIGNAL(updateDisplayAfterDeletingCard()), this, SLOT(display()));
    QObject::connect(testDisplay, SIGNAL(testFinished()), this, SLOT(on_TestYourselfFinished()));
    QObject::connect(testDisplay, SIGNAL(progressUpdate()), this, SLOT(on_testProgressUpdate()));
}

MainWindow::~MainWindow(){

    delete ui;
}

void MainWindow::on_actionNew_triggered(){

    newFile();
}

void MainWindow::on_actionOpen_triggered(){

    openFile();
}

void MainWindow::on_actionSave_triggered(){

    saveFile();
}

void MainWindow::on_actionClose_triggered(){

    QWidget::close();
}

void MainWindow::on_actionSave_As_triggered(){

    saveAsFile();
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About Flashcards"), tr("Version 1.0\n\nCreators:\n"
                                                        "Marvin Duro, Duy Do, Daniel Ceja, Crystal Juarez, An Ngo\n"));
}
void MainWindow::on_AddNewCardButton_clicked(){

    deck.addNewCard();
    display();
}

void MainWindow::on_searchButton_clicked(){
    deck.runSearchFeature(ui->searchEdit->text());
}

void MainWindow::on_searchEdit_editingFinished() {
    deck.runSearchFeature(ui->searchEdit->text());
    ui->searchEdit->clearFocus();
}

void MainWindow::on_searchEdit_textChanged(const QString &arg1) {
    deck.runSearchFeature(ui->searchEdit->text());
}

void MainWindow::on_StopTestYourselfButton_clicked()
{
    on_TestYourselfFinished();
}
bool MainWindow::okToClose(){

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

void MainWindow::setCurrentFile(const QString &fileName){

    currentFileName = fileName;
}

void MainWindow::newFile(){

    if( okToClose() ){
        deck.Clear();
        currentFileName = "";
        deck.setDeckModified(false);
        updateDisplayWindow();
    }

}

void MainWindow::openFile(){

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

bool MainWindow::saveFile(){

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

void MainWindow::updateWindowTitle(){

    QString windowTitle = currentFileName + " - Flashcards";
    this->setWindowTitle(windowTitle);
}

/* Function to display the list of cards on Main Window */
void MainWindow::display() {

    int columns = qMax( (this->size().width() - 32) / (432 + 24), 1 ); // 32 for the window border, 24 for the spacing between each card
    Flashcard* card;
    int total = 0;

    foreach (card, deck.deck_) {
        int row = total / columns;
        int column = total % columns;
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

void MainWindow::on_TestYourselfButton_clicked() {
    if ( deck.deck_.length() > 0 ){
        testDisplay->setDeck(&deck);
        ui->displayStackedWidget->setCurrentWidget(testDisplayWidget);
        ui->bottomStackedWidget->setCurrentWidget(ui->bottomStackedWidgetPage2);
        ui->topStackedWidget->setCurrentWidget(ui->topStackedWidgetPage2);
        ui->progressBar->setMaximum(deck.deck_.length());
        ui->progressBar->setValue(1);
        testDisplay->startTest();
    }
    else {
        QMessageBox::information(this, tr("Test Yourself"),
                                 tr("Deck is empty. Please open a deck"));
    }
}

void MainWindow::on_TestYourselfFinished(){
    ui->displayStackedWidget->setCurrentWidget(ui->displayFlashcards);
    ui->bottomStackedWidget->setCurrentWidget(ui->bottomStackedWidgetPage1);
    ui->topStackedWidget->setCurrentWidget(ui->topStackedWidgetPage1);
}

void MainWindow::on_testProgressUpdate() {
    ui->progressBar->setValue(testDisplay->currentSequenceIndex_+1);
    ui->rightLabel->setText(QString::number(testDisplay->rightCards_));
    ui->wrongLabel->setText(QString::number(testDisplay->wrongCards_));
}

