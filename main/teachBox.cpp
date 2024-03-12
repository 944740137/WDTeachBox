#include "teachBox.h"
#include "ui_teachBox.h"
#include "json/json.h"

TeachBox::TeachBox(const Config &config, Ui::MainWindow *ui, QWidget *parent)
    : QMainWindow(parent)
    , ui(ui)
{
    ui->setupUi(this);
    this->communicationController = new CommunicationController(config, ui);
    this->interfaceController = new InterfaceController(config, ui);
}
TeachBox::~TeachBox()
{
    delete ui;
    delete communicationController;
}

// 功能表切换
void TeachBox::on_fun_ListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    this->interfaceController->functionPageSwitching(current, previous, this->communicationController);
}
// ip端口设置按钮
void TeachBox::on_setNet_Btn_toggled(bool checked)
{
     this->interfaceController->setIPandPort(checked, this->communicationController);
}
// 规控切换组合框
void TeachBox::on_ctr_ComboBox_activated(int index)
{
    this->communicationController->changeControllerCommand(index);
}
void TeachBox::on_plan_ComboBox_activated(int index)
{
    this->communicationController->changePlannerCommand(index);
}
// 速度增减按钮
void TeachBox::on_jogVel_Btn2_clicked()
{
    this->interfaceController->changeVelocity(VelocityType::jogVelocity, true, this->communicationController);
}
void TeachBox::on_jogVel_Btn1_clicked()
{
    this->interfaceController->changeVelocity(VelocityType::jogVelocity, false, this->communicationController);
}
void TeachBox::on_runVel_Btn_clicked()
{
    this->interfaceController->changeVelocity(VelocityType::runVelocity, true, this->communicationController);
}
void TeachBox::on_runVel_Btn_2_clicked()
{
    this->interfaceController->changeVelocity(VelocityType::runVelocity, false, this->communicationController);
}
// 功能按钮类
void TeachBox::on_backZero_Btn_clicked()
{
    this->communicationController->backToZeroCommand();
}
void TeachBox::on_stop_Btn_clicked()
{
    this->communicationController->stopMoveCommand();
}
