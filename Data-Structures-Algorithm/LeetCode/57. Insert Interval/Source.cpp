#include <iostream>
#include <vector>
using namespace std;

class Solution {
    int isOverlap(vector<int>& a, vector<int>& b) {
        if (a[1] < b[0]) {
            return -10;
        } else if (a[0] >= b[0] && a[1] <= b[1]) {
            return 0;
        } else if (b[0] >= a[0] && b[1] <= a[1]) {
            return 0;
        } else if (a[1] >= b[0] && a[1] <= b[1]) {
            return -1;
        } else if (a[0] >= b[0] && a[0] <= b[1]) {
            return 1;
        } else {
            return 10;
        }
    }
    int min_val(int a, int b) {
        return (a < b)? a : b;
    }
    int max_val(int a, int b) {
        return (a > b)? a : b;
    }
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ans(0);
        if (intervals.size() <= 0) {
            ans.push_back(newInterval);
            return ans;
        }
        bool merged = false;
        int i = 0;
        while (i <intervals.size() 
               && isOverlap(newInterval, intervals[i]) == 10) {
            ans.push_back(intervals[i]);
            i++;
        }
        int s = newInterval[0], e = newInterval[1];
        while (i < intervals.size()
              && isOverlap(newInterval, intervals[i]) != -10) {
            s = min_val(s, intervals[i][0]);
            e = max_val(e, intervals[i][1]);
            i++;
        }
        ans.push_back({s,e});
        while (i < intervals.size() && isOverlap(newInterval, intervals[i]) == -10) {
            ans.push_back(intervals[i]);
            i++;
        }
        
        return ans;
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    int TC;
    cin >> TC;
    for (int test = 1; test <= TC; test++) {
        int N;
        cin >> N;
        vector<vector<int>> intervals(N, vector<int>(2, 0));
        for (int i = 0; i < N; i++) {
            cin >> intervals[i][0] >> intervals[i][1];
        }
        vector<int> new_interval(2,0);
        cin >> new_interval[0] >> new_interval[1];
        Solution soln;
        cout << "Exists : [";
        for (auto interval : intervals) {
            cout << "[" << interval[0] << " , " << interval[1] << "], ";
        }
        cout << "]." << endl;
        cout << "New Interval : [" << new_interval[0] << " , ";
        cout << new_interval[1] << "]" << endl;
        cout << "After Merge : [";
        for (auto interval : soln.insert(intervals, new_interval)) {
            cout << "[" << interval[0] << " , " << interval[1] << "],";
        }
        cout << "]." << endl;

    }
    return 0;
}