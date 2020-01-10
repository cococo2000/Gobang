#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15 //棋盘的大小
#define CHARSIZE 2 //GBK棋子和棋盘字符所占字节数

#define MAXIN 100 //最大的键盘输入控制量的长度

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
char play1CurrentPic[]="▲"; //黑棋上一步落子位置
char play2Pic[]="◎";//白棋子;
char play2CurrentPic[]="△";//白棋子上一步落子位置

//此数组用于记录棋盘格局 
int aRecordBoard[SIZE][SIZE];
//黑棋分数表
int ScoreBoardBlack[SIZE][SIZE];
//白旗分数表
int ScoreBoardWhite[SIZE][SIZE];
//棋子颜色代号
#define BLACK 1 
#define WHITE 2

//关于direction的代号和值
#define Horizontal 10  //水平方向
#define Vertical 20 //垂直方向
#define RightBevel 30//右斜
#define LeftBevel 40//左斜

//棋形的半宽,即判断一个点棋形时左右扫描的点数
#define PSIZE 4

int getPic(int turn);  //人人对战时的落子控制
int getPicVs(int turn); //人机对战时的人方落子控制
int fool(int turn); //傻子ai
int win(int player,int x,int y); //判断输赢
int forbidden(int x,int y);//外部用
int forbidd(int x,int y);//内部用
int countline(int player,int x,int y,int direction); //数连子数
char code[10]="0";
char* pattern(int x,int y,int color,int direction); //棋形编码函数，编码为长度为九的字符串
void AIfind(int *ai_x,int *ai_y,int turn); //人机对战时机器落子函数

int score(int i,int j,char code[],int color);//赋分函数
//赋分参数如下
#define WIN5 1000000 //成5的棋形,即下一步就可以赢的棋形
#define LIVE4 250000 //活四011110,有两个点可以成五
#define JUMP4ss 160000 //跳冲四且堵后仍可形成冲三，即#1011100，且能冲四
#define JUMP4s 150000 //跳冲四且堵后仍可形成冲三，即#101110#。但不能冲四
#define JUMP4bss 140000 //1101100正中间缺子的冲四，且一边有两个空处
#define JUMP4bs 130000 //110110正中间缺子的冲四，且一边有一个空处
#define HALF4 120000 //冲四
//以上为一级棋形，不堵马上就会输的
#define LIVE3 55000 //活三，能形成两个活四
#define HALFLIVE3 50000 //半活半冲三：一点可以形成活四，另一点只能形成冲四
//以上为二级棋形，除非自己成四，必须马上堵
#define JUMP3bbsss 20500 //10011000跳三，中间空两格，且另一侧三个空位，两个点冲四
#define HALFHALFLIVE3 20000 //双冲三，两个点可以形成冲四
#define JUMP3bbss 20000 //1001100跳三，中间空两格，且另一侧2个空位，两个点冲四
#define JUMP3bss 19000 //101100跳三，中间空一格，另一侧空两格，？点冲四，可形成101101
#define JUMP3bbs 17500 //100110跳三，中间空两格，且另一侧1个空位，两个点冲四
#define JUMP3bs 14000 //10110跳三，中间空一格，且另一侧1个空位，两个点冲四
#define HALF3 10000 //只能形成一个冲四的三
#define LIVE2bbbsssp 6700 //活二且形如 100011000 可以连五甚至长连,另一侧三个空
#define LIVE2bbbssp 6600 //活二且形如 10001100 可以连五甚至长连，另一侧两个空
#define LIVE2sss0 6500 //活二且形如 000011000 可以连五,可能长连，两端分别空4，3个
#define LIVE2ss00 6400 //活二且形如 00001100 可以连五,两端分别空4，2个
#define LIVE2sss 6200 //活二且形如 00011000 可以连五,不能长连,两端都是三个
#define LIVE2ss0 6000 //活二且形如 0001100 可以连五,两端分别空3，2个
#define LIVE2ss 5500 //活二且形如 001100 可以连五,不能长连,两端都是2个
#define LIVE2s0 5200 //活二且形如 00110 可以连五,两端分别空1，2个
//以上为三级棋形，取胜的趋向较大
//以下大多为两子棋形，b代表棋形中的空，s代表基本棋形外的对称空，0代表不对称空
#define JUMP2bbbssss 2500 //100010000
#define JUMP2bbssss 2300 //10010000
#define JUMP2bbsss 2100 //1001000
#define JUMP2bbbsss 2000 //10001000
#define JUMP2bbbss 1500 //1000100
#define	JUMP2bbss 1300 //100100
#define JUMP2bbbs 1200 //100010
#define HALF2 1000 //冲二
#define LIVE1ssss 600 //活一，两边均有4个空格
#define LIVE1sss0 550 //活一，两边的空格数分别为3，4
#define LIVE1sss 500
#define LIVE1ss0 450
#define LIVE1ss 200
//空位
#define BLANK 20
int findmax(int color,int *temp_x,int *temp_y); //找到赋分表中的最大值

int blackhuosi(int x,int y,int direction); //黑棋活四判断
int blackchongsi(int x,int y,int direction); //黑棋冲四判断
int blackhuosan(int x,int y,int direction); //黑棋活三判断

int strindex(char s[],char t[]); //在字符串s中查找t字符串是否存在，用于判断棋形
int power(int x);//计算幂次
void changeloc(int location,int *x, int *y,int direction);//根据方向改变点的坐标

int PeopleVsPeople(void); //人人对战函数
int PeopleVsComputer(void); //人机对战函数

static int x,y; //记录当前落子，是电脑棋盘的坐标
static int player; //记录当前玩家，1为黑棋，2为白旗

