#ifndef SECOND
#define SECOND

#define MAX 100
// 栈数据结构
struct stack1
{
	char date[MAX]; //静态分配，等同于，指定大小的分配
	int top;
};
void pushStack1(struct stack1 *p,char date);
char popStack1(struct stack1 *p);
int IsFull1(struct stack1 *p);
int IsEmpty1(struct stack1 *p);
int inputdate1(struct stack1 *p);
void swapfun1(struct stack1 *src,struct stack1 *dest);
void myprt1(struct stack1 *p);
int mypop1(struct stack1 *p);

#endif

