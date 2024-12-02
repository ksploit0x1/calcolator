#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QPushButton>
#include<QtQml/QJSEngine>
#include<QRegularExpression>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(391, 240);//
    history.add(""); // initialize first node with empty stirng
    QList<QPushButton*> buttons = this->findChildren<QPushButton*>();
    foreach (QPushButton *btn, buttons) { // iterate through all Girdlayout buttons and add set_line_edite_value function that will handle all operation
        connect(btn,&QPushButton::clicked,this,[=](){
            this->set_line_edite_value(btn->text());
        });
    }
    connect(ui->actionUndo,&QAction::triggered,this,&MainWindow::undo);
    connect(ui->actionRedo,&QAction::triggered,this,&MainWindow::redo);

}


void MainWindow::set_line_edite_value(const QString value)
{
    QString old_value = ui->lineEdit->text();
    if(value == "="){
        calculate(old_value);
        history.add(old_value);
        return;
    }
    if(value == "Undo"){
        undo();
        return;
    }
    if(value == "Clear"){
        clear();
        return;
    }
    if(value == "x²"){
        ui->lineEdit->setText(old_value+"²");
        history.add(old_value+"²");
        return;
    }
    ui->lineEdit->setText(old_value+value);
    history.add(old_value+value);
}

void MainWindow::calculate(QString expression)
{
    for(int i = 0 ; i < expression.length(); i++){
        if(!QString::compare(expression[i],"÷")){
            expression[i]='/';
        }
        if(!QString::compare(expression[i],"×")){
            expression[i]='*';
        }

        if(!QString::compare(expression[i],"(") || !QString::compare(expression[i],"√")){
            if(i == 0){
                 continue;
            }
            else{
                if(expression[i-1] == "÷" ||
                   expression[i-1] == "×" ||
                   expression[i-1] == "+" ||
                   expression[i-1] == "*" ||
                   expression[i-1] == "/" ||
                   expression[i-1] == "-")
                {
                    continue;

                }else{
                    expression.insert(i,QString("*"));
                    i++;
                }
            }
        }
    }
    if(expression.contains("²")){
        expression.replace(QRegularExpression("(\\d+)²"), "Math.pow(\\1, 2)");
    }
    if(expression.contains("^")){
        expression.replace(QRegularExpression("(\\d+)\\^(\\d+)"), "Math.pow(\\1, \\2)");
    }
    if(expression.contains("√")){
        expression.replace(QRegularExpression("√(\\d+)"), "Math.sqrt(\\1)");
    }
    if(expression.contains("%")){
        expression.replace(QRegularExpression("(\\d+)%"), "\\1/100");
    }
    QJSEngine myEngine;
    QJSValue result = myEngine.evaluate(expression);
    if(result.isNumber()){
        ui->lineEdit->setText(result.toString());
    }else{
        ui->lineEdit->setText("Malformed expression");
    }

}

void MainWindow::undo()
{
    if(history.getCurrent() != ""){
        history.undo();
        ui->lineEdit->setText(history.getCurrent());
    }else{
        ui->lineEdit->setText("");
    }


}

void MainWindow::redo()
{
    history.redo();
    ui->lineEdit->setText(history.getCurrent());
}

void MainWindow::clear()
{
    ui->lineEdit->clear();
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionCopy_triggered()
{
    ui->lineEdit->selectAll();
    ui->lineEdit->copy();
    ui->lineEdit->deselect();
}


void MainWindow::on_actionPast_triggered()
{
    ui->lineEdit->paste();
    history.add(ui->lineEdit->text());
}


void MainWindow::on_actionQuit_triggered()
{
    this->close();
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,"About calcolator","This simple calculator created using Qt for learning purpose !");
}

