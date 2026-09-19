# 41443153

作業一

##解題說明

阿克曼函式 $A(m, n)$ 是一個數值成長極其快速的雙變數數學函式

##解題策略

使用遞迴並且依照題目要求輸入條件A(m,n)
如果 m==0 回傳 n+1
如果 m>0 && n==0 回傳 A(m-1,1)
如果 m>0 && n>0 回傳 A(m-1, A(m,n-1))

##程式實作 

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

