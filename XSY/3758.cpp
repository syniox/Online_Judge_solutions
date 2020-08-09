#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long lint;
const int N=524290;
int n,q;
struct pic{
	int d,l,r;
}pc[N];
struct piece{
	int b,st;
	bool k;
	friend bool operator<(const piece &a,const piece &b);
	friend bool operator==(const piece &a,const piece &b);
	friend piece operator*(const piece &a,const piece &b);
	friend int crs_pt(const piece &a,const piece &b);
	int opt(const int x) const;
};

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

bool operator<(const piece &a,const piece &b){
	return assert(a.k==b.k),a.b<b.b;
}
bool operator==(const piece &a,const piece &b){
	return a.k==b.k&&a.b==b.b;
}
piece operator*(const piece &a,const piece &b){
	int p=max(a.st,b.st);
	return (piece){b.opt(a.opt(p)),p,a.k&b.k};
}
int crs_pt(const piece &a,const piece &b){
	assert(a.k!=b.k);
	return (a.b-b.b)*(b.k-a.k);//same as /
}
int piece::opt(const int x)const{
	return k*x+b;
}

inline void check_and_push(vector<piece> &vt,const piece &x){
	if(vt.empty()||!(vt.back()==x)) vt.push_back(x);
}
inline int psh_crs(vector<piece> &res,piece a,piece b,const int st,const int ed){//[st,ed)
	assert(a.k!=b.k);
	int cpt=crs_pt(a,b);//a负责到cpt-1
	if(a.k) swap(a,b);
	if(cpt>st){
		check_and_push(res,a);
	}
	if(cpt<ed){
		check_and_push(res,(piece){b.b,max(st,cpt),b.k});
	}
	return cpt;
}
int set_st(int pbuk[],const vector<piece> &a,const vector<piece> &b){
	int cnt1,cnt=0;
	for(vector<piece>::const_iterator it=a.begin(); it!=a.end(); ++it){
		pbuk[++cnt]=it->st;
	}
	cnt1=cnt;
	for(vector<piece>::const_iterator it=a.begin(); it!=a.end(); ++it){
		pbuk[++cnt]=it->st;
	}
	inplace_merge(pbuk+1,pbuk+cnt1+1,pbuk+cnt+1);
	return unique(pbuk+1,pbuk+cnt+1)-pbuk-1;
}

vector<piece> concat(const vector<piece> &a,const vector<piece> &b){
	assert(!a.empty()&&!b.empty());
	vector<piece> res;
	res.reserve(a.size()+b.size());
	vector<piece>::const_iterator ia=a.begin(),ib=b.begin();
	for(int i=-1e8; i<=1e8; ){
		if(ia+1!=a.end()&&(ia+1)->st<=i) ++ia;
		if(ib+1!=b.end()&&(ib+1)->st<=ia->opt(i)) ++ib;
		int lima=(ia+1==a.end()?(int)1e8+1:(ia+1)->st)-i;
		int limb=ia->k?(ib+1==b.end()?(int)1e8+1:(ib+1)->st)-ia->opt(i):2e8;
		check_and_push(res,*ia**ib);
		i+=min(lima,limb);
	}
	return res;
}

void apl_to(const vector<piece> &a,vector<piece> &b){
	static int pbuk[N*4];
	static vector<piece> res(N*4);
	res.clear();
	int cnt=set_st(pbuk,a,b);
	pbuk[cnt+1]=1e8+1;
	vector<piece>::const_iterator ia=a.begin(),ib=b.begin();
	for(int i=1; i<=cnt; ++i){
		if(ia+1!=a.end()&&(ia+1)->st<=i) ++ia;
		if(ib+1!=b.end()&&(ib+1)->st<=i) ++ib;
		if(ia->k==ib->k){
			piece tmp=max(*ia,*ib);
			check_and_push(res,(piece){tmp.b,i,tmp.k});
		}else{
			psh_crs(res,*ia,*ib,pbuk[i],pbuk[i+1]);
		}
	}
	b=res;
}

void load_pic(vector<piece> &vt,const pic &p){
	assert(vt.empty());
	if(p.l==p.r){
		vt.push_back((piece){p.l,-(int)1e8,0});
		return;
	}
	int c1=crs_pt((piece){p.d,0,1},(piece){p.l,0,0});
	vt.push_back((piece){p.l,-(int)1e8,0});
	vt.push_back((piece){p.d,c1,0});
	int c2=crs_pt((piece){p.d,0,1},(piece){p.r,0,0});
	vt.push_back((piece){p.r,c2,0});
}

int qans(const vector<piece> &vt,const int x){
	assert(!vt.empty());
	int l=0,r=vt.size()-1,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(x<vt[mid].st) l=mid+1;
		else r=mid;
	}
	assert(l<(int)vt.size());
	return vt[l].opt(x);
}

namespace T{
#define mid ((l+r)>>1)
	vector<piece> tr[N*2][4];//最大值函数
	//第0位表示是否卡左边，1位表示是否卡右边
	int x,y,v,ans;

	inline int idx(const int l,const int r){
		return (l+r)>>1;
	}
	void build(const int l,const int r){
		const int k=idx(l,r);
		if(l==r){
			load_pic(tr[k][3],pc[l]);
			tr[k][0]=tr[k][1]=tr[k][2]=tr[k][3];
			return;
		}
		build(l,mid),build(mid+1,r);
		int ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k][3]=concat(tr[ls][3],tr[rs][3]);
		tr[k][2]=tr[rs][2];
		apl_to(concat(tr[ls][2],tr[rs][3]),tr[k][2]);
		tr[k][1]=tr[ls][1];
		apl_to(concat(tr[ls][3],tr[rs][1]),tr[k][1]);
		tr[k][0]=concat(tr[ls][2],tr[rs][1]);
		apl_to(tr[ls][0],tr[k][0]);
		apl_to(tr[rs][0],tr[k][0]);
	}

	int getans(const int l,const int r,const int v){
		if(l>=x&&r<=y){
			apx(ans,qans(tr[idx(l,r)][0],T::v));
			return max(qans(tr[idx(l,r)][3],v),qans(tr[idx(l,r)][2],T::v));
		}
		if(y<=mid) return getans(l,mid,v);
		if(x>mid) return getans(mid+1,r,v);
		int px=getans(l,mid,v);
		apx(ans,qans(tr[idx(mid+1,r)][1],px));
		return getans(mid+1,r,px);
	}

	int solve(const int v,const int l,const int r){
		assert(l<=r);
		T::x=l,T::y=r,T::v=v,ans=-1e8;
		getans(1,n,v);
		return ans;
	}
#undef mid
}

int main(){
	n=ni,q=ni;
	for(int i=1; i<=n; ++i){
		pc[i]=(pic){ni,ni,ni};
	}
	T::build(1,n);
	while(q--){
		int l=ni,r=ni,d=ni;
		printf("%d\n",T::solve(d,l,r));
	}
	return 0;
}
