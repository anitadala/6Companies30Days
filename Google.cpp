Company 5 : Google

1.  Maximum Consecutive Floors Without Special Floors

class Solution {
public:
    int maxConsecutive(int bottom, int top, vector<int>& arr) {
        int res = 0,n =arr.size() ;
        
        sort(arr.begin(),arr.end()); //sort the special floors
        
        for(int i=0;i<n;i++){
            //take diff between special floors and find maximum
            if(i==0){
                res=max(res,arr[i]-bottom);
            }
            else{
                res=max(res,arr[i]-arr[i-1]-1);
            }
        }
        
        res=max(res,top-arr[n-1]);
        
        return res;
    }
};

2.  Maximum Good People Based on Statements

class Solution {
public:
    int countBits(int mask) {
        int cnt = 0;
        while(mask) {
            cnt += mask & 1;
            mask >>= 1;
        }
        return cnt;
    }
    int isGood(int mask, int i) {
        return mask & (1 << i);
    }
    int maximumGood(vector<vector<int>>& statements) {
        int n = statements.size();
        int mask = 1 << n;
        int ans = 0;
        for(int s = mask - 1; s >= 0; --s) {
            int isValid = true;
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < n; ++j) {
                    if(isGood(s, i)) {
                        if((statements[i][j] == 0 && isGood(s, j)) || (statements[i][j] == 1 && !isGood(s, j))) {
                            isValid = false;
                            break;
                        }
                    }
                }
                if(!isValid) break;
            }
            if(isValid) {
                ans = max(ans, countBits(s));
            }
        }
        return ans;
    }
};

3.  Sort an array 

class Solution {
public:
	vector<int> sortArray(vector<int>& nums) {
		priority_queue<int, vector<int>, greater<int>>q;
		for(int i=0; i<nums.size(); i++){
			q.push(nums[i]);
		}
		vector<int>ans;
		while(!q.empty()){
			ans.push_back(q.top());
			q.pop();
		}
		return ans;
	}
};

4.  Fruit into Baskets


int totalFruit(vector<int>& fruits) {
    int right=0, left=0, fruit=0;
    unordered_map<int, int> mp;
    while(right<fruits.size()){
        if(mp.find(fruits[right])==mp.end()){
            if(mp.size()==2){
                int ind = right-1, temp = fruits[ind];
                while(ind>=0){
                    if(fruits[ind]!=temp){
                        mp.erase(fruits[ind]);
                        break;
                    }
                    ind--;
                }
                left = ind+1;
            }
            mp.insert({fruits[right], 1});
        }
        right++;
        fruit = max(fruit, right-left);
    }
    return fruit;
}

5.  Number of Closed Islands

class Solution {
public:
	bool dfs(int x, int y, vector<vector<int>>& grid){
		if(x<0 || x>=grid.size() || y<0 || y>=grid[0].size()){return false;}
		if(grid[x][y]==1){return true;}
		grid[x][y]=1;
		bool chk1=dfs(x-1, y, grid), chk2=dfs(x, y-1, grid), chk3=dfs(x+1, y, grid), chk4=dfs(x, y+1, grid);
		return (chk1 && chk2 && chk3 && chk4);
	}
	int closedIsland(vector<vector<int>>& grid) {
		vector<vector<int>>v(grid.size(), vector<int>(grid[0].size(), 0));
		int cnt=0;
		for(int i=0; i<grid.size(); i++){
			for(int j=0; j<grid[0].size(); j++){
				if(grid[i][j]==0){
					if(dfs(i, j, grid)){cnt++;}
				}
			}
		}
		return cnt;
	}
};

6.  Distinct Echo Substrings

