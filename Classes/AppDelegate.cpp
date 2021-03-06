#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "Net/NetMgr.h"
#include "Net/NetMgrTolua.h"
#include "TDSkillTolua.h"
#include "updateMangerTolua.h"
#include "LuaPB.h"

using namespace CocosDenshion;

extern int luaopen_CCPora (lua_State* tolua_S);

USING_NS_CC;
using namespace std;


static Size designSize(0,0);

static std::string getuidir(Size winSize)
{
	float rate = winSize.width/winSize.height;
	float rate1 = 960/640.0;    //iphone4/4s
	float rate2 = 1280.0/720.0; //iphone5/5s
	float rate3 = 1024.0/768.0; //ipad
	float sub1 = (rate1 - rate) / rate;
	if(sub1 < 0){ sub1 = -sub1; }
	float sub2 = (rate2 - rate) / rate;
	if(sub2 < 0){ sub2 = -sub2; }
	float sub3 = (rate3 - rate) / rate;
	if(sub3 < 0){ sub3 = -sub3; }

	designSize = Size(1280,720);
	return std::string("res/ui/1280_720");

	if(sub1 < sub2 && sub1 < sub3)
	{
		designSize = Size(960,640);
		return std::string("res/ui/960_640");
	}
	if(sub2 < sub1 && sub2 < sub3)
	{
		designSize = Size(1280,720);
		return std::string("res/ui/1280_720");
	}
	designSize = Size(1024,768);
	return std::string("res/ui/1024_768");
}

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Cpp Tests");
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
	director->setNotificationNode(NetMgr::getInstance());

    auto screenSize = glview->getFrameSize();

    auto fileUtils = FileUtils::getInstance();
	auto writePath = fileUtils->getWritablePath();
	if(writePath.at(writePath.length()-1) == '\\' || writePath.at(writePath.length()-1) == '/')
	{
		writePath.erase(writePath.length()-1);
	}

    std::vector<std::string> searchPaths;
	searchPaths.push_back(writePath + "/src");
	searchPaths.push_back(writePath + "/res");
	searchPaths.push_back(writePath + "/res/image");
	searchPaths.push_back(writePath + getuidir(screenSize));
	
	searchPaths.push_back("src");
	searchPaths.push_back("src/framwork");
	searchPaths.push_back("res");
	searchPaths.push_back("res/fonts");
	searchPaths.push_back("res/image");
	searchPaths.push_back(getuidir(screenSize));

	fileUtils->setSearchPaths(searchPaths);

	//director->setContentScaleFactor(resourceSize.height/designSize.height);
	
	glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);
	//glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);
	//glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
	
    
	auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
	auto state = engine->getLuaStack()->getLuaState();
	luaopen_Net(state);
	luaopen_luapb(state);
	luaopen_TDSkillTolua(state);
	luaopen_updateManager(state);
	luaopen_CCPora(state);
	if (engine->executeScriptFile("src/main.lua")) {
        return false;
    }

	//Update::run();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	//char empty[] = "";
	//NetMgr::getInstance()->sendMessage(0, 1, 8, empty);
	NetMgr::getInstance()->pushMsg(TMessage(0, 0, 0, 0, 0, 0, 0, "syncServerTime"));
	
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
