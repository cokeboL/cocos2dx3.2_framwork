#include "DBMgr.h"

static DBMgr dbMgr;

DBMgr* DBMgr::getInstance() 
{
	static DBMgr *pInstance = NULL;
	if(pInstance == NULL)
	{
		pInstance = &dbMgr;
	}
	return pInstance;
}


void DBMgr::parseFileToItems(std::string file)
{
	auto path = FileUtils::getInstance()->fullPathForFilename(file);

	std::string s = FileUtils::getInstance()->getStringFromFile(path);
	auto len = s.length();

	if(len <= 0)
	{
		return;
	}
	int encryptMask = 0;
	int iSize = sizeof(encryptMask);
	char *cp = (char*)&encryptMask;
	
	for(auto i=0; i<iSize; i++)
	{
		cp[i] = m_encryptMask+i*7;
	}

	int *p = (int*)(s.c_str());
	int iLen = sizeof(encryptMask);

	int i;
	for(i=0; i<int(len/iLen); i++)
	{
		*p++ ^= encryptMask;
		
	}

	cp = (char*)p;

	for(i=0; i<int(len%iLen); i++)
	{
		cp[i] ^= encryptMask-i*3;
	}

	const char *head = "{\"id\":\"";
	const unsigned int headLen = strlen(head);
	char *begin = 0;
	char *headEnd = 0;
	char *end = 0;
	char *sBegin = (char *)s.c_str();
	unsigned int currLen = 0;

	cp = const_cast<char*>(s.c_str());

	while(1)
	{
		begin = strstr(cp, head);
		if(!begin)
		{
			break;
		}
		headEnd = begin + headLen;
		end = strstr(headEnd, head);
		if(end)
		{
			 end -= 1;
			 m_itemCache.push_back(s.substr(begin-sBegin, end-begin));
			 cp += (end-begin+1);
		}
		else
		{
			auto tmps = s.substr(begin-sBegin);
			auto pos = tmps.find_last_of("}");
			m_itemCache.push_back(tmps.substr(0, pos+1));
			break;
		}
	}
	
}

void DBMgr::addFile(std::string file)
{
	auto path = FileUtils::getInstance()->fullPathForFilename(file);
	m_fileCache.push_back(path);
}

void DBMgr::asyncLoadAll()
{
	for (auto it = std::begin(m_fileCache); it != std::end(m_fileCache); ++it)
	{
		parseFileToItems(*it);
	}
	m_allLoaded = true;
}

void DBMgr::loadAll()
{
	m_allLoaded = false;
	auto t = new std::thread(&DBMgr::asyncLoadAll, this);
	t->detach();

}

std::string  DBMgr::getAndRemoveOneItem()
{
	if(!m_itemCache.empty())
	{
		std::string s = m_itemCache.front();
		m_itemCache.pop_front();
		return s;
	}
	return "";
}
