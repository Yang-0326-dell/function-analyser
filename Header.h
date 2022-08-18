#ifndef HEADER_H
#define HEADER_H

#include <iostream>
using namespace std;
#include <string>
#include <vector>
using std::vector;
#include<array>
#include <regex>
#include <Windows.h>
#include <math.h>

#define NON			0x00
#define ADD			0x01//
#define INV			0x02//
#define MUL			0x03//
#define REC			0x04//
#define MOD			0x05//
#define SIN			0x06//
#define COS			0x07//
#define TAN			0x08//
#define ASIN		0x09//
#define ACOS		0x0a//
#define ATAN		0x0b//
#define LOG			0x0c//
#define LG			0x0d//
#define LN			0x0e//
#define POW			0x0f//
//#define INV			0x10
//#define REC			0x11
#define VAR1		0x80
#define VAR2		0x81
#define VAR3		0x82//
#define VAR4		0x83//
#define CON			0x84

//#define SIN_C		0x86
//#define COS_C		0x87
//#define TAN_C		0x88
//#define ASIN_C		0x89
//#define ACOS_C		0x8a
//#define ATAN_C		0x8b
//#define LOG_C		0x8c
//#define LG_C		0x8d
//#define LN_C		0x8f

#define CHARACTER_MAX	20

#define NON_FLAG		0x1
#define DIVIDED_BY_0	0x2
#define LNERROR			0x3

#define RADIO			1
#define ARROW			10

struct  fs {
	int X;
	int Y;
};


#endif