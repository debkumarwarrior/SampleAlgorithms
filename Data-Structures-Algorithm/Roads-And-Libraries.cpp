#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the roadsAndLibraries function below.// Complete the roadsAndLibraries function below.
long getEdgeCount(vector<vector<int>> graph, bool * visited, int n, int u);
long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
    vector<vector<int>> graph(n + 1);
    for (auto links : cities) {
        graph[links[0]].push_back(links[1]);
        graph[links[1]].push_back(links[0]);
    }

    vector<long> edgeCount;
    bool * visited = new bool[n + 1];
    for (int i = 0; i <= n; i++) {
        visited[i] = false;
    }

    for (int idx = 1; idx <= n; idx++) {
        if (visited[idx] == false) {
            long cnt = 0;
            int * queue = new int[n + 1];
            int front = 0, rear = 0;
            queue[front] = idx;
            visited[idx] = true;
            while (front <= rear) {
                int u = queue[front++];
                for (auto v : graph[u]) {
                    if (visited[v] == false) {
                        visited[v] = true;
                        cnt++;
                        queue[++rear] = v;
                    }
                }
            }
            delete[]queue;
            edgeCount.push_back(cnt);
        }
    }
    delete[]visited;

    long totCost = 0;
    for (auto cnt : edgeCount) {
        if (c_road > c_lib) {
            totCost += (cnt + 1) * c_lib;
        }
        else {
            totCost += (cnt * c_road) + c_lib;
        }
    }
    return totCost;

}
long getEdgeCount(vector<vector<int>> graph, bool * visited, int n, int u) {
    if (visited[u]) {
        return 0;
    }
    visited[u] = true;
    long cnt = 0;
    for (auto v : graph[u]) {
        if (visited[v] == false) {
            cnt += 1 + getEdgeCount(graph,visited, n, v);
        }
    }
    return cnt;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nmC_libC_road_temp;
        getline(cin, nmC_libC_road_temp);

        vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

        int n = stoi(nmC_libC_road[0]);

        int m = stoi(nmC_libC_road[1]);

        int c_lib = stoi(nmC_libC_road[2]);

        int c_road = stoi(nmC_libC_road[3]);

        vector<vector<int>> cities(m);
        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> cities[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
