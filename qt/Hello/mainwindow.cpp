#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QPushButton *b = new QPushButton();
    b->setParent(this);
    b->show();
    ui->setupUi(this);
    this->layout()->setSpacing(20);

}

MainWindow::~MainWindow()
{
    delete ui;
}

