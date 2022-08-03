class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::set <int> easyFind;
        for(int i=0; i<nums.size(); i++) easyFind.insert(nums[i]);
        
        for(int i=0; i<nums.size(); i++) {
            if(easyFind.count(target-nums[i]) != 0) {
                for(int k=0; k<nums.size(); k++) {
                    if(k != i && nums[k] == target-nums[i]) return {i,k};
                }
            }
        }
        
        return {0,0};
    }
    
    
};
