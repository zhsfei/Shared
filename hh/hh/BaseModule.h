#pragma once
#include <string>
class Player;

class BaseModule
{
public:
	BaseModule(const std::string& name, Player* pOwner) :m_bInitOk(false)
	{
		m_ModuleName = name;
		m_pOwner = pOwner;
	}
	virtual ~BaseModule(void){};

public:
	std::string GetModuleName(){ return m_ModuleName; }

	virtual bool Init(){ return true; }

	bool IsInitOk(){ return m_bInitOk; }

	Player* GetOwner(){ return m_pOwner; }

	virtual void OnLogin(){ return; }


protected:
	void setInitOk();

protected:
	std::string m_ModuleName;
	Player* m_pOwner;

	bool m_bInitOk;
};

class ModuleFactory
{
public:
	ModuleFactory(const std::string& name);

	/**
	* @brief		Desconstructor
	* @details		ע�⣬������������Ϊ�麯��
	* @remarks
	*/
	virtual ~ModuleFactory(void);

public:
	virtual BaseModule* CreateModule(Player* pOwner) = 0;

	std::string GetModuleName(){ return m_ModuleName; }

protected:
	std::string m_ModuleName;
};