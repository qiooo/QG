#include "binary_sort_tree.h"
Status BST_init(BinarySortTreePtr BST){ 
	BST->root=(NodePtr)malloc(sizeof(Node));
	printf("\n请输入根结点的数据：");
	BST->root->value=judgeinput(); 
	BST->root->left=NULL;
	BST->root->right=NULL;
	length=1;
	printf("\n初始化二叉排序树成功！\n\n"); 
	return SUCCESS;
}

Status BST_IsInit(BinarySortTreePtr BST){
	if(BST->root!=NULL)return SUCCESS;
	else{
		printf("\n前二叉排序树树未初始化，请先初始化！\n\n");
		return ERROR; 
	}
}

Status BST_IsEmpty(BinarySortTreePtr BST){
	if(BST->root->left==NULL&&BST->root->right==NULL)return SUCCESS;
	else return ERROR;
}

Status BST_insert(BinarySortTreePtr BST, ElemType value){
	NodePtr node,temp; /* node:新插入的结点,temp:暂时的结点 */ 
	temp=BST->root;
	node=(NodePtr)malloc(sizeof(Node)); // 创建新结点 
	node->value=value;
	node->left=NULL;
	node->right=NULL;
	while(1){
		if(value<temp->value){ // 小的进左结点 
			if(temp->left==NULL){
				temp->left=node;
				break; 
			}
			else temp=temp->left;
		}
		else{                  // 否则进右结点 
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
	ElemType i,n,value; /* i:迭代，n:结点数,value:数据值 */ 
	printf("\n请输入你要创建的排序二叉树的结点数：");
	n=judgeinput();
	for(i=1;i<=n;i++){
		printf("\n请输入第%d个结点的数据：",i);
		value=judgeinput();
		BST_insert(BST,value);
	}
	printf("\n创建二叉排序树成功！\n\n");
	return SUCCESS;
}

Status BST_delete(BinarySortTreePtr BST, ElemType value){
	NodePtr parent,cur,partemp,temp; /* parent:当前结点的父结点,cur:当前结点,partemp:暂时结点的父结点，temp:暂时的结点 */ 
	char c;                  /* 选择 */ 
	cur=BST->root;
	while(cur->value!=value){ 
	// 因为判断过是否存在，所以肯定能找得到，因此不需要考虑左右结点是否均为null的情况 
		parent=cur;
		if(value<cur->value)cur=parent->left;
		else cur=parent->right;
	}
	// 找到要删除的结点 
	if(cur->left==NULL&&cur->right==NULL){               // 叶结点 
		if(parent->left==cur)parent->left=NULL;
		else parent->right=NULL;
	}
	else if(cur->left==NULL||cur->right==NULL){         // 只有一个左结点或右结点 
		if(parent->left==cur){                          // 父结点的左结点 
			if(cur->left==NULL)parent->left=cur->right; // 左结点为空
			else parent->left=cur->left;                // 右结点为空 
		}
		else{                                           // 父结点的右结点 
			if(cur->left==NULL)parent->right=cur->right; 
			else parent->right=cur->left;
		} 
	}
	else{                                          // 左右结点都存在 
		printf("\n请选择你要替换当前结点的结点：\n");
		printf("-----------------------------\n");
		printf("1.左子树中数据最大值的结点\n");
		printf("\n2.右子树中数据最小值的结点\n");
		printf("-----------------------------\n");
		printf("请输入你的选择："); 
		fflush(stdin);
		c=getchar();
		fflush(stdin);
		while(c!='1'&&c!='2'){
			printf("\n请输入1或2！重新输入：");
			c=getchar();
			fflush(stdin);
		}
		switch(c){
			case '1':
				temp=cur->left;
				while(temp->right!=NULL){ // 找到左子树中的最大 
					partemp=temp;
					temp=temp->right;
				}
				partemp->right=NULL;
				if(parent->left==cur)parent->left=temp;
				else parent->right=temp;
				temp->left=cur->left;     // 替换结点 
				temp->right=cur->right;
				break;
			case '2':
				temp=cur->left;
				while(temp->left!=NULL){ // 找到右子树中的最小 
					partemp=temp;
					temp=temp->left;
				}
				partemp->left=NULL;
				if(parent->left==cur)parent->left=temp;
				else parent->right=temp;
				temp->left=cur->left;     // 替换结点 
				temp->right=cur->right;
				break;
		}
	}
	free(cur);
	length--;
	printf("\n删除结点成功！\n\n");
	return SUCCESS; 
}

Status BST_search(BinarySortTreePtr BST, ElemType value){
	NodePtr temp; /* temp:暂时的结点 */ 
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
	NodePtr temp;   /* temp:暂时的结点 */
	BinarySortTree *BSTL=NULL;
	BinarySortTree *BSTR=NULL;
	temp=BST->root; // 不会为0 
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
	NodePtr stack[length]; /* 存放树的栈 */
	NodePtr temp;          /* temp:暂时的结点 */
	ElemType i=0;          /* 迭代 */ 
	temp=BST->root;        // 不会为0
	stack[i]=temp;         // 根结点入栈 
	while(i>=0){           // 出栈 
		(*visit)(stack[i--]);
		if(temp->right!=NULL)stack[++i]=temp->right; // 右边先进栈 
		if(temp->left!=NULL)stack[++i]=temp->left;
		temp=stack[i]; 
	}
	return SUCCESS; 
}

Status BST_inorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)){
	NodePtr temp;   /* temp:暂时的结点 */
	BinarySortTree *BSTL=NULL;
	BinarySortTree *BSTR=NULL;
	temp=BST->root; // 不会为0 
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
	NodePtr stack[length]; /* 存放树的栈 */
	NodePtr temp;          /* temp:暂时的结点 */
	ElemType i=-1;         /* 迭代 */ 
	temp=BST->root;            // 不会为0 
	while(temp!=NULL||i>=0){   // 结束标志 temp==null&&i==-1 
		while(temp!=NULL){     // 入栈 
			stack[++i]=temp;    
			temp=temp->left; 	 
		}
		temp=stack[i];
		(*visit)(stack[i--]);  // 栈顶出栈 
		temp=temp->right;      // 右结点 
	} 
	return SUCCESS; 
}

