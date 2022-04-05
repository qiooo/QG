#include "LQueue.h" 
Status IsInitQueue(LQueue *Q){
	if(Q->length==-1){
		printf("\n当前队列未初始化！请先初始化队列！\n\n");
		return FALSE;
	}
	else return TRUE;
}
/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void InitLQueue(LQueue *Q){
	Q->rear=(Node *)malloc(sizeof(Node));
	Q->front=Q->rear;
	Q->length=0;
	Q->front->next=NULL;
	printf("\n初始化队列成功！\n\n");
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
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
	printf("\n销毁队列成功！\n\n");
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q){
	if(Q->front==Q->rear)return TRUE;
	else return FALSE;
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q e 队列指针Q,返回数据指针e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadLQueue(LQueue *Q, void *e){
	e=(void *)malloc(21);
	memcpy(e,Q->front->next->data,21); 
	printf("\n当前队头元素为：");
	LPrint(Q->front->next); 
	printf("\n\n");
	return TRUE;
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status LengthLQueue(LQueue *Q){
	printf("\n当前队列的长度为：%d\n\n",Q->length);
	return TRUE;
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否为空
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
	printf("\n入队成功！\n\n");
	return TRUE;
}

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q){
	Node *p;
	p=Q->front->next;
	Q->front->next=p->next;
	if(!Q->front->next)Q->rear=Q->front; /* the situation of only one data */
	Q->length--;
	free(p);
	printf("\n出队成功！\n\n");
	return TRUE;
}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : 清空队列
 *    @param         Q 队列指针Q
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
	printf("\n清空队列成功！\n\n");
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q/*, void (*foo)(Node *q)*/){
	Node *p;
	printf("\n当前队列为各元素为：\n");
	for(p=Q->front->next;p;p=p->next){
		LPrint(p);
	}
	printf("\n\n");
	return TRUE;
}

/**
 *  @name        : void LPrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q
 
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




