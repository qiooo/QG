#include "linkedList.h"
Status judge(LinkedList L){
	if(L==NULL){
		printf("\n当前无链表，请先初始化链表！\n"); 
		return ERROR;
	}
	else if(L->next==NULL){
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

Status InitList(LinkedList *L){
	ElemType n;          /* input the number of nodes */
	LinkedList node,end; /* node(the ordinary node),end(the end node) */
	(*L)=(LinkedList)malloc(sizeof(LNode));
	(*L)->next=NULL;
	printf("\n初始化链表成功！\n");
	printf("\n请输入你要构造的节点数(整数)："); 
	n=judgeinput();
	end=(*L);
	for(int i=1;i<=n;i++){
		node=(LinkedList)malloc(sizeof(LNode));
		printf("\n请输入第%d个节点的数据(整数)：",i);
		node->data=judgeinput();
		end->next=node;
		end=node;
	}
	end->next=NULL;
	printf("\n");
	return SUCCESS;
} 

void DestroyList(LinkedList *L){
	LNode *node;
	while((*L)!=NULL){
		node=(*L);
		*L=(*L)->next; /* L is the latter pointer,(if*L=node->next,node's next has already been destroyed) */
		free(node);
	}
	printf("\n销毁链表成功！\n");
}

Status SearchList(LinkedList L, ElemType e){
	while(L!=NULL){
		if(L->data==e)
			return SUCCESS;
		L=L->next;
	}
	return ERROR;
}

Status InsertList(LNode *p, LNode *q){ /* p is the insert pointer,q is the head pointer */
	ElemType e; /* data */
	printf("\n请输入你要插入到的位置的前一个节点的数据(若有重复则默认第一个)：");
	e=judgeinput();
	if(SearchList(q,e)==1){ /* q now is the current pointer,the sentence is false beacuse the value dont change */
		p=(LinkedList)malloc(sizeof(LNode));
		printf("\n请输入你要插入的节点的数据：");
		p->data=judgeinput();
		while(q!=NULL){ /* how to do this without traverselist twice */
			if(q->data==e){
				p->next=q->next;
				q->next=p;
				printf("\n插入节点成功！\n");
				break;
			}
			q=q->next;
		} 
	}
	else printf("\n没有找到你要插入的前节点！请检查输入！\n");
	return SUCCESS;
}

Status DeleteList(LNode *p, ElemType *e){ /* p is the head pointer */ 
	ElemType n;         /* data */
	LinkedList delnode; /* the deleted pointer */
	printf("\n请输入你要删除的节点的前节点数据：");
	n=judgeinput();
	if(SearchList(p,n)==1){
		while(p!=NULL){ /* how to do this without traverselist twice */ 
			if(p->data==n){
				if(p->next!=NULL){
					delnode=p->next;
	    			e=&(delnode->data); /* why it dont point to the right value? */
					p->next=delnode->next;
					printf("\n已成功删除数据：%d",*e);
					free(delnode);
				}
				else printf("\n删除数据失败，请重新输入节点数据！\n"); 
				break;
			}
			p=p->next;
		} 
	}
	else printf("\n没有找到你要插入的前节点！请检查输入！");
	printf("\n\n");
	return SUCCESS;
}

void TraverseList(LinkedList L, void (*visit)(ElemType e)){
	printf("\n当前链表为：\n");
	L=L->next;
	while(L!=NULL){
		printf("%d->",L->data);
		L=L->next;
	}
	printf("NULL\n\n");
}

Status ReverseList(LinkedList *L){
	LinkedList revhead;        /* the new head pointer */
	LinkedList revnode,revend; /* revnode(the ordinary node),revend(new end pointer) */
	revend=(*L)->next;
	revnode=revend->next;
	revend->next=NULL; /* the first time reverse */
	revhead=revend;
	while(revnode!=NULL){
		revend=revnode;
		revnode=revend->next;
		revend->next=revhead;
		revhead=revend;
	}
	(*L)->next=revhead; /* dont change the born head pointer */
	printf("\n链表反转成功！\n");
	return SUCCESS;
}

Status IsLoopList(LinkedList L){
	LinkedList p1,p2; /* p1 go 1 step everytime but p2 go 2 steps */
	p1=L->next; 
	if(p1->next!=NULL){ /* avoid only one pointer */
		p2=p1->next;
		while(p2->next!=NULL&&p2->next->next!=NULL){
			if(p2==p1){
				printf("\n该链表是循环链表\n");
				return SUCCESS;
			}
			p1=p1->next;
			p2=p2->next->next;
		}
	}
	return ERROR; 
}

LNode* FindMidNode(LinkedList *L){
	ElemType len=0,n; /* len is the length of list,n is the middata */
	LinkedList node;  /* for the traverse */
	node=(*L)->next;
	while(node!=NULL){ /* get the length */
		node=node->next;
		len++;
	} 
	node=(*L)->next; /* go back the beginning */
	if(len%2==0){
		for(int i=1;i<=len/2;i++){
			if(i==len/2){
				n=node->data;
				break;
			}
			node=node->next;	
		}
	}
	else{
		for(int i=1;i<=len/2+1;i++){
			if(i==len/2+1){
				n=node->data;
				break;
			}
			node=node->next;
		}
	}
	printf("\n该链表的中间节点的数据为：%d",n);
	printf("\n\n");
	return node;	
} 

LNode* ReverseEvenList(LinkedList *L){
	LinkedList p,p1,p2; /* p,p1,p2 */
	if(p->next==NULL){
		printf("\n当前链表无法反转！\n"); 
		return *L; /* only one pointer */
	}
	p=(*L);
	while(p->next!=NULL&&(p->next)->next!=NULL){
		p1=p->next;
		p2=p1->next;
		p->next=p2; /* reverse */ 
		p1->next=p2->next;
		p2->next=p1;
		p=p1; /* make the traverse continue*/
		
	}
	printf("\n链表反转成功！\n");
	return *L;
}

Status ToLoopList(LinkedList *L){
	LinkedList head; /* head pointer */
	head=(*L);
	while(head!=NULL){
		if(head->next==NULL){
			head->next=(*L)->next; /* connect from beginning to end */
			printf("\n生成循环链表成功！\n\n");
			return SUCCESS;
		}
		head=head->next;
	}
}
