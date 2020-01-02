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
void changeloc(int location,int *x, int *y,int direction);
int main(){
    int x=5,y=5;
    int location=-2;
    changeloc(location,&x,&y,LeftBevel);
    printf("%d %d\n",x,y);
    return 0;
}


void changeloc(int location,int *x, int *y,int direction){
	if(direction==Horizontal){
		*y+=location;
	}else if(direction==Vertical){
		*x+=location;
	}else if(direction==RightBevel){
		*x+=location;
		*y+=location;
	}else if(direction==LeftBevel){
		*x-=location;
		*y+=location;
	}
}