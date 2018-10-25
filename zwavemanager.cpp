#include "zwavemanager.h"
#include "commandrouter.h"

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "Options.h"
#include "Manager.h"
#include "Driver.h"
#include "Node.h"
#include "Group.h"
#include "Notification.h"
#include "value_classes/ValueStore.h"
#include "value_classes/Value.h"
#include "value_classes/ValueBool.h"
#include "platform/Log.h"
#include "Defs.h"
#include "zone.h"

#include <QDebug>

extern QMap<QString, Zone> gZoneMap;
extern QMap <int, int> g_nodeValues;


using namespace OpenZWave;

bool temp = false;


static uint32 g_homeId = 0;
static bool   g_initFailed = false;

typedef struct
{
    uint32			m_homeId;
    uint8			m_nodeId;
    bool			m_polled;
    list<ValueID>	m_values;
}NodeInfo;

static list<NodeInfo*> g_nodes;
static pthread_mutex_t g_criticalSection;
static pthread_cond_t  initCond  = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t initMutex = PTHREAD_MUTEX_INITIALIZER;

//-----------------------------------------------------------------------------
// <GetNodeInfo>
// Return the NodeInfo object associated with this notification
//-----------------------------------------------------------------------------
NodeInfo* GetNodeInfo
(
        Notification const* _notification
        )
{
    uint32 const homeId = _notification->GetHomeId();
    uint8 const nodeId = _notification->GetNodeId();
    for( list<NodeInfo*>::iterator it = g_nodes.begin(); it != g_nodes.end(); ++it )
    {
        NodeInfo* nodeInfo = *it;
        if( ( nodeInfo->m_homeId == homeId ) && ( nodeInfo->m_nodeId == nodeId ) )
        {
            return nodeInfo;
        }
    }

    return NULL;
}

