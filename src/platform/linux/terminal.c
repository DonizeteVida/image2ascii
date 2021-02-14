/*
 * terminal.c
 *
 *  Created on: Feb 13, 2021
 *      Author: doni
 */
#include <sys/ioctl.h>

#include "../terminal.h"

void getTerminalInfo(struct TerminalInfo* terminalInfo) {
	struct winsize max;
	ioctl(0, TIOCGWINSZ , &max);
	terminalInfo->width = max.ws_col;
	terminalInfo->height = max.ws_row;
}