//主函数，根据输入选择人人、人机模式，并且输出胜负，结束游戏后询问是否再来一盘
int main(){
	int reset=1;//初始化变量，当reset为1时，Gobang初始化
	while(reset==1){
		reset=0;//初始化变量赋0
		x=y=1000;//初始化落子，使落子在外部即可
		initRecordBorard();//初始化置0
		recordtoDisplayArray();//转换棋盘
		displayBoard();//显示棋盘
		int mode=100;//初始化模式选择，赋一个非法模式值即可
		int winner=0;//记录赢家，1为黑棋赢，2为白棋赢，3为平局
		do{
			printf("人人对战请按1，人机对战请按2（退出请按0）：");//提示使用者输入选择模式
			scanf("%d",&mode);
			fflush(stdin);//清空缓存区
			if(mode!=0 && mode!=1 && mode!=2){
				printf("\t请检查您的输入，然后重新输入。\n");//玩家输入错误后报错，并提示玩家
			}
		}while(mode!=0 && mode!=1 && mode!=2);

		if(mode==0){//玩家选择0，则退出游戏（程序）
			return 1;
		}else if(mode==1){//模式一：人人对战
			winner=PeopleVsPeople();
		}else if(mode==2){//模式二：人机对战
			winner=PeopleVsComputer();
		}
		switch(winner){//输出游戏结果，十位的1、2代表模式，个位的1、2等代表赢棋方，其中人机模式下有两种先手情况，故有四种赢家情况输出
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
		printf("\n再来一局请按1，结束请按任意键：");//游戏结束，提醒玩家是否再来一局
		scanf("%d",&reset);
		fflush(stdin);//清空缓存区
	}
    return 0;//退出程序
}

int PeopleVsPeople(void){
	int player=1;//记录当前玩家
	int turn=1;//记录当前落子数
	int ifwin;//记录是否有人赢了，以及赢家是谁
	while(turn<225){
		printf("--------Player1 vs Player2--------\n");
		ifwin=getPic(turn);//将落子数传给轮流落子函数
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
	int player=1;//记录当前玩家
	int turn=1;//记录当前落子数
	int ifwin;//记录是否有人赢了，以及赢家是谁
	int whofirst=0;//电脑先为1，Player先为2；
	do{
		printf("电脑执黑请按1，玩家执黑请按2（退出请按0）：");
		scanf("%d",&whofirst);//人机模式下提示玩家选择先手or后手
		fflush(stdin);//清空缓存区
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

		//判断胜负，返回胜利者或者平局代号
		if(whofirst==1 && ifwin==1){//player1 wins（电脑先手）
			return 21;
		}else if(whofirst==1 && ifwin==2){//player2 wins（电脑先手）
			return 22;
		}else if(whofirst==2 && ifwin==1){//player1 wins（玩家先手）
			return 23;
		}else if(whofirst==2 && ifwin==2){//player2 wins（玩家先手）
			return 24;
		}
		else if(ifwin==0){
			return 0;
		}
		turn++;
	}
	return 3;
}

//人机模式下的轮流落子函数
int getPic(int turn){
	char input[MAXIN];//储存键盘输入内容
	int len;//存储键盘输入内容的长度
	if(turn>1){
		aRecordBoard[x][y]-=2;//将三角标注的棋子还原成正常棋子，即将上一步落子还原
		printf("第%d回合，Player%d落子的位置为：%d%c\n",turn/2,player,SIZE-x,y+'A');//输出回合数和玩家？的落子坐标（玩家可见棋盘上的坐标）
	}
	printf("(退出请按0)\n");
	player=((turn%2)==0)?2:1;//根据落子数判断当期落子人

	do{
		do{
			do{
				printf("Player%d: please enter your piece(number character):",player);//提示玩家输入落子信息
				scanf("%s",input);
				fflush(stdin);
				//判断输入是否合法，不合法则提醒并重新输入
				len=strlen(input);
				if(input[0]=='0'){
					return 0;//退出
				}
				if(len!=2 && len!=3){
					printf("Wrong Input!\n");
				}
			}while(len!=2 && len!=3);
				//转换玩家可见坐标与电脑存储棋盘的坐标
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
			//判断落子棋盘外？
			if(x<0 || x>SIZE-1 || (y>-1000 && y<0) || y<-1000 || y>SIZE-1){
				printf("棋盘外落子，请重新落子\n");
			}
		}while(x<0 || x>SIZE-1 || y<0 || y>SIZE-1);
		//判断玩家落子位置是否已经有人落子
			if(aRecordBoard[x][y]!=0){
				printf("已经有子，请重新落子\n");
		}
	}while(aRecordBoard[x][y]!=0);
	//确认输入正确后，给电脑棋盘落子（三角形的）
	aRecordBoard[x][y]=player+2;
	recordtoDisplayArray();
	displayBoard();
	//如果是黑棋，判断是否禁手，禁手则输出“禁手”，返回白棋赢
	if(player==1 && forbidden(x,y)==1){
		printf("黑棋禁手!\n");
		return 2;
	}
	return win(player,x,y);
}//判断是否在当前赢棋，返回赢家

int fool(int turn){
	player=((turn%2)==0)?2:1;//判断当前玩家
	if(turn>1){
		aRecordBoard[x][y]-=2;//还原三角形棋子
	}
	if(turn==1){
		x=y=7;//如果电脑是黑棋，第一步落在天元，即8H
	}else{
		int ai_x,ai_y;//存储ai落子位置
		AIfind(&ai_x,&ai_y,turn);//调用aifind找到最佳落子位置
		//将ai找到的点赋给x，y
		x=ai_x;
		y=ai_y;
		//以下注释为随机落子大猩猩
		// do{
		// 	x=rand()%14;
		// 	y=rand()%14;
		// }while(aRecordBoard[x][y]!=0);
	}
	//电脑落子，注意当前落子为三角形
	aRecordBoard[x][y]=player+2;
	recordtoDisplayArray();
	displayBoard();
	return win(player,x,y);//判断是否在当前赢棋，返回赢家
}

//人机模式下，玩家落子，与人人轮流落子相似
int getPicVs(int turn){
	char input[MAXIN];//储存键盘输入内容
	int len;//存储键盘输入内容的长度
	if(turn>1){
		aRecordBoard[x][y]-=2;//将三角标注的棋子还原成正常棋子，即将上一步落子还原
		printf("第%d回合，Computer落子的位置为：%d%c\n",turn/2,SIZE-x,y+'A');//输出回合数和玩家or电脑的落子坐标（玩家可见棋盘上的坐标）
	}
	printf("(退出请按0)\n");
	player=((turn%2)==0)?2:1;

	do{
		do{
			do{
				printf("Player%d: please enter your piece(number character):",player);//提示玩家输入落子信息
				scanf("%s",input);
				fflush(stdin);
				len=strlen(input);
				if(input[0]=='0'){
					return 0;//退出
				}
				//判断输入是否合法，不合法则提醒并重新输入
				len=strlen(input);
				if(len!=2 && len!=3){
					printf("Wrong Input!\n");
				}
			}while(len!=2 && len!=3);
				//转换玩家可见坐标与电脑存储棋盘的坐标
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
			//判断落子是否棋盘外
			if(x<0 || x>SIZE-1 || (y>-1000 && y<0) || y<-1000 || y>SIZE-1){
				printf("棋盘外落子，请重新落子\n");
			}
		}while(x<0 || x>SIZE-1 || y<0 || y>SIZE-1);
		//判断玩家落子位置是否已经有人落子
			if(aRecordBoard[x][y]!=0){
				printf("已经有子，请重新落子\n");
		}
	}while(aRecordBoard[x][y]!=0);
	//确认输入正确后，给电脑棋盘落子（三角形的）
	aRecordBoard[x][y]=player+2;
	recordtoDisplayArray();
	displayBoard();
	//判断黑棋是否禁手
	if(player==1 && forbidden(x,y)==1){
		printf("黑棋禁手!\n");
		return 2;
	}
	return win(player,x,y);//判断是否在当前赢棋，返回赢家
}

//判断x，y落下后，player玩家是否赢棋，若赢棋==5则返回player，若连子数大于5，则返回白棋WHITE（因为不管是谁，此时白棋赢了，黑棋长连禁手，白棋不禁手）
int win(int player,int x,int y){
	int total=1;//记录连子数
	int i=1;//控制移动坐标
	//四个方向依次扫描，判断输赢，一旦确认则立刻返回，不再进行接下来的扫描
	//水平
	while(aRecordBoard[x][y+i]==player && x>=0 && x<=SIZE-1 && y+i>=0 && y+i<=SIZE-1){
		i++;
		total++;
	}
	i=1;
	while(aRecordBoard[x][y-i]==player && x>=0 && x<=SIZE-1 && y-i>=0 && y-i<=SIZE-1){
		i++;
		total++;

	}
	//判断是否返回赢家
	if(total==5){
		return player;
	}else if(total>5){
		return WHITE;
	}
	//纵向
	i=1;
	total=1;
	while(aRecordBoard[x-i][y]==player && x-i>=0 && x-i<=SIZE-1 && y>=0 && y<=SIZE-1){
		i++;
		total++;
	}
	i=1;
	while(aRecordBoard[x+i][y]==player && x+i>=0 && x+i<=SIZE-1 && y>=0 && y<=SIZE-1){
		i++;
		total++;
	}
	//判断是否返回赢家
	if(total==5){
		return player;
	}else if(total>5){
		return WHITE;
	}
	//右斜
	i=1;
	total=1;
	while(aRecordBoard[x-i][y-i]==player && x-i>=0 && x-i<=SIZE-1 && y-i>=0 && y-i<=SIZE-1){
		i++;
		total++;
	}
	i=1;
	while(aRecordBoard[x+i][y+i]==player && x+i>=0 && x+i<=SIZE-1 && y+i>=0 && y+i<=SIZE-1){
		i++;
		total++;
	}
	//判断是否返回赢家
	if(total==5){
		return player;
	}else if(total>5){
		return WHITE;
	}
	//左斜
	i=1;
	total=1;
	while(aRecordBoard[x+i][y-i]==player && x+i>=0 && x+i<=SIZE-1 && y-i>=0 && y-i<=SIZE-1){
		i++;
		total++;
	}
	i=1;
	while(aRecordBoard[x-i][y+i]==player && x-i>=0 && x-i<=SIZE-1 && y+i>=0 && y+i<=SIZE-1){
		i++;
		total++;
	}
	//判断是否返回赢家
	if(total==5){
		return player;
	}else if(total>5){
		return WHITE;
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
	printf("Gobang(五子棋)\t Work of 葛忠鑫\n");
	//第二步：将aDisplayBoardArray输出到屏幕上
	for(i=0;i<SIZE;i++)
		printf("%2d%s\n",SIZE-i,aDisplayBoardArray[i]);
	//第三步：输出最下面的一行字母A B .... )
	printf("   A B C D E F G H I J K L M N O \n");
	//以下注释代码为检查黑白棋盘赋分情况时所用
	// int j;
	// for(i=0;i<SIZE;i++){
	// 	for(j=0;j<SIZE;j++){
	// 		printf("%5d  ",ScoreBoardBlack[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");
	// for(i=0;i<SIZE;i++){
	// 	for(j=0;j<SIZE;j++){
	// 		printf("%5d  ",ScoreBoardWhite[i][j]);
	// 	}
	// 	printf("\n");
	// }
} 

//判断黑棋是否禁手，有长连禁手，三三禁手和四四禁手三种情况，发现其一则禁手，返回1
int forbidden(int x,int y){
	int blacksansan(int x,int y,int direction);
	int blacksisi(int x,int y);
	if(win(BLACK,x,y)!=BLACK){
		if(countline(1,x,y,0)>5){
			printf("长连");
			return 1;
		}
		if(blacksisi(x,y)==1){
			printf("四四");
			return 1;
		}
		if(blacksansan(x,y,0)==1){
			printf("三三");
			return 1;
		}
	}else{
		return 0;
	}
}

//数出连子数一旦有大于5的连子数则返回此连子数，结束此函数
//direction为控制条件，为一时扫描四个方向返回大于五的值
//direction为有意义的指示方向的宏定义时，只扫描当前方向的连子数
int countline(int player,int x,int y,int direction){
	int total=1;
	int i=1;
	if(direction==0){//返回大于五的
		//水平
		while(aRecordBoard[x][y+i]==player && x>=0 && x<=SIZE-1 && y+i>=0 && y+i<=SIZE-1){
			i++;
			total++;
		}
		i=1;
		while(aRecordBoard[x][y-i]==player && x>=0 && x<=SIZE-1 && y-i>=0 && y-i<=SIZE-1){
			i++;
			total++;
		}
		if(total>5){
			return total;
		}
		//纵向
		i=1;
		total=1;
		while(aRecordBoard[x-i][y]==player && x-i>=0 && x-i<=SIZE-1 && y>=0 && y<=SIZE-1){
			i++;
			total++;
		}
		i=1;
		while(aRecordBoard[x+i][y]==player && x+i>=0 && x+i<=SIZE-1 && y>=0 && y<=SIZE-1){
			i++;
			total++;
		}
		if(total>5){
			return total;
		}
		//右斜
		i=1;
		total=1;
		while(aRecordBoard[x-i][y-i]==player && x-i>=0 && x-i<=SIZE-1 && y-i>=0 && y-i<=SIZE-1){
			i++;
			total++;
		}
		i=1;
		while(aRecordBoard[x+i][y+i]==player && x+i>=0 && x+i<=SIZE-1 && y+i>=0 && y+i<=SIZE-1){
			i++;
			total++;
		}
		if(total>5){
			return total;
		}
		//左斜
		i=1;
		total=1;
		while(aRecordBoard[x+i][y-i]==player && x+i>=0 && x+i<=SIZE-1 && y-i>=0 && y-i<=SIZE-1){
			i++;
			total++;
		}
		i=1;
		while(aRecordBoard[x-i][y+i]==player && x-i>=0 && x-i<=SIZE-1 && y+i>=0 && y+i<=SIZE-1){
			i++;
			total++;
		}
		if(total>5){
			return total;
		}
	}else if(direction==Horizontal){
		//水平
		while(aRecordBoard[x][y+i]==player && x>=0 && x<=SIZE-1 && y+i>=0 && y+i<=SIZE-1){
			i++;
			total++;
		}
		i=1;
		while(aRecordBoard[x][y-i]==player && x>=0 && x<=SIZE-1 && y-i>=0 && y-i<=SIZE-1){
			i++;
			total++;
		}
		if(total>5){
			return total;
		}
	}else if(direction==Vertical){
		//纵向
		i=1;
		total=1;
		while(aRecordBoard[x-i][y]==player && x-i>=0 && x-i<=SIZE-1 && y>=0 && y<=SIZE-1){
			i++;
			total++;
		}
		i=1;
		while(aRecordBoard[x+i][y]==player && x+i>=0 && x+i<=SIZE-1 && y>=0 && y<=SIZE-1){
			i++;
			total++;
		}
		if(total>5){
			return total;
		}
	}else if(direction==RightBevel){
		//右斜
		i=1;
		total=1;
		while(aRecordBoard[x-i][y-i]==player && x-i>=0 && x-i<=SIZE-1 && y-i>=0 && y-i<=SIZE-1){
			i++;
			total++;
		}
		i=1;
		while(aRecordBoard[x+i][y+i]==player && x+i>=0 && x+i<=SIZE-1 && y+i>=0 && y+i<=SIZE-1){
			i++;
			total++;
		}
		if(total>5){
			return total;
		}
	}else if(direction==LeftBevel){
		//左斜
		i=1;
		total=1;
		while(aRecordBoard[x+i][y-i]==player && x+i>=0 && x+i<=SIZE-1 && y-i>=0 && y-i<=SIZE-1){
			i++;
			total++;
		}
		i=1;
		while(aRecordBoard[x-i][y+i]==player && x-i>=0 && x-i<=SIZE-1 && y+i>=0 && y+i<=SIZE-1){
			i++;
			total++;
		}
		if(total>5){
			return total;
		}
	}else{
		printf("countline direction error.\n");
	}
	return 0;
}

//依次判断落点处的四个方向是否出现三三禁手，当多于或等于两个方向存在活三时返回1
int blacksansan(int x,int y,int direction){
	int san=0;
	if(blackhuosan(x,y,Horizontal)==1){
		san++;
	}
	if(blackhuosan(x,y,Vertical)==1){
		san++;
	}
	if(blackhuosan(x,y,RightBevel)==1){
		san++;
	}
	if(blackhuosan(x,y,LeftBevel)==1){
		san++;
	}
	if(san>=2){
		return 1;
	}else{
		return 0;
	}
}

//判断黑棋是否四四禁手
int blacksisi(int x,int y){
	int si=0;//记录活四和冲四的情形
	if(blackchongsi(x,y,Horizontal)==1 || blackhuosi(x,y,Horizontal)==1){
		si++;
	}
	if(blackchongsi(x,y,Vertical)==1 || blackhuosi(x,y,Vertical)==1){
		si++;
	}
	if(blackchongsi(x,y,RightBevel)==1 || blackhuosi(x,y,RightBevel)==1){
		si++;
	}
	if(blackchongsi(x,y,LeftBevel)==1 || blackhuosi(x,y,LeftBevel)==1){
		si++;
	}
	//下面四种特殊情形，同时会形成两个四，如果出现则给si再加1
	pattern(x,y,BLACK,Horizontal);
	if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
		si++;
	}
	pattern(x,y,BLACK,Vertical);
	if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
		si++;
	}
	pattern(x,y,BLACK,RightBevel);
	if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
		si++;
	}
	pattern(x,y,BLACK,LeftBevel);
	if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
		si++;
	}
	//如果同时出现两及以上个四则四四禁手成立，返回1
	if(si>=2){
		return 1;
	}else{
		return 0;
	}
}

