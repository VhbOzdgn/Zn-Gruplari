#include "mymath.h"


MyMath::MyMath()
{

}

bool MyMath::isPrime(int arg)
{
    if(arg < 2){
        return false;
    }
    int testLimit = (int)sqrt(arg);
    for (int i = 2; i <= testLimit; i++) {
        if(arg % i == 0){
            return false;
        }

    }
    return true;
}






QList<int> MyMath::additiveZnGroup(int n)
{
    if(n <= 0)
         throw "Invalid argument!";

    QList <int> list;


    for (int i = 0; i < n; i++) {
        list.push_back(i);
    }
    return list;
}








QList<int> MyMath::multiplicativeZnGroup(int n)
{
    if(n <= 1)
         throw "Invalid argument!";

    QList <int> newList;
    for (int i = 1; i < n; i++) {
        if(gcd(n, i) == 1){
            newList.push_back(i);
        }
    }
    return newList;
}













int MyMath::gcd(int number1, int number2)
{
    if(number1 == 0 || number2 == 0){
        throw "Cannot be calculated for zero!";
    }


    if(number1 < number2){
        swap(&number1,&number2);
    }
    int remainder;
    while(true){
        remainder = (number1%number2);
        if(remainder == 0){
            return number2;
        }
        number1 = number2;
        number2 = remainder;
    }

}










void MyMath::swap(int *number1, int *number2)
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}








int MyMath::mPow(int number, int power, int module)
{
   if(number == 0 && power == 0)
        throw "Zero zero force can not be calculated!";

   else if(power == 0)
       return 1;

    while(number < 0){
        number += module;
    }
    number %= module;
    long long result = number;
    for(int i = 1; i < power; i++){
        result *= number;
        result %= module;
    }
    return (int)result;
}









QList<int> MyMath::unsignedDivisors(int arg)
{
    if(arg < 1){
        throw "Invalid argument!";
    }
    QList <int> list;
    for (int i = 1; i <= arg; i++) {
        if(arg % i == 0){
            list.push_back(i);
        }
    }
    return list;
}













bool MyMath::listsEqual(QList<int> list1, QList<int> list2)
{
    if(list1.isEmpty() || list2.isEmpty()){
        throw "List or lists are empty";
    }

    if(list1.size() != list2.size()){
        return false;
    }

    qSort(list1.begin(),list1.end());
    qSort(list2.begin(),list2.end());

    for (int i = 0; i < list1.size(); i++) {
        if(list1[i] != list2[i]){
            return false;
        }
    }

    return true;
}








QList<int> MyMath::FindMultiplicationGenerator(int n)
{
    QList <int> multiplicativeZn = multiplicativeZnGroup(n);

    QList <int> generators;

    for (int i = 1; i < multiplicativeZn.size(); i++) {
        QList <int> testList;
        for (int j = 1;; j++) {
            testList.push_back(mPow(multiplicativeZn[i],j,n));
            if(mPow(multiplicativeZn[i],j,n) == 1){
                break;
            }
        }


      qSort(testList.begin(),testList.end());
      if(listsEqual(multiplicativeZn,testList)){
         generators.push_back(multiplicativeZn[i]);
         for (int j = 2; j < multiplicativeZn.size(); j++) {
             if(gcd(multiplicativeZn.size(),j) == 1){
                generators.push_back(mPow(multiplicativeZn[i],j,n));
             }
          }
                qSort(generators.begin(),generators.end());
                return generators;
       }


        else{
            continue;
        }
    }
    return generators;

}






QList<QList<int> > MyMath::multiplicationSubGroups(int n)
{
    QList <QList <int>> subGroups;
    QList <int> subGroup;
    if(FindMultiplicationGenerator(n).size() < 1){
        subGroup.push_back(1);
        subGroups.push_back(subGroup);
        subGroups.push_back(multiplicativeZnGroup(n));
        return subGroups;
    }
    QList <int> dividingList = unsignedDivisors(multiplicativeZnGroup(n).size());
    int generator = FindMultiplicationGenerator(n)[0];
    for (int i = 0; i < dividingList.size(); i++) {
        int value = multiplicativeZnGroup(n).size() / dividingList[i];
        int replacement = value;
        while (true) {
            subGroup.push_back(mPow(generator,value,n));
            if(mPow(generator,value,n) == 1){
                break;
            }
            value += replacement;
        }
        qSort(subGroup.begin(),subGroup.end());
        subGroups.push_back(subGroup);
        subGroup.clear();
    }
    return subGroups;
}








