/*
** Lua binding: NetMgr
** Generated automatically by tolua++-1.0.92 on 08/18/14 16:29:55.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
#include "Net/NetMgr.h"
#include "tolua_fix.h"


/* Exported function */
TOLUA_API int  tolua_NetMgr_open (lua_State* tolua_S);


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
 tolua_usertype(tolua_S,"NetMgr");
 tolua_usertype(tolua_S,"CNetBean");
}

/* method: new of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_NetMgr_TMessage_new00
static int tolua_NetMgr_TMessage_new00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_NetMgr_TMessage_new00_local
static int tolua_NetMgr_TMessage_new00_local(lua_State* tolua_S)
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

/* get function: name of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_get_TMessage_name
static int tolua_get_TMessage_name(lua_State* tolua_S)
{
  TMessage* self = (TMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_set_TMessage_name
static int tolua_set_TMessage_name(lua_State* tolua_S)
{
  TMessage* self = (TMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->name = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: len of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_get_TMessage_len
static int tolua_get_TMessage_len(lua_State* tolua_S)
{
  TMessage* self = (TMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->len);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: len of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_set_TMessage_len
static int tolua_set_TMessage_len(lua_State* tolua_S)
{
  TMessage* self = (TMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->len = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: message of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_get_TMessage_message
static int tolua_get_TMessage_message(lua_State* tolua_S)
{
  TMessage* self = (TMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'message'",NULL);
#endif
  //tolua_pushstring(tolua_S,(const char*)self->message);
  lua_pushlstring(tolua_S,(const char*)self->message, self->len);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: message of class  TMessage */
#ifndef TOLUA_DISABLE_tolua_set_TMessage_message
static int tolua_set_TMessage_message(lua_State* tolua_S)
{
  TMessage* self = (TMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'message'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->message = ((char*)  tolua_tostring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_NetMgr_NetMgr_getInstance00
static int tolua_NetMgr_NetMgr_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   NetMgr* tolua_ret = (NetMgr*)  NetMgr::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"NetMgr");
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

/* method: getMessage of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_NetMgr_NetMgr_getMessage00
static int tolua_NetMgr_NetMgr_getMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMessage'", NULL);
#endif
  {
   const TMessage& tolua_ret = (const TMessage&)  self->getMessage();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const TMessage");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: popMessage of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_NetMgr_NetMgr_popMessage00
static int tolua_NetMgr_NetMgr_popMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: sendMessage of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_NetMgr_NetMgr_sendMessage00
static int tolua_NetMgr_NetMgr_sendMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  int len = ((int)  tolua_tonumber(tolua_S,3,0));
  char* content = ((char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendMessage'", NULL);
#endif
  {
   self->sendMessage(name,len,content);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerCallBacks of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_NetMgr_NetMgr_registerCallBacks00
static int tolua_NetMgr_NetMgr_registerCallBacks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,4,"LUA_FUNCTION",0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,5,"LUA_FUNCTION",0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,6,"LUA_FUNCTION",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
  /*
  int connCB = ((int)  tolua_tonumber(tolua_S,2,0));
  int disconnCB = ((int)  tolua_tonumber(tolua_S,3,0));
  int errCB = ((int)  tolua_tonumber(tolua_S,4,0));
  int timeoutCB = ((int)  tolua_tonumber(tolua_S,5,0));
  int msgCB = ((int)  tolua_tonumber(tolua_S,6,0));
  */
  LUA_FUNCTION connCB = (  toluafix_ref_function(tolua_S,2,0));
  LUA_FUNCTION disconnCB = (  toluafix_ref_function(tolua_S,3,0));
  LUA_FUNCTION errCB = (  toluafix_ref_function(tolua_S,4,0));
  LUA_FUNCTION timeoutCB = (  toluafix_ref_function(tolua_S,5,0));
  LUA_FUNCTION msgCB = (  toluafix_ref_function(tolua_S,6,0));

#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerCallBacks'", NULL);
#endif
  {
   self->registerCallBacks(connCB,disconnCB,errCB,timeoutCB,msgCB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerCallBacks'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAddress of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_NetMgr_NetMgr_setAddress00
static int tolua_NetMgr_NetMgr_setAddress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: connect of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_NetMgr_NetMgr_connect00
static int tolua_NetMgr_NetMgr_connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: close of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_NetMgr_NetMgr_close00
static int tolua_NetMgr_NetMgr_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
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

/* method: httpRequest of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_NetMgr_NetMgr_httpRequest00
static int tolua_NetMgr_NetMgr_httpRequest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     //!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
  std::string url = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  //int cbFunc = ((int)  tolua_tonumber(tolua_S,3,0));
  LUA_FUNCTION cbFunc = (  toluafix_ref_function(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'httpRequest'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->httpRequest(url,cbFunc);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)url);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'httpRequest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_NetMgr_open (lua_State* tolua_S)
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
   tolua_function(tolua_S,"new",tolua_NetMgr_TMessage_new00);
   tolua_function(tolua_S,"new_local",tolua_NetMgr_TMessage_new00_local);
   tolua_function(tolua_S,".call",tolua_NetMgr_TMessage_new00_local);
   tolua_variable(tolua_S,"name",tolua_get_TMessage_name,tolua_set_TMessage_name);
   tolua_variable(tolua_S,"len",tolua_get_TMessage_len,tolua_set_TMessage_len);
   tolua_variable(tolua_S,"message",tolua_get_TMessage_message,tolua_set_TMessage_message);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"NetMgr","NetMgr","CNetBean",NULL);
  tolua_beginmodule(tolua_S,"NetMgr");
   tolua_function(tolua_S,"getInstance",tolua_NetMgr_NetMgr_getInstance00);
   tolua_function(tolua_S,"getMessage",tolua_NetMgr_NetMgr_getMessage00);
   tolua_function(tolua_S,"popMessage",tolua_NetMgr_NetMgr_popMessage00);
   tolua_function(tolua_S,"sendMessage",tolua_NetMgr_NetMgr_sendMessage00);
   tolua_function(tolua_S,"registerCallBacks",tolua_NetMgr_NetMgr_registerCallBacks00);
   tolua_function(tolua_S,"setAddress",tolua_NetMgr_NetMgr_setAddress00);
   tolua_function(tolua_S,"connect",tolua_NetMgr_NetMgr_connect00);
   tolua_function(tolua_S,"close",tolua_NetMgr_NetMgr_close00);
   tolua_function(tolua_S,"httpRequest",tolua_NetMgr_NetMgr_httpRequest00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_NetMgr (lua_State* tolua_S) {
 return tolua_NetMgr_open(tolua_S);
};
#endif

