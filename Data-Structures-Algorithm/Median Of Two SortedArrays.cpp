class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		if (nums1.size() < nums2.size()) {
			return medianSortedArrays(nums1, nums2);
		}
		else {
			return medianSortedArrays(nums2, nums1);
		}

	}
	inline int max(int a, int b) {
		return (a > b) ? a : b;
	}
	inline int min(int a, int b) {
		return (a < b) ? a : b;
	}
	double medianSortedArrays(vector<int>& a, vector<int>& b) {
		int lefthalfCnt = (a.size() + b.size() + 1) / 2;

		int aMinCnt = 0;
		int aMaxCnt = a.size();

		while (aMinCnt <= aMaxCnt) {
			int aCount = aMinCnt + ((aMaxCnt - aMinCnt) / 2);
			int bCount = lefthalfCnt - aCount;

			if (aCount > 0 && a[aCount - 1] > b[bCount]) {
				aMaxCnt = aCount - 1;
			} else if ((aCount < a.size()) && (b[bCount - 1] > a[aCount])) {
				aMinCnt = aCount + 1;
			} else {
				int leftHalfEnd = (aCount == 0) ? b[bCount - 1] : (bCount == 0) ? a[aCount - 1] : max(a[aCount - 1], b[bCount - 1]);
				if ((a.size() + b.size()) & 1) {
					return leftHalfEnd;
				}
				int rightHalfStart = (aCount == a.size()) ? b[bCount] : (bCount == b.size()) ? a[aCount] : min(a[aCount], b[bCount]);

				return ((double)(leftHalfEnd + rightHalfStart)) / 2.0;
			}
		}
		return 0.0;
	}
};
