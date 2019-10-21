#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
typedef long long lint;
const int N=5e5+5;
int n,tot,val[N],col[N],mp[N];
int psum[3][N];
struct vst{
	int r,g,b;
	friend bool operator <= (const vst &a,const vst &b){
		return a.r<=b.r&&a.g<=b.g&&a.b<=b.b;
	}
}st[N];

struct pnt{
	int x,y;
	friend bool operator < (const pnt &a,const pnt &b){
		return a.x==b.x?a.y<b.y:a.x<b.x;
	}
};

bool cp_r(const vst &a,const vst &b){
	return a.r==b.r?a.g<b.g:a.r<b.r;
}

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

void get_st(){
	for(int i=1; i<=tot; ++i){
		int pos=std::upper_bound(mp+1,mp+tot+1,mp[i]*2-1)-mp-1;
		vst x;
		x.r=psum[0][pos]-psum[0][i-1];
		x.g=psum[1][pos]-psum[1][i-1];
		x.b=psum[2][pos]-psum[2][i-1];
		st[i]=x;
	}
}

lint solve(){
	static std::set <pnt> pst;
	std::sort(st+1,st+tot+1,cp_r);
	lint res=0,ans=0;
	for(int i=st[tot].r,j=tot; i>=0; --i){
		for(; j&&st[j].r>=i; --j){
			const int x=st[j].g,y=st[j].b;
			std::set <pnt> ::iterator cur=pst.lower_bound((pnt){x,y});
			if(cur!=pst.end()&&cur->x>=x&&cur->y>=y) continue;
			int nxt_y=-1;
			if(cur!=pst.end()){
				nxt_y=cur->y;
			}
			if(cur!=pst.begin()){
				--cur;
				while(cur->y<=y){
					int lst_x=-1;
					if(cur!=pst.begin()){
						lst_x=(--cur)->x;
						++cur;
					}
					res-=(lint)(cur->x-lst_x)*(cur->y-nxt_y);
					if(cur==pst.begin()){
						pst.erase(cur);
						break;
					}
					pst.erase(cur--);
				}
			}
			int lst_x=-1;
			cur=pst.lower_bound((pnt){x,y});
			if(cur!=pst.begin()){
				lst_x=(--cur)->x;
				++cur;
			}
			pst.insert(cur,(pnt){x,y});
			res+=(lint)(x-lst_x)*(y-nxt_y);
		}
		ans+=res;
	}
	return ans-1;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		mp[i]=val[i]=nxi();
		char c;
		while((c=getchar())>'Z'||c<'A');
		switch(c){
			case 'R': col[i]=0; break;
			case 'G': col[i]=1; break;
			case 'B': col[i]=2; break;
		}
	}
	std::sort(mp+1,mp+n+1);
	tot=std::unique(mp+1,mp+n+1)-mp-1;
	for(int i=1; i<=n; ++i){
		val[i]=std::lower_bound(mp+1,mp+tot+1,val[i])-mp;
		++psum[col[i]][val[i]];
	}
	for(int i=0; i<3; ++i){
		for(int j=2; j<=tot; ++j){
			psum[i][j]+=psum[i][j-1];
		}
	}
	get_st();
	printf("%lld\n",solve());
	return 0;
}
