#include<math.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
size_t n;
char outputTurn(float i){
	return floor(i)==i?'X':'O';
}
void drawTable(char **table){
	for(size_t i=0;i<n;i++){
		if(i)
			for(auto j=(float)n*2-1;j--;)
				if(j/2>floor(j/2))
					printf("+");
				else
					printf("-");
		printf("\n");
		for(size_t j=0;j<n;j++){
			if(j)
				printf("|");
			printf("%c",table[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}
bool win(char **table,const char turn){
	bool b=1;
	for(size_t i=n;b&&i--;)
		if(table[i][i]!=turn)
			b=0;
	if(b)
		return 1;
	b=1;
	for(size_t i=n;b&&i--;)
		if(table[i][n-i-1]!=turn)
			b=0;
	if(b)
		return 1;
	b=1;
	for(size_t i=n;i--;b=1){
		for(size_t j=n;b&&j--;)
			if(table[i][j]!=turn)
				b=0;
		if(b)
			return 1;
		b=1;
		for(size_t j=n;b&&j--;)
			if(table[j][i]!=turn)
				b=0;
		if(b)
			return 1;
	}
	return 0;
}
int main(){
	size_t x,y;
	while(1){
		printf("New game...\n");
		start:
		printf("\nThe number of the columns/rows (must be more than 2): "),scanf("%zu",&n);
		if(n<3){
			printf("\nThe number you entered isn't bigger than 2!\n");
			goto start;
		}
		char **table=(char**)malloc(sizeof(char*)*n);
		for(size_t i=n;i--;){
			table[i]=(char*)malloc(sizeof(char)*n);
			for(size_t j=n;j--;)
				table[i][j]=' ';
		}
		for(auto i=(float)n*n;i--;){
			turn:
			drawTable(table);
			printf("The numbers of the column & row from top right to put the %c (in order and seperated by newline(s), tab(s) or space(s)): ",outputTurn(i/2)),scanf("%zu%zu",&x,&y);
			if(x>n||!x--||y>n||!y--||table[y][x]!=' '){
				printf("\nInvalid position!\n");
				goto turn;
			}
			table[y][x]=outputTurn(i/2);
			if(win(table,outputTurn(i/2))){
				printf("\n%c is the winner!\n",outputTurn(i/2)),drawTable(table);
				break;
			}
			if(!i)
				printf("\nIt's a draw!\n"),drawTable(table);
		}
		while(n--)
			free(table[n]);
		free(table);
	}
	return 0;
}
