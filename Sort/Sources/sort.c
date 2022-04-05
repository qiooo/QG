#include "sort.h"
void Initfile(){              // create a file
	FILE *fp;
	extern char filename[20]; /* file's name */
	printf("\n请输入你要创建的txt文件的文件名（若超过20个字则取前20个字）：");
	scanf("%s",filename);
	if((fp=fopen(filename,"w"))==NULL){
		printf("\n创建文件失败！\n\n");
		exit(0); //close all the file and exit the system
	} 
	else printf("\n创建文件成功！\n\n");
	fclose(fp); // close the file
}

int openfile(){               // if the filename has already existed
	FILE *fp;                 /* file */
	extern char filename[20]; /* file's name */
	printf("\n请输入你要操作的文件名：");
	scanf("%s",filename);
	if(!(fp=fopen(filename,"r"))){
		printf("\n该文件不存在！请先创建文件！\n\n");
		return 0; // not init 
	}
	else{
		fclose(fp);
		return 1; // already init
	}
}

int nullfile(){               // if has generate the array
	FILE *fp;                 /* file */
	extern char filename[20]; /* file's name */
	char c;                   /* getchar first */
	fp=fopen(filename,"r");
	c=fgetc(fp);
	if(!feof(fp)){
		fclose(fp);
		return 1; 
	}
	else{
		fclose(fp);
		printf("\n当前的文件内容为空！请先生成随机数数组！\n\n");
		return 0;
	}
}

void generate(int **a,int test){       /* secondary pointer */ 
	int judgeinput();
	int maxpos;               /* 随机数最大的数 */ 
	extern int length;        /* length of array */ 
	FILE *fp;                 /* file */
	extern char filename[20]; /* file's name */
	fp=fopen(filename,"w");   // open file
	if(test!=1){              // test=0,test=1 means test,test=2 means color
		printf("\n请输入你要生成的随机数数组的长度(不能超过200000):");
		length=judgeinput(); 
		while(length>MAXLEN){
			printf("\n请输入不超过200000的整数：");
			length=judgeinput();
		}
	}
	else if(test==1){
		printf("\n请输入你要测试的数据量(10000，50000或200000)：");
		length=judgeinput();
		while(length!=10000&&length!=50000&&length!=200000){
			printf("\n请输入10000，50000或200000：");
			length=judgeinput();
		}
	}
	*a=(int *)calloc(length,sizeof(int));
	if(!(*a)){
		printf("\n内存申请失败！\n\n");
		exit(1); 
	}
	else{
		fputs("random array:\n",fp);
		srand((unsigned)time(NULL)); // 按时间重新播种
		if(test!=2){
			printf("\n请输入你要生成的随机数数值的上限：");
			maxpos=judgeinput();
		}
		for(int i=0;i<length;i++){
			if(i!=0&&i%10==0)fputc('\n',fp);
			if(test!=2)*(*a+i)=rand()%maxpos+1;  // generate rand numbers 
			else *(*a+i)=rand()%3;
			fprintf(fp,"%d\t",*(*a+i));
		}
		printf("\n生成随机数数组成功！\n\n");
		fclose(fp);
	}
}

void traversefile(){          // 查询文件 
	FILE *fp;
	int num;                  /* get the array number */
	int count=1;              /* count the length */ 
	char word[15];            /* get "random array:" */
	extern char filename[20]; /* file's name */
	fp=fopen(filename,"r");
	printf("\n当前的文件内容为：\n\n");
	fgets(word,15,fp); // 文件流中的换行符长度需要计为2"\n" 
	printf("%s",word);
	while(!feof(fp)){
		fscanf(fp,"%d\t",&num);
		printf("%d\t",num);
		if(count%10==0)printf("\n"); 
		count++;	
	} 
	printf("\n\n");
} 

void getdata(int **a){ // 直接提取文件中的数据到数组 
	FILE *fp;
	extern int length;
	extern char filename[20];
	*a=(int *)calloc(MAXLEN,sizeof(int));
	fp=fopen(filename,"r");
	fseek(fp,15L,0);   // 移动光标，跳过开头的"random array" 
	for(int i=0;!feof(fp);i++){
		fscanf(fp,"%d\t",*a+i);
		length++;
	}
	//for(int i=MAXLEN-1;i>=length;i--)free(*a+i); // 不需要free吗 
	fclose(fp);
}
	
void insertSort(int *a,int n){ // 默认升序排序 ,考虑只有一个数的情况 
	int i,j,temp; 
	for(i=1;i<n;i++){          // 从第二个元素开始，认为在此元素之前的都是已经排好序的 
		temp=*(a+i);
		for(j=i-1;j>=0;j--){
			if(temp<*(a+j)){
				*(a+j+1)=*(a+j); // 大的往后放
				*(a+j)=temp;
			}
			else break;
		}	
	}
}

