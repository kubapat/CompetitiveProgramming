class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        std::vector <int> result;
        int i=0, j=0;
        while(i<nums1.size() && j<nums2.size()) {
            if(nums1[i] <= nums2[j]) result.push_back(nums1[i++]);
            else result.push_back(nums2[j++]);
        }
        
        if(i<nums1.size()) while(i<nums1.size()) result.push_back(nums1[i++]);
        else if(j<nums2.size()) while(j<nums2.size()) result.push_back(nums2[j++]);
        
        double finalScore = ((int)result.size()%2 == 0) ? ((double)result[result.size()/2 - 1]+(double)result[result.size()/2])/2 : (double)result[result.size()/2];
        
        
        return finalScore;
    }
};
