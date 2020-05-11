#pragma once
#ifndef Kernel_H__
#define Kernel_H__

#include<stdlib.h>
#include<time.h>
#include<stdio.h>

#define true 1
#define false 0
#define bool int
#define SIZE 4


typedef struct MAP
{
	unsigned map[SIZE][SIZE];
}Map,* pMap;





typedef struct STACK
{
	int element[SIZE];
	int top;
}Stack,* lStack;


bool stackpush(lStack,int element);

int stackpop(lStack);

Map InitialMap();

void TopMove(pMap);

void BottomMove(pMap);

void LeftMove(pMap);

void RightMove(pMap);

bool IsFailure(const Map);

unsigned short SquareRandom(int);

void GerenralNew(pMap);

int GetInfo(Map);

bool Save(Map);

#endif
