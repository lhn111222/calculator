#ifndef FIRST
#define FIRST

#define MAX 100

// ջ���ݽṹ
struct stack
{
	float date[MAX]; //��̬���䣬��ͬ�ڣ�ָ����С�ķ���
	int top;
};

void pushStack(struct stack *p,float date);
float popStack(struct stack *p);
int IsFull(struct stack *p);
int IsEmpty(struct stack *p);
int inputdate(struct stack *p);
void swapfun(struct stack *src,struct stack *dest);
void myprt(struct stack *p);

// ���ʽ���㲿��
//void ceal(); 
int precedence(char op);
float applyOperator(float a, float b, char op);

#endif

