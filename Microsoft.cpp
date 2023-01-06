1. You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.


class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int>stk;
        for(int i=0;i<tokens.size();i++){
            if(tokens[i]=="+"||tokens[i]=="-"||tokens[i]=="*"||tokens[i]=="/"){
                int n1= stk.top();
                stk.pop();
                int n2 = stk.top();
                stk.pop();
                if(tokens[i]=="+"){
                    int num = n1 + n2;
                    stk.push(num);
                }
                else if(tokens[i]=="-"){
                    int num = n2 - n1;
                    stk.push(num);
                }
                else if(tokens[i]=="*"){
                    int num = n2 * n1;
                    stk.push(num);
                }
                else if(tokens[i]=="/"){
                    int num = n2 / n1;
                    stk.push(num);
                }
            }
            else{
                stk.push(stoi(tokens[i]));
            }
        }
        return stk.top();
    }
};

2. Combination Sum with a twist.

class Solution {
public:
    vector<vector<int>> ans;
    void f(int i,vector<int> &nums,vector<int> &ds,int tar,int k)
    {
        if(i>=nums.size())
        {
            if(ds.size()==k and tar==0)
            {
                ans.push_back(ds);
            }
            return;
        }
        if(nums[i]<=tar)
        {
            ds.push_back(nums[i]);
            f(i+1,nums,ds,tar-nums[i],k);
            ds.pop_back();
        }
        f(i+1,nums,ds,tar,k);
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> nums;
        vector<int> ds;
       for(int i=1;i<=9;i++)
       {
           nums.push_back(i);
       }
        f(0,nums,ds,n,k);
        return ans;
    }
};

3. Bulls and Cows

class Solution {
public:
       int pairs(string str1, string str2, int size){
        
        int f1[11] = { 0 };
        int f2[11] = { 0 };
        int i, c = 0;
		
        for (i = 0; i < size; i++)
          f1[str1[i] - '0']++;
        
        for (i = 0; i < size; i++)
          f2[str2[i] - '0']++;
        for (i = 0; i < 11; i++)
          c += (min(f1[i], f2[i]));
        
        return c;
    }
    string getHint(string secret, string guess) {
        int a=0,b,n = secret.size();
        b=pairs(secret,guess,n);  
        for(int i=0;i<n;i++) 
            if(secret[i]==guess[i])
                a++;
        string res=to_string(a)+'A'+to_string(b-a)+'B'; 
        return res;
    }
};

4. You are given an integer array nums of length n. Return maximum length of Rotation Function.

int sum=0, sum1=0, ans=0;
        for(int i=0; i<nums.size(); i++){
            sum+=nums[i];
            sum1+=(i*nums[i]);
        }
        ans=sum1;
        for(int i=nums.size()-1; i>=0; i--){
            sum1+=sum-(nums[i]*nums.size());
            ans=max(ans, sum1);
        }
return ans;

5. Largest Divisible Subset.

vector<int>dp(nums.size(),1);
        sort(nums.begin(),nums.end());
        for(int i=1;i<nums.size();i++){
            for(int j=0;j<i;j++){
                if(nums[i]%nums[j]==0) dp[i]=max(dp[i],1+dp[j]);
            }
        }
        int val=0;
        for(int i=0;i<dp.size();i++) if(val<dp[i]) val=dp[i];
        vector<int>v;
        for(int i=dp.size()-1;i>-1;i--){
            if(val==dp[i] and (!v.size() or v[v.size()-1]%nums[i]==0)){
                v.push_back(nums[i]);
                val--;
            }
        }
return v;}

6. How to find a perfect Rectangle.
 
 bool isRectangleCover(vector<vector<int>>& rectangles) {
    int n = rectangles.size();

    if (n == 1) return true;

    // maps all points to a respective calculation. If it is a valid rectangle,
    // all interior points should have count 0, bootom left most and top right
    // most point should have value 1, and top left and bottom right should have
    // count -1. If it is different than this, it is not a perfect rectangle.
    map<pair<int, int>, int> pointCounts;

    for (auto& rect : rectangles) {
      pointCounts[{rect[0], rect[1]}]++;
      pointCounts[{rect[2], rect[3]}]++;
      pointCounts[{rect[0], rect[3]}]--;
      pointCounts[{rect[2], rect[1]}]--;
    }

    int numMarks = 0;

    for (auto it = pointCounts.begin(); it != pointCounts.end(); it++) {
      if (it->second != 0) {
        if (abs(it->second) != 1) return false;

        numMarks++;
      }
    }

    return numMarks == 4;
  }
  
