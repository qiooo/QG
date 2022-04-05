#include "sort.h"
char filename[20]; /* file's name */
int length=0;      /* length of array */

int main(){
	short option;          /* choose the function to operate */
	int *a=NULL;           /* array one-dimensional pointer */
	int *temp=NULL;        /* a temp array to sort */ 
	int K,Kmax,Kmin;
		while(1){
		menu();
    	printf("��������Ҫ���еĲ�����");
		while(1){
			option=judgeinput(); /* check the type */ 
			if(option>13||option<0)printf("\n���������������������1-11�������������룺");
			else break;
		}
		switch(option){
			case 1:
				Initfile();
				operation();
				break; /* finish the switch */
			case 2:
				if(openfile()&&nullfile())traversefile();
				operation();
				break; 
			case 3:
				if(openfile())generate(&a,0); // ǰ���ǲ����������ļ� 
				operation();
				break;
			case 4:
				if(openfile()&&nullfile()){        // Ϊ��ʱ���ļ������� 
					if(!a)getdata(&a);
    				insertSort(a,length); 				
					printf("\n����������ɣ�\n");
					result(a,length);
				}
				operation();
				break;
			case 5:
				if(openfile()&&nullfile()){        // Ϊ��ʱ���ļ������� 
					if(!a)getdata(&a);
					MergeSort(a,0,length-1,temp);
					printf("\n�鲢������ɣ�\n");
					result(a,length);
				}
				operation();
				break;
			case 6:
				if(openfile()&&nullfile()){
					if(!a)getdata(&a);
					QuickSort_Recursion(a,0,length-1);
					printf("\n��������(�ݹ�)��ɣ�\n");
					result(a,length);
				}
				operation();
				break;
			case 7:
				if(openfile()&&nullfile()){
					if(!a)getdata(&a);
					CountSort(a,length);
					printf("\n����������ɣ�\n");
					result(a,length);
				}
				operation();
				break;
			case 8:
				if(openfile()&&nullfile()){
					if(!a)getdata(&a);
					RadixCountSort(a,length);
					printf("\n��������������ɣ�\n");
					result(a,length);
				}
				operation();
				break;
			case 9:
				Initfile();     // create a file
				generate(&a,1); // generate datas 
				testmeans(a);
				operation();
				break;
			case 10:
				testtimes(a);
				operation();
				break;
			case 11: 
				if(openfile()&&nullfile()){
					if(!a)getdata(&a);
					printf("\n������Kֵ��");
					K=judgeinput();
					while(K>length){
						printf("\n��ǰ���鳤��Ϊ%d,������1~%d��������",length,length);
						K=judgeinput();
					}
					Kminmax(a,0,length-1,K,Kmax,Kmin);
				}
				operation();
				break;
			case 12:
				if(openfile()){
					generate(&a,2);
					ColorSort(a,length);
					printf("\n��ɫ������ɣ�\n");
					result(a,length);	
				}
				operation();
				break;
			case 13:
				return 0; 
		}
	}	 
}
