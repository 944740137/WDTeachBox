#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "message/message.h"
#include "json/json.h"

MainWindow::MainWindow(const Config &config, Ui::MainWindow *ui, QWidget *parent)
    : QMainWindow(parent)
    , ui(ui)
{

    ui->setupUi(this);
    this->communicationController = new CommunicationController(config, ui);
    this->interfaceController = new InterfaceController(config, ui);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete communicationController;
}
// 功能列表
void MainWindow::on_fun_ListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    this->interfaceController->functionPageSwitching(current, previous, this->communicationController);
}
// 网络设置
void MainWindow::resetNetConfigInterface()
{
    ui->IP_LineEdit->setText(this->communicationController->ip);
    ui->port_LineEdit->setText(QString::number(this->communicationController->port));
    ui->setNet_Btn->setChecked(false);
    ui->setNet_Btn->setText("修改");
    ui->IP_LineEdit->setEnabled(false);
    ui->port_LineEdit->setEnabled(false);
}

void MainWindow::on_setNet_Btn_toggled(bool checked)
{
    if(checked)
    {
        ui->setNet_Btn->setText("确定");
        ui->IP_LineEdit->setEnabled(true);
        ui->port_LineEdit->setEnabled(true);
    }
    else
    {
        QString ip = ui->IP_LineEdit->text();
        QString port = ui->port_LineEdit->text();
        // 判断格式正确
        if(ip.count('.')!=3 || port.isEmpty() ||ip.right(1)=="." )
        {
            messageAbout(this, IP_ERROR);
            this->resetNetConfigInterface();
            return;
        }
        ui->setNet_Btn->setText("修改");
        ui->IP_LineEdit->setEnabled(false);
        ui->port_LineEdit->setEnabled(false);
        // 判断相同？
        if(ip==this->communicationController->ip&&port.toInt()==this->communicationController->port)
            return;
        this->communicationController->resetConnect(ip,port.toInt());
    }
}

void MainWindow::on_ctr_ComboBox_activated(int index)
{
    this->communicationController->changeControllerCommand(index);
}
void MainWindow::on_plan_ComboBox_activated(int index)
{
    this->communicationController->changePlannerCommand(index);
}

//速度
void MainWindow::setVel()
{
    int jogVel = ui->jogVel_lab_2->text().toInt();
    int runVel = ui->runVel_lab_2->text().toInt();
    this->communicationController->changeVelocityCommand(runVel, jogVel);
}
void MainWindow::velUp(int &vel)
{
    if(vel == 1)
        vel = 0;
    vel = vel + 5;
    if(vel >= 100)
        vel = 100;
}
void MainWindow::velDown(int &vel)
{
    vel = vel - 5;
    if(vel <= 0)
        vel = 1;
}
void MainWindow::on_jogVel_Btn2_clicked()
{
    int jogVel = ui->jogVel_lab_2->text().toInt();
    velUp(jogVel);
    ui->jogVel_lab_2->setText(QString::number(jogVel));
    this->setVel();
}
void MainWindow::on_jogVel_Btn1_clicked()
{
    int jogVel = ui->jogVel_lab_2->text().toInt();
    velDown(jogVel);
    ui->jogVel_lab_2->setText(QString::number(jogVel));
    this->setVel();
}
void MainWindow::on_runVel_Btn_clicked()
{
    int runVel = ui->runVel_lab_2->text().toInt();
    velUp(runVel);
    ui->runVel_lab_2->setText(QString::number(runVel));
    this->setVel();
}
void MainWindow::on_runVel_Btn_2_clicked()
{
    int runVel = ui->runVel_lab_2->text().toInt();
    velDown(runVel);
    ui->runVel_lab_2->setText(QString::number(runVel));
    this->setVel();
}

// 按钮类
void MainWindow::on_backZero_Btn_clicked()
{
    this->communicationController->backToZeroCommand();
}

void MainWindow::on_stop_Btn_clicked()
{
    this->communicationController->stopMoveCommand();
}
void MainWindow::getPosition()
{
    this->communicationController->getPositionCommand();
}
