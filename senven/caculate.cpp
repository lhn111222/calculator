#include "caculate.h"
#include "ui_caculate.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include <cmath>

// 按钮文本数组 - 定义计算器按钮上的文本
static QString ch[12] = {"7", "8", "9", "x", "4", "5", "6", "-", "1", "2", "3", "+"};
static int num = 0;  // 全局索引计数器，用于顺序初始化按钮文本

// 构造函数 - 初始化计算器界面
Caculate::Caculate(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Caculate)
{
    ui->setupUi(this);

    // 创建并显示TT窗口
    pt = new TT(this);  // TT窗口作为当前窗口的子对象
    pt->show();

    // 设置主窗口大小
    resize(800, 600);

    // 主垂直布局 - 包含所有界面元素
    pvb = new QVBoxLayout(this);

    // 创建4个水平布局 - 每行按钮一个水平布局
    for (int i = 0; i < 4; i++) {
        phb[i] = new QHBoxLayout();  // 初始化水平布局
    }

    // 创建标签和输入框
    plb = new QLabel("标准", this);   // "标准"标签
    pe = new QLineEdit(this);         // 输入框，显示表达式和结果
    pe->setReadOnly(true);            // 设置为只读

    expression = "";  // 初始化表达式字符串

    // 初始化第一行按钮 (7,8,9,x)
    for (int i = 0; i < 4; i++) {
        pb[i] = new QPushButton(ch[num++], this);  // 创建按钮并设置文本
        pb[i]->setFixedSize(60, 40);               // 固定按钮大小
        phb[0]->addWidget(pb[i]);                  // 添加到第一行水平布局
        // 连接按钮点击信号到处理函数
        connect(pb[i], &QPushButton::clicked, this, &Caculate::handleButtonClick);
    }

    // 初始化第二行按钮 (4,5,6,-)
    for (int i = 0; i < 4; i++) {
        pb1[i] = new QPushButton(ch[num++], this);
        pb1[i]->setFixedSize(60, 40);
        phb[1]->addWidget(pb1[i]);
        connect(pb1[i], &QPushButton::clicked, this, &Caculate::handleButtonClick);
    }

    // 初始化第三行按钮 (0,(,),.)
    const char* row2Text[4] = {"0", "(", ")", "."};  // 按钮文本
    for (int i = 0; i < 4; i++) {
        pb2[i] = new QPushButton(row2Text[i], this);
        pb2[i]->setFixedSize(60, 40);
        phb[2]->addWidget(pb2[i]);
        connect(pb2[i], &QPushButton::clicked, this, &Caculate::handleButtonClick);
    }

    // 初始化第四行按钮 (C,=,/,%)
    const char* row3Text[4] = {"C", "=", "/", "%"};  // 按钮文本
    for (int i = 0; i < 4; i++) {
        pb3[i] = new QPushButton(row3Text[i], this);
        pb3[i]->setFixedSize(60, 40);
        phb[3]->addWidget(pb3[i]);

        // 特殊按钮连接不同的槽函数
        if (i == 0) {  // "C"按钮 - 清除
            connect(pb3[i], &QPushButton::clicked, this, &Caculate::clearDisplay);
        }
        else if (i == 1) {  // "="按钮 - 计算结果
            connect(pb3[i], &QPushButton::clicked, this, &Caculate::calculateExpression);
        }
        else {  // 其他按钮
            connect(pb3[i], &QPushButton::clicked, this, &Caculate::handleButtonClick);
        }
    }

    // 组合所有布局
    pvb->addWidget(plb);  // 添加标签
    pvb->addWidget(pe);   // 添加输入框
    for (int i = 0; i < 4; i++) {
        pvb->addLayout(phb[i]);  // 添加每行按钮的水平布局
    }
}


Caculate::~Caculate()
{
    delete ui;

}

// 处理按钮点击 - 将按钮文本添加到表达式
void Caculate::handleButtonClick()
{
    // 获取发送信号的按钮
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString text = button->text();

        // 特殊符号转换：将"x"转换为乘法符号"*"
        if (text == "x") text = "*";

        // 将按钮文本添加到表达式
        expression += text;
        // 在输入框中显示当前表达式
        pe->setText(expression);
    }
}

// 清除显示 - 重置表达式和输入框
void Caculate::clearDisplay()
{
    expression.clear();  // 清空表达式
    pe->clear();         // 清空输入框
}

// 计算表达式 - 对当前表达式求值
void Caculate::calculateExpression()
{
    // 如果表达式为空，直接返回
    if (expression.isEmpty()) return;

    try {
        // 计算表达式结果
        double result = evaluateExpression(expression);
        // 显示结果（最多10位有效数字）
        pe->setText(QString::number(result, 'g', 10));
        // 更新表达式为结果（用于连续计算）
        expression = QString::number(result, 'g', 10);
    } catch (const std::exception& e) {
        // 捕获并显示错误信息
        pe->setText("Error: " + QString(e.what()));
        expression.clear();  // 清空表达式
    }
}


