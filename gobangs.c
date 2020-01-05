#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 2

#define MAXIN 100

void initRecordBorard(void);
void recordtoDisplayArray(void);
void displayBoard(void);

//����ʹ�õ���GBK���룬ÿһ�������ַ�ռ��2���ֽڡ�

//���̻���ģ�� 
char aInitDisplayBoardArray[SIZE][SIZE*CHARSIZE+1] = {
	"���өөөөөөөөөөөөө�",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"�ĩ��������������",
	"���۩۩۩۩۩۩۩۩۩۩۩۩۩�"
};
	//������������ʾ���� 
char aDisplayBoardArray[SIZE][SIZE*CHARSIZE+1];
//�������� 
char play1Pic[]="��";//������;
char play1CurrentPic[]="��"; 
char play2Pic[]="��";//������;
char play2CurrentPic[]="��";
//���������ڼ�¼���̸�� 
int aRecordBoard[SIZE][SIZE];
int ScoreBoardBlack[SIZE][SIZE];//���������
int ScoreBoardWhite[SIZE][SIZE];//���������

#define BLACK 1
#define WHITE 2
//����direction
#define Horizontal 10
#define Vertical 20
#define RightBevel 30//��б
#define LeftBevel 40//��б
#define PSIZE 4//���εİ��

int getPic(int turn);
int getPicVs(int turn);
int fool(int turn);
int win(int player,int x,int y);
int forbidden(int x,int y);//�ⲿ��
int forbidd(int x,int y);//�ڲ���
int countline(int player,int x,int y,int direction);
char code[10]="0";
char* pattern(int x,int y,int color,int direction);
void AIfind(int *ai_x,int *ai_y,int turn);
int score(int i,int j,char code[],int color);//���ֺ���
#define WIN5 1000000
#define LIVE4 250000//����011110
#define JUMP4ss 160000 //�������Ҷº��Կ��γɳ�������#1011100�����ܳ���
#define JUMP4s 150000 //�������Ҷº��Կ��γɳ�������#101110#�������ܳ���
#define JUMP4bss 140000 //1101100
#define JUMP4bs 130000 //110110
#define HALF4 120000 //����

#define LIVE3 55000 //���������γ���������
#define HALFLIVE3 50000 //���������һ������γɻ��ģ���һ��ֻ���γɳ���

#define JUMP3bbsss 20500 //10011000�������м����������һ��������λ�����������
#define HALFHALFLIVE3 20000 //˫����������������γɳ���
#define JUMP3bbss 20000 //1001100�������м����������һ��2����λ�����������
#define JUMP3bss 19000 //101100�������м��һ����һ������񣬣�����ģ����γ�101101
#define JUMP3bbs 17500 //100110�������м����������һ��1����λ�����������
#define JUMP3bs 14000 //10110
#define HALF3 10000 //ֻ���γ�һ�����ĵ���
#define LIVE2bbbsssp 6700 //��������� 100011000 ����������������,��һ��������
#define LIVE2bbbssp 6600 //��������� 10001100 ��������������������һ��������
#define LIVE2sss0 6500 //��������� 000011000 ��������,���ܳ��������˷ֱ��4��3��
#define LIVE2ss00 6400 //��������� 00001100 ��������,���˷ֱ��4��2��
#define LIVE2sss 6200 //��������� 00011000 ��������,���ܳ���,���˶�������
#define LIVE2ss0 6000 //��������� 0001100 ��������,���˷ֱ��3��2��
#define LIVE2ss 5500 //��������� 001100 ��������,���ܳ���,���˶���2��
#define LIVE2s0 5200 //��������� 00110 ��������,���˷ֱ��1��2��

#define JUMP2bbbssss 2500 //100010000
#define JUMP2bbssss 2300 //10010000
#define JUMP2bbsss 2100 //1001000
#define JUMP2bbbsss 2000 //10001000
#define JUMP2bbbss 1500 //1000100
#define	JUMP2bbss 1300 //100100
#define JUMP2bbbs 1200 //100010
#define HALF2 1000
#define LIVE1ssss 600 //��һ�����߾���4���ո�
#define LIVE1sss0 550 //��һ�����ߵĿո����ֱ�Ϊ3��4
#define LIVE1sss 500
#define LIVE1ss0 450
#define LIVE1ss 200

#define BLANK 20
int findmax(int color,int *temp_x,int *temp_y);

int blackhuosi(int x,int y,int direction);
int blackchongsi(int x,int y,int direction);
int blackhuosan(int x,int y,int direction); 

int strindex(char s[],char t[]);
int power(int x);
void changeloc(int location,int *x, int *y,int direction);

int PeopleVsPeople(void);
int PeopleVsComputer(void);

static int x,y;
static int player;

