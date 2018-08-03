#include <iostream>
#include <string>
#include <math.h>
using namespace std;
int checkWin(int*, int);
int main()
{
  int gameBoard[64]= {0,0,0,0, 1,0,0,0, 0,0,0,0, 0,0,0,0, 
  					  0,0,0,0, 0,1,0,0, 0,0,0,0, 0,0,0,0, 
					  0,0,0,0, 0,0,1,0, 0,0,0,0, 0,0,0,0, 
					  0,0,0,0, 0,0,0,1, 0,0,0,0, 0,0,0,0};
  int termination=checkWin(gameBoard, 21);
  if(termination>0)
  {cout << "Player "<<termination<<" Wins";}
  else
  {cout << "Continue";}
}

int checkWin(int board[64], int startPosition) //0 means no win met, 1 means player 1 wins, 2 means player 2 wins
{
    int result = 0; 
	int player = board[startPosition];
	int layerNumber;
	int rowNumber;
	int columnNumber;
	//UP and DOWN
    for (layerNumber = 0; layerNumber < 4; )
    {
		if(board[startPosition%16+16*layerNumber]!=player) {break;}
		layerNumber++;   	
	}
	if(layerNumber == 4) {return(player);}
	//LEFT and RIGHT
	for (columnNumber = 0; columnNumber < 4; )
	{
		if(board[startPosition - startPosition%4 + columnNumber] != player) {break;}
		columnNumber++;
	}
	if(columnNumber == 4) {return(player);}
	//FORWARD and BACKWARD
	for (rowNumber = 0; rowNumber < 4; )
	{
		if(board[startPosition%4 + 4*rowNumber + startPosition - startPosition%16] != player) {break;}
		rowNumber++;
	}
	if(rowNumber == 4) {return(player);}
    //Top Left to Bottom Right Same layer
    if((startPosition%16)%5 == 0)
    {
    	for (rowNumber = 0; rowNumber < 4; )
		{
			if(board[startPosition - startPosition%16 + 5*rowNumber] != player) {break;}
			rowNumber++;
		}
		if(rowNumber == 4) {return(player);}
	}
	//Bottom Left to Top Right Same Layer
	else if(((startPosition%16)%3 == 0) && ((startPosition+1)%16>1))
    {
    	for (rowNumber = 0; rowNumber < 4; )
		{
			if(board[startPosition - startPosition%16 + 3*rowNumber+3] != player) {break;}
			rowNumber++;
		}
		if(rowNumber == 4) {return(player);}
	}
	//Top layer Left Column to Bottom Layer Right Column
	if((startPosition%16-int(floor(startPosition/16)))%4 == 0)
    {
    	for (rowNumber = 0; rowNumber < 4; )
		{
			if(board[startPosition%17 + 17*rowNumber] != player) {break;}
			rowNumber++;
		}
		if(rowNumber == 4) {return(player);}
	}
	//Top layer Right Column to Bottom Layer Left Column
	else if((startPosition%16+int(floor(startPosition/16)))%4 == 3)
    {
    	for (rowNumber = 0; rowNumber < 4; )
		{
			if(board[startPosition%15 + 15*rowNumber] != player) {break;}
			rowNumber++;
		}
		if(rowNumber == 4) {return(player);}
	}
	//Top layer Back Row to Bottom Layer Front Row
	if((startPosition%16-int(floor(startPosition/16))*4) < 4)
    {
    	for (rowNumber = 0; rowNumber < 4; )
		{
			if(board[startPosition%20 + 20*rowNumber] != player) {break;}
			rowNumber++;
		}
		if(rowNumber == 4) {return(player);}
	}
	//Top layer Front Row to Bottom Layer Back Row
	else if((startPosition%16+int(floor(startPosition/16))*4)%16 > 11)
    {
    	for (rowNumber = 0; rowNumber < 4; )
		{
			if(board[startPosition%20 + 20*rowNumber] != player) {break;}
			rowNumber++;
		}
		if(rowNumber == 4) {return(player);}
	}
	//0 to 63
	if((startPosition%16-int(floor(startPosition/16))*5) ==0)
    {
    	for (rowNumber = 0; rowNumber < 4; )
		{
			if(board[0 + 21*rowNumber] != player) {break;}
			rowNumber++;
		}
		if(rowNumber == 4) {return(player);}
	}
	//3 to 60
	else if((startPosition%16-int(floor(startPosition/16))*3) == 3)
    {
    	for (rowNumber = 0; rowNumber < 4; )
		{
			if(board[3 + 19*rowNumber] != player) {break;}
			rowNumber++;
		}
		if(rowNumber == 4) {return(player);}
	}
	//12 to 51
	else if((startPosition%16+int(floor(startPosition/16))*3) == 12)
    {
    	for (rowNumber = 0; rowNumber < 4; )
		{
			if(board[12 + 13*rowNumber] != player) {break;}
			rowNumber++;
		}
		if(rowNumber == 4) {return(player);}
	}
	//15 to 48
	else if((startPosition%16+int(floor(startPosition/16))*5) ==15)
    {
    	for (rowNumber = 0; rowNumber < 4; )
		{
			if(board[15 + 11*rowNumber] != player) {break;}
			rowNumber++;
		}
		if(rowNumber == 4) {return(player);}
	}
	return(0);
}
