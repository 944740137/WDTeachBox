#ifndef CLIENTCOM_H
#define CLIENTCOM_H
#include <QThread>
#include <QDebug>
#include <QHostAddress>
#include <QTcpSocket>
#include <QTimer>
#include "ui_mainwindow.h"

class ClientComThread: public QThread
{

public:
    ~ClientComThread();
    ClientComThread();

    ClientComThread(const ClientComThread &) = delete;
    void operator=(const ClientComThread &) = delete;

    void run();
};

struct TcpMessage
{
    uint16_t commandNum;
    char data[512] = {0};
};
class ClientCom:public QObject
{
    /* 用到信号槽即需要此宏定义 */
    Q_OBJECT

    friend class MainWindow;
private:
    Ui::MainWindow *ui;
    //从站状态查询定时器
    QTimer *checkoutSlaveTimer;

    QTimer *timer; // connect
    QString ip;
    int port;
    QTcpSocket *tcpSocket;
    TcpMessage tcpSendMessage;
    TcpMessage tcpRecvMessage;
public:
    ~ClientCom();
    ClientCom(const QString &ipAddress_in, int port_in, Ui::MainWindow *ui, QWidget *parent = nullptr);
    ClientCom()= delete;
    ClientCom(const ClientCom &) = delete;
    void operator=(const ClientCom &) = delete;

    //连接与收发
    bool resetConnect(const QString &ip_in,int port);
    void sendMessages(uint16_t num, const QString &messages);

    //功能
    void getPosition();
    void initialInformationInquiry();
    void changeCtronller(int index);
    void changePlanner(int index);
    void changeVel(int runVel,int jogVel);
    void backToZero();
    void stopMove();

private slots:
    void checkSlaveConnect();//从站状态查询
    void toConnect();
    void connected();
    void disconnected();
    void receiveMessages();

};
#endif // CLIENTCOM_H
