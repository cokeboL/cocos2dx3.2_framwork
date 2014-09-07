/*
** Lua binding: NetManager
** Generated automatically by tolua++-1.0.92 on 02/20/14 18:27:12.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_NetManager_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_TMessage (lua_State* tolua_S)
{
 TMessage* self = (TMessage*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"TMessage");
 tolua_usertype(tolua_S,"CNetBean");
 tolua_usertype(tolua_S,"CGameNetManager");
 tolua_usertype(tolua_S,"LUA_FUNCTION");
}

/* method: new of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_NetManager_TMessage_new00
static int tolua_NetManager_TMessage_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TMessage",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  int len = ((int)  tolua_tonumber(tolua_S,3,0));
  char* content = ((char*)  tolua_tostring(tolua_S,4,0));
  {
   TMessage* tolua_ret = (TMessage*)  Mtolua_new((TMessage)(name,len,content));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TMessage");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_NetManager_TMessage_new00_local
static int tolua_NetManager_TMessage_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TMessage",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  int len = ((int)  tolua_tonumber(tolua_S,3,0));
  char* content = ((char*)  tolua_tostring(tolua_S,4,0));
  {
   TMessage* tolua_ret = (TMessage*)  Mtolua_new((TMessage)(name,len,content));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TMessage");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_Name of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_get_TMessage_m_Name
static int tolua_get_TMessage_m_Name(lua_State* tolua_S)
{
  TMessage* self = (TMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->m_Name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_Name of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_set_TMessage_m_Name
static int tolua_set_TMessage_m_Name(lua_State* tolua_S)
{
  TMessage* self = (TMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Name'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_Name = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_Len of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_get_TMessage_m_Len
static int tolua_get_TMessage_m_Len(lua_State* tolua_S)
{
  TMessage* self = (TMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Len'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_Len);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_Len of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_set_TMessage_m_Len
static int tolua_set_TMessage_m_Len(lua_State* tolua_S)
{
  TMessage* self = (TMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Len'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_Len = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_Content of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_get_TMessage_m_Content
static int tolua_get_TMessage_m_Content(lua_State* tolua_S)
{
  TMessage* self = (TMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Content'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->m_Content);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_Content of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_set_TMessage_m_Content
static int tolua_set_TMessage_m_Content(lua_State* tolua_S)
{
  TMessage* self = (TMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_Content'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_Content = ((char*)  tolua_tostring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_getInstance00
static int tolua_NetManager_CGameNetManager_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CGameNetManager* tolua_ret = (CGameNetManager*)  CGameNetManager::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CGameNetManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: netInit of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_netInit00
static int tolua_NetManager_CGameNetManager_netInit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGameNetManager* self = (CGameNetManager*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned short port = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'netInit'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->netInit(ip,port);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'netInit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNetMessage of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_getNetMessage00
static int tolua_NetManager_CGameNetManager_getNetMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGameNetManager* self = (CGameNetManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNetMessage'", NULL);
#endif
  {
   const TMessage& tolua_ret = (const TMessage&)  self->getNetMessage();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const TMessage");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNetMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: popMessage of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_popMessage00
static int tolua_NetManager_CGameNetManager_popMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGameNetManager* self = (CGameNetManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'popMessage'", NULL);
#endif
  {
   self->popMessage();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'popMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendNetMessage of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_sendNetMessage00
static int tolua_NetManager_CGameNetManager_sendNetMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGameNetManager* self = (CGameNetManager*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  int len = ((int)  tolua_tonumber(tolua_S,3,0));
  char* content = ((char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendNetMessage'", NULL);
#endif
  {
   self->sendNetMessage(name,len,content);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendNetMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerOnMessageScriptHandler of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_registerOnMessageScriptHandler00
static int tolua_NetManager_CGameNetManager_registerOnMessageScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGameNetManager* self = (CGameNetManager*)  tolua_tousertype(tolua_S,1,0);
  std::string s = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerOnMessageScriptHandler'", NULL);
#endif
  {
   self->registerOnMessageScriptHandler(s);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerOnMessageScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerOnCreateScriptHandler of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_registerOnCreateScriptHandler00
static int tolua_NetManager_CGameNetManager_registerOnCreateScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGameNetManager* self = (CGameNetManager*)  tolua_tousertype(tolua_S,1,0);
  std::string s = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerOnCreateScriptHandler'", NULL);
#endif
  {
   self->registerOnCreateScriptHandler(s);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerOnCreateScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerOnConnectedScriptHandler of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_registerOnConnectedScriptHandler00
static int tolua_NetManager_CGameNetManager_registerOnConnectedScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGameNetManager* self = (CGameNetManager*)  tolua_tousertype(tolua_S,1,0);
  std::string s = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerOnConnectedScriptHandler'", NULL);
#endif
  {
   self->registerOnConnectedScriptHandler(s);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerOnConnectedScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerOnDisconnectedScriptHandler of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_registerOnDisconnectedScriptHandler00
static int tolua_NetManager_CGameNetManager_registerOnDisconnectedScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGameNetManager* self = (CGameNetManager*)  tolua_tousertype(tolua_S,1,0);
  std::string s = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerOnDisconnectedScriptHandler'", NULL);
#endif
  {
   self->registerOnDisconnectedScriptHandler(s);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerOnDisconnectedScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerOnConnectErrorScriptHandler of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_registerOnConnectErrorScriptHandler00
static int tolua_NetManager_CGameNetManager_registerOnConnectErrorScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGameNetManager* self = (CGameNetManager*)  tolua_tousertype(tolua_S,1,0);
  std::string s = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerOnConnectErrorScriptHandler'", NULL);
#endif
  {
   self->registerOnConnectErrorScriptHandler(s);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerOnConnectErrorScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerOnConnectTimeoutScriptHandler of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_registerOnConnectTimeoutScriptHandler00
static int tolua_NetManager_CGameNetManager_registerOnConnectTimeoutScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGameNetManager* self = (CGameNetManager*)  tolua_tousertype(tolua_S,1,0);
  std::string s = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerOnConnectTimeoutScriptHandler'", NULL);
#endif
  {
   self->registerOnConnectTimeoutScriptHandler(s);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerOnConnectTimeoutScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAddress of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_setAddress00
static int tolua_NetManager_CGameNetManager_setAddress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGameNetManager* self = (CGameNetManager*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned short port = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAddress'", NULL);
#endif
  {
   self->setAddress(ip,port);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAddress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: connect of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_connect00
static int tolua_NetManager_CGameNetManager_connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGameNetManager* self = (CGameNetManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'connect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->connect();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: close of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_close00
static int tolua_NetManager_CGameNetManager_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGameNetManager* self = (CGameNetManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'close'", NULL);
#endif
  {
   self->close();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: request of class  CGameNetManager */
