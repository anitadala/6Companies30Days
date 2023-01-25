Company 4 : Flipkart
1. Partition to K Equal Sum Subsets

class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        sum = accumulate(nums.begin(), nums.end(), sum);
        if (nums.size() < k || sum % k) return false;
        
        vector<int>visited(nums.size(), false);
        return backtrack(nums, visited, sum / k, 0, 0, k);
    }
    
    bool backtrack(vector<int>& nums,vector<int>visited, int target, int curr_sum, int i, int k) {
        if (k == 1) 
            return true;
        
        if (curr_sum == target) 
            return backtrack(nums, visited, target, 0, 0, k-1);
        
        for (int j = i; j < nums.size(); j++) {
            if (visited[j] || curr_sum + nums[j] > target) continue;
            
            visited[j] = true;
            if (backtrack(nums, visited, target, curr_sum + nums[j], j+1, k)) return true;
            visited[j] = false;
        }
        
        return false;
    }
};

2. Sale and Offers at Flipkart BBD

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

3. Remove Zero Sum Consecutive Nodes

class Solution {
public:
    int findKthNumber(int n, int k) {
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

4. Winner of the Game

class Solution {
    public int solve(int n,int k){
        if(n==1){
            return 0;
        }
        return (solve(n-1,k)+k)%n;
    }
    public int findTheWinner(int n, int k) {
        int ans=solve(n,k);
        return ans+1;
        
    }
}

5. Finding the Mountain Array

    int findInMountainArray(int target, MountainArray &mountainArr) {
        int l=0;
        int n,h;
        n=h=mountainArr.length()-1;
        int peak;
        int ans=INT_MAX;
        while(l<h)
        {
            int mid=(l+h)/2;
            int val=mountainArr.get(mid);
            if(mountainArr.get(mid) < mountainArr.get(mid+1)) l=mid+1;
            else h=mid;
        }
        peak=l;
        if(mountainArr.get(peak) == target) return peak;
        
        //finding target in left part of peak
        l=0;
        h=peak;
        while(l<=h)
        {
            int mid=(l+h)/2;
            int val=mountainArr.get(mid);
            if(val == target){
                ans=min(ans,mid);
                break;
            }
            else if(val < target) l=mid+1;
            else h=mid-1;
        }
        if(ans!=INT_MAX) return ans;
        
        
        //if we did not find out peak in left part so now
        //finding target in right part of peak
        l=peak+1;
        h=n;        
        while(l<=h)
        {
            int mid=(l+h)/2;
            cout<<mid<<endl;
            int val=mountainArr.get(mid);
            if(val == target){
                ans=min(ans,mid);
                break;
            }
            else if(val > target) l=mid+1;
            else h=mid-1;
        }
        if(ans!=INT_MAX) return ans;
        return -1;
        
    }

6. Number of ways to separate Numbers
 class Solution {
public:
    int numberOfCombinations(string num) {
        if (num[0] == '0') return 0;
        long N = num.size(), ans = 0, mod = 1e9 + 7;
        vector<vector<long>> lcp(N + 1, vector<long>(N + 1)), dp(N + 1, vector<long>(N + 1));
        for (int i = N - 1; i >= 0; --i) {
            for (int j = N - 1; j >= 0; --j) {
                if (num[i] == num[j]) lcp[i][j] = lcp[i + 1][j + 1] + 1;
            }
        }
        auto le = [&](int k, int i, int j) {
            int len = lcp[k][i];
            return len >= j + 1 - i || num[k + len] < num[i + len];
        };
        for (int j = 0; j < N; ++j) dp[0][j] = 1;
        for (int i = 1; i < N; ++i) {
            if (num[i] == '0') continue;
            for (int j = i, k = i - 1, sum = 0; j < N; ++j) {
                dp[i][j] = sum; // case 1
                if (k < 0) continue; // if k < 0, case 2 (equal length) is invalid but we still need to continue to handle case 1, so we should use `continue` here.
                if (num[k] > '0' && le(k, i, j)) dp[i][j] = (dp[i][j] + dp[k][i - 1]) % mod; // case 2
                sum = (sum + dp[k][i - 1]) % mod; // update the sum used in case 1.
                --k;
            }
        }
        for (int i = 0; i < N; ++i) ans = (ans + dp[i][N - 1]) % mod;
        return ans;
    }
};

7. City With the Smallest Number of Neighbors at a Threshold Distance

    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> dis(n, vector(n, 10001));
        int res = 0, smallest = n;
        for (auto& e : edges)
            dis[e[0]][e[1]] = dis[e[1]][e[0]] = e[2];
        for (int i = 0; i < n; ++i)
            dis[i][i] = 0;
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < n; ++j)
                if (dis[i][j] <= distanceThreshold)
                    ++count;
            if (count <= smallest) {
                res = i;
                smallest = count;
            }
        }
        return res;
    }

8. Closest Primes in Range

