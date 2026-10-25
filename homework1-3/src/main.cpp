#include<iostream>
#include<cmath>
#include <algorithm>
using namespace std;

class polynomial;

class Term {
    friend polynomial;
    friend istream& operator>>(istream& input, polynomial& p);
    friend ostream& operator<<(ostream& output, const polynomial& p);
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
        terms = x.terms;
        termarray = new Term[capacity];
        for (int i = 0; i < terms; i++) {
            termarray[i] = x.termarray[i];
        }
    }

    polynomial add(polynomial p) {
        polynomial test;
        for (int i = 0; i < this->terms; i++) {
            int flag = 0;
            for (int j = 0; j < p.terms; j++) {
                if (this->termarray[i].exp == p.termarray[j].exp) {
                    flag = 1;
                    test.newterm(this->termarray[i].coef + p.termarray[j].coef, 
                    this->termarray[i].exp);
                    break; 
                }
            }
            if (flag != 1) {
                test.newterm(this->termarray[i].coef, this->termarray[i].exp);
            }
        }
        for (int i = 0; i < p.terms; i++) {
            int flag = 0;
            for (int j = 0; j < this->terms; j++) {
                if (p.termarray[i].exp == this->termarray[j].exp) {
                    flag = 1;
                    break;
                }
            }
            if (flag != 1) {
                test.newterm(p.termarray[i].coef, p.termarray[i].exp);
            }
        }
        sort(test.termarray, test.termarray + test.terms, [](Term a,Term b) {
            return a.exp > b.exp;});
        return test;
    }

    polynomial mult(polynomial p) {
        polynomial a,b;
        for (int i = 0; i < this->terms; i++) {
            for (int j = 0; j < p.terms; j++) {
                a.newterm(this->termarray[i].coef * p.termarray[j].coef,
                this->termarray[i].exp + p.termarray[j].exp);
            }
        }
        if (a.terms == 0) return a;
        sort(a.termarray, a.termarray + a.terms, [](Term x, Term y) {
            return x.exp > y.exp;});
        b.newterm(a.termarray[0].coef, a.termarray[0].exp);
        for (int i = 1; i < a.terms; i++) {
            if (a.termarray[i].exp == b.termarray[b.terms - 1].exp) {
                b.termarray[b.terms - 1].coef += a.termarray[i].coef;
            }else {
                b.newterm(a.termarray[i].coef, a.termarray[i].exp);
            }
        }
        return b;
    }

    double Eval(double n) {
        double sum=0;
        for (int i = 0; i < terms; i++) {
            sum += termarray[i].coef*pow(n, termarray[i].exp);
        }
        return sum;
    }

    void newterm(double ncoef, int nexp) {
        if (terms >= capacity) {
            capacity *= 2;
            Term* temp = new Term[capacity];
            copy(termarray, termarray + terms, temp);
            delete []termarray;
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
    bool flag=true;
    while (1) {
        input >> coef;
        if (!flag) {
            coef *= -1;
            flag = true;
        }
        input.get(temp);
        if (temp == '\n') {
            p.newterm(coef, 0);
            break;
        }
        input.ignore();
        input >> exp;
        p.newterm(coef, exp);
        input.get(temp);
        if (temp == '\n')break;
        else if (temp == '-')flag = false;
    }
    return input;
}
ostream& operator<<(ostream& output, const polynomial& p) {
    for (int i = 0; i < p.terms; i++) {
        if (p.termarray[i].exp == 0) {
            if (i==0) {
                output << p.termarray[i].coef;
            }
            else if (p.termarray[i].coef < 0) {
                output << p.termarray[i].coef;
            }
            else {
                output <<"+" << p.termarray[i].coef;
            }
            continue;
        }
        if (i == 0) {
            output << p.termarray[i].coef << "x^" << p.termarray[i].exp;
        }
        else if (p.termarray[i].coef < 0) {
            output << p.termarray[i].coef << "x^" << p.termarray[i].exp;
        }
        else {
            output << "+" << p.termarray[i].coef << "x^" << p.termarray[i].exp;
        }
    }
    return output;
}
int main() {
    polynomial poly1;
    polynomial poly2;

    poly1.newterm(2, 2);
    poly1.newterm(2, 1);
    poly1.newterm(2, 0);

    poly2.newterm(2, 2);
    poly2.newterm(2, 1);
    poly2.newterm(2, 0);

    cout << "(" << poly1 << ") + (" << poly2 << ") = ";
    cout << poly1.add(poly2) << "\n";
    cout << "(" << poly1 << ") X (" << poly2 << ") = ";
    cout << poly1.mult(poly2) << "\n";
    return 0;
}