#ifndef TOLUA_DISABLE_tolua_NetManager_CGameNetManager_request00
static int tolua_NetManager_CGameNetManager_request00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CGameNetManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CGameNetManager* self = (CGameNetManager*)  tolua_tousertype(tolua_S,1,0);
  string tag = ((string)  tolua_tocppstring(tolua_S,2,0));
  string url = ((string)  tolua_tocppstring(tolua_S,3,0));
  const char* postData = ((const char*)  tolua_tostring(tolua_S,4,0));
  LUA_FUNCTION cbFunc = *((LUA_FUNCTION*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'request'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->request(tag,url,postData,cbFunc);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)tag);
   tolua_pushcppstring(tolua_S,(const char*)url);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'request'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_NetManager_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TMessage","TMessage","",tolua_collect_TMessage);
  #else
  tolua_cclass(tolua_S,"TMessage","TMessage","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TMessage");
   tolua_function(tolua_S,"new",tolua_NetManager_TMessage_new00);
   tolua_function(tolua_S,"new_local",tolua_NetManager_TMessage_new00_local);
   tolua_function(tolua_S,".call",tolua_NetManager_TMessage_new00_local);
   tolua_variable(tolua_S,"m_Name",tolua_get_TMessage_m_Name,tolua_set_TMessage_m_Name);
   tolua_variable(tolua_S,"m_Len",tolua_get_TMessage_m_Len,tolua_set_TMessage_m_Len);
   tolua_variable(tolua_S,"m_Content",tolua_get_TMessage_m_Content,tolua_set_TMessage_m_Content);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CGameNetManager","CGameNetManager","CNetBean",NULL);
  tolua_beginmodule(tolua_S,"CGameNetManager");
   tolua_function(tolua_S,"getInstance",tolua_NetManager_CGameNetManager_getInstance00);
   tolua_function(tolua_S,"netInit",tolua_NetManager_CGameNetManager_netInit00);
   tolua_function(tolua_S,"getNetMessage",tolua_NetManager_CGameNetManager_getNetMessage00);
   tolua_function(tolua_S,"popMessage",tolua_NetManager_CGameNetManager_popMessage00);
   tolua_function(tolua_S,"sendNetMessage",tolua_NetManager_CGameNetManager_sendNetMessage00);
   tolua_function(tolua_S,"registerOnMessageScriptHandler",tolua_NetManager_CGameNetManager_registerOnMessageScriptHandler00);
   tolua_function(tolua_S,"registerOnCreateScriptHandler",tolua_NetManager_CGameNetManager_registerOnCreateScriptHandler00);
   tolua_function(tolua_S,"registerOnConnectedScriptHandler",tolua_NetManager_CGameNetManager_registerOnConnectedScriptHandler00);
   tolua_function(tolua_S,"registerOnDisconnectedScriptHandler",tolua_NetManager_CGameNetManager_registerOnDisconnectedScriptHandler00);
   tolua_function(tolua_S,"registerOnConnectErrorScriptHandler",tolua_NetManager_CGameNetManager_registerOnConnectErrorScriptHandler00);
   tolua_function(tolua_S,"registerOnConnectTimeoutScriptHandler",tolua_NetManager_CGameNetManager_registerOnConnectTimeoutScriptHandler00);
   tolua_function(tolua_S,"setAddress",tolua_NetManager_CGameNetManager_setAddress00);
   tolua_function(tolua_S,"connect",tolua_NetManager_CGameNetManager_connect00);
   tolua_function(tolua_S,"close",tolua_NetManager_CGameNetManager_close00);
   tolua_function(tolua_S,"request",tolua_NetManager_CGameNetManager_request00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_NetManager (lua_State* tolua_S) {
 return tolua_NetManager_open(tolua_S);
};
#endif

