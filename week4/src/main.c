#include "binary_sort_tree.h"
int main() {
	short option;
	BinarySortTree *BST=NULL; /* 根节点 */ 
	ElemType value;           /* 结点的值 */ 
	BST=(BinarySortTreePtr)malloc(sizeof(BinarySortTree));
	BST->root=NULL;
	length=0; 
	while(1){
		menu();
    	printf("请输入你要进行的操作：");
		while(1){
			option=judgeinput(); /* check the type */ 
			if(option>13||option<0)printf("\n你输入的数据有误（请输入1-13），请重新输入：");
			else break;
		}
		switch(option){
			case 1:
				BST_init(BST);
				operation();
				break; 
			case 2:
				if(BST_IsInit(BST)){
					if(BST_IsEmpty(BST))BST_create(BST);
					else printf("\n当前二叉排序树非空，请进行插入操作！\n\n");
				}
				operation();
				break; 
			case 3:
				if(BST_IsInit(BST)){
					printf("\n请输入要删除的结点的数据：");
					value=judgeinput();
					if(BST_search(BST,value)){
						if(BST_IsEmpty(BST))printf("\n该结点数据为根结点的数据，不能删除二叉排序树中根结点！\n\n");
						else BST_delete(BST,value); // 数据存在进行删除操作
					}
					else printf("\n该数据不存在于二叉排序树中！请重新输入要删除的结点数据！\n\n");
				}
				operation();
				break;
			case 4:
				if(BST_IsInit(BST)){
					printf("\n请输入要插入的结点的数据：");
					value=judgeinput(); 
					BST_insert(BST,value);
					printf("\n插入结点成功！\n\n");
				}
				operation();
				break; 
			case 5:
				printf("\n二叉排序树的递归先序遍历结果：\n"); 
				if(BST_IsInit(BST))BST_preorderI(BST,print);
				printf("\n\n");
				operation();
				break;
			case 6:
				printf("\n二叉排序树的非递归先序遍历结果：\n"); 
				if(BST_IsInit(BST))BST_preorderR(BST,print);
				printf("\n\n");
				operation();
				break;
			case 7:
				printf("\n二叉排序树的递归中序遍历结果：\n"); 
				if(BST_IsInit(BST))BST_inorderI(BST,print);
				printf("\n\n");
				operation();
				break;
			case 8:
				printf("\n二叉排序树的非递归中序遍历结果：\n"); 
				if(BST_IsInit(BST))BST_inorderR(BST,print);
				printf("\n\n");
				operation();
				break;
			case 9:
				printf("\n二叉排序树的递归后序遍历结果：\n"); 
				if(BST_IsInit(BST))BST_postorderI(BST,print);
				printf("\n\n");
				operation();
				break;
			case 10:
				printf("\n二叉排序树的非递归后序遍历结果：\n"); 
				if(BST_IsInit(BST))BST_postorderR(BST,print);
				printf("\n\n");
				operation();
				break;
			case 11:
				printf("\n二叉排序树的层次遍历结果：\n"); 
				if(BST_IsInit(BST))BST_levelOrder(BST,print);
				printf("\n\n");
				operation();
				break;
			case 12:
				if(BST_IsInit(BST)){
					printf("\n请输入要查找的结点的数据：");
					value=judgeinput(); 
					if(BST_search(BST,value))printf("\n该数据存在于二叉排序树中！\n\n");
					else printf("\n该数据不存在于二叉排序树中！\n\n");
				}
				operation();
				break;	
			case 13: 
				return 0; 
		}
	}	
}
