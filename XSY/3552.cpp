#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=65;
//A$,AAB,AB,B$,BA,BBA
int n,q;
lint dp[N][6],psum[N][6];
const int st_fr[6]={3,4,-1,0,-1,2};

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

void get_dp(){
	dp[0][0]=1;
	for(int i=1; i<=n; ++i){
		for(int j=0; j<6; ++j){
			if(~st_fr[j]) dp[i][j]=dp[i-1][st_fr[j]];
		}
		dp[i][2]=dp[i-1][0]+dp[i-1][5]+dp[i-1][1]+dp[i-1][2];
		dp[i][4]=dp[i-1][3]+dp[i-1][4]+dp[i-1][5]+dp[i-1][1];
		psum[i][0]=dp[i][0];
		for(int j=1; j<6; ++j){
			psum[i][j]=psum[i][j-1]+dp[i][j];
		}
	}
}

lint solve(const int n,lint rk){
	//A$,AAB,AB,B$,BA,BBA
	//2 <- 0,5,1,2
	//4 <- 3,4,5,1
	static const int ch[2][4]={{0,5,1,2},{3,4,5,1}};
	static const int pos_odd[2][4]={{1,0,1,1},{1,1,1,0}};
	if(n==0){
		assert(rk==1);
		return 1;
	}
	for(int i=0; i<6; ++i){
		if(psum[n][i]<rk) continue;
		if(~st_fr[i]){
			lint lst_s=st_fr[i]?psum[n-1][st_fr[i]-1]:0;
			lint cur_s=i?psum[n][i-1]:0;
			return solve(n-1,lst_s+(rk-cur_s))*2;
		}
		else{
			const int p=i==4;
			rk-=p?psum[n][3]:psum[n][1];
			lint s=0;
			for(int j=0; j<4; ++j){
				if(s+dp[n-1][ch[p][j]]>=rk){
					lint lst_s=ch[p][j]?psum[n-1][ch[p][j]-1]:0;
					return solve(n-1,lst_s+rk-s)*2-pos_odd[p][j];
				}
				s+=dp[n-1][ch[p][j]];
			}
			assert(0);
		}
	}
	assert(0);
	return 0;
}

int main(){
	n=nxi<int>(),q=nxi<int>();
	get_dp();
	while(q--){
		printf("%lld\n",solve(n,nxi<lint>()));
	}
	return 0;
}