void MergeArray(int *a,int begin,int mid,int end,int *temp){
	int i,j,k; 
	extern int length;
	for(i=begin,j=mid+1,k=0;i<=mid&&j<=end;k++){
		if(*(a+i)<*(a+j)){
			*(temp+k)=*(a+i);
			i++; 
		}
		else{
			*(temp+k)=*(a+j);
			j++;
		}
	}
	if(i==mid+1){ // 处理剩下的 
		while(j<=end){
			*(temp+k)=*(a+j);
			k++;
			j++;
		}
	}
	else{
		while(i<=mid){
			*(temp+k)=*(a+i);
			k++;
			i++;
		}
	}
	//if(begin==0&&end==length-1){
		//for(i=0;i<=end;i++)*(a+i)=*(temp+i); // 这样是错的，temp是一级指针，不会保留原来的值 
	for(i=begin,j=0;j<k;j++,i++)*(a+i)=*(temp+j);
}

void MergeSort(int *a,int begin,int end,int *temp){
	int mid; /* mid location */
	temp=(int *)calloc(end+1,sizeof(int)); // end is the length
	if(begin>=end)return;                  // only one data 
	mid=(begin+end)/2;
	MergeSort(a,begin,mid,temp);
	MergeSort(a,mid+1,end,temp);
	MergeArray(a,begin,mid,end,temp);
}

void QuickSort_Recursion(int *a, int begin, int end){
	int location;  /* key's index */
	if(begin<end){ // 递归结束begin>=end 
		location=Partition(a,begin,end);
		QuickSort_Recursion(a,begin,location-1); //begin,key,end
		QuickSort_Recursion(a,location+1,end);
	}	
}

int Partition(int *a, int begin, int end){
	int key=*(a+begin); /* first data */
	while(begin<end){
		while(begin<end&&*(a+end)>=key)end--;
		*(a+begin)=*(a+end);
		while(begin<end&&*(a+begin)<=key)begin++;
		*(a+end)=*(a+begin);
	}
	*(a+begin)=key; // begin=end
	return begin; 
}

void CountSort(int *a, int size/* , int max*/){
	int *temp; /* 存放元素数量的数组 */
	int i,j;
	int max,min;
	max=min=*a;
	for(i=1;i<size;i++){
		if(*(a+i)>max)max=*(a+i);
		if(*(a+i)<min)min=*(a+i);
	}
	temp=(int *)calloc(max-min+1,sizeof(int)); // 初始值为0 
	for(i=0;i<size;i++){       // 计算出现次数 
		j=max-*(a+i);          // 差值，越大数越小
		temp[j]++;  
	}
	for(i=size-1,j=0;i>=0;){ // i是从后往前 
		while(*(temp+j)){    // 等于不等于要区别清楚！ 
			*(a+i)=max-j;
			i--;
			temp[j]--;
		}
		j++;		
	} 
}

void Kminmax(int *a,int begin,int end,int K,int Kmax,int Kmin){ // 采用快排思路 
	int location; 
	extern int length;
	if(begin<end){                       // 结束递归 
		location=Partition(a,begin,end); // location is index
		if(location==K-1){
			Kmin=a[location];
			printf("\n第%d小的数：%d\n",K,Kmin);
		}	
		if(location==length-K){
			Kmax=a[location];
			printf("\n第%d大的数：%d\n",K,Kmax);
		}
		if(location>K-1)Kminmax(a,begin,location-1,K,Kmax,Kmin);
		if(location>length-K)Kminmax(a,begin,location-1,K,Kmax,Kmin);
		if(location<K-1)Kminmax(a,location+1,end,K,Kmax,Kmin);
		if(location<length-K)Kminmax(a,location+1,end,K,Kmax,Kmin);
	}
}

int getnum(int num,int pos){
	int i,j;
	for(i=1,j=1;j<pos;j++,i*=10);
	return (num/i)%10;
}

void RadixCountSort(int *a,int size){
	int *temp[10];  /* 二维数组,0~9 */
	int maxpos=1;   /* 位数 */ 
	int pos;        /* 第几位上的数字 */ 
	int index;      /* 第几个数 */ 
	int i,j,k,m;
	for(i=0;i<10;i++){
		temp[i]=(int *)calloc(size+1,sizeof(int));  // 多一位来记录数据个数
		temp[i][0]=0; // 记录数据个数 
	} 
	for(i=1,m=*a;i<size;i++){     // 求最大值 
		if(*(a+i)>m)m=*(a+i);
	}
	for(i=m;i>=10;i/=10)maxpos++; // 求位数 
	for(i=1;i<=maxpos;i++){       // i是第几位，从个位开始
		for(j=0;j<size;j++){      // 分配数据 
			pos=getnum(*(a+j),i); 
			index=++temp[pos][0]; // 记录数据个数 
			temp[pos][index]=*(a+j); 
		}
		for(j=0,m=0;j<10;j++){        // 收集数据
			for(k=1;k<=temp[j][0];k++,m++){
				*(a+m)=temp[j][k];    // 排序 
			} 
			temp[j][0]=0;             // 复位  
		}
	} 
}