//编码函数，以（x，y）为中心，向direction所指示方向左右各扫描4个棋子，并记录到9元字符数组中
//0代表空，1代表己方棋子，2代表对方棋子，5代表边界
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

//辅助函数，计算幂次
int power(int x){
    int i;
    int sum=1;
    for(i=0;i<x;i++){
        sum=sum*10;
    }
    return sum;
}

//辅助函数：比较字符串s和t，如果s中含有t，则返回1.判断棋形的重要函数
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

//判断黑棋活四，direction为控制量，其为方向时正常理解，其为0时则扫描四个方向返回
//运用递归判断复杂禁手//最后fail了
int blackhuosi(int x,int y,int direction){
	pattern(x,y,BLACK,direction);
	int temp_x,temp_y;
	int san,si;
	if(strindex(code,"011110")>=0 && strindex(code,"1011110")<0 && strindex(code,"0111101")<0){
		if(strindex(code,"011110")==0){
			temp_x=x;
			temp_y=y;
			changeloc(-4,&temp_x,&temp_y,direction);
			if(direction==Horizontal){
				san=0;
				if(blackhuosan(temp_x,temp_y,Vertical)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,RightBevel)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Vertical);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,RightBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,LeftBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(1,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Vertical)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,RightBevel)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Vertical);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,RightBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,LeftBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else if(direction==Vertical){
				san=0;
				if(blackhuosan(temp_x,temp_y,Horizontal)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,RightBevel)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Horizontal);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,RightBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,LeftBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(1,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Horizontal)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,RightBevel)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Horizontal);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,RightBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,LeftBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else if(direction==RightBevel){
				san=0;
				if(blackhuosan(temp_x,temp_y,Horizontal)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,Vertical)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Horizontal);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Vertical);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,LeftBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(1,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Horizontal)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,Vertical)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Horizontal);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Vertical);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,LeftBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else if(direction==LeftBevel){
				san=0;
				if(blackhuosan(temp_x,temp_y,Horizontal)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,Vertical)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,RightBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Horizontal);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Vertical);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,RightBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(1,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Horizontal)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,Vertical)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,RightBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Horizontal);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Vertical);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,RightBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else{
				printf("direction error(huosi0).\n");
			}
		}else if(strindex(code,"011110")==1){
			temp_x=x;
			temp_y=y;
			changeloc(-3,&temp_x,&temp_y,direction);
			if(direction==Horizontal){
				san=0;
				if(blackhuosan(temp_x,temp_y,Vertical)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,RightBevel)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Vertical);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,RightBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,LeftBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(2,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Vertical)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,RightBevel)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Vertical);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,RightBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,LeftBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else if(direction==Vertical){
				san=0;
				if(blackhuosan(temp_x,temp_y,Horizontal)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,RightBevel)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Horizontal);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,RightBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,LeftBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(2,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Horizontal)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,RightBevel)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Horizontal);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,RightBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,LeftBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else if(direction==RightBevel){
				san=0;
				if(blackhuosan(temp_x,temp_y,Horizontal)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,Vertical)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Horizontal);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Vertical);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,LeftBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(2,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Horizontal)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,Vertical)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Horizontal);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Vertical);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,LeftBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else if(direction==LeftBevel){
				san=0;
				if(blackhuosan(temp_x,temp_y,Horizontal)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,Vertical)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,RightBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Horizontal);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Vertical);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,RightBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(2,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Horizontal)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,Vertical)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,RightBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Horizontal);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Vertical);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,RightBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else{
				printf("direction error(huosi1).\n");
			}
		}else if(strindex(code,"011110")==2){
			temp_x=x;
			temp_y=y;
			changeloc(-2,&temp_x,&temp_y,direction);
			if(direction==Horizontal){
				san=0;
				if(blackhuosan(temp_x,temp_y,Vertical)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,RightBevel)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Vertical);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,RightBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,LeftBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(3,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Vertical)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,RightBevel)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Vertical);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,RightBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,LeftBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else if(direction==Vertical){
				san=0;
				if(blackhuosan(temp_x,temp_y,Horizontal)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,RightBevel)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Horizontal);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,RightBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,LeftBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(3,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Horizontal)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,RightBevel)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Horizontal);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,RightBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,LeftBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else if(direction==RightBevel){
				san=0;
				if(blackhuosan(temp_x,temp_y,Horizontal)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,Vertical)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Horizontal);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Vertical);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,LeftBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(3,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Horizontal)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,Vertical)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Horizontal);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Vertical);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,LeftBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else if(direction==LeftBevel){
				san=0;
				if(blackhuosan(temp_x,temp_y,Horizontal)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,Vertical)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,RightBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Horizontal);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Vertical);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,RightBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(3,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Horizontal)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,Vertical)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,RightBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Horizontal);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Vertical);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,RightBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else{
				printf("direction error(huosi2).\n");
			}
		}else if(strindex(code,"011110")==3){
			temp_x=x;
			temp_y=y;
			changeloc(-1,&temp_x,&temp_y,direction);
			if(direction==Horizontal){
				san=0;
				if(blackhuosan(temp_x,temp_y,Vertical)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,RightBevel)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Vertical);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,RightBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,LeftBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(4,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Vertical)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,RightBevel)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Vertical);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,RightBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,LeftBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else if(direction==Vertical){
				san=0;
				if(blackhuosan(temp_x,temp_y,Horizontal)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,RightBevel)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Horizontal);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,RightBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,LeftBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(4,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Horizontal)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,RightBevel)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Horizontal);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,RightBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,LeftBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else if(direction==RightBevel){
				san=0;
				if(blackhuosan(temp_x,temp_y,Horizontal)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,Vertical)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Horizontal);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Vertical);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,LeftBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(4,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Horizontal)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,Vertical)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,LeftBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,LeftBevel)==1 || blackhuosi(temp_x,temp_y,LeftBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Horizontal);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Vertical);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,LeftBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else if(direction==LeftBevel){
				san=0;
				if(blackhuosan(temp_x,temp_y,Horizontal)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,Vertical)==1){
					san++;
				}
				if(blackhuosan(temp_x,temp_y,RightBevel)==1){
					san++;
				}
				si=0;
				if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
					si++;
				}
				if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Horizontal);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,Vertical);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				pattern(temp_x,temp_y,BLACK,RightBevel);
				if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
					si++;
				}
				if(san<2 && si<2){
					temp_x=x;
					temp_y=y;
					changeloc(4,&temp_x,&temp_y,direction);
					san=0;
					if(blackhuosan(temp_x,temp_y,Horizontal)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,Vertical)==1){
						san++;
					}
					if(blackhuosan(temp_x,temp_y,RightBevel)==1){
						san++;
					}
					si=0;
					if(blackchongsi(temp_x,temp_y,Horizontal)==1 || blackhuosi(temp_x,temp_y,Horizontal)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,Vertical)==1 || blackhuosi(temp_x,temp_y,Vertical)==1){
						si++;
					}
					if(blackchongsi(temp_x,temp_y,RightBevel)==1 || blackhuosi(temp_x,temp_y,RightBevel)==1){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Horizontal);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,Vertical);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					pattern(temp_x,temp_y,BLACK,RightBevel);
					if(strindex(code,"1011101")>=0 || strindex(code,"11011011")>=0 || strindex(code,"111010111")>=0){
						si++;
					}
					if(san<2 && si<2){
						return 1;
					}
				}
			}else{
				printf("direction error(huosi2).\n");//出现意外报错
			}
		}
		//return 1;
	}
	return 0;
	// pattern(x,y,BLACK,direction);
	// if(strindex(code,"011110")>=0 && strindex(code,"1011110")<0 && strindex(code,"0111101")<0){
	// 	return 1;
	// }else{
	// 	return 0;
	// }
}

