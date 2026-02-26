#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    // Function 1: divideByTwo
    // Kaam: agar number even hai (last digit 0) to bas last character hata do
    // Yeh binary mein /2 karne ke barabar hai
    void divideByTwo(string& s) {
        s.pop_back();           // last character delete kar diya → /2 ho gaya
    }

    
    // Function 2: addOne
    // Kaam: binary number mein +1 karna (jaise school mein 199 + 1 = 200 hota hai)
    void addOne(string& s) {
        int i = s.size() - 1;       // last index se shuru karte hain (rightmost digit)

        // Jab tak '1' milta rahe, usko '0' banao aur carry aage le jao
        while (i >= 0 && s[i] != '0') {
            s[i] = '0';             // 1 ko 0 kar diya (carry generate hua)
            i--;                    // ek position left chale gaye
        }

        // Ab do cases bante hain:

        if (i < 0) {
            // Case 1: poora number 1111...1 tha
            // Example: 111 + 1 = 1000
            // Matlab starting mein ek naya '1' lagana padega
            s = '1' + s;            // "111" → "1000"  (s ab "1000" ban gaya)
        } 
        else {
            // Case 2: kahin pe '0' mila → usko '1' bana do
            // Example: 1011 + 1 = 1100
            //         1011
            //       +    1
            //       ------
            //         1100
            s[i] = '1';             // woh pehla 0 jo mila usko 1 kar diya
        }
    }

    
    // Main function: yeh decide karega kitne steps lage
    int numSteps(string s) {
        
        int operations = 0;         // yeh count karega kitne steps hue

        // Jab tak string mein 1 se zyada characters hain (yaani number > 1)
        while (s.size() > 1) {
            
            int N = s.size();       // har baar nayi length nikaal lo
                                    // kyunki addOne se length badh sakti hai

            // Last character check karo (LSB - least significant bit)
            if (s[N - 1] == '0') {
                // Even number → divide by 2
                divideByTwo(s);     // last digit hata diya
            } 
            else {
                // Odd number → +1 karo
                addOne(s);          // yeh function carry handle karega
            }

            operations++;           // har operation ke baad count badhao
                                    // chahe divide kiya ho ya add kiya ho
        }

        // Jab loop khatam hua matlab string "1" ban gayi
        return operations;
    }
};
