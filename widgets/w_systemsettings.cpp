#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QLabel>
#include <QSpacerItem>
#include <QTimer>

#include "w_systemsettings.h"
#include "build_number.h"
#include "tcpserver.h"
#include "sensor.h"

extern QString MY_HW_ADDR;
extern QString MY_IP_ADDR;
extern TCPServer tcpServer;
extern QList <Sensor*> g_sensorList;
extern QMap <QString, RPIDevice*> g_deviceList;



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
    grdDevStatus->setAlignment(Qt::AlignTop);

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
    QEngravedLabel *lblbattery = new QEngravedLabel("battery");


    lblSensor->setObjectName("gridHeader");
    lblid->setObjectName("gridHeader");
    lbllux->setObjectName("gridHeader");
    lblbattery->setObjectName("gridHeader");

    grdSensorStatus->setSpacing(0);
    grdSensorStatus->addWidget(lblSensor,0,0);
    grdSensorStatus->addWidget(lblid,0,1);
    grdSensorStatus->addWidget(lbllux,0,2);
    grdSensorStatus->addWidget(lblbattery,0,3);
    vboxSensorStatus->addLayout(grdSensorStatus);
    int senscnt = 1;
    for(Sensor *sensor : g_sensorList)
    {

        grdSensorStatus->addWidget(new QEngravedLabel(sensor->getName()),senscnt,0);
        grdSensorStatus->addWidget(new QEngravedLabel(QString::number(sensor->getNodeId())),senscnt,1);
        senscnt++;
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
