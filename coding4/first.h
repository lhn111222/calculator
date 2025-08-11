#ifndef FIRST
#define FIRST

#define MAX 100

// 栈数据结构
struct stack
{
	float date[MAX]; //静态分配，等同于，指定大小的分配
	int top;
};

void pushStack(struct stack *p,float date);
float popStack(struct stack *p);
int IsFull(struct stack *p);
int IsEmpty(struct stack *p);
int inputdate(struct stack *p);
void swapfun(struct stack *src,struct stack *dest);
void myprt(struct stack *p);

// 表达式计算部分
//void ceal(); 
int precedence(char op);
float applyOperator(float a, float b, char op);

#endif

