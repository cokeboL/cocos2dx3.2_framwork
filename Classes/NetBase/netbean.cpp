#include "netbean.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif


CNetBean::CNetBean():
m_nnPort(0),
m_nConnectStatus(ENULL),
m_isRunning(false),
m_nRecvPackLength(0)
{
}


CNetBean::~CNetBean()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	Sleep(100);
#else
	usleep(100);
#endif
}

void CNetBean::setAddress(const char* ip, unsigned short port)
{
	this->m_nnPort = port;
	this->m_nnAddress = ip;
}

bool CNetBean::connect()
{
	//there is connected or connecting 
	if(this->m_nConnectStatus == EConnected || this->m_nConnectStatus == EConnecting){
		return false;
	}
	//validate value
	if(this->m_nnAddress == "" || this->m_nnPort == 0) {
		return false;
	}
	if(!m_Sock.Create()) {
		return false;
	}
	if(!m_Sock.Connect(this->m_nnAddress.c_str(), this->m_nnPort)) {
		return false;
	}
	//set the connecting status
	this->m_nConnectStatus = EConnecting;
	//get the connect time of started.
	gettimeofday(&m_ccConnectTime, NULL);
	//call back to virtual function 
	this->onCreate();

	return true;
}

bool CNetBean::isConnected()
{
	if(this->m_nConnectStatus == EConnected)
	{
		return true;
	}
	return false;
}

void CNetBean::close()
{
	this->m_Sock.Close();
	//this->m_nConnectStatus = EDisconnected;
	this->m_nConnectStatus = ENULL;
}


void CNetBean::release()
{
	this->close();
	delete this;
}

//void CNetBean::write(CStream &stream)
void CNetBean::write(char* data, uint16_t length)
{
	//check status
	if( this->m_nConnectStatus != EConnected ) {
		return;
	}
	//check io is alive
	if( m_Sock.IsWritable() ) 
	{
		//pack length
		//int length = stream.size();
		//char* data = stream.flush();
		if( length != 0 ) {
			int nLen = m_Sock.Write( data, length );
			if( nLen == SOCKET_ERROR ) {
				//set the connecting status
				this->m_nConnectStatus = EDisconnected;
				//call back to virtual function
				this->onDisconnected();
				//release socket
				this->close();
				//log
				CCLOG("## [DEBUG] Write Disconnected if(nLen == SOCKET_ERROR)");
			}
		}
	} 
	else 
	{
		CCLOG("## [DEBUG] Write Disconnected if( m_Sock.IsWritable() )");
	}
}

bool CNetBean::parseMessage()
{
	//check pack recv
	if(this->m_nRecvPackLength == 0) 
	{
		//read length of pack head
		if(this->m_vFrameDecodeBuffer.size() > pack_len_bytes) 
		{
			//read 4 char to int
			this->m_nRecvPackLength = 0;
			for(int i = 0; i < pack_len_bytes; i++) 
			{
				//this->m_nRecvPackLength <<= 8;
				this->m_nRecvPackLength |= (uint16_t((this->m_vFrameDecodeBuffer[i] & 0xff)) << (i*8));
			}
		} else {
			//there is no 4 bytes in buffer
			return false;
		}
	}
	int readable_size = this->m_vFrameDecodeBuffer.size();// - pack_len_bytes;
	//if readable
	if(readable_size >= this->m_nRecvPackLength) 
	{
		//to delelte 4 char of pack length
		int packLen = 0;
		for(int i = 0; i < pack_len_bytes; i++)
		{
			packLen |= (uint16_t(this->m_vFrameDecodeBuffer[0] & 0xff) << (i*8));
			this->m_vFrameDecodeBuffer.pop_front();
		}
		
		int messageNameLen = 0;
		for(int i = 0; i < pack_message_name_len_bytes; i++) 
		{
			messageNameLen |= (uint16_t(this->m_vFrameDecodeBuffer[0] & 0xff) << (i*8));
			this->m_vFrameDecodeBuffer.pop_front();
		}

		int idx;
		char *messageName = new char[messageNameLen];
		for(idx = 0; idx < messageNameLen; idx++) 
		{
			messageName[idx] = this->m_vFrameDecodeBuffer.front();
			this->m_vFrameDecodeBuffer.pop_front();
		}

		int contentLen = packLen - pack_len_bytes - pack_message_name_len_bytes - messageNameLen;
		char *messageContent = new char[contentLen];
		//read data from buffer
		for(idx = 0; idx < contentLen; idx++) 
		{
			messageContent[idx] = this->m_vFrameDecodeBuffer.front();
			this->m_vFrameDecodeBuffer.pop_front();
		}
		
		this->m_nRecvPackLength = 0;


		this->m_MessageQueue.push_back(TMessage((const char*)messageName, contentLen, messageContent));

		delete messageName;
		delete messageContent;

		return true;
	}
	return false;
}

void CNetBean::read(char* buff, int len)
{
	for(int idx = 0; idx < len; idx++ ) {
		this->m_vFrameDecodeBuffer.push_back(m_RecvBuffer[idx]);
	}
	while(this->parseMessage());
}




