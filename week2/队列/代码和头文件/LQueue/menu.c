#include "LQueue.h" 
void menu(){
	printf("*********************系统功能菜单**********************\n");
    printf("-------------------------------------------------------\n");
    printf("    ***********************************************    \n");
    printf("    *  1.初始化队列       * *    2.销毁队列       *    \n");
    printf("    ***********************************************    \n");
    printf("    *  3.入队             * *    4.出队           *	   \n");
    printf("    ***********************************************	   \n");
    printf("    *  5.查看队列元素     * *    6.清空队列       *    \n");
    printf("    ***********************************************    \n");
    printf("    *  7.查看队列长度     * *    8.查看队头元素   *    \n");
    printf("    ***********************************************    \n");
    printf("    *  9.退出系统                                 *    \n");
    printf("    ***********************************************    \n");
    printf("-------------------------------------------------------\n");
}

void operation(){
	printf("请按任意键继续. . .");
	getchar();
	system("cls");
}

int judgeint(){ /* to judge the input's type and change the 'int' type from char to int */
	char input[10];
	int flag=1;  /* when flag=0 means input a wrong data */
	int len,n=0; /* len(the length of input),n(the real input data) */  
	while(flag==1){
		scanf("%s",input); /* input the data */
		len=strlen(input);
		for(int i=0;i<len;i++){
			if(*(input+i)<'0'||*(input+i)>'9'){ /* judge if input a unreasonable data */
				printf("\n你输入的数据有误（请输入整数），请重新输入：");
				break;
			}
			else if(i==strlen(input)-1)flag=0; /* if not stop input and go next*/
		}
	}
	for(int i=0,k=1;i<len;i++){ /* change the char into int */
		for(int j=0;j<len-1-i;j++){
			k*=10;
		}
		n+=(input[i]-'0')*k; /* sum up all the digits */
		k=1; 
	}
	return n;
}

double judgedouble(){
	char input[20];
	int flag=1;  /* when flag=0 means input a wrong data */
	int len,len1,len2; /* len(the length of input),len1(the length of int),len2(the length of decimal) */  
	double n,j=0.1; /* n(the real input data),j(to sum up the decimals) */
	while(flag==1){
		scanf("%s",input); /* input the data */
		len=strlen(input);
		for(int i=0;i<len;i++){
			if((*(input+i)<'0'||*(input+i)>'9')&&*(input+i)!='.'){ /* judge if input a unreasonable data */
				printf("\n你输入的数据有误（请输入浮点数），请重新输入：");
				break;
			}
			else if(i==strlen(input)-1)flag=0; /* if not stop input and go next*/
		}
	}
	/* change the char into int */
	for(int i=0,k=1;*(input+i)!='.';i++,k++)len1=k;
	for(int i=1,k=len1-1;k>=0;k--){
		n+=(*(input+k)-'0')*i;
		i*=10;
	}	
	for(int i=len-1,k=1;*(input+i)!='.';i--,k++)len2=k; /* len1+2 means the number after '.' */
	for(int k=len1+1;*(input+k);k++){
		n+=(*(input+k)-'0')*j; /* sum up all the digits */
		j/=10;
	}	
	return n;
}

void type(LQueue *Q){
	Status EnLQueue(LQueue *Q, void *data);
	char c;          /* choice,char is smaller than short */
	printf("\n请选择你要输入的数据的数据类型\n");
	printf("------------------------------\n");
	printf("1.int\n");
	printf("2.float\n");
	printf("3.double\n");
	printf("4.char\n");
	printf("5.string\n"); 
	printf("------------------------------\n");
	printf("请输入你的选择："); 
	scanf("%c",&c);
	fflush(stdin);
	while(c<'1'||c>'5'){
		printf("\n你输入的数据有误（请输入1-5），请重新输入：");
		scanf("%c",&c);
		fflush(stdin);
	}
	printf("\n请输入要入队的数据（若要输入字符串注意字符串长度不能超过20！）："); 
	switch(c){
		case '1':
			/*data=(int *)malloc(sizeof(int));
			data=judgeinput();
			EnLQueue(Q,&data);*/ //how to do this using this means?
			int data1;
			data1=judgeint();
			EnLQueue(Q,&data1);
			break;
		case '2':
			float data2;
			data2=judgedouble();
			EnLQueue(Q,&data2);
			break;
		case '3':
			double data3;
			data3=judgedouble();
			EnLQueue(Q,&data3);
			break;
		case '4':
			char data4;
			scanf("%c",&data4);
			EnLQueue(Q,&data4);
			break;
		case '5':
			char data5[20]; /* not more than 20 */ 
			scanf("%s",data5);
			EnLQueue(Q,data5);
			break;
	}
	Q->rear->nodetype=c; /* record the type */
}
