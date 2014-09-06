#include "Net/NetMgr.h"
#include "CCLuaEngine.h"


NetMgr::~NetMgr()
{
	//CSceneManager::sharedSceneManager()->removeLooper(this);
	m_isRunning = false;
	m_MessageQueue.clear(); 
	this->close();
}

void NetMgr::onCreate()
{
	auto t = std::thread(&NetMgr::updateMessage, this);
	t.detach();
}

void NetMgr::onConnected()
{
	if(m_connCB)
	{
		LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(m_connCB, 0);
	}
}

void NetMgr::onDisconnected()
{
	if(m_disconnCB)
	{
		LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(m_disconnCB, 0);
	}
}

void NetMgr::onConnectError()
{
	if(m_errCB)
	{
		LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(m_errCB, 0);
	}
}

void NetMgr::onConnectTimeout()
{
	if(m_timeoutCB)
	{
		LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(m_timeoutCB, 0);
	}
}

void NetMgr::onMessag()
{
	if(m_msgCB)
	{
		LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(m_msgCB, 0);
	}
}

const TMessage &NetMgr::getMessage()
{
	if(!m_MessageQueue.empty())
	{
		TMessage res = m_MessageQueue.front();
		m_MessageQueue.pop_front();
		return res;
	}
	return TMessage((const char*)"", 0, "");
}

void NetMgr::popMessage()
{
	if(!m_MessageQueue.empty())
	{
		m_MessageQueue.pop_front();
	}
}

void NetMgr::sendMessage(std::string &name, int len, char *content)
{
	uint16_t packLen = pack_len_bytes + pack_message_name_len_bytes + name.length() + len + 1;

	uint16_t messageNameLen = name.length() + 1;
	uint16_t messageContentLen = len;
	char *buf = new char[packLen];

	//write pakage len
	*((uint16_t*)buf) = packLen;

	//write message name len
	*((uint16_t*)(buf+pack_len_bytes)) = messageNameLen;

	//copy message name
	strcpy((buf + pack_len_bytes + pack_message_name_len_bytes), name.c_str());

	//copy message body
	int n =  pack_len_bytes + pack_message_name_len_bytes + messageNameLen;
	memcpy((buf + pack_len_bytes + pack_message_name_len_bytes + messageNameLen), content, messageContentLen);
	
	//STREAM stream(buf, packLen);
	this->write(buf, packLen);
	//this->write(stream);

	delete buf;
}

void NetMgr::registerCallBacks(int connCB, int disconnCB, int errCB, int timeoutCB, int msgCB)
{
	m_connCB = connCB;
	m_disconnCB = disconnCB;
	m_timeoutCB = timeoutCB;
	m_errCB = errCB;
	m_msgCB = msgCB;
}

bool NetMgr::httpRequest(std::string & url, int cbFunc)
{
	HttpRequest* request = new HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(NetMgr::httpResponse));
	
	char buf[16] = {0};
	sprintf(buf, "%x", cbFunc);
	std::string tag(buf);
    request->setTag(tag.c_str());

	requestMap[tag] = cbFunc;
	
    HttpClient::getInstance()->send(request);
    request->release();
	return true;
}

void NetMgr::httpResponse(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    
	bool ret = false;

	std::string tag(response->getHttpRequest()->getTag());
	if(!requestMap[tag])
	{
		return;
	}
    
    //int statusCode = response->getResponseCode();
    //char statusString[64] = {0};
    //sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    //log("response code: %d", statusCode);
    
	std::string value;
    if (!response->isSucceed()) 
    {
        ret = false;
        value = std::string(response->getErrorBuffer());
    }
	else
	{
		std::vector<char> *buffer = response->getResponseData();
		char *data = new char[buffer->size()+1];
		for (unsigned int i = 0; i < buffer->size(); i++)
		{
			data[i] = (*buffer)[i];
		}
		data[buffer->size()] = 0;
		value = std::string(data);
		delete [] data;
	}

	auto L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
	lua_pushboolean(L, ret);
  	lua_pushstring(L, value.c_str());
  	LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(requestMap[tag], 2);
	requestMap[tag] = 0;
	sender->destroyInstance();
}

void NetMgr::visit() 
{ 
	if (this->m_nConnectStatus == EConnecting) {
		int nRet = this->m_Sock.IsConnected();	
		if (nRet == 1) {
			this->m_nConnectStatus = EConnected;
			this->onConnected();
		} else if (nRet < 0) {
			this->m_nConnectStatus = EConnectError;
			this->onConnectError();
			this->close();
		} else {
			struct timeval ccTimeNow;
			gettimeofday(&ccTimeNow, NULL);
			if(ccTimeNow.tv_sec - m_ccConnectTime.tv_sec >= SOCK_CONNECT_TIMEOUT){
				this->m_nConnectStatus = EConnectTimeout;
				this->onConnectTimeout();
				this->close();
			}
		}
	}
	else if(this->m_nConnectStatus == EDisconnected)
	{
		this->onDisconnected();
		this->close();
	}
	if(!m_MessageQueue.empty())
	{
		
		this->onMessag();
	}
}

void NetMgr::updateMessage()
{
	while(m_isRunning)
	{
		if(this->m_nConnectStatus == EConnected)
		{
			while(m_Sock.IsReadable())
			{
				int nLen = m_Sock.Read(m_RecvBuffer, SOCK_RECVBUFFERSIZE);
				if (nLen == 0 || nLen  == SOCKET_ERROR) 
				{
					this->m_nConnectStatus = EDisconnected;
					break;
				} 
				else 
				{
					this->read(m_RecvBuffer, nLen);
				}
			}			
		}
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			Sleep(30);
		#else
			usleep(30);
		#endif
	}
}
