#include<cmath>
#include<iostream>
unsigned long long n;
char outputTurn(float i){
	return 'X'*(floor(i)==i)+'O'*(floor(i)!=i);
}
void drawTable(char **table){
	for(unsigned long long i=0;i<n;i++){
		if(i)
			for(float j=(float)n*2-1;j--;)
				if(j/2>floor(j/2))
					std::cout<<'+';
				else
					std::cout<<'-';
		std::cout<<'\n';
		for(unsigned long long j=0;j<n;j++){
			if(j)
				std::cout<<'|';
			std::cout<<table[i][j];
		}
		std::cout<<'\n';
	}
	std::cout<<'\n';
	return;
}
bool win(char **table,const char turn){
	bool b=1;
	for(unsigned long long i=n;b&&i--;)
		if(table[i][i]!=turn)
			b=0;
	if(b)
		return 1;
	b=1;
	for(unsigned long long i=n;b&&i--;)
		if(table[i][n-i-1]!=turn)
			b=0;
	if(b)
		return 1;
	b=1;
	for(unsigned long long i=n;i--;b=1){
		for(unsigned long long j=n;b&&j--;)
			if(table[i][j]!=turn)
				b=0;
		if(b)
			return 1;
		b=1;
		for(unsigned long long j=n;b&&j--;)
			if(table[j][i]!=turn)
				b=0;
		if(b)
			return 1;
	}
	return 0;
}
int main(){
	unsigned long long x,y;
	while(1){
		std::cout<<"New game...\n";
		start:
		std::cout<<"\nThe number of the columns/rows (must be more than 2): ",std::cin>>n;
		if(n<3){
			std::cout<<"\nThe number you entered isn't bigger than 2!\n";
			goto start;
		}
		char **table=new char*[n];
		for(unsigned long long i=n;i--;){
			table[i]=new char[n];
			for(unsigned long long j=n;j--;)
				table[i][j]=' ';
		}
		for(float i=(float)n*n;i--;){
			turn:
			drawTable(table);
			std::cout<<"The numbers of the column & row from top right to put the "<<outputTurn(i/2)<<" (in order and seperated by newline(s), tab(s) or space(s)): ",std::cin>>x>>y;
			if(!x--||x>=n||!y--||y>=n||table[y][x]!=' '){
				std::cout<<"\nInvalid position!\n";
				goto turn;
			}
			table[y][x]=outputTurn(i/2);
			if(win(table,outputTurn(i/2))){
				std::cout<<'\n'<<outputTurn(i/2)<<" is the winner!\n";
				drawTable(table);
				break;
			}
			if(!i){
				std::cout<<"\nIt's a draw!\n";
				drawTable(table);
			}
		}
		delete table;
	}
	return 0;
}
