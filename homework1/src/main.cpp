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
