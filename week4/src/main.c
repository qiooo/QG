#include "binary_sort_tree.h"
int main() {
	short option;
	BinarySortTree *BST=NULL; /* ���ڵ� */ 
	ElemType value;           /* ����ֵ */ 
	BST=(BinarySortTreePtr)malloc(sizeof(BinarySortTree));
	BST->root=NULL;
	length=0; 
	while(1){
		menu();
    	printf("��������Ҫ���еĲ�����");
		while(1){
			option=judgeinput(); /* check the type */ 
			if(option>13||option<0)printf("\n���������������������1-13�������������룺");
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
					else printf("\n��ǰ�����������ǿգ�����в��������\n\n");
				}
				operation();
				break; 
			case 3:
				if(BST_IsInit(BST)){
					printf("\n������Ҫɾ���Ľ������ݣ�");
					value=judgeinput();
					if(BST_search(BST,value)){
						if(BST_IsEmpty(BST))printf("\n�ý������Ϊ���������ݣ�����ɾ�������������и���㣡\n\n");
						else BST_delete(BST,value); // ���ݴ��ڽ���ɾ������
					}
					else printf("\n�����ݲ������ڶ����������У�����������Ҫɾ���Ľ�����ݣ�\n\n");
				}
				operation();
				break;
			case 4:
				if(BST_IsInit(BST)){
					printf("\n������Ҫ����Ľ������ݣ�");
					value=judgeinput(); 
					BST_insert(BST,value);
					printf("\n������ɹ���\n\n");
				}
				operation();
				break; 
			case 5:
				printf("\n�����������ĵݹ�������������\n"); 
				if(BST_IsInit(BST))BST_preorderI(BST,print);
				printf("\n\n");
				operation();
				break;
			case 6:
				printf("\n�����������ķǵݹ�������������\n"); 
				if(BST_IsInit(BST))BST_preorderR(BST,print);
				printf("\n\n");
				operation();
				break;
			case 7:
				printf("\n�����������ĵݹ�������������\n"); 
				if(BST_IsInit(BST))BST_inorderI(BST,print);
				printf("\n\n");
				operation();
				break;
			case 8:
				printf("\n�����������ķǵݹ�������������\n"); 
				if(BST_IsInit(BST))BST_inorderR(BST,print);
				printf("\n\n");
				operation();
				break;
			case 9:
				printf("\n�����������ĵݹ������������\n"); 
				if(BST_IsInit(BST))BST_postorderI(BST,print);
				printf("\n\n");
				operation();
				break;
			case 10:
				printf("\n�����������ķǵݹ������������\n"); 
				if(BST_IsInit(BST))BST_postorderR(BST,print);
				printf("\n\n");
				operation();
				break;
			case 11:
				printf("\n�����������Ĳ�α��������\n"); 
				if(BST_IsInit(BST))BST_levelOrder(BST,print);
				printf("\n\n");
				operation();
				break;
			case 12:
				if(BST_IsInit(BST)){
					printf("\n������Ҫ���ҵĽ������ݣ�");
					value=judgeinput(); 
					if(BST_search(BST,value))printf("\n�����ݴ����ڶ����������У�\n\n");
					else printf("\n�����ݲ������ڶ����������У�\n\n");
				}
				operation();
				break;	
			case 13: 
				return 0; 
		}
	}	
}
