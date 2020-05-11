#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
	bool dfs(int n, vector<vector<int>>& adjM, vector<bool>& hasApple, bool * visited, int u, int& edgeCnt) {
		bool bInc = hasApple[u];
		for (int v : adjM[u]) {
			bInc |= dfs(n, adjM, hasApple, visited, v, edgeCnt);
		}
		if (bInc) {
			edgeCnt += 1;
		}
		return bInc;
	}
	int dfs(int n, vector<vector<int>>& adjM, vector<bool>& hasApple) {
		bool * visited = new bool[n];
		for (int i = 0; i < n; i++) {
			visited[i] = false;
		}
		int edgeCnt = 0;
		bool bFound = dfs(n, adjM, hasApple, visited, 0, edgeCnt);

		delete[]visited;
		return (bFound)? (2 * (edgeCnt - 1)) : 0;
	}
public:
	int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
		vector<vector<int>> adjM(n);
		for (vector<int> e : edges) {
			int a = e[0], b = e[1];
			adjM[a].push_back(b);
		}
		return dfs(n, adjM, hasApple);
	}
};

int main()
{
	freopen("input.txt", "r", stdin);
	int TC;
	cin >> TC;
	Solution soln;
	for (int t = 1; t <= TC; t++) {
		int n;
		cin >> n;
		vector<vector<int>> edges(0);
		for (int i = 0; i < n - 1; i++) {
			vector<int> edge(2);
			cin >> edge[0] >> edge[1];
			edges.push_back(edge);
		}
		vector<bool> hasApple(n);
		for (int i = 0; i < n; i++) {
			int b;
			cin >> b;
			hasApple[i] = (b == 0) ? false : true;
		}

		cout << "#" << t << " " << soln.minTime(n, edges, hasApple) << endl;
	}
	return 0;
}