class Solution {
public:
    long long base = 31 , mod = 1011001110001111;
    long long prev[2001];
    unordered_map<long long,int> mp;
    int distinctEchoSubstrings(string s) {
         int n = s.size();
         for(int i=1; i<=n/2; i++) {
               long long hash = 0 , limit = 1;
               int l = 0;
               for(int k=0; k<n; k++) {
                     hash = (( hash * base ) % mod  + (s[k] - 'a' + 1))%mod;
                     if(k>=i-1) {
                         prev[k]=hash;
                         if(k >= 2*i - 1 && prev[k-i]==hash) {
                              mp[hash]++;
                         }
                         hash = (hash - ((s[l] - 'a' + 1)*limit)%mod)%mod;
                         if(hash<0) hash+=mod;
                         l++;
                     }else {
                         limit =( limit * base ) % mod;
                     }
               }
         }
        return mp.size();
    }
};

7.  K divisible Array Substrings

class Solution {
public:

    int countDistinct(vector<int>& nums, int k, int p) {
        
        int n=nums.size();
        set<vector<int>>ans;
        
        int i,j;
        for(i=0;i<n;i++)
        {
            vector<int>tt;
            int ct=0;
            for(j=i;j<n;j++)
            {
                tt.push_back(nums[j]);
                if(nums[j]%p==0)
                    ++ct;
                if(ct>k)
                    break;
                ans.insert(tt);
                    
            }
        }
        return ans.size();
    }
    
};

8.  Random Pick with Weight (New Project at Google Play Services)

class Solution {
public:
    vector<int> v;
    Solution(vector<int>& w) {
        v.push_back(w[0]);
        for(int i=1;i<w.size();i++){
            v.push_back(v[i-1]+w[i]);
        }
    }
    
    int pickIndex() {
        int n= rand()%v[v.size()-1];
        auto it=upper_bound(v.begin(),v.end(),n);
        return it-v.begin();
    }
};

9.  Maximum Numbers of Coins you can get

class Solution {
public:
    int maxCoins(vector<int>& piles) {
       int l= piles.size()- (piles.size()/3); 
	   int sum=0;
        sort(piles.begin(),piles.end(),greater());
        for(int i=1;i<l;i++)
            sum+=piles[i++];
        return sum;
    }
};

10. Network Delay Time

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<int>>adj[n];
        for(int i=0; i<times.size(); i++){
            adj[times[i][0]-1].push_back({times[i][1]-1, times[i][2]});
        }
        vector<int>v(n, 1e9);
        queue<pair<int, int>>q;
        q.push({k-1, 0});
        v[k-1]=0;
        while(!q.empty()){
            int pos=q.front().first, wt=q.front().second;
            q.pop();
            for(auto it: adj[pos]){
                if(wt+it[1]<v[it[0]]){
                    v[it[0]]=it[1]+wt;
                    q.push({it[0], v[it[0]]});
                }
            }
        }
        for(int i=0; i<v.size(); i++){if(v[i]==1e9){return -1;}}
        return *max_element(v.begin(), v.end());
    }
};

11. Matrix Block Sum


#include<iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int K) {
        vector<vector<int>> prefix_sum = prefixSum(mat);
        vector<vector<int>> answer = prefix_sum;
        
        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat[0].size(); j++) {
                int upper_i = ((i+K) >= mat.size()) ? (mat.size()-1) : (i+K);
                int upper_j = ((j+K) >= mat[0].size()) ? (mat[0].size()-1) : (j+K);
                
                int lower_i = ((i-K) <= 0 ) ? 0 : (i-K);
                int lower_j = ((j-K) <= 0 ) ? 0 : (j-K);
            
                
                answer[i][j] = prefix_sum[upper_i][upper_j] - ((lower_i == 0) ? 0 : prefix_sum[lower_i-1][upper_j]) - ((lower_j == 0) ? 0 : prefix_sum[upper_i][lower_j-1]) + ((lower_i == 0) || (lower_j == 0)  ? 0 : prefix_sum[lower_i-1][lower_j-1]);
            }
        }
    
        
        return answer;
        
    }
    
    vector<vector<int>> prefixSum(vector<vector<int>>& mat) {
        vector<vector<int>> prefix_sum = mat;
        
        for (int i = 0; i < mat.size(); i++) {
            int sum = 0;
            for (int j = 0; j < mat[0].size(); j++) {
                sum = sum + mat[i][j];
                if (i > 0) {
                    prefix_sum[i][j] = sum + prefix_sum[i-1][j];
                } else {
                    prefix_sum[i][j] = sum;   
                }
            }
        }
        
        return prefix_sum;
    }

};

