
/***************************************************************************
 *  exceptions.h - Lua related exceptions
 *
 *  Created: Mon Jun 23 10:28:58 2008
 *  Copyright  2006-2008  Tim Niemueller [www.niemueller.de]
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

#ifndef __LUA_EXCEPTIONS_H_
#define __LUA_EXCEPTIONS_H_

#ifndef USE_ROS
#  include <core/exception.h>
#else
#  include <ros/exception.h>
using ros::Exception;
#endif

namespace fawkes {

class LuaRuntimeException : public Exception
{
 public:
  LuaRuntimeException(const char *what, const char *errmsg);
};

class LuaErrorException : public Exception
{
 public:
  LuaErrorException(const char *what, const char *errmsg);
};


} // end of namespace fawkes

#endif
