Challenge Company 2 : Goldman Sachs

1. Max Points on a Line

class Solution {
public:
    int maxPoints(vector<vector<int>>& p) {
        int total =0;
        int n = p.size();
        if(n<=2)    return n;
        int maxi =2;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                int total = 2;
                for(int k=0;k<n;k++){
                    if(k!=i && k!=j){
                        if(((p[j][1]-p[i][1])*(p[i][0]-p[k][0])  )==(p[j][0]-p[i][0])*(p[i][1]-p[k][1]))
                        total++;
                    }
                }
                maxi = max(maxi,total);
            }
        }
        return maxi;
    }
};

2. Valid Square

class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        unordered_set<int>s;
        s.insert(dist(p1,p2));
        s.insert(dist(p1,p3));
        s.insert(dist(p1,p4));
        s.insert(dist(p2,p3));
        s.insert(dist(p2,p4));
        s.insert(dist(p3,p4));
        return s.count(0)==0 && s.size()==2;
    }
    int dist(vector<int>p1,vector<int>p2){
        return (p2[0]-p1[0])* (p2[0]-p1[0])+ (p2[1]-p1[1])*(p2[1]-p1[1]);
    }
};


3. Factorial with Trailing Zeroes

class Solution {
public:
    int trailingZeroes(int n) {
        int count =0;
        while(n>0)
            {
            n=n/5;
            count +=n;
        }
        return count;
    }
};

4. Number of Boomerangs (Similar to peacocks question)

class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        if(points.size()<3)
            return 0;
         int res=0;
        for (int i=0; i<points.size(); i++){
            map<int,int> mp; 
            for (int j=0; j<points.size(); j++){ 
                if (i!=j){
                    int dist= (points[i][1]-points[j][1])*(points[i][1]-points[j][1])+(points[i][0]-points[j][0])*(points[i][0]-points[j][0]);
                    mp[dist]++;
                }
            }
            for (auto val: mp){
                if(val.second>=2)
                    res+= ((val.second)*(val.second-1)); 
            }
        }
        return res;

    }
};

5. Split Array into Sequences

class Solution {
public:
bool isPossible(vector& nums) {
map<int,int>fm;
map<int,int>hm;
for(int i:nums){
fm[i]++;
}
for(int i:nums){
if(fm[i]==0)continue;
if(hm[i]>0){
hm[i]--;
hm[i+1]++;
fm[i]--;
}else if(fm[i]>0&&fm[i+1]>0&&fm[i+2]>0){
fm[i]--;
fm[i+1]--;
fm[i+2]--;
hm[i+3]++;
}else return false;
}
return true;
}
};

6. Minimum Consecutive Cards to pick up

class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        unordered_map<int,int>m;
        int res=INT_MAX;
        for(int i=0;i<cards.size();i++){
            if(m.find(cards[i])!=m.end()){
                res=min(res,i-m[cards[i]]+1);
            }
            m[cards[i]]=i;            
        }

        if(res!=INT_MAX){
            return res;
        }else
        return -1;
        
    }
};

7. Count Good Triplets in Array (Profits in a Startup Question)

class Solution {
public:
    // function to return the last bit set in the input number
    inline int lastOne(int x) {
        return x & (-x);
    }
    
    // function to update a Fenwick tree with delta at index i
    void updateFenwickTree(vector<int>& fenwickTree, int index, int delta) {
        for(;index < fenwickTree.size(); index += lastOne(index)) {
            fenwickTree[index] += delta; 
        }
    }
    
    // function to get the prefix sum of the Fenwick tree up to index i
    int getPrefixSum(vector<int>& fenwickTree, int index) {
        int prefixSum = 0; 
        for(;index;index -= lastOne(index)) {
            prefixSum += fenwickTree[index];
        }
        return prefixSum; 
    }
    
    // function to get the range sum of the Fenwick tree between startIndex and endIndex
    int getRangeSum(vector<int>& fenwickTree, int startIndex, int endIndex) {
        return getPrefixSum(fenwickTree,endIndex) - (startIndex == 1?0:getPrefixSum(fenwickTree,startIndex-1));
    }
    
