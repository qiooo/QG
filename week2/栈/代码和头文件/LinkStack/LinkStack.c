#include "LinkStack.h" 
//链栈

//初始化栈
Status initLStack(LinkStack *s){
	s->top=(LinkStackPtr)malloc(sizeof(StackNode)); /* not null */ 
	s->top->next=NULL;
	s->count=0;
	printf("\n初始化链表成功！\n\n");
	return SUCCESS;
}

//判断栈是否初始化 
Status isInitStack(LinkStack *s){
	if(s->count==-1){
		printf("\n当前栈未初始化，请先初始化！\n\n");
		return ERROR;
	}	
	return SUCCESS;
}

//判断栈是否为空
Status isEmptyLStack(LinkStack *s){
	if(s->top){ /* not init */
		if(s->top->next==NULL){
			printf("\n当前栈为空，请入栈！\n\n");
			return ERROR; 
		}
	}
	return SUCCESS;
}

//得到栈顶元素
Status getTopLStack(LinkStack *s,ElemType *e){
	LinkStackPtr p;
	p=(LinkStackPtr)malloc(sizeof(StackNode));
	p=s->top;
	e=&(p->data);
	printf("\n当前栈顶元素为：%d\n\n",*e);
	return SUCCESS;
}

//清空栈
Status clearLStack(LinkStack *s){
	LinkStackPtr p;
	p=(LinkStackPtr)malloc(sizeof(StackNode));
	while(s->count){
		p=s->top;
		s->top=s->top->next;
		s->count--;
		free(p);
	}
	printf("\n清空栈成功！\n\n");
	return SUCCESS;
}

//销毁栈
Status destroyLStack(LinkStack *s){
	LinkStackPtr p;
	p=(LinkStackPtr)malloc(sizeof(StackNode));
	while(s->top){
		p=s->top;
		s->top=s->top->next;
		s->count--;
		free(p);
	}
	printf("\n销毁栈成功！\n\n");
	return SUCCESS;
}

//检测栈长度
Status LStackLength(LinkStack *s,int *length){
	printf("\n当前栈的长度为：%d\n\n",s->count);
	length=&(s->count);
	return SUCCESS;
}

//入栈
Status pushLStack(LinkStack *s,ElemType data){
	LinkStackPtr p;
	p=(LinkStackPtr)malloc(sizeof(StackNode));
	p->data=data;
	p->next=s->top;
	s->top=p;
	s->count++;
	printf("\n入栈成功！\n\n");
	return SUCCESS;
}

//出栈
Status popLStack(LinkStack *s,ElemType *data){
	LinkStackPtr p;
	p=(LinkStackPtr)malloc(sizeof(StackNode));
	p=s->top;
	*data=p->data;
	s->top=s->top->next;
	s->count--;
	free(p);
	printf("\n出栈成功！出栈的数据为：%d\n\n",*data);
	return SUCCESS;
}


