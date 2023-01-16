Company 3 : Adobe
1.  Fraction to a recurring Decimal

class Solution {
public:
    string tostring(long long n){
        if (n==0)return "0";
        string ans;
        while (n>0){
            string dem;
            dem+= ((n%10)+'0');
            ans= dem+ans;
            n/=10;
        }
        return ans;
    }
    string fractionToDecimal(int num, int denom) {
        if (num==0)return "0";
        string ans;
        if ((num<0 && denom>0) || (num>0 && denom<0))ans.push_back('-');
        num= abs(num); denom= abs(denom);
        long long quotient= num/denom;
        long long remainder= num%denom;
        ans= ans+tostring(quotient);
        if (remainder==0)return ans;
        ans+='.';
        map<long long, int> mp;
        while (remainder != 0){
            if (mp.find(remainder)!= mp.end()){
                int pos= mp[remainder];
                ans.insert(pos,"(");
                ans+=')';
                break;
            }
            else {
                mp[remainder]= ans.length();
                remainder*= 10;
                quotient= remainder/denom;
                remainder= remainder%denom;
                ans+= tostring(quotient);
            }
        }
        return ans;
    }
};

2.  Increasing Triplet Sequence

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        long long a = 1e10, b = 1e10;
        for (int i : nums) {
            if (i > b) return true;
            if (i > a) b = min((long long) i, b);
            a = min((long long) i, a);
        }
        return false;
    }
};

3.  Kth smallest in Lexographical Order

class Solution {
public:
   int findKthNumber(int n, int k)
    {
        int result = 1;
        for(--k; k > 0; )
        {            int count = 0;
            for (long long first = static_cast<long long>(result), last = first + 1;
                first <= n; 
                first *= 10, last *= 10) 
            {
                count += static_cast<int>((min(n + 1LL, last) - first)); 
            }
            
            if (k >= count)
            {   
                ++result;
                k -= count;
            }
            else
            {   
                result *= 10;
                --k;
            }
        }
        return result;
    }
};

4.  Magical String

class Solution {
public:
    int magicalString(int n) {
        if(n <= 2) return 1;

        string s = "122";
        int i = 2,end=2;
        while(s.size() < n){
            if(s[i] == '1'){
                if(s[end]=='2'){
                    s.push_back('1');
                }
                else{
                    s.push_back('2');
                }
            }
            else{
                if(s[end]=='2'){
                   s += "11";
                }
                else{
                    s += "22";
                }
            }

            i++;
            end = s.size() - 1;
        }

        int ans = 0;
        for(int i=0;i<n;i++){
            if(s[i]=='1') ans++;
        }

        return ans;
    }
};

5.  Non Negative Integers without consecutive ones

int findIntegers(int num) {
    static int fb[31] = { 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946,
        17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578 };
    if (num < 3) return num + 1;
    for (int bt = 29; bt >= 0; --bt) 
        if (num & (1 << bt)) return num & (1 << (bt - 1)) ? fb[bt] : fb[bt - 1] + findIntegers((num & ~(1 << bt)));
}

6.  Knight in a Chessboard

class Solution {
public:
    double knightProbability(int n, int k, int row, int col) 
    {
        vector<vector<vector<double>>> dp(k + 1, vector<vector<double>> (n, vector<double>(n, -1)));
        return solve(n, k, row, col, dp);
    }
    
private:
    double solve(int n, int k, int row, int col, vector<vector<vector<double>>>& dp)
    {
        if (row < 0 || row >= n || col < 0 || col >= n) return 0;
        if (k == 0) return 1;
        
        if (dp[k][row][col] != -1)
            return dp[k][row][col];
        
        double total = solve(n, k - 1, row - 2, col + 1, dp) + solve(n, k - 1, row - 1, col + 2, dp)
                    + solve(n, k - 1, row + 1, col + 2, dp) + solve(n, k - 1, row + 2, col + 1, dp)
                    + solve(n, k - 1, row + 2, col - 1, dp) + solve(n, k - 1, row + 1, col - 2, dp)
                    + solve(n, k - 1, row - 1, col - 2, dp) + solve(n, k - 1, row - 2, col - 1, dp);
            
        total = total / 8;
        return dp[k][row][col] = total;
    }
};

7.  Matching Subsequences

class Solution {
public:
    bool isSubsequence(string s1, string s2, int m, int n){
        int j = 0;
        for(int i = 0; i < m && j < n; i++){
            if(s1[i] == s2[j]) j++;
        }
        return j == n;
    }
    int numMatchingSubseq(string s, vector<string>& words) {
        int count = 0;
        map<string, bool> mp;
        for(auto x: words){
            if(mp.find(x) != mp.end()) {
                if(mp[x] == true) {
                    count++;
                }
                continue;
            }
            mp[x] = isSubsequence(s, x, s.size(), x.size());
            count += (mp[x] == true);
        }
        return count;
    }
};

