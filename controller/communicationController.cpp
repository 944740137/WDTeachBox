#include <QDebug>
#include "json/json.h"
#include "controller/communicationController.h"
#include "h/protocol.h"

CommunicationController::~CommunicationController()
{

}
CommunicationController::CommunicationController(const Config &config, ReferenceManager *referenceManager, Ui::MainWindow *ui, QWidget *parent):ip(config.ip),
    port(config.port),connectTimer(new QTimer(this)),askPosTimer(new QTimer(this)),tcpSocket(new QTcpSocket(this)),ui(ui),referenceManager(referenceManager)
{
    Q_UNUSED(parent);
    //网络通信
    connect(this->connectTimer, SIGNAL(timeout()), this, SLOT(toConnect()));
    this->connectTimer->start(3000);
    connect(this->tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(this->tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveMessages()));

    // 从站心跳
    this->checkoutSlaveTimer = new QTimer(this);
    connect(this->checkoutSlaveTimer, SIGNAL(timeout()), this, SLOT(checkSlaveConnectCommand()));
    this->checkoutSlaveTimer->start(500);

    this->jogTimer = new QTimer(this);
    connect(this->jogTimer, SIGNAL(timeout()), this, SLOT(jogMoveCycleCommand()));

    // 运行界面位置更新
    connect(this->askPosTimer, SIGNAL(timeout()), this, SLOT(getPositionCommand()));
}

// 网络通讯
void CommunicationController::connected()
{
    qDebug()<<"连接成功"<<endl;
    // 停止重连计时器
    this->connectTimer->stop();
    // 连接状态指示灯
    ui->netStatus_Label->setStyleSheet("background-color: rgb(37,231,18)");
    ui->netStatus_Label->setText("主站连接");
    this->initializeParamCommand();
}
void CommunicationController::disconnected()
{
    qDebug()<<"连接断开"<<endl;
    // 开始重连计时器
    this->connectTimer->start();
    // 连接状态指示灯
    ui->netStatus_Label->setStyleSheet("background-color: rgb(255,0,0)");
    ui->netStatus_Label->setText("主站断开");
    ui->slaveStatus_Label->setStyleSheet("background-color: rgb(255,0,0)");
    ui->slaveStatus_Label->setText("从站掉线");
}
void CommunicationController::toConnect()
{
    QHostAddress hostAddress(this->ip);
    this->tcpSocket->connectToHost(hostAddress, this->port);
    this->tcpSocket->waitForConnected(2); //wait 2ms
}
void CommunicationController::receiveMessages()
{
    int ret = this->tcpSocket->read((char*)&this->tcpRecvMessage,sizeof(this->tcpSendMessage));
    if(ret !=   sizeof(this->tcpSendMessage))
        qDebug() <<  " 接收的数据包有误 不是预设固定帧格式的大小";
    QString str_data = QString::fromLocal8Bit(this->tcpRecvMessage.data); //char[] 转 string
    QJsonDocument jsonDocument = QJsonDocument::fromJson(str_data.toLocal8Bit().data());//string 转 json
    switch (this->tcpRecvMessage.commandNum)
    {
    case Response_ChangeController: // 更换控制器
        this->responseChangeController(jsonDocument["result"].toBool(),jsonDocument["controlLaw"].toInt());
        break;
    case Response_ChangePlanner: // 更换规划器
        this->responseChangePlanner(jsonDocument["result"].toBool(),jsonDocument["planner"].toInt());
        break;
    case Response_SlaveConnect: // 询问从站状态
        this->responseSlaveConnect(jsonDocument["connect"].toBool());
        break;
    case Response_Start: // 示教器开机初始化
        this->responseStart(jsonDocument["connect"].toBool(), jsonDocument["controlLaw"].toInt(), jsonDocument["planner"].toInt(), jsonDocument["space"].toInt(), jsonDocument["runSpeed"].toInt(), jsonDocument["jogspeed"].toInt(), "panda");
        break;
    case Response_ChangeVel: // 修改速度
        this->responseChangeVel(jsonDocument["result"].toBool());
        break;
    case Response_BackToZero: // 回零
        this->responseBackToZero(jsonDocument["result"].toBool());
        break;
    case Response_Position: // 查询位置
        this->responsePosition(jsonDocument["result"].toBool(), jsonDocument);
        break;
    case Response_JogMove: // 点动开始
        //
        break;
    case Response_JogStop: // 点动停止
        //
        break;
    case Response_ChangeSpace: // 坐标系
        this->responseChangeSpace(jsonDocument["result"].toBool(),jsonDocument["space"].toInt());
        break;
    default:
        break;
    }
    memset(this->tcpRecvMessage.data, 0, sizeof(this->tcpRecvMessage.data));
}
// 网络通讯(非槽函数)
void CommunicationController::sendMessages(uint16_t commandNum, const QString &messages)
{
    if(tcpSocket->state() != tcpSocket->ConnectedState)
        return;
    this->tcpSendMessage.commandNum = commandNum;
    //qstring转char[]
    qstrncpy(this->tcpSendMessage.data, (messages.toUtf8()).constData(), sizeof(this->tcpSendMessage.data));
    this->tcpSocket->write(QByteArray((char*)&this->tcpSendMessage, sizeof(this->tcpSendMessage)));
    memset(this->tcpSendMessage.data, 0, sizeof(this->tcpSendMessage.data));
}
bool CommunicationController::resetConnect(const QString &ip_in,int port_in)
{
    this->connectTimer->stop();
    this->ip = ip_in;
    this->port = port_in;

    //更改配置文件
    QJsonObject jsonObject;
    jsonObject["ControllerIP"] = ip_in;
    jsonObject["Port"] = port_in;
    setJsonObjectToFile(TeachBoxJsonPath, jsonObject);

    //更换连接地址
    if (tcpSocket->state() == tcpSocket->ConnectedState)
    {
        qDebug() << "断开连接";
        this->tcpSocket->disconnectFromHost();
        this->tcpSocket->close();
    }
    QHostAddress hostAddress(this->ip);
    this->connectTimer->start();
    return true;
}

