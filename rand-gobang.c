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
	printf("Gobang(������)\t Author:������\n");
	//�ڶ�������aDisplayBoardArray�������Ļ��
	for(i=0;i<SIZE;i++)
		printf("%2d%s\n",SIZE-i,aDisplayBoardArray[i]);
	//������������������һ����ĸA B .... )
	printf("   A B C D E F G H I J K L M N O \n");
} 