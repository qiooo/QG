#include "duLinkedList.h"
int main(){
	void menu();
	void operation();
	void (*visit)(ElemType e)=NULL; /* dont understand the meaning of this function */
	Status judge(DuLinkedList L);   /* if the list has not created */
	Status SearchList(DuLinkedList L, ElemType e);
	ElemType judgeinput();          /* jugde the input if it is reasonable */
	short option;                   /* choose the option */  
	DuLinkedList L=NULL;            /* the head pointer */
	DuLinkedList p=NULL;            /* actionable pointers */
	ElemType n;                     /* n(the searching data) */
	ElemType *e=NULL;               /* the deleted data pointer */
	while(1){
		menu();
    	printf("��������Ҫ���еĲ�����");
		while(1){
			option=judgeinput(); /* check the type */ 
			if(option>8||option<0)printf("\n���������������������1-10�������������룺");
			else break;
		}
		switch(option){
			case 1:
				InitList_DuL(&L); 
				operation();
				break; /* finish the switch */
			case 2:
				if(judge(L)==1)DestroyList_DuL(&L);
				operation();
				break; 
			case 3:
				if(judge(L)==1)InsertBeforeList_DuL(p,L);
				operation();
				break;
			case 4:
				if(judge(L)==1)InsertAfterList_DuL(p,L);
				operation();
				break;
			case 5:
				if(judge(L)==1)DeleteList_DuL(L,e);
				operation();
				break;
			case 6:
				if(judge(L)==1)TraverseList_DuL(L,visit);
				operation();
				break;
			case 7:
				if(judge(L)==1){
					printf("\m��������Ҫ���ҵĽڵ�����ݣ�");
					n=judgeinput();
					if(SearchList(L,n)==1)printf("\n��������������\n");
					else printf("\n�����ݲ���������\n");
				}
				operation();
				break;
			case 8:
				return 0; 
		}
	}	
} 
