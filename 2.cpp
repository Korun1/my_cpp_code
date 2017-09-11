#include<string>
#include<cstring>
#include<iostream>
#include<queue>
#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXSIZE = 100000 + 5;
int n,m;
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
	cin >> n >> m;
	int Increasing = n;
	makeSet(n);
	for (int i=0;i<n;i++){
		cin >> x[i] >> y[i] >> z[i];
		if (z[i] == 1){
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
	for (int i=0;i<n;i++) if(z[i] == 2)  {
		int x_father = find(x[i]);
		int y_father = find(y[i]);
		Map[ x_father ][ y[i] ] = true;
		Map[ y_father ][ x[i] ] = true;
	}
	for (int i=0;i<m;i++){
		int a,b;
		cin>>a>>b;
		int a_father = find(a);
		int b_father = find(b);
		if (a_father == b_father){
			cout<<"朋友关系"<<endl;
		}
		else if (Map[a_father][b] == true || Map[b_father][a] == true){
			cout<<"敌人关系"<<endl;
		}
		else{
			cout<<"不认识"<<endl;
		}
	}
	return 0;	
}