//判断黑棋落子后是否冲四
int blackchongsi(int x,int y,int direction){
	pattern(x,y,BLACK,direction);
	if((strindex(code,"511110")>=0 && strindex(code,"5111101")<0) || (strindex(code,"011115")>=0 && strindex(code,"1011115")<0)
	|| (strindex(code,"211110")>=0 && strindex(code,"2111101")<0) || (strindex(code,"011112")>=0 && strindex(code,"1011112")<0)
	|| strindex(code,"1011110")>=0 || strindex(code,"0111101")>=0 || 
	(strindex(code,"11101")>=0 && strindex(code,"111101")<0 && strindex(code,"111011")<0) ||
	(strindex(code,"10111")>=0 && strindex(code,"110111")<0 && strindex(code,"101111")<0) ||
	(strindex(code,"11011")>=0 && strindex(code,"111011")<0 && strindex(code,"110111")<0)){
		return 1;
	}else{
		return 0;
	}
}

//判断黑棋落下当前子后死否形成活三，direction控制扫描棋盘的方向
int blackhuosan(int x,int y,int direction){
	pattern(x,y,BLACK,direction);
	int temp_x,temp_y;
	if(strindex(code,"01110")>=0){
		if(strindex(code,"01110")==1){
			temp_x=x;
			temp_y=y;
			changeloc(-3,&temp_x,&temp_y,direction);
			if(blackhuosi(temp_x,temp_y,direction)==1){
				temp_x=x;
				temp_y=y;
				changeloc(1,&temp_x,&temp_y,direction);
				if(blackhuosi(temp_x,temp_y,direction)==1){
					return 1;
				}
			}
		}else if(strindex(code,"01110")==2){
			temp_x=x;
			temp_y=y;
			changeloc(-2,&temp_x,&temp_y,direction);
			if(blackhuosi(temp_x,temp_y,direction)==1){
				temp_x=x;
				temp_y=y;
				changeloc(2,&temp_x,&temp_y,direction);
				if(blackhuosi(temp_x,temp_y,direction)==1){
					return 1;
				}
			}
		}else if(strindex(code,"01110")==3){
			temp_x=x;
			temp_y=y;
			changeloc(-1,&temp_x,&temp_y,direction);
			if(blackhuosi(temp_x,temp_y,direction)==1){
				temp_x=x;
				temp_y=y;
				changeloc(3,&temp_x,&temp_y,direction);
				if(blackhuosi(temp_x,temp_y,direction)==1){
					return 1;
				}
			}
		}
	}else if(strindex(code,"010110")>=0){
		if(strindex(code,"010110")==0){
			temp_x=x;
			temp_y=y;
			changeloc(-2,&temp_x,&temp_y,direction);
			if(blackhuosi(temp_x,temp_y,direction)==1){
					return 1;
			}
		}else if(strindex(code,"010110")==1){
			temp_x=x;
			temp_y=y;
			changeloc(-1,&temp_x,&temp_y,direction);
			if(blackhuosi(temp_x,temp_y,direction)==1){
					return 1;
			}
		}else if(strindex(code,"010110")==3){
			temp_x=x;
			temp_y=y;
			changeloc(1,&temp_x,&temp_y,direction);
			if(blackhuosi(temp_x,temp_y,direction)==1){
					return 1;
			}
		}
	}else if(strindex(code,"011010")>=0){
		if(strindex(code,"011010")==0){
			temp_x=x;
			temp_y=y;
			changeloc(-1,&temp_x,&temp_y,direction);
			if(blackhuosi(temp_x,temp_y,direction)==1){
					return 1;
			}
		}else if(strindex(code,"011010")==2){
			temp_x=x;
			temp_y=y;
			changeloc(1,&temp_x,&temp_y,direction);
			if(blackhuosi(temp_x,temp_y,direction)==1){
					return 1;
			}
		}else if(strindex(code,"011010")==3){
			temp_x=x;
			temp_y=y;
			changeloc(2,&temp_x,&temp_y,direction);
			if(blackhuosi(temp_x,temp_y,direction)==1){
					return 1;
			}
		}
	}
	return 0;
}

//判断棋形和禁手时可能需要临时移动x，y的值，changloc用来根据传入的方向direction和偏移位置location找到需要重新判断的点
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

