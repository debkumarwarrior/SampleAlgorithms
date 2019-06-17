/*
In this problem, we define "set" is a collection of distinct numbers. For two sets  and , we define their sum set is a set . In other word,  set  contains all elements which can be represented as sum of an element in  and an element in . Given two sets , your task is to find set  of positive integers less than or equals  with maximum size such that . It is guaranteed that there is unique such set.

Input Format

The first line contains  denoting the number of elements in set , the following line contains  space-separated integers  denoting the elements of set .

The third line contains  denoting the number of elements in set , the following line contains  space-separated integers  denoting the elements of set .

Output Format

Print all elements of  in increasing order in a single line, separated by space.

*/
// Write your code here
#include <iostream>
using namespace std;
 
int main() {
    int n = 0;
    cin >> n;
    int A[101] = {0};
    
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    
    int m = 0;
    cin >> m;
    int C[101] = {0};
    
    for (int i = 0; i < m; i++) {
        cin >> C[i];
    }
 
    int B[101] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((C[j] - A[i]) >= 0) {
                B[C[j] - A[i]]++;
            }
        }
    }
    
    for (int i = 0; i < 101; i++) {
        if (B[i] == n) {
            cout << i << " ";
        }
    }
    cout << endl;
    
}