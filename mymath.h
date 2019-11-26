#ifndef MYMATH_H
#define MYMATH_H
#include <QList>
#include <math.h>
#include <qregularexpression.h>


class MyMath
{
public:
    MyMath();


    bool isPrime(int);

    QList <int> additiveZnGroup(int);

    QList <int> multiplicativeZnGroup(int);

    int gcd(int,int);

    void swap(int* ,int*);

    int mPow(int,int,int);

    QList <int> unsignedDivisors(int);

    bool listsEqual(QList<int>, QList<int>);

    QList <int> FindMultiplicationGenerator(int);

    QList <QList <int>> multiplicationSubGroups(int n);

    QList <int> findAdditiveGenerator(int n);

    QList <QList <int>> additiveSubGroups(int n);

    QList <int> getNumbers(QString arg);

    bool IsMultiplyOff(QList <int> list, int mod);

    bool IsAdditiveOff(QList <int> list, int mod);

    bool multiplicativeUnit(QList <int> list, int mod);

    bool additiveUnit(QList <int> list, int mod);

    bool multiplyInverse(QList <int> list, int mod);

    bool additiveInverse(QList <int> list, int mod);
};

#endif // MYMATH_H
