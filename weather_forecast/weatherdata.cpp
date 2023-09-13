#include "weatherdata.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDateTime>

Today::Today()
{
    date = "0000-00-00";
    city = "null";
    fl = u8"无数据";
    fx = u8"无数据";
    ganmao = u8"无数据";
    notice = u8"无数据";
    pm25 = u8"无数据";
    quality = u8"无数据";
    shidu = u8"无数据";
    sunrise = "00:00";
    sunset = "00:00";
    wendu = "null";
    type = u8"无数据";
}

Today &Today::operator=(const QJsonObject &jsObj)
{
    QString dateStr = jsObj.value("date").toString();
    date = QDate::fromString(dateStr, "yyyyMMdd").toString("yyyy-MM-dd");
    city = jsObj.value("cityInfo").toObject().value("city").toString();

    // 解析data
    QJsonObject dataObj = jsObj.value("data").toObject();
    shidu = dataObj.value("shidu").toString();
    pm25 = QString::number( dataObj.value("pm25").toDouble() );
    quality = dataObj.value("quality").toString();
    wendu = dataObj.value("wendu").toString() + u8"°";
    ganmao = dataObj.value("ganmao").toString();
    QJsonArray forecastArr = dataObj.value("forecast").toArray();
    QJsonObject todayObj = forecastArr.at(0).toObject();
    fx = todayObj.value("fx").toString();
    fl = todayObj.value("fl").toString();
    type = todayObj.value("type").toString();
    sunrise = todayObj.value("sunrise").toString();
    sunset = todayObj.value("sunset").toString();
    notice = todayObj.value("notice").toString();
    return *this;
}

Forecast::Forecast()
{
    aqi = "0";
    date = u8"00日星期0";
    week = u8"星期0";
    high = u8"高温 0.0℃";
    low = u8"低温 0.0℃";
    type = "undefined";
}

Forecast &Forecast::operator=(const QJsonObject &obj)
{
    date = obj.value("date").toString();
    week = obj.value("week").toString();
    high = obj.value("high").toString();
    low = obj.value("low").toString();
    aqi = QString::number( obj.value("aqi").toDouble() );
    type = obj.value("type").toString();
    return *this;
}
