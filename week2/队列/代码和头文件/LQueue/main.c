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
    	printf("��������Ҫ���еĲ�����");
    	scanf("%c",&option);
		fflush(stdin);
		while(option>'9'||option<'1'){
			printf("\n\n���������������������1-9�������������룺");
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
				else if(IsEmptyLQueue(Q))printf("\n��ǰ����Ϊ�գ��޷����г��Ӳ�����������ӣ�\n\n");
				system("pause");
				system("cls");
				break;
			case '5':
				if(IsInitQueue(Q)&&!IsEmptyLQueue(Q))TraverseLQueue(Q);
				else if(IsEmptyLQueue(Q))printf("\n��ǰ����Ϊ�գ�������ӣ�\n\n");
				system("pause");
				system("cls");
				break;
			case '6':
				if(IsInitQueue(Q)&&!IsEmptyLQueue(Q))ClearLQueue(Q);
				else if(IsEmptyLQueue(Q))printf("\n��ǰ����Ϊ�գ�������գ�����ӣ�\n\n");
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
				else if(IsEmptyLQueue(Q))printf("\n��ǰ����Ϊ�գ�û�ж�ͷԪ�أ�����ӣ�\n\n");
				system("pause");
				system("cls");
				break;
			case '9':
				return 0; 
		}
	}	
}
