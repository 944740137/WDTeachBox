#ifndef CONFIG_H
#define CONFIG_H
#include <QString>

#define  TeachBoxJsonPath "/home/wd/workSpace/WDcontroller/config/teachBox.json"

struct Config
{
    Config(const QString & ip_in, int port_in) : ip(ip_in), port(port_in) {}
    QString ip;
    int port;
};
enum VelocityType
{
    jogVelocity = 0,
    runVelocity = 1
};

#endif // CONFIG_H
