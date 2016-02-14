#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
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
            setCurrentFile(fileName);
            display.Set(ui->scrollAreaWidgetContents, &deck);
            display.Update();
            //deck.Display(ui->scrollAreaWidgetContents);
        }
    }
}
