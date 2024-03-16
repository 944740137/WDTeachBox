#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
bool getJsonObjectFromFile(const QString &fileName, QJsonObject &josnObject);
bool setJsonObjectToFile(const QString &fileName, const QJsonObject &jsonObject);
