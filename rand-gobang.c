#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 2

#define MAXIN 100

void initRecordBorard(void);
void recordtoDisplayArray(void);
void displayBoard(void);


//棋盘使用的是GBK编码，每一个中文字符占用2个字节。

//棋盘基本模板 
char aInitDisplayBoardArray[SIZE][SIZE*CHARSIZE+1] = {
	"┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
};
	//此数组用于显示棋盘 
char aDisplayBoardArray[SIZE][SIZE*CHARSIZE+1];
//各种棋子 
char play1Pic[]="●";//黑棋子;
char play1CurrentPic[]="▲"; 
char play2Pic[]="◎";//白棋子;
char play2CurrentPic[]="△";
//此数组用于记录棋盘格局 
int aRecordBoard[SIZE][SIZE];

int getPic(int turn);
int getPicVs(int turn);
int fool(int turn);
int win(int player,int x,int y);

int PeopleVsPeople(void);
int PeopleVsComputer(void);

static int x,y;
static int player;

int main(){
	int reset=1;
	while(reset==1){
		reset=0;
		x=y=1000;
		initRecordBorard();//初始化置0
		recordtoDisplayArray();//转换棋盘
		displayBoard();//显示棋盘
		int mode=100;
		int winner=0;
		do{
			printf("人人对战请按1，人机对战请按2（退出请按0）：");
			scanf("%d",&mode);
			fflush(stdin);
			if(mode!=0 && mode!=1 && mode!=2){
				printf("\t请检查您的输入，然后重新输入。\n");
			}
		}while(mode!=0 && mode!=1 && mode!=2);

		if(mode==0){
			return 1;
		}else if(mode==1){
			winner=PeopleVsPeople();
		}else if(mode==2){
			winner=PeopleVsComputer();
		}
		switch(winner){
			case 11:
		      	printf("--------Player1 vs Player2--------\n");
				printf("\n\tThe winner is Player1.\n");
				break;
			case 12:
				printf("--------Player1 vs Player2--------\n");
				printf("\n\tThe winner is Player2.\n");
				break;
			case 21:
				printf("\n\tThe winner is Computer!\n");
				break;
			case 22:
				printf("\n\tThe winner is Player.\n");
				break;
			case 23:
				printf("\n\tThe winner is Player.\n");
				break;
			case 24:
				printf("\n\tThe winner is Computer!\n");
				break;
			case 3:
				printf("\n\tIt ends in a draw.\n");
				break;
			case 0:
				break;
			default:
				printf("\n\tSomething wrong?\n");
		}
		printf("\n再来一局请按1，结束请按任意键：");
		scanf("%d",&reset);
		fflush(stdin);
	}
    return 0;
}

int PeopleVsPeople(void){
	int player=1;
	int turn=1;
	int ifwin;
	while(turn<225){
		printf("--------Player1 vs Player2--------\n");
		ifwin=getPic(turn);
		//判断胜负
		if(ifwin==1){//player1 wins
			return 11;
		}else if(ifwin==2){//player2 wins
			return 12;
		}else if(ifwin==0){
			return 0;
		}
		turn++;
	}
	return 3;//平局
}

int PeopleVsComputer(void){
	int player=1;
	int turn=1;
	int ifwin;
	int whofirst=0;//电脑先为1，Player先为2；
	do{
		printf("电脑执黑请按1，玩家执黑请按2（退出请按0）：");
		scanf("%d",&whofirst);
		fflush(stdin);
		if(whofirst!=0 && whofirst!=1 && whofirst!=2){
			printf("\t请检查您的输入，然后重新输入。\n");
		}
	}while(whofirst!=0 && whofirst!=1 && whofirst!=2);
	if(whofirst==0){
		return 0;//退出
	}
	while(turn<225){
		if(whofirst==1){
			printf("-------Computer vs Player-------\n");
			if(turn%2==1){
				ifwin=fool(turn);
			}else{
				ifwin=getPicVs(turn);
			}
		}else if(whofirst==2){
			printf("-------Player vs Computer-------\n");
			if(turn%2==1){
				ifwin=getPicVs(turn);
			}else{
				ifwin=fool(turn);
			}
		}else{
			printf("Losing First!");
		}

		//判断胜负
		if(whofirst==1 && ifwin==1){//player1 wins
			return 21;
		}else if(whofirst==1 && ifwin==2){//player2 wins
			return 22;
		}else if(whofirst==2 && ifwin==1){//player1 wins
			return 23;
		}else if(whofirst==2 && ifwin==2){//player2 wins
			return 24;
		}else if(ifwin==0){
			return 0;
		}
		turn++;
	}
	return 3;
}