    // main function to find good triplets
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        // get the size of the input vectors
        const int vectorSize = nums1.size(); 
        // create a vector to hold the index positions of nums1
        vector<int> indexPositions(vectorSize);
        for(int i = 0; i < vectorSize; i++) {
            indexPositions[nums1[i]] = i;
        }
        // variable to count the number of good triplets
        long long goodTripletCount = 0; 
        // create a Fenwick tree with size n + 5
        vector<int> fenwickTree(vectorSize + 5);
        // create a vector to hold the number of elements smaller than nums2[i] in nums1 to the right of nums1[i]
        vector<int> smallerElementsToRight(vectorSize);
        // loop through nums2 backwards
        for(int i = vectorSize - 1; i >= 0; i--) {
            // get the index position of nums2[i] in nums1
            int index = indexPositions[nums2[i]];
            // store the number of elements smaller than nums2[i] in nums1 to the right of nums1[i]
            smallerElementsToRight[nums2[i]] = getRangeSum(fenwickTree,index + 1,vectorSize + 1);
            // update the Fenwick tree at index j + 1
            updateFenwickTree(fenwickTree,index + 1,1);
        }
        // reset the Fenwick tree
        fenwickTree.assign(vectorSize + 5,0);
        // loop through nums2 forwards
        for(int i = 0; i < vectorSize; i++) {
            // get the index position of nums2[i] in nums1
            int index = indexPositions[nums2[i]];
            // count the number of good triplets using the stored values
            long long smallerElementsBefore = getPrefixSum(fenwickTree,index);
            goodTripletCount += smallerElementsBefore * smallerElementsToRight[nums2[i]];
            // update the Fenwick tree at index j + 1
            updateFenwickTree(fenwickTree,index + 1,1);
        }
    return goodTripletCount;
    }
};

8. Maximum Points in Archery Competition

class Solution {
public:
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
        vector<int>v;
        int maxi=0;
        for(int i=0; i<(1<<12); i++){
            int n=numArrows, cnt=0;
            vector<int>temp(12, 0);
            for(int j=11; j>=0; j--){
                if(i&(1<<j)){
                    if(n>aliceArrows[j]){
                        n-=(aliceArrows[j]+1);
                        temp[j]=(aliceArrows[j]+1);
                    }
                }
            }
            for(int j=0; j<12; j++){
                if(i&(1<<j)){
                    temp[j]+=n;
                    break;
                }
            }
            for(int j=0; j<12; j++){
                if(temp[j]>aliceArrows[j]){cnt+=j;}
            }
            if(cnt>maxi){
                maxi=cnt;
                v=temp;
            }
        }
        return v;
    }
};

9. Initial Public Offering

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        priority_queue<int>q;
        int i=0;
        vector<pair<int, int>>v;
        for(int i=0; i<profits.size(); i++){
            v.push_back({capital[i], profits[i]});
        }
        sort(v.begin(), v.end());
        while(i<v.size() && k){
            if(w>=v[i].first){
                q.push(v[i].second);
                i++;
            }
            else{
                if(q.empty()){
                    return w;
                }
                else{
                    w+=q.top();
                    q.pop();
                    k--;
                }
            }
        }
        while(k-- && !q.empty()){
            w+=q.top();
            q.pop();
        }
        return w;
    }
};

10. People and Secret

    int peopleAwareOfSecret(int n, int delay, int forget) {
        vector<long> dp(n + 1);
        dp[1] = 1;
        int share = 0, mod = 1e9 + 7, res = 0 ;
        for (int i = 2; i <= n; ++i)
            dp[i] = share = (share + dp[max(i - delay, 0)] - dp[max(i - forget, 0)] + mod) % mod;
        for (int i = n - forget + 1; i <= n; ++i)
            res = (res + dp[i]) % mod;
        return res;
    }

11. Invalid Transactions in an EMI

class Transaction {
    public:
    // name of the person making the transaction
    string personName;
    // time of the transaction in minutes
    int transactionTime; 
    // amount of the transaction
    int transactionAmount;
    // city of the transaction
    string transactionCity;
        
    // constructor for creating transaction object
    Transaction(string name, int time, int amount, string city)
    {
        this->personName = name;
        this->transactionTime = time;
        this->transactionAmount = amount;
        this->transactionCity = city;
    }
};

class Solution {
public:

