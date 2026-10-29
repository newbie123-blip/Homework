# 41443153

# 解題說明

## 作業二 多項式運算

## 解題說明

這次的題目要求實現多項式的加法與乘法，並用多項式的方式顯示出來。

### 解題策略

1. 先設定類別Term為多項式每一組的資料，與polynomial為多項式實作類別，兩者都要先frined i、ostream等一下會用到。

2. 寫好自訂的input與output的operator運算子多載，讓系統知道我的自訂多項式類別是要怎麼分別讀取常數分辨非常數。

3. 再來是newterm新增Term類別陣列，就用判斷現在是否已到上限?到了就創一個新陣列把空間*2再把舊的資料copy過來再刪除舊陣列後再將新陣列變成termarray。

4. 多項式加法:新增多項C，我用了雙迴圈檢查以確保沒有數值被漏掉。

5. 多項式乘法:用了多項式C作為第一次乘法結果暫存再用多項式D作為同指數相加後的最終答案回傳。

6. 代入X的數值n:用sum把termarray裡的coef*(n^exp)從頭到尾全部加起來就好了。

## 程式實作

以下為主要程式碼：

```cpp
#include<iostream>
#include<cmath>
#include <algorithm>
using namespace std;

class polynomial;

class Term {
    friend polynomial;
    friend istream& operator>>(istream& input, polynomial& p);
    friend ostream& operator<<(ostream& output, const polynomial& p);               //多項式的資料類別
private:
    double coef;
    int exp;
};

class polynomial {
    friend istream& operator>>(istream& input, polynomial& p);
    friend ostream& operator<<(ostream& output, const polynomial& p);
private:
    Term* termarray;
    int capacity;
    int terms;
public:
    polynomial() {
        capacity = 1;
        terms = 0;
        termarray = new Term[capacity];
    }

    polynomial(const polynomial& x) {
        capacity = x.capacity;
        terms = x.terms;                                       //拷貝建構子
        termarray = new Term[capacity];
        for (int i = 0; i < terms; i++) {
            termarray[i] = x.termarray[i];
        }
    }

    polynomial add(polynomial p) {
        polynomial test;
        for (int i = 0; i < terms; i++) {
            int flag = 0;
            for (int j = 0; j < p.terms; j++) {
                if (termarray[i].exp == p.termarray[j].exp) {                       //以陣列1為主指數相同相加
                    flag = 1;
                    test.newterm(termarray[i].coef + p.termarray[j].coef,
                        termarray[i].exp);
                    break;
                }
            }
            if (flag != 1) {
                test.newterm(termarray[i].coef, termarray[i].exp);
            }
        }
        for (int i = 0; i < p.terms; i++) {
            int flag = 0;
            for (int j = 0; j < terms; j++) {
                if (p.termarray[i].exp == termarray[j].exp) {                              //以陣列2為主再加一次避免漏掉
                    flag = 1;
                    break;
                }
            }
            if (flag != 1) {
                test.newterm(p.termarray[i].coef, p.termarray[i].exp);
            }
        }
        sort(test.termarray, test.termarray + test.terms, [](Term a, Term b) {
            return a.exp > b.exp; });
        return test;
    }

    polynomial mult(polynomial p) {
        polynomial a, b,c;
        for (int i = 0; i < terms; i++) {
            for (int j = 0; j < p.terms; j++) {
                a.newterm(termarray[i].coef * p.termarray[j].coef,
                    termarray[i].exp + p.termarray[j].exp);             //相乘結果全部存在 a 陣列裡。
            }
        }
        if (a.terms == 0) return a;

        for (int i = 0;i<a.terms-1;i++) {
            for (int j = i;j<a.terms-1;j++) {
                Term d;
                if (a.termarray[i].exp < a.termarray[j].exp) {
                    d=a.termarray[j];                                 //用指數進行泡沫排序
                    a.termarray[j] = a.termarray[i];
                    a.termarray[i] = d;
                }
            }
        }
        
        b.newterm(a.termarray[0].coef, a.termarray[0].exp);
        for (int i = 1; i < a.terms; i++) {
            if (a.termarray[i].exp == b.termarray[b.terms - 1].exp) {
                b.termarray[b.terms - 1].coef += a.termarray[i].coef;            //剛剛的泡沫排序法把同指數都排在旁邊了
            }                                                                    //跟旁邊指數相同的話相加
            else {
                b.newterm(a.termarray[i].coef, a.termarray[i].exp);
            }
        }
        return b;
    }

    double Eval(double n) {
        double sum = 0;
        for (int i = 0; i < terms; i++) {
            sum += termarray[i].coef * pow(n, termarray[i].exp);
        }
        return sum;
    }

    void newterm(double ncoef, int nexp) {
        if (terms >= capacity) {
            capacity *= 2;
            Term* temp = new Term[capacity];
            copy(termarray, termarray + terms, temp);
            delete[]termarray;
            termarray = temp;
        }
        termarray[terms].coef = ncoef;
        termarray[terms++].exp = nexp;
    }

    ~polynomial() {
        delete[] termarray;
    }
};
istream& operator>>(istream& input, polynomial& p) {
    double coef;
    int exp;
    char temp;
    bool flag = true;                                        //判斷是不是負的
    while (1) {
        input >> coef;                                        //先讀取第一個數字coef
        if (!flag) {
            coef *= -1;
            flag = true;                                     //如果是前面是"-"號把讀入的數值*-1
        }                                                      
        input.get(temp);                                      //跳過x
        if (temp == '\n') {                                    //下一位是換行結束迴圈
            p.newterm(coef, 0);
            break;
        }
        input.ignore();                                         //跳過^符號
        input >> exp;
        p.newterm(coef, exp);                                    //前面都沒問題放進陣列
        input.get(temp);                                         //讀下一個是否為負
        if (temp == '\n')break;
        else if (temp == '-')flag = false;
    }
    return input;
}
ostream& operator<<(ostream& output, const polynomial& p) {
    for (int i = 0; i < p.terms; i++) {
        if (p.termarray[i].exp == 0){                                //第一位是常數的情況
            if (i == 0) {
                output << p.termarray[i].coef;                      //第一位不輸出+號
            }
            else if (p.termarray[i].coef < 0) {
                output << p.termarray[i].coef;                       //如果是負顯示"-"
            }
            else {
                output << "+" << p.termarray[i].coef;               //如果是正顯示"+"
            }
            continue;
        }
        if (i == 0) {
            output << p.termarray[i].coef << "x^" << p.termarray[i].exp;
        }
        else if (p.termarray[i].coef < 0) {
            output << p.termarray[i].coef << "x^" << p.termarray[i].exp;              //負的正常顯示
        }
        else {
            output << "+" << p.termarray[i].coef << "x^" << p.termarray[i].exp;         //正的多顯示一個"+"
        }
    }
    return output;
}
int main() {
    polynomial p1;
    polynomial p2;

    while (cin >> p1 >> p2) {
        cout << "(" << p1 << ") + (" << p2 << ") = ";
        cout << p1.add(p2) << "\n";
        cout << "(" << p1 << ") X (" << p2 << ") = ";
        cout << p1.mult(p2) << "\n";
    }
    return 0;
}
```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 $O(N*M+(N+M)\log(N+M))$。
因為用到了雙迴圈與排序比較花時間。