class Solution {
public:
    vector<int>ans;
    void fillPrimes(vector<int>& prime, int high)
    {
        bool ck[high + 1];
        memset(ck, true, sizeof(ck));
        ck[1] = false;
        ck[0] = false;
        for (int i = 2; (i * i) <= high; i++) {
            if (ck[i] == true) {
                for (int j = i * i; j <= sqrt(high); j = j + i) {
                    ck[j] = false;
                }
            }
        }
        for (int i = 2; i * i <= high; i++) {
            if (ck[i] == true) {
                prime.push_back(i);
            }
        }
    }
    void segmentedSieve(int low, int high)
    {
        if (low<2 and high>=2){
            low = 2;
        }
        bool prime[high - low + 1];

        memset(prime, true, sizeof(prime));

        vector<int> chprime;
        fillPrimes(chprime, high);

        for (int i : chprime) {
            int lower = (low / i);

            if (lower <= 1) {
                lower = i + i;
            }
            else if (low % i) {
                lower = (lower * i) + i;
            }
            else {
                lower = (lower * i);
            }
            for (int j = lower; j <= high; j = j + i) {
                prime[j - low] = false;
            }
        }

        for (int i = low; i <= high; i++) {
            if (prime[i - low] == true) {
                ans.push_back(i);
            }
        }
    }
    vector<int> closestPrimes(int left, int right) {
        segmentedSieve(left,right);
        sort(ans.begin(),ans.end());
        int mini=INT_MAX;
        vector<int>arr(2);
        for(int i=1;i<ans.size();i++)
        {
            if(ans[i]-ans[i-1]<mini)
            {
                mini=ans[i]-ans[i-1];
                arr={ans[i-1],ans[i]};
            }
        }
        if(ans.size()<2) return {-1,-1};
        return arr;
    }
};

9. Top K frequent Words

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
       unordered_map<string,int> dict;
        for(const string& s:words) dict[s]++;
        
        priority_queue<pair<string,int>, vector<pair<string,int>>, Comp> pq;
        for(const auto& pa:dict) {
            pq.push(pa);
            if(pq.size()>k) pq.pop();
        }    
        
        vector<string> result;
        while(!pq.empty()) {
            result.push_back(pq.top().first);
            pq.pop();
        }
        reverse(result.begin(),result.end());    
        return result;    
    }
private:
    struct Comp {
        Comp() {}
        ~Comp() {}
        bool operator()(const pair<string,int>& a, const pair<string,int>& b) {
            return a.second>b.second || (a.second==b.second && a.first<b.first);
        }
    };
};

10. Distant Barcodes

class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& bar) {
        unordered_map<int, int> m;
        for(int i : bar) m[i]++;
        
        vector<pair<int, int>> v;
        for(auto i : m) v.push_back({i.second, i.first});
        
        sort(v.begin(), v.end(), greater<pair<int, int>>());
        
        vector<int> ans(bar.size()), temp;
        for(auto p : v) {
            for(int i=0; i<p.first; i++) temp.push_back(p.second);
        }
        
        int k = 0;
        for(int i=0; i<bar.size(); i+=2) ans[i] = temp[k++];
        for(int i=1; i<bar.size(); i+=2) ans[i] = temp[k++];
        
        return ans;
    }
};

11. The new game to Play

class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        if(k==0 || n>=k+maxPts-1)
            return (double) 1;
        vector<double> dp(n+1);
        dp[0]=1;
        double sum = 0;
        for(int i=0; i<n; i++)
        {
            if(i<k)
                sum+=dp[i];  
            if(i>=maxPts)
                sum-=dp[i-maxPts];
                
            dp[i+1] = sum/maxPts;
        }
        double ret = 0;
        for(int i=k; i<=n; i++)
            ret+=dp[i];
        return ret;
    }
};

12. Check If a String Contains All Binary Codes of Size K

bool hasAllCodes(string str, int k) {
    int total = 1<<k;
    int oner = total-1;
    int curr = 0;
    unordered_set<int>s;
    
    for(int i=0;i<str.size();i++)
    {
        curr = (((curr<<1)&oner)|(str[i]-'0'));
        if(i>=k-1)
            s.insert(curr);
    }
    
    return (s.size()==total);
}

13. Max Area of Island



14. Custom String Sorting

class Solution { 
public:
    string customSortString(string order, string str) {
        int cnt[128] = {};
        for (char c : str) ++cnt[c];
        int i = 0;
        for (char c : order) {
            while (cnt[c] > 0) {
                str[i++] = c;
                --cnt[c];
            }
        }
        for (char c = 'a'; c <= 'z'; ++c) {
            while (cnt[c] > 0) {
                str[i++] = c;
                --cnt[c];
            }
        }
        return str;
    }
};

15. House Robber - Very Imp.

class Solution {
public:
    int tryRob(TreeNode* root, int& l, int& r) {
        if (!root)
            return 0;
            
        int ll = 0, lr = 0, rl = 0, rr = 0;
        l = tryRob(root->left, ll, lr);
        r = tryRob(root->right, rl, rr);
        
        return max(root->val + ll + lr + rl + rr, l + r);
    }

    int rob(TreeNode* root) {
        int l, r;
        return tryRob(root, l, r);
    }
};
