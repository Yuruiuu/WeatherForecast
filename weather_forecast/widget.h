#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <weatherdata.h>
#include <QPainter>
#include <QTimer>
#include "WeatherTool.h"
#include "weatherdata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    virtual bool eventFilter(QObject* watched, QEvent* event);

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void contextMenuEvent(QContextMenuEvent *event);
    void getWeatherInfo(QNetworkAccessManager*);
    void parseJson(QByteArray&);
    void setLabelContent();
    void paintSunRiseSet();
    void paintCurve();

private slots:
    void slot_exitApp();
    void replyFinished(QNetworkReply*);

    void on_refreshBt_clicked();

    void on_toolButtonsearchBt_clicked();

private:
    Ui::Widget *ui;
    QMenu* exitMenu;//右键退出菜单
    QAction* exitAct;//推出的行为
    QPoint mPos;//窗口移动的点

    //UI
    QList<QLabel *> forecast_week_list;         //星期
    QList<QLabel *> forecast_date_list;         //日期
    QList<QLabel *> forecast_aqi_list;          //天气指数
    QList<QLabel *> forecast_type_list;         //天气
    QList<QLabel *> forecast_typeIco_list;      //天气图标
    QList<QLabel *> forecast_high_list;         //高温
    QList<QLabel *> forecast_low_list;          //低温

    //网络请求
    QString url;        //接口链接
    QString city;       //访问的城市
    QString cityTmp;    //临时存放城市变量，防止输入错误城市的时候，原来的城市名称还在。
    WeatherTool tool;   //天气工具对象
    QNetworkAccessManager* manager;

    //本地数据
    Today today;
    Forecast forecast[6];

    static const QPoint sun[2];
    static const QRect sunRizeSet[2];
    static const QRect rect[2];
    QTimer* sunTimer;
};
#endif // WIDGET_H
