#include <iostream>
using namespace std;

class Solution {
    void rotateMatrix(int ** arr, int rs, int re, int cs, int ce, int offset);
    friend void print(int ** arr, int N, int M);
public:
    void rotateMatrix(int ** arr, int N, int M, int offset);
};

void Solution::rotateMatrix(int ** arr, int rs, int re, int cs, int ce, int offset)
{
    int T = 2 * ((re - rs + 1) + (ce - cs + 1)) - 4;
    int * elements = new int[T];
    int idx = 0;

    for (int i = cs; i <= ce; i++) {
        elements[idx] = arr[rs][i];
        idx++;
    }
    for (int i = rs + 1; i <= re - 1; i++) {
        elements[idx] = arr[i][ce];
        idx++;
    }
    for (int i = ce; i >= cs; i--) {
        elements[idx] = arr[re][i];
        idx++;
    }
    for (int i = re - 1; i >= rs + 1; i--) {
        elements[idx] = arr[i][cs];
        idx++;
    }
    /****** Feed ended *******/
    idx = offset;
    for (int i = cs; i <= ce; i++) {
        arr[rs][i] = elements[idx % T];
        idx++;
    }
    for (int i = rs + 1; i <= re - 1; i++) {
        arr[i][ce] = elements[idx % T];
        idx++;
    }
    for (int i = ce; i >= cs; i--) {
        arr[re][i] = elements[idx % T];
        idx++;
    }
    for (int i = re - 1; i >= rs + 1; i--) {
        arr[i][cs] = elements[idx % T];
        idx++;
    }
    delete[]elements;
}

void Solution::rotateMatrix(int ** arr, int N, int M, int offset)
{
    int rs = 0, re = N - 1, cs = 0, ce = M - 1;
    while (rs <= re && cs <= ce) {
        rotateMatrix(arr, rs, re, cs, ce, offset);
        rs += 1, re -= 1;
        cs += 1, ce -= 1;
    }
}

void print(int ** arr, int N, int M)
{    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
int main()
{
    Solution soln;
    int N, M;
    cin >> N >> M;
    int offset;
    cin >> offset;
    int ** arr = new int*[N];
    for (int i = 0; i < N; i++) {
        arr[i] = new int[M];
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
        }
    }
    soln.rotateMatrix(arr, N, M, offset);
    print(arr, N, M);
    for (int i = 0; i < N; i++) {
        delete[]arr[i];
    }
    delete[]arr;
    return 0;
}

