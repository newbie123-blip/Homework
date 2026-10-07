# 41443153

作業一

## 解題說明

阿克曼函式 $A(m, n)$ 是一個數值成長極其快速的雙變數數學函式

## 解題策略

使用遞迴並且依照題目要求輸入條件A(m,n)

1. 如果 m==0 回傳 n+1
2. 如果 m>0 && n==0 回傳 A(m-1,1)
3. 如果 m>0 && n>0 回傳 A(m-1, A(m,n-1))

## 遞迴程式實作 

```cpp
#include<iostream>
using namespace std;

int AA(int m,int n){
if(m==0){return n+1;}
else if(m>0 && n==0){return AA(m-1,1) ;}
else if(m>0 && n>0){return AA(m-1, AA(m,n-1));}
}

int main(){
int x,y;
while(cin>>x>>y){
cout<<AA(x,y)<<"\n";

}
return 0;
}
```
## 非遞迴程式實作 

```cpp
#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> sta;
        
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                sta.push(s[i]);
            } else if (sta.empty()) {
                return false;
            } else if (s[i] == ')') {
                if (sta.top() == '(') {
                    sta.pop();
                } else {
                    return false;
                }
            } else if (s[i] == '}') {
                if (sta.top() == '{') {
                    sta.pop();
                } else {
                    return false;
                }
            } else if (s[i] == ']') {
                if (sta.top() == '[') {
                    sta.pop();
                } else {
                    return false;
                }
            }
        }
        
        if (sta.empty()) return true;
        else return false;
    }
};

int main() {
    Solution solution;
    string arr;
    while (cin >> arr) {
        if (solution.isValid(arr)) {
            cout << "結果：true (合法)" << "\n";
        } else {
            cout << "結果：false (不合法)" << "\n";
        }
    }

    return 0;
}
```
## 效能分析
遞迴效能分析:
1. 時間複雜度：程式的時間複雜度為 $O(A(m, n))$ 指數成長。
2. 空間複雜度：空間複雜度為 $O(A(m, n))$。

非遞迴效能分析:
1. 時間複雜度：程式的時間複雜度為 $O(N)$ 指數成長。
2. 空間複雜度：空間複雜度為 $O(N)$。


## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $(m,n)$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $m = 0$ $n = 0$ | 1        | 1        |
| 測試二   | $m = 1$ $m = 2$ | 4        | 4        |
| 測試三   | $m = 2$ $m = 2$ | 7        | 7        |
| 測試四   | $m = 3$ $m = 2$ | 29      | 29     |
| 測試五   | $m =-1$ $m = 0$ | 程式崩潰 | -1 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o sigma sigma.cpp
$ ./sigma
6
```

### 結論

1. 程式能正確計算小數值範圍內的阿克曼函式結果。  
2. 測試案例涵蓋了三種遞迴分支與邊界條件（$m=0$、$n=0$）。  
3. 當 $m \ge 4$ 時，由於計算量與遞迴深度爆炸性成長，程式會迅速超出記憶體限制導致 Stack Overflow（堆疊溢位）。

## 申論及開發報告

### 選擇遞迴的原因

為何不用非遞迴
1.**遞迴速度快且簡短** 
  遞迴的寫法能快速達到想要的效果。
  如使用非遞迴則需要很多條件又很慢來達到此目的。
  且阿克曼函式本身就是透過遞迴式定義的範例。

2.**使用非遞迴**
  改寫成非遞迴需要寫出複雜的stack結構。
  增加程式的維護成本。
  可讀性變差。

3.**遞迴的語意清楚**
  在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。
  這種設計簡化了邏輯，不需要額外變數來維護中間狀態。

在阿克曼函式中可以看到使用遞迴與非遞迴的程式複雜度的差別，所以特定條件的程式要使用正確的方式否則就會降低程式的可讀性與清晰度。