Status BST_postorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)){
	NodePtr temp;   /* temp:暂时的结点 */
	BinarySortTree *BSTL=NULL;
	BinarySortTree *BSTR=NULL;
	temp=BST->root; // 不会为0 
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
	NodePtr stack[length];      /* 存放树的栈 */
	ElemType timestack[length]; /* 记录访问次数 */
	NodePtr temp;               /* temp:暂时的结点,parent:父结点 */
	ElemType i=-1;              /* 迭代 */ 
	temp=BST->root;             // 不会为0 
	while(temp!=NULL||i>=0){    // 结束标志 temp==null&&i==-1 
		while(temp!=NULL){      // 入栈 
			stack[++i]=temp;  
			timestack[i]=1;  
			temp=temp->left; 	 
		}
		if(timestack[i]==1){
			temp=stack[i];        // 取栈
			timestack[i]=2;
			temp=temp->right;	
		}
		else (*visit)(stack[i--]); // 栈顶出栈	
	} 
	return SUCCESS; 
}

Status BST_levelOrder(BinarySortTreePtr BST, void (*visit)(NodePtr)){ // 应该用链表来写更好，顺序队列顺序栈浪费的空间太多了 
	NodePtr queue[length]; /* 存放树的队列 */
	NodePtr temp;          /* temp:暂时的结点 */
	ElemType i=0,j;        /* i:迭代入队个数，j:出栈 */ 
	temp=BST->root;
	queue[i]=temp;         // 根结点入队 
	for(j=i;j<length;j++){
		temp=queue[j];        // 当前结点 
		(*visit)(queue[j]); // 出队
		if(temp->left!=NULL)queue[++i]=temp->left;
		if(temp->right!=NULL)queue[++i]=temp->right;
	}
	return SUCCESS;
}
