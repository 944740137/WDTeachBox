#include <QDebug>
#include "controller/interfaceController.h"
#include "json/json.h"

InterfaceController::~InterfaceController()
{
}
InterfaceController::InterfaceController(const Config &config, ReferenceManager *referenceManager, Ui::MainWindow *ui, QWidget *parent)
    :ui(ui),referenceManager(referenceManager)
{
    // 网络设置初始化与输入约束设置
    ui->IP_LineEdit->setText(config.ip);
    ui->port_LineEdit->setText(QString::number(config.port));
    QRegExp ipExp("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    QValidator * ipFormat = new QRegExpValidator(ipExp, this);
    ui->IP_LineEdit->setValidator(ipFormat);
    ui->IP_LineEdit->setEnabled(false);
    QRegExp portExp("^([0-9]|[1-9]\\d|[1-9]\\d{2}|[1-9]\\d{3}|[1-5]\\d{4}|6[0-4]\\d{3}|65[0-4]\\d{2}|655[0-2]\\d|6553[0-5])$");
    QValidator * portFormat = new QRegExpValidator(portExp, this);
    ui->port_LineEdit->setValidator(portFormat);
    ui->port_LineEdit->setEnabled(false);
    ui->setNet_Btn->setText("修改");
    ui->setNet_Btn->setCheckable(true);

    // 主从站状态设置初始化
    ui->netStatus_Label->setStyleSheet("background-color: rgb(255,0,0)");
    ui->netStatus_Label->setText("主站断开");
    ui->slaveStatus_Label->setStyleSheet("background-color: rgb(255,0,0)");
    ui->slaveStatus_Label->setText("从站掉线");

    // 运行界面：目标位置输入约束
    for(int i =0; i<this->referenceManager->jointRunningQueueGroup.size();i++)
    {
        for(int j =0; j<referenceManager->jointRunningQueueGroup[0].size();j++)
        {
            this->referenceManager->jointRunningQueueGroup[i][j]->setValidator(new QIntValidator(this->referenceManager->jointRunningQueueGroup[i][j]));
            this->referenceManager->jointRunningQueueGroup[i][j]->setValidator(new QRegExpValidator(QRegExp("^-?((1[0-7]\\d(\\.\\d{1,2})?)|180(\\.0{1,2})?|\\d{1,2}(\\.\\d{1,2})?)$")));
        }
    }
    for(int i =0; i<this->referenceManager->cartesianRunningQueueGroup.size();i++)
    {
        for(int j =0; j<3; j++)
        {
            this->referenceManager->cartesianRunningQueueGroup[i][j]->setValidator(new QIntValidator(this->referenceManager->cartesianRunningQueueGroup[i][j]));
            this->referenceManager->cartesianRunningQueueGroup[i][j]->setValidator(new QRegExpValidator(QRegExp("^-?([01](\.\d{1,4})?|1(\.0{1,4})?|-1(\.[0-5]{1,4})?)$")));
        }
        for(int j =3; j<6; j++)
        {
            this->referenceManager->cartesianRunningQueueGroup[i][j]->setValidator(new QIntValidator(this->referenceManager->cartesianRunningQueueGroup[i][j]));
            this->referenceManager->cartesianRunningQueueGroup[i][j]->setValidator(new QRegExpValidator(QRegExp("^-?((1[0-7]\\d(\\.\\d{1,2})?)|180(\\.0{1,2})?|\\d{1,2}(\\.\\d{1,2})?)$")));
        }
    }
    // 运行界面：修改点位
    for(int i =0; i < this->referenceManager->runPageChangeMoveGoal.size();i++)
    {
        this->referenceManager->runPageChangeMoveGoal[i]->setText("修改");
        this->referenceManager->runPageChangeMoveGoal[i]->setCheckable(true);
        for (int j = 0; j < this->referenceManager->jointRunningQueueGroup[0].size(); j++)
            this->referenceManager->jointRunningQueueGroup[i][j]->setEnabled(false);
    }
}

// 交互处理逻辑
void InterfaceController::functionPageSwitching(QListWidgetItem *current, QListWidgetItem *previous, CommunicationController *communicationController)
{
    if(previous==nullptr)
        return;

    // 离开设置界面:重置未保存数据
    if(previous->text()=="设置" && current->text()!="设置")
    {
        ui->IP_LineEdit->setText(communicationController->ip);
        ui->port_LineEdit->setText(QString::number(communicationController->port));
        ui->setNet_Btn->setChecked(false);
        ui->setNet_Btn->setText("修改");
        ui->IP_LineEdit->setEnabled(false);
        ui->port_LineEdit->setEnabled(false);
    }

    // 离开运行界面:重置未保存数据
    if(previous->text()=="运行" && current->text()!="运行")
    {
        for(int i =0; i < this->referenceManager->runPageChangeMoveGoal.size();i++)
        {
            this->referenceManager->runPageChangeMoveGoal[i]->setText("修改");
            this->referenceManager->runPageChangeMoveGoal[i]->setChecked(false);
            for (int j = 0; j < this->referenceManager->jointRunningQueueGroup[0].size(); j++)
            {
                this->referenceManager->jointRunningQueueGroup[i][j]->setEnabled(false);
            }
        }
    }

    // 进入运行界面:启动查询位置定时器位置
    if(current->text()=="运行")
        communicationController->askPosTimer->start(500);//500ms
    else
        communicationController->askPosTimer->stop();

}
void InterfaceController::setIPandPort(bool checked, CommunicationController *communicationController)
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
//            messageAbout(this, IP_ERROR); // todo:增加message类
            qDebug()<<"[------] error IP_ERROR";
            ui->IP_LineEdit->setText(communicationController->ip);
            ui->port_LineEdit->setText(QString::number(communicationController->port));
            ui->setNet_Btn->setChecked(false);
            ui->setNet_Btn->setText("修改");
            ui->IP_LineEdit->setEnabled(false);
            ui->port_LineEdit->setEnabled(false);
            return;
        }
        ui->setNet_Btn->setText("修改");
        ui->IP_LineEdit->setEnabled(false);
        ui->port_LineEdit->setEnabled(false);
        // 判断相同？
        if(ip==communicationController->ip&&port.toInt()==communicationController->port)
            return;
        communicationController->resetConnect(ip,port.toInt());
    }
}
void InterfaceController::changeVelocity(VelocityType velocityType, bool isPlus, CommunicationController *communicationController)
{
    auto updateVelocity = [](bool isPlus, int& vel)//vel:1,5,10....100
    {
        vel = isPlus ? qMin(vel + 5, 100) : qMax(vel - 5, 1);
        vel = (vel == 6) ? 5 : vel;
    };

    int Vel = 0;
    switch (velocityType) {
    case VelocityType::jogVelocity:
        Vel = ui->jogVel_lab_2->text().toInt();
        updateVelocity(isPlus,Vel);
        ui->jogVel_lab_2->setText(QString::number(Vel));
        break;
    case VelocityType::runVelocity:
        Vel = ui->runVel_lab_2->text().toInt();
        updateVelocity(isPlus,Vel);
        ui->runVel_lab_2->setText(QString::number(Vel));
        break;
    default:
        break;
    }

    int jogVel = ui->jogVel_lab_2->text().toInt();
    int runVel = ui->runVel_lab_2->text().toInt();
    communicationController->changeVelocityCommand(runVel, jogVel);
}
void InterfaceController::changeMoveGoal(int index, bool checked)
{
    if(checked)
    {
        this->referenceManager->runPageChangeMoveGoal[index - 1]->setText("确定");
        for(int i =0; i < this->referenceManager->jointRunningQueueGroup[0].size(); i++)
        {
            this->referenceManager->jointRunningQueueGroup[index - 1][i]->setEnabled(true);
        }
    }
    else
    {
        // 按下确定
        this->referenceManager->runPageChangeMoveGoal[index - 1]->setText("修改");
        for(int i =0; i < this->referenceManager->jointRunningQueueGroup[0].size(); i++)
        {
            this->referenceManager->jointRunningQueueGroup[index - 1][i]->setEnabled(false);
        }

        QJsonObject robotJsonObject;
        QJsonObject taskJsonObject;
        QJsonArray bearArray[7];
        QList<QString> position = {"q1","q2","q3","q4","q5","q6"};
        for (int i = 0; i < position.size(); i++)
        {
            for (int j = 0; j < this->referenceManager->jointRunningQueueGroup[i].size(); j++)
            {
                bearArray[i].append(this->referenceManager->jointRunningQueueGroup[i][j]->text().toDouble());
            }
            robotJsonObject[position[i]] = bearArray[i];
        }
        taskJsonObject["panda"] = robotJsonObject;
        setJsonObjectToFile(TaskJsonPath, taskJsonObject);
    }

}


