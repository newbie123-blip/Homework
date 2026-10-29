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
