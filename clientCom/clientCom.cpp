#include <QtWidgets/QWidget>
#include <QThread>
#include <QDebug>
#include "clientCom/clientCom.h"
#include "json/json.h"
#include "config.h"
#include "protocol.h"

ClientComThread::~ClientComThread()
{
}
ClientComThread::ClientComThread()
{
}
void ClientComThread::run()
{
    int i = 0;
    while(1)
    {
        i++;
        //        qDebug()<<" i"<<i<<endl;
        sleep(2);
    }
}


ClientCom::~ClientCom()
{

}
ClientCom::ClientCom(const QString &ipAddress_in, int port_in, Ui::MainWindow *ui, QWidget *parent):ip(ipAddress_in),
    port(port_in),timer(new QTimer(this)),tcpSocket(new QTcpSocket(this))
{
    this->checkoutSlaveTimer = new QTimer(this);
    connect(this->checkoutSlaveTimer, SIGNAL(timeout()), this, SLOT(checkSlaveConnect()));
    this->checkoutSlaveTimer->start(500);

    Q_UNUSED(parent);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(toConnect()));
    this->timer->start(3000);
    connect(this->tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(this->tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveMessages()));
    this->ui=ui;
}
void ClientCom::connected()
{
    qDebug()<<"连接成功"<<endl;
    // 停止重连计时器
    this->timer->stop();
    // 连接状态指示灯
    ui->netStatus_Label->setStyleSheet("background-color: rgb(37,231,18)");
    ui->netStatus_Label->setText("主站连接");
}
void ClientCom::disconnected()
{
    qDebug()<<"连接断开"<<endl;
    // 开始重连计时器
    this->timer->start();
    // 连接状态指示灯
    ui->netStatus_Label->setStyleSheet("background-color: rgb(255,0,0)");
    ui->netStatus_Label->setText("主站断开");
    ui->slaveStatus_Label->setStyleSheet("background-color: rgb(255,0,0)");
    ui->slaveStatus_Label->setText("从站掉线");
}
void ClientCom::toConnect()
{
    QHostAddress hostAddress(this->ip);
    this->tcpSocket->connectToHost(hostAddress, this->port);
    this->tcpSocket->waitForConnected(2); //wait 2ms
}
void ClientCom::receiveMessages()
{
    int ret = this->tcpSocket->read((char*)&this->tcpRecvMessage,sizeof(this->tcpSendMessage));
    if(ret !=   sizeof(this->tcpSendMessage))
        qDebug() <<  " 接收的数据包有误 不是预设固定帧格式的大小";
    QString str_data = QString::fromLocal8Bit(this->tcpRecvMessage.data); //char[] 转 string
    QJsonDocument jsonDocument = QJsonDocument::fromJson(str_data.toLocal8Bit().data());//string 转 json
    switch (this->tcpRecvMessage.commandNum)
    {
    case Response_ChangeController:
        if(!jsonDocument["result"].toBool())
        {
            qDebug()<<jsonDocument["error"].toString();
        }
        ui->ctr_ComboBox->setCurrentIndex(jsonDocument["controlLaw"].toInt());
        break;

    case Response_ChangePlanner:
        if(!jsonDocument["result"].toBool())
        {
            qDebug()<<jsonDocument["error"].toString();
        }
        ui->ctr_ComboBox->setCurrentIndex(jsonDocument["controlLaw"].toInt());
        break;

    case Response_SlaveConnect:
        if(jsonDocument["connect"].toBool())
        {
            ui->slaveStatus_Label->setStyleSheet("background-color: rgb(37,231,18)");
            ui->slaveStatus_Label->setText("从站在线");
        }
        else
        {
            ui->slaveStatus_Label->setStyleSheet("background-color: rgb(255,0,0)");
            ui->slaveStatus_Label->setText("从站掉线");
        }
        break;
    default:
        break;
    }
    memset(this->tcpRecvMessage.data, 0, sizeof(this->tcpRecvMessage.data));
}
void ClientCom::sendMessages(uint16_t commandNum, const QString &messages)
{
    if(tcpSocket->state() != tcpSocket->ConnectedState)
        return;
    this->tcpSendMessage.commandNum = commandNum;
    //qstring转char[]
    qstrncpy(this->tcpSendMessage.data, (messages.toUtf8()).constData(), sizeof(this->tcpSendMessage.data));
    this->tcpSocket->write(QByteArray((char*)&this->tcpSendMessage, sizeof(this->tcpSendMessage)));
    memset(this->tcpSendMessage.data, 0, sizeof(this->tcpSendMessage.data));
}
bool ClientCom::resetConnect(const QString &ip_in,int port_in)
{
    this->timer->stop();
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
    this->timer->start();
    return true;
}
void ClientCom::changeCtronller(int index)
{
    QJsonObject jsonObject;
    jsonObject["controlLaw"] = index;
    //json to qstring
    this->sendMessages(Request_ChangeController, QString(QJsonDocument(jsonObject).toJson()));
}
void ClientCom::changePlanner(int index)
{
    QJsonObject jsonObject;
    jsonObject["planner"] = index;
    //json to qstring
    this->sendMessages(Request_ChangePlanner, QString(QJsonDocument(jsonObject).toJson()));
}
void ClientCom::checkSlaveConnect()
{
    QJsonObject jsonObject;
    this->sendMessages(Ask_SlaveConnect, QString(QJsonDocument(jsonObject).toJson()));
}