//找到棋盘中最有力的落子点
void AIfind(int *ai_i,int *ai_j,int turn){
	int i,j;
	int black_i,black_j,white_i,white_j;
	int maxblack,maxwhite;
	//初始化打分棋盘
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++){
			ScoreBoardBlack[i][j]=0;
			ScoreBoardWhite[i][j]=0;
		}
	//给每个空位赋分
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			if(aRecordBoard[i][j]!=0){
				ScoreBoardBlack[i][j]=0;
				ScoreBoardWhite[i][j]=0;
			}else{
				pattern(i,j,BLACK,Horizontal);
				score(i,j,code,BLACK);
				pattern(i,j,BLACK,Vertical);
				score(i,j,code,BLACK);
				pattern(i,j,BLACK,RightBevel);
				score(i,j,code,BLACK);
				pattern(i,j,BLACK,LeftBevel);
				score(i,j,code,BLACK);

				pattern(i,j,WHITE,Horizontal);
				score(i,j,code,WHITE);
				pattern(i,j,WHITE,Vertical);
				score(i,j,code,WHITE);
				pattern(i,j,WHITE,RightBevel);
				score(i,j,code,WHITE);
				pattern(i,j,WHITE,LeftBevel);
				score(i,j,code,WHITE);
				//给黑棋的禁手点赋0分
				if(forbidd(i,j)==1){
					ScoreBoardBlack[i][j]=-1;
				}
			}
		}
	}
	//分别找到黑棋和白棋赋分表中的最大分数
	maxblack=findmax(BLACK,&black_i,&black_j);
	maxwhite=findmax(WHITE,&white_i,&white_j);
	//再找到赋分后的选择问题
	if(turn%2==1){
		//电脑执黑
		//黑棋下一步就可以成五获胜，则走黑棋最大分数点，即成五的点
		if(maxblack>=WIN5){
			*ai_i=black_i;
			*ai_j=black_j;
		}else{//如果下一步不能马上成五
		//判断对方有没有成五和形成活四和冲四的点
		//如果有，则去去堵住对方的成棋点
			if(maxwhite>=HALF4){
				*ai_i=white_i;
				*ai_j=white_j;
			}else if(maxwhite>=HALFLIVE3){
				//如果对方没有，则判断对方是否有活三
				//判断自己能否成四，有则下自己的棋，无则堵住对方的棋
				if(maxblack>=HALF4){
					*ai_i=black_i;
					*ai_j=black_j;
				}else{
				*ai_i=white_i;
				*ai_j=white_j;					
				}
			}else{
				//什么威胁都没有的情况下比较两方的最大的分，谁的最大分大（即谁的更有利）则下在哪一个点
				if(maxblack>=maxwhite){
					*ai_i=black_i;
					*ai_j=black_j;
				}else{
					*ai_i=white_i;
					*ai_j=white_j;
				}
			}
		}
	}else{
		if(maxwhite>=WIN5){
			*ai_i=white_i;
			*ai_j=white_j;
		}else{
			if(maxblack>=HALF4){
				*ai_i=black_i;
				*ai_j=black_j;				
			}else if(maxblack>=HALFLIVE3){
				if(maxwhite>=HALF4){
					*ai_i=white_i;
					*ai_j=white_j;
				}else{
					*ai_i=black_i;
					*ai_j=black_j;
				}
			}else{
				if(maxblack>=maxwhite){
					*ai_i=black_i;
					*ai_j=black_j;
				}else{
					*ai_i=white_i;
					*ai_j=white_j;
				}
			}
		}

	}
}

