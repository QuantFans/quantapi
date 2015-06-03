/*
 * opencog/util/oc_assert.h
 *
 * Copyright (C) 2002-2007 Novamente LLC
 * All Rights Reserved
 *
 * Written by Thiago Maia <thiago@vettatech.com>
 *            Andre Senna <senna@vettalabs.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef LOG_ASSERT_H
#define LOG_ASSERT_H 
#include "Exceptions.h"


#ifndef IGNORE_LOG_ASSERT
/** 
 * ”√∑®£∫LOG_ASSERT(condition);
 *       LOG_ASSERT(condition, "message");
 *       LOG_ASSERT(condition, "message %d", int );
 *
*/
#define LOG_ASSERT(...) \
    QuantDigger::Util::cassert(TRACE_INFO, __VA_ARGS__)
#else
#define LOG_ASSERT(...) \
    ((void)0)
#endif

namespace QuantDigger{
namespace Util {
    

/**
 * cassert complet with message and trace info
 */
void cassert(const char * trace,  bool condition, const char * msg, ...);

///**
// * cassert with a string instead of const char* and vaargs
// */
//void cassert(const char* trace, bool condition, const std::string& msg);

/**
 * cassert without message. Just trace information
 */
void cassert(const char * trace, bool condition);

} /* Util */
} // namespace QuantDigger

#endif
