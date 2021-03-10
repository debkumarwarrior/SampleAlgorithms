class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int xor_expect = nums.size();
        int xor_actual = 0;
        for (int i = 0; i < nums.size(); i++) {
            xor_expect ^= i;
            xor_actual ^= nums[i];
        }
        
        return xor_actual ^ xor_expect;        
    }
};
