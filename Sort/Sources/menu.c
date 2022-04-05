#include "sort.h"
void menu(){
	printf("************************系统功能菜单****************************\n");
    printf("----------------------------------------------------------------\n");
    printf("    ********************************************************    \n");
    printf("    *  1.创建文件           * *    2.查询文件              *    \n");
    printf("    ********************************************************    \n");
    printf("    *  3.生成随机数         * *    4.插入排序              *	\n");
    printf("    ********************************************************	\n");
    printf("    *  5.归并排序           * *    6.快速排序(递归)        *    \n");
    printf("    ********************************************************    \n");
    printf("    *  7.计数排序           * *    8 .基数计数排序         *    \n");
    printf("    ********************************************************    \n");
    printf("    *  9.大数据量用时测试   * *   10.大量小数据量用时测试  *    \n");
    printf("    ********************************************************    \n");
    printf("    *  11.查找随机数数组的第K大第K小的值                   *    \n");
    printf("    ********************************************************    \n");
    printf("    *  12.颜色排序          * *   13.退出系统              *    \n");
    printf("    ********************************************************    \n");
    printf("----------------------------------------------------------------\n");
} 

void operation(){
	system("pause"); 
	getchar();
	system("cls");
}

int judgeinput(){ /* to judge the input's type and change the 'int' type from char to int */
	char input[10];
	int flag=1;  /* when flag=0 means input a wrong data */
	int len,n=0; /* len(the length of input),n(the real input data) */  
	while(flag==1){
		scanf("%s",input); /* input the data */
		len=strlen(input);
		for(int i=0;i<len;i++){
			if(*(input+i)<'0'||*(input+i)>'9'){ /* judge if input a unreasonable data */
				printf("\n你输入的数据有误（请输入整数），请重新输入：");
				break;
			}
			else if(i==strlen(input)-1)flag=0; /* if not stop input and go next*/
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


