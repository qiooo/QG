#include "binary_sort_tree.h"
void menu(){
	printf("************************系统功能菜单****************************\n");
    printf("----------------------------------------------------------------\n");
    printf("    ********************************************************    \n");
    printf("    *  1.初始化二叉排序树   * *    2.创建二叉排序树        *    \n");
    printf("    ********************************************************    \n");
    printf("    *  3.删除结点           * *    4.插入结点              *	\n");
    printf("    ********************************************************	\n");
    printf("    *  5.先序遍历(递归)     * *    6.先序遍历(非递归)      *    \n");
    printf("    ********************************************************    \n");
    printf("    *  7.中序遍历(递归)     * *    8 .中序遍历(非递归)     *    \n");
    printf("    ********************************************************    \n");
    printf("    *  9.后序遍历(递归)     * *    10.后序遍历(非递归)     *    \n");
    printf("    ********************************************************    \n");
    printf("    *  11.层次遍历          * *    12.查找结点是否在树上   *    \n");
    printf("    ********************************************************    \n");
    printf("    *  13.退出系统                                         *    \n");
    printf("    ********************************************************    \n");
    printf("----------------------------------------------------------------\n");
} 

void operation(){
	system("pause"); 
	getchar();
	system("cls");
}

ElemType judgeinput(){ /* to judge the input's type and change the 'int' type from char to int */
	char input[10];
	int flag=1;        /* when flag=0 means input a wrong data */
	int len,i,j,k,n=0; /* len(the length of input),n(the real input data) */  
	while(flag==1){
		scanf("%s",input); /* input the data */
		len=strlen(input);
		for(i=0;i<len;i++){
			if(*(input+i)<'0'||*(input+i)>'9'){ /* judge if input a unreasonable data */
				printf("\n你输入的数据有误（请输入整数），请重新输入：");
				break;
			}
			else if(i==strlen(input)-1)flag=0; /* if not stop input and go next*/
		}
	}
	for(i=0,k=1;i<len;i++){ /* change the char into int */
		for(j=0;j<len-1-i;j++){
			k*=10;
		}
		n+=(input[i]-'0')*k; /* sum up all the digits */
		k=1; 
	}
	return n;
}
