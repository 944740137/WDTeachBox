#include "json/json.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>

bool getJsonObjectFromFile(const QString &fileName, QJsonObject &jsonObject)
{
    QFile file(fileName);
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "[getJsonObjectFromFile Error] open error.";
        return false;
    }

    QTextStream jsonStream(&file);
    QString jsonString = jsonStream.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8(), &jsonError);

    if (jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << "[getJsonObjectFromFile Error] Error parsing JSON: " << jsonError.errorString();
        return false;
    }

    if (!jsonDocument.isObject())
    {
        qDebug() << "[getJsonObjectFromFile Error] JSON document is not an object.";
        return false;
    }

    jsonObject = jsonDocument.object();
    return true;
}

bool setJsonObjectToFile(const QString &fileName, const QJsonObject &jsonObject)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "[setJsonObjectToFile Error] Could not open file for writing: " << file.errorString();
        return false;
    }

    QJsonDocument jsonDocument(jsonObject);
    QByteArray jsonData = jsonDocument.toJson();

    QTextStream jsonStream(&file);
    jsonStream << jsonData;

    return true;
}
