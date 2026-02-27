class Solution {
public:
    int minOperations(string s, int k) {
        
        // Step 1: Basic setup
        int n = s.size();           // string ki length
        int m = 0;                  // total number of '0's jo abhi string mein hain
        
        // Yeh vector distance store karega
        // dist[zeros] = minimum operations to reach exactly 'zeros' number of 0's remaining
        vector<int> dist(n + 1, INT_MAX);
        
        // Important observation: har operation exactly k positions flip karta hai
        // → number of 0's change by even number (kyunki k positions flip → even ya odd depend karta hai)
        // Actually: har flip 0 ko 1 banata hai ya 1 ko 0 → net change in zero count = (number of 0's flipped) - (number of 1's flipped)
        // But number of 0's flipped + number of 1's flipped = k
        // So change in zero count = 2 * (number of 0's flipped) - k
        // → change is always even ya odd same as k ke parity ke saath
        
        // Isliye hum sirf same parity wale zero counts tak pahunch sakte hain
        
        // nodeSets[0] → even number of zeros wale states
        // nodeSets[1] → odd number of zeros wale states
        vector<set<int>> nodeSets(2);
        
        // Step 2: initial setup
        for (int i = 0; i <= n; i++) {
            // har possible zero count (0 se n tak) ko appropriate set mein daal rahe
            nodeSets[i % 2].insert(i);
            
            // s mein kitne '0' hain count kar rahe
            if (i < n && s[i] == '0') {
                m++;
            }
        }
        
        // m = initial number of zeros
        
        // Queue for BFS — yeh shortest path find karega
        queue<int> q;
        q.push(m);                  // start from initial zeros count
        
        dist[m] = 0;                // 0 operations se m zeros hain
        
        // Ab is state ko visited mark kar rahe (set se hata rahe)
        nodeSets[m % 2].erase(m);
        
        // Step 3: BFS chalate hain — goal hai 0 zeros tak pahunchna
        while (!q.empty()) {
            m = q.front();          // current number of zeros
            q.pop();
            
            // Ab ek operation karne se kitne zeros kam ya zyada ho sakte hain?
            
            // Ek operation mein exactly k positions flip karte hain
            // Maan lo humne x ta '0' flip kiye (i.e. 0 → 1)
            // toh (k - x) ta '1' flip kiye (1 → 0)
            
            // Net change in zero count:
            // -x (jo 0 gaye) + (k - x) (jo naye 0 aaye) = k - 2x
            
            // x can range from max(0, k - (n - m)) to min(k, m)
            // kyuki:
            //   x <= m           (itne se zyada 0 nahi hain)
            //   k - x <= n - m   (itne se zyada 1 nahi hain)
            //   → x >= k - (n - m)
            
            int c1 = max(k - (n - m), 0);   // minimum possible x (0's flipped)
            int c2 = min(m, k);             // maximum possible x
            
            // Ab possible new zero counts:
            // new_zeros = m + (k - 2*x)   where x in [c1, c2]
            
            // Jab x badhta hai → new_zeros ghatta hai
            // isliye leftmost (sabse chhota) new zero count jab x = c2
            // rightmost (sabse bada) jab x = c1
            
            int lnode = m + k - 2 * c2;     // smallest possible new zero count
            int rnode = m + k - 2 * c1;     // largest possible new zero count
            
            // Ab humein sirf same parity wale nodes hi consider karne hain
            // (kyunki change = k - 2x → parity same rahega k ke parity ke saath)
            auto& nodeSet = nodeSets[lnode % 2];
            
            // set mein lower_bound se search karte hain
            // lnode se rnode tak ke saare reachable states visit karenge
            for (auto iter = nodeSet.lower_bound(lnode);
                 iter != nodeSet.end() && *iter <= rnode; ) {
                
                int m2 = *iter;             // yeh naya zero count
                
                // yeh state pehle nahi aaya → iska distance set karo
                dist[m2] = dist[m] + 1;
                
                q.push(m2);                 // BFS mein daal do
                
                // important: erase karna padega warna loop infinite ho jayega
                // (kyunki hum same set iterate kar rahe)
                auto to_erase = iter;
                ++iter;                     // pehle next karo
                nodeSet.erase(to_erase);    // phir erase karo
            }
        }
        
        // End mein check karo:
        // agar dist[0] update hua hai toh wohi answer
        // nahi toh impossible → -1
        return dist[0] == INT_MAX ? -1 : dist[0];
    }
};
