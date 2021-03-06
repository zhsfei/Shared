#pragma once
#include "netserver/NetService.h"
#include "Player.h"
#include "ModuleManager.h"
#include "log/Log.h"
#include "PlayerMgr.h"
#include "MapManager.h"
#include "timer/TimerManager.h"
#include "netserver/NetClient.h"
#include "AccountNetClient.h"
#include "DBNetClient.h"
#include "timer/TimeWheel.h"
#include "proto_data.h"

#include "mysql/MysqlStmt.h"
#include "CoroutineManager.h"
#include "NPCManager.h"

using namespace xlib;

class Application : public NetObserver, public Singleton<Application>
{
public:
	Application();
	~Application();
	void run();
	void update(double diff);

	void OnConnect(ConnectPtr&);
	void OnDisConnect(ConnectPtr&);

	void loadTable();
	void destoryTable();

	int64 getDBID();

    AccountNetClient& GetAccountConnect();
    DBNetClient& GetDataBaseConnect();

    void AllInitialOK();

    NetService& GetNetService()
    {
        return *m_pNetService;
    }

	timewheel::TimeWheel& GetTimeWheel()
	{
		return *m_pTimeWheel;
	}

	time_t GetServerTime()
	{
		return m_ServerTime;
	}

	MysqlStmt& GetMysqlStmt()
	{
		return *m_pMysqlStmt;
	}

	LogService& GetLogServer()
	{
		return *m_pLogServer;
	}
private:
    AccountNetClient* m_pAccount;
    DBNetClient* m_pDatabase;

	NetService* m_pNetService;
	ModuleManager *m_pModuleMgr;
	LogService* m_pLogServer;
	//TypeTable* m_pTypeTable;
	PlayerManager* m_pPlayerMgr;
	MapManager* m_pMapMgr;
	TimerManager* m_pTimerManager;
	timewheel::TimeWheel* m_pTimeWheel;
	CoroutineManager* m_pCoroutineManager;
	NPCManager* m_pNPCManager;

	MysqlStmt* m_pMysqlStmt;

	xlib::DBService* m_pDBService;

	int64 m_dbid;
	int32 m_increment;
	int64 m_id;

	time_t m_ServerTime;
};

#define sApp Application::getInstance()
#define sNetService Application::getInstance().GetNetService()
#define sTimer Application::getInstance().GetTimeWheel()
#define sStmt sApp.GetMysqlStmt()