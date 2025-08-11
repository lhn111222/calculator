#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
#include "first.h"
#include "second.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
    //2���ṹ�� һ�������� һ�������
    struct stack values, operators;
    memset(&values, 0, sizeof(values));
    memset(&operators, 0, sizeof(operators));

    char expr[MAX];
    
    while (1) {
        printf("��������ʽ������exit�˳�����");
        fgets(expr, MAX, stdin); // ��ȡ�û�����ı��ʽ
        
        int len = strlen(expr);
        if (len > 0 && expr[len - 1] == '\n') {
            expr[len - 1] = '\0'; // �滻���з�
        }

        if (strcmp(expr, "exit") == 0) {
            break; // ����������"exit"���˳�ѭ��
        }

        // ����ƥ����
        int count = 0;
        int j = 0;
        while (expr[j] != '\0') {
            if (expr[j] == '(') {
                count++;
            } else if (expr[j] == ')') {
                count--;
            }
            if (count < 0) {
                printf("�������Ų�ƥ�䣡\n");
                break;
            }
            j++;
        }

        if (count != 0) {
            printf("�������Ų�ƥ�䣡\n");
            continue;
        }

        int i = 0; // ��ǰ�ַ��±�
        float num = 0; // ���ڹ�����λ����
        char current_op, top_op; // ��ǰ����� �� ջ�������(��һ��)
        float a, b, result; // ��������������� �� ������

        while (expr[i] != '\0') {
            if (expr[i] == ' ') {
                i++;
                continue;
            }

            // ���������
            if (expr[i] == '-' && (i == 0 || expr[i - 1] == '(' || expr[i - 1] == '+' || expr[i - 1] == '-' || expr[i - 1] == '*' || expr[i - 1] == '/')) {
                // ����Ǹ��ţ���ȡ����
                num = 0;
                i++; // ��������
                while (expr[i] >= '0' && expr[i] <= '9') {
                    num = num * 10 + (expr[i] - '0');
                    i++;
                }
                // �������С���㣬������ȡ
                if (expr[i] == '.') {
                    i++;
                    float decimalPlace = 0.1;
                    while (expr[i] >= '0' && expr[i] <= '9') {
                        num = num + (expr[i] - '0') * decimalPlace;
                        decimalPlace = decimalPlace / 10;
                        i++;
                    }
                }
                num = -num; // ������
                pushStack(&values, num);
                continue;
            }

            // �������ֺ͸�����
            if (expr[i] >= '0' && expr[i] <= '9') {
                num = 0;
                while (expr[i] >= '0' && expr[i] <= '9') {
                    num = num * 10 + (expr[i] - '0');
                    i++;
                }
                if (expr[i] == '.') //����С���� 
                {
                    i++; // ����С����
                    float decimalPlace = 0.1;
                    while (expr[i] >= '0' && expr[i] <= '9') {
                        num = num + (expr[i] - '0') * decimalPlace;
                        decimalPlace = decimalPlace / 10;
                        i++;
                    }
                }
                pushStack(&values, num);
                continue;
            }

            if (expr[i] == '(') {
                pushStack(&operators, expr[i]);
                i++;
            } else if (expr[i] == ')') {
                while (operators.top > 0 && operators.date[operators.top - 1] != '(') {
                    b = popStack(&values);
                    a = popStack(&values);
                    top_op = popStack(&operators);
                    result = applyOperator(a, b, top_op);
                    pushStack(&values, result);
                }
                if (operators.top > 0 && operators.date[operators.top - 1] == '(') {
                    popStack(&operators); // ����������
                }
                i++;
            } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
                current_op = expr[i];
                while (operators.top > 0) {
                    top_op = operators.date[operators.top - 1];
                    if (top_op == '(') {
                        break;
                    }
                    if (precedence(top_op) >= precedence(current_op)) {
                        b = popStack(&values);
                        a = popStack(&values);
                        top_op = popStack(&operators);
                        result = applyOperator(a, b, top_op);
                        pushStack(&values, result);
                    } else {
                        break;
                    }
                }
                pushStack(&operators, current_op);
                i++;
            } else {
                printf("������Ч�ַ� '%c'\n", expr[i]);
                return 0;
            }
        }

        while (operators.top > 0) {
            b = popStack(&values);
            a = popStack(&values);
            top_op = popStack(&operators);
            result = applyOperator(a, b, top_op);
            pushStack(&values, result);
        }

        if (values.top == 1) {
            printf("����ǣ�%.1f\n", popStack(&values)); // ��С����
        } else {
            printf("���ʽ����\n");
        }
    }
    return 0;
}

