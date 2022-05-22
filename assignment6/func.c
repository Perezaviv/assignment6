#include "header.h"


//function recives the size and outputs the arr in the new format
Short_client* createShortClientArr(int size)
{
	Client* originArr;
	Short_client* newArr;

	originArr = (Client*)malloc(sizeof(Client) * size);
	checkMalloc(originArr);

	getClientInfo(originArr, size);

	newArr = makeShortClient(originArr, size);

	return newArr;
}
//this function recives the original arr and it's size, and compresses it to the new format
Short_client* makeShortClient(Client* originArr, int size)
{
	Short_client* newArr;
	BYTE b, mask;
	int firstNum=0, secondNum=0, i, j, counter=0;

	newArr = (Short_client*)calloc(size, sizeof(Short_client));
	checkMalloc(newArr);

	for (i = 0; i < size; i++)
	{
		for (j = 0; j <= 7; j++)
		{
			firstNum = originArr[i].id[j] - '0';
			secondNum = originArr[i].id[j + 1] - '0';
			//The last number
			if (j == 7)
				secondNum = (int)'\0';

			newArr[i].short_id[counter] = makeBinNum(firstNum, secondNum);

			if (j == 0)
			{
				firstNum = originArr[i].phone[j] - '0';
				secondNum = originArr[i].phone[j + 1] - '0';
			}
			else if(j==2) 
			{
				//originArr[i].phone[3] value is '-' so we skip it and from now on we count + 2
				firstNum = originArr[i].phone[j] - '0';
				secondNum = originArr[i].phone[j + 2] - '0';
			}
			newArr[i].short_phone[counter] = makeBinNum(firstNum, secondNum);
			counter++;
			j++;

		}
		firstNum = originArr[i].phone[j+1] - '0';
		secondNum = originArr[i].phone[j + 2] - '0';
		newArr[i].short_phone[counter] = makeBinNum(firstNum, secondNum);
	}
	free(originArr);
	return newArr;
}
//this function recives two integers between 1-9 and makes them in to one byte
BYTE makeBinNum(int firstNum, int secondNum)
{
	BYTE maskFirst,  maskSecond;

	maskFirst = (BYTE)firstNum;
	maskSecond = (BYTE)secondNum;

	maskFirst = maskFirst << 4;

	return(maskFirst | maskSecond);

}
void checkMalloc(void* arr)
{
	if (arr == NULL)
		exit(1);
}
void getClientInfo(Client* arr, int size)
{
	int i=0;

	for (i = 0; i < size; i++)
	{
	
		scanf("%s", arr[i].id);
		scanf("%s", arr[i].phone);
	}
}
//this function compares the id recived from user to the array we created.
//the function recives the short format arr, the size of it, and the selected id
//if the function finds a match between the selected id to an id in the array, it returns the matching number in the old format.
//if there's no match, the funtion returns NULL
char* searchClientByID(Short_client* arr, int size, char id[9])
{
	BYTE shortID[4];
	char* newNum = NULL;
	int i;


	makeShortID(shortID, id);

	for (i = 0; i < size; i++)
	{
		if (idMatch(shortID, arr[i].short_id))
		{
			newNum = longNum(arr[i].short_phone);
		}
	}
	return newNum;
}
//recives numbrt in the short format and turns it back to the original format
char* longNum(BYTE* b)
{
	BYTE mask1, mask2;
	char* newNum;
	int i, j=0;

	newNum = (char*)malloc(sizeof(char) * 12);
	checkMalloc(newNum);

	newNum[3] = 0 | ('-');

	for (i = 0; i < 11; i++)
	{
		mask1 = NULL, mask2 = NULL;
		mask1 = mask1 | (b[j] >> 4);
		mask2 = mask2 | (b[j] << 4);
		mask2 = mask2 >> 4;

		newNum[i] = (0 | mask1) + '0';
		if (i == 2)
		{
			i++;
		}
		newNum[i + 1] = (0 | mask2) + '0';
		i++;
		j++;
	}

	newNum[i] = '\0';

	return newNum;

}
//the function compares the bytes of the id and returns true or false
bool idMatch(BYTE* b1, char* b2)
{
	int i;
	BYTE mask[4];

	for (i = 0; i < 4; i++)
	{
		mask[i] = (BYTE)b2[i];
		if (b1[i] & mask[i])
			return false;
	}
	return true;
}
//function recives id in the long format and transforms it to the new format
void makeShortID(BYTE shortID[4], char id[9])
{
	int i, firstNum = 0, secondNum = 0, counter = 0;

	for (i = 0; i < 8; i++)
	{
		firstNum = (int)id[i] - '0';
		secondNum = (int)id[i+1] - '0';

		//the last number we read is firstNum when i==6
		if (i == 6)
		{
			secondNum = (int)'\0';
		}
		shortID[counter] = makeBinNum(firstNum, secondNum);
		counter++;
		i++;
	}
}
