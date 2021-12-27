#include "sensor.h"


Sensor::Sensor(QString name, int node_id, int device_id, bool farenheit, uint32 home_id, QObject *parent) : QObject(parent)
{
    //DbManager db(path);
    //if (this->db.isOpen()) {
//        this->db.createTable();
  //  } else  {
//        qWarning() << "Database is not open!";
  //  }
    this->name = name;
    this->node_id = node_id;
    this->device_id = device_id;
    this->farenheit = farenheit;
    this->home_id = home_id;
}

Sensor::Sensor(QObject *parent) : QObject(parent)
{

}