void ColorSort(int *a,int size){
	for(int i=0,j=0,k=size-1;i!=k;){
		if(*(a+i)==0&&i!=j){  
			*(a+i)=*(a+j);
			*(a+j)=0;
			j++;
		}
		if(*(a+i)==0&&i==j){
			j++;
			i++;
		}
		if(*(a+i)==2){
			*(a+i)=*(a+k);
			*(a+k)=2;
			k--;
		}
		if(*(a+i)==1)i++;
	}
}

void result(int *a,int n){
	printf("\nordered array：\n");
	for(int i=0;i<n;i++){
		if(i!=0&&i%10==0)printf("\n");
		printf("%d\t",*(a+i));
	}
	printf("\n\n");
}

void testmeans(int *a){
	int *temp=NULL;
	int max;
	extern int length;
	clock_t start, finish; /* caculate the time */
	double duration[5];    /* array of time,five means */
	for(int i=0;i<5;i++){
		switch(i){
    		case 0:
    			start=clock();
    			insertSort(a,length);
    			finish=clock();
    			printf("\n插入排序法的用时："); 
    			break;
    		case 1:
    			start=clock();
    			MergeSort(a,0,length-1,temp);
    			printf("\n归并排序法的用时：");
    			finish=clock();
    			break;
    		case 2:
    			start=clock();
    			QuickSort_Recursion(a,0,length-1);
    			printf("\n快速排序法(递归)的用时：");
    			finish=clock();
    			break;
    		case 3:
    			start=clock();
    			CountSort(a,length);
    			printf("\n计数排序法的用时：");
    			finish=clock();
    			break;
    		case 4:
    			start=clock();
    			RadixCountSort(a,length);
    			printf("\n基数计数排序法的用时：");
    			finish=clock();
    			break;
		}
		duration[i]=(double)(finish-start)/CLOCKS_PER_SEC;
		printf("%f seconds\n",*(duration+i)); 
	}
	printf("\n");
}

void testtimes(int *a){
	char c;                /* option */
	int num,maxpos;        /* num(数组个数),maxpos(上限) */ 
	int *temp=NULL;
	extern int length;
	clock_t start, finish; /* caculate the time */
	double *duration;      /* array of time,five means */
	printf("\n请输入要生成的长度为100的数组个数(测试个数至少为10000)："); 
	num=judgeinput();
	while(num<10000){
		printf("\n请输入大于等于10000的数：");
		num=judgeinput();
	}
	duration=(double *)calloc(num+1,sizeof(double));
	duration[0]=0; // 第一位不用 
	length=100;
	a=(int *)calloc(length,sizeof(int));
	if(!a){
		printf("\n内存申请失败！\n\n");
		exit(1); 
	}
	else{
		printf("\n请输入你要生成的随机数数值的上限：");
		maxpos=judgeinput();
		printf("\n请选择要测试的排序方法：\n");
		printf("--------------------------\n"); 
		printf("1.插入排序法\n");
		printf("2.归并排序法\n");
		printf("3.快速排序法(递归)\n");
		printf("4.计数排序法\n");
		printf("5.基数计数排序法\n");
		printf("--------------------------\n");
		printf("请输入你的选择(1~5)：");
		fflush(stdin);
		scanf("%c",&c);
		fflush(stdin);
		while(c<'1'||c>'5'){
			printf("\n你输入的数据有误（请输入1-5），请重新输入：");
			scanf("%c",&c);
			fflush(stdin);
		}
		for(int i=1;i<=num;i++){        // 次数 
			srand((unsigned)time(NULL));
			for(int j=0;j<length;j++){
				*(a+j)=rand()%maxpos+1; // 生成随机数组 
			}
			switch(c){
				case '1':
					start=clock();
    				insertSort(a,length);
    				finish=clock();
    				printf("\n第%d次插入排序法的用时：",i);
					break;
				case '2':
					start=clock();
    				MergeSort(a,0,length-1,temp);
    				printf("\n第%d次归并排序法的用时：",i);
    				finish=clock();
    				break;
    			case '3':
    				start=clock();
    				QuickSort_Recursion(a,0,length-1);
    				printf("\n第%d次快速排序法(递归)的用时：",i);
    				finish=clock();
    				break;
    			case '4':
    				start=clock();
    				CountSort(a,length);
    				printf("\n第%d次计数排序法的用时：",i);
    				finish=clock();
    				break;
    			case '5':
    				start=clock();
    				RadixCountSort(a,length);
    				printf("\n第%d次基数计数排序法的用时：",i);
    				finish=clock();
    				break;
				}
			duration[i]=(double)(finish-start)/CLOCKS_PER_SEC;
			printf("%f seconds\n",*(duration+i));
		}
	}
	printf("\n");
} 

