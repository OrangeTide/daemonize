/**
 * @file daemonize.c
 *
 * Places a program in the background as a daemon.
 *
 * @author Jon Mayo <jon.mayo@gmail.com>
 * @date 2020 Dec 9
 *
 * Copyright (c) 2011-2020 Jon Mayo
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#define _GNU_SOURCE
#include "daemonize.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <unistd.h>

void
daemonize(void)
{
	pid_t pid;
	pid_t sid;

	if (getuid() != geteuid()) {
		fprintf(stderr, "%s: this program does not work as setuid\n",
			program_invocation_short_name);
		exit(1);
	}
	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(1);
	}
	if (pid)
		exit(0);
	sid = setsid();
	if (sid < 0) {
		perror("setsid");
		exit(1);
	}
	/*
	if (chdir("/"))
		perror("/");
	*/
	if (!freopen("/dev/null", "r", stdin) ||
		!freopen("/dev/null", "w", stdout) ||
		!freopen("/dev/null", "w", stderr)) {
		perror("/dev/null");
		exit(1);
	}
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
}
