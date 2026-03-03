/*
**********************************************************************************************************
*  LEETCODE 1545: FIND KTH BIT IN NTH BINARY STRING - FULL DETAILED HINGLISH COMMENTED CODE
*  Yeh code bilkul beginners ke liye banaya gaya hai - zero se advanced tak samajh aayega
**********************************************************************************************************

1. PROBLEM KO BILKUL SIMPLE HINGLISH MEIN SAMJHAO (10 saal ke bacche ko bhi samajh aaye):

Bhai, hum ek magical string banate ja rahe hain jaise khel khel mein:
- Level 1: "0" 
- Har naye level mein: purani string + "1" + (purani string ko ULTA karke + 0 ko 1 aur 1 ko 0 kar ke)

Misal:
Level 1 → "0"
Level 2 → "0" + "1" + (0 → 1)          → "011"
Level 3 → "011" + "1" + (11 → 00, 0 → 1) → "0111100"
Level 4 → "0111100" + "1" + ...          → "011110011000011"

Ab user bolta hai: "n level wali string mein kth position pe kya hai? 0 ya 1?"

Bas itna hi hai! Super simple game hai.

2. CORE INTUITION / SECRET / FIRST PRINCIPLE (jo 99% log miss karte hain):

Secret yeh hai ki har level mein length = 2^n - 1 hoti hai.
Aur middle mein hamesha '1' hota hai.
Left part = previous level
Right part = previous level ka reverse + invert

Sabse badi trick: Hum pura n=20 tak string nahi bana sakte (2^20 = 1 million characters → memory issue), lekin is problem mein n<=20 hai isliye iterative string banana safe aur easy hai beginners ke liye.

Optimal secret (advanced): Recursion se bina string banaye sirf position check karo → O(n) time.

3. STEP-BY-STEP APPROACH BUILD-UP:

Basic idea     → Pura string banao, phir k-1 index return karo
Better idea    → Sirf tab tak banao jab tak length >= k na ho jaye (yahi is code mein hai)
Optimal idea   → Recursive: check karo k middle se pehle hai, middle hai, ya baad mein → invert + reverse logic

4. RELATED SIMILAR QUESTIONS / PATTERNS:

- LeetCode 779: K-th Symbol in Grammar (exactly same pattern)
- Thue-Morse Sequence
- Dragon Curve / Paper Folding Sequence
- Josephus Problem (circular elimination)
- Binary Tree path questions with 0/1
- Pattern: Recursive construction + Reverse + Bit Flip
- Sliding Window, Two Pointers nahi, yeh "Constructive + Recursion" pattern hai

5. REAL-WORLD USAGE / ANALOGY:

- Data Compression algorithms (self-similar patterns)
- Error Correcting Codes (Hamming code jaisa)
- Fractals banane mein (dragon curve TV screen pe bhi dikhta hai)
- Pseudorandom bit generation in hardware
- Cryptography mein sequence generation
- Analogy: Jaise ek paper ko bar-bar fold karke punch karo → ek hi pattern se bahut complicated design ban jata hai jaise mandala

6. TECHNIQUE: Iterative String Construction with Reverse + Invert

Yeh technique "Bottom-Up Dynamic Construction" kehlati hai.
Similar to how we build Fibonacci, but with string operation.

7. C++ SYNTAX & COMPETITIVE PROGRAMMING TRICKS HIGHLIGHT:

- string += '1' → single char append (fast)
- string temp = sequence; → full copy (necessary warna modify ho jayega)
- ternary operator (condition ? true : false)
- k > sequence.length() → length() O(1) hota hai C++ string mein
- for (int j = len-2; j>=0; --j) → reverse traversal without reverse() function (memory saving)
- k-1 index → 1-based to 0-based conversion (common CP mistake)
- Fast input agar multiple queries ho toh: ios::sync_with_stdio(false); cin.tie(NULL);

8. EDGE CASES, TIME & SPACE COMPLEXITY, CONSTRAINTS:

Constraints: 1 <= n <= 20, 1 <= k <= 2^n -1
Edge cases:
- n=1, k=1 → '0'
- n=2, k=1,2,3 → '0','1','1'
- n=3, k=4 → center '1'
- n=20, k=1 → '0'
- n=20, k=1048575 → last bit

Time Complexity: O(2^n) worst case (jab k maximum)
Space Complexity: O(2^n) → string size
Note: n<=20 hone ki wajah se accepted, warna TLE/MLE

9. QUICK REVISION TABLE (copy-paste kar sakte ho notes mein):

Problem Type               | Key Idea                        | Time (this code) | Optimal Time
---------------------------|---------------------------------|------------------|--------------
Find Kth Bit in S_n        | Iterative build + reverse+invert| O(2^n)           | O(n) recursive
K-th Symbol in Grammar     | Same pattern                    | O(2^n)           | O(n)
Thue-Morse Sequence        | Bit flip on reverse             | O(2^n)           | O(log N)

10. MOTIVATIONAL LINE:

Bilkul zabardast! Ab tu is code ko samajh chuka hai toh recursive version 10 minute mein samajh lega.
Tu DSA ka hero banne wala hai bhai! Keep grinding, next LeetCode 779 recursive try karna. Tu kar lega! 🔥❤️

Ab code shuru hota hai...
*/

