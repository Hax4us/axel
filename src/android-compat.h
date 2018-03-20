/*
  Axel -- A lighter download accelerator for Linux and other Unices

  Copyright 2018      Ismael Luceno

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  In addition, as a special exception, the copyright holders give
  permission to link the code of portions of this program with the
  OpenSSL library under certain conditions as described in each
  individual source file, and distribute linked combinations including
  the two.

  You must obey the GNU General Public License in all respects for all
  of the code used other than OpenSSL. If you modify file(s) with this
  exception, you may extend this exception to your version of the
  file(s), but you are not obligated to do so. If you do not wish to do
  so, delete this exception statement from your version. If you delete
  this exception statement from all source files in the program, then
  also delete it here.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

/* Android compatibility stubs */

#if !defined(AXEL_COMPAT_ANDROID) && defined(__ANDROID__)

inline static
int pthread_cancel(pthread_t h) {
	return pthread_kill(h, 0);
}

static void thread_cancel_handler(int sig_num)
{
	if (sig_num == SIGUSR1)
	{
		pthread_exit(0);
	}
}

static int pthread_setcancelable()
{
	struct sigaction action;
	memset(&action, 0, sizeof(action));
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	action.sa_handler = &thread_cancel_signal_handler;	
	return sigaction(SIGUSR1, &action, NULL);
}

inline static
int pthread_setcanceltype(int type, int *oldtype)
{
	return 0;
}
#endif /* !defined(AXEL_COMPAT_ANDROID) && defined(__ANDROID__) */
