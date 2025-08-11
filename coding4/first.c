#include <stdio.h>
#include <string.h>
#include "first.h"

// 表达式计算部分

int precedence(char op) //优先级 
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}


float applyOperator(float a, float b, char op) // */+-运算 
{
    if (op == '+') 
	{
        return a + b;
    } 
    else if (op == '-') 
	{
        return a - b;
    } 
    else if (op == '*') 
	{
        return a * b;
    } 
    else if (op == '/') 
	{	
		if(b ==0)
		{
			printf("不能做分母\n");
			return 0; 
		}
		else
		{ 
        	return a / b;
		}
    } 
    else 
	{
        return 0;  // 无效操作符
    }
}


int main_first()
{
	struct stack st,st1;
	struct stack stbak,st1bak;
	memset(&st,0x00,sizeof(st));
	memset(&st1,0x00,sizeof(st1));

	memset(&stbak,0x00,sizeof(stbak));
	memset(&st1bak,0x00,sizeof(st1bak));

	inputdate(&st);
	inputdate(&st1);
	
	swapfun(&st,&stbak);
	swapfun(&st1,&st1bak);
	swapfun(&stbak,&st1);
	swapfun(&st1bak,&st);

	myprt(&st);
	myprt(&st1);

}

void myprt(struct stack *p)
{
	while(p->top)
	{
		printf("%d\t",popStack(p));
	}
	printf("\n");

}
void swapfun(struct stack *src,struct stack *dest)
{
	float tmp;  // 改为浮动数值
	while(src->top)
	{
		tmp = popStack(src);
		pushStack(dest,tmp);	
	}
}

int inputdate(struct stack *p)
{
	float date;  
	while(1)
	{
		scanf("%f",&date);  // 读取浮动值
		if(date == 0)
		{
			return 0;		
		}
		pushStack(p,date);	
	}
	return 1;
}
/*int main()
{
	struct stack st,st1;
	printf("%ld\n",sizeof(st));
	// 栈的初始化
	int i;
	for(i=0;i<100;i++)
	{
		st.date[i]=0;
	}
	st.top = 0;

	// 初始化方法2
	memset(&st,0x00,sizeof(st));
	memset(&st1,0x00,sizeof(st1));
	
	// 压栈操作
	for(i=0;i<5;i++)
		pushStack(&st); // struct stack *p = &st;
//	pushStack(&st); // struct stack *p = &st;
	// 栈顶元素输出
	printf("%d\t",st.date[st.top-1]);
	printf("%d\n",st.top);

	// 弹栈操作
	for(i=0;i<5;i++)
	{
		int tmp = popStack(&st);
		printf("%d\t",tmp);
	}
	printf("\n");
	// 栈顶元素输出
	printf("%d\t",st.date[st.top-1]);
	printf("%d\n",st.top);
	return 0;
}*/

void pushStack(struct stack *p,float date)
{
	if(IsFull(p))
	{
		return; // 栈已满
	}
	p->date[p->top]=date; // st.date[st.top]=da;
	p->top++;

}

float popStack(struct stack *p)
{
	if(IsEmpty(p))
	{
		return 0;
	}
	float tmp = p->date[--p->top];
	return tmp;
}

int IsFull(struct stack *p)
{
	if(p->top >= MAX)
	{
		return 1; // 满了 
	}
	else
	{
		return 0; // 未满
	}
}
int IsEmpty(struct stack *p)
{
	if(p->top <= 0)
	{
		return 1; // 空了
	}
	else
	{
		return 0; // 没空
	}
}
