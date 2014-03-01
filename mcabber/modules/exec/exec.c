/*
 *  Module "exec"    -- Execute shell commands
 *
 * Copyright (C) 2011 sh!zeeg <sh!zeeg@ya.ru>
 *
 * This module is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <mcabber/modules.h>
#include <mcabber/settings.h>
#include <mcabber/hooks.h>
#include <mcabber/logprint.h>
#include <mcabber/commands.h>
#include <mcabber/compl.h>


#define HELP_TEXT "/exec <command> [parameters]\nShow only command's output:"\
	"/exec @<command> [parameters]"
static void exec_init   (void);
static void exec_uninit (void);

/* Module description */
module_info_t info_exec = {
        .branch         = MCABBER_BRANCH,
        .api            = MCABBER_API_VERSION,
        .version        = MCABBER_VERSION,
        .description    = "Execute shell commands.",
        .requires       = NULL,
        .init           = exec_init,
        .uninit         = exec_uninit,
        .next           = NULL,
};

static guint    exec_cid  = 0;  /* Command completion category id */
static gpointer exec_cmid = 0;  /* Command id */


/* entry point */
static void do_exec(char *args)
{
  if (!args)
    return;

  gchar *buff = g_strnfill(8192, '\0');
  gchar *cmd[PATH_MAX];
  gboolean isNoEcho = FALSE;
  if (g_str_has_prefix(args, "@")) {
    args[0] = ' ';
    isNoEcho = TRUE;
  }

  g_sprintf(cmd, "%s 2>&1", args);


  FILE *fp = popen(cmd, "r");
  if (!fp ) {
    pclose(fp);
    src_log_print(LPRINT_NORMAL, "exec error!");
    return;
  }

  fread(buff, 4096, 1, fp);
  pclose(fp);

  g_strchomp(buff);
  gchar *str = g_strdup_printf("$ %s\n%s", args, buff);
  if (isNoEcho)
    say_cmd(buff, LPRINT_NORMAL);
  else
    say_cmd(str, LPRINT_NORMAL);
  readline_refresh_screen(); // can I use low-level func here?
  g_free(buff);
  g_free(str);

}

/* init */
static void exec_init(void)
{
  exec_cid = compl_new_category();
  exec_cmid = cmd_add("exec", HELP_TEXT, exec_cid, 0, do_exec, NULL);
}

/* uninit */
static void exec_uninit(void)
{
  cmd_del(exec_cmid);
  if (exec_cid) {
    compl_del_category(exec_cid);
  }
}
