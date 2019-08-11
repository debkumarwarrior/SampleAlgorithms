using namespace std;

int main() {
	//code
	int TC = 0;
	cin >> TC;
	while (TC--) {
	    int n = 0;
	    cin >> n;
	    int * ar = new int[n];
	    int * maxr = new int[n];
	    for (int i = 0 ; i < n; i++) {
	        cin >> ar[i];
	        if (i == 0) {
	            maxr[i] = ar[i];
	        } else {
	            maxr[i] = ((ar[i] + maxr[i - 1]) > ar[i])? (ar[i] + maxr[i - 1]) : ar[i];
	        }
	    }
	    int mx = maxr[0];
	    for (int i = 1; i < n; i++) {
	        mx = (mx > maxr[i])? mx : maxr[i];
	    }
	    cout << mx << endl;
	    delete[]ar;
	    delete[]maxr;
	}
	return 0;
}