int main(){
	int reset=1;
	while(reset==1){
		reset=0;
		x=y=1000;
		initRecordBorard();//��ʼ����0
		recordtoDisplayArray();//ת������
		displayBoard();//��ʾ����
		int mode=100;
		int winner=0;
		do{
			printf("���˶�ս�밴1���˻���ս�밴2���˳��밴0����");
			scanf("%d",&mode);
			fflush(stdin);
			if(mode!=0 && mode!=1 && mode!=2){
				printf("\t�����������룬Ȼ���������롣\n");
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
		printf("\n����һ���밴1�������밴�������");
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
		//�ж�ʤ��
		if(ifwin==1){//player1 wins
			return 11;
		}else if(ifwin==2){//player2 wins
			return 12;
		}else if(ifwin==0){
			return 0;
		}
		turn++;
	}
	return 3;//ƽ��
}

int PeopleVsComputer(void){
	int player=1;
	int turn=1;
	int ifwin;
	int whofirst=0;//������Ϊ1��Player��Ϊ2��
	do{
		printf("����ִ���밴1�����ִ���밴2���˳��밴0����");
		scanf("%d",&whofirst);
		fflush(stdin);
		if(whofirst!=0 && whofirst!=1 && whofirst!=2){
			printf("\t�����������룬Ȼ���������롣\n");
		}
	}while(whofirst!=0 && whofirst!=1 && whofirst!=2);
	if(whofirst==0){
		return 0;//�˳�
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

		//�ж�ʤ��
		if(whofirst==1 && ifwin==1){//player1 wins
			return 21;
		}else if(whofirst==1 && ifwin==2){//player2 wins
			return 22;
		}else if(whofirst==2 && ifwin==1){//player1 wins
			return 23;
		}else if(whofirst==2 && ifwin==2){//player2 wins
			return 24;
		}
		else if(ifwin==0){
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
		printf("��%d�غϣ�Player%d���ӵ�λ��Ϊ��%d%c\n",turn/2,player,SIZE-x,y+'A');
	}
	printf("(�˳��밴0)\n");
	player=((turn%2)==0)?2:1;

	do{
		do{
			do{
				printf("Player%d: please enter your piece(number character):",player);
				scanf("%s",input);
				fflush(stdin);
				len=strlen(input);
				if(input[0]=='0'){
					return 0;//�˳�
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
				printf("���������ӣ�����������\n");
			}
		}while(x<0 || x>SIZE-1 || y<0 || y>SIZE-1);
			if(aRecordBoard[x][y]!=0){
				printf("�Ѿ����ӣ�����������\n");
		}
	}while(aRecordBoard[x][y]!=0);

	aRecordBoard[x][y]=player+2;
	recordtoDisplayArray();
	displayBoard();

	if(player==1 && forbidden(x,y)==1){
		printf("�������!\n");
		return 2;
	}
	return win(player,x,y);
}

int fool(int turn){
	char input[MAXIN];
	int len;
	player=((turn%2)==0)?2:1;
	if(turn>1){
		aRecordBoard[x][y]-=2;
	}
	if(turn==1){
		x=y=7;
	}else{
		int ai_x,ai_y;
		AIfind(&ai_x,&ai_y,turn);
		x=ai_x;
		y=ai_y;
		// do{
		// 	x=rand()%14;
		// 	y=rand()%14;
		// }while(aRecordBoard[x][y]!=0);
	}
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
		printf("��%d�غϣ�Computer���ӵ�λ��Ϊ��%d%c\n",turn/2,SIZE-x,y+'A');
	}
	printf("(�˳��밴0)\n");
	player=((turn%2)==0)?2:1;

	do{
		do{
			do{
				printf("Player%d: please enter your piece(number character):",player);
				scanf("%s",input);
				fflush(stdin);
				len=strlen(input);
				if(input[0]=='0'){
					return 0;//�˳�
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
				printf("���������ӣ�����������\n");
			}
		}while(x<0 || x>SIZE-1 || y<0 || y>SIZE-1);
			if(aRecordBoard[x][y]!=0){
				printf("�Ѿ����ӣ�����������\n");
		}
	}while(aRecordBoard[x][y]!=0);

	aRecordBoard[x][y]=player+2;
	recordtoDisplayArray();
	displayBoard();
	if(player==1 && forbidden(x,y)==1){
		printf("�������!\n");
		return 2;
	}
	return win(player,x,y);
}

int win(int player,int x,int y){
	int total=1;
	int i=1;
	//ˮƽ
	while(aRecordBoard[x][y+i]==player && x>=0 && x<=SIZE-1 && y+i>=0 && y+i<=SIZE-1){
		i++;
		total++;
	}
	i=1;
	while(aRecordBoard[x][y-i]==player && x>=0 && x<=SIZE-1 && y-i>=0 && y-i<=SIZE-1){
		i++;
		total++;

	}
	if(total==5){
		return player;
	}else if(total>5){
		return WHITE;
	}
	//����
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
	if(total==5){
		return player;
	}else if(total>5){
		return WHITE;
	}
	//��б
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
	if(total==5){
		return player;
	}else if(total>5){
		return WHITE;
	}
	//��б
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
	if(total==5){
		return player;
	}else if(total>5){
		return WHITE;
	}
	return 3;
}

//��ʼ�����̸�� 
void initRecordBorard(void){
//ͨ��˫��ѭ������aRecordBoard��0
	int i,j;
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
			aRecordBoard[i][j]=0;
}

//��aRecordBoard�м�¼������λ�ã�ת����aDisplayBoardArray��
void recordtoDisplayArray(void){
	int i,j;
//��һ������aInitDisplayBoardArray�м�¼�Ŀ����̣����Ƶ�aDisplayBoardArray��
    for(i=0;i<SIZE;i++)
		for(j=0;j<=SIZE*CHARSIZE+1;j++)
			aDisplayBoardArray[i][j]=aInitDisplayBoardArray[i][j];
//�ڶ�����ɨ��aRecordBoard����������0��Ԫ�أ�������ߡ��Ƶ�aDisplayBoardArray����Ӧλ����
//ע�⣺aDisplayBoardArray����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽڡ�
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

//��ʾ���̸�� 
void displayBoard(void){
	int i;
	//��һ��������
	system("cls");
	printf("Gobang(������)\t Work of ������\n");
	//�ڶ�������aDisplayBoardArray�������Ļ��
	for(i=0;i<SIZE;i++)
		printf("%2d%s\n",SIZE-i,aDisplayBoardArray[i]);
	//������������������һ����ĸA B .... )
	printf("   A B C D E F G H I J K L M N O \n");
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

int forbidden(int x,int y){
	int blacksansan(int x,int y,int direction);
	int blacksisi(int x,int y);
	if(win(BLACK,x,y)!=BLACK){
		if(countline(1,x,y,0)>5){
			printf("����");
			return 1;
		}
		if(blacksisi(x,y)==1){
			printf("����");
			return 1;
		}
		if(blacksansan(x,y,0)==1){
			printf("����");
			return 1;
		}
	}else{
		return 0;
	}
}

int countline(int player,int x,int y,int direction){
	int total=1;
	int i=1;
	if(direction==0){//���ش������
		//ˮƽ
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
		//����
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
		//��б
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
		//��б
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
		//ˮƽ
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
		//����
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
		//��б
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
		//��б
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

int blacksisi(int x,int y){
	int si=0;
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
	if(si>=2){
		return 1;
	}else{
		return 0;
	}
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
				printf("direction error(huosi2).\n");
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

void AIfind(int *ai_i,int *ai_j,int turn){
	int i,j;
	int black_i,black_j,white_i,white_j;
	int maxblack,maxwhite;
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++){
			ScoreBoardBlack[i][j]=0;
			ScoreBoardWhite[i][j]=0;
		}
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

				if(forbidd(i,j)==1){
					ScoreBoardBlack[i][j]=-1;
				}
			}
		}
	}
	maxblack=findmax(BLACK,&black_i,&black_j);
	maxwhite=findmax(WHITE,&white_i,&white_j);
	if(turn%2==1){
		if(maxblack>=WIN5){
			*ai_i=black_i;
			*ai_j=black_j;
		}else{
			if(maxwhite>=HALF4){
				*ai_i=white_i;
				*ai_j=white_j;
			}else if(maxwhite>=HALFLIVE3){
				if(maxblack>=HALF4){
					*ai_i=black_i;
					*ai_j=black_j;
				}else{
				*ai_i=white_i;
				*ai_j=white_j;					
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

int score(int i,int j,char code[],int color){
	int countblank(char code[]);
	if(color==BLACK){
		if(strindex(code,"11111")>=0){
			ScoreBoardBlack[i][j]+=WIN5;
		}else if(strindex(code,"1111")>=1 && strindex(code,"1111")<=4){
			if(strindex(code,"011110")>=0){
				ScoreBoardBlack[i][j]+=LIVE4;
			}else if(strindex(code,"11110")>=0 || strindex(code,"01111")>=0){
				ScoreBoardBlack[i][j]+=HALF4;
			}//else dead4����
		}else if((code[2]=='1' && code[3]=='1') || (code[3]=='1' && code[5]=='1') || (code[5]=='1' && code[6]=='1')){//111
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
				}//else ���� #0111#
			}//else ����
		}
		else if(code[3]=='1' || code[5]=='1'){
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
		ScoreBoardBlack[i][j]+=(countblank(code)*BLANK);
	}else{
        if(strindex(code,"11111")>=0){
            ScoreBoardWhite[i][j]+=WIN5;
        }else if(strindex(code,"1111")>=1 && strindex(code,"1111")<=4){
            if(strindex(code,"011110")>=0){
                ScoreBoardWhite[i][j]+=LIVE4;
            }else if(strindex(code,"11110")>=0 || strindex(code,"01111")>=0){
                ScoreBoardWhite[i][j]+=HALF4;
            }//else dead4����
        }else if((code[2]=='1' && code[3]=='1') || (code[3]=='1' && code[5]=='1') || (code[5]=='1' && code[6]=='1')){//111
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
                }//else ���� #0111#
            }//else ����
        }
		else if(code[3]=='1' || code[5]=='1'){
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
        ScoreBoardWhite[i][j]+=(countblank(code)*BLANK);
	}
	return 0;
}

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