#include "LinkStack.h" 
int main(){
	void menu();
	void operation();
	ElemType judgeinput();
	Status isInitStack(LinkStack *s);
	short option;      /* choose the function to orperate */
	LinkStack *s=NULL; /* init the pointer */
	ElemType data;     /* insert or delete data */
	ElemType *e=NULL;  /* the top pointer value */
	int *length=NULL;  /* the length of list node */
	s=(LinkStack *)malloc(sizeof(LinkStack));
	s->count=-1;       /* to judge the link init */
	while(1){
		menu();
    	printf("��������Ҫ���еĲ�����");
		while(1){
			option=judgeinput(); /* check the type */ 
			if(option>8||option<0)printf("\n���������������������1-8�������������룺");
			else break;
		}
		switch(option){
			case 1:
				initLStack(s);
				operation();
				break; /* finish the switch */
			case 2:
				if(isInitStack(s))destroyLStack(s);
				operation();
				break; 
			case 3:
				if(isInitStack(s)){
					printf("\n��������Ҫ��ջ�����ݣ�");
					data=judgeinput();
					pushLStack(s,data); 
				} 
				operation();
				break;
			case 4:
				if(isInitStack(s)&&isEmptyLStack(s))popLStack(s,&data);
				operation();
				break;
			case 5:
				if(isInitStack(s)&&isEmptyLStack(s))getTopLStack(s,e);
				operation();
				break;
			case 6:
				if(isInitStack(s)&&isEmptyLStack(s))clearLStack(s);
				operation();
				break;
			case 7:
				if(isInitStack(s))LStackLength(s,length);
				operation();
				break;
			case 8:
				return 0; 
		}
	}	
} 