//打分函数，给对应的棋形赋给相应的分数
int score(int i,int j,char code[],int color){
	int countblank(char code[]);
	if(color==BLACK){
		if(strindex(code,"11111")>=0){//成五棋形
			ScoreBoardBlack[i][j]+=WIN5;
		}else if(strindex(code,"1111")>=1 && strindex(code,"1111")<=4){//含有连续的四个己方棋子
			if(strindex(code,"011110")>=0){
				ScoreBoardBlack[i][j]+=LIVE4;
			}else if(strindex(code,"11110")>=0 || strindex(code,"01111")>=0){
				ScoreBoardBlack[i][j]+=HALF4;
			}//else dead4死四
		}else if((code[2]=='1' && code[3]=='1') || (code[3]=='1' && code[5]=='1') || (code[5]=='1' && code[6]=='1')){//111，含有连续的三个己方棋子
			if(strindex(code,"0011100")>=0){
				ScoreBoardBlack[i][j]+=LIVE3;
			}else if(strindex(code,"011100")>=0 || strindex(code,"001110")>=0){
				if(strindex(code,"1011100")>=0 || strindex(code,"0011101")>=0){
					ScoreBoardBlack[i][j]+=JUMP4ss;
				}else{//2011100
					ScoreBoardBlack[i][j]+=HALFLIVE3;
				}
			}else if(strindex(code,"01110")>=0){
				if(strindex(code,"1011101")>=0){
					ScoreBoardBlack[i][j]+=LIVE4*2;
				}else if(strindex(code,"011101")>=0 || strindex(code,"101110")>=0){
					ScoreBoardBlack[i][j]+=JUMP4s;
				}else{//2011102
					ScoreBoardBlack[i][j]+=HALFHALFLIVE3;
				}
			}else if(strindex(code,"1110")>=0 || strindex(code,"0111")>=0){
				if(strindex(code,"11101")>=0 || strindex(code,"10111")>=0){
					ScoreBoardBlack[i][j]+=HALF4;
				}//else 憋三 #0111#
			}//else 死三
		}
		else if(code[3]=='1' || code[5]=='1'){//含有连续的两个己方棋子
			if(strindex(code,"00011000")>=0){
				if(strindex(code,"100011000")>=0 || strindex(code,"000110001")>=0){
					ScoreBoardBlack[i][j]+=LIVE2bbbsssp;
				}else if(strindex(code,"000011000")>=0 || strindex(code,"000110000")>=0){
					ScoreBoardBlack[i][j]+=LIVE2sss0;
				}else{
					ScoreBoardBlack[i][j]+=LIVE2sss;
				}
			}else if(strindex(code,"0011000")>=0 || strindex(code,"0001100")>=0){
				if(strindex(code,"100110001")>=0 || strindex(code,"100011001")>=0){
					ScoreBoardBlack[i][j]+=(JUMP3bbsss+LIVE2bbbssp);
				}else if(strindex(code,"10011000")>=0 || strindex(code,"00011001")>=0){
					ScoreBoardBlack[i][j]+=JUMP3bbsss;
				}else if(strindex(code,"00110001")>=0 || strindex(code,"10001100")>=0){
					ScoreBoardBlack[i][j]+=LIVE2bbbssp;
				}else if(strindex(code,"00110000")>=0 || strindex(code,"00001100")>=0){
					ScoreBoardBlack[i][j]+=LIVE2ss00;
				}else{
					ScoreBoardBlack[i][j]+=LIVE2ss0;
				}
			}else if(strindex(code,"001100")>=0){
				if(strindex(code,"10011001")>=0){
					ScoreBoardBlack[i][j]+=JUMP3bbss*2;
				}else if(strindex(code,"1001100")>=0 || strindex(code,"0011001")>=0){
					ScoreBoardBlack[i][j]+=JUMP3bbss;
				}else{
					ScoreBoardBlack[i][j]+=LIVE2ss;
				}
			}else if(strindex(code,"01100")>=0 || strindex(code,"00110")>=0){
				if(strindex(code,"1011001")>=0){
					ScoreBoardBlack[i][j]+=(JUMP3bbs+JUMP3bss);
				}else if(strindex(code,"101100")>=0 || strindex(code,"011001")>=0){
					if(strindex(code,"1101100")>=0 || strindex(code,"0110011")>=0){
						ScoreBoardBlack[i][j]+=JUMP4bss;
					}else{
						ScoreBoardBlack[i][j]+=JUMP3bss;
					}
				}else if(strindex(code,"011001")>=0 || strindex(code,"100110")>=0){
					ScoreBoardBlack[i][j]+=JUMP3bbs;
				}else{
					ScoreBoardBlack[i][j]+=JUMP3bbs;
				}
			}else if(strindex(code,"0110")>=0){
				if(strindex(code,"11011011")>=0){
					ScoreBoardBlack[i][j]+=(LIVE4+JUMP4bs);
				}else if(strindex(code,"1101101")>=0 || strindex(code,"1011011")>=0){
					ScoreBoardBlack[i][j]+=(HALF4+JUMP4bs);
				}else if(strindex(code,"101101")>=0){
					ScoreBoardBlack[i][j]+=JUMP3bbss*2;
				}else if(strindex(code,"10110")>=0 || strindex(code,"01101")>=0){
					if(strindex(code,"110110")>=0 || strindex(code,"011011")>=0){
						ScoreBoardBlack[i][j]+=JUMP4bs;
					}else{
						ScoreBoardBlack[i][j]+=JUMP3bbss;
					}
				}else{
					ScoreBoardBlack[i][j]+=LIVE2ss;
				}
			}else if(strindex(code,"110")>=0 || strindex(code,"011")>=0){
				if(strindex(code,"11011")>=0){
					ScoreBoardBlack[i][j]+=HALF4;
				}else if(strindex(code,"110")>=0 || strindex(code,"011")>=0){
					ScoreBoardBlack[i][j]+=HALF2;
				}
			}//else 
		}
		//下面是单独一个子的情形赋分，由于赋分不善，导致棋力降低，予以注释，比赛前发现了这个问题，但反复调整效果甚微，遂准备了不注释和注释掉以下代码的两个源代码
		//前两局选择了不注释的版本，一赢一负，后面采用了注释的版本求稳，在和别人填棋盘的三局比赛中输了一次，其他均胜利（特此注释）
		// else{
		// 	if(strindex(code,"000010000")>=0){
		// 		ScoreBoardBlack[i][j]+=LIVE1ssss;
		// 	}else if(strindex(code,"00001000")>=0 || strindex(code,"00010000")>=0){
		// 		if(strindex(code,"000010001")>=0 || strindex(code,"100010000")>=0){
		// 			ScoreBoardBlack[i][j]+=JUMP2bbbssss;
		// 		}else{//#00001000#
		// 			ScoreBoardBlack[i][j]+=LIVE1sss0;
		// 		}
		// 	}else if(strindex(code,"0001000")>=0){
		// 		if(strindex(code,"100010001")>=0){
		// 			ScoreBoardBlack[i][j]+=JUMP2bbbsss*2;
		// 		}else if(strindex(code,"10001000")>=0 || strindex(code,"00010001")>=0){
		// 			ScoreBoardBlack[i][j]+=JUMP2bbbsss;
		// 		}else{//#0001000#
		// 			ScoreBoardBlack[i][j]+=LIVE1sss;
		// 		}
		// 	}else if(strindex(code,"001000")>=0 || strindex(code,"000100")>=0){
		// 		if(strindex(code,"110010001")>=0 || strindex(code,"100010011")>=0){
		// 			ScoreBoardBlack[i][j]+=(JUMP3bbsss+JUMP2bbbss);
		// 		}else if(strindex(code,"11001000")>=0 || strindex(code,"00010011")>=0){
		// 			ScoreBoardBlack[i][j]+=JUMP3bbsss;
		// 		}else if(strindex(code,"010010001")>=0 || strindex(code,"100010010")>=0){
		// 			ScoreBoardBlack[i][j]+=(JUMP2bbbss+JUMP2bbsss);
		// 		}else if(strindex(code,"10010001")>=0 || strindex(code,"10001001")>=0){
		// 			ScoreBoardBlack[i][j]+=(JUMP2bbbss+JUMP2bbsss);
		// 		}else if(strindex(code,"10010000")>=0 || strindex(code,"00001001")>=0){
		// 			ScoreBoardBlack[i][j]+=JUMP2bbssss;
		// 		}else if(strindex(code,"1001000")>=0 || strindex(code,"0001001")>=0){
		// 			ScoreBoardBlack[i][j]+=JUMP2bbsss;
		// 		}else{//#001000#
		// 			ScoreBoardBlack[i][j]+=LIVE1ss0;
		// 		}
		// 	}else if(strindex(code,"00100")>=0){
		// 		if(strindex(code,"110010011")>=0){
		// 			ScoreBoardBlack[i][j]+=JUMP3bbss*2;
		// 		}else if(strindex(code,"110010010")>=0 || strindex(code,"010010011")>=0){
		// 			ScoreBoardBlack[i][j]+=(JUMP3bbss+JUMP2bbss);
		// 		}else if(strindex(code,"010010010")>=0){
		// 			ScoreBoardBlack[i][j]+=(JUMP2bbss*2+BLANK*2);
		// 		}else if(strindex(code,"01001001")>=0 || strindex(code,"10010010")>=0){
		// 			ScoreBoardBlack[i][j]+=(JUMP2bbss*2+BLANK);
		// 		}else if(strindex(code,"1001001")>=0){
		// 			ScoreBoardBlack[i][j]+=JUMP2bbss*2;
		// 		}else if(strindex(code,"0001001")>=0 || strindex(code,"1001000")>=0){
		// 			ScoreBoardBlack[i][j]+=JUMP2bbsss;
		// 		}else{
		// 			ScoreBoardBlack[i][j]+=LIVE1ss;
		// 		}
		// 	}else if((code[3]=='0' && code[5]=='0' && code[6]=='0') || (code[2]=='0' && code[3]=='0' && code[5]=='0')){
		// 		if(strindex(code,"111010011")>=0 || strindex(code,"110010111")>=0){
		// 			ScoreBoardBlack[i][j]+=(HALF4+JUMP3bbs);
		// 		}else if(strindex(code,"011010011")>=0 || strindex(code,"110010110")>=0){
		// 			ScoreBoardBlack[i][j]+=(JUMP3bss+BLANK+JUMP3bbs);
		// 		}else if(strindex(code,"101010011")>=0 || strindex(code,"110010101")>=0){
		// 			ScoreBoardBlack[i][j]+=(JUMP3bbs+JUMP3bbss);
		// 		}else if(strindex(code,"001010011")>=0 || strindex(code,"110010100")>=0){
		// 			ScoreBoardBlack[i][j]+=(HALF2+JUMP3bbs);
		// 		}else if(strindex(code,"111010010")>=0 || strindex(code,"010010111")>=0){
		// 			ScoreBoardBlack[i][j]+=(JUMP2bbss+JUMP4bss);
		// 		}else if(strindex(code,"111010000")>=0 || strindex(code,"000010111")>=0){
		// 			ScoreBoardBlack[i][j]+=JUMP4bss;
		// 		}else if(strindex(code,"011010010")>=0 || strindex(code,"010010110")>=0){
		// 			ScoreBoardBlack[i][j]+=(JUMP3bss+JUMP2bbss);
		// 		}else if(strindex(code,"011010000")>=0 || strindex(code,"000010110")>=0){
		// 			ScoreBoardBlack[i][j]+=HALFLIVE3;
		// 		}else if(strindex(code,"101010010")>=0 || strindex(code,"010010101")>=0){
		// 			ScoreBoardBlack[i][j]+=(JUMP3bbs+JUMP2bbss);
		// 		}else if(strindex(code,"101010000")>=0 || strindex(code,"000010101")>=0){
		// 			ScoreBoardBlack[i][j]+=JUMP3bbsss;
		// 		}else if(strindex(code,"001010010")>=0 || strindex(code,"010010100")>=0){
		// 			ScoreBoardBlack[i][j]+=(HALF2+JUMP2bbss);
		// 		}else if(strindex(code,"01010010")>=0 || strindex(code,"01001010")>=0){
		// 			ScoreBoardBlack[i][j]+=(HALF2+JUMP2bbss);
		// 		}else if(strindex(code,"00101001")>=0 || strindex(code,"10010100")>=0){
		// 			ScoreBoardBlack[i][j]+=(HALF2+JUMP2bbbs);
		// 		}else if(strindex(code,"0101001")>=0 || strindex(code,"1001010")>=0){
		// 			ScoreBoardBlack[i][j]+=(HALF2+JUMP2bbbs);
		// 		}else if(strindex(code,"101001")>=0 || strindex(code,"100101")>=0){
		// 			ScoreBoardBlack[i][j]+=HALF2*2;
		// 		}else if(strindex(code,"101000")>=0 || strindex(code,"000101")>=0){
		// 			ScoreBoardBlack[i][j]+=HALF2;
		// 		}else if(strindex(code,"10100")>=0 || strindex(code,"00101")>=0){
		// 			ScoreBoardBlack[i][j]+=HALF2;
		// 		}
		// 	}else if(code[3]=='0' && code[5]=='0'){
		// 		if(strindex(code,"111010111")>=0){
		// 			ScoreBoardBlack[i][j]+=LIVE4;
		// 		}else if(countblank(code)==3){
		// 			ScoreBoardBlack[i][j]+=(HALF4+JUMP3bbs);
		// 		}else if(strindex(code,"011010110")>=0 || 
		// 		strindex(code,"101010101")>=0 || 
		// 		strindex(code,"101010110")>=0 || strindex(code,"011010101")>=0){
		// 			ScoreBoardBlack[i][j]+=JUMP3bbs*2;
		// 		}else if(strindex(code,"001010111")>=0 || strindex(code,"111010100")>=0){
		// 			ScoreBoardBlack[i][j]+=(HALF4+HALF2);
		// 		}else if(strindex(code,"11101011")>=0 || strindex(code,"11010111")>=0){
		// 			ScoreBoardBlack[i][j]+=(HALF4+HALF3);
		// 		}else if(strindex(code,"01101011")>=0 || strindex(code,"11010110")>=0 || 
		// 		strindex(code,"10101011")>=0 || strindex(code,"11010101")>=0){
		// 			ScoreBoardBlack[i][j]+=HALF3*2;
		// 		}else if(strindex(code,"11101010")>=0 || strindex(code,"01010111")>=0){
		// 			ScoreBoardBlack[i][j]+=(HALF4+HALF2);
		// 		}else if(strindex(code,"01101010")>=0 || strindex(code,"01010110")>=0){
		// 			ScoreBoardBlack[i][j]+=(HALF3+HALF2);
		// 		}else if(strindex(code,"1101011")>=0){
		// 			ScoreBoardBlack[i][j]+=HALF3;
		// 		}else if(strindex(code,"1101010")>=0 || strindex(code,"0101011")>=0){
		// 			ScoreBoardBlack[i][j]+=(HALF3+HALF2);
		// 		}else if(strindex(code,"0101010")>=0){
		// 			ScoreBoardBlack[i][j]+=JUMP3bbss;
		// 		}else if(strindex(code,"101010")>=0 || strindex(code,"010101")>=0){
		// 			ScoreBoardBlack[i][j]+=JUMP3bbs;
		// 		}else{//10101
		// 			ScoreBoardBlack[i][j]+=HALF3;
		// 		}
		// 	}
		// }
		//根据扫描的左右四个格点中的空格位置给该点加一定的分数，即根据code字符串中‘0’的个数加分
		ScoreBoardBlack[i][j]+=(countblank(code)*BLANK);
	}else{
        if(strindex(code,"11111")>=0){//成五棋形
            ScoreBoardWhite[i][j]+=WIN5;
        }else if(strindex(code,"1111")>=1 && strindex(code,"1111")<=4){//连四棋形
            if(strindex(code,"011110")>=0){
                ScoreBoardWhite[i][j]+=LIVE4;
            }else if(strindex(code,"11110")>=0 || strindex(code,"01111")>=0){
                ScoreBoardWhite[i][j]+=HALF4;
            }//else dead4死四
        }else if((code[2]=='1' && code[3]=='1') || (code[3]=='1' && code[5]=='1') || (code[5]=='1' && code[6]=='1')){//111连三棋形
            if(strindex(code,"0011100")>=0){
                ScoreBoardWhite[i][j]+=LIVE3;
            }else if(strindex(code,"011100")>=0 || strindex(code,"001110")>=0){
                if(strindex(code,"1011100")>=0 || strindex(code,"0011101")>=0){
                    ScoreBoardWhite[i][j]+=JUMP4ss;
                }else{//2011100
                    ScoreBoardWhite[i][j]+=HALFLIVE3;
                }
            }else if(strindex(code,"01110")>=0){
                if(strindex(code,"1011101")>=0){
                    ScoreBoardWhite[i][j]+=LIVE4*2;
                }else if(strindex(code,"011101")>=0 || strindex(code,"101110")>=0){
                    ScoreBoardWhite[i][j]+=JUMP4s;
                }else{//2011102
                    ScoreBoardWhite[i][j]+=HALFHALFLIVE3;
                }
            }else if(strindex(code,"1110")>=0 || strindex(code,"0111")>=0){
                if(strindex(code,"11101")>=0 || strindex(code,"10111")>=0){
                    ScoreBoardWhite[i][j]+=HALF4;
                }//else 憋三 #0111#
            }//else 死三
        }
		else if(code[3]=='1' || code[5]=='1'){//连二棋形
            if(strindex(code,"00011000")>=0){
                if(strindex(code,"100011000")>=0 || strindex(code,"000110001")>=0){
                    ScoreBoardWhite[i][j]+=LIVE2bbbsssp;
                }else if(strindex(code,"000011000")>=0 || strindex(code,"000110000")>=0){
                    ScoreBoardWhite[i][j]+=LIVE2sss0;
                }else{
                    ScoreBoardWhite[i][j]+=LIVE2sss;
                }
            }else if(strindex(code,"0011000")>=0 || strindex(code,"0001100")>=0){
                if(strindex(code,"100110001")>=0 || strindex(code,"100011001")>=0){
                    ScoreBoardWhite[i][j]+=(JUMP3bbsss+LIVE2bbbssp);
                }else if(strindex(code,"10011000")>=0 || strindex(code,"00011001")>=0){
                    ScoreBoardWhite[i][j]+=JUMP3bbsss;
                }else if(strindex(code,"00110001")>=0 || strindex(code,"10001100")>=0){
                    ScoreBoardWhite[i][j]+=LIVE2bbbssp;
                }else if(strindex(code,"00110000")>=0 || strindex(code,"00001100")>=0){
                    ScoreBoardWhite[i][j]+=LIVE2ss00;
                }else{
                    ScoreBoardWhite[i][j]+=LIVE2ss0;
                }
            }else if(strindex(code,"001100")>=0){
                if(strindex(code,"10011001")>=0){
                    ScoreBoardWhite[i][j]+=JUMP3bbss*2;
                }else if(strindex(code,"1001100")>=0 || strindex(code,"0011001")>=0){
                    ScoreBoardWhite[i][j]+=JUMP3bbss;
                }else{
                    ScoreBoardWhite[i][j]+=LIVE2ss;
                }
            }else if(strindex(code,"01100")>=0 || strindex(code,"00110")>=0){
                if(strindex(code,"1011001")>=0){
                    ScoreBoardWhite[i][j]+=(JUMP3bbs+JUMP3bss);
                }else if(strindex(code,"101100")>=0 || strindex(code,"011001")>=0){
                    if(strindex(code,"1101100")>=0 || strindex(code,"0110011")>=0){
                        ScoreBoardWhite[i][j]+=JUMP4bss;
                    }else{
                        ScoreBoardWhite[i][j]+=JUMP3bss;
                    }
                }else if(strindex(code,"011001")>=0 || strindex(code,"100110")>=0){
                    ScoreBoardWhite[i][j]+=JUMP3bbs;
                }else{
                    ScoreBoardWhite[i][j]+=JUMP3bbs;
                }
            }else if(strindex(code,"0110")>=0){
                if(strindex(code,"11011011")>=0){
                    ScoreBoardWhite[i][j]+=(LIVE4+JUMP4bs);
                }else if(strindex(code,"1101101")>=0 || strindex(code,"1011011")>=0){
                    ScoreBoardWhite[i][j]+=(HALF4+JUMP4bs);
                }else if(strindex(code,"101101")>=0){
                    ScoreBoardWhite[i][j]+=JUMP3bbss*2;
                }else if(strindex(code,"10110")>=0 || strindex(code,"01101")>=0){
                    if(strindex(code,"110110")>=0 || strindex(code,"011011")>=0){
                        ScoreBoardWhite[i][j]+=JUMP4bs;
                    }else{
                        ScoreBoardWhite[i][j]+=JUMP3bbss;
                    }
                }else{
                    ScoreBoardWhite[i][j]+=LIVE2ss;
                }
            }else if(strindex(code,"110")>=0 || strindex(code,"011")>=0){
                if(strindex(code,"11011")>=0){
                    ScoreBoardWhite[i][j]+=HALF4;
                }else if(strindex(code,"110")>=0 || strindex(code,"011")>=0){
                    ScoreBoardWhite[i][j]+=HALF2;
                }
            }//else 
        }
		//下面是单独一个子的情形赋分，由于赋分不善，导致棋力降低，予以注释，比赛前发现了这个问题，但反复调整效果甚微，遂准备了不注释和注释掉以下代码的两个源代码
		//前两局选择了不注释的版本，一赢一负，后面采用了注释的版本求稳，在和别人填棋盘的三局比赛中输了一次，其他均胜利（特此注释）
		// else{
        //     if(strindex(code,"000010000")>=0){
        //         ScoreBoardWhite[i][j]+=LIVE1ssss;
        //     }else if(strindex(code,"00001000")>=0 || strindex(code,"00010000")>=0){
        //         if(strindex(code,"000010001")>=0 || strindex(code,"100010000")>=0){
        //             ScoreBoardWhite[i][j]+=JUMP2bbbssss;
        //         }else{//#00001000#
        //             ScoreBoardWhite[i][j]+=LIVE1sss0;
        //         }
        //     }else if(strindex(code,"0001000")>=0){
        //         if(strindex(code,"100010001")>=0){
        //             ScoreBoardWhite[i][j]+=JUMP2bbbsss*2;
        //         }else if(strindex(code,"10001000")>=0 || strindex(code,"00010001")>=0){
        //             ScoreBoardWhite[i][j]+=JUMP2bbbsss;
        //         }else{//#0001000#
        //             ScoreBoardWhite[i][j]+=LIVE1sss;
        //         }
        //     }else if(strindex(code,"001000")>=0 || strindex(code,"000100")>=0){
        //         if(strindex(code,"110010001")>=0 || strindex(code,"100010011")>=0){
        //             ScoreBoardWhite[i][j]+=(JUMP3bbsss+JUMP2bbbss);
        //         }else if(strindex(code,"11001000")>=0 || strindex(code,"00010011")>=0){
        //             ScoreBoardWhite[i][j]+=JUMP3bbsss;
        //         }else if(strindex(code,"010010001")>=0 || strindex(code,"100010010")>=0){
        //             ScoreBoardWhite[i][j]+=(JUMP2bbbss+JUMP2bbsss);
        //         }else if(strindex(code,"10010001")>=0 || strindex(code,"10001001")>=0){
        //             ScoreBoardWhite[i][j]+=(JUMP2bbbss+JUMP2bbsss);
        //         }else if(strindex(code,"10010000")>=0 || strindex(code,"00001001")>=0){
        //             ScoreBoardWhite[i][j]+=JUMP2bbssss;
        //         }else if(strindex(code,"1001000")>=0 || strindex(code,"0001001")>=0){
        //             ScoreBoardWhite[i][j]+=JUMP2bbsss;
        //         }else{//#001000#
        //             ScoreBoardWhite[i][j]+=LIVE1ss0;
        //         }
        //     }else if(strindex(code,"00100")>=0){
        //         if(strindex(code,"110010011")>=0){
        //             ScoreBoardWhite[i][j]+=JUMP3bbss*2;
        //         }else if(strindex(code,"110010010")>=0 || strindex(code,"010010011")>=0){
        //             ScoreBoardWhite[i][j]+=(JUMP3bbss+JUMP2bbss);
        //         }else if(strindex(code,"010010010")>=0){
        //             ScoreBoardWhite[i][j]+=(JUMP2bbss*2+BLANK*2);
        //         }else if(strindex(code,"01001001")>=0 || strindex(code,"10010010")>=0){
        //             ScoreBoardWhite[i][j]+=(JUMP2bbss*2+BLANK);
        //         }else if(strindex(code,"1001001")>=0){
        //             ScoreBoardWhite[i][j]+=JUMP2bbss*2;
        //         }else if(strindex(code,"0001001")>=0 || strindex(code,"1001000")>=0){
        //             ScoreBoardWhite[i][j]+=JUMP2bbsss;
        //         }else{
        //             ScoreBoardWhite[i][j]+=LIVE1ss;
        //         }
        //     }else if((code[3]=='0' && code[5]=='0' && code[6]=='0') || (code[2]=='0' && code[3]=='0' && code[5]=='0')){
        //         if(strindex(code,"111010011")>=0 || strindex(code,"110010111")>=0){
        //             ScoreBoardWhite[i][j]+=(HALF4+JUMP3bbs);
        //         }else if(strindex(code,"011010011")>=0 || strindex(code,"110010110")>=0){
        //             ScoreBoardWhite[i][j]+=(JUMP3bss+BLANK+JUMP3bbs);
        //         }else if(strindex(code,"101010011")>=0 || strindex(code,"110010101")>=0){
        //             ScoreBoardWhite[i][j]+=(JUMP3bbs+JUMP3bbss);
        //         }else if(strindex(code,"001010011")>=0 || strindex(code,"110010100")>=0){
        //             ScoreBoardWhite[i][j]+=(HALF2+JUMP3bbs);
        //         }else if(strindex(code,"111010010")>=0 || strindex(code,"010010111")>=0){
        //             ScoreBoardWhite[i][j]+=(JUMP2bbss+JUMP4bss);
        //         }else if(strindex(code,"111010000")>=0 || strindex(code,"000010111")>=0){
        //             ScoreBoardWhite[i][j]+=JUMP4bss;
        //         }else if(strindex(code,"011010010")>=0 || strindex(code,"010010110")>=0){
        //             ScoreBoardWhite[i][j]+=(JUMP3bss+JUMP2bbss);
        //         }else if(strindex(code,"011010000")>=0 || strindex(code,"000010110")>=0){
        //             ScoreBoardWhite[i][j]+=HALFLIVE3;
        //         }else if(strindex(code,"101010010")>=0 || strindex(code,"010010101")>=0){
        //             ScoreBoardWhite[i][j]+=(JUMP3bbs+JUMP2bbss);
        //         }else if(strindex(code,"101010000")>=0 || strindex(code,"000010101")>=0){
        //             ScoreBoardWhite[i][j]+=JUMP3bbsss;
        //         }else if(strindex(code,"001010010")>=0 || strindex(code,"010010100")>=0){
        //             ScoreBoardWhite[i][j]+=(HALF2+JUMP2bbss);
        //         }else if(strindex(code,"01010010")>=0 || strindex(code,"01001010")>=0){
        //             ScoreBoardWhite[i][j]+=(HALF2+JUMP2bbss);
        //         }else if(strindex(code,"00101001")>=0 || strindex(code,"10010100")>=0){
        //             ScoreBoardWhite[i][j]+=(HALF2+JUMP2bbbs);
        //         }else if(strindex(code,"0101001")>=0 || strindex(code,"1001010")>=0){
        //             ScoreBoardWhite[i][j]+=(HALF2+JUMP2bbbs);
        //         }else if(strindex(code,"101001")>=0 || strindex(code,"100101")>=0){
        //             ScoreBoardWhite[i][j]+=HALF2*2;
        //         }else if(strindex(code,"101000")>=0 || strindex(code,"000101")>=0){
        //             ScoreBoardWhite[i][j]+=HALF2;
        //         }else if(strindex(code,"10100")>=0 || strindex(code,"00101")>=0){
        //             ScoreBoardWhite[i][j]+=HALF2;
        //         }
        //     }else if(code[3]=='0' && code[5]=='0'){
        //         if(strindex(code,"111010111")>=0){
        //             ScoreBoardWhite[i][j]+=LIVE4;
        //         }else if(countblank(code)==3){
        //             ScoreBoardWhite[i][j]+=(HALF4+JUMP3bbs);
        //         }else if(strindex(code,"011010110")>=0 || 
        //         strindex(code,"101010101")>=0 || 
        //         strindex(code,"101010110")>=0 || strindex(code,"011010101")>=0){
        //             ScoreBoardWhite[i][j]+=JUMP3bbs*2;
        //         }else if(strindex(code,"001010111")>=0 || strindex(code,"111010100")>=0){
        //             ScoreBoardWhite[i][j]+=(HALF4+HALF2);
        //         }else if(strindex(code,"11101011")>=0 || strindex(code,"11010111")>=0){
        //             ScoreBoardWhite[i][j]+=(HALF4+HALF3);
        //         }else if(strindex(code,"01101011")>=0 || strindex(code,"11010110")>=0 || 
        //         strindex(code,"10101011")>=0 || strindex(code,"11010101")>=0){
        //             ScoreBoardWhite[i][j]+=HALF3*2;
        //         }else if(strindex(code,"11101010")>=0 || strindex(code,"01010111")>=0){
        //             ScoreBoardWhite[i][j]+=(HALF4+HALF2);
        //         }else if(strindex(code,"01101010")>=0 || strindex(code,"01010110")>=0){
        //             ScoreBoardWhite[i][j]+=(HALF3+HALF2);
        //         }else if(strindex(code,"1101011")>=0){
        //             ScoreBoardWhite[i][j]+=HALF3;
        //         }else if(strindex(code,"1101010")>=0 || strindex(code,"0101011")>=0){
        //             ScoreBoardWhite[i][j]+=(HALF3+HALF2);
        //         }else if(strindex(code,"0101010")>=0){
        //             ScoreBoardWhite[i][j]+=JUMP3bbss;
        //         }else if(strindex(code,"101010")>=0 || strindex(code,"010101")>=0){
        //             ScoreBoardWhite[i][j]+=JUMP3bbs;
        //         }else{//10101
        //             ScoreBoardWhite[i][j]+=HALF3;
        //         }
        //     }
        // }
		//根据扫描的左右四个格点中的空格位置给该点加一定的分数，即根据code字符串中‘0’的个数加分
        ScoreBoardWhite[i][j]+=(countblank(code)*BLANK);
	}
	return 0;
}