//-----------------------------------------------------------------------------
// <OnNotification>
// Callback that is triggered when a value, group or node changes
//-----------------------------------------------------------------------------
void OnNotification
(
        Notification const* _notification,
        void* _context
        )
{
    // Must do this inside a critical section to avoid conflicts with the main thread
    pthread_mutex_lock( &g_criticalSection );

    switch( _notification->GetType() )
    {
    case Notification::Type_ValueAdded:
    {
        if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
        {
            // Add the new value to our list
            nodeInfo->m_values.push_back( _notification->GetValueID() );
        }
        break;
    }

    case Notification::Type_ValueRemoved:
    {
        if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
        {
            // Remove the value from out list
            for( list<ValueID>::iterator it = nodeInfo->m_values.begin(); it != nodeInfo->m_values.end(); ++it )
            {
                if( (*it) == _notification->GetValueID() )
                {
                    nodeInfo->m_values.erase( it );
                    break;
                }
            }
        }
        break;
    }

    case Notification::Type_ValueChanged:
    {
        // One of the node values has changed
        pthread_mutex_lock( &g_criticalSection );
        if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
        {
            nodeInfo = nodeInfo;		// placeholder for real action
            for( list<ValueID>::iterator it2 = nodeInfo->m_values.begin();
                 it2 != nodeInfo->m_values.end(); ++it2 )
            {
                ValueID v = *it2;
                if( v.GetCommandClassId() == 0x25)
                {
                    bool value;
                    Manager::Get()->GetValueAsBool(v, &value);
                    pthread_mutex_unlock( &g_criticalSection );
                    g_nodeValues.insert(nodeInfo->m_nodeId, (int) value);
                    qDebug() << "Node state changed:" << nodeInfo->m_nodeId << value;
                    for (Zone zone : gZoneMap.values())
                    {
                        if (zone.getLightById(nodeInfo->m_nodeId) != NULL)
                        {
                            zone.getLightById(nodeInfo->m_nodeId)->updateLevel(value);
                            zone.getLightById(nodeInfo->m_nodeId)->setLastUpdateLocal(true);
                        }
                    }

                    //    return value;
                }
                if( v.GetCommandClassId() == 0x26)
                {
                    switch (v.GetType())
                    {
                    case ValueID::ValueType_Bool:
                    {
                        bool value;
                        Manager::Get()->GetValueAsBool(v, &value);
                        //qDebug() << nodeInfo->m_nodeId << value << v.GetType() << QString::fromStdString(Manager::Get()->GetValueLabel(v));
                        break;
                    }

                    case ValueID::ValueType_Byte:
                    {
                        uint8 value;
                        Manager::Get()->GetValueAsByte(v, &value);
                        if (v.GetIndex() == 0) {
                            g_nodeValues.insert(nodeInfo->m_nodeId, (int) value);
                            for (Zone zone : gZoneMap.values())
                            {
                                if (zone.getLightById(nodeInfo->m_nodeId) != NULL)
                                {
                                    zone.getLightById(nodeInfo->m_nodeId)->updateLevel(value);
                                    zone.getLightById(nodeInfo->m_nodeId)->setLastUpdateLocal(true);
                                }
                            }
                            qDebug() << nodeInfo->m_nodeId << value << v.GetIndex() << v.GetType() << QString::fromStdString(Manager::Get()->GetValueLabel(v));
                        }
                        break;
                    }

                    default: {
                        // qDebug() << nodeInfo->m_nodeId << "UNKNOWN" << v.GetType() << QString::fromStdString(Manager::Get()->GetValueLabel(v));
                    }
                    }

                    pthread_mutex_unlock( &g_criticalSection );
                    //for (Zone zone : gZoneMap.values())
                    //{
                    //if (zone.getLightById(nodeInfo->m_nodeId) != NULL)
                    //    zone.getLightById(nodeInfo->m_nodeId)->updateState(value);
                    //}

                    //    return value;
                }

                if( v.GetCommandClassId() == 0x27)
                {

                    //qDebug() << "SA" << v.GetCommandClassId() << "NODE" << nodeInfo->m_nodeId << "TYPE" << v.GetType() << "INDEX" << v.GetIndex() << QString::fromStdString(Manager::Get()->GetValueLabel(v));
                }
            }
        }
        break;
    }

    case Notification::Type_Group:
    {
        // One of the node's association groups has changed
        if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
        {
            nodeInfo = nodeInfo;		// placeholder for real action
        }
        break;
    }

    case Notification::Type_NodeAdded:
    {
        // Add the new node to our list
        NodeInfo* nodeInfo = new NodeInfo();
        nodeInfo->m_homeId = _notification->GetHomeId();
        nodeInfo->m_nodeId = _notification->GetNodeId();
        nodeInfo->m_polled = false;
        g_nodes.push_back( nodeInfo );
        if (temp == true) {
            Manager::Get()->CancelControllerCommand( _notification->GetHomeId() );
        }
        break;
    }

    case Notification::Type_NodeRemoved:
    {
        // Remove the node from our list
        uint32 const homeId = _notification->GetHomeId();
        uint8 const nodeId = _notification->GetNodeId();
        for( list<NodeInfo*>::iterator it = g_nodes.begin(); it != g_nodes.end(); ++it )
        {
            NodeInfo* nodeInfo = *it;
            if( ( nodeInfo->m_homeId == homeId ) && ( nodeInfo->m_nodeId == nodeId ) )
            {
                g_nodes.erase( it );
                delete nodeInfo;
                break;
            }
        }
        break;
    }

    case Notification::Type_NodeEvent:
    {
        // We have received an event from the node, caused by a
        // basic_set or hail message.
        if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
        {
            nodeInfo = nodeInfo;		// placeholder for real action
        }
        break;
    }

    case Notification::Type_PollingDisabled:
    {
        if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
        {
            nodeInfo->m_polled = false;
        }
        break;
    }

    case Notification::Type_PollingEnabled:
    {
        if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
        {
            nodeInfo->m_polled = true;
        }
        break;
    }

    case Notification::Type_DriverReady:
    {
        g_homeId = _notification->GetHomeId();
        break;
    }

    case Notification::Type_DriverFailed:
    {
        g_initFailed = true;
        pthread_cond_broadcast(&initCond);
        break;
    }

    case Notification::Type_AwakeNodesQueried:
    case Notification::Type_AllNodesQueried:
    case Notification::Type_AllNodesQueriedSomeDead:
    {
        pthread_cond_broadcast(&initCond);
        break;
    }

    case Notification::Type_DriverReset:
    case Notification::Type_Notification:
    case Notification::Type_NodeNaming:
    case Notification::Type_NodeProtocolInfo:
    case Notification::Type_NodeQueriesComplete:
    default:
    {
    }
    }

    pthread_mutex_unlock( &g_criticalSection );
}

bool getZWaveState(int nodeid)
{
    //ValueID vIndex1;
    //ValueID vIndex2;
    pthread_mutex_lock( &g_criticalSection );
    for( list<NodeInfo*>::iterator it = g_nodes.begin(); it != g_nodes.end(); ++it )
    {
        NodeInfo* nodeInfo = *it;
        if( nodeInfo->m_nodeId != nodeid ) continue;

        for( list<ValueID>::iterator it2 = nodeInfo->m_values.begin();
             it2 != nodeInfo->m_values.end(); ++it2 )
        {
            ValueID v = *it2;
            //string val = Manager::Get()->GetValueLabel(v);
            if( v.GetCommandClassId() == 0x25)
            {
                bool value;
                Manager::Get()->GetValueAsBool(v, &value);
                pthread_mutex_unlock( &g_criticalSection );
                return value;
            }
            if( v.GetCommandClassId() == 0x26)
            {
                if (v.GetIndex() == 0)
                {
                    //vIndex1 = v;
                    //uint8 val2 = 50;
                    //Manager::Get()->SetValue(v, val2);
                    //qDebug() << "setting value" << val2;
                    //qDebug() << "CC" << v.GetCommandClassId() << "NODE" << nodeInfo->m_nodeId << "TYPE" << v.GetType() << "INDEX" << v.GetIndex() << QString::fromStdString(Manager::Get()->GetValueLabel(v));

                }

                if (v.GetIndex() == 2)
                {
                    //vIndex2 = v;
                    //bool val2 = true;
                    //Manager::Get()->SetValue(v, val2);
                    //qDebug() << "applying value";
                    //qDebug() << "CC" << v.GetCommandClassId() << "NODE" << nodeInfo->m_nodeId << "TYPE" << v.GetType() << "INDEX" << v.GetIndex() << QString::fromStdString(Manager::Get()->GetValueLabel(v));
                }
            }
        }
    }
    pthread_mutex_unlock( &g_criticalSection );
    return false;
}

