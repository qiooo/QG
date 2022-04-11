#include "binary_sort_tree.h"
Status BST_init(BinarySortTreePtr BST){ 
	BST->root=(NodePtr)malloc(sizeof(Node));
	printf("\n��������������ݣ�");
	BST->root->value=judgeinput(); 
	BST->root->left=NULL;
	BST->root->right=NULL;
	length=1;
	printf("\n��ʼ�������������ɹ���\n\n"); 
	return SUCCESS;
}

Status BST_IsInit(BinarySortTreePtr BST){
	if(BST->root!=NULL)return SUCCESS;
	else{
		printf("\nǰ������������δ��ʼ�������ȳ�ʼ����\n\n");
		return ERROR; 
	}
}

Status BST_IsEmpty(BinarySortTreePtr BST){
	if(BST->root->left==NULL&&BST->root->right==NULL)return SUCCESS;
	else return ERROR;
}

Status BST_insert(BinarySortTreePtr BST, ElemType value){
	NodePtr node,temp; /* node:�²���Ľ��,temp:��ʱ�Ľ�� */ 
	temp=BST->root;
	node=(NodePtr)malloc(sizeof(Node)); // �����½�� 
	node->value=value;
	node->left=NULL;
	node->right=NULL;
	while(1){
		if(value<temp->value){ // С�Ľ����� 
			if(temp->left==NULL){
				temp->left=node;
				break; 
			}
			else temp=temp->left;
		}
		else{                  // ������ҽ�� 
			if(temp->right==NULL){
				temp->right=node;
				break;
			}
			else temp=temp->right;
		}
	}
	length++;
	return SUCCESS;
}

Status BST_create(BinarySortTreePtr BST){
	ElemType i,n,value; /* i:������n:�����,value:����ֵ */ 
	printf("\n��������Ҫ����������������Ľ������");
	n=judgeinput();
	for(i=1;i<=n;i++){
		printf("\n�������%d���������ݣ�",i);
		value=judgeinput();
		BST_insert(BST,value);
	}
	printf("\n���������������ɹ���\n\n");
	return SUCCESS;
}

Status BST_delete(BinarySortTreePtr BST, ElemType value){
	NodePtr parent,cur,partemp,temp; /* parent:��ǰ���ĸ����,cur:��ǰ���,partemp:��ʱ���ĸ���㣬temp:��ʱ�Ľ�� */ 
	char c;                  /* ѡ�� */ 
	cur=BST->root;
	while(cur->value!=value){ 
	// ��Ϊ�жϹ��Ƿ���ڣ����Կ϶����ҵõ�����˲���Ҫ�������ҽ���Ƿ��Ϊnull����� 
		parent=cur;
		if(value<cur->value)cur=parent->left;
		else cur=parent->right;
	}
	// �ҵ�Ҫɾ���Ľ�� 
	if(cur->left==NULL&&cur->right==NULL){               // Ҷ��� 
		if(parent->left==cur)parent->left=NULL;
		else parent->right=NULL;
	}
	else if(cur->left==NULL||cur->right==NULL){         // ֻ��һ��������ҽ�� 
		if(parent->left==cur){                          // ���������� 
			if(cur->left==NULL)parent->left=cur->right; // ����Ϊ��
			else parent->left=cur->left;                // �ҽ��Ϊ�� 
		}
		else{                                           // �������ҽ�� 
			if(cur->left==NULL)parent->right=cur->right; 
			else parent->right=cur->left;
		} 
	}
	else{                                          // ���ҽ�㶼���� 
		printf("\n��ѡ����Ҫ�滻��ǰ���Ľ�㣺\n");
		printf("-----------------------------\n");
		printf("1.���������������ֵ�Ľ��\n");
		printf("\n2.��������������Сֵ�Ľ��\n");
		printf("-----------------------------\n");
		printf("���������ѡ��"); 
		fflush(stdin);
		c=getchar();
		fflush(stdin);
		while(c!='1'&&c!='2'){
			printf("\n������1��2���������룺");
			c=getchar();
			fflush(stdin);
		}
		switch(c){
			case '1':
				temp=cur->left;
				while(temp->right!=NULL){ // �ҵ��������е���� 
					partemp=temp;
					temp=temp->right;
				}
				partemp->right=NULL;
				if(parent->left==cur)parent->left=temp;
				else parent->right=temp;
				temp->left=cur->left;     // �滻��� 
				temp->right=cur->right;
				break;
			case '2':
				temp=cur->left;
				while(temp->left!=NULL){ // �ҵ��������е���С 
					partemp=temp;
					temp=temp->left;
				}
				partemp->left=NULL;
				if(parent->left==cur)parent->left=temp;
				else parent->right=temp;
				temp->left=cur->left;     // �滻��� 
				temp->right=cur->right;
				break;
		}
	}
	free(cur);
	length--;
	printf("\nɾ�����ɹ���\n\n");
	return SUCCESS; 
}

