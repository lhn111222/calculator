#include <stdio.h>
#include <string.h>
#include "second.h"
int main_second()
{
	struct stack1 st,st1;
	memset(&st,0x00,sizeof(st));
	memset(&st1,0x00,sizeof(st1));

	char buf[200];
	memset(buf,0x00,sizeof(buf));

	printf("�������ַ�����\n");
	scanf("%s",buf);

	int i=0;
	while(buf[i]!='\0')
	{
		if(buf[i]!=')')
		{
			pushStack1(&st,buf[i]);
		}
		else
		{
			int tmp = mypop1(&st);
			if(tmp == 1)
			{
				printf("��ƥ��!\n");
				return 1;
			}		
		}
		i++;
	}

	while(st.top)
	{
		char ch = popStack1(&st);
		if(ch == '(')
		{
			printf("��ƥ��!\n");
			return 1;
		}
	
	}
	printf("ƥ��!\n");
	return 0;
}
int mypop1(struct stack1 *p)
{
	char ch;
	while(p->top)
	{
		ch = popStack(p);
		if(ch=='(')
		{
			return 0;
		}
	
	}	
	return 1;
}

void myprt1(struct stack1 *p)
{
	while(p->top)
	{
		printf("%c\t",popStack(p));
	}
	printf("\n");

}
void swapfun1(struct stack1 *src,struct stack1 *dest)
{
	char tmp;
	while(src->top)
	{
		tmp = popStack(src);
		pushStack(dest,tmp);	
	}
}

int inputdate1(struct stack1 *p)
{
	char date;
	while(1)
	{
		scanf("%c",&date);
		if(date == '0')
		{
			return 0;		
		}
		pushStack(p,date);	
	}
	return 1;
}

void pushStack1(struct stack1 *p,char date)
{
	if(IsFull(p))
	{
		return; // ջ����
	}
	p->date[p->top]=date; // st.date[st.top]=da;
	p->top++;

}

char popStack1(struct stack1 *p)
{
	if(IsEmpty(p))
	{
		return 0;
	}
	char tmp = p->date[--p->top];
	return tmp;
}

int IsFull1(struct stack1 *p)
{
	if(p->top >= MAX)
	{
		return 1; // ���� 
	}
	else
	{
		return 0; // δ��
	}
}
int IsEmpty1(struct stack1 *p)
{
	if(p->top <= 0)
	{
		return 1; // ����
	}
	else
	{
		return 0; // û��
	}
}
