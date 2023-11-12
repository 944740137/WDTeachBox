#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "message/message.h"
#include "json/json.h"
extern ClientComThread *clientComThread;

MainWindow::MainWindow(const QString &ipAddress_in, int port_in, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->clientCom = new ClientCom(ipAddress_in, port_in, ui);

    // 网络设置
    ui->IP_LineEdit->setText(ipAddress_in);
    ui->port_LineEdit->setText(QString::number(port_in));
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
    ui->netStatus_Label->setStyleSheet("background-color: rgb(255,0,0)");
    ui->netStatus_Label->setText("断开");
    //
}

MainWindow::~MainWindow()
{
    delete ui;
    delete clientCom;
    clientComThread->quit();
}
// 功能列表
void MainWindow::on_fun_ListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(previous==nullptr)
        return;
    if(previous->text()=="设置" && current->text()!="设置")
    {
        this->resetNetConfigInterface();
    }
}
// 网络设置
void MainWindow::resetNetConfigInterface()
{
    ui->IP_LineEdit->setText(this->clientCom->ip);
    ui->port_LineEdit->setText(QString::number(this->clientCom->port));
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
        if(ip==this->clientCom->ip&&port.toInt()==this->clientCom->port)
            return;
        this->clientCom->resetConnect(ip,port.toInt());
    }
}

// tmp
void MainWindow::on_tmp_clicked()
{

}

void MainWindow::on_tmp2_clicked()
{

}


void MainWindow::on_ctr_ComboBox_activated(int index)
{
    this->clientCom->changeCtronller(index);
}
