#include<math.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
size_t n;//Initialize table size
char outputTurn(float i){//Initialize the turn outputter
	return floor(i)==i?'X':'O';//Output either 'X' or 'O' based on the turn
}
void drawTable(char **table){//Initialize the table printer
	for(size_t i=0;i<n;i++){//Print the table
		if(i)//Print the horizontal cell delimiter
			for(size_t j=0;j<n;j++){
				if(j)//Print the horizontal & vertical delimiter joint
					printf("+");
				printf("-");//Print the delimiter
		}
		printf("\n");//Print a newline
		for(size_t j=0;j<n;j++){//Output the cell values & the horizontal delimiters
			if(j)//Print the horizontal delimiters
				printf("|");
			printf("%c",table[i][j]);//Print the cell values
		}
		printf("\n");//Print a newline
	}
	printf("\n");//Print a newline
	return;
}
bool win(char **table,const char turn){//Initialize winner indicator
	bool b=1;//Initialize winning boolean variable
	for(size_t i=n;b&&i--;)//Check the main cross
		if(table[i][i]!=turn)//(Not won by this)
			b=0;
	if(b)//Return true if won
		return 1;
	b=1;//Reset the boolean variable
	for(size_t i=n;b&&i--;)//Check the other cross
		if(table[i][n-i-1]!=turn)//(Not won by this)
			b=0;
	if(b)//Return true if won
		return 1;
	b=1;//Reset the boolean variable
	for(size_t i=n;i--;b=1){//Check horizontally & vertically
		for(size_t j=n;b&&j--;)//Check horizontally
			if(table[i][j]!=turn)//(Not won by this)
				b=0;
		if(b)//Return true if won
			return 1;
		b=1;//Reset the boolean variable
		for(size_t j=n;b&&j--;)//Check vertically
			if(table[j][i]!=turn)//(Not won by this)
				b=0;
		if(b)//Return true if won
			return 1;
	}
	return 0;//Return false if didn't win
}
int main(){
	size_t x,y;//Initialize the axis
	while(1){
		printf("New game...\n");//Notify about the new game
		start://Start
		printf("\nThe number of the columns/rows (must be more than 2): "),scanf("%zu",&n);//Prompt for table size input
		if(n<3){//Ask again if the number isn't bigger than 2
			printf("\nThe number you entered isn't bigger than 2!\n");//Alert
			goto start;//Re-start
		}
		char **table=(char**)malloc(sizeof(char*)*n);//Alloacate column size
		for(size_t i=n;i--;){//Alloacate each row
			table[i]=(char*)malloc(sizeof(char)*n);//Alloacate row size
			for(size_t j=n;j--;)//Put a space in each cell
				table[i][j]=' ';
		}
		for(float i=(float)n*n;i--;){//Run the game
			turn://Start a turn
			drawTable(table);//Draw the table
			printf("The numbers of the column & row from top right to put the %c (in order and seperated by newline(s), tab(s) or space(s)): ",outputTurn(i/2)),scanf("%zu%zu",&x,&y);//Prompt for axis input
			if(x>n||!x--||y>n||!y--||table[y][x]!=' '){//(Invalid position (either out of range, or already full))
				printf("\nInvalid position!\n");//Alert
				goto turn;//Restart the turn
			}
			table[y][x]=outputTurn(i/2);//Fill the cell
			if(win(table,outputTurn(i/2))){//Finish if the winner is found
				printf("\n%c is the winner!\n",outputTurn(i/2)),drawTable(table);//Notify
				break;//Exit
			}
			if(!i)//Notify if it's a draw
				printf("\nIt's a draw!\n"),drawTable(table);
		}
		while(n--)//Free each column
			free(table[n]);
		free(table);//Free each row
	}
	return 0;
}
