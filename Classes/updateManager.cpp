#include "updateManager.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include "rapidjson.h"
#include "document.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
#include "platform/android/jni/JniHelper.h"  
#include<jni.h>  
#endif
#include "unzip/unzip.h"
#include "CCLuaEngine.h"
using namespace cocos2d;
using namespace std;
#define BUFFER_SIZE    8192
#define MAX_FILENAME   512
updateManger::updateManger()
{
	_connectionTimeout = 3;
	_getDataFail = false;
	_storagePath = FileUtils::getInstance()->getWritablePath();
	setSearchPath();
}

updateManger::~updateManger()
{

}
void updateManger::setSearchPath()
{
	vector<string> searchPaths = FileUtils::getInstance()->getSearchPaths();
	vector<string>::iterator iter = searchPaths.begin();
	searchPaths.insert(iter, _storagePath);
	FileUtils::getInstance()->setSearchPaths(searchPaths);
}

updateManger* updateManger::getInstance()
{
	if(m_pUpdateManger == nullptr)
	{
		m_pUpdateManger = new updateManger();
	}
	return m_pUpdateManger;
}

updateManger* updateManger::m_pUpdateManger = nullptr;



static size_t getUrlsData(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	string *version = (string*)userdata;
	version->append((char*)ptr, size * nmemb);
	return (size * nmemb);
}
static size_t downLoadPackage(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	FILE *fp = (FILE*)userdata;
	size_t written = fwrite(ptr, size, nmemb, fp);
	return written;
}
int assetsManagerProgressFunc(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
	static int percent = 0;
	int tmp = (int)(nowDownloaded / totalToDownload * 100);
	if ( tmp != percent)
	{
		percent = tmp;
		if(percent<0)
			percent = 0;
		CCLOG("downloading... %d%%", percent);
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
			updateManger::getInstance()->setPercent(percent,totalToDownload,nowDownloaded);
		});
		
	}
	return 0;
}
void updateManger::getUrls(char* url)
{
	_urls.clear();
	_resouceUrls.clear();
	auto _curl = curl_easy_init();
	if (! _curl)
	{
		CCLOG("can not init curl");
		return;
	}
	_getData.clear();
	std::string dataUrl = url;
	CURLcode res;
	curl_easy_setopt(_curl, CURLOPT_URL, dataUrl.c_str());
	curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, getUrlsData);
	curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_getData);
	if (_connectionTimeout) curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, _connectionTimeout);
	curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
	res = curl_easy_perform(_curl);
	if (res != 0)
	{
		_getDataFail = true;
		curl_easy_cleanup(_curl);
	}
	//解析urlstr 
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(_getData.c_str());
	if (doc.HasParseError() || !doc.IsArray())
	{
		CCLog("doc.HasParseError()");
		return;
	}
	for (int i = 1 ;i < doc.Size();i++)
	{
		rapidjson::Value &valu = doc[i];
		int a= 0;
		urlInfo data;
		data.index = valu[a++].GetInt();
		data.url = valu[a++].GetString();
		data.versionid = valu[a++].GetString();
		int mustGetUpdate = valu[a++].GetInt();
		if(mustGetUpdate == 0)
		{
			data.mustUpdate = false;
		}
		else
		{
			data.mustUpdate = true;
		}
		if(data.index<=100)
			_resouceUrls.insert(std::pair<int,urlInfo>(data.index,data));
		else
			_urls.insert(std::pair<int, urlInfo>(data.index, data));
	}
	curl_easy_cleanup(_curl);
}
void updateManger::startUpadate(int heroLv,int func)
{
	m_updateLuaCB = func;
	bool getUpadateUrl = false;
	bool needUpdate = false;
	bool updateBack = false;
	bool mustUpdate = false;
	_updateUrls.clear();
	if(_urls.empty()&&_getDataFail == true)
	{
		CCLOG("获取更新包失败");
		cocos2d::LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
		stack->pushBoolean(getUpadateUrl);
		stack->pushBoolean(needUpdate);
		stack->pushBoolean(updateBack);
		stack->pushBoolean(mustUpdate);
		stack->executeFunctionByHandler(m_updateLuaCB, 4);
		stack->clean();
		return;
	}
	getUpadateUrl = true;
	std::map<int,urlInfo>::iterator it2 = _urls.begin();
	int currversionId = UserDefault::getInstance()->getIntegerForKey("currversionId",100);
	for (;it2 != _urls.end();it2 ++)
	{
		if(it2->first > currversionId)
		{
			_updateUrls.insert(std::pair<int,urlInfo>(it2->first,it2->second));
		}
	}
	if(_updateUrls.empty())
	{
		CCLOG("无需更新");
		cocos2d::LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
		stack->pushBoolean(getUpadateUrl);
		stack->pushBoolean(needUpdate);
		stack->pushBoolean(updateBack);
		stack->pushBoolean(mustUpdate);
		stack->executeFunctionByHandler(m_updateLuaCB, 4);
		stack->clean();
		return;
	}
	needUpdate = true;

	std::map<int,urlInfo>::iterator it = _resouceUrls.begin();
	for (;it != _resouceUrls.end(); it++)
	{
		char key[100];
		sprintf(key,"resource%d",it->first);
		bool resourceUpdate = UserDefault::getInstance()->getBoolForKey(key,false);
		if(resourceUpdate == false)
		{
			if(heroLv >= 10)
			{
				mustUpdate = true;
				break;
			}
		}
	}
	std::map<int,urlInfo>::iterator it3 = _updateUrls.begin();
	for(;it3 != _updateUrls.end();it3++)
	{

		if(it3->second.mustUpdate)
		{
			mustUpdate = true;
			break;
		}
	}
	cocos2d::LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
	stack->pushBoolean(getUpadateUrl);
	stack->pushBoolean(needUpdate);
	stack->pushBoolean(updateBack);
	stack->pushBoolean(mustUpdate);
	stack->executeFunctionByHandler(m_updateLuaCB, 4);
	stack->clean();
}
void updateManger::startResouceUpadate(int heroLv,int func)
{
	m_resouceUpdateLuaCB = func;
	bool getUpadateUrl = false;
	bool needUpdate = false;
	bool updateBack = false;
	bool mustUpdate = false;
	_updateUrls.clear();
	if(_resouceUrls.empty()&&_getDataFail == true)
	{
		CCLOG("获取更新包失败");
		cocos2d::LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
		stack->pushBoolean(getUpadateUrl);
		stack->pushBoolean(needUpdate);
		stack->pushBoolean(updateBack);
		stack->pushBoolean(mustUpdate);
		stack->executeFunctionByHandler(m_resouceUpdateLuaCB, 4);
		stack->clean();
		return;
	}
	getUpadateUrl = true;
	std::map<int,urlInfo>::iterator it = _resouceUrls.begin();
	for (;it != _resouceUrls.end(); it++)
	{
		char key[100];
		sprintf(key,"resource%d",it->first);
		bool resourceUpdate = UserDefault::getInstance()->getBoolForKey(key,false);
		if(resourceUpdate == false)
		{
			_updateUrls.insert(std::pair<int,urlInfo>(it->first,it->second));
		}
	}
	std::map<int,urlInfo>::iterator it2 = _urls.begin();
	if(_updateUrls.empty())
	{
		CCLOG("无需更新");
		cocos2d::LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
		stack->pushBoolean(getUpadateUrl);
		stack->pushBoolean(needUpdate);
		stack->pushBoolean(updateBack);
		stack->pushBoolean(mustUpdate);
		stack->executeFunctionByHandler(m_resouceUpdateLuaCB, 4);
		stack->clean();
		return;
	}
	needUpdate = true;
	std::map<int,urlInfo>::iterator it3 = _updateUrls.begin();
	for(;it3 != _updateUrls.end();it3++)
	{
		if(it3->first <=100&&heroLv < 10)
		{
			updateBack = true;
			break;
		}
	}
	it3 = _updateUrls.begin();
	for(;it3 != _updateUrls.end();it3++)
	{
		if(it3->second.mustUpdate)
		{
			mustUpdate = true;
			break;
		}
	}
	cocos2d::LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
	stack->pushBoolean(getUpadateUrl);
	stack->pushBoolean(needUpdate);
	stack->pushBoolean(updateBack);
	stack->pushBoolean(mustUpdate);
	stack->executeFunctionByHandler(m_resouceUpdateLuaCB, 4);
	stack->clean();
}
void updateManger::download(int func)
{
	m_downLoadCB = func;
	auto t = std::thread(&updateManger::downloadAndUncompress, this);
	t.detach();
}
void updateManger::downloadAndUncompress()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
	JavaVM *vm;   
	JNIEnv *env;   
	vm = JniHelper::getJavaVM();   
	JavaVMAttachArgs thread_args;   
	thread_args.name = "download";   
	thread_args.version = JNI_VERSION_1_4;   
	thread_args.group = NULL;   
	vm->AttachCurrentThread(&env, &thread_args);  