int getPic(int turn){
	char input[MAXIN];
	int len;
	if(turn>1){
		aRecordBoard[x][y]-=2;
		printf("第%d回合，Player%d落子的位置为：%d%c\n",turn/2,player,SIZE-x,y+'A');
	}
	printf("(退出请按0)\n");
	player=((turn%2)==0)?2:1;

	do{
		do{
			do{
				printf("Player%d: please enter your piece(number character):",player);
				scanf("%s",input);
				fflush(stdin);
				len=strlen(input);
				if(input[0]=='0'){
					return 0;//退出
				}
				if(len!=2 && len!=3){
					printf("Wrong Input!\n");
				}
			}while(len!=2 && len!=3);

				if(len==2){
					x=(int)(SIZE-input[0]+'0');
				}else{
					x=(int)(SIZE-(input[0]-'0')*10-input[1]+'0');
				}
				if(input[len-1]<'P' && input[len-1]>='A'){
					y=(int)(input[len-1]-'A');
				}else if(input[len-1]>='a' && input[len-1]<'p'){
					y=(int)(input[len-1]-'a');
				}else{
					y=-1000;
					printf("y is wrong.\n");
				}

			if(x<0 || x>SIZE-1 || (y>-1000 && y<0) || y<-1000 || y>SIZE-1){
				printf("棋盘外落子，请重新落子\n");
			}
		}while(x<0 || x>SIZE-1 || y<0 || y>SIZE-1);
			if(aRecordBoard[x][y]!=0){
				printf("已经有子，请重新落子\n");
		}
	}while(aRecordBoard[x][y]!=0);

	aRecordBoard[x][y]=player+2;
	recordtoDisplayArray();
	displayBoard();
	return win(player,x,y);
}

int fool(int turn){
	char input[MAXIN];
	int len;
	player=((turn%2)==0)?2:1;
	if(turn>1){
		aRecordBoard[x][y]-=2;
	}
	do{
		x=rand()%14;
		y=rand()%14;
	}while(aRecordBoard[x][y]!=0);
	aRecordBoard[x][y]=player+2;
	recordtoDisplayArray();
	displayBoard();
	return win(player,x,y);
}

int getPicVs(int turn){
	char input[MAXIN];
	int len;
	if(turn>1){
		aRecordBoard[x][y]-=2;
		printf("第%d回合，Computer落子的位置为：%d%c\n",turn/2,SIZE-x,y+'A');
	}
	printf("(退出请按0)\n");
	player=((turn%2)==0)?2:1;

	do{
		do{
			do{
				printf("Player%d: please enter your piece(number character):",player);
				scanf("%s",input);
				fflush(stdin);
				len=strlen(input);
				if(input[0]=='0'){
					return 0;//退出
				}
				if(len!=2 && len!=3){
					printf("Wrong Input!\n");
				}
			}while(len!=2 && len!=3);

				if(len==2){
					x=(int)(SIZE-input[0]+'0');
				}else{
					x=(int)(SIZE-(input[0]-'0')*10-input[1]+'0');
				}
				if(input[len-1]<'P' && input[len-1]>='A'){
					y=(int)(input[len-1]-'A');
				}else if(input[len-1]>='a' && input[len-1]<'p'){
					y=(int)(input[len-1]-'a');
				}else{
					y=-1000;
					printf("y is wrong.\n");
				}

			if(x<0 || x>SIZE-1 || (y>-1000 && y<0) || y<-1000 || y>SIZE-1){
				printf("棋盘外落子，请重新落子\n");
			}
		}while(x<0 || x>SIZE-1 || y<0 || y>SIZE-1);
			if(aRecordBoard[x][y]!=0){
				printf("已经有子，请重新落子\n");
		}
	}while(aRecordBoard[x][y]!=0);

	aRecordBoard[x][y]=player+2;
	recordtoDisplayArray();
	displayBoard();
	return win(player,x,y);
}

