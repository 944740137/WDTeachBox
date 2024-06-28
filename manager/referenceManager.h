#ifndef REFERENCEMANAGER_H
#define REFERENCEMANAGER_H

#include <QMainWindow>
#include "ui_teachBox.h"

#include <QList>
#include <QLabel>

#include "h/config.h"
class ReferenceManager:public QObject
{
    /* 用到信号槽即需要此宏定义 */
//    Q_OBJECT
    friend class CommunicationController;
    friend class InterfaceController;

private:
    RobotType robotType;
    Ui::MainWindow *ui;
    QList<QLabel*> runPageNowJointPosition;
    QList<QLabel*> runPageNowCartesianPosition;
    QList<QList<QLineEdit*>> jointRunningQueueGroup;
    QList<QList<QLineEdit*>> cartesianRunningQueueGroup;
    QList<QPushButton*> runPageChangeMoveGoal;
    QList<QPushButton*> runPageTeachPosition;

public:
    ~ReferenceManager();
    ReferenceManager(Ui::MainWindow *ui, QWidget *parent = nullptr);
    ReferenceManager()= delete;
    ReferenceManager(const ReferenceManager &) = delete;
    void operator=(const ReferenceManager &) = delete;

private slots:
};
#endif // REFERENCEMANAGER_H
