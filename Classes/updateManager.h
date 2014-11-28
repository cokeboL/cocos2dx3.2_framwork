#ifndef _UPDATE_MANAGER_H_
#define _UPDATE_MANAGER_H_
#include <string>
#include <mutex>
#include "cocos2d.h"
#include "extensions/ExtensionMacros.h"
#include "cocos-ext.h"

typedef void (*CallFunction)(); 
struct urlInfo
{
	int index;
	std::string url;
	std::string versionid;
	bool mustUpdate;
};
class updateManger
{
public:
	static updateManger* getInstance();
	updateManger();
	~updateManger();
	void startUpadate(int heroLv,int func);
	void startResouceUpadate(int heroLv,int func);
	void getUrls(char* url);
	void download(int func);
	void setPercent(int percent,double totalToDownload,double nowDownloaded);
	int m_downLoadCB;
private:
	int m_resouceUpdateLuaCB;
	int m_updateLuaCB;
	void downloadAndUncompress();
	bool downLoadData(std::string packageUrl);
	bool uncompressData();
	void setSearchPath();
	bool createDirectory(const char *path);
	std::map<int,urlInfo> _urls;
	std::map<int,urlInfo> _resouceUrls;
	std::map<int,urlInfo> _updateUrls;
	int _connectionTimeout;
	std::string _getData;
	bool _getDataFail;
	std::string _storagePath;
	static updateManger* m_pUpdateManger;
};

#endif