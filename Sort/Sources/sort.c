#include "sort.h"
void Initfile(){              // create a file
	FILE *fp;
	extern char filename[20]; /* file's name */
	printf("\n��������Ҫ������txt�ļ����ļ�����������20������ȡǰ20���֣���");
	scanf("%s",filename);
	if((fp=fopen(filename,"w"))==NULL){
		printf("\n�����ļ�ʧ�ܣ�\n\n");
		exit(0); //close all the file and exit the system
	} 
	else printf("\n�����ļ��ɹ���\n\n");
	fclose(fp); // close the file
}

int openfile(){               // if the filename has already existed
	FILE *fp;                 /* file */
	extern char filename[20]; /* file's name */
	printf("\n��������Ҫ�������ļ�����");
	scanf("%s",filename);
	if(!(fp=fopen(filename,"r"))){
		printf("\n���ļ������ڣ����ȴ����ļ���\n\n");
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
		printf("\n��ǰ���ļ�����Ϊ�գ�����������������飡\n\n");
		return 0;
	}
}

void generate(int **a,int test){       /* secondary pointer */ 
	int judgeinput();
	int maxpos;               /* ����������� */ 
	extern int length;        /* length of array */ 
	FILE *fp;                 /* file */
	extern char filename[20]; /* file's name */
	fp=fopen(filename,"w");   // open file
	if(test!=1){              // test=0,test=1 means test,test=2 means color
		printf("\n��������Ҫ���ɵ����������ĳ���(���ܳ���200000):");
		length=judgeinput(); 
		while(length>MAXLEN){
			printf("\n�����벻����200000��������");
			length=judgeinput();
		}
	}
	else if(test==1){
		printf("\n��������Ҫ���Ե�������(10000��50000��200000)��");
		length=judgeinput();
		while(length!=10000&&length!=50000&&length!=200000){
			printf("\n������10000��50000��200000��");
			length=judgeinput();
		}
	}
	*a=(int *)calloc(length,sizeof(int));
	if(!(*a)){
		printf("\n�ڴ�����ʧ�ܣ�\n\n");
		exit(1); 
	}
	else{
		fputs("random array:\n",fp);
		srand((unsigned)time(NULL)); // ��ʱ�����²���
		if(test!=2){
			printf("\n��������Ҫ���ɵ��������ֵ�����ޣ�");
			maxpos=judgeinput();
		}
		for(int i=0;i<length;i++){
			if(i!=0&&i%10==0)fputc('\n',fp);
			if(test!=2)*(*a+i)=rand()%maxpos+1;  // generate rand numbers 
			else *(*a+i)=rand()%3;
			fprintf(fp,"%d\t",*(*a+i));
		}
		printf("\n�������������ɹ���\n\n");
		fclose(fp);
	}
}

void traversefile(){          // ��ѯ�ļ� 
	FILE *fp;
	int num;                  /* get the array number */
	int count=1;              /* count the length */ 
	char word[15];            /* get "random array:" */
	extern char filename[20]; /* file's name */
	fp=fopen(filename,"r");
	printf("\n��ǰ���ļ�����Ϊ��\n\n");
	fgets(word,15,fp); // �ļ����еĻ��з�������Ҫ��Ϊ2"\n" 
	printf("%s",word);
	while(!feof(fp)){
		fscanf(fp,"%d\t",&num);
		printf("%d\t",num);
		if(count%10==0)printf("\n"); 
		count++;	
	} 
	printf("\n\n");
} 

void getdata(int **a){ // ֱ����ȡ�ļ��е����ݵ����� 
	FILE *fp;
	extern int length;
	extern char filename[20];
	*a=(int *)calloc(MAXLEN,sizeof(int));
	fp=fopen(filename,"r");
	fseek(fp,15L,0);   // �ƶ���꣬������ͷ��"random array" 
	for(int i=0;!feof(fp);i++){
		fscanf(fp,"%d\t",*a+i);
		length++;
	}
	//for(int i=MAXLEN-1;i>=length;i--)free(*a+i); // ����Ҫfree�� 
	fclose(fp);
}
	
