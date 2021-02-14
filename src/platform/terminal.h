/*
 * terminal.h
 *
 *  Created on: Feb 13, 2021
 *      Author: doni
 */

#ifndef PLATFORM_TERMINAL_H_
#define PLATFORM_TERMINAL_H_

struct TerminalInfo {
	int width;
	int height;
};

void getTerminalInfo(struct TerminalInfo* terminalInfo);

#endif /* PLATFORM_TERMINAL_H_ */
