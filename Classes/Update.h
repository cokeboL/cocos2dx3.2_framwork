#ifndef _UPDATE_H_
#define _UPDATE_H_

#include "CCApplication.h"
#include "cocos2d.h"
#include "extensions/assets-manager/AssetsManager.h"
#include "extensions/cocos-ext.h"
#include "CCLuaEngine.h"
#include "CCLuaEngine.h"

using namespace std;
USING_NS_CC;

class Update : public cocos2d::Layer, public cocos2d::extension::AssetsManagerDelegateProtocol
{
public:
    Update();

    ~Update();

    bool setInfo(std::string url_pack, std::string url_version);
    
	//static Update* getInstance();
	static Update* create();

	bool init();

	static void run();

	void startUpdate();
	void resetVersion();

    virtual void onError(cocos2d::extension::AssetsManager::ErrorCode errorCode);
    virtual void onProgress(int percent);
    virtual void onSuccess();
	/*
	void registerOnErrorScriptHandler(int fNoNew, int fErr);
	void registerOnProgressScriptHandler(int f);
	void registerOnSuccessScriptHandler(int f);
	*/
private:
	void createDownloadedDir();

	void startGame();

private:
    cocos2d::extension::AssetsManager* assetsManager;

	std::string pathToSave;
	/*
	int onErrNoVersionHandler;
	int onErrNetworkHandler;
	int onProgressScriptHandler;
	int onSuccessScriptHandler;
	*/
	Sprite *m_bg;
	ProgressTimer *m_percent;

};

#endif //_UPDATE_H_