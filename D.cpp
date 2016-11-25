#include <iostream>
#include <algorithm>
using namespace std;

#define  MOD 1000000007

int A[750005];
int dp[750005];


int main(){
	int t,n;
	cin>>t;
	while(t--){
		for(int i=0;i<750005;++i){
			dp[i]=0;
		}
		cin>>n;
		for(int i=0;i<n;++i){
			cin>>A[i];
		}
		sort(A,A+n);

		dp[A[n-1]]=1;
		int ans =1;

		for(int i=n-2;i>=0;--i){
			dp[A[i]]=1;
			int k = 2*A[i];
			while(k<=A[n-1]){
				dp[A[i]]=(dp[A[i]]+dp[k])%MOD;
				k+=A[i];
			}
			ans=(ans+dp[A[i]])%MOD;
		}

		cout<<ans<<"\n";
	}
	return 0;
}