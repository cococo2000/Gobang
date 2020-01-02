#include<stdio.h>
#define SIZE 15
#define BLACK 1
#define WHITE 2
//关于direction
#define Horizontal 10
#define Vertical 20
#define RightBevel 30//右斜
#define LeftBevel 40//左斜
#define PSIZE 4//棋形的半宽
int aRecordBoard[SIZE][SIZE]={
    {2,1,4,0,1,2,3,1,1,0,0,2,4,1,2},
    {1,2,1,4,0,1,2,3,1,1,0,0,2,4,1},
    {3,1,2,1,4,0,1,2,3,1,1,0,0,2,4},
    {4,2,1,4,0,1,2,3,1,1,0,0,2,2,1},
    {2,1,4,0,1,2,3,1,1,0,0,2,4,1,2},
    {1,2,1,4,0,1,2,3,1,1,0,0,2,4,1},
    {3,1,2,1,4,0,1,2,3,1,1,0,0,2,4},
    {4,2,1,4,0,1,2,3,1,1,0,0,2,2,1},
    {3,1,2,1,4,0,1,2,3,1,1,0,0,2,4},
    {4,2,1,4,0,1,2,3,1,1,0,0,2,2,1},
    {2,1,4,0,1,2,3,1,1,0,0,2,4,1,2},
    {1,2,1,4,0,1,2,3,1,1,0,0,2,4,1},
    {3,1,2,1,4,0,1,2,3,1,1,0,0,2,4},
    {4,2,1,4,0,1,2,3,1,1,0,0,2,2,1},
    {3,1,2,1,4,0,1,2,3,1,1,0,0,2,4},
};
char code[10]="0";
int power(int x);
char* pattern(int x,int y,int color,int direction);
int strindex(char s[],char t[]);
int main(){
	int k;
    int x=0,y=6,color=1;
    printf("%s\n",pattern(x,y,color,Horizontal));
	k=strindex(code,"1100");
	printf("%d\n",k);
    return 0;
}

