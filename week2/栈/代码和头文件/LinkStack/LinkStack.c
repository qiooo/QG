#include "LinkStack.h" 
//��ջ

//��ʼ��ջ
Status initLStack(LinkStack *s){
	s->top=(LinkStackPtr)malloc(sizeof(StackNode)); /* not null */ 
	s->top->next=NULL;
	s->count=0;
	printf("\n��ʼ������ɹ���\n\n");
	return SUCCESS;
}

//�ж�ջ�Ƿ��ʼ�� 
Status isInitStack(LinkStack *s){
	if(s->count==-1){
		printf("\n��ǰջδ��ʼ�������ȳ�ʼ����\n\n");
		return ERROR;
	}	
	return SUCCESS;
}

//�ж�ջ�Ƿ�Ϊ��
Status isEmptyLStack(LinkStack *s){
	if(s->top){ /* not init */
		if(s->top->next==NULL){
			printf("\n��ǰջΪ�գ�����ջ��\n\n");
			return ERROR; 
		}
	}
	return SUCCESS;
}

//�õ�ջ��Ԫ��
Status getTopLStack(LinkStack *s,ElemType *e){
	LinkStackPtr p;
	p=(LinkStackPtr)malloc(sizeof(StackNode));
	p=s->top;
	e=&(p->data);
	printf("\n��ǰջ��Ԫ��Ϊ��%d\n\n",*e);
	return SUCCESS;
}

//���ջ
Status clearLStack(LinkStack *s){
	LinkStackPtr p;
	p=(LinkStackPtr)malloc(sizeof(StackNode));
	while(s->count){
		p=s->top;
		s->top=s->top->next;
		s->count--;
		free(p);
	}
	printf("\n���ջ�ɹ���\n\n");
	return SUCCESS;
}

//����ջ
Status destroyLStack(LinkStack *s){
	LinkStackPtr p;
	p=(LinkStackPtr)malloc(sizeof(StackNode));
	while(s->top){
		p=s->top;
		s->top=s->top->next;
		s->count--;
		free(p);
	}
	printf("\n����ջ�ɹ���\n\n");
	return SUCCESS;
}

//���ջ����
Status LStackLength(LinkStack *s,int *length){
	printf("\n��ǰջ�ĳ���Ϊ��%d\n\n",s->count);
	length=&(s->count);
	return SUCCESS;
}

//��ջ
Status pushLStack(LinkStack *s,ElemType data){
	LinkStackPtr p;
	p=(LinkStackPtr)malloc(sizeof(StackNode));
	p->data=data;
	p->next=s->top;
	s->top=p;
	s->count++;
	printf("\n��ջ�ɹ���\n\n");
	return SUCCESS;
}

//��ջ
Status popLStack(LinkStack *s,ElemType *data){
	LinkStackPtr p;
	p=(LinkStackPtr)malloc(sizeof(StackNode));
	p=s->top;
	*data=p->data;
	s->top=s->top->next;
	s->count--;
	free(p);
	printf("\n��ջ�ɹ�����ջ������Ϊ��%d\n\n",*data);
	return SUCCESS;
}


