
#ifndef __CCNET_NETBEAN_H__
#define __CCNET_NETBEAN_H__

#include "socket.h"
#include "stream.h"
#include "CCLuaEngine.h"
#include "ThreadSafeQueue.h"

USING_NS_CC;

typedef CStream STREAM;
#define SOCK_CONNECT_TIMEOUT 10
#define SOCK_RECVBUFFERSIZE (1024 * 4)
#define CLIP_PACKET 1

#define DEFINE_SINGLE_FUNCTION(__TYPE__) \
static __TYPE__* sharedNetBean() { \
static __TYPE__ *pInstance = NULL; \
if(pInstance == NULL){ \
	pInstance = new __TYPE__(); \
} \
return pInstance; \
}

//message
class TMessage{
public:
	TMessage(const char *name, int len, char *content): m_Name(name), m_Len(len), m_Content(NULL)
	{
		if(len > 0)
		{
			m_Content = new char[len];
			memcpy(m_Content, content, len);
		}
	}
	TMessage(const TMessage &message): m_Name(message.m_Name), m_Len(message.m_Len), m_Content(NULL)
	{
		if(message.m_Len > 0)
		{
			m_Content = new char[message.m_Len];
			memcpy(m_Content, message.m_Content, message.m_Len);
		}
	}
	~TMessage()
	{
		if(m_Content)
		{
			delete [] m_Content;
		}
	}
	void release()
	{
		if(m_Content)
		{
			delete [] m_Content;
		}
	}
	std::string	m_Name;
	int m_Len;
	char *m_Content;
};

#define pack_len_bytes 2
#define pack_message_name_len_bytes 2
class CNetBean: public Node
{
public:
	//
	CNetBean();
	//
	virtual ~CNetBean();

public:
	//
	void setAddress(const char* ip, unsigned short port);

public:
	//
	virtual bool connect();
	//
	virtual bool isConnected();
	//
	virtual void close();
	//
	virtual void drive();
	//non block
	virtual void write(CStream &stream);
	//
	virtual void release();

public:
	
	virtual void onCreate(){};
	
	virtual void onConnected(){};
	
	virtual void onDisconnected(){};
	
	virtual void onConnectError(){};
	
	virtual void onConnectTimeout(){};
	
	//virtual TMessage &getNetMessage() = 0;

	//virtual void sendNetMessage(std::string &name, std::string &content) = 0;

	void execLuaFunc(std::string s)
	{
		if(s != std::string(""))
		{
			m_pLuaEngine->executeGlobalFunction(s.c_str());
		}
	}

	virtual void registerOnMessageScriptHandler(std::string s)
	{
		m_onMessageScriptHandler = s;
	}
	virtual void registerOnCreateScriptHandler(std::string s)
	{
		m_onCreateScriptHandler = s;
	}
	virtual void registerOnConnectedScriptHandler(std::string s)
	{
		m_onConnectedScriptHandler = s;
	}
	virtual void registerOnDisconnectedScriptHandler(std::string s)
	{
		m_onDisconnectedScriptHandler = s;
	}
	virtual void registerOnConnectErrorScriptHandler(std::string s)
	{
		m_onConnectErrorScriptHandler = s;
	}
	virtual void registerOnConnectTimeoutScriptHandler(std::string s)
	{
		m_onConnectTimeoutScriptHandler = s;
	}

private:
	//
	bool parseMessage();
	void read(char* buff, int len);

protected:
	//
	enum {
		ENULL			= 1,	//
		EConnecting		= 2,	//
		EConnected		= 3,	//
		EConnectTimeout = 4,	//
		EConnectError	= 5,	//
		EDisconnected	= 6		//
	} 
	m_nConnectStatus;

	//
	struct timeval m_ccConnectTime;

protected:
	//
	char m_RecvBuffer[SOCK_RECVBUFFERSIZE];

#if CLIP_PACKET
	//
	deque<char> m_vFrameDecodeBuffer;
	//
	uint16_t m_nRecvPackLength;
#endif

protected:
	//
	string m_nnAddress;
	//
	unsigned short m_nnPort;

protected:
	//
	CSocket	m_Sock;

protected:
	//list<TMessage> m_MessageQueue;
	ThreadSafeQueue<TMessage> m_MessageQueue;

	std::string m_onMessageScriptHandler;
	std::string m_onCreateScriptHandler;
	std::string m_onConnectedScriptHandler;
	std::string m_onDisconnectedScriptHandler;
	std::string m_onConnectErrorScriptHandler;
	std::string m_onConnectTimeoutScriptHandler;
	
	LuaEngine *m_pLuaEngine;

	bool m_isRunning;

};

#endif //__CCNET_NETBEAN_H__