7. Scheduling a Course.

   bool iscycle(vector<int> adj[],vector<int> &vis,int id){
        if(vis[id]==1)
            return true;
        if(vis[id]==0){
            vis[id]=1;
            for(auto edge : adj[id]){
                if(iscycle(adj,vis,edge))
                    return true;
            }
        }
        vis[id] = 2;
        return false;
    }
    bool canFinish(int n, vector<vector<int>>& prq) {
        vector<int>vis(n,0);
        vector<int>adj[n];
        for(auto it:prq){
            //adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
       for(int i =0;i<n;i++){
           if(!vis[i]){
               if(iscycle(adj,vis,i))
                   return false;
           }
       } 
    
    return true;
    }

8. Profitable Path in a Tree.

class Solution {
public:
    void AliceDfs(int node,int par,int dis,vector<int> &parent,
                  vector<int> &distance, vector<int> adj[])
    {
        parent[node]=par;
        distance[node]=dis;
        for(auto it : adj[node])
        {
            if(it!=par) AliceDfs(it,node,dis+1,parent,distance,adj);
        }
    }
    void BobDfs(int node,int dis,vector<int> &amount,
                  vector<int> &distance,vector<int> &parent, vector<int> adj[])
    {
        if(dis<distance[node]) amount[node]=0;
        if(dis==distance[node]) amount[node] /=2;
        if(node==0) return ;
        BobDfs(parent[node],dis+1,amount,distance,parent,adj);
    }
    int CollectAmount(int node,vector<int> &amount,vector<int> &visited,
                      vector<int> adj[])
    {
        visited[node]=1;
        int res = amount[node];
        int maxi=INT_MIN;
        for(auto it : adj[node])
        {
            if(visited[it]==0)
            maxi=max(maxi,CollectAmount(it,amount,visited,adj)); 
            
        }
        if(maxi==INT_MIN) return res;
        return res + maxi;
    }
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) 
    {
        int n = edges.size()+1;
        vector<int> adj[n];
        vector<int> parent(n,0);
        vector<int> visited(n,0);
        vector<int> distance(n,0);
        for(auto it : edges)
        {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        AliceDfs(0,0,0,parent,distance,adj);
        BobDfs(bob,0,amount,distance,parent,adj);
        return CollectAmount(0,amount,visited,adj);
    }
};

9. Number of Pairs satisfying Inequality.

class Solution {
public:
    typedef long long ll;
    
    class SegmentTree {
        public:
        int maxN;
        vector<ll> seg;
        
        SegmentTree(int n) : maxN(n) {
            seg = vector<ll> (maxN * 4 + 10, 0);
        }
        
        ll query(int l, int r) {
            return query_util(0, 0, maxN - 1, l, r);
        }
        
        ll query_util(int i, int low, int high, int l, int r) {
            if(low >= l && high <= r) 
                return seg[i];
            if(l > high || r < low)
                return 0;
            int mid = (low + high) / 2;
            ll left = query_util(2 * i + 1, low, mid, l, r);
            ll right = query_util(2 * i + 2, mid + 1, high, l, r);
            return left + right;
        }
        
        void update(int ele) {
            update_util(0, 0, maxN - 1, ele);
        }
        
        void update_util(int i, int low, int high, int ele) {
            if(low == high) {
                seg[i]++;
                return;
            }
            int mid = (low + high) / 2;
            if(ele <= mid) {
                update_util(2 * i + 1, low, mid, ele);
            } else {
                update_util(2 * i + 2, mid + 1, high, ele);
            }
            seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
        }
    };
    
    long long numberOfPairs(vector<int>& nums, vector<int>& nums2, int diff) {
        int n = nums.size();
        int offset = 20000;
        int max_ele = nums[0];
        for(int i = 0; i < n; i++) {
            nums[i] -= nums2[i];
            max_ele = max(max_ele, nums[i]);
        }
        SegmentTree seg(max_ele + offset + 1);
        ll ans = 0;
        for(auto it : nums) {
            ll count = seg.query(0, it + diff + offset);
            ans += count;
            seg.update(it + offset);
        }
        return ans;
    }
};


10. Shortest Unsorted continuous Subarray

class Solution {
public:
    int findUnsortedSubarray(vector<int>& vec) {
        int max = vec[0];
        int min = vec[vec.size()-1];
        int start = 0,end=-1;
        for(int i=1;i<vec.size();i++){
            if(max>vec[i]){
                end = i;
            }
            else max = vec[i];
        }
        for(int i=vec.size()-2;i>=0;i--){
            if(min<vec[i]){
                start = i;
            }
            else min = vec[i];
        }
        return end-start+1;
    }
};

11. Number of ways to arrive at a Destination.

class Solution {    
private:
    int dijkstra(vector<pair<int, int>> adj[], int n) {
		int mod = 1e9 + 7;
        priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
        vector<long long> dis(n, 1e15), path(n, 0);
        pq.push({0, 0});
        dis[0] = 0;
        path[0] = 1;
        while (!pq.empty()) {
            long long dist = pq.top().first;
            int node = pq.top().second;
            pq.pop();

           
            for (auto &child : adj[node]) {
                int adjNode = child.first;
                long long wt = child.second;

             
                if (dist + wt < dis[adjNode]) {
                    dis[adjNode] = dist + wt;
                    path[adjNode] = path[node];
                    pq.push({dist + wt, adjNode});
                }
                else if (dist + wt == dis[adjNode]) {
                  
                    path[adjNode] = (path[node] + path[adjNode]) % mod;
                }
            }
        }

        return path[n - 1];
    }
    
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        // adjacency list
        vector<pair<int, int>> adj[n];

        // create the graph
        for (auto &v : roads) {
            adj[v[0]].push_back({v[1], v[2]});
            adj[v[1]].push_back({v[0], v[2]});
        }
        
        return dijkstra(adj, n);
    }
};

12. Longest Happy Prefix
13. Seat Arrangement in a SpiceJet Problem - Online OA February ‘22
14. Deletions to make an array divisible.
15. Substrings containing all three Characters



