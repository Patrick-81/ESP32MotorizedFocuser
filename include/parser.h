#ifndef __PARSER_H__
#define __PARSER_H__
#include "AbsoluteDriver.h"
#include "Config.h"
#define FORWARD   1
#define BACKWARD -1
void initialize(int initPos);
void process_data(const char *input);
void move();
void stop();
void inithandpad();
void processIncomingByte (const byte inByte);
// pilotage par unité mobile
void gofwd();
void gobwd();
void gotozero();
void speedplus();
void speedmoins();
unsigned long getpos();
int getspeed();
#endif