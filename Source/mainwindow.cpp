#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->textBrowser);
    createActions();
    createMenu();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    // Action to create a new deck
    newAction = new QAction(tr("&New"), this);
    newAction->setStatusTip("Create a new deck");
    //connect(newAction, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    // Action to open an existing deck
    openAction = new QAction(tr("&Open"), this);
    openAction->setStatusTip("Open an existing deck");
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));

}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
}

bool MainWindow::okToContinue()
{
    if (isWindowModified())
    {
        int r = QMessageBox::warning(this, tr("&Deck"),
                                     tr("The deck has been modified.\n"
                                        "Do you want to save your changes?"),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (r == QMessageBox::Yes)
        {
            return false;
        }
    }

    return true;
}

void MainWindow::openFile()
{
    if (okToContinue())
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open a deck"), ".", tr("*.txt"));
        if (!fileName.isEmpty())
        {
            loadFile(fileName);
        }
    }
}

bool MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QTextStream in(&file);
    while(!in.atEnd())
    {
        cardType* newCard = new cardType;
        QString Question = in.readLine();
        newCard->Question = Question;

        QString Answer = in.readLine();
        newCard->Answer = Answer;

        deck.append(newCard);
    }

    //Call function display() to show the cards
    display();
    return true;
}

void MainWindow::display()
{
    foreach (cardType* card, deck)
    {
        ui->textBrowser->append(card->Question);
        ui->textBrowser->append(card->Answer);
    }

}