void setZWaveToggle(bool value, int nodeid)
{
    pthread_mutex_lock( &g_criticalSection );
    for( list<NodeInfo*>::iterator it = g_nodes.begin(); it != g_nodes.end(); ++it )
    {
        NodeInfo* nodeInfo = *it;
        if( nodeInfo->m_nodeId != nodeid ) continue;
        for( list<ValueID>::iterator it2 = nodeInfo->m_values.begin();
             it2 != nodeInfo->m_values.end(); ++it2 )
        {
            ValueID v = *it2;
            if( v.GetCommandClassId() == 0x25)
            {
                Manager::Get()->SetValue(v, value);
                break;
            }
            if( v.GetCommandClassId() == 0x26)
            {
                qDebug() << "DIMMER" << v.GetCommandClassId() << "NODE" << nodeInfo->m_nodeId << "TYPE" << v.GetType() << "INDEX" << v.GetIndex() << QString::fromStdString(Manager::Get()->GetValueLabel(v));

                uint8 val2 = 0;
                if (value == true)
                    val2 = 100;
                Manager::Get()->SetValue(v, val2);
                break;
            }
        }
    }
    pthread_mutex_unlock( &g_criticalSection );
}

void init_zwave()
{
    pthread_mutexattr_t mutexattr;

    pthread_mutexattr_init ( &mutexattr );
    pthread_mutexattr_settype( &mutexattr, PTHREAD_MUTEX_RECURSIVE );
    pthread_mutex_init( &g_criticalSection, &mutexattr );
    pthread_mutexattr_destroy( &mutexattr );

    pthread_mutex_lock( &initMutex );

    // Create the OpenZWave Manager.
    // The first argument is the path to the config files (where the manufacturer_specific.xml file is located
    // The second argument is the path for saved Z-Wave network state and the log file.  If you leave it NULL
    // the log file will appear in the program's working directory.
    Options::Create( "/usr/local/etc/openzwave/", "/tmp/", "" );
    Options::Get()->AddOptionInt( "SaveLogLevel", LogLevel_Detail );
    Options::Get()->AddOptionInt( "QueueLogLevel", LogLevel_Debug );
    Options::Get()->AddOptionInt( "DumpTrigger", LogLevel_Error );
    Options::Get()->AddOptionBool( "ConsoleOutput", false );
    Options::Get()->AddOptionInt( "PollInterval", 100 );
    //Options::Get()->AddOptionInt( "RetryTimeout", 30 );
    Options::Get()->AddOptionBool( "IntervalBetweenPolls", true );
    Options::Get()->AddOptionBool( "AssumeAwake", true );
    Options::Get()->AddOptionBool("ValidateValueChanges", true);
    Options::Get()->Lock();

    Manager::Create();

    // Add a callback handler to the manager.  The second argument is a context that
    // is passed to the OnNotification method.  If the OnNotification is a method of
    // a class, the context would usually be a pointer to that class object, to
    // avoid the need for the notification handler to be a static.
    Manager::Get()->AddWatcher( OnNotification, NULL);

    // Add a Z-Wave Driver
    // Modify this line to set the correct serial port for your PC interface.


    string port = "/dev/ttyACM0";

    Manager::Get()->AddDriver( port );


    // Now we just wait for either the AwakeNodesQueried or AllNodesQueried notification,
    // then write out the config file.
    // In a normal app, we would be handling notifications and building a UI for the user.
    pthread_cond_wait( &initCond, &initMutex );

    // Since the configuration file contains command class information that is only
    // known after the nodes on the network are queried, wait until all of the nodes
    // on the network have been queried (at least the "listening" ones) before
    // writing the configuration file.  (Maybe write again after sleeping nodes have
    // been queried as well.)
    if( !g_initFailed )
    {



    }


    return;
}


void zwave_destroy()
{
    Driver::DriverData data;
    Manager::Get()->GetDriverStatistics( g_homeId, &data );
    printf("SOF: %d ACK Waiting: %d Read Aborts: %d Bad Checksums: %d\n", data.m_SOFCnt, data.m_ACKWaiting, data.m_readAborts, data.m_badChecksum);
    printf("Reads: %d Writes: %d CAN: %d NAK: %d ACK: %d Out of Frame: %d\n", data.m_readCnt, data.m_writeCnt, data.m_CANCnt, data.m_NAKCnt, data.m_ACKCnt, data.m_OOFCnt);
    printf("Dropped: %d Retries: %d\n", data.m_dropped, data.m_retries);

    Manager::Get()->RemoveDriver("/dev/ttyACM0");
    Manager::Get()->RemoveWatcher( OnNotification, NULL );
    Manager::Destroy();
    Options::Destroy();
    pthread_mutex_destroy( &g_criticalSection );
}