8.  Genetic Mutation

class Solution 
{
public:
    int minMutation(string start, string end, vector<string>& bank) 
    {
        deque<pair<string,int>> q({{start,0}});
        set<string> b(bank.begin(), bank.end());
        vector<char> nucleotides = {'A', 'T', 'G', 'C'};
        
        while (!q.empty())
        {
            auto [g, m] = q.front(); q.pop_front();
            if (g == end) return m;
            
            for (int i = 0; i < g.size(); ++i)
                for (char n : nucleotides)
                {
                    string gm = g; gm[i] = n;
                    if (b.count(gm))
                    {
                        b.erase(gm);
                        q.emplace_back(gm, m+1);
                    }
                }
        }
        
        return -1;
    }
};

9.  Count  nodes equal to average of Subtree

int count=0;
pair<int,int> valueSum(TreeNode* root){
	if(root==NULL) return {0,0};
	auto left=valueSum(root->left);
	auto right=valueSum(root->right);
	int sum=(left.first+right.first+root->val);
	int n=(left.second+right.second+1);        
	count+=((sum/n)==root->val);
	return {sum,n};
}
int averageOfSubtree(TreeNode* root) {
	auto p1=valueSum(root);
	return count;
}

10. Max matrix Sum

class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long mn = INT_MAX, cnt = 0, sum = 0;
        for(auto r : matrix) {
            for(int i : r) {
                if(i < 0) cnt++;
                mn = min(mn, (long long)abs(i));
                sum += abs(i);
            }
        }
        return cnt % 2 ? sum - 2 * mn : sum;
    }
};

11. Stock Price Fluctuation

class StockPrice {
    map<int, int> stock; 
    map<int, int> prices;
    pair<int, int> currentStock = {-1, -1};
public:    
    StockPrice() {
        
    }    
    void update(int timestamp, int price) {
        if(timestamp >= currentStock.first) {
            currentStock = {timestamp, price};
        }
        
        if(stock.find(timestamp) != stock.end()) {
			
            int old_price = stock[timestamp]; 
            
            prices[old_price]--;  
            if(prices[old_price] == 0) prices.erase(old_price); 
        }
        prices[price]++;  
        stocks[timestamp] = price;        
    }
    int current() {
        return currentStock.second;
    }
    int maximum() {
			return prices.rbegin()->first;  
    }
    int minimum() {
        return prices.begin()->first; 
    }
};

12. Shortest Unsorted Continuous Subarray
13. Game of Dungeon

class Solution {
public:
    int calculateMinimumHP(vector<vector<int> > &dungeon) {
        int M = dungeon.size();
        int N = dungeon[0].size();
        vector<vector<int> > hp(M + 1, vector<int>(N + 1, INT_MAX));
        hp[M][N - 1] = 1;
        hp[M - 1][N] = 1;
        for (int i = M - 1; i >= 0; i--) {
            for (int j = N - 1; j >= 0; j--) {
                int need = min(hp[i + 1][j], hp[i][j + 1]) - dungeon[i][j];
                hp[i][j] = need <= 0 ? 1 : need;
            }
        }
        return hp[0][0];
    }
};

14. People aware of secret

class Solution {
public:
    long dp[1001];
    long m=1e9+7;
    int peopleAwareOfSecret(int n, int delay, int forget) {
        memset(dp,-1,sizeof(dp));
        return helper(1,n,delay,forget);
    }
    long helper(int day,int &n,int &delay,int &forget){
        if(dp[day]!=-1)
            return dp[day];
        long ans=0;
        ans++;
        if(day+forget<=n)
            ans--;
        for(int start=day+delay;start<(min(day+forget,n+1));start++){
            ans+=helper(start,n,delay,forget);
            ans%=m;
        }
        dp[day]=ans;
        return ans;
        
    }
};

15. Kth smallest Trimmed number

class Solution {
public:
    vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& queries) {
        vector<int> res;
        for(auto x:queries)
        {
            priority_queue<pair<string,int>> v;
            for(int i=0;i<nums.size();i++)
            {
                int t=nums[i].length()-x[1];
                string p=nums[i].substr(t,x[1]);
                if(v.size()<x[0])
                    v.push({p,i});
                else
                {
                    if(v.top().first > p)
                    {
                        v.pop();
                        v.push({p,i});
                    }
                }
            }
            int val=v.top().second;
            res.push_back(val);
        }
        return res;
    }
};