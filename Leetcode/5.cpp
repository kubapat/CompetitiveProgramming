class Solution {
public:
    string longestPalindrome(string s) {
        bool dp[1005][1005];
        for(int i=0; i<s.length(); i++) {
            for(int j=0; j<s.length(); j++) { 
                if(i==j) dp[i][j] = true;
                else dp[i][j] = false;
            }
        }
        
        int maxVal=0, start=0, end=0;
        for(int i=s.length()-1; i>=0; i--) {
            for(int j=i+1; j<s.length(); j++) {
                if(s[i] != s[j]) continue;
                
                if(j-i == 1 || dp[i+1][j-1]) {
                    dp[i][j] = true;
                    if(j-i > maxVal) {
                        maxVal = j-i;
                        start = i;
                        end = j;
                    }
                }
            }
        }
            
        std::string retStr = "";
        for(int i=start; i<=end; i++) retStr += s[i];
            
        return retStr;
    }
};
