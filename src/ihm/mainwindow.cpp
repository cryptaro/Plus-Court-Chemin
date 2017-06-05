#include "ihm/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    nbX(10),nbY(10)
{
    ui->setupUi(this);

    connect(ui->actionNew_Grid, SIGNAL(triggered(bool)), this, SLOT(reset()));
    connect(ui->butLaunch, SIGNAL(clicked(bool)), this, SLOT(launch()));
    connect(ui->enableDiagCheck, SIGNAL(toggled(bool)), ui->grid, SLOT(includeDiag(bool)));
    connect(ui->showHeiristicCheck, SIGNAL(toggled(bool)), ui->grid, SLOT(showHeuristique(bool)));

    connect(ui->butClear, SIGNAL(clicked(bool)), this, SLOT(clean()));
    connect(ui->butNew, SIGNAL(clicked(bool)), this, SLOT(reset()));

    ui->grid->showHeuristique(ui->showHeiristicCheck->isChecked());
    ui->grid->includeDiag(ui->enableDiagCheck->isChecked());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::reset(){
    ui->grid->reset(ui->xSpin->value(), ui->ySpin->value());
    ui->grid->showHeuristique(ui->showHeiristicCheck->isChecked());
    ui->grid->includeDiag(ui->enableDiagCheck->isChecked());
}

void MainWindow::clean(){
    ui->grid->clean();
    ui->grid->includeDiag(ui->enableDiagCheck->isChecked());
    ui->grid->showHeuristique(ui->showHeiristicCheck->isChecked());
}


void MainWindow::launch(){
    ui->grid->compute(ui->timeSpin->value());
}