char* pattern(int x,int y,int color,int direction){
	int mark=555515555;
	int i;
	int othercolor;
	othercolor=(color==BLACK)?WHITE:BLACK;
	if(direction==Horizontal){
		for(i=1;i<=PSIZE && x>=0 && x<=SIZE-1 && y-i>=0 && y-i<=SIZE-1;i++){
			if(aRecordBoard[x][y-i]==color || aRecordBoard[x][y-i]==color+2){
				mark+=(1-5)*power(PSIZE+i);
			}else if(aRecordBoard[x][y-i]==othercolor || aRecordBoard[x][y-i]==othercolor+2){
				mark+=(2-5)*power(PSIZE+i);
			}else if(aRecordBoard[x][y-i]==0){
				mark-=5*power(PSIZE+i);
			}
		}
		for(i=1;i<=PSIZE && x>=0 && x<=SIZE-1 && y+i>=0 && y+i<=SIZE-1;i++){
			if(aRecordBoard[x][y+i]==color || aRecordBoard[x][y+i]==color+2){
				mark+=(1-5)*power(PSIZE-i);
			}else if(aRecordBoard[x][y+i]==othercolor || aRecordBoard[x][y+i]==othercolor+2){
				mark+=(2-5)*power(PSIZE-i);
			}else if(aRecordBoard[x][y+i]==0){
				mark-=5*power(PSIZE-i);
			}
		}
	}else if(direction==Vertical){
		for(i=1;i<=PSIZE && x-i>=0 && x-i<=SIZE-1 && y>=0 && y<=SIZE-1;i++){
			if(aRecordBoard[x-i][y]==color || aRecordBoard[x-i][y]==color+2){
				mark+=(1-5)*power(PSIZE+i);
			}else if(aRecordBoard[x-i][y]==othercolor || aRecordBoard[x-i][y]==othercolor+2){
				mark+=(2-5)*power(PSIZE+i);
			}else if(aRecordBoard[x-i][y]==0){
				mark-=5*power(PSIZE+i);
			}
		}
		for(i=1;i<=PSIZE && x+i>=0 && x+i<=SIZE-1 && y>=0 && y<=SIZE-1;i++){
			if(aRecordBoard[x+i][y]==color || aRecordBoard[x+i][y]==color+2){
				mark+=(1-5)*power(PSIZE-i);
			}else if(aRecordBoard[x+i][y]==othercolor || aRecordBoard[x+i][y]==othercolor+2){
				mark+=(2-5)*power(PSIZE-i);
			}else if(aRecordBoard[x+i][y]==0){
				mark-=5*power(PSIZE-i);
			}
		}
	}else if(direction==RightBevel){
		for(i=1;i<=PSIZE && x-i>=0 && x-i<=SIZE-1 && y-i>=0 && y-i<=SIZE-1;i++){
			if(aRecordBoard[x-i][y-i]==color || aRecordBoard[x-i][y-i]==color+2){
				mark+=(1-5)*power(PSIZE+i);
			}else if(aRecordBoard[x-i][y-i]==othercolor || aRecordBoard[x-i][y-i]==othercolor+2){
				mark+=(2-5)*power(PSIZE+i);
			}else if(aRecordBoard[x-i][y-i]==0){
				mark-=5*power(PSIZE+i);
			}
		}
		for(i=1;i<=PSIZE && x+i>=0 && x+i<=SIZE-1 && y+i>=0 && y+i<=SIZE-1;i++){
			if(aRecordBoard[x+i][y+i]==color || aRecordBoard[x+i][y+i]==color+2){
				mark+=(1-5)*power(PSIZE-i);
			}else if(aRecordBoard[x+i][y+i]==othercolor || aRecordBoard[x+i][y+i]==othercolor+2){
				mark+=(2-5)*power(PSIZE-i);
			}else if(aRecordBoard[x+i][y+i]==0){
				mark-=5*power(PSIZE-i);
			}
		}
	}else if(direction==LeftBevel){
		for(i=1;i<=PSIZE && x+i>=0 && x+i<=SIZE-1 && y-i>=0 && y-i<=SIZE-1;i++){
			if(aRecordBoard[x+i][y-i]==color || aRecordBoard[x+i][y-i]==color+2){
				mark+=(1-5)*power(PSIZE+i);
			}else if(aRecordBoard[x+i][y-i]==othercolor || aRecordBoard[x+i][y-i]==othercolor+2){
				mark+=(2-5)*power(PSIZE+i);
			}else if(aRecordBoard[x+i][y-i]==0){
				mark-=5*power(PSIZE+i);
			}
		}
		for(i=1;i<=PSIZE && x-i>=0 && x-i<=SIZE-1 && y+i>=0 && y+i<=SIZE-1;i++){
			if(aRecordBoard[x-i][y+i]==color || aRecordBoard[x-i][y+i]==color+2){
				mark+=(1-5)*power(PSIZE-i);
			}else if(aRecordBoard[x-i][y+i]==othercolor || aRecordBoard[x-i][y+i]==othercolor+2){
				mark+=(2-5)*power(PSIZE-i);
			}else if(aRecordBoard[x-i][y+i]==0){
				mark-=5*power(PSIZE-i);
			}
		}
	}else{
		printf("pattern error.\n");
	}
	i=8;
	do{
		code[i--]=mark%10+'0';
		mark/=10;
	}while(i>=0);
	code[9]='\0';
	return code;
}

int power(int x){
    int i;
    int sum=1;
    for(i=0;i<x;i++){
        sum=sum*10;
    }
    return sum;
}

int strindex(char s[],char t[]){
    int i,j,k;
    for(i=0;s[i]!='\0';i++){
        for(j=i,k=0;t[k]!='\0' && s[j]==t[k];j++,k++)
            ;
        if(k>0 && t[k]=='\0')
            return i;
    }
    return -1;
}