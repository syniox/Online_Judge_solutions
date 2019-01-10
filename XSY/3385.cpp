#include <vector>
#include <algorithm>
#include "rank.hpp"
const int N=1005;

static inline int jdg_g(const int x,const int y){
	if(ask(x,y)=='g') return x;
	if(ask(y,x)=='g') return y;
	return -1;
}

static inline int jdg_b(const int x,const int y){
	if(ask(x,y)=='b') return x;
	if(ask(y,x)=='b') return y;
	return -1;
}

static bool cmp_b(int x,int y){
	return ask(x,y)=='b';
}

static bool cmp_g(int x,int y){
	return ask(y,x)=='g';
}

static std::vector <int> vt_sort(std::vector <int> vt,bool(*const cmp)(int,int)){
	std::vector <int> ans;
	int n=vt.size();
	ans.push_back(vt[0]);
	for(int i=1; i<n; ++i){
		int l=0,r=i,mid;
		while(l!=r){
			mid=(l+r)>>1;
			if(cmp(vt[i],ans[mid])) r=mid;
			else l=mid+1;
		}
		if(l==i) ans.push_back(vt[i]);
		else{
			std::vector <int> ::iterator it=ans.begin()+l;
			ans.insert(it,vt[i]);
		}
	}
	return ans;
}

std::vector <int> work(const int n){
	static bool vis[N];
	static int mp[N];
	std::vector <int> ans,res,buk;
	int large3=-1,smallest;
	for(int i=0; i<n-1; i+=2){
		large3&=jdg_g(i,i+1);
		if(large3!=-1) break;
	}
	if(large3==-1&&n&1){
		large3&=jdg_g(0,n-1);
	}
	if(large3==-1){
		for(int i=0; i<n; ++i){
			res.push_back(i);
		}
		//std::sort(res.begin(),res.end(),cmp_b);
		res=vt_sort(res,cmp_b);
		for(int i=n-3,flag=1; flag&&i<n; ++i){
			for(int j=i+1; j<n; ++j){
				int tp=jdg_b(res[i],res[j]);
				if(tp==-1) continue;
				int f1,f2,f3;
				f2=tp,f3=res[i]+res[j]-tp;
				f1=res[n-3]^res[n-2]^res[n-1]^f2^f3;
				res[n-3]=f1;
				res[n-2]=f2;
				res[n-1]=f3;
				flag=0;
				break;
			}
		}
		smallest=3-n+1;
	}
	else{
		std::vector <int> ::iterator _pos;
		int rk1=-1,rk2=-1;
		for(int i=0; i<n; ++i){
			if(i!=large3&&ask(i,large3)=='b'){
				vis[i]=1;
				res.push_back(i);
			}
		}
		//std::sort(res.begin(),res.end(),cmp_b);
		res=vt_sort(res,cmp_b);
		smallest=-res.size()+2;
		_pos=res.end();
		--_pos;
		for(int i=0; i<n; ++i){
			if(i!=*_pos&&ask(*_pos,i)=='b'){
				vis[i]=1;
				buk.push_back(i);
			}
		}
		//std::sort(buk.begin(),buk.end(),cmp_g);
		buk=vt_sort(buk,cmp_g);
		for(int i=0; i<n; ++i){
			if(!vis[i]){
				if(rk1==-1) rk1=i;
				else rk2=i;
			}
		}
		if(ask(rk1,*_pos)=='b') std::swap(rk1,rk2);
		_pos=res.insert(_pos,rk2);
		_pos=res.insert(_pos,rk1);
		_pos=res.end();
		res.insert(_pos,buk.begin(),buk.end());
	}
	for(int i=0; i<n; ++i){
		mp[res[i]]=smallest+i;
	}
	for(int i=0; i<n; ++i){
		ans.push_back(mp[i]);
	}
	return ans;
}
