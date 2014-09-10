#include "Update.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <dirent.h>
#include <sys/stat.h>
#endif
#include "Net/NetMgr.h"
#include "Net/NetMgrTolua.h"
#include "LuaPB.h"
#include "CCLuaEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

/*
static Update updateInstance;

Update* Update::getInstance() 
{
	static Update *pInstance = NULL;
	if(pInstance == NULL)
	{
		//pInstance = new CDeviceManager();
		pInstance = &updateInstance;
	}
	return pInstance;
}
*/

Update::Update():
assetsManager(NULL),
pathToSave("")
/*
onErrNoVersionHandler(0),
onErrNetworkHandler(0),
onProgressScriptHandler(0),
onSuccessScriptHandler(0)
*/
{
	//assetsManager = new cocos2d::extension::AssetsManager("", "", "");
}

Update::~Update()
{
}

Update* Update::create()
{
    Update *layer = new Update();
    if (layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool Update::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	auto s = Director::getInstance()->getWinSize();

	m_bg = Sprite::create("Battle_background_up.jpg");
	m_bg->setPosition(Point(s.width/2, s.height/2));
	addChild(m_bg);

	m_percent = ProgressTimer::create(Sprite::create("Battle_bgEnd_1.png"));
	m_percent->setType(ProgressTimer::Type::BAR);
    m_percent->setMidpoint(Point(1, 0));
    m_percent->setBarChangeRate(Point(1, 0));
    m_percent->setPosition(Point(s.width/2, s.height/3));
	addChild(m_percent);

	/*
	auto fileUtiles = FileUtils::getInstance();
	auto *program = new GLProgram();
	program->initWithFilenames("example_Monjori.vsh", "Gray.fsh");
	m_bg->setShaderProgram(program);
	*/
}

void Update::run()
{
	auto scene = Scene::create();
	auto updateLayer = Update::create();
	scene->addChild(updateLayer);
	updateLayer->setInfo("127.0.0.1:3001/package.zip", "127.0.0.1:3001/version");

	Director::getInstance()->runWithScene(scene);

	updateLayer->startUpdate();
}

bool Update::setInfo(std::string url_pack, std::string url_version)
{
    //Layer::init();
   
	if(!assetsManager)
	{
		assetsManager = new cocos2d::extension::AssetsManager(url_pack.c_str(), url_version.c_str(), FileUtils::getInstance()->getWritablePath().c_str());
		//assetsManager->setPackageUrl(url_pack.c_str());
		//assetsManager->setVersionFileUrl(url_version.c_str());
		assetsManager->setDelegate(this);
		assetsManager->setConnectionTimeout(30);
		addChild(assetsManager);
		assetsManager->release();
	}
	else
	{
		assetsManager->setPackageUrl(url_pack.c_str());
		assetsManager->setVersionFileUrl(url_version.c_str());
		//assetsManager->setStoragePath(FileUtils::getInstance()->getWritablePath());
	}
    
    createDownloadedDir();
    return true;
}

void Update::startUpdate()
{
	assetsManager->update();
}

void Update::resetVersion()
{
    // Remove downloaded files
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    string command = "rm -r ";
    // Path may include space.
    command += "\"" + pathToSave + "\"";
    system(command.c_str());
#else
    string command = "rd /s /q ";
    // Path may include space.
    command += "\"" + pathToSave + "\"";
    system(command.c_str());
#endif
    // Delete recorded version codes.
    assetsManager->deleteVersion();
    
    createDownloadedDir();
}

void Update::createDownloadedDir()
{
    pathToSave = FileUtils::getInstance()->getWritablePath();
    pathToSave += "tmpdir";
    
    // Create the folder if it doesn't exist
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    DIR *pDir = NULL;
    
    pDir = opendir (pathToSave.c_str());
    if (! pDir)
    {
        mkdir(pathToSave.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    }
#else
	if ((GetFileAttributesA(pathToSave.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(pathToSave.c_str(), 0);
	}
#endif
}


void Update::startGame()
{
	Director::getInstance()->setNotificationNode(NetMgr::getInstance());

	auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
	
	auto state = engine->getLuaStack()->getLuaState();
	luaopen_NetMgr(state);
	luaopen_luapb(state);
	engine->executeScriptFile("main.lua");
}

void Update::onError(AssetsManager::ErrorCode errorCode)
{
    if (errorCode == AssetsManager::ErrorCode::NO_NEW_VERSION)
    {
		startGame();
    }
	else
	{
		//show net err
		startGame();
	}
}

void Update::onProgress(int percent)
{
	/*
	if(onProgressScriptHandler)
	{
		m_percent->setPercentage(percent);
	}
	*/
}

void Update::onSuccess()
{
	startGame();
	/*
	if(onSuccessScriptHandler)
	{
		startGame();
	}
	*/
}
/*
void Update::registerOnErrorScriptHandler(int fNoNew, int fErr)
{
	onErrNoVersionHandler = fNoNew;
	onErrNetworkHandler = fErr;
}

void Update::registerOnProgressScriptHandler(int f)
{
	onProgressScriptHandler = f;
}

void Update::registerOnSuccessScriptHandler(int f)
{
	onSuccessScriptHandler = f;
}
*/
