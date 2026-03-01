// Pehle basic se shuru karte hain: Yeh problem DSA mein "Greedy" category ka hai.
// Greedy ka matlab: Har step mein best local choice lo, aur umeed karo ki woh global best ban jaaye.
// Yeh similar hai "Minimum number of coins to make a sum" jaise problems se, jahan sabse badi denomination pehle use karte ho.
// Real world: Jaise ATM mein minimum notes dena hai customer ko.
// Ab yahan: Number ko deci-binary (sirf 0 aur 1 wale numbers) ke sum mein banana hai, aur minimum count chahiye.

// Intuition (sochne ka tareeka):
// Har digit ko alag socho - jaise school mein addition karte hain column-wise (units, tens, etc.).
// Har column mein digit 'd' hai toh usko pura karne ke liye exactly 'd' ones (1) chahiye, kyunki har deci-binary max 1 hi contribute kar sakta hai us column mein.
// Carry-over? Nahi, kyunki deci-binary mein sirf 0/1 hota hai, toh carry max 1 hi hota hai, lekin hum yahan sum kar rahe hain multiple numbers ka.
// Wait, actually yeh problem unique hai: Kyunki agar koi digit 9 hai, toh 9 ones chahiye us column mein.
// Aur agar dusre column mein 3 hai, toh woh 9 waale numbers mein se 3 mein 1 daal do, baaki 6 mein 0.
// Toh bottleneck hai sabse badi digit - uske liye minimum utne numbers chahiye, aur baaki sab adjust ho jayenge.
// First principle: Har position independent nahi hai puri tarah, lekin max digit decide karta hai kyunki baaki positions mein chhoti requirement hoti hai.

// Approach build-up (basic to advance):
// Basic: Pura number integer mein convert karo aur loop se subtract karo deci-binary, lekin yeh O(infinite) time lega kyunki number bohot bada hai (10^5 digits).
// Advance: String hi use karo, kyunki big integer.
// Intuition: Jaise binary mein bits on karte ho, yahan deci-binary decimal places mein 0/1.
// Similar question: LeetCode "Partitioning Into Minimum Number Of Deci-Binary Numbers" hi yeh hai.
// Related: "Minimum Platforms Required for Trains" - max overlapping (bottleneck).
// Real world usage: Resource allocation - minimum servers chahiye max load handle karne ke liye (jaise cloud computing mein peak demand).

// Complexity: Time O(n) - string traverse, Space O(1) - constant variables.
// Edge cases: "1" → 1, "10" → 1 (kyunki 10 khud deci-binary), "999" → 9.
// Constraints: n.length <= 10^5, toh efficient hona chahiye - no nested loops.

// Ab code: Class LeetCode style mein, public function.

class Solution {
public:
    int minPartitions(string n) {  // Input: string n (jaise "82734"), positive integer without leading zeros.
        
        int ans = 0;  // Initialize: Sabse bada digit track karne ke liye, shuru mein 0 assume karo (min possible).
                      // Kyunki agar sab digits 0 hote (but n positive hai toh nahi), lekin safe.
        
        // Loop: For-each style - modern C++ (C++11 se), efficient aur readable.
        // char& c: Reference use kiya taaki original change kar sake (but yahan nahi change kar rahe).
        for (char& c : n) {
            
            // Important conversion: char to int.
            // '0' ASCII 48, '9' 57, toh c - '0' se 0-9 milta hai.
            // Yeh trick har jagah use hoti hai competitive programming mein - yaad rakhna!
            // Agar c = '8', then 8 milta hai.
            
            // max function: <algorithm> header se aata hai, do values mein bada return.
            // Yeh greedy choice hai - har step mein update max.
            // Intuition: Jaise jaise traverse, max bottleneck update hota rahega.
            ans = max(ans, c - '0');  // Short aur efficient - no if-else needed.
            
            // Alternate lambe tareeke se (basic understanding ke liye):
            // int digit = c - '0';
            // if (digit > ans) ans = digit;
        }
        
        // Return: Yeh hi minimum numbers chahiye.
        // Proof: Sabse badi digit 'm' hai, toh m numbers se kam mein us column ko nahi bhar sakte.
        // Aur m se zyada ki zarurat nahi kyunki baaki digits <= m, toh adjust ho jayenge.
        return ans;
    }
};

// Extra tips for competitive programming:
// - Yeh code LeetCode pe 100% beat karega time mein kyunki O(n) aur n=1e5.
// - Similar problems solve karo: "Maximum Subarray" (Kadane) - local max to global.
// - Real world: Banking software mein minimum transactions to balance accounts.
// - Advance: Agar negative numbers hote toh alag hota, but yahan positive.
// - Learn: String handling in C++ bohot important hai big numbers ke liye (no BigInteger jaise Java mein built-in).

// Practice: Yeh code copy karke "32" pe run karo mentally - ans=3 (max '3').
// "82734" - max '8'.
// "101" - max '1'.
// Yaad rakhna: Intuition column-wise addition pe based hai - visualize karo paper pe.
