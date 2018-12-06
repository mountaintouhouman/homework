#include<stdio.h>
#include<stdlib.h>
#include<time.h>




char map[12][13]={
			"************",
			"*          *",
			"*          *",
			"*          *",
			"*          *",
			"*          *",
			"*          *",
			"*          *",
			"*          *",
			"*          *",
			"*          *",
			"************"
			};


int headX=1,headY=1;


void printfMap(void){
		system("cls");
		map[headX][headY]='H';
	
	//map
	
	for(int i=0;i<12;++i){
		printf("%s\n",map[i]);
		
	
};

};


int main(void){
	
	printfMap();
	
	char control=0;
	
	while(1){
	map[headX][headY]=' ';
	scanf("%c",&control);
	if(control=='s'||control=='S'){
		++headX;
	}else if(control=='w'||control=='W'){
		--headX;
	}else if(control=='a'||control=='A'){
		--headY;
	}else if(control=='d'||control=='D'){
		++headY;
	};
	
	printfMap();
	
	};
	
	return 0;
}
