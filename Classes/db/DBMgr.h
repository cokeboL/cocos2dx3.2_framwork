#ifndef _DATA_MGR_H_
#define _DATA_MGR_H_

#include <map>
#include <vector>
#include <string>
#include "cocos2d.h"
#include "ThreadSafeQueue.h"

USING_NS_CC;

class DBMgr
{
public:
	DBMgr():m_encryptMask(0xFF), m_allLoaded(false){}
	
	~DBMgr(){ clear(); }

	static DBMgr* getInstance();

	void addFile(std::string file);

	void loadAll();
	
	bool isAllLoaded(){ return m_allLoaded; }

	std::string getAndRemoveOneItem();
	
	void clear(){ m_fileCache.clear(); m_itemCache.clear(); }

protected:
	void asyncLoadAll();

	void parseFileToItems(std::string file);

private:
	char m_encryptMask;
	bool m_allLoaded;
	std::vector<std::string> m_fileCache;
	ThreadSafeQueue<std::string> m_itemCache;
	
};

#endif //_DATA_MGR_H_
