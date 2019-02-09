/* Expression evaluation for plural form selection.
   Copyright (C) 2000-2003, 2005, 2015-2016 Free Software Foundation, Inc.
   Written by Ulrich Drepper <drepper@cygnus.com>, 2000.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

# include <libgnu/config_libgnu.h>

/* Specification.  */
#include "plural-eval.h"

#include <stddef.h>
#include <signal_gnu.h>

#include "plural-exp.h"


#define STATIC /*extern*/

/* Include the expression evaluation code from libintl, this time with
   'extern' linkage.  */
#include "eval-plural.h"


/* Exit point.  Must be set before calling install_sigfpe_handler().  */
sigjmp_buf sigfpe_exit;


/* Evaluate the plural expression and return an index value.  */

unsigned long plural_eval (const struct expression *pexp, unsigned long int n)
{
  switch (pexp->nargs)
    {
    case 0:
      switch (pexp->operation)
    {
    case var:
      return n;
    case num:
      return pexp->val.num;
    default:
      break;
    }
      // NOTREACHED
      break;
    case 1:
      {
    // pexp->operation must be lnot.
    unsigned long int arg = plural_eval (pexp->val.args[0], n);
    return ! arg;
      }
    case 2:
      {
    unsigned long int leftarg = plural_eval (pexp->val.args[0], n);
    if (pexp->operation == lor)
      return leftarg || plural_eval (pexp->val.args[1], n);
    else if (pexp->operation == land)
      return leftarg && plural_eval (pexp->val.args[1], n);
    else
      {
        unsigned long int rightarg = plural_eval (pexp->val.args[1], n);

        switch (pexp->operation)
          {
          case mult:
        return leftarg * rightarg;
          case divide:
#if !INTDIV0_RAISES_SIGFPE
        if (rightarg == 0)
          raise (SIGFPE);
#endif
        return leftarg / rightarg;
          case module:
#if !INTDIV0_RAISES_SIGFPE
        if (rightarg == 0)
          raise (SIGFPE);
#endif
        return leftarg % rightarg;
          case plus:
        return leftarg + rightarg;
          case minus:
        return leftarg - rightarg;
          case less_than:
        return leftarg < rightarg;
          case greater_than:
        return leftarg > rightarg;
          case less_or_equal:
        return leftarg <= rightarg;
          case greater_or_equal:
        return leftarg >= rightarg;
          case equal:
        return leftarg == rightarg;
          case not_equal:
        return leftarg != rightarg;
          default:
        break;
          }
      }
    // NOTREACHED
    break;
      }
    case 3:
      {
    // pexp->operation must be qmop.
    unsigned long int boolarg = plural_eval (pexp->val.args[0], n);
    return plural_eval (pexp->val.args[boolarg ? 1 : 2], n);
      }
    }
  // NOTREACHED
  return 0;
}


#if USE_SIGINFO

/* Additional information that is set before sigfpe_exit is invoked.  */
int sigfpe_code;

/* Signal handler called in case of arithmetic exception (e.g. division
   by zero) during plural_eval.  */
static void
sigfpe_handler (int sig, siginfo_t *sip, void *scp)
{
  sigfpe_code = sip->si_code;
  siglongjmp (sigfpe_exit, 1);
}

#else

/* Signal handler called in case of arithmetic exception (e.g. division
   by zero) during plural_eval.  */
static void
sigfpe_handler (int sig)
{
  siglongjmp (sigfpe_exit, 1);
}

#endif

void
install_sigfpe_handler (void)
{
#if USE_SIGINFO
  struct sigaction action;
  action.sa_sigaction = sigfpe_handler;
  action.sa_flags = SA_SIGINFO;
  sigemptyset (&action.sa_mask);
  sigaction (SIGFPE, &action, (struct sigaction *) NULL);
#else
  signal (SIGFPE, sigfpe_handler);
#endif
}

void
uninstall_sigfpe_handler (void)
{
#if USE_SIGINFO
  struct sigaction action;
  action.sa_handler = SIG_DFL;
  action.sa_flags = 0;
  sigemptyset (&action.sa_mask);
  sigaction (SIGFPE, &action, (struct sigaction *) NULL);
#else
  signal (SIGFPE, SIG_DFL);
#endif
}
