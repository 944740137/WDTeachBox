#include "h/config.h"
#include "teachBox.h"
#include "json/json.h"

#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    // 设置示教器大小与ui设计界面的大小一样
    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling,true);

    // QApplication
    QApplication a(argc, argv);

    // 其他线程（debug）

    // 加载配置参数
    QJsonObject configJsonObject;
    getJsonObjectFromFile(TeachBoxJsonPath, configJsonObject);
    Config config(configJsonObject["ControllerIP"].toString(), configJsonObject["Port"].toInt());

    // 界面任务线程
    Ui::MainWindow *ui = new Ui::MainWindow();
    TeachBox teachBox(config, ui);
    teachBox.show();

    // QApplication
    return a.exec();
}
