#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
typedef long long lint;
const int N=2e5+5;
const int mod=998244353;
int n,lg2[N],dp[N];
char src[N];
class data{
	public:
		int sum,gap,r;
};
std::vector <data> vt[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

class SA{
	int sa[N],rank[N],height[19][N];

	inline int get_rk(int x){
		return x>n?0:rank[x];
	}

	public:

	inline void qsort(int *sa,int *rank,int *idx){
		static int buk[N];
		const int limit=std::max(n,27);
		memset(buk+1,0,limit*sizeof(int));
		for(int i=1; i<=n; ++i){
			++buk[rank[idx[i]]];
		}
		for(int i=1; i<=limit; ++i){
			buk[i]+=buk[i-1];
		}
		for(int i=n; i; --i){
			sa[buk[rank[idx[i]]]--]=idx[i];
		}
	}

	inline void build_sa(){
		static int tmp[N];
		for(int i=1; i<=n; ++i){
			rank[i]=src[i]-'a'+1;
			tmp[i]=i;
		}
		qsort(sa,rank,tmp);
		for(int w=1,cnt_rk=0; w<=n&&cnt_rk<n; w<<=1){
			int pos=0;
			for(int i=n-w+1; i<=n; ++i){
				tmp[++pos]=i;
			}
			for(int i=1; i<=n; ++i){
				if(sa[i]>w) tmp[++pos]=sa[i]-w;
			}
			qsort(sa,rank,tmp);
			cnt_rk=0;
			for(int i=1; i<=n; ++i){
				if(rank[sa[i]]!=rank[sa[i-1]]||get_rk(sa[i]+w)!=get_rk(sa[i-1]+w)){
					++cnt_rk;
				}
				tmp[sa[i]]=cnt_rk;
			}
			memcpy(rank+1,tmp+1,n*sizeof(int));
		}
	}

	inline void build(){
		build_sa();
		for(int i=1,pre=0; i<=n; ++i){
			pre=std::max(pre-1,0);
			if(rank[i]==1) continue;
			for(int x=i+pre,y=sa[rank[i]-1]+pre; x<=n&&y<=n&&src[x]==src[y]; ){
				++pre,++x,++y;
			}
			height[0][rank[i]]=pre;
		}
		for(int i=1; i<19; ++i){
			for(int j=1; j<=n; ++j){
				height[i][j]=height[i-1][j];
				if(j>1<<(i-1)){
					apn(height[i][j],height[i-1][j-(1<<(i-1))]);
				}
			}
		}
	}

	inline int get_lcp(int l,int r){
		l=rank[l],r=rank[r];
		if(l>r) std::swap(l,r);
		int p=lg2[r-l];
		return std::min(height[p][l+(1<<p)],height[p][r]);
	}
}sa0,sa1;

inline void init(){
	for(int i=2; i<=n; ++i){
		lg2[i]=lg2[i-1]+(i==(i&-i));
	}
}

inline void get_tag(){
	static bool *ban[N];
	static int len[N];
	for(int i=1; i<=n>>1; ++i){
		len[i]=n/i;
		ban[i]=new bool[len[i]+1];
	}
	for(int i=1; i<=n>>1; ++i){
		for(int j=1; j<len[i]; ++j){
			if(ban[i][j]) continue;
			const int lcp_r=sa0.get_lcp(j*i,(j+1)*i);
			const int lcp_l=sa1.get_lcp(n-(j+1)*i+1,n-j*i+1);
			if(lcp_l+lcp_r<=i) continue;
			const int pos_l=(j+0)*i-lcp_l+1;
			const int pos_r=(j+1)*i+lcp_r-1;
			//create tag
			for(int k=0; k<i<<1&&k+pos_l+(i<<1)-1<=pos_r; ++k){
				vt[pos_l+k+(i<<1)-1].push_back((data){0,i<<1,pos_r});
			}
			//ban node
			for(int k=i; k<<1<=(pos_r-pos_l+1); k+=i){
				for(int l=(pos_l+k-1)/k; (l+1)*k<=pos_r; ++l){
					ban[k][l]=1;
				}
			}
		}
	}
}

int main(){
	scanf("%s",src+1);
	n=strlen(src+1);
	init();
	sa0.build();
	std::reverse(src+1,src+n+1);
	sa1.build();

	get_tag();
	dp[0]=1;
	for(int sum=1,i=1; i<=n; ++i){
		int res=0;
		for(std::vector <data> ::iterator it=vt[i].begin(); it!=vt[i].end(); ++it){
			it->sum=(it->sum+dp[i-(it->gap)])%mod;
			res=(res+it->sum)%mod;
			if(i+it->gap<=it->r){
				vt[i+it->gap].push_back(*it);
			}
		}
		dp[i]=(sum+(lint)(mod-2)*res)%mod;
		sum=(sum+dp[i])%mod;
	}
	printf("%d\n",dp[n]);
	return 0;
}
