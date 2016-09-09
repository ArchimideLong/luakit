/*
 * extension/log.c - logging interface for web extension
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "globalconf.h"
#include "extension/extension.h"
#include "common/log.h"
#include "common/msg.h"

#include <glib/gprintf.h>

void
_log(log_level_t lvl, gint line, const gchar *fct, const gchar *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    va_log(lvl, line, fct, fmt, ap);
    va_end(ap);
}

void
va_log(log_level_t lvl, gint line, const gchar *fct, const gchar *fmt, va_list ap) {
    lua_State *L = extension.WL;
    gchar *msg = g_strdup_vprintf(fmt, ap);

    lua_pushinteger(L, lvl);
    lua_pushinteger(L, line);
    lua_pushstring(L, fct);
    lua_pushstring(L, msg);
    msg_send_lua(extension.ipc, MSG_TYPE_log, L, -4, -1);
    lua_pop(L, 4);

    g_free(msg);
}

// vim: ft=c:et:sw=4:ts=8:sts=4:tw=80
