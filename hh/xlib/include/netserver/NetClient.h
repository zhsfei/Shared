#pragma once

#include "../include/define/define.h"
#include "NetService.h"
#include "../include/timer/TimerManager.h"

#pragma warning (push)

#pragma warning (disable: 4251)


namespace xlib
{
	enum c_status
	{
		status_free,
		status_connect,
		status_disconnect,
	};

	template class _declspec(dllexport) std::basic_string<char>;

	class XDLL NetClient
	{
	public:
		NetClient(TimerManager* ptimer);
		virtual ~NetClient(void);

		struct PackData
		{
			void Release()
			{
				if (p != nullptr)
				{
					delete p;
					p = nullptr;
				}
			}
			PackData(int id, const char* pdata, int len, int _roleid)
			{
				messageid = id;
				p = new char[len];
				memcpy(p, pdata, len);
				length = len;
				roleid = _roleid;
			}

			int messageid;
			char*p;
			int length;
			int roleid;
		};

	public:
		virtual void registMessage();
		void RegisterMessage(int id, boost::function<void(PackPtr&)> sfunc);
		template<class... _Types >
		void Register(int id, _Types... arg)
		{
			m_pNetService->RegisterMessage(id, arg...);
		}

		bool ConnectTo(const char* ip, int port);

		bool Send(int messageid, const char* pdata, int length, int roleid = 0, bool bResend = false);
		template<typename T>
		bool Send(const T& t, unsigned int mesageid, int roleid = 0, bool bResend = false)
		{
			return Send(mesageid, (const char *)&t, sizeof(T), m_address, roleid);
		}

		const char* getAddress();

		const char* getIP(){ return m_ip.c_str(); }

		int getPort(){ return m_port; }

		void update();

	protected:
		virtual void OnConnect(ConnectPtr&);
		virtual void OnDisConnect(ConnectPtr&);

		void ReConnect();
	private:
		std::string m_ip;
		int m_port = 0;
		std::string m_address;
		NetService* m_pNetService;
		ConnectPtr m_pConnect;
		ConnectPtr m_pConnectTemp;
		TimerManager* m_pTimer;
		std::vector<PackData> m_pPackData;
		Timer* tTimer;
		int conn_status = status_free;
	};
}

#pragma warning (pop)