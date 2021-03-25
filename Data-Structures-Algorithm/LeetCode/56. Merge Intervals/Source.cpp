#include <iostream>
#include <vector>

using namespace std;

class Solution {
    bool lessThan(vector<int>& a, vector<int>& b) {
        if (a[0] < b[0]) {
            return true;
        } else if (a[0] == b[0]) {
            if (a[1] > b[1]) {
                return true;
            }
        }
        return false;
    }

    int partition(vector<vector<int>>& intervals, int start, int end) {
        auto pvt = intervals[start + (end - start)/2];
        int i = start - 1, j = end + 1;
        while (i < j) {
            i += 1;
            while (lessThan(intervals[i], pvt))
            {
                i += 1;
            }

            j-= 1;
            while (lessThan(pvt, intervals[j])) {
                j -= 1;
            }
            if (i >= j) {
                return j;
            }

            auto t = intervals[i];
            intervals[i] = intervals[j];
            intervals[j] = t;
        }
        return -1;
    }

    void qSort(vector<vector<int>>& intervals, int start, int end) {
        if (start < end) {
            int indx = partition(intervals, start, end);
            qSort(intervals, start, indx);
            qSort(intervals, indx + 1, end);
        }
    }
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() <= 0) {
            return vector<vector<int>>(0);
        }
        qSort(intervals, 0, intervals.size() - 1);
        vector<vector<int>> ans(0);
        int start = intervals[0][0], end = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= end) {
                if (intervals[i][1] > end) {
                    end = intervals[i][1];
                }
            } else {
                ans.push_back({start, end});
                start = intervals[i][0];
                end = intervals[i][1];
            }
        }
        ans.push_back({start, end});
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
        vector<vector<int>> intervals(N, vector<int>(2,0));
        for (int i = 0; i < N; i++) {
            cin >> intervals[i][0] >> intervals[i][1];
        }
        cout << "Input : [";
        for (auto interval : intervals) {
            cout << "[" << interval[0] << "," << interval[1] << "]"; 
        }
        cout << "]" << endl;

        Solution soln;
        cout << "Output : [";
        for (auto interval : soln.merge(intervals)) {
            cout << "[" << interval[0] << "," << interval[1] << "]"; 
        }
        cout << "]" << endl;
    }
    return 0;
}