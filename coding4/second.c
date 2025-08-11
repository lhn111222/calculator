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

	printf("ÇëÊäÈë×Ö·û´®¡£\n");
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
				printf("²»Æ¥Åä!\n");
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
			printf("²»Æ¥Åä!\n");
			return 1;
		}
	
	}
	printf("Æ¥Åä!\n");
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
		return; // Õ»ÒÑÂú
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
		return 1; // ÂúÁË 
	}
	else
	{
		return 0; // Î´Âú
	}
}
int IsEmpty1(struct stack1 *p)
{
	if(p->top <= 0)
	{
		return 1; // ¿ÕÁË
	}
	else
	{
		return 0; // Ã»¿Õ
	}
}
