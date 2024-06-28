#include "teachBox.h"
#include "ui_teachBox.h"
#include "json/json.h"

TeachBox::TeachBox(const Config &config, Ui::MainWindow *ui, QWidget *parent)
    : QMainWindow(parent)
    , ui(ui)
{
    ui->setupUi(this);
    this->referenceManager = new ReferenceManager(ui);
    this->communicationController = new CommunicationController(config, this->referenceManager, ui);
    this->interfaceController = new InterfaceController(config, this->referenceManager, ui);

}
TeachBox::~TeachBox()
{
    delete ui;
    delete communicationController;
    delete interfaceController;
    if(referenceManager!=nullptr)
        delete referenceManager;
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
// 运行页面：运行按钮
void TeachBox::on_runQueue_enable_Btn12_clicked()
{
    this->communicationController->startMoveCommand(Space::joint, 1);
}
void TeachBox::on_runQueue_enable_Btn22_clicked()
{
    this->communicationController->startMoveCommand(Space::joint, 2);
}
void TeachBox::on_runQueue_enable_Btn32_clicked()
{
    this->communicationController->startMoveCommand(Space::joint, 3);
}
void TeachBox::on_runQueue_enable_Btn42_clicked()
{
    this->communicationController->startMoveCommand(Space::joint, 4);
}
void TeachBox::on_runQueue_enable_Btn52_clicked()
{
    this->communicationController->startMoveCommand(Space::joint, 5);
}
void TeachBox::on_runQueue_enable_Btn62_clicked()
{
    this->communicationController->startMoveCommand(Space::joint, 6);
}
// 运行页面：示教按钮
void TeachBox::on_runQueue_enable_Btn11_clicked()
{
    //    this->interfaceController->teachPosition(1, checked);
}
void TeachBox::on_runQueue_enable_Btn21_clicked()
{

}
void TeachBox::on_runQueue_enable_Btn31_clicked()
{

}
void TeachBox::on_runQueue_enable_Btn41_clicked()
{

}
void TeachBox::on_runQueue_enable_Btn51_clicked()
{

}
void TeachBox::on_runQueue_enable_Btn61_clicked()
{

}
// 运行页面：保存按钮
void TeachBox::on_runQueue_enable_Btn13_toggled(bool checked)
{
    this->interfaceController->changeMoveGoal(1, checked);
}
void TeachBox::on_runQueue_enable_Btn23_toggled(bool checked)
{
    this->interfaceController->changeMoveGoal(2, checked);
}
void TeachBox::on_runQueue_enable_Btn33_toggled(bool checked)
{
    this->interfaceController->changeMoveGoal(3, checked);
}
void TeachBox::on_runQueue_enable_Btn43_toggled(bool checked)
{
    this->interfaceController->changeMoveGoal(4, checked);
}
void TeachBox::on_runQueue_enable_Btn53_toggled(bool checked)
{
    this->interfaceController->changeMoveGoal(5, checked);
}
void TeachBox::on_runQueue_enable_Btn63_toggled(bool checked)
{
    this->interfaceController->changeMoveGoal(6, checked);
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
// 点动类
void TeachBox::on_J1_Btn1_pressed()
{
    this->communicationController->jogMoveCommand(1,-1);
}
void TeachBox::on_J1_Btn2_pressed()
{
    this->communicationController->jogMoveCommand(1,1);
}
void TeachBox::on_J2_Btn1_pressed()
{
    this->communicationController->jogMoveCommand(2,-1);
}
void TeachBox::on_J2_Btn2_pressed()
{
    this->communicationController->jogMoveCommand(2,1);
}
void TeachBox::on_J3_Btn1_pressed()
{
    this->communicationController->jogMoveCommand(3,-1);
}
void TeachBox::on_J3_Btn2_pressed()
{
    this->communicationController->jogMoveCommand(3,1);
}
void TeachBox::on_J4_Btn1_pressed()
{
    this->communicationController->jogMoveCommand(4,-1);
}
void TeachBox::on_J4_Btn2_pressed()
{
    this->communicationController->jogMoveCommand(4,1);
}
void TeachBox::on_J5_Btn1_pressed()
{
    this->communicationController->jogMoveCommand(5,-1);
}
void TeachBox::on_J5_Btn2_pressed()
{
    this->communicationController->jogMoveCommand(5,1);
}
void TeachBox::on_J6_Btn1_pressed()
{
    this->communicationController->jogMoveCommand(6,-1);
}
void TeachBox::on_J6_Btn2_pressed()
{
    this->communicationController->jogMoveCommand(6,1);
}
void TeachBox::on_J7_Btn1_pressed()
{
    this->communicationController->jogMoveCommand(7,-1);
}
void TeachBox::on_J7_Btn2_pressed()
{
    this->communicationController->jogMoveCommand(7,1);
}
void TeachBox::on_J1_Btn1_released()
{
    this->communicationController->jogStopCommand(1);
}
void TeachBox::on_J1_Btn2_released()
{
    this->communicationController->jogStopCommand(1);
}
void TeachBox::on_J2_Btn1_released()
{
    this->communicationController->jogStopCommand(2);
}
void TeachBox::on_J2_Btn2_released()
{
    this->communicationController->jogStopCommand(2);
}
void TeachBox::on_J3_Btn1_released()
{
    this->communicationController->jogStopCommand(3);
}
void TeachBox::on_J3_Btn2_released()
{
    this->communicationController->jogStopCommand(3);
}
void TeachBox::on_J4_Btn1_released()
{
    this->communicationController->jogStopCommand(4);
}
void TeachBox::on_J4_Btn2_released()
{
    this->communicationController->jogStopCommand(4);
}
void TeachBox::on_J5_Btn1_released()
{
    this->communicationController->jogStopCommand(5);
}
void TeachBox::on_J5_Btn2_released()
{
    this->communicationController->jogStopCommand(5);
}
void TeachBox::on_J6_Btn1_released()
{
    this->communicationController->jogStopCommand(6);
}
void TeachBox::on_J6_Btn2_released()
{
    this->communicationController->jogStopCommand(6);
}
void TeachBox::on_J7_Btn1_released()
{
    this->communicationController->jogStopCommand(7);
}
void TeachBox::on_J7_Btn2_released()
{
    this->communicationController->jogStopCommand(7);
}

