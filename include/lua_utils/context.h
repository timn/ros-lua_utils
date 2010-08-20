
/***************************************************************************
 *  context.h - Fawkes Lua Context
 *
 *  Created: Fri May 23 11:29:01 2008
 *  Copyright  2006-2009  Tim Niemueller [www.niemueller.de]
 *
 ****************************************************************************/

/*  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  Read the full text in the LICENSE.GPL file in the doc directory.
 */

#ifndef __LUA_CONTEXT_H_
#define __LUA_CONTEXT_H_

#ifndef USE_ROS
#  include <lua/exceptions.h>
#  include <core/utils/lock_list.h>
#  include <utils/system/fam.h>
#else
#  include <lua_utils/exceptions.h>
#  include <lua_utils/fam.h>
#endif

#include <lua.hpp>

#include <map>
#include <utility>
#include <list>
#include <string>

namespace fawkes {
#if 0 /* just to make Emacs auto-indent happy */
}
#endif

#ifndef USE_ROS
class LuaContextWatcher;
class Mutex;
#endif

class LuaContext : public FamListener
{
 public:
  LuaContext(bool watch_dirs = true, bool enable_tracebacks = true);
  LuaContext(lua_State *L);
  ~LuaContext();

  void set_start_script(const char *start_script);

  void restart();

  void add_package_dir(const char *path);
  void add_cpackage_dir(const char *path);
  void add_package(const char *package);
  void add_watchdir(const char *path);
  void add_watchfile(const char *path);

  lua_State *  get_lua_state();

#ifndef USE_ROS
  void lock();
  bool try_lock();
  void unlock();
#endif

  void do_file(const char *filename);
  void do_string(const char *format, ...);

  void load_string(const char *s);
  void pcall(int nargs = 0, int nresults = 0, int errfunc = 0);

  void set_usertype(const char *name, void *data, const char *type_name,
		     const char *name_space = 0);
  void set_string(const char *name, const char *value);
  void set_number(const char *name, lua_Number value);
  void set_boolean(const char *name, bool value);
  void set_integer(const char *name, lua_Integer value);
  void set_cfunction(const char *name, lua_CFunction function);
  void remove_global(const char *name);
  void set_global(const char *name);

  void push_boolean(bool value);
  void push_fstring(const char *format, ...);
  void push_integer(lua_Integer value);
  void push_light_user_data(void *p);
  void push_lstring(const char *s, size_t len);
  void push_nil();
  void push_number(lua_Number value);
  void push_string(const char *value);
  void push_thread();
  void push_value(int idx);
  void push_vfstring(const char *format, va_list arg);
  void push_usertype(void *data, const char *type_name, const char *name_space = 0);
  void push_cfunction(lua_CFunction function);

  void pop(int n);
  void remove(int idx);
  int  stack_size();

  void create_table(int narr = 0, int nrec = 0);
  void set_table(int t_index = -3);
  void set_field(const char *key, int t_index = -2);

  void get_table(int idx);
  void get_field(int idx, const char *k);
  void get_global(const char *name);

  void raw_set(int idx);
  void raw_seti(int idx, int n);
  void raw_get(int idx);
  void raw_geti(int idx, int n);

  lua_Number   to_number(int idx);
  lua_Integer  to_integer(int idx);
  bool         to_boolean(int idx);
  const char * to_string(int idx);

  bool         is_boolean(int idx);
  bool         is_cfunction(int idx);
  bool         is_function(int idx);
  bool         is_light_user_data(int idx);
  bool         is_nil(int idx);
  bool         is_number(int idx);
  bool         is_string(int idx);
  bool         is_table(int idx);
  bool         is_thread(int idx);

  size_t       objlen(int idx);
  void         setfenv(int idx = -2);

#ifndef USE_ROS
  void         add_watcher(LuaContextWatcher *watcher);
  void         remove_watcher(LuaContextWatcher *watcher);
#endif

  /* from FamListener */
  virtual void fam_event(const char *filename, unsigned int mask);
  void process_fam_events();


 private:
  lua_State *  init_state();
  void         do_string(lua_State *L, const char *format, ...);
  void         do_file(lua_State *L, const char *s);
  void         assert_unique_name(const char *name, std::string type);

 private:
  lua_State *__L;
  bool       __owns_L;
  bool       __enable_tracebacks;

#ifndef USE_ROS
  Mutex  *__lua_mutex;
#endif
  char   *__start_script;

  std::list<std::string>            __package_dirs;
  std::list<std::string>            __cpackage_dirs;
  std::list<std::string>            __packages;
  std::list<std::string>::iterator  __slit;

  std::map<std::string, std::pair<void *, std::string> > __usertypes;
  std::map<std::string, std::pair<void *, std::string> >::iterator __utit;
  std::map<std::string, std::string>             __strings;
  std::map<std::string, std::string>::iterator   __strings_it;
  std::map<std::string, bool>                    __booleans;
  std::map<std::string, bool>::iterator          __booleans_it;
  std::map<std::string, lua_Number>              __numbers;
  std::map<std::string, lua_Number>::iterator    __numbers_it;
  std::map<std::string, lua_Integer>             __integers;
  std::map<std::string, lua_Integer>::iterator   __integers_it;
  std::map<std::string, lua_CFunction>           __cfunctions;
  std::map<std::string, lua_CFunction>::iterator __cfunctions_it;

  FileAlterationMonitor  *__fam;

#ifndef USE_ROS
  LockList<LuaContextWatcher *> __watchers;
#endif

};

} // end of namespace fawkes

#endif
