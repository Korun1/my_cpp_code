#include<string>
#include<cstring>
#include<iostream>
#include<queue>
#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXSIZE = 100000 + 5;
int n,m,Q;
int x[MAXSIZE],y[MAXSIZE],z[MAXSIZE];
int uset[MAXSIZE];  
  
void makeSet(int size) {  
    for(int i = 1;i <= size*2 ;i++)  uset[i] = i;  
}  
  
int find(int x) {  
    if (x != uset[x]) uset[x] = find(uset[x]);  
    return uset[x];  
}
map<int,bool>Map[MAXSIZE<<1];  

int main()
{
	cin >> n >> m >> Q; //n个人， m对关系，Q个询问
	int Increasing = n+1;
	makeSet(n);
	for (int i=0;i<m;i++){
		cin >> x[i] >> y[i] >> z[i];
		if (z[i] == 1){ 
			// 先把所有的朋友关系划分成不同的圈子，一共有n个点,每出现一对朋友关系，
			// 只要这两个人之前都没有划分圈子，那么新增一个圈子，代表这两个人的圈子；
			// 只有这两个人任一已经属于某个圈子，那么只需把另一个人合并入这个圈子;
			// 若两个人属于不同的圈子，那么把这两个圈子合并。
			int x_father = find(x[i]);
			int y_father = find(y[i]);
			if (x_father == x[i] && y_father == y[i] ){
				uset[ x[i] ] = uset[ y[i] ]  = Increasing;
				uset[ Increasing ] = Increasing;
				Increasing += 1;
			}
			else if ( x_father == x[i] || y_father == y[i] ){
				if ( x_father == x[i] ){
					uset[ x_father ] = y_father;
				}
				else{
					uset[ y_father ] = x_father;
				}
			}
			else if ( x_father != x[i] || y_father != y[i]  ){
				if ( x_father == y_father ){
					continue;		
				}
				else{
					uset[x_father] = y_father;
				}
			}
		}
	}
	for (int i=0;i<m;i++) if(z[i] == 2)  {
		// 敌人关系，把他们的圈子标记为敌人状态
		int x_father = find(x[i]);
		int y_father = find(y[i]);
		Map[ x_father ][ y[i] ] = true;
		Map[ y_father ][ x[i] ] = true;
	}
	for (int i=0;i<Q;i++){
		int a,b;
		cin>>a>>b;
		int a_father = find(a);
		int b_father = find(b);
		if (a_father == b_father){
			// 首先查询是否同一个圈子，判断是否朋友关系
			cout<<"朋友关系"<<endl;
		}
		else if (Map[a_father][b] == true || Map[b_father][a] == true){
			// 判断是否敌人关系
			cout<<"敌人关系"<<endl;
		}
		else{
			// 第三种关系
			cout<<"不认识"<<endl;
		}
	}
	return 0;	
}
