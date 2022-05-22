#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef unsigned char BYTE;

typedef struct _client
{
	char id[9];     // “12345678”	
	char phone[12]; // “054-1234567” 
	                //  012j45678910
} Client;

typedef struct _short_client
{
	unsigned char short_id[4];
	unsigned char short_phone[5];
} Short_client;

Short_client* createShortClientArr(int size);
void checkMalloc(void* arr);
Short_client* makeShortClient(Client* originArr, int size);
BYTE makeBinNum(int firstNum, int secondNum);
void checkMalloc(void* arr);
void getClientInfo(Client* arr, int size);
char* searchClientByID(Short_client* arr, int size, char id[9]);
void makeShortID(BYTE shortID[4], char id[9]);
char* longNum(BYTE* b);
bool idMatch(BYTE* b1, char* b2);









