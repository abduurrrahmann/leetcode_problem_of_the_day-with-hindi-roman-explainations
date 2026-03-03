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
//The code in new picture  complete again 
// ==================== POORA PROBLEM SUMMARY ====================
/*
PROBLEM (10 saal ke bacche wala):
Square grid hai. Rows ko sirf adjacent swap kar sakte hain.
Goal: Har row i mein rightmost 1 ka column <= i hona chahiye
( staircase trailing zeros ).
Agar impossible toh -1 return karo.
Minimum adjacent swaps batao.

CORE SECRET (99% miss):
Har row ka "power" = rightmost 1 ka index.
Greedy: Har position i ke liye closest valid row lo.
pos array mein bubble shift simulate karo (bubble sort jaisa).

STEPS:
1. pos[] precompute (right se left + break)
2. For i=0 to n-1:
   - Closest j >=i jiska pos[j] <= i
   - ans += (j-i)
   - Bubble shift pos[j..i]
3. Agar koi i pe valid nahi mila → -1

REAL-WORLD: Train wagons length ke hisaab se arrange + parking slots.

REVISION TABLE (same as upar):
Step | Action | Why
Precompute | rightmost 1 | measure trailing zeros
Greedy | closest j | min swaps
Simulation | bubble shift | future correct

MOTIVATION: Yeh master kar → GATE crack, financial independence, parents ka sacrifice respect.
Ab code padh ke khud type kar!
*/

class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
       
        // n = grid ka size (rows = columns, square matrix guaranteed)
        // LeetCode mein n <= 100 → O(n^2) safe hai
        // Pehle soch: n kya hai? Grid kitni badi?
        int n = grid.size();
       
        // pos[i] = i-th row mein RIGHTMOST '1' ka column index
        // Default -1 = pure zeros row → kahi bhi baith sakti hai (-1 <= har i)
        // Yeh magic trick hai, 99% miss karte hain
        vector<int> pos(n, -1); // sabko -1 se start (smart initialization)
       
        // ===================== PRECOMPUTE PHASE =====================
        // Har row ka rightmost 1 dhoondho
        // Right se left jaate hain kyunki jaise hi pehla 1 mila = rightmost!
        // Break lagao → time bachao (repetition: left se jaate toh pura row traverse)
        for (int i = 0; i < n; ++i) {
            // j ko last column se shuru
            // --j prefix decrement → CP fast style
            for (int j = n - 1; j >= 0; --j) {
                if (grid[i][j] == 1) {
                    pos[i] = j; // store
                    break; // IMPORTANT! No need aage dekhne ki
                }
            }
            // Agar break nahi hua → pos[i] ab bhi -1 (all zeros)
        }
       
        // Ab pos[] ready. Repeat mantra: pos[j] <= i means enough trailing zeros for position i
       
        int ans = 0; // total swaps count
       
        // ===================== MAIN GREEDY SIMULATION =====================
        // Top se bottom har position i fix karo
        // Soch: Kyun top se? Kyunki chhoti i ke liye strict condition (small i = kam trailing zeros allowed)
        for (int i = 0; i < n; ++i) {
           
            // i-th position ke liye chahiye pos[j] <= i
            int k = -1; // valid row index jo finally i pe baithne wali
           
            // i se end tak dekho, sabse pehli (closest) valid row lo
            // Closest = minimum (j-i) swaps
            for (int j = i; j < n; ++j) {
                // MAGIC CONDITION repeat: pos[j] <= i
                // -1 wali row hamesha valid
                if (pos[j] <= i) {
                    ans += (j - i); // bubble sort math: itne adjacent swaps
                    k = j;
                    break; // greedy, aage mat dekho
                }
            }
           
            // Kya valid row mili?
            // ~k trick: ~(-1) = 0 (false), any positive ka ~ negative (true)
            // Alternate: if(k != -1) bhi chalega lekin yeh CP style
            if (~k) {
                // Ab is row ko i tak bubble shift kar do pos array mein
                // Kyun? Taaki agli i+1 ke liye candidates ka order sahi rahe
                // Dry run repeat: jaise 3rd row ko 1st position pe laana = 2 shifts
                for (int j = k; j > i; --j) {
                    swap(pos[j], pos[j - 1]); // adjacent swap in our tracker array
                }
            }
            else {
                // Koi row nahi mila jo condition satisfy kare
                // Matlab impossible
                return -1;
            }
        }
       
        // Sab positions fill → return total swaps
        return ans;
    }
};