    // method to find invalid transactions
    vector<string> invalidTransactions(vector<string>& transactions) {
        int numTransactions = transactions.size();
        // boolean flag for each transaction indicating whether it's valid or not
        vector<bool> isValid(numTransactions, true);
        vector<Transaction> inputTransactions;
        
        // Extracting information from string
        for(int i=0; i<numTransactions; i++)
        {
            string currTransaction = transactions[i];
            string name = "", time = "", amount = "", city = "";
            int j = 0;
            
            // Extracting name
            while(currTransaction[j] != ',')
            {
                name += currTransaction[j++];
            }
            j++;
            // Extracting time
            while(currTransaction[j] != ',')
            {
                time += currTransaction[j++];
            }
            j++;
            // Extracting amount
            while(currTransaction[j] != ',')
            {
                amount += currTransaction[j++];
            }
            j++;
            // Extracting city
            while((j < currTransaction.size()) && (currTransaction[j] != ','))
            {
                city += currTransaction[j++];
            }
            
            // Creating a new transaction object with the extracted information
            Transaction newTransaction(name, stoi(time), stoi(amount), city);
            inputTransactions.push_back(newTransaction);
        }
        
        // First check: transaction amount > 1000
        for(int i=0;i<inputTransactions.size(); i++)
        {
            if(inputTransactions[i].transactionAmount > 1000)
                isValid[i] = false;
        }
        
        // Second check, pair-wise
        for(int i=0;i<(inputTransactions.size()); i++)
        {
            for(int j=0; j<inputTransactions.size(); j++)
            {
                // We do not need to check a transaction against itself
                if(i == j)
                    continue;
                    int timeDiff = abs(inputTransactions[j].transactionTime - inputTransactions[i].transactionTime);
            if(timeDiff <= 60)
            {
                if((inputTransactions[j].personName == inputTransactions[i].personName) && (inputTransactions[j].transactionCity != inputTransactions[i].transactionCity))
                {
                    // If the above conditions are met, the transaction is invalid.
                    isValid[i] = false;
                    isValid[j] = false;
                }
            }
        }
    }
    
    // Adding invalid transactions to the answer
    vector<string> invalidTransactions;
    for(int i=0;i<inputTransactions.size(); i++)
    {
        if(!isValid[i])
            invalidTransactions.push_back(transactions[i]);
    }
    
    return invalidTransactions;
}
};

12. All elements of a binary Search Tree

class Solution {
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> ans;
        stack<TreeNode*> stk1,stk2;
        while (!stk1.empty() || !stk2.empty() || root1 || root2){
            while (root1){
                stk1.push(root1);
                root1= root1->left;
            }
            while (root2){
                stk2.push(root2);
                root2= root2->left;
            }
            if (stk2.empty() || (!stk1.empty() && stk1.top()->val <= stk2.top()->val)){
                root1= stk1.top();
                ans.push_back(root1->val);
                stk1.pop();
                root1=root1->right;
            }
            else{
                root2= stk2.top();
                ans.push_back(root2->val);
                stk2.pop();
                root2= root2->right;
            }
        }
        
        return ans;
    }
};

13. Rhombus Sums in a GRID

class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        vector<vector<int> > ld = grid, rd = grid;//ld = left diagonal, rd = right diagonal
        int m = grid.size();
        int n = grid[0].size();
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                int pi = i - 1;
                int prevj = j - 1;
                if(pi >= 0 && prevj >= 0) ld[i][j] += ld[pi][prevj];
                prevj = j + 1;
                if(pi >= 0 && prevj < n) rd[i][j] += rd[pi][prevj];
            }
        }
        map<int, int> cnt;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                ++cnt[grid[i][j]];
                for(int k = 1; k <=max(m, n); ++k) {
                    int left = j - k;
                    int right = j + k;
                    int bot = i + 2 * k;
                    if(left < 0 || right >= n || bot >= m) continue;
                    int sum = rd[i + k][left] - rd[i][j] 
                                         + ld[i + k][right] - ld[i][j] 
                                         + ld[bot][j] - ld[i + k][left]
                                         + rd[bot][j] - rd[i + k][right]
                                         + grid[i][j] - grid[bot][j];
                    ++cnt[sum];
                }
                while(cnt.size() > 3) {
                    auto it = cnt.begin();
                    cnt.erase(it);
                }
            }
        }
        vector<int> ans;
        for(auto it = cnt.rbegin(); it != cnt.rend(); it++) {
            ans.push_back(it->first);
            if(ans.size() >= 3) return ans;
        }
        return ans;
    }
};

14. Nice Pairs in Array (OTT Platforms and John)
15. Good People based on Statements

int maximumGood(vector<vector<int>>& A) {
    int n = A.size(), ans = 0;
    for (int num = 1 << n; num < 1 << (n + 1); num++) {
        string permutation = bitset<15>(num).to_string().substr(15 - n);
        if (check(permutation, A, n)) {
            int c = count(begin(permutation), end(permutation), '1');
            ans = max(ans, c);
        }
    }
    return ans;
}
bool check(string& perm, vector<vector<int>>& A, int n) {
    for (int i = 0; i < n; i++) {
        if (perm[i] == '0') continue;
        for (int j = 0; j < n; j++) {
            if (A[i][j] == 2) continue;
            if ((A[i][j] == 1 && perm[j] == '0') || 
                (A[i][j] == 0 && perm[j] == '1')) 
                return false;
        }
    }
    return true;
}

