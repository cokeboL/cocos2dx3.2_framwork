
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
	TMessage(const char *name_, int len, char *content): name(name_), len(len), message(NULL)
	{
		if(len > 0)
		{
			message = new char[len];
			memcpy(message, content, len);
		}
	}
	TMessage(const TMessage &m): name(m.name), len(m.len), message(NULL)
	{
		if(m.len > 0)
		{
			message = new char[m.len];
			memcpy(message, m.message, m.len);
		}
	}
	~TMessage()
	{
		if(message)
		{
			delete [] message;
		}
	}
	
	std::string	name;
	int len;
	char *message;
};

#define pack_len_bytes 2
#define pack_message_name_len_bytes 2
class CNetBean: public Node
{
public:
	CNetBean();
	
	virtual ~CNetBean();

	void setAddress(const char* ip, unsigned short port);

	virtual bool connect();
	
	virtual bool isConnected();
	
	virtual void close();

	virtual void write(char*, uint16_t);
	
	virtual void release();
	
	virtual void onCreate(){};
	
	virtual void onConnected(){};
	
	virtual void onDisconnected(){};
	
	virtual void onConnectError(){};
	
	virtual void onConnectTimeout(){};
	
	void read(char* buff, int len);

private:
	bool parseMessage();

protected:
	
	enum {
		ENULL			= 1,	
		EConnecting		= 2,	
		EConnected		= 3,	
		EConnectTimeout = 4,	
		EConnectError	= 5,	
		EDisconnected	= 6		
	} 
	m_nConnectStatus;

	struct timeval m_ccConnectTime;

protected:
	
	char m_RecvBuffer[SOCK_RECVBUFFERSIZE];

	deque<char> m_vFrameDecodeBuffer;
	
	uint16_t m_nRecvPackLength;

protected:
	
	string m_nnAddress;
	
	unsigned short m_nnPort;

protected:
	
	CSocket	m_Sock;

protected:
	
	bool m_isRunning;

	ThreadSafeQueue<TMessage> m_MessageQueue;
};

#endif //__CCNET_NETBEAN_H__


