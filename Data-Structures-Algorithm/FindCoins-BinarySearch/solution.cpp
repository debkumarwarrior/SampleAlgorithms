//#include<iostream>
//using namespace std;

typedef struct Result {
	int tenIndex;
	int thirtyIndex;
}Result;

extern int weigh(int leftNum, int * left, int rightNum, int * right);
int split_even(int N, int * left, int * right, int & leftNum, int & rightNum);
int split_odd(int N, int * left, int * right, int & leftNum, int & rightNum, Result & ans);
int findTenIdx(int * arr, int N);
int findThirtyIdx(int * arr, int N);

Result findCoins(int N)
{
	Result answer;

	int * left = new int[N + 1];
	int * right = new int[N + 1];
	
	int leftNum = 0;
	int rightNum = 0;

	int res = 0;
	if (N & 1)
	{
		res = split_odd(N, left, right, leftNum, rightNum, answer);
	}
	else
	{
		res = split_even(N, left, right, leftNum, rightNum);
	}

	/*for (int i = 1; i <= leftNum; i++) {
		cout << left[i] << " ";
	}
	cout << endl;
	*/
	if (res == -1)
	{
		answer.tenIndex = findTenIdx(left, leftNum);
		answer.thirtyIndex = findThirtyIdx(right, rightNum);
	}
	if (res == 1)
	{
		answer.tenIndex = findTenIdx(right, rightNum);
		answer.thirtyIndex = findThirtyIdx(left, leftNum);
	}
	delete[]left;
	delete[]right;

	
	return answer;
}

int split_odd(int N, int * left, int * right, int & leftNum, int & rightNum, Result & ans)
{
	left[1] = (N / 2) + 1;
	leftNum = 1;

	right[1] = N;
	rightNum = 1;

	int res2 = weigh(leftNum, left, rightNum, right);
	if (res2 == 0)
	{
		leftNum = 0;
		rightNum = 0;
		return split_even(N - 1, left, right, leftNum, rightNum);
	}

	left[1] = 1;
	leftNum = 1;

	right[1] = N;
	rightNum = 1;

	int res3 = weigh(leftNum, left, rightNum, right);
	if (res3 == 0)
	{
		leftNum = 0;
		rightNum = 0;
		return split_even(N - 1, left, right, leftNum, rightNum);
	}

	left[1] = 1;
	leftNum = 1;

	right[1] = (N / 2) + 1;
	rightNum = 1;

	int res1 = weigh(leftNum, left, rightNum, right);
	if (res1 == 0)
	{
		if (res2 == -1)
		{
			ans.thirtyIndex = N;
			int * a = new int[N + 1];
			for (int i = 1; i <= N - 1; i++) {
				a[i] = i;
			}
			return findTenIdx(a, N - 1);

		}
		if (res2 == 1)
		{
			ans.tenIndex = N;
			int * a = new int[N + 1];
			for (int i = 1; i <= N - 1; i++) {
				a[i] = i;
			}
			return findThirtyIdx(a, N - 1);

		}
	}

	if ((res1 == -1) && (res2 == -1) && (res3 == -1)) {
		ans.tenIndex = 1;
		ans.thirtyIndex = N;
	}
	if ((res1 == -1) && (res2 == 1) && (res3 == -1)) {
		ans.tenIndex = 1;
		ans.thirtyIndex = (N / 2) + 1;
	}
	if ((res1 == 1) && (res2 == -1) && (res3 == -1)) {
		ans.tenIndex = (N / 2) + 1;
		ans.thirtyIndex = N;
	}
	if ((res1 == -1) && (res2 == 1) && (res3 == 1)) {
		ans.tenIndex = N;
		ans.thirtyIndex = (N / 2) + 1;
	}
	if ((res1 == 1) && (res2 == -1) && (res3 == -1)) {
		ans.tenIndex = (N / 2) + 1;
		ans.thirtyIndex = 1;
	}
	if ((res1 == 1) && (res2 == 1) && (res3 == 1)) {
		ans.tenIndex = N;
		ans.thirtyIndex = 1;
	}

	return 0;
}

int split_even(int N, int * left, int * right, int & leftNum, int & rightNum)
{
	int * idx = new int[N + 1];
	int * perm = new int[N + 1];

	for (int i = 1; i <= N; i++) {
		idx[i] = i;
		perm[i] = i;
	}

	int offset = 1;
	int res = 0;
	while (true)
	{
		for (int i = 1, j = N; i < j; i++, j--)
		{
			left[i] = perm[i];
			leftNum++;

			right[i] = perm[j];
			rightNum++;
		}

		res = weigh(leftNum, left, rightNum, right);
		if (res != 0)
		{
			break;
		}

		for (int i = 1, j = N; i < j; i++, j--)
		{
			if ((((i - 1) / offset) % 2) == 0)
			{
				perm[i] = idx[i];
				perm[j] = idx[j];
			}
			else
			{
				perm[i] = idx[j];
				perm[j] = idx[i];
			}
		}
		offset += 1;
		leftNum = 0;
		rightNum = 0;
	}

	delete[]idx;
	delete[]perm;

	return res;
}

int findTenIdx(int * arr, int N)
{
	//cout << arr[N] << endl;
	if (N == 1) {
		return arr[N];
	}
	int * left = new int[N + 1];
	int leftNum = 0;

	int * right = new int[N + 1];
	int rightNum = 0;

	for (int i = 1, j = N; i < j; i++, j--) {
		left[i] = arr[i];
		leftNum++;

		right[i] = arr[j];
		rightNum++;
	}

	int res = weigh(leftNum, left, rightNum, right);
	int ret = -1;
	if (res == 0) {
		ret = arr[(N / 2) + 1];
	}

	if (res == -1) {
		ret = findTenIdx(left, leftNum);
	}

	if (res == 1) {
		ret = findTenIdx(right, rightNum);
	}
	delete[]left;
	delete[]right;
	return ret;
}

int findThirtyIdx(int * arr, int N)
{
	if (N == 1) {
		return arr[N];
	}
	int * left = new int[N + 1];
	int leftNum = 0;

	int * right = new int[N + 1];
	int rightNum = 0;

	for (int i = 1, j = N; i < j; i++, j--) {
		left[i] = arr[i];
		leftNum++;

		right[i] = arr[j];
		rightNum++;
	}

	int res = weigh(leftNum, left, rightNum, right);
	if (res == 0) {
		delete[]left;
		delete[]right;
		return arr[(N / 2) + 1];
	}
	int ret = -1;
	if (res == 1) {
		ret = findThirtyIdx(left, leftNum);
	}

	if (res == -1) {
		ret = findThirtyIdx(right, rightNum);
	}
	delete[]left;
	delete[]right;
	return ret;
}