#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(string s) {
        
        /*
        ====================== PROBLEM SAMAJH LO ======================
        Humare paas binary string hai (sirf '0' aur '1')
        Hum chahte hain ki ye string alternating ho jaye
        Matlab ya to: 01010101...
                   ya: 10101010...
        Minimum kitne characters change karne padenge?
        ====================== CORE SECRET ======================
        Sirf 2 hi possible perfect strings hain
        Isliye sirf 2 possibilities check karni hain
        Aur jisme kam changes lagen – wahi answer
        */

        // Counter 1: agar pattern 010101... se shuru ho to kitne badlav chahiye
        int start0 = 0;
        
        // Counter 2: agar pattern 101010... se shuru ho to kitne badlav chahiye
        int start1 = 0;
       
        // Har ek character / position ko dekhte hain
        for (int i = 0; i < s.size(); i++) {
            
            // Even index (0,2,4,6...) 
            if (i % 2 == 0) {
                
                // Pattern 010101... → even pe '0' hona chahiye
                // Agar yahan '0' nahi hai (yani '1' hai) → start0 pattern ke liye galat
                if (s[i] == '0') {
                    // 101010... pattern ke liye yeh position galat hai → change karna padega
                    start1++;
                } else {
                    // 010101... pattern ke liye yeh galat hai
                    start0++;
                }
            }
            
            // Odd index (1,3,5,7...)
            else {
                
                // Pattern 010101... → odd pe '1' hona chahiye
                if (s[i] == '1') {
                    // 101010... pattern ke liye galat
                    start1++;
                } else {
                    // 010101... pattern ke liye galat
                    start0++;
                }
            }
        }
       
        /*
        Ab dono patterns ke liye jitne changes chahiye – unme se
        sabse kam wala number hi final jawab hai
        */
        return min(start0, start1);
        
        // Time Complexity  → O(n)  → n = length of string
        // Space Complexity → O(1)  → sirf 4 integer variables
    }
};

/*
Quick Revision Table (comment mein yaad rakhne ke liye)

/----------------------------------------------------\
| Problem Type                | Key Idea                  | Time | Space |
|-----------------------------|---------------------------|------|-------|
| Alternating binary string   | Count for both patterns   | O(n) | O(1)  |
| Minimum changes to pattern  | Only 2 candidates         | O(n) | O(1)  |
| Parity based decision       | Use i%2 to decide         | O(n) | O(1)  |
\----------------------------------------------------/
*/
