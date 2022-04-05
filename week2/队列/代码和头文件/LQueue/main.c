#include "LQueue.h" 
int main(){
	void menu();
	int judgeint();
	double judgedouble();
	void type(LQueue *Q);
	Status IsInitQueue(LQueue *Q); /* judge is init */
	char option;    /* choose the function to operate */
	LQueue *Q=NULL; /* head pointer */
	void *e=NULL;   /* front pointer */
	Q=(LQueue *)malloc(sizeof(LQueue)); /* allocate memory */
	Q->length=-1; /* symbolize not init */
	while(1){
		menu();
    	printf("请输入你要进行的操作：");
    	scanf("%c",&option);
		fflush(stdin);
		while(option>'9'||option<'1'){
			printf("\n\n你输入的数据有误（请输入1-9），请重新输入：");
			scanf("%c",&option);
			fflush(stdin);
		}
		switch(option){
			case '1':
				InitLQueue(Q); 
				system("pause");
				system("cls");
				break; /* finish the switch */
			case '2':
				if(IsInitQueue(Q))DestoryLQueue(Q);
				system("pause");
				system("cls");
				break; 
			case '3':
				if(IsInitQueue(Q))type(Q); 
				//if(IsInitQueue(Q))EnLQueue(Q,type(Q)); /* dont do this or return data will turn back void */
				system("pause");
				getchar();
				system("cls");
				break;
			case '4':
				if(IsInitQueue(Q)&&!IsEmptyLQueue(Q))DeLQueue(Q); 
				else if(IsEmptyLQueue(Q))printf("\n当前队列为空，无法进行出队操作！请先入队！\n\n");
				system("pause");
				system("cls");
				break;
			case '5':
				if(IsInitQueue(Q)&&!IsEmptyLQueue(Q))TraverseLQueue(Q);
				else if(IsEmptyLQueue(Q))printf("\n当前队列为空！请先入队！\n\n");
				system("pause");
				system("cls");
				break;
			case '6':
				if(IsInitQueue(Q)&&!IsEmptyLQueue(Q))ClearLQueue(Q);
				else if(IsEmptyLQueue(Q))printf("\n当前队列为空，无需清空！请入队！\n\n");
				system("pause");
				system("cls");
				break;
			case '7':
				if(IsInitQueue(Q))LengthLQueue(Q);
				system("pause");
				system("cls");
				break;
			case '8':
				if(IsInitQueue(Q)&&!IsEmptyLQueue(Q))GetHeadLQueue(Q,e);
				else if(IsEmptyLQueue(Q))printf("\n当前队列为空，没有对头元素！请入队！\n\n");
				system("pause");
				system("cls");
				break;
			case '9':
				return 0; 
		}
	}	
}
