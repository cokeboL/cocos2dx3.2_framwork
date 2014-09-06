/*
** Lua binding: DBMgr
** Generated automatically by tolua++-1.0.92 on 08/08/14 14:29:34.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
#include "DBMgr.h"

/* Exported function */
TOLUA_API int  tolua_DBMgr_open (lua_State* tolua_S);


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"DBMgr");
}

/* method: getInstance of class  DBMgr */
#ifndef TOLUA_DISABLE_tolua_DBMgr_DBMgr_getInstance00
static int tolua_DBMgr_DBMgr_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DBMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DBMgr* tolua_ret = (DBMgr*)  DBMgr::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DBMgr");
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

/* method: addFile of class  DBMgr */
#ifndef TOLUA_DISABLE_tolua_DBMgr_DBMgr_addFile00
static int tolua_DBMgr_DBMgr_addFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBMgr",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBMgr* self = (DBMgr*)  tolua_tousertype(tolua_S,1,0);
  std::string file = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addFile'", NULL);
#endif
  {
   self->addFile(file);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadAll of class  DBMgr */
#ifndef TOLUA_DISABLE_tolua_DBMgr_DBMgr_loadAll00
static int tolua_DBMgr_DBMgr_loadAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBMgr* self = (DBMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadAll'", NULL);
#endif
  {
   self->loadAll();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isAllLoaded of class  DBMgr */
#ifndef TOLUA_DISABLE_tolua_DBMgr_DBMgr_isAllLoaded00
static int tolua_DBMgr_DBMgr_isAllLoaded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBMgr* self = (DBMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isAllLoaded'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isAllLoaded();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isAllLoaded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAndRemoveOneItem of class  DBMgr */
#ifndef TOLUA_DISABLE_tolua_DBMgr_DBMgr_getAndRemoveOneItem00
static int tolua_DBMgr_DBMgr_getAndRemoveOneItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBMgr* self = (DBMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAndRemoveOneItem'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getAndRemoveOneItem();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAndRemoveOneItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  DBMgr */
#ifndef TOLUA_DISABLE_tolua_DBMgr_DBMgr_clear00
static int tolua_DBMgr_DBMgr_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBMgr* self = (DBMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_DBMgr_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"DBMgr","DBMgr","",NULL);
  tolua_beginmodule(tolua_S,"DBMgr");
   tolua_function(tolua_S,"getInstance",tolua_DBMgr_DBMgr_getInstance00);
   tolua_function(tolua_S,"addFile",tolua_DBMgr_DBMgr_addFile00);
   tolua_function(tolua_S,"loadAll",tolua_DBMgr_DBMgr_loadAll00);
   tolua_function(tolua_S,"isAllLoaded",tolua_DBMgr_DBMgr_isAllLoaded00);
   tolua_function(tolua_S,"getAndRemoveOneItem",tolua_DBMgr_DBMgr_getAndRemoveOneItem00);
   tolua_function(tolua_S,"clear",tolua_DBMgr_DBMgr_clear00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_DBMgr (lua_State* tolua_S) {
 return tolua_DBMgr_open(tolua_S);
};
#endif

