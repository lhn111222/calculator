#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
#include "first.h"
#include "second.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
    //2个结构体 一个存数字 一个存符号
    struct stack values, operators;
    memset(&values, 0, sizeof(values));
    memset(&operators, 0, sizeof(operators));

    char expr[MAX];
    
    while (1) {
        printf("请输入表达式（输入exit退出）：");
        fgets(expr, MAX, stdin); // 获取用户输入的表达式
        
        int len = strlen(expr);
        if (len > 0 && expr[len - 1] == '\n') {
            expr[len - 1] = '\0'; // 替换换行符
        }

        if (strcmp(expr, "exit") == 0) {
            break; // 如果输入的是"exit"，退出循环
        }

        // 括号匹配检查
        int count = 0;
        int j = 0;
        while (expr[j] != '\0') {
            if (expr[j] == '(') {
                count++;
            } else if (expr[j] == ')') {
                count--;
            }
            if (count < 0) {
                printf("错误：括号不匹配！\n");
                break;
            }
            j++;
        }

        if (count != 0) {
            printf("错误：括号不匹配！\n");
            continue;
        }

        int i = 0; // 当前字符下标
        float num = 0; // 用于构建多位整数
        char current_op, top_op; // 当前运算符 和 栈顶运算符(上一个)
        float a, b, result; // 运算的两个操作数 和 运算结果

        while (expr[i] != '\0') {
            if (expr[i] == ' ') {
                i++;
                continue;
            }

            // 处理负数情况
            if (expr[i] == '-' && (i == 0 || expr[i - 1] == '(' || expr[i - 1] == '+' || expr[i - 1] == '-' || expr[i - 1] == '*' || expr[i - 1] == '/')) {
                // 如果是负号，读取负数
                num = 0;
                i++; // 跳过负号
                while (expr[i] >= '0' && expr[i] <= '9') {
                    num = num * 10 + (expr[i] - '0');
                    i++;
                }
                // 如果遇到小数点，继续读取
                if (expr[i] == '.') {
                    i++;
                    float decimalPlace = 0.1;
                    while (expr[i] >= '0' && expr[i] <= '9') {
                        num = num + (expr[i] - '0') * decimalPlace;
                        decimalPlace = decimalPlace / 10;
                        i++;
                    }
                }
                num = -num; // 处理负数
                pushStack(&values, num);
                continue;
            }

            // 处理数字和浮点数
            if (expr[i] >= '0' && expr[i] <= '9') {
                num = 0;
                while (expr[i] >= '0' && expr[i] <= '9') {
                    num = num * 10 + (expr[i] - '0');
                    i++;
                }
                if (expr[i] == '.') //处理小数点 
                {
                    i++; // 跳过小数点
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
                    popStack(&operators); // 弹出左括号
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
                printf("错误：无效字符 '%c'\n", expr[i]);
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
            printf("结果是：%.1f\n", popStack(&values)); // 带小数点
        } else {
            printf("表达式错误\n");
        }
    }
    return 0;
}

