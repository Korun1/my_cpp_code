#include<cstdio>
#include<algorithm>
#include<vector>
#include<string>
typedef long long LL;
using namespace std;
const int maxn = 100000 + 10;
LL inf = -1ll*maxn*maxn;
int n,node;
LL res;
vector<int>Value[maxn];
vector<int>Edge[maxn];
bool L[maxn],R[maxn];
int solve(int root){
	if (Edge[root].size() == 0) {
		return 0; //叶子节点，直接返回0
	}
	int son[2] = {inf,inf};
	for (int i=0;i<Edge[root].size();i++){
		int node_i = Edge[root][i];
		int val_i = Value[root][i];
		son[i] = solve(node_i) + val_i;
	}
	int L_value = son[0], R_value = son[1];
	int top;
	if ( L_value >= 0  && R_value >= 0 ){
		top = L_value + R_value;
		L[root] = R[root] = true;
		if ( top > res ){
			res = top;
			node = root;
		}
	}
	else if ( L_value >= 0 || R_value >= 0 ){
		if ( L_value >= 0 ){
			top = L_value;
			L[root] = true;
			if (top > res){
				res = top;
				node = root;
			}
		}
		else{
			top = R_value;
			R[root] = true;
			if (top > res){
				res = top;
				node = root;
			}
		}
	}
	else if ( L_value < 0 && R_value < 0 ){
		top = max(L_value,R_value);
		L[root] = L_value > R_value ? true : false;
		R[root] = R_value > L_value ? true : false;
		if(top > res){
			res = top;
			node = root;
		}
	}
	return max(L_value, R_value);
}
vector<int>answer;
void print_edge(int root){
	answer.push_back(root);
	for (int i=0;i<Edge[root].size();i++){
		if (i == 0 && L[root] == true){
			print_edge(Edge[root][i]);
		}
		if (i == 1 && R[root] == true){
			print_edge(Edge[root][i]);
		}
	}
}
int main()
{
	scanf("%d",&n);// 共有n个节点，默认根节点为1
	if (n == 1){
		printf("找不到路径，只有一个点\n");
		return 0;
	}
	for (int i=1;i<=n ;i++) {
		Value[i].clear();
		Edge[i].clear();
		L[i] = false;
		R[i] = false;
	}
	for (int i=1;i<=n-1;i++){ // 树的n-1条边
		int node_a,node_b,value;
		scanf("%d %d %d",&node_a,&node_b,&value);
		Edge[node_a].push_back(node_b);
		Value[node_a].push_back(value);
	}
	res = inf; // 一个负的很小的值
	solve(1);
	printf("最大路径值为: %lld\n",res);
	answer.clear();
	print_edge(node);
	printf("路径包含这些节点：\n");
	for (int i=0;i<answer.size();i++){
		printf("%d%c",answer[i],i == answer.size()-1 ? '\n' : ' ');
	}
	return 0;
}
