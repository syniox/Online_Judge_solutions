#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+5;
int n,m,val[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int get_kind(int x){
	if(x<4) return x-1;
	return 3+(x&1);
}

namespace S{
	//0:1  1:2  2:3  3:>3,&1=0  4:>3,&1=1
	int len[5],buk[5][N];
	int ans[3][N];

	inline void init(){
		for(int i=1; i<=m; ++i){
			val[i]=nxi();
			int k=get_kind(val[i]);
			buk[k][++len[k]]=i;
		}
	}

	inline void clear_3(int &pt){
		for(int i=1; i<=len[2]; ++i,++pt){
			ans[0][pt]=buk[2][i];
			ans[1][pt]=buk[2][i];
			ans[2][pt]=buk[2][i];
		}
	}

	inline void build_12(int &pt){
		int x,l;
		if(len[4]) x=buk[4][len[4]--];
		else x=buk[3][len[3]--];
		l=val[x];
		const int limit_0=std::min(len[0],(l-3)>>1);
		const int limit_1=l-3-(limit_0<<1);
		const int end=(l-1+limit_1)>>1;
		const int turn=l-1-end;
		
		for(int i=0; i<end; ++i){
			ans[0][pt+i]=x;
		}
		ans[1][pt]=x;
		for(int i=1; i<=limit_0; ++i){
			ans[1][pt+i]=buk[0][len[0]--];
		}
		for(int i=0; i<turn; ++i){
			ans[2][pt+i]=x;
		}
		for(int i=turn; i<end; ++i){
			ans[1][pt+i]=buk[1][len[1]];
			ans[2][pt+i]=buk[1][len[1]--];
		}
		pt+=end;
	}

	inline void build_11(int &pt){
		const int x=buk[3][len[3]];
		const int l1=val[x];

		for(int i=0; i<l1>>1; ++i){
			ans[0][pt+i]=x;
		}
		ans[1][pt]=x;
		for(int i=0; i<=l1>>1; ++i){
			ans[2][pt+i]=x;
		}
		for(int i=1; i<(l1>>1)-1; ++i){
			ans[1][pt+i]=buk[0][len[0]--];
		}
		pt=pt+(l1>>1)-1;

		if(len[3]>1){
			const int y=buk[3][len[3]-1];
			const int l2=val[y];
			const int end=pt+(l2>>1)-1;

			for(int i=0; i<(l2+1)>>1; ++i){
				ans[1][pt+i]=y;
			}
			for(int i=0; i<l2>>1; i+=2){
				ans[0][pt+i]=y;
			}
			for(int i=1; i<l2>>1; i+=2){
				ans[0][pt+i]=buk[0][len[0]--];
			}
			for(int i=0; i<(l2-2)>>1; i+=2){
				ans[2][pt+i+1]=y;
			}
			for(int i=1; i<(l2-2)>>1; i+=2){
				ans[2][pt+i+1]=buk[0][len[0]--];
			}
			pt=end+1;
			len[3]-=2;
		}
		else{
			ans[0][pt]=buk[0][len[0]--];
			ans[1][pt]=buk[0][len[0]--];
			++pt;
			len[3]-=1;
		}
	}

	inline void clear_12(int pt){
		int pt1=pt;
		for(; pt1<=n&&len[1]; --len[1],++pt1){
			ans[0][pt1]=buk[1][len[1]];
			ans[1][pt1]=buk[1][len[1]];
		}
		for(; pt1<=n; ++pt1){
			ans[0][pt1]=buk[0][len[0]--];
			ans[1][pt1]=buk[0][len[0]--];
		}
		for(; pt<=n&&len[1]; pt+=2,--len[1]){
			ans[2][pt]=buk[1][len[1]];
			ans[2][pt+1]=buk[1][len[1]];
		}
		for(; pt<=n; ++pt){
			ans[2][pt]=buk[0][len[0]--];
		}
	}

	inline bool solve(){
		if(m<n) return 0;
		int pt=1;
		clear_3(pt);
		while(len[3]||len[4]){
			if(!len[4]&&!len[1]) build_11(pt);
			else build_12(pt);
		}
		clear_12(pt);
		return 1;
	}
}

int main(){
	n=nxi(),m=nxi();
	S::init();
	if(!S::solve()){
		puts("no");
		return 0;
	}
	puts("yes");
	for(int i=0; i<3; ++i){
		for(int j=1; j<=n; ++j){
			printf("%d ",S::ans[i][j]);
		}
		puts("");
	}
	return 0;
}