void insertSort(int *a,int n){ // Ĭ���������� ,����ֻ��һ��������� 
	int i,j,temp; 
	for(i=1;i<n;i++){          // �ӵڶ���Ԫ�ؿ�ʼ����Ϊ�ڴ�Ԫ��֮ǰ�Ķ����Ѿ��ź���� 
		temp=*(a+i);
		for(j=i-1;j>=0;j--){
			if(temp<*(a+j)){
				*(a+j+1)=*(a+j); // ��������
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
	if(i==mid+1){ // ����ʣ�µ� 
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
		//for(i=0;i<=end;i++)*(a+i)=*(temp+i); // �����Ǵ�ģ�temp��һ��ָ�룬���ᱣ��ԭ����ֵ 
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
	if(begin<end){ // �ݹ����begin>=end 
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
	int *temp; /* ���Ԫ������������ */
	int i,j;
	int max,min;
	max=min=*a;
	for(i=1;i<size;i++){
		if(*(a+i)>max)max=*(a+i);
		if(*(a+i)<min)min=*(a+i);
	}
	temp=(int *)calloc(max-min+1,sizeof(int)); // ��ʼֵΪ0 
	for(i=0;i<size;i++){       // ������ִ��� 
		j=max-*(a+i);          // ��ֵ��Խ����ԽС
		temp[j]++;  
	}
	for(i=size-1,j=0;i>=0;){ // i�ǴӺ���ǰ 
		while(*(temp+j)){    // ���ڲ�����Ҫ��������� 
			*(a+i)=max-j;
			i--;
			temp[j]--;
		}
		j++;		
	} 
}

void Kminmax(int *a,int begin,int end,int K,int Kmax,int Kmin){ // ���ÿ���˼· 
	int location; 
	extern int length;
	if(begin<end){                       // �����ݹ� 
		location=Partition(a,begin,end); // location is index
		if(location==K-1){
			Kmin=a[location];
			printf("\n��%dС������%d\n",K,Kmin);
		}	
		if(location==length-K){
			Kmax=a[location];
			printf("\n��%d�������%d\n",K,Kmax);
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
	int *temp[10];  /* ��ά����,0~9 */
	int maxpos=1;   /* λ�� */ 
	int pos;        /* �ڼ�λ�ϵ����� */ 
	int index;      /* �ڼ����� */ 
	int i,j,k,m;
	for(i=0;i<10;i++){
		temp[i]=(int *)calloc(size+1,sizeof(int));  // ��һλ����¼���ݸ���
		temp[i][0]=0; // ��¼���ݸ��� 
	} 
	for(i=1,m=*a;i<size;i++){     // �����ֵ 
		if(*(a+i)>m)m=*(a+i);
	}
	for(i=m;i>=10;i/=10)maxpos++; // ��λ�� 
	for(i=1;i<=maxpos;i++){       // i�ǵڼ�λ���Ӹ�λ��ʼ
		for(j=0;j<size;j++){      // �������� 
			pos=getnum(*(a+j),i); 
			index=++temp[pos][0]; // ��¼���ݸ��� 
			temp[pos][index]=*(a+j); 
		}
		for(j=0,m=0;j<10;j++){        // �ռ�����
			for(k=1;k<=temp[j][0];k++,m++){
				*(a+m)=temp[j][k];    // ���� 
			} 
			temp[j][0]=0;             // ��λ  
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
	printf("\nordered array��\n");
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
    			printf("\n�������򷨵���ʱ��"); 
    			break;
    		case 1:
    			start=clock();
    			MergeSort(a,0,length-1,temp);
    			printf("\n�鲢���򷨵���ʱ��");
    			finish=clock();
    			break;
    		case 2:
    			start=clock();
    			QuickSort_Recursion(a,0,length-1);
    			printf("\n��������(�ݹ�)����ʱ��");
    			finish=clock();
    			break;
    		case 3:
    			start=clock();
    			CountSort(a,length);
    			printf("\n�������򷨵���ʱ��");
    			finish=clock();
    			break;
    		case 4:
    			start=clock();
    			RadixCountSort(a,length);
    			printf("\n�����������򷨵���ʱ��");
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
	int num,maxpos;        /* num(�������),maxpos(����) */ 
	int *temp=NULL;
	extern int length;
	clock_t start, finish; /* caculate the time */
	double *duration;      /* array of time,five means */
	printf("\n������Ҫ���ɵĳ���Ϊ100���������(���Ը�������Ϊ10000)��"); 
	num=judgeinput();
	while(num<10000){
		printf("\n��������ڵ���10000������");
		num=judgeinput();
	}
	duration=(double *)calloc(num+1,sizeof(double));
	duration[0]=0; // ��һλ���� 
	length=100;
	a=(int *)calloc(length,sizeof(int));
	if(!a){
		printf("\n�ڴ�����ʧ�ܣ�\n\n");
		exit(1); 
	}
	else{
		printf("\n��������Ҫ���ɵ��������ֵ�����ޣ�");
		maxpos=judgeinput();
		printf("\n��ѡ��Ҫ���Ե����򷽷���\n");
		printf("--------------------------\n"); 
		printf("1.��������\n");
		printf("2.�鲢����\n");
		printf("3.��������(�ݹ�)\n");
		printf("4.��������\n");
		printf("5.������������\n");
		printf("--------------------------\n");
		printf("���������ѡ��(1~5)��");
		fflush(stdin);
		scanf("%c",&c);
		fflush(stdin);
		while(c<'1'||c>'5'){
			printf("\n���������������������1-5�������������룺");
			scanf("%c",&c);
			fflush(stdin);
		}
		for(int i=1;i<=num;i++){        // ���� 
			srand((unsigned)time(NULL));
			for(int j=0;j<length;j++){
				*(a+j)=rand()%maxpos+1; // ����������� 
			}
			switch(c){
				case '1':
					start=clock();
    				insertSort(a,length);
    				finish=clock();
    				printf("\n��%d�β������򷨵���ʱ��",i);
					break;
				case '2':
					start=clock();
    				MergeSort(a,0,length-1,temp);
    				printf("\n��%d�ι鲢���򷨵���ʱ��",i);
    				finish=clock();
    				break;
    			case '3':
    				start=clock();
    				QuickSort_Recursion(a,0,length-1);
    				printf("\n��%d�ο�������(�ݹ�)����ʱ��",i);
    				finish=clock();
    				break;
    			case '4':
    				start=clock();
    				CountSort(a,length);
    				printf("\n��%d�μ������򷨵���ʱ��",i);
    				finish=clock();
    				break;
    			case '5':
    				start=clock();
    				RadixCountSort(a,length);
    				printf("\n��%d�λ����������򷨵���ʱ��",i);
    				finish=clock();
    				break;
				}
			duration[i]=(double)(finish-start)/CLOCKS_PER_SEC;
			printf("%f seconds\n",*(duration+i));
		}
	}
	printf("\n");
} 

