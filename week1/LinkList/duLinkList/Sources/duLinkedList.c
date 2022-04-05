#include "duLinkedList.h"
Status judge(DuLinkedList L){
	if(L==NULL){
		printf("\n当前无链表，请先初始化链表！\n"); 
		return ERROR;
	}
	else if(L->next==NULL&&L->prior==NULL){
		printf("\n当前链表为空，请重新创建链表！\n");
		return ERROR;
	}
	else return SUCCESS;
}

ElemType judgeinput(){
	char input[10];
	int flag=1;  /* when flag=0 is input a wrong data */
	int len,n=0; /* len is the length of input,n is the real input data */  
	while(flag==1){
		scanf("%s",input); /* input the data */
		fflush(stdin);     /* clean up the cache to avoid the situation like blank space*/
		len=strlen(input);
		for(int i=0;i<len;i++){
			if(*(input+i)<'0'||*(input+i)>'9'){ /* judge if input a unreasonable data */
				printf("\n你输入的数据有误（请输入整数），请重新输入：");
				break;
			}
			else if(i==strlen(input)-1)flag=0; /* if not stop input */
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

Status InitList_DuL(DuLinkedList *L){
	ElemType n;            /* input the number of nodes */
	DuLinkedList node,end; /* node(the ordinary node),end(the end node) */
	(*L)=(DuLinkedList)malloc(sizeof(DuLNode));
	(*L)->next=NULL;
	(*L)->prior=NULL;
	printf("\n初始化链表成功！\n");
	printf("\n请输入你要构造的节点数(整数)："); 
	n=judgeinput();
	end=(*L);
	for(int i=1;i<=n;i++){
		node=(DuLinkedList)malloc(sizeof(DuLNode));
		printf("\n请输入第%d个节点的数据(整数)：",i);
		node->data=judgeinput();
		end->next=node;
		node->prior=end;
		end=node;
	}
	end->next=NULL;
	printf("\n");
	return SUCCESS;
}

void DestroyList_DuL(DuLinkedList *L){
	DuLNode *node;
	while((*L)!=NULL){
		node=(*L);
		*L=(*L)->next; /* L is the latter pointer,(if*L=node->next,node's next has already been destroyed) */
		if((*L)==NULL)free(node);
		else (*L)->prior=NULL;
	} 
	printf("\n销毁链表成功！\n");
}

Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q){
	ElemType e; /* data */
	printf("\n请输入你要插入到的位置的后一个节点的数据(若有重复则默认第一个)：");
	e=judgeinput();
	while(q!=NULL){ /* how to do this without traverselist twice */
		if(q->data==e){
			p=(DuLinkedList)malloc(sizeof(DuLNode));
			printf("\n请输入你要插入的节点的数据：");
			p->data=judgeinput();
			p->next=q; /* begin inseting */
			p->prior=q->prior;
			q->prior->next=p;
			q->prior=p; 
			printf("\n插入节点成功！\n\n");
			break;
		}
		else if(q->next==NULL)printf("\n没有找到你要插入的后节点！请检查输入！\n\n");
		q=q->next;
	} 
	return SUCCESS;
}

Status InsertAfterList_DuL(DuLNode *p, DuLNode *q){
	ElemType e; /* data */
	printf("\n请输入你要插入到的位置的前一个节点的数据(若有重复则默认第一个)：");
	e=judgeinput();
	while(q!=NULL){ /* how to do this without traverselist twice */
		if(q->data==e){
			p=(DuLinkedList)malloc(sizeof(DuLNode));
			printf("\n请输入你要插入的节点的数据：");
			p->data=judgeinput();
			if(q->next==NULL){ /* two situations:the end node is null?*/
				p->prior=q;
				p->next=q->next;
				q->next=p;
			}
			else{
				p->prior=q;
				p->next=q->next;
				q->next=p;
				q->next->prior=p;
			}
			printf("\n插入节点成功！\n\n");
			break;
		}
		else if(q->next==NULL)printf("\n没有找到你要插入的后节点！请检查输入！\n\n");
		q=q->next;
	} 
	return SUCCESS;
}

Status DeleteList_DuL(DuLNode *p, ElemType *e){
	ElemType n;         /* data */
	DuLinkedList delnode; /* the deleted pointer */
	printf("\n请输入你要删除的节点的前节点数据：");
	n=judgeinput();
	while(p!=NULL){ /* how to do this without traverselist twice */ 
		if(p->data==n){
			delnode=p->next;
	    	e=&(delnode->data); /* why it dont point to the right value? */
			p->next=delnode->next;
			if(p->next!=NULL)p->next->prior=p; /* the end pointer only have single arrow*/
			printf("\n已成功删除数据：%d",*e);
			free(delnode);
			break;
		}
		else if(p->next==NULL)printf("\n没有找到你要插入的前节点！请检查输入！");
		p=p->next;
	} 
	printf("\n\n");
	return SUCCESS;
}

void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)){
	printf("\n当前链表为：\n");
	L=L->next;
	printf("NULL");
	while(L!=NULL){
		printf("<-%d->",L->data);//null<->1<->2->null
		L=L->next;
	}
	printf("NULL\n\n");
}

Status SearchList(DuLinkedList L, ElemType e){
	while(L!=NULL){
		if(L->data==e)
			return SUCCESS;
		L=L->next;
	}
	return ERROR;
}
