#include "LQueue.h" 
Status IsInitQueue(LQueue *Q){
	if(Q->length==-1){
		printf("\n��ǰ����δ��ʼ�������ȳ�ʼ�����У�\n\n");
		return FALSE;
	}
	else return TRUE;
}
/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : ��ʼ������
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void InitLQueue(LQueue *Q){
	Q->rear=(Node *)malloc(sizeof(Node));
	Q->front=Q->rear;
	Q->length=0;
	Q->front->next=NULL;
	printf("\n��ʼ�����гɹ���\n\n");
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : ���ٶ���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q){
	Node *p; /* actionable node */
	while(Q->front->next){
		p=Q->front->next;
		Q->front->next=p->next;
		Q->length--;
		free(p);
	}
	free(Q->front);
	Q->length=-1; /* means not init */
	Q=NULL;
	printf("\n���ٶ��гɹ���\n\n");
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q){
	if(Q->front==Q->rear)return TRUE;
	else return FALSE;
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : �鿴��ͷԪ��
 *    @param         Q e ����ָ��Q,��������ָ��e
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
Status GetHeadLQueue(LQueue *Q, void *e){
	e=(void *)malloc(21);
	memcpy(e,Q->front->next->data,21); 
	printf("\n��ǰ��ͷԪ��Ϊ��");
	LPrint(Q->front->next); 
	printf("\n\n");
	return TRUE;
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : ȷ�����г���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status LengthLQueue(LQueue *Q){
	printf("\n��ǰ���еĳ���Ϊ��%d\n\n",Q->length);
	return TRUE;
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : ��Ӳ���
 *    @param         Q ����ָ��Q,�������ָ��data
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ�Ϊ��
 */
Status EnLQueue(LQueue *Q, void *data){
	Node *p; /* new pointer */
	p=(Node *)malloc(sizeof(Node));
	p->data=(void *)malloc(21); /* why is 20? and why should allocate memory to p->data */
	memcpy(p->data,data,21);
	Q->rear->next=p;
	Q->rear=p;
	Q->length++;
	p->next=NULL;
	printf("\n��ӳɹ���\n\n");
	return TRUE;
}

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q){
	Node *p;
	p=Q->front->next;
	Q->front->next=p->next;
	if(!Q->front->next)Q->rear=Q->front; /* the situation of only one data */
	Q->length--;
	free(p);
	printf("\n���ӳɹ���\n\n");
	return TRUE;
}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : ��ն���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q){
	Node *p;
	while(Q->front->next){
		p=Q->front->next;
		Q->front->next=p->next;
		Q->length--;
		free(p);
	}
	Q->rear=Q->front;
	printf("\n��ն��гɹ���\n\n");
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : ������������
 *    @param         Q ����ָ��Q����������ָ��foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q/*, void (*foo)(Node *q)*/){
	Node *p;
	printf("\n��ǰ����Ϊ��Ԫ��Ϊ��\n");
	for(p=Q->front->next;p;p=p->next){
		LPrint(p);
	}
	printf("\n\n");
	return TRUE;
}

/**
 *  @name        : void LPrint(void *q)
 *    @description : ��������
 *    @param         q ָ��q
 
 *  @notice      : None
 */
void LPrint(Node *q){
	switch(q->nodetype){
		case '1':
			printf("%d\t",*(int *)q->data);
			break;
		case '2':
			printf("%f\t",*(float *)q->data);
			break;
		case '3':
			printf("%lf\t",*(double *)q->data);
			break;
		case '4':
			printf("\'%c\'\t",*(char *)q->data);
			break;
		case '5':
			printf("\"%s\"\t",(char *)q->data);
			break;
	}
}




