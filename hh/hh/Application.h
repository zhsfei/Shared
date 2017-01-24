#pragma once
#include "NetService.h"
#include "Player.h"
#include "ModuleManager.h"
#include "Log.h"
#include "PlayerMgr.h"
#include "MapManager.h"
#include "TimerManager.h"
#include "NetClient.h"
#include "AccountNetClient.h"
#include "DBNetClient.h"
#include "TimeWheel.h"

class Application : public NetObserver, public Singleton<Application>
{
public:
	Application();
	~Application();
	void run();
	void update(double diff);

	void OnConnect(ConnectPtr&);
	void OnDisConnect(ConnectPtr&);

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
private:
    AccountNetClient* m_pAccount;
    DBNetClient* m_pDatabase;

	NetService* m_pNetService;
	ModuleManager *m_pModuleMgr;
	LogService* m_pLogServer;
	TypeTable* m_pTypeTable;
	PlayerManager* m_pPlayerMgr;
	MapManager* m_pMapMgr;
	TimerManager* m_pTimerManager;
	timewheel::TimeWheel* m_pTimeWheel;

	DBService* m_pDBService;

	int64 m_dbid;
	int32 m_increment;
	int64 m_id;
};

#define sApp Application::getInstance()
#define sNetService Application::getInstance().GetNetService()
#define sTimer Application::getInstance().GetTimeWheel()