#ifndef CommunicationController_H
#define CommunicationController_H
#include "config.h"

#include <QDebug>
#include <QHostAddress>
#include <QTcpSocket>
#include <QTimer>

#include "ui_mainwindow.h"

struct TcpMessage
{
    uint16_t commandNum;
    char data[512] = {0};
};

class CommunicationController:public QObject
{
    /* 用到信号槽即需要此宏定义 */
    Q_OBJECT

    friend class MainWindow;
private:

    Ui::MainWindow *ui;

    //从站状态查询定时器
    QTimer *checkoutSlaveTimer;

    // 网络通讯
    QTimer *connectTimer;
    QString ip;
    int port;
    QTcpSocket *tcpSocket;
    TcpMessage tcpSendMessage;
    TcpMessage tcpRecvMessage;

public:
    ~CommunicationController();
    CommunicationController(const Config &config, Ui::MainWindow *ui, QWidget *parent = nullptr);
    CommunicationController()= delete;
    CommunicationController(const CommunicationController &) = delete;
    void operator=(const CommunicationController &) = delete;

    // 网络通讯
    bool resetConnect(const QString &ip_in,int port);
    void sendMessages(uint16_t num, const QString &messages);

    // 操作命令
    void initializeParamCommand();// 初始化示教器值
    void getPositionCommand();
    void changeControllerCommand(int index);    // 切换速度，规控
    void changePlannerCommand(int index);
    void changeVelocityCommand(int runVel,int jogVel);
    void backToZeroCommand();
    void stopMoveCommand();

private slots:
    // 网络通讯
    void toConnect();
    void connected();
    void disconnected();
    void receiveMessages();

    // 定时器命令
    void checkSlaveConnectCommand();//从站状态查询
};
#endif // CLIENTCOM_H
