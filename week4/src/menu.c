#include "binary_sort_tree.h"
void menu(){
	printf("************************ϵͳ���ܲ˵�****************************\n");
    printf("----------------------------------------------------------------\n");
    printf("    ********************************************************    \n");
    printf("    *  1.��ʼ������������   * *    2.��������������        *    \n");
    printf("    ********************************************************    \n");
    printf("    *  3.ɾ�����           * *    4.������              *	\n");
    printf("    ********************************************************	\n");
    printf("    *  5.�������(�ݹ�)     * *    6.�������(�ǵݹ�)      *    \n");
    printf("    ********************************************************    \n");
    printf("    *  7.�������(�ݹ�)     * *    8 .�������(�ǵݹ�)     *    \n");
    printf("    ********************************************************    \n");
    printf("    *  9.�������(�ݹ�)     * *    10.�������(�ǵݹ�)     *    \n");
    printf("    ********************************************************    \n");
    printf("    *  11.��α���          * *    12.���ҽ���Ƿ�������   *    \n");
    printf("    ********************************************************    \n");
    printf("    *  13.�˳�ϵͳ                                         *    \n");
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
				printf("\n��������������������������������������룺");
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
