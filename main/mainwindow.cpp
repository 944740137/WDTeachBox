#include "mainwindow.h"
#include "ui_mainwindow.h"
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

// 功能表切换
void MainWindow::on_fun_ListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    this->interfaceController->functionPageSwitching(current, previous, this->communicationController);
}
// ip端口设置按钮
void MainWindow::on_setNet_Btn_toggled(bool checked)
{
     this->interfaceController->setIPandPort(checked, this->communicationController);
}

// 规控切换组合框
void MainWindow::on_ctr_ComboBox_activated(int index)
{
    this->communicationController->changeControllerCommand(index);
}
void MainWindow::on_plan_ComboBox_activated(int index)
{
    this->communicationController->changePlannerCommand(index);
}
// 速度增减按钮
void MainWindow::on_jogVel_Btn2_clicked()
{
    this->interfaceController->changeVelocity(VelocityType::jogVelocity, true, this->communicationController);
}
void MainWindow::on_jogVel_Btn1_clicked()
{
    this->interfaceController->changeVelocity(VelocityType::jogVelocity, false, this->communicationController);
}
void MainWindow::on_runVel_Btn_clicked()
{
    this->interfaceController->changeVelocity(VelocityType::runVelocity, true, this->communicationController);
}
void MainWindow::on_runVel_Btn_2_clicked()
{
    this->interfaceController->changeVelocity(VelocityType::runVelocity, false, this->communicationController);
}
// 功能按钮类
void MainWindow::on_backZero_Btn_clicked()
{
    this->communicationController->backToZeroCommand();
}

void MainWindow::on_stop_Btn_clicked()
{
    this->communicationController->stopMoveCommand();
}
