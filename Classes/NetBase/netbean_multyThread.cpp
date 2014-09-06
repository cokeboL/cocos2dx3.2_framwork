#include "netbean.h"

CNetBean::CNetBean():
m_nnPort(0),
m_nConnectStatus(ENULL),
m_isRunning(false)
{
#if CLIP_PACKET
	m_nRecvPackLength = 0;
	m_pLuaEngine = LuaEngine::getInstance();
#endif
}


CNetBean::~CNetBean(){}

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
	//Node::release();

	this->close();
	delete this;
}

void CNetBean::write(CStream &stream)
{
	//check status
	if( this->m_nConnectStatus != EConnected ) {
		return;
	}
	//check io is alive
	if( m_Sock.IsWritable() ) 
	{
		//pack length
		int length = stream.size();
#if CLIP_PACKET
		char* data = stream.flush();
#else
		char* data = stream.flush();
#endif
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
#if CLIP_PACKET
		//delete buff;
#endif
	} 
	else 
	{
		//log
		CCLOG("## [DEBUG] Write Disconnected if( m_Sock.IsWritable() )");
	}
}

bool CNetBean::parseMessage()
{
	//check pack recv
	if(this->m_nRecvPackLength == 0) {
		//read length of pack head
		if(this->m_vFrameDecodeBuffer.size() > pack_len_bytes) {
			//read 4 char to int
			this->m_nRecvPackLength = 0;
			for(int i = 0; i < pack_len_bytes; i++) {
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
	if(readable_size >= this->m_nRecvPackLength) {
		//to stream buffer
		
		//to delelte 4 char of pack length
		int packLen = 0;
		for(int i = 0; i < pack_len_bytes; i++)
		{
			packLen |= (uint16_t(this->m_vFrameDecodeBuffer[0] & 0xff) << (i*8));
			this->m_vFrameDecodeBuffer.pop_front();
		}
		
		int messageNameLen = 0;
		for(int i = 0; i < pack_message_name_len_bytes; i++) {
			//messageNameLen <<= 8;
			messageNameLen |= (uint16_t(this->m_vFrameDecodeBuffer[0] & 0xff) << (i*8));
			this->m_vFrameDecodeBuffer.pop_front();
		}

		int idx;
		char *messageName = new char[messageNameLen];
		for(idx = 0; idx < messageNameLen; idx++) {
			messageName[idx] = this->m_vFrameDecodeBuffer.front();
			this->m_vFrameDecodeBuffer.pop_front();
		}
		//messageName[messageNameLen] = 0;

		int contentLen = packLen - pack_len_bytes - pack_message_name_len_bytes - messageNameLen;
		char *messageContent = new char[contentLen];
		//read data from buffer
		for(idx = 0; idx < contentLen; idx++) {
			messageContent[idx] = this->m_vFrameDecodeBuffer.front();
			this->m_vFrameDecodeBuffer.pop_front();
		}
		//messageContent[idx] = 0;
		
		
		this->m_nRecvPackLength = 0;


		this->m_MessageQueue.push_back(TMessage((const char*)messageName, contentLen, messageContent));
		//execLuaFunc(m_onMessageScriptHandler);

		delete messageName;
		delete messageContent;

		return true;
	}
	return false;
}

void CNetBean::read(char* buff, int len)
{
#if CLIP_PACKET
	//add data to buffer
	for(int idx = 0; idx < len; idx++ ) {
		this->m_vFrameDecodeBuffer.push_back(m_RecvBuffer[idx]);
	}
	while(this->parseMessage());
	//check pack recv
	//if(this->m_nRecvPackLength == 0) {
	//	//read length of pack head
	//	if(this->m_vFrameDecodeBuffer.size() > pack_len_bytes) {
	//		//read 4 char to int
	//		this->m_nRecvPackLength = 0;
	//		for(int i = 0; i < pack_len_bytes; i++) {
	//			//this->m_nRecvPackLength <<= 8;
	//			this->m_nRecvPackLength |= (uint16_t((this->m_vFrameDecodeBuffer[i] & 0xff)) << (i*8));
	//		}
	//	} else {
	//		//there is no 4 bytes in buffer
	//		return;
	//	}
	//}
	//int readable_size = this->m_vFrameDecodeBuffer.size();// - pack_len_bytes;
	////if readable
	//if(readable_size >= this->m_nRecvPackLength) {
	//	//to stream buffer
	//	
	//	//to delelte 4 char of pack length
	//	int packLen = 0;
	//	for(int i = 0; i < pack_len_bytes; i++)
	//	{
	//		packLen |= (uint16_t(this->m_vFrameDecodeBuffer[0] & 0xff) << (i*8));
	//		this->m_vFrameDecodeBuffer.pop_front();
	//	}
	//	
	//	int messageNameLen = 0;
	//	for(int i = 0; i < pack_message_name_len_bytes; i++) {
	//		//messageNameLen <<= 8;
	//		messageNameLen |= (uint16_t(this->m_vFrameDecodeBuffer[0] & 0xff) << (i*8));
	//		this->m_vFrameDecodeBuffer.pop_front();
	//	}

	//	int idx;
	//	char *messageName = new char[messageNameLen];
	//	for(idx = 0; idx < messageNameLen; idx++) {
	//		messageName[idx] = this->m_vFrameDecodeBuffer.front();
	//		this->m_vFrameDecodeBuffer.pop_front();
	//	}
	//	//messageName[messageNameLen] = 0;

	//	int contentLen = packLen - pack_len_bytes - pack_message_name_len_bytes - messageNameLen;
	//	char *messageContent = new char[contentLen];
	//	//read data from buffer
	//	for(idx = 0; idx < contentLen; idx++) {
	//		messageContent[idx] = this->m_vFrameDecodeBuffer.front();
	//		this->m_vFrameDecodeBuffer.pop_front();
	//	}
	//	//messageContent[idx] = 0;
	//	
	//	
	//	this->m_nRecvPackLength = 0;


	//	this->m_MessageQueue.push_back(TMessage(std::string(messageName), contentLen, messageContent));
	//	//execLuaFunc(m_onMessageScriptHandler);

	//	delete messageName;
	//	delete messageContent;

	//}
#else
	//make stream to logic
	CStream stream(buff, len);
	//call back to virtual function 
	this->onMessage(stream);
#endif

}

void CNetBean::drive()
{
	//connect successed
	while(m_isRunning){
	if(this->m_nConnectStatus == EConnected){
		//Read Buffer
		while(m_Sock.IsReadable())
		{
			int nLen = m_Sock.Read(m_RecvBuffer, SOCK_RECVBUFFERSIZE);
			//check error
			if (nLen == 0 || nLen  == SOCKET_ERROR) {
				//change connecting status
				this->m_nConnectStatus = EDisconnected;
				//call back to virtual function
				//this->onDisconnected();
				//release socket
				//this->close();
				//stop while and loop;
				break;
			} else {
				//read data
				this->read(m_RecvBuffer, nLen);
			}
		}
	}
	//sock was keeping connecting status
	//else if (this->m_nConnectStatus == EConnecting) {
	//	//check connected status of unblock socket
	//	int nRet = this->m_Sock.IsConnected();	
	//	if (nRet == 1) {
	//		//set the connecting status
	//		this->m_nConnectStatus = EConnected;
	//		//call back to virtual function
	//		this->onConnected();
	//	} else if (nRet < 0) {	//error
	//		//set the connecting status
	//		this->m_nConnectStatus = EConnectError;
	//		//call back to virtual function
	//		this->onConnectError();
	//		//close socket
	//		this->close();
	//	} else {
	//		//if it didn't finish the work at time
	//		struct timeval ccTimeNow;
	//		gettimeofday(&ccTimeNow, NULL);
	//		if(ccTimeNow.tv_sec - m_ccConnectTime.tv_sec >= SOCK_CONNECT_TIMEOUT){
	//			//set the connecting status
	//			this->m_nConnectStatus = EConnectTimeout;
	//			//call back to virtual function
	//			this->onConnectTimeout();
	//			//release socket
	//			this->close();
	//		}
	//	}
	//}
	else
	{
		//sleep(0.001);
	}
	}
	/*
	if(!m_MessageQueue.empty())
	{
		execLuaFunc(m_onMessageScriptHandler);
	}
	*/
}