// 定时器命令
void CommunicationController::checkSlaveConnectCommand()
{
    QJsonObject jsonObject;
    this->sendMessages(Ask_SlaveConnect, QString(QJsonDocument(jsonObject).toJson()));
}
void CommunicationController::getPositionCommand()
{
    QJsonObject jsonObject;
    this->sendMessages(Ask_Position, QString(QJsonDocument(jsonObject).toJson()));
}
// 操作命令
void CommunicationController::initializeParamCommand()
{
    QJsonObject jsonObject;
    this->sendMessages(Start, QString(QJsonDocument(jsonObject).toJson()));
}
void CommunicationController::changeControllerCommand(int index)
{
    QJsonObject jsonObject;
    jsonObject["controlLaw"] = index;
    //json to qstring
    this->sendMessages(Request_ChangeController, QString(QJsonDocument(jsonObject).toJson()));
}
void CommunicationController::changePlannerCommand(int index)
{
    QJsonObject jsonObject;
    jsonObject["planner"] = index;
    //json to qstring
    this->sendMessages(Request_ChangePlanner, QString(QJsonDocument(jsonObject).toJson()));
}
void CommunicationController::changeSpaceCommand(int index)
{
    QJsonObject jsonObject;
    jsonObject["space"] = index;
    //json to qstring
    qDebug()<<"changeSpaceCommand"<<endl;
    this->sendMessages(Request_ChangeSpace, QString(QJsonDocument(jsonObject).toJson()));
}
void CommunicationController::changeVelocityCommand(int runVel, int jogVel)
{
    QJsonObject jsonObject;
    jsonObject["runSpeed"] = runVel;
    jsonObject["jogspeed"] = jogVel;
    this->sendMessages(Request_ChangeVel, QString(QJsonDocument(jsonObject).toJson()));
}
void CommunicationController::backToZeroCommand()
{
    QJsonObject jsonObject;
    this->sendMessages(Request_BackToZero, QString(QJsonDocument(jsonObject).toJson()));
}
void CommunicationController::stopMoveCommand()
{
    QJsonObject jsonObject;
    this->sendMessages(Request_StopMove, QString(QJsonDocument(jsonObject).toJson()));
}
void CommunicationController::startMoveCommand(Space planSpace, int queueNumber)
{
    QJsonObject jsonObject;
    QJsonArray jsonArray;
    switch (planSpace) {
    case Space::joint:
        for (int i = 0; i < this->referenceManager->jointRunningQueueGroup[0].size(); i++)
        {
            if(this->referenceManager->jointRunningQueueGroup[queueNumber - 1][i]->text().isEmpty())
            {
                qDebug()<<"[------]错误，空目标！！！";
                return;
            }
            jsonArray.append(this->referenceManager->jointRunningQueueGroup[queueNumber - 1][i]->text().toDouble());
        }
        jsonObject["planType"] = 0;
        jsonObject["q_d"] = jsonArray;
        break;
    case Space::cartesian:
        for (int i = 0; i < 6; i++)
        {
            if(this->referenceManager->cartesianRunningQueueGroup[queueNumber - 1][i]->text().isEmpty())
            {
                qDebug()<<"[------]错误，空目标！！！";
                return;
            }
            jsonArray.append(this->referenceManager->cartesianRunningQueueGroup[queueNumber - 1][i]->text().toDouble());
        }
        jsonObject["planType"] = 1;
        jsonObject["x_d"] = jsonArray;
        break;
    default:
        qDebug()<<"[------] error startMoveCommand"<<endl;
        break;
    }
    this->sendMessages(Request_CreateRunTask, QString(QJsonDocument(jsonObject).toJson()));
}
void CommunicationController::jogMoveCommand(int index,int dir)
{

    QJsonObject jsonObject;
    jsonObject["joint"] = index;
    jsonObject["space"] = ui->space_ComboBox->currentIndex();
    qDebug()<<ui->space_ComboBox->currentIndex()<<endl;
    jsonObject["dir"] = dir;
    this->sendMessages(Request_JogMove, QString(QJsonDocument(jsonObject).toJson()));
    this->jogTimer->start(50);
}
void CommunicationController::jogMoveCycleCommand()
{
    QJsonObject jsonObject;
    this->sendMessages(Request_JogCycleMove, QString(QJsonDocument(jsonObject).toJson()));
}
void CommunicationController::jogStopCommand(int index)
{
    QJsonObject jsonObject;
    this->sendMessages(Request_JogStop, QString(QJsonDocument(jsonObject).toJson()));
    this->jogTimer->stop();
}
//回应
void CommunicationController::responseChangeController(bool result, int controlLaw)
{
    //    if(result)
    this->ui->ctr_ComboBox->setCurrentIndex(controlLaw);
}
void CommunicationController::responseChangePlanner(bool result, int planner)
{
    //    if(result)
    this->ui->plan_ComboBox->setCurrentIndex(planner);
}
void CommunicationController::responseChangeSpace(bool result, int space)
{
    //    if(result)
    qDebug()<<"space "<<space<<endl;
    this->ui->space_ComboBox->setCurrentIndex(space);
}
void CommunicationController::responseSlaveConnect(bool isConnect)
{
    if(isConnect)
    {
        this->ui->slaveStatus_Label->setStyleSheet("background-color: rgb(37,231,18)");
        this->ui->slaveStatus_Label->setText("从站在线");
    }
    else
    {
        this->ui->slaveStatus_Label->setStyleSheet("background-color: rgb(255,0,0)");
        this->ui->slaveStatus_Label->setText("从站掉线");
    }
}
void CommunicationController::responseStart(bool isConnect, int controlLaw, int planner, int space, int runSpeed, int jogspeed, QString robotType)
{
    if(isConnect)
    {
        this->ui->slaveStatus_Label->setStyleSheet("background-color: rgb(37,231,18)");
        this->ui->slaveStatus_Label->setText("从站在线");
    }
    else
    {
        this->ui->slaveStatus_Label->setStyleSheet("background-color: rgb(255,0,0)");
        this->ui->slaveStatus_Label->setText("从站掉线");
    }
    this->ui->ctr_ComboBox->setCurrentIndex(controlLaw);
    this->ui->plan_ComboBox->setCurrentIndex(planner);
    this->ui->space_ComboBox->setCurrentIndex(space);
    this->ui->runVel_lab_2->setText(QString::number(runSpeed));
    this->ui->jogVel_lab_2->setText(QString::number(jogspeed));

    //点位信息
    QJsonObject taskJsonObject;
    getJsonObjectFromFile(TaskJsonPath, taskJsonObject);
    QJsonDocument taskJsonDocument(taskJsonObject);

    for (int i = 0; i < this->referenceManager->jointRunningQueueGroup[0].size(); i++)
    {
        this->referenceManager->jointRunningQueueGroup[0][i]->setText(QString::number(taskJsonDocument[robotType]["q1"][i].toDouble()));
        this->referenceManager->jointRunningQueueGroup[1][i]->setText(QString::number(taskJsonDocument[robotType]["q2"][i].toDouble()));
        this->referenceManager->jointRunningQueueGroup[2][i]->setText(QString::number(taskJsonDocument[robotType]["q3"][i].toDouble()));
        this->referenceManager->jointRunningQueueGroup[3][i]->setText(QString::number(taskJsonDocument[robotType]["q4"][i].toDouble()));
        this->referenceManager->jointRunningQueueGroup[4][i]->setText(QString::number(taskJsonDocument[robotType]["q5"][i].toDouble()));
        this->referenceManager->jointRunningQueueGroup[5][i]->setText(QString::number(taskJsonDocument[robotType]["q6"][i].toDouble()));
    }
}
void CommunicationController::responseChangeVel(bool result)
{

}
void CommunicationController::responseBackToZero(bool result)
{

}
void CommunicationController::responsePosition(bool result, QJsonDocument &jsonDocument)
{
    for (int i = 0; i < 7; ++i)
    {
        this->referenceManager->runPageNowJointPosition[i]->setText(QString::number(jsonDocument["q"][i].toDouble(),'f', 2));
    }
    for (int i = 0; i < 6; ++i)
    {
        this->referenceManager->runPageNowCartesianPosition[i]->setText(QString::number(jsonDocument["X"][i].toDouble(),'f', 2));
    }
}