Status BST_search(BinarySortTreePtr BST, ElemType value){
	NodePtr temp; /* temp:��ʱ�Ľ�� */ 
	temp=BST->root;
	while(temp!=NULL){
		if(value==temp->value)return SUCCESS;
		if(value<temp->value)temp=temp->left;
		else temp=temp->right;
	}
	return ERROR; 
}

void print(NodePtr node){
	printf("%d ",node->value); 
}

Status BST_preorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)){
	NodePtr temp;   /* temp:��ʱ�Ľ�� */
	BinarySortTree *BSTL=NULL;
	BinarySortTree *BSTR=NULL;
	temp=BST->root; // ����Ϊ0 
	if(temp!=NULL){
		(*visit)(temp);
		BSTL=&(temp->left);
		BSTR=&(temp->right);
		BST_preorderI(BSTL,visit);
		BST_preorderI(BSTR,visit);
	}	
	return SUCCESS;
}

Status BST_preorderR(BinarySortTreePtr BST, void (*visit)(NodePtr)){
	NodePtr stack[length]; /* �������ջ */
	NodePtr temp;          /* temp:��ʱ�Ľ�� */
	ElemType i=0;          /* ���� */ 
	temp=BST->root;        // ����Ϊ0
	stack[i]=temp;         // �������ջ 
	while(i>=0){           // ��ջ 
		(*visit)(stack[i--]);
		if(temp->right!=NULL)stack[++i]=temp->right; // �ұ��Ƚ�ջ 
		if(temp->left!=NULL)stack[++i]=temp->left;
		temp=stack[i]; 
	}
	return SUCCESS; 
}

Status BST_inorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)){
	NodePtr temp;   /* temp:��ʱ�Ľ�� */
	BinarySortTree *BSTL=NULL;
	BinarySortTree *BSTR=NULL;
	temp=BST->root; // ����Ϊ0 
	if(temp!=NULL){
		BSTL=&(temp->left);
		BSTR=&(temp->right);
		BST_inorderI(BSTL,visit);
		(*visit)(temp);
		BST_inorderI(BSTR,visit);
	}	
	return SUCCESS;
}

Status BST_inorderR(BinarySortTreePtr BST, void (*visit)(NodePtr)){
	NodePtr stack[length]; /* �������ջ */
	NodePtr temp;          /* temp:��ʱ�Ľ�� */
	ElemType i=-1;         /* ���� */ 
	temp=BST->root;            // ����Ϊ0 
	while(temp!=NULL||i>=0){   // ������־ temp==null&&i==-1 
		while(temp!=NULL){     // ��ջ 
			stack[++i]=temp;    
			temp=temp->left; 	 
		}
		temp=stack[i];
		(*visit)(stack[i--]);  // ջ����ջ 
		temp=temp->right;      // �ҽ�� 
	} 
	return SUCCESS; 
}

Status BST_postorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)){
	NodePtr temp;   /* temp:��ʱ�Ľ�� */
	BinarySortTree *BSTL=NULL;
	BinarySortTree *BSTR=NULL;
	temp=BST->root; // ����Ϊ0 
	if(temp!=NULL){
		BSTL=&(temp->left);
		BSTR=&(temp->right);
		BST_postorderI(BSTL,visit);
		BST_postorderI(BSTR,visit);
		(*visit)(temp);
	}	
	return SUCCESS;
}

Status BST_postorderR(BinarySortTreePtr BST, void (*visit)(NodePtr)){
	NodePtr stack[length];      /* �������ջ */
	ElemType timestack[length]; /* ��¼���ʴ��� */
	NodePtr temp;               /* temp:��ʱ�Ľ��,parent:����� */
	ElemType i=-1;              /* ���� */ 
	temp=BST->root;             // ����Ϊ0 
	while(temp!=NULL||i>=0){    // ������־ temp==null&&i==-1 
		while(temp!=NULL){      // ��ջ 
			stack[++i]=temp;  
			timestack[i]=1;  
			temp=temp->left; 	 
		}
		if(timestack[i]==1){
			temp=stack[i];        // ȡջ
			timestack[i]=2;
			temp=temp->right;	
		}
		else (*visit)(stack[i--]); // ջ����ջ	
	} 
	return SUCCESS; 
}

Status BST_levelOrder(BinarySortTreePtr BST, void (*visit)(NodePtr)){ // Ӧ����������д���ã�˳�����˳��ջ�˷ѵĿռ�̫���� 
	NodePtr queue[length]; /* ������Ķ��� */
	NodePtr temp;          /* temp:��ʱ�Ľ�� */
	ElemType i=0,j;        /* i:������Ӹ�����j:��ջ */ 
	temp=BST->root;
	queue[i]=temp;         // �������� 
	for(j=i;j<length;j++){
		temp=queue[j];        // ��ǰ��� 
		(*visit)(queue[j]); // ����
		if(temp->left!=NULL)queue[++i]=temp->left;
		if(temp->right!=NULL)queue[++i]=temp->right;
	}
	return SUCCESS;
}
