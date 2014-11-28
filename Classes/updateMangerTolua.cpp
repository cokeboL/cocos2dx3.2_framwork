/*
** Lua binding: updateManager
** Generated automatically by tolua++-1.0.92 on 11/14/14 10:34:13.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
#include "updateManager.h"
#include "tolua_fix.h"
#include "CCLuaValue.h"
/* Exported function */
TOLUA_API int  tolua_updateManager_open (lua_State* tolua_S);


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"updateManger");
 tolua_usertype(tolua_S,"CallFunction");
}

/* method: getInstance of class  updateManger */
#ifndef TOLUA_DISABLE_tolua_updateManager_updateManger_getInstance00
static int tolua_updateManager_updateManger_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"updateManger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   updateManger* tolua_ret = (updateManger*)  updateManger::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"updateManger");
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

/* method: startUpadate of class  updateManger */
#ifndef TOLUA_DISABLE_tolua_updateManager_updateManger_startUpadate00
static int tolua_updateManager_updateManger_startUpadate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"updateManger",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     //(tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CallFunction",0,&tolua_err)) ||
	 !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  updateManger* self = (updateManger*)  tolua_tousertype(tolua_S,1,0);
  int heroLv = ((int)  tolua_tonumber(tolua_S,2,0));
  //CallFunction func = *((CallFunction*)  tolua_tousertype(tolua_S,3,0));
  cocos2d::LUA_FUNCTION func = (  toluafix_ref_function(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startUpadate'", NULL);
#endif
  {
   self->startUpadate(heroLv,func);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startUpadate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startResouceUpadate of class  updateManger */
#ifndef TOLUA_DISABLE_tolua_updateManager_updateManger_startResouceUpadate00
static int tolua_updateManager_updateManger_startResouceUpadate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"updateManger",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		//(tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CallFunction",0,&tolua_err)) ||
		!toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		updateManger* self = (updateManger*)  tolua_tousertype(tolua_S,1,0);
		int heroLv = ((int)  tolua_tonumber(tolua_S,2,0));
		//CallFunction func = *((CallFunction*)  tolua_tousertype(tolua_S,3,0));
		cocos2d::LUA_FUNCTION func = (  toluafix_ref_function(tolua_S,3,0));
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startResouceUpadate'", NULL);
#endif
		{
			self->startResouceUpadate(heroLv,func);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'startResouceUpadate'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUrls of class  updateManger */
#ifndef TOLUA_DISABLE_tolua_updateManager_updateManger_getUrls00
static int tolua_updateManager_updateManger_getUrls00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"updateManger",0,&tolua_err) ||
	 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  updateManger* self = (updateManger*)  tolua_tousertype(tolua_S,1,0);
  char* url = ((char*)tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUrls'", NULL);
#endif
  {
   self->getUrls(url);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUrls'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: download of class  updateManger */
#ifndef TOLUA_DISABLE_tolua_updateManager_updateManger_download00
static int tolua_updateManager_updateManger_download00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"updateManger",0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  updateManger* self = (updateManger*)  tolua_tousertype(tolua_S,1,0);
   cocos2d::LUA_FUNCTION func = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'download'", NULL);
#endif
  {
   self->download(func);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'download'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_updateManager_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"updateManger","updateManger","",NULL);
  tolua_beginmodule(tolua_S,"updateManger");
   tolua_function(tolua_S,"getInstance",tolua_updateManager_updateManger_getInstance00);
   tolua_function(tolua_S,"startUpadate",tolua_updateManager_updateManger_startUpadate00);
   tolua_function(tolua_S,"startResouceUpadate",tolua_updateManager_updateManger_startResouceUpadate00);
   tolua_function(tolua_S,"getUrls",tolua_updateManager_updateManger_getUrls00);
   tolua_function(tolua_S,"download",tolua_updateManager_updateManger_download00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_updateManager (lua_State* tolua_S) {
 return tolua_updateManager_open(tolua_S);
};
#endif