QList<int> MyMath::findAdditiveGenerator(int n)
{
    return multiplicativeZnGroup(n);
}

QList<QList<int> > MyMath::additiveSubGroups(int n)
{
    if(n < 1){
        throw "invalid argument";
    }
    QList <QList <int>> subGroups;
    QList <int> subGroup;
    QList <int> dividingList = unsignedDivisors(additiveZnGroup(n).size());
    //generator = 1
    for (int i = 0; i < dividingList.size(); i++) {
        int value = additiveZnGroup(n).size() / dividingList[i];
        int replacement = value;
        while (true) {
            subGroup.push_back(value % n);
            if(value % n == 0){
                break;
            }
            value += replacement;
        }
        qSort(subGroup.begin(),subGroup.end());
        subGroups.push_back(subGroup);
        subGroup.clear();
    }
    return subGroups;
}






QList<int> MyMath::getNumbers(QString arg)
{
    QRegularExpression rx("\\d+");
    QRegularExpressionMatchIterator i = rx.globalMatch(arg);
    QList <int> numberList;
    while (i.hasNext()){
        QRegularExpressionMatch match = i.next();
        numberList.push_back(match.captured(0).toInt());
    }

    return numberList;
}






bool MyMath::IsMultiplyOff(QList<int> list, int mod)
{
    if(mod < 2 || list.isEmpty())
        throw "Invalid argument";

    QList <int> testList;

    for (int i = 0; i < list.size(); i++) {
        testList.push_back(list[i] % mod);
    }


    for (int i = 0; i < testList.size(); i++) {
        for (int j = i; j < testList.size(); j++) {
            if(!testList.contains((testList[i] * testList[j]) % mod)){
                return false;
            }
        }
    }
    return true;
}






bool MyMath::IsAdditiveOff(QList<int> list, int mod)
{
    if(mod < 1 || list.isEmpty())
        throw "Invalid argument";

    QList <int> testList;

    for (int i = 0; i < list.size(); i++) {
        testList.push_back(list[i] % mod);
    }

    for (int i = 0; i < testList.size(); i++) {
        for (int j = i; j < testList.size(); j++) {
            if(!testList.contains((testList[i] + testList[j]) % mod)){
                return false;
            }
        }
    }
    return true;
}






bool MyMath::multiplicativeUnit(QList<int> list, int mod)
{
    if(mod < 2 || list.isEmpty())
        throw "Invalid argument";

    QSet <int> testList;
    for (int i = 0; i < list.size(); i++) {
        testList << (list[i] % mod);
    }

    if(testList.contains(1)){
        return true;
    }

    return false;
}




bool MyMath::additiveUnit(QList<int> list, int mod)
{
    if(mod < 1 || list.isEmpty())
        throw "Invalid argument";

    QSet <int> testList;
    for (int i = 0; i < list.size(); i++) {
        testList << (list[i] % mod);
    }

    if(testList.contains(0)){
        return true;
    }

    return false;
}




bool MyMath::multiplyInverse(QList<int> list, int mod)
{
    if(mod < 2 || list.isEmpty())
        throw "Invalid argument";

    bool here = false;
    QSet <int> testSet;
    for (int i = 0; i < list.size(); i++) {
        testSet << (list[i] % mod);
    }

    if(testSet.contains(0)){
        return false;
    }

    QList <int> testList = testSet.toList();
    for (int i = 0; i < testList.size(); i++) {
        for (int j = 0; j < testList.size(); j++) {
            if((testList[i] * testList[j]) % mod == 1){
                here = true;
                break;
            }
        }
        if(!here){
            return false;
        }
        here = false;
    }
    return true;
}




bool MyMath::additiveInverse(QList<int> list, int mod)
{
    if(mod < 1 || list.isEmpty())
        throw "Invalid argument";

    bool here = false;
    QSet <int> testSet;
    for (int i = 0; i < list.size(); i++) {
        testSet << (list[i] % mod);
    }

    QList <int> testList = testSet.toList();
    for (int i = 0; i < testList.size(); i++) {
        for (int j = 0; j < testList.size(); j++) {
            if((testList[i] + testList[j]) % mod == 0){
                here = true;
                break;
            }
        }
        if(!here){
            return false;
        }
        here = false;
    }
    return true;
}
