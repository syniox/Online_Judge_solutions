#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=1e5+5;
const int S=320;
int n,val[N];
bool type;

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}
template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}
bool cmp_val(int x,int y){
	return val[x]<val[y];
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace D{
	int pt,mp[N];
	inline void ins(const int v){
		mp[pt++]=v;
	}
	inline void build(){
		std::sort(mp,mp+pt);
		pt=std::unique(mp,mp+pt)-mp;
	}
	inline int ask(const int v){
		return std::lower_bound(mp,mp+pt,v)-mp+1;
	}
}

namespace B{
	int cnt_blk,idx[S][S+5],bans[S][N],vans[S][N];
	int lis[N],invlis[N],buk[N];

	inline void build_idx(){
		const int remain=(n-1)%S+1;
		++cnt_blk;
		for(int i=1,j=1; i<=n; ++i,++j){
			if(j==S+1) j=1,++cnt_blk;
			idx[cnt_blk][j]=i;
		}
		for(int i=1; i<cnt_blk; ++i){
			std::sort(idx[i]+1,idx[i]+S+1,cmp_val);
		}
		std::sort(idx[cnt_blk]+1,idx[cnt_blk]+remain+1,cmp_val);
	}

	inline void build_lis(){
		int pt_buk;
		pt_buk=1;
		for(int i=1; i<=n; ++i){
			int l=1,r=pt_buk,mid;
			while(l!=r){
				mid=(l+r)>>1;
				if(buk[mid]<val[i]) l=mid+1;
				else r=mid;
			}
			buk[l]=val[i];
			lis[i]=l;
			if(l==pt_buk) ++pt_buk;
		}
		pt_buk=1;
		for(int i=n; i; --i){
			int l=1,r=pt_buk,mid;
			while(l!=r){
				mid=(l+r)>>1;
				if(buk[mid]>val[i]) l=mid+1;
				else r=mid;
			}
			buk[l]=val[i];
			invlis[i]=l;
			if(l==pt_buk) ++pt_buk;
		}
	}

	inline void build_ans(){
		int pt_buk;
		pt_buk=1;
		for(int i=1; i<=n; ++i){
			apx(pt_buk,lis[i]+1);
			buk[lis[i]]=val[i];
			if(i%S) continue;

			const int blk=i/S;
			bans[blk][n+1]=pt_buk-1;
			for(int j=n; j>i; --j){
				int l=0,r=pt_buk-1,mid;
				while(l!=r){
					mid=(l+r+1)>>1;
					if(buk[mid]<val[j]) l=mid;
					else r=mid-1;
				}
				bans[blk][j]=std::max(bans[blk][j+1],invlis[j]+l);
			}
		}

		pt_buk=1;
		for(int i=n; i; --i){
			apx(pt_buk,invlis[i]+1);
			buk[invlis[i]]=val[i];
			if(i%S!=1) continue;

			const int blk=i/S+1;
			vans[blk][0]=pt_buk-1;
			for(int j=1; j<i; ++j){
				int l=0,r=pt_buk-1,mid;
				while(l!=r){
					mid=(l+r+1)>>1;
					if(buk[mid]>val[j]) l=mid;
					else r=mid-1;
				}
				vans[blk][j]=std::max(vans[blk][j-1],lis[j]+l);
			}
		}
	}

	inline int solve(const int l,const int r){
		static bool mark_l[N],mark_r[N];
		const int bel_l=(l-1)/S+1,bel_r=(r-1)/S+1;
		const int lim_l=bel_l==cnt_blk?(n-1)%S+1:S;
		const int lim_r=bel_r==cnt_blk?(n-1)%S+1:S;
		const int pt_l=(bel_l-1)*S+1;
		const int pt_r=(bel_r-1)*S+lim_r;
		int ans=std::max(bans[bel_l-1][r],vans[bel_r+1][l]);

		for(int i=pt_l; i<=l; ++i){
			mark_l[i]=1;
			apx(ans,lis[i]);
		}
		for(int i=r; i<=pt_r; ++i){
			mark_r[i]=1;
			apx(ans,invlis[i]);
		}
		for(int i=1,j=1,res=0; j<=lim_r; ++j){
			const int x=idx[bel_r][j];
			if(!mark_r[x]) continue;
			for(; i<=lim_l&&(val[idx[bel_l][i]]<val[x]||!mark_l[idx[bel_l][i]]); ++i){
				if(mark_l[idx[bel_l][i]]){
					apx(res,lis[idx[bel_l][i]]);
				}
			}
			apx(ans,res+invlis[x]);
		}
		for(int i=r; i<=pt_r; ++i) mark_r[i]=0;
		for(int i=pt_l; i<=l; ++i) mark_l[i]=0;
		return ans;
	}
}

int main(){
	n=nxi(),type=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		D::ins(val[i]);
	}
	D::build();
	for(int i=1; i<=n; ++i){
		val[i]=D::ask(val[i]);
	}
	B::build_idx();
	B::build_lis();
	B::build_ans();
	for(int ans=0,q=nxi(); q; --q){
		int l=nxi(),r=nxi();
		if(type) l^=ans,r^=ans;
		printf("%d\n",ans=B::solve(l-1,r+1));
	}
	return 0;
}
