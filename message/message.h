#ifndef MESSAGETIPS_H
#define MESSAGETIPS_H
#include <QWidget>
#include <QString>
# pragma execution_character_set("utf-8")

//网络
#define IP_ERROR 50


struct MessageContent
{
    QString reminderTitle;
    QString reminderText;
};

void messageCritical(QWidget *parent,int messageNum);
void messageAbout(QWidget *parent,int messageNum);

#endif // MESSAGETIPS_H


