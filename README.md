# Daemonize

[![Build Status](https://travis-ci.com/OrangeTide/daemonize.svg?branch=master)](https://travis-ci.com/OrangeTide/daemonize)

## Description

Places your program in the background as a daemon.

## Usage

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "daemonize.h"
int
main(int argc, char *argv[])
{
	int foreground_mode = 0;
	int opt;

	while ((opt = getopt(argc, argv, "f")) != -1) {
		switch (opt) {
		case 'f':
			foreground_mode = 1; // foreground mode
			break;
		default:
			fprintf(stderr, "Usage: %s [-f]\n", argv[0]);
			exit(1);
		}
	}

	if (!foreground_mode)
		daemonize();

	return 0;
}
```