double Caculate::evaluateExpression(const QString& expr)
{
    QStack<double> numbers;    // 存储操作数的栈
    QStack<QChar> operators;   // 存储运算符的栈
    QString numStr;            // 当前解析的数字字符串
    bool lastWasOperator = true; // 标记上一个字符是否是运算符（用于处理负数）

    // 定义运算符优先级（值越高优先级越高）
    QMap<QChar, int> precedence;
    precedence['+'] = 1;  // 加法优先级
    precedence['-'] = 1;  // 减法优先级
    precedence['*'] = 2;  // 乘法优先级
    precedence['/'] = 2;  // 除法优先级
    precedence['%'] = 2;  // 取模优先级

    // 遍历表达式中的每个字符
    for (int i = 0; i < expr.length(); i++) {
        QChar c = expr[i];

        // 处理数字和小数点
        if (c.isDigit() || c == '.') {
            numStr += c;  // 添加到当前数字字符串
            lastWasOperator = false;  // 标记当前字符不是运算符
        }
        // 处理左括号 '('
        else if (c == '(') {
            operators.push(c);  // 压入运算符栈
            lastWasOperator = true;  // 标记为运算符（因为括号后可能跟负号）
        }
        // 处理右括号 ')'
        else if (c == ')') {
            // 如果当前有数字字符串，先压入操作数栈
            if (!numStr.isEmpty()) {
                numbers.push(numStr.toDouble());
                numStr.clear();  // 清空数字字符串
            }

            // 计算括号内的表达式：直到遇到左括号
            while (!operators.isEmpty() && operators.top() != '(') {
                applyOperator(numbers, operators.pop());  // 应用运算符
            }

            // 弹出左括号
            if (!operators.isEmpty() && operators.top() == '(') {
                operators.pop();
            } else {
                throw std::runtime_error("Mismatched parentheses");  // 括号不匹配错误
            }
            lastWasOperator = false;  // 括号后不是运算符
        }
        // 处理负号（当负号出现在表达式开头或运算符后）
        else if (c == '-' && lastWasOperator) {
            numStr += c;  // 添加到数字字符串（作为负号）
        }
        // 处理其他运算符（+、-、*、/、%）
        else {
            // 如果当前有数字字符串，先压入操作数栈
            if (!numStr.isEmpty()) {
                numbers.push(numStr.toDouble());
                numStr.clear();  // 清空数字字符串
            }

            // 处理运算符优先级：弹出优先级更高或相等的运算符
            while (!operators.isEmpty() &&
                   operators.top() != '(' &&
                   precedence[operators.top()] >= precedence[c]) {
                applyOperator(numbers, operators.pop());  // 应用运算符
            }

            // 将当前运算符压入栈
            operators.push(c);
            lastWasOperator = true;  // 标记当前字符是运算符
        }
    }

    // 处理最后一个数字（如果存在）
    if (!numStr.isEmpty()) {
        numbers.push(numStr.toDouble());
    }

    // 应用栈中剩余的运算符
    while (!operators.isEmpty()) {
        if (operators.top() == '(') {
            throw std::runtime_error("Mismatched parentheses");  // 有未匹配的左括号
        }
        applyOperator(numbers, operators.pop());  // 应用运算符
    }

    // 检查最终结果：操作数栈应只剩一个元素
    if (numbers.size() != 1) {
        throw std::runtime_error("Invalid expression");  // 无效表达式
    }

    // 返回计算结果
    return numbers.pop();
}


// 应用运算符函数 - 从操作数栈弹出两个操作数，应用运算符，将结果压回栈

void Caculate::applyOperator(QStack<double>& numbers, QChar op)
{
    // 检查是否有足够的操作数
    if (numbers.size() < 2) {
        throw std::runtime_error("Not enough operands");  // 操作数不足
    }

    // 弹出右操作数和左操作数
    double right = numbers.pop();
    double left = numbers.pop();
    double result = 0.0;  // 计算结果

    // 根据运算符执行相应计算
    switch (op.unicode()) {
    case '+':
        result = left + right;
        break;
    case '-':
        result = left - right;
        break;
    case '*':
        result = left * right;
        break;
    case '/':
        // 检查除零错误
        if (right == 0.0) throw std::runtime_error("Division by zero");
        result = left / right;  // 除法
        break;
    case '%':
        // 检查模零错误
        if (right == 0.0) throw std::runtime_error("Modulo by zero");
        result = std::fmod(left, right);
        break;
    default:
        throw std::runtime_error("Unknown operator");  // 未知运算符
    }

    // 将计算结果压回操作数栈
    numbers.push(result);
}
