#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QLabel>
#include <QSpacerItem>
#include <QTimer>
#include <QDateTime>

#include "w_systemsettings.h"
#include "build_number.h"
#include "tcpconnectionfactory.h"
#include "sensor.h"
#include "zwavemanager.h"

extern QString MY_HW_ADDR;
extern QString MY_IP_ADDR;
extern TCPConnectionFactory tcpServer;
extern QList <Sensor*> g_sensorList;
extern QMap <QString, RPIDevice*> g_deviceList;
extern uint32  g_homeId;
extern QString g_zwaveDriver;


SystemSettings::SystemSettings(QWidget *parent) : QWidget(parent)
{
    //statusList = new QEngravedList(this);
    //deviceList = new QEngravedList(this);

    //statusList->setObjectName("labelList");
    //statusList->setEnabled(false);
    //deviceList->setObjectName("labelList");
    //deviceList->setEnabled(false);

    QTimer *refreshTimer = new QTimer(this);
    QWidget *devStatus = new QWidget(this);
    QVBoxLayout *vboxDevStatus = new QVBoxLayout(devStatus);
    QGridLayout *grdDevStatus = new QGridLayout();
    vboxDevStatus->addLayout(grdDevStatus);
    QEngravedLabel *lblStatus = new QEngravedLabel("local device status");
    QEngravedLabel *lblZwave = new QEngravedLabel("N/A");
    lblStatus->setObjectName("gridHeader");
    grdDevStatus->setSpacing(0);
    grdDevStatus->addWidget(lblStatus,0,0,1,4);
    grdDevStatus->addWidget(new QEngravedLabel("build number"),1,0);
    grdDevStatus->addWidget(new QEngravedLabel(QString::number(BUILD)),1,1);
    grdDevStatus->addWidget(new QEngravedLabel("build date"),2,0);
    grdDevStatus->addWidget(new QEngravedLabel(QString(DATE)),2,1);
    grdDevStatus->addWidget(new QEngravedLabel("IP Address"),3,0);
    grdDevStatus->addWidget(new QEngravedLabel(QString(MY_IP_ADDR)),3,1);
    grdDevStatus->addWidget(new QEngravedLabel("mac Address"),4,0);
    grdDevStatus->addWidget(new QEngravedLabel(QString(MY_HW_ADDR)),4,1);
    grdDevStatus->addWidget(new QEngravedLabel("z-wave status"),5,0);
    grdDevStatus->addWidget(lblZwave ,5,1);
    grdDevStatus->setAlignment(Qt::AlignTop);

    connect(refreshTimer, &QTimer::timeout, [lblZwave]()
    {
       lblZwave->setText("Driver: "  + g_zwaveDriver + "\n"
                         + "ID: " + QString::number(g_homeId, 16)) ;
    });

    QWidget *deviceStatus = new QWidget(this);
    QVBoxLayout *vboxDeviceStatus = new QVBoxLayout(deviceStatus);
    QGridLayout *grdDeviceStatus = new QGridLayout();
    QEngravedLabel *lblName = new QEngravedLabel("name");
    QEngravedLabel *lblMac= new QEngravedLabel("mac");
    QEngravedLabel *lblip = new QEngravedLabel("ip");
    QEngravedLabel *lblVersion = new QEngravedLabel("version");

    lblName->setObjectName("gridHeader");
    lblMac->setObjectName("gridHeader");
    lblip->setObjectName("gridHeader");
    lblVersion->setObjectName("gridHeader");

    grdDeviceStatus->setSpacing(0);


    grdDeviceStatus->addWidget(lblName,0,0);
    grdDeviceStatus->addWidget(lblMac,0,1);
    grdDeviceStatus->addWidget(lblip,0,2);
    grdDeviceStatus->addWidget(lblVersion,0,3);
    vboxDeviceStatus->addLayout(grdDeviceStatus);
    int devcnt = 1;
    for(RPIDevice *device : g_deviceList)
    {

        grdDeviceStatus->addWidget(new QEngravedLabel(device->getName() + "\t"),devcnt,0);
        grdDeviceStatus->addWidget(new QEngravedLabel(device->getHwAddress() + "\t"),devcnt,1);
        QEngravedLabel *lblIP = new QEngravedLabel("-\t");
        QEngravedLabel *lblVersion = new QEngravedLabel("-");
        grdDeviceStatus->addWidget(lblIP,devcnt,2);
        grdDeviceStatus->addWidget(lblVersion,devcnt,3);
        devcnt++;
        connect(device, &RPIDevice::ipChanged, [lblIP,lblVersion,device](QString ip) {
            lblIP->setText(ip);
            lblVersion->setText(QString::number(device->getVersion()));
        });
    }
    grdDeviceStatus->setAlignment(Qt::AlignTop);


    QWidget *sensorStatus = new QWidget(this);
    QVBoxLayout *vboxSensorStatus = new QVBoxLayout(sensorStatus);
    QGridLayout *grdSensorStatus = new QGridLayout();
    QEngravedLabel *lblSensor = new QEngravedLabel("sensor");
    QEngravedLabel *lblid = new QEngravedLabel("id");
    QEngravedLabel *lbllux = new QEngravedLabel("lux");
    QEngravedLabel *lblrh = new QEngravedLabel("RH");
    QEngravedLabel *lbltemp = new QEngravedLabel("temp");
    QEngravedLabel *lblbattery = new QEngravedLabel("battery");
    QEngravedLabel *lblupdated = new QEngravedLabel("updated");

    lblSensor->setObjectName("gridHeader");
    lblid->setObjectName("gridHeader");
    lbllux->setObjectName("gridHeader");
    lblbattery->setObjectName("gridHeader");
    lblupdated->setObjectName("gridHeader");
    lblrh->setObjectName("gridHeader");
    lbltemp->setObjectName("gridHeader");

    grdSensorStatus->setSpacing(0);
    grdSensorStatus->addWidget(lblSensor,0,0);
    grdSensorStatus->addWidget(lblid,0,1);
    grdSensorStatus->addWidget(lbllux,0,2);
    grdSensorStatus->addWidget(lblrh,0,3);
    grdSensorStatus->addWidget(lbltemp,0,4);
    grdSensorStatus->addWidget(lblbattery,0,5);
    grdSensorStatus->addWidget(lblupdated,0,6);

    vboxSensorStatus->addLayout(grdSensorStatus);
    int senscnt = 1;
    for(Sensor *sensor : g_sensorList)
    {

        grdSensorStatus->addWidget(new QEngravedLabel(sensor->getName()),senscnt,0);
        grdSensorStatus->addWidget(new QEngravedLabel(QString::number(sensor->getNodeId())),senscnt,1);
        QEngravedLabel *sensupdate = new QEngravedLabel("");
        QEngravedLabel *sensbattery = new QEngravedLabel("");
        QEngravedLabel *senslux = new QEngravedLabel("");
        QEngravedLabel *sensrh = new QEngravedLabel("");
        QEngravedLabel *senstemp = new QEngravedLabel("");
        grdSensorStatus->addWidget(senslux,senscnt,2);
        grdSensorStatus->addWidget(sensrh,senscnt,3);
        grdSensorStatus->addWidget(senstemp,senscnt,4);
        grdSensorStatus->addWidget(sensbattery,senscnt,5);
        grdSensorStatus->addWidget(sensupdate,senscnt,6);

        senscnt++;
        connect(refreshTimer, &QTimer::timeout, [sensor, sensbattery,sensupdate,sensrh,senslux,senstemp]()
        {
            sensupdate->setText(QDateTime::fromSecsSinceEpoch(sensor->getLastUpdate()).toString());
            sensbattery->setText(QString::number(sensor->getBattery()));
            senslux->setText(QString::number(sensor->getLux()));
            sensrh->setText(QString::number(sensor->getHumidity()));
            senstemp->setText(QString::number(sensor->getTemperature()));
        });

    }
    grdSensorStatus->setAlignment(Qt::AlignTop);


    topWidget = new QWidget;
    contentLayout = new QGridLayout(topWidget);
    contentLayout->setAlignment(Qt::AlignTop);
    contentLayout->addWidget(new QEngravedLabel("device info"),0,0);
    contentLayout->addWidget(new QEngravedLabel("devices"),0,1);
    contentLayout->addWidget(new QEngravedLabel("sensors"),2,0);

    contentLayout->addWidget(devStatus,1,0);
    contentLayout->addWidget(deviceStatus,1,1);
    contentLayout->addWidget(sensorStatus,3,0);

    refreshTimer->setInterval(1000);
    refreshTimer->start();
    //connect(light, &Light::levelChanged, [slider, light](){
    //       slider->setValue(light->getLevel());
    //  });

    //connect(&tcpServer, &TCPServer::deviceReady, [](RPIDevice device){
    //    qDebug() << device.getIP();
    //lblIP->setText("device.getIP()");
    //    });

    //connect(&tcpServer,SIGNAL(deviceReady(RPIDevice)),this,SLOT(addDevice(RPIDevice)));
    //connect(&tcpServer,SIGNAL(deviceLost(RPIDevice)),this,SLOT(removeDevice(RPIDevice)));
}

void SystemSettings::reloadStyles()
{
    QString homeLocation = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QDir::setCurrent(homeLocation + "/.smah/assets");

    QFile File("main.css");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);
}
