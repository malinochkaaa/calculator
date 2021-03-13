#include "mainwindow.h"
#include "ui_mainwindow.h"

double calVal=0.0;
bool divTrigger=false;
bool multTrigger=false;
bool addTrigger=false;
bool subTrigger=false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calVal));
    QPushButton *numButtons[16];
    for(int i=0; i<16; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button -> text();
    QString displayVal = ui -> Display -> text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui -> Display -> setText(butVal);
    }else{
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui -> Display -> setText(QString::number(dblNewVal, 'g', 16));

    }
}

void MainWindow::MathButtonressed(){
    bool divTrigger=false;
    bool multTrigger=false;
    bool addTrigger=false;
    bool subTrigger=false;
    QString displayVal = ui -> Display ->text();
    calVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button -> text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger=true;
    }else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger=true;
    }else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger=true;
    }else{
        subTrigger=true;
    }
    ui->Display->setText("");
}

void MainWindow::EqualButton(){
    double solution = 0.0;
    QString displayVal = ui -> Display -> text();
    double dblDisplayVal = displayVal.toDouble();
    if(divTrigger || multTrigger || addTrigger || subTrigger){
        if(divTrigger){
            solution = calVal / dblDisplayVal;
        }else if(multTrigger ){
            solution = calVal * dblDisplayVal;
        }else if(addTrigger){
            solution = calVal + dblDisplayVal;
        }else{
            solution = calVal - dblDisplayVal;
        }
    }
    ui -> Display ->setText(QString::number(solution));
}

void MainWindow::ChangeNumberSign(){

}