2. 空間複雜度：空間複雜度為 $O(N+M)$。
有使用暫存用的類別。

## 測試與驗證

本節透過命令列進行多項式程式的編譯、執行與驗證，確保加法、乘法以及輸出格式皆符合預期。

### 測試項目與結果對照表

| 測試項目 | 測試例子 | 輸出結果 |
| :--- | :--- | :--- |
| **2. 多項式加法運算** | (2x^2+2x^1+2) + (2x^2+2x^1+2) | 4x^2+4x^1+4 |
| **3. 多項式乘法運算** | (2x^2+2x^1+2) X (2x^2+2x^1+2) | 4x^4+8x^3+12x^2+8x+4 |

## 程式測試
```shell
$ g++ main.cpp --std=c++17 -o main.exe
$ .\main.exe

```
## 申論及開發報告

1. **程式邏輯**
  輸入:我是用先讀取第一個數字後再讀取第二個字元判斷是否為換行(也就是結束)再ignore下一字元這樣會到指數的位置指數讀完一樣讀取下一位元判斷是否結束沒結束ignore+-符號後重複此循環。
  輸出:我是以for迴圈是跑完整個termarray判斷是否為負數來決定需不需要coef前面加一個+號，以及如果指數為0就不用顯示x直接顯示數字就好這樣的規則去實作。
  
   多項式加法: 第一個for迴圈就是把多項式A+B後存在一個新的多項式C裡面，第二個迴圈就是檢查有沒有B有的數但A沒有的如果有就newterm到多項式C裡面最後用sort排序讓他從大排到小。
  
   多項式乘法: 新增了多項式C、D，先把多項式A、B相乘然後把結果存在C裡面再用sort排序讓同指數的排在旁邊，最後在讓C內的同指數係數相加存在多項式D裡面，最後回傳多項式D。
  
2. **心得討論**
  在上課時聽老師說的時候不難理解，可是輪到自己時就發現很難寫出來，這跟平時寫題目時不一樣是更深層的應用，你要學習創造一個架構並且後面會持續使用到他所以需要考量到很多因素，還有程式碼的優化也很重要我目前在加法   那邊只能用雙迴圈達成目的但如果遇到更多資料的話會很耗能，我終於體會到這就是演算法的重要性，甚至有時候我還需要Ai來幫我除錯因為有些細節少打一個符號就會全部無法執行真的寫一個好程式碼是一個很難的事情。
