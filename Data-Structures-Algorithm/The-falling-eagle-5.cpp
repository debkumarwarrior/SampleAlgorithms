/*
Fatal Eagle is extremely impressed by his new acquaintance Arjit's strategies, but it has got him worried and skeptical about him. He is thinking that what if Arjit is working for Mr. XYZ and trying to kill him! Or, is his mind playing a game with him with all these conspiracy theories? If only he knew.

Lost in his thoughts, Fatal Eagle went to C8 to have a beer not realizing that drugs were already mixed in his drink by Mr. XYZ and his band of villains. Fatal Eagle ends up being so tipsy that he cannot even recognize that Arjit was the one who mixed drugs into his drink.

Now Arjit, seeing all this scene in front of him is laughing at Fatal Eagle like crazy, revealing that he is Mr. XYZ, and was planning this all along. Fatal Eagle, meanwhile is seeing N same Arjits standing in front of him. He's having difficulty in recognizing the real one among the fake images. So, he mentally assigns every Arjit a drunk quotient - and in a simpler way, he follows this particular algorithm:

He sees a sequence of N Arjits standing in a line.
He assigns every Arjit a drunk quotient.
He selects an index i at his will.
He compares ith Arjit to i+1th Arjit.
Then, he figures out that the Arjit whose value of drunk quotient is less - is NOT real.
After which, he replaces the two Arjits, ith and i+1th, by a single Arjit, which would be the one with the greater value of the drunk quotient.
Fatal Eagle loses energy equal to the maximum of the two Arjits compared.
After (n-1) such attempts by Fatal Eagle, there will be only one Arjit remaining. (Hopefully real!)
Now, you have to help Fatal Eagle in finding out the optimal way out so that he can lower the number of Arjits to save his energy. In short, he needs to reach a point where he can see the real Arjit in front of him.
*/
#include <iostream>
using namespace std;
typedef unsigned long long int ll;
#define MAX(a,b) (((a) > (b))? (a) : (b))
int main() {
	ll TC;
	cin >> TC;										// Reading input from STDIN
	while (TC--) {
	    int N;
	    cin >> N;
	    ll a = 0, b = 0;
	    ll sum = 0;
	    cin >> a;
	    for (int i = 1; i < N; i++) {
	        cin >> b;
	        sum += MAX(a,b);
	        a = b;
	    }
	    if (N== 1) {
	        sum = a;
	    }
	    cout << sum << endl;
	}
}