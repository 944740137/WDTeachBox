#include "messageManager.h"
#include <QMessageBox>


typedef std::map<int, MessageContent> MessageContentMap;
MessageContentMap messageContentMap = {
    {IP_ERROR ,{"网络设置", "IP格式错误"}}
    };

void messageCritical(QWidget *parent,int messageNum)
{
    QMessageBox::critical(parent, messageContentMap[messageNum].reminderTitle, messageContentMap[messageNum].reminderText);
}

void messageAbout(QWidget *parent,int messageNum)
{
    QMessageBox::about(parent, messageContentMap[messageNum].reminderTitle, messageContentMap[messageNum].reminderText);
}

//void messageCritical()
//{
//    QMessageBox::critical(this, "Critical消息框", "这是一个Critical消息框！");
//}

//void messageCritical()
//{
//    QMessageBox::critical(this, "Critical消息框", "这是一个Critical消息框！");
//}