//电脑行棋时调用的禁手判断条件，与forbidden函数功能一样，只是少了几个printf输出
int forbidd(int x,int y){
	int blacksansan(int x,int y,int direction);
	int blacksisi(int x,int y);
	if(win(BLACK,x,y)!=BLACK){
		if(countline(1,x,y,0)>5){
			return 1;
		}
		if(blacksisi(x,y)==1){
			return 1;
		}
		if(blacksansan(x,y,0)==1){
			return 1;
		}
	}else{
		return 0;
	}
}

//对打分表进行查找，找到最大的那个值，返回分数，通过指针将坐标也传回
int findmax(int color,int *temp_x,int *temp_y){
	int maxi[226],maxj[226];
	int i,j;
	for(i=0;i<226;i++){
		maxi[i]=maxj[i]=-1;
	}
	int count=1;
	int maxscore=-1;
	if(color==BLACK){
		for(i=0;i<SIZE;i++){
			for(j=0;j<SIZE;j++){
				if(ScoreBoardBlack[i][j]>maxscore){
					count=1;
					maxscore=ScoreBoardBlack[i][j];
					maxi[count]=i;
					maxj[count]=j;
					count++;
				}else if(ScoreBoardBlack[i][j]==maxscore){
					maxi[count]=i;
					maxj[count]=j;
					count++;				
				}
			}
		}
		if(count!=2){
			count=rand()%(count-1);
			*temp_x=maxi[count+1];
			*temp_y=maxj[count+1];
		}else{
			*temp_x=maxi[count-1];
			*temp_y=maxj[count-1];
		}
	}else{
		for(i=0;i<SIZE;i++){
			for(j=0;j<SIZE;j++){
				if(ScoreBoardWhite[i][j]>maxscore){
					count=1;
					maxscore=ScoreBoardWhite[i][j];
					maxi[count]=i;
					maxj[count]=j;
					count++;
				}else if(ScoreBoardWhite[i][j]==maxscore){
					maxi[count]=i;
					maxj[count]=j;
					count++;					
				}
			}
		}
		if(count!=2){
			count=rand()%(count-1);
			*temp_x=maxi[count+1];
			*temp_y=maxj[count+1];
		}else{
			*temp_x=maxi[count-1];
			*temp_y=maxj[count-1];
		}
	}
	return maxscore;
}

//数一个点左边四个和右边四个里有几个空格，即数code中含有几个‘0’
int countblank(char code[]){
	int n;
	int blank=0;
	for(n=0;n<10;n++){
		if(code[n]=='0'){
			blank++;
		}
	}
	return blank;
}