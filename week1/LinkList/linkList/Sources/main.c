#include "linkedList.h"
int main(){ 
	void menu();
	void operation();
	void (*visit)(ElemType e)=NULL;  /* dont understand the meaning of this function */
	Status judge(LinkedList L);      /* if the list has not created */
	Status ToLoopList(LinkedList *L); /* become a looplist */
	ElemType judgeinput();           /* jugde the input if it is reasonable */
	short option;                    /* choose the option */  
	LinkedList L=NULL;               /* the head pointer */
	LinkedList p=NULL;               /* actionable pointers */
	ElemType n;                      /* n(the searching data) */
	ElemType *e=NULL;                /* the deleted data pointer */
	while(1){
		menu();
    	printf("请输入你要进行的操作：");
		while(1){
			option=judgeinput(); /* check the type */ 
			if(option>12||option<0)printf("\n你输入的数据有误（请输入1-10），请重新输入：");
			else break;
		}
		switch(option){
			case 1:
				InitList(&L); 
				operation();
				break; /* finish the switch */
			case 2:
				if(judge(L)==1&&IsLoopList(L)==0)DestroyList(&L);
				operation();
				break; 
			case 3:
				if(judge(L)==1&&IsLoopList(L)==0)InsertList(p,L);
				operation();
				break;
			case 4:
				if(judge(L)==1&&IsLoopList(L)==0)DeleteList(L,e);
				operation();
				break;
			case 5:
				if(judge(L)==1&&IsLoopList(L)==0)TraverseList(L,visit);
				operation();
				break;
			case 6:
				if(judge(L)==1&&IsLoopList(L)==0){
					printf("\n请输入你要查找的节点的数据：");
					n=judgeinput();
					if(SearchList(L,n)==1)printf("\n该数据在链表中\n");
					else printf("\n该数据不在链表中\n");
				}
				operation();
				break;
			case 7:
				if(judge(L)==1&&IsLoopList(L)==0)ReverseList(&L);
				operation();
				break;
			case 8:
				if(judge(L)==1){
					if(IsLoopList(L)==0)printf("\n该链表不是循环链表\n");
				}
				operation();
				break;
			case 9:
				if(judge(L)==1&&IsLoopList(L)==0)FindMidNode(&L);
				operation();
				break;
			case 10:
				if(judge(L)==1&&IsLoopList(L)==0)ReverseEvenList(&L);
				operation();
				break;
			case 11:
				if(judge(L)==1&&IsLoopList(L)==0)ToLoopList(&L);
				operation();
				break;	
			case 12:
				return 0; 
		}
	}	
}
