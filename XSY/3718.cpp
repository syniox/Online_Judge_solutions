#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
typedef long long lint;
const double eps=1e-12;
using namespace std;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

double calc(const vector <int> &src,double x){
	long double ans=0,w=1;
	for(int i=0; i<(int)src.size(); w*=x,++i){
		ans+=w*src[i];
	}
	return ans;
}
double qzero(const vector <int> &src,double l,double r){
	bool f=calc(src,l)<calc(src,r);
	for(int i=60; i--; ){
		double mid=(l+r)/2;
		if((calc(src,mid)<0)==f) l=mid;
		else r=mid;
	}
	return l;
}
inline bool difs(const vector <int> &src,double a,double b){
	double resa=calc(src,a),resb=calc(src,b);
	return ((resa<0)^(resb<0))||abs(resb)<eps;//abs(resa)<eps会被前面的区间计入
}

vector <double> solve(vector <int> src){
	vector <int> ds(src.size()-1);
	if(src.size()==2){
		vector <double> res;
		res.push_back((double)src[0]/-src[1]);
		return res;
	}
	for(int i=0; i<(int)ds.size(); ++i){
		ds[i]=src[i+1]*(i+1);
	}
	vector <double> res,lst=solve(ds);
	if(lst.empty()){
		if(difs(src,-1e4,1e4)) res.push_back(qzero(src,-1e4,1e4));
		return res;
	}
	if(difs(src,-1e4,lst[0])){
		res.push_back(qzero(src,-1e4,lst[0]));
	}
	lst.push_back(1e4);
	for(int i=0; i<(int)lst.size()-1; ++i){
		if(difs(src,lst[i],lst[i+1])){
			res.push_back(qzero(src,lst[i],lst[i+1]));
		}
	}
	return res;
}

int main(){
	for(int T=nxi(); T; --T){
		vector <int> vt(nxi()+1);
		for(int i=0; i<(int)vt.size(); ++i){
			vt[i]=nxi();
		}
		vector <double> ans=solve(vt);
		printf("%d\n",(int)ans.size());
		for(vector<double>::iterator it=ans.begin(); it!=ans.end(); ++it){
			printf("%.9lf\n",*it);
		}
	}
	return 0;
}
