#ifndef CACULATE_H
#define CACULATE_H

#include "tt.h"
#include <QWidget>
#include <QStack>
#include <QMap>
#include <cmath>
#include <stdexcept>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QString>

// 前向声明
namespace Ui {
class Caculate;
}

class Caculate : public QWidget
{
    Q_OBJECT

public:
    explicit Caculate(QWidget *parent = nullptr);
    ~Caculate();

private slots:
    void handleButtonClick();
    void calculateExpression();
    void clearDisplay();

private:
    Ui::Caculate *ui;
    TT *pt;

    // 布局和控件
    QVBoxLayout *pvb;
    QHBoxLayout *phb[4];
    QLabel *plb;
    QLineEdit *pe;
    QPushButton *pb[4];
    QPushButton *pb1[4];
    QPushButton *pb2[4];
    QPushButton *pb3[4];

    QString expression;

    double evaluateExpression(const QString& expr);
    void applyOperator(QStack<double>& numbers, QChar op);
};

#endif // CACULATE_H