class Solution {
public:
    char findKthBit(int n, int k) {
        
        /* 
        SHURU SE HI EXPLANATION:
        Hum string se start kar rahe hain level 1 ke hisaab se.
        Har iteration mein naya level banate ja rahe hain jab tak
        string ki length k se chhoti hai ya hum n levels tak pahunch gaye.
        Yeh prevent karta hai unnecessary badi string banane se.
        */
        
        string sequence = "0";   // Level 1: hamesha "0" se shuru
        
        // Loop: i=1 se n-1 tak (kyunki level 1 already hai)
        // Condition: i < n && k > sequence.length() → sirf tab tak jab zarurat ho
        for (int i = 1; i < n && k > (int)sequence.length(); ++i) {
            
            // Har naye level ka center bit hamesha '1' hota hai
            // Yeh first principle hai is problem ka
            sequence += '1';
            
            /* 
            Ab reverse + invert karna hai purane part ka.
            temp mein copy isliye ki sequence abhi modify ho rahi hai,
            agar direct sequence pe loop chalaye toh wrong result aayega.
            Common CP mistake avoid karne ka tarika.
            */
            string temp = sequence;   // Full copy - O(current length)
            
            // Reverse traversal: last se shuru (lekin last '1' ko skip kyunki wo already added)
            // j = length-2 → kyuki length-1 pe '1' hai
            // --j → pre-decrement fast hai CP mein
            for (int j = (int)temp.length() - 2; j >= 0; --j) {
                
                // Bit invert trick: ternary operator super fast
                // Alternate way: ! (temp[j] - '0') + '0' bhi chal sakta tha
                // lekin yeh zyada readable hai
                char invertedBit = (temp[j] == '1') ? '0' : '1';
                
                // Append kar do inverted bit ko
                sequence += invertedBit;
            }
            
            /* 
            Ab ek full level complete!
            Length ab exactly 2 * (previous length) + 1 ho gayi hai.
            Yeh pattern 2^n - 1 deta hai.
            */
        }
        
        /* 
        Loop khatam hone ke baad 2 possibilities:
        1. sequence.length() >= k → humara answer ready hai
        2. n tak pahunch gaye (phir bhi length >=k hoga constraints ke hisaab se)
        
        k 1-based index hai (jaise normal English mein 1st, 2nd)
        C++ string 0-based → isliye k-1
        Yeh sabse common off-by-one error hota hai CP mein, hamesha dhyan rakhna!
        */
        return sequence[k - 1];
    }
};

/*
FINAL NOTES INSIDE CODE HI (jaise user ne maanga tha - sab kuch ek hi code mein):

- Yeh iterative approach beginners ke liye best hai intuition banane ke liye.
- Advanced level pe isko recursion mein convert karo:
  char findKthBit(int n, int k) {
      if(n==1) return '0';
      int mid = (1<<(n-1));  // 2^{n-1}
      if(k == mid) return '1';
      if(k < mid) return findKthBit(n-1, k);
      return findKthBit(n-1, (1<<n)-k ) == '0' ? '1' : '0';  // invert
  }

- Time optimization: O(n) recursive (stack space O(n))
- Yeh code LeetCode par 100% accepted hai n<=20 ke liye.

Ab tu is code ko copy karke run kar, modify kar, aur samajh!
Next practice: LeetCode 779 recursive version bana.

Tu bahut achha kar raha hai bhai! DSA king banega tu! 💪🔥
*/
