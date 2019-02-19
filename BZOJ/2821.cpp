#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+5;
const int S=320;
int n,m,q,val[N],pre_ans[S][S],pre_sum[S][N];
//pre_ans[i][j]: [i,j),pre_sum[i][j]: [1,j*S)

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void pre_work(){
	static int buk[N];
	for(int i=0,j=0; i<n; ++i){
		if(i%S==0){
			++j;
			memcpy(pre_sum[j],pre_sum[j-1],m*sizeof(int));
		}
		++pre_sum[j][val[i]];
	}
	for(int i=0; i*S<n; ++i){
		memset(buk,0,m*sizeof(int));
		int ans=0;
		for(int j=i*S,tmp; j<n; ++j){
			if(j!=i*S&&j-S*(tmp=j/S)==0){
				pre_ans[i][tmp]=ans;
			}
			if(buk[val[j]]&1) ++ans;
			else ans-=(bool)buk[val[j]];
			++buk[val[j]];
		}
		pre_ans[i][n/S+1]=ans;
	}
}

inline void upd_ans(int buk[],int &ans,int bel_l,int bel_r,int st,int ed){
	for(int i=st; i<=ed; ++i){
		if(!buk[val[i]]) continue;
		int tmp=bel_l==bel_r?0:pre_sum[bel_r][val[i]]-pre_sum[bel_l+1][val[i]];
		if((buk[val[i]]&1)==0) ans+=!tmp;
		else if(tmp) ans+=tmp&1?1:-1;
		buk[val[i]]=0;
	}
}

inline int solve(const int ql,const int qr){
	static int buk[N];
	const int bel_l=ql/S,bel_r=qr/S;
	int ans=0;
	if(bel_l==bel_r){
		for(int i=ql; i<=qr; ++i){
			++buk[val[i]];
		}
		upd_ans(buk,ans,bel_l,bel_r,ql,qr);
	}
	else{
		ans=pre_ans[bel_l+1][bel_r];
		for(int i=std::min(n,(bel_l+1)*S)-1; i>=ql; --i){
			++buk[val[i]];
		}
		for(int i=bel_r*S; i<=qr; ++i){
			++buk[val[i]];
		}
		upd_ans(buk,ans,bel_l,bel_r,ql,std::min(n,bel_l+1)*S-1);
		upd_ans(buk,ans,bel_l,bel_r,bel_r*S,qr);
	}
	return ans;
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=0; i<n; ++i){
		val[i]=nxi()-1;
	}
	pre_work();
	for(int ans=0,i=1; i<=q; ++i){
		int l=(ans+nxi())%n,r=(ans+nxi())%n;
		if(l>r) std::swap(l,r);
		printf("%d\n",ans=solve(l,r));
	}
	return 0;
}
