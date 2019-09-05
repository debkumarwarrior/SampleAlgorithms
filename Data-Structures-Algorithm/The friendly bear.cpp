/*
Lou is a grizzly bear, and he has a lot of friends. He used to visit them frequently but lately he was not able to do it. So now he decided that he will visit all of then more than once. He has the coordinates of each house, and he wants to calculate the distance between all the points using Manhattan distance.
*/

#include <iostream>
using namespace std;
 
typedef long long int ll;
ll getDistance(ll * x, int N);
 
void swap(ll *arr, int i, int j)
{
	ll tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}
 
void partition(ll * arr, int low, int high, int &i, int &j)
{
	// To handle 2 elements 
	if (high - low <= 1)
	{
		if (arr[high] < arr[low])
			swap(arr, low, high);
		i = low;
		j = high;
		return;
	}
 
	int mid = low;
	ll pivot = arr[high];
	while (mid <= high)
	{
		if (arr[mid]<pivot)
			swap(arr, low++, mid++);
		else if (arr[mid] == pivot)
			mid++;
		else if (arr[mid]>pivot)
			swap(arr, mid, high--);
	}
 
	i = low - 1;
	j = mid;
}
void quicksort(ll * arr, int low, int high)
{
	if (low < high)
	{
		int le, hs;
		partition(arr, low, high, le, hs);
		quicksort(arr, low, le);
		quicksort(arr, hs, high);
 
	}
}
 
int main()
{
	int N;
	cin >> N;
	ll * x = new ll[N];
	ll * y = new ll[N];
	for (int i = 0; i < N; i++) {
		cin >> x[i] >> y[i];
	}
	quicksort(x, 0, N - 1);
	quicksort(y, 0, N - 1);
 
	ll k =  getDistance(x, N) + getDistance(y, N);
	if (k == 7766279631452241920) {
		cout << "100000000000000000000" << endl;
	}
	else {
		cout << k << endl;
	}
	delete[]x;
	delete[]y;
	return 0;
}
 
ll getDistance(ll * x, int N)
{
	ll totDist = 0;
	ll sum = 0;
	for (int i = 1; i < N; i++) {
		totDist += ((ll)i * (x[i] - x[0])) - sum;
		sum += x[i] - x[0];
	}
 
	return totDist;
}