12. Restore IP Addresses

class Solution {
public:
    bool check(string s){
        int n=s.size();
        //if the size of string is 1 that is always possible so return true
        if(n==1){
            return true;
        }
        //if we have length >3 or string starts with 0 return false
        if(n>3||s[0]=='0'){
            return false;
        }
        //we are converting string to integer to check if it is less than equalto 255
        int val=stoi(s);
        if(val>255){
            return false;
        }
        //return true at last
        return true;
    }
    vector<string> restoreIpAddresses(string s) {
        int n=s.size();
        vector<string>ans;
        if(n>12){
            return ans;
        }
        for(int i=1;i<=3;i++){
            for(int j=1;j<=3;j++){
                for(int k=1;k<=3;k++){
                    if(i+j+k<n&&i+j+k+3>=n){
                        string a=s.substr(0,i);
                        string b=s.substr(i,j);
                        string c=s.substr(j+i,k);
                        string d=s.substr(i+j+k);
                        if(check(a)&&check(b)&&check(c)&&check(d)){
                            ans.push_back(a+"."+b+"."+c+"."+d);
                        }
                    }
                }
            }
        }
        return ans;
    }
};

13. Swim in rising Water (Jeff and the rising hat)

class Solution {
public:
    bool chk(int i, int j, int n){
        return i>=0 && i<n && j>=0 && j<n;
    }
    int swimInWater(vector<vector<int>>& grid) {
        int n=grid.size();
        vector<vector<int>>v(n, vector<int>(n, 1e9));
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>>q;
        q.push({grid[0][0], {0, 0}});
        v[0][0]=grid[0][0];
        while(!q.empty()){
            int cnt=q.top().first, x=q.top().second.first, y=q.top().second.second;
            q.pop();
            int c[4]={-1, 0, 1, 0};
            int r[4]={0, -1, 0, 1};
            for(int i=0 ;i<4; i++){
                int row=r[i]+x, col=c[i]+y;
                if(chk(row, col, n)){
                    if(cnt<grid[row][col]){
                        v[row][col]=grid[row][col];
                        q.push({v[row][col], {row, col}});
                    }
                    else if(cnt<v[row][col]){
                        v[row][col]=cnt;
                        q.push({v[row][col], {row, col}});
                    }
                }
            }
        }
        return v[n-1][n-1];
    }
};

14. Strictly Palindromic Number

class Solution {
public:
    bool palindrome(string &s){
        int p=0;
        int q=s.size()-1;
        while(p<q){
            if(s[p]==s[q]){
                p++;
                q--;
            }
            else{
                return false;
            }
        }
        
        return true;
    }
    
    bool isStrictlyPalindromic(int n) {
        for(int i=2;i<=n-2;i++){
            int p=n;
            string s;
            while(p>0){
                s.push_back(p%i);
                p/=i;
            }
            if(!palindrome(s)){
                return false;
            }
        }
        
        return true;
    }
};

15. Max Compatibility Score

class Solution {
    int used[9] = {}, ans = 0, m, n;
    void dfs(vector<vector<int>>& S, vector<vector<int>>& M, int i, int score) {
        if (i == m) {
            ans = max(ans, score);
            return;
        }
        for (int j = 0; j < m; ++j) {
            if (used[j]) continue;
            used[j] = 1;
            int s = 0;
            for (int k = 0; k < n; ++k) s += S[i][k] == M[j][k]; // calculate the compatibility score of student `i` and mentor `j`.
            dfs(S, M, i + 1, score + s);
            used[j] = 0;
        }
    }
public:
    int maxCompatibilitySum(vector<vector<int>>& S, vector<vector<int>>& M) {
        m = S.size(), n = S[0].size();
        dfs(S, M, 0, 0);
        return ans;
    }
};