#endif 
	std::map<int,urlInfo>::iterator it = _updateUrls.begin();
	for (;it != _updateUrls.end(); it++)
	{
		if(!downLoadData(it->second.url))
		{
			CCLOG("download fail %d",it->first);
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
				cocos2d::LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
				stack->pushBoolean(true);
				stack->pushInt(0);
				stack->pushBoolean(false);
				stack->executeFunctionByHandler(m_downLoadCB, 3);
				stack->clean();
			});
			return;
		}
		if (!uncompressData())
		{
			CCLOG("uncompress fail %d",it->first);
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
				cocos2d::LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
				stack->pushBoolean(true);
				stack->pushInt(0);
				stack->pushBoolean(false);
				stack->executeFunctionByHandler(m_downLoadCB, 3);
				stack->clean();
			});
			return;
		}
		if(it->first<=100)
		{
			char key[100];
			sprintf(key,"resource%d",it->first);
			UserDefault::getInstance()->setBoolForKey(key,true);
		}
		else
		{
			UserDefault::getInstance()->setIntegerForKey("currversionId",it->first);
		}
		UserDefault::getInstance()->flush();
		if(it->second.versionid.compare("0") != 0)
		{
			UserDefault::getInstance()->setStringForKey("versionid",it->second.versionid);
			UserDefault::getInstance()->flush();
		}
	}
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
		cocos2d::LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
		stack->pushBoolean(false);
		stack->pushInt(0);
		stack->pushBoolean(true);
		stack->executeFunctionByHandler(m_downLoadCB, 3);
		stack->clean();
	});
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
	vm->DetachCurrentThread();
