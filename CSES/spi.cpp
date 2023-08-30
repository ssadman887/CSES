#include<bits/stdc++.h>
using namespace std;

int main()
{
    long long t,y,x;
    cin>>t;
    while(t--) {
        cin>> y;
        cin>> x;

        long long k = max(y,x);
        long long k2 = k*k;
        long long ans =0;

        if(k%2){
            if(y==k){
                ans =k2 -x+1;

            }
            else{
                ans =k2-y+1;
            }
        }
        else{
            if(x==k){
                ans =k2 -y+1;

            }
            else{
                ans =k2-x+1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}