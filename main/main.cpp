#include "config.h"
#include "mainwindow.h"
#include "json/json.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
    // 设置示教器大小与ui设计界面的大小一样
    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling,true);

    // QApplication
    QApplication a(argc, argv);

    // 其他线程（debug）

    // 加载参数
    QJsonObject jsonObject;
    getJsonObjectFromFile(TeachBoxJsonPath, jsonObject);
    Config config(jsonObject["ControllerIP"].toString(), jsonObject["Port"].toInt());

    // 界面任务线程
    Ui::MainWindow *ui = new Ui::MainWindow();
    MainWindow w(config, ui);
    w.show();

    return a.exec();
}