int win(int player,int x,int y){
	int total=1;
	int i=1,j=1;

	while(aRecordBoard[x][y+i]==player && x>=0 && x<=SIZE-1 && y>=0 && y<=SIZE-1){
		i++;
		total++;
		if(total==5){
			return player;
		}
	}
	i=1;
	while(aRecordBoard[x][y-i]==player && x>=0 && x<=SIZE-1 && y>=0 && y<=SIZE-1){
		i++;
		total++;
		if(total==5){
			return player;
		}
	}

	i=1;
	total=1;
	while(aRecordBoard[x-i][y]==player && x>=0 && x<=SIZE-1 && y>=0 && y<=SIZE-1){
		i++;
		total++;
		if(total==5){
			return player;
		}
	}
	i=1;
	while(aRecordBoard[x+i][y]==player && x>=0 && x<=SIZE-1 && y>=0 && y<=SIZE-1){
		i++;
		total++;
		if(total==5){
			return player;
		}
	}

	i=1;
	total=1;
	while(aRecordBoard[x-i][y-j]==player && x>=0 && x<=SIZE-1 && y>=0 && y<=SIZE-1){
		i++;
		j++;
		total++;
		if(total==5){
			return player;
		}
	}
	i=1;
	j=1;
	while(aRecordBoard[x+i][y+j]==player && x>=0 && x<=SIZE-1 && y>=0 && y<=SIZE-1){
		i++;
		j++;
		total++;
		if(total==5){
			return player;
		}
	}

	i=1;
	j=1;
	total=1;
	while(aRecordBoard[x+i][y-j]==player && x>=0 && x<=SIZE-1 && y>=0 && y<=SIZE-1){
		i++;
		j++;
		total++;
		if(total==5){
			return player;
		}
	}
	i=1;
	j=1;
	while(aRecordBoard[x-i][y+j]==player && x>=0 && x<=SIZE-1 && y>=0 && y<=SIZE-1){
		i++;
		j++;
		total++;
		if(total==5){
			return player;
		}
	}
	return 3;
}

//初始化棋盘格局 
void initRecordBorard(void){
//通过双重循环，将aRecordBoard清0
	int i,j;
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
			aRecordBoard[i][j]=0;
}

//将aRecordBoard中记录的棋子位置，转化到aDisplayBoardArray中
void recordtoDisplayArray(void){
	int i,j;
//第一步：将aInitDisplayBoardArray中记录的空棋盘，复制到aDisplayBoardArray中
    for(i=0;i<SIZE;i++)
		for(j=0;j<=SIZE*CHARSIZE+1;j++)
			aDisplayBoardArray[i][j]=aInitDisplayBoardArray[i][j];
//第二步：扫描aRecordBoard，当遇到非0的元素，将●或者◎复制到aDisplayBoardArray的相应位置上
//注意：aDisplayBoardArray所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			if(aRecordBoard[i][j]==1){
				aDisplayBoardArray[i][CHARSIZE*j]=play1Pic[0];
				aDisplayBoardArray[i][CHARSIZE*j+1]=play1Pic[1];
			}else if(aRecordBoard[i][j]==2){
				aDisplayBoardArray[i][CHARSIZE*j]=play2Pic[0];
				aDisplayBoardArray[i][CHARSIZE*j+1]=play2Pic[1];
			}else if(aRecordBoard[i][j]==3){
				aDisplayBoardArray[i][CHARSIZE*j]=play1CurrentPic[0];
				aDisplayBoardArray[i][CHARSIZE*j+1]=play1CurrentPic[1];
			}else if(aRecordBoard[i][j]==4){
				aDisplayBoardArray[i][CHARSIZE*j]=play2CurrentPic[0];
				aDisplayBoardArray[i][CHARSIZE*j+1]=play2CurrentPic[1];
			}
		}
	}		
}

//显示棋盘格局 
void displayBoard(void){
	int i;
	//第一步：清屏
	system("cls");
	printf("Gobang(五子棋)\t Author:葛忠鑫\n");
	//第二步：将aDisplayBoardArray输出到屏幕上
	for(i=0;i<SIZE;i++)
		printf("%2d%s\n",SIZE-i,aDisplayBoardArray[i]);
	//第三步：输出最下面的一行字母A B .... )
	printf("   A B C D E F G H I J K L M N O \n");
} 