#endif
}	
void updateManger::setPercent(int percent,double totalToDownload,double nowDownloaded)
{
	CCLOG("setPercent");
	cocos2d::LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
	stack->pushBoolean(false);
	stack->pushInt(percent);
	stack->pushBoolean(false);
	stack->pushLong(totalToDownload);
	stack->pushLong(nowDownloaded);
	stack->executeFunctionByHandler(m_downLoadCB, 5);
	stack->clean();
}
bool updateManger::downLoadData(std::string packageUrl)
{
	int index = packageUrl.find_last_of('/');
	std::string packageName;
	if(index != -1)
	{
		packageName = packageUrl.substr(index+1,packageUrl.length());
	}
	else
	{
		packageName = packageUrl;
	}
	UserDefault::getInstance()->setStringForKey("downurl",packageName);
	const string outFileName = _storagePath +"loadPackage.zip";
	FILE *fp = fopen(outFileName.c_str(), "wb");
	if (! fp)
	{
		CCLOG("can not create file %s", outFileName.c_str());
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
			cocos2d::LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
			stack->pushBoolean(true);
			stack->pushInt(0);
			stack->pushBoolean(false);
			stack->executeFunctionByHandler(m_downLoadCB, 3);
			stack->clean();
		});

		return false;
	}
	auto _curl = curl_easy_init();
	if (! _curl)
	{
		CCLOG("can not init curl");
		return false;
	}
	CURLcode res;
	curl_easy_setopt(_curl, CURLOPT_URL, packageUrl.c_str());
	curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, downLoadPackage);
	curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, false);
	curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION,assetsManagerProgressFunc);
	curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA, this);
	curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
	res = curl_easy_perform(_curl);
	curl_easy_cleanup(_curl);
	if (res != 0)
	{
		CCLOG("error when download package");
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
			cocos2d::LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
			stack->pushBoolean(true);
			stack->pushInt(0);
			stack->pushBoolean(false);
			stack->executeFunctionByHandler(m_downLoadCB, 3);
			stack->clean();
		});
		fclose(fp);
		return false;
	}
	CCLOG("succeed downloading package %s", packageUrl.c_str());
	fclose(fp);
	return true;
}
bool updateManger::uncompressData()
{
	const string outFileName = _storagePath +"loadPackage.zip";
	unzFile zipfile = unzOpen(outFileName.c_str());
	if (! zipfile)
	{
		CCLOG("can not open downloaded zip file %s", outFileName.c_str());
		return false;
	}
	// Get info about the zip file
	unz_global_info global_info;
	if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
	{
		CCLOG("can not read file global info of %s", outFileName.c_str());
		unzClose(zipfile);
		
		return false;
	}

	// Buffer to hold data read from the zip file
	char readBuffer[BUFFER_SIZE];

	CCLOG("start uncompressing");
	// Loop to extract all files.
	uLong i;
	for (i = 0; i < global_info.number_entry; ++i)
	{
		// Get info about current file.
		unz_file_info fileInfo;
		char fileName[MAX_FILENAME];
		if (unzGetCurrentFileInfo(zipfile,
			&fileInfo,
			fileName,
			MAX_FILENAME,
			nullptr,
			0,
			nullptr,
			0) != UNZ_OK)
		{
			CCLOG("can not read file info");
			unzClose(zipfile);
			return false;
		}

		const string fullPath = _storagePath + fileName;

		// Check if this entry is a directory or a file.
		const size_t filenameLength = strlen(fileName);
		if (fileName[filenameLength-1] == '/')
		{
			// Entry is a direcotry, so create it.
			// If the directory exists, it will failed scilently.
			if (!createDirectory(fullPath.c_str()))
			{
				CCLOG("can not create directory %s", fullPath.c_str());
				unzClose(zipfile);
				return false;
			}
		}
		else
		{
			//There are not directory entry in some case.
			//So we need to test whether the file directory exists when uncompressing file entry
			//, if does not exist then create directory
			const string fileNameStr(fileName);

			size_t startIndex=0;

			size_t index=fileNameStr.find("/",startIndex);

			while(index != std::string::npos)
			{
				const string dir=_storagePath+fileNameStr.substr(0,index);

				FILE *out = fopen(dir.c_str(), "r");

				if(!out)
				{
					if (!createDirectory(dir.c_str()))
					{
						CCLOG("can not create directory %s", dir.c_str());
						unzClose(zipfile);
						return false;
					}
					else
					{
						CCLOG("create directory %s",dir.c_str());
					}
				}
				else
				{
					fclose(out);
				}

				startIndex=index+1;

				index=fileNameStr.find("/",startIndex);

			}



			// Entry is a file, so extract it.

			// Open current file.
			if (unzOpenCurrentFile(zipfile) != UNZ_OK)
			{
				CCLOG("can not open file %s", fileName);
				unzClose(zipfile);
				return false;
			}

			// Create a file to store current file.
			FILE *out = fopen(fullPath.c_str(), "wb");
			if (! out)
			{
				CCLOG("can not open destination file %s", fullPath.c_str());
				unzCloseCurrentFile(zipfile);
				unzClose(zipfile);
				return false;
			}

			// Write current file content to destinate file.
			int error = UNZ_OK;
			do
			{
				error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
				if (error < 0)
				{
					CCLOG("can not read zip file %s, error code is %d", fileName, error);
					unzCloseCurrentFile(zipfile);
					unzClose(zipfile);
					return false;
				}

				if (error > 0)
				{
					fwrite(readBuffer, error, 1, out);
				}
			} while(error > 0);

			fclose(out);
		}

		unzCloseCurrentFile(zipfile);

		// Goto next entry listed in the zip file.
		if ((i+1) < global_info.number_entry)
		{
			if (unzGoToNextFile(zipfile) != UNZ_OK)
			{
				CCLOG("can not read next file");
				unzClose(zipfile);
				return false;
			}
		}
	}
	CCLOG("end uncompressing");
	unzClose(zipfile);
	return true;
}
bool updateManger::createDirectory(const char *path)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	mode_t processMask = umask(0);
	int ret = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
	umask(processMask);
	if (ret != 0 && (errno != EEXIST))
	{
		return false;
	}

	return true;
#else
	BOOL ret = CreateDirectoryA(path, nullptr);
	if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
	{
		return false;
	}
	return true;
#endif
}