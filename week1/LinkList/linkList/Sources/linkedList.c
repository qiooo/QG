#include "linkedList.h"
Status judge(LinkedList L){
	if(L==NULL){
		printf("\n��ǰ���������ȳ�ʼ������\n"); 
		return ERROR;
	}
	else if(L->next==NULL){
		printf("\n��ǰ����Ϊ�գ������´�������\n");
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
				printf("\n��������������������������������������룺");
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
	printf("\n��ʼ������ɹ���\n");
	printf("\n��������Ҫ����Ľڵ���(����)��"); 
	n=judgeinput();
	end=(*L);
	for(int i=1;i<=n;i++){
		node=(LinkedList)malloc(sizeof(LNode));
		printf("\n�������%d���ڵ������(����)��",i);
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
	printf("\n��������ɹ���\n");
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
	printf("\n��������Ҫ���뵽��λ�õ�ǰһ���ڵ������(�����ظ���Ĭ�ϵ�һ��)��");
	e=judgeinput();
	if(SearchList(q,e)==1){ /* q now is the current pointer,the sentence is false beacuse the value dont change */
		p=(LinkedList)malloc(sizeof(LNode));
		printf("\n��������Ҫ����Ľڵ�����ݣ�");
		p->data=judgeinput();
		while(q!=NULL){ /* how to do this without traverselist twice */
			if(q->data==e){
				p->next=q->next;
				q->next=p;
				printf("\n����ڵ�ɹ���\n");
				break;
			}
			q=q->next;
		} 
	}
	else printf("\nû���ҵ���Ҫ�����ǰ�ڵ㣡�������룡\n");
	return SUCCESS;
}

Status DeleteList(LNode *p, ElemType *e){ /* p is the head pointer */ 
	ElemType n;         /* data */
	LinkedList delnode; /* the deleted pointer */
	printf("\n��������Ҫɾ���Ľڵ��ǰ�ڵ����ݣ�");
	n=judgeinput();
	if(SearchList(p,n)==1){
		while(p!=NULL){ /* how to do this without traverselist twice */ 
			if(p->data==n){
				if(p->next!=NULL){
					delnode=p->next;
	    			e=&(delnode->data); /* why it dont point to the right value? */
					p->next=delnode->next;
					printf("\n�ѳɹ�ɾ�����ݣ�%d",*e);
					free(delnode);
				}
				else printf("\nɾ������ʧ�ܣ�����������ڵ����ݣ�\n"); 
				break;
			}
			p=p->next;
		} 
	}
	else printf("\nû���ҵ���Ҫ�����ǰ�ڵ㣡�������룡");
	printf("\n\n");
	return SUCCESS;
}

void TraverseList(LinkedList L, void (*visit)(ElemType e)){
	printf("\n��ǰ����Ϊ��\n");
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
	printf("\n����ת�ɹ���\n");
	return SUCCESS;
}

Status IsLoopList(LinkedList L){
	LinkedList p1,p2; /* p1 go 1 step everytime but p2 go 2 steps */
	p1=L->next; 
	if(p1->next!=NULL){ /* avoid only one pointer */
		p2=p1->next;
		while(p2->next!=NULL&&p2->next->next!=NULL){
			if(p2==p1){
				printf("\n��������ѭ������\n");
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
	printf("\n��������м�ڵ������Ϊ��%d",n);
	printf("\n\n");
	return node;	
} 

LNode* ReverseEvenList(LinkedList *L){
	LinkedList p,p1,p2; /* p,p1,p2 */
	if(p->next==NULL){
		printf("\n��ǰ�����޷���ת��\n"); 
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
	printf("\n����ת�ɹ���\n");
	return *L;
}

Status ToLoopList(LinkedList *L){
	LinkedList head; /* head pointer */
	head=(*L);
	while(head!=NULL){
		if(head->next==NULL){
			head->next=(*L)->next; /* connect from beginning to end */
			printf("\n����ѭ������ɹ���\n\n");
			return SUCCESS;
		}
		head=head->next;
	}
}
