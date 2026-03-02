class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        
        // n = grid ka size (rows = columns, square matrix guaranteed)
        // LeetCode problem mein n <= 100 hota hai mostly, toh O(n^2) safe hai
        int n = grid.size();
        
        // pos[i] = i-th row mein RIGHTMOST '1' ka column index
        // Agar row mein koi 1 nahi hai (pure zeros) → pos[i] = -1 rakhenge
        // Kyunki -1 <= kisi bhi i ke liye true hota hai → all-zero row kahi bhi ja sakti hai
        vector<int> pos(n, -1);  // sabko default -1 initialize kar diya (smart!)
        
        // ===================== PRECOMPUTE PHASE =====================
        // Har row ka RIGHTMOST 1 dhoondh rahe hain
        // Kyun right se left ja rahe hain? Kyunki jaise hi pehla 1 mile → break kar do!
        // Left se right jaate to pura row traverse karna padta har baar
        for (int i = 0; i < n; ++i) {
            
            // j ko last column se shuru kar rahe hain (n-1)
            // --j prefix decrement → CP style fast increment/decrement
            for (int j = n - 1; j >= 0; --j) {
                
                // grid[i][j] == 1 mila → yeh rightmost 1 hai (kyunki right se aa rahe hain)
                if (grid[i][j] == 1) {
                    pos[i] = j;     // store kar diya index
                    break;          // IMPORTANT OPTIMIZATION! Ab aage check karne ki zarurat nahi
                }
            }
            // Agar loop pura chala aur break nahi hua → pos[i] ab bhi -1 rahega
            // Matlab yeh row pure zeros ki hai → infinite trailing zeros
        }
        
        // Ab pos[] array ready hai
        // Example: agar pos = [2, -1, 0, 1] → matlab
        // row 0 ka last 1 column 2 pe
        // row 1 pure zeros
        // row 2 ka last 1 column 0 pe
        // row 3 ka last 1 column 1 pe
        
        int ans = 0;  // total minimum adjacent swaps jo lagenge
        
        // ===================== MAIN GREEDY SIMULATION =====================
        // Har final position i ke liye decide kar rahe hain kaun si row aayegi
        for (int i = 0; i < n; ++i) {
            
            // i-th position ke liye chahiye: last 1 <= i (trailing zeros >= n-i-1)
            // Yani pos[j] <= i hona chahiye
            
            int k = -1;  // yeh variable batayega ki kaun si row (index) finally i pe baithne wali
            
            // Ab current position i se lekar end tak dekho
            // Sabse pehli (closest) valid row dhoondho
            // Kyunki closest = minimum swaps (greedy choice)
            for (int j = i; j < n; ++j) {
                
                // MAGIC CONDITION jo sab kuch decide karta hai
                // pos[j] <= i → is row mein enough trailing zeros hain position i ke liye
                // Agar pos[j] = -1 (all zeros) → -1 <= i hamesha true
                if (pos[j] <= i) {
                    
                    // Yeh row le lenge
                    // Kitne adjacent swaps lagenge isko i tak laane mein?
                    // Exactly (j - i) swaps (bubble sort mathematics)
                    // Jaise 5th position se 2nd position laane mein 3 adjacent swaps
                    ans += (j - i);
                    
                    k = j;    // yaad rakh lo is row ka original index
                    break;    // closest mil gaya → aage dekhne ki zarurat nahi (greedy!)
                }
            }
            
            // Ab check karo ki koi row mili bhi ya nahi
            // ~k trick: ~(-1) = 0 (false), ~(positive) = negative (true in if)
            // Alternate likh sakte the: if(k != -1)
            // Lekin yeh CP style mein bahut common aur thoda faster
            if (~k) {
                
                // Ab is row (k) ko position i tak bubble shift kar do
                // Kyun? Kyunki agli baar jab hum i+1 pe jayenge
                // toh candidates ka order sahi rehna chahiye (jo pehle se use ho chuke)
                // Yeh exactly bubble sort ka ek pass hai
                for (int j = k; j > i; --j) {
                    swap(pos[j], pos[j - 1]);  // adjacent swap in pos array
                    // Isse pos array update ho jata hai
                    // Jaise array shift left kar rahe hain
                }
                
                // Dry run example (n=4, i=1, k=3):
                // pehle pos = [..., x, y, z, valid]
                // baad mein pos = [..., valid, x, y, z]
                // valid row ab index 1 pe aa gayi
            } 
            else {
                // Koi bhi row nahi mili jo pos[j] <= i satisfy kare
                // Matlab impossible arrangement
                return -1;
            }
        }
        
        // Sab positions fill ho gaye → total swaps return kar do
        return ans;
    }
};
