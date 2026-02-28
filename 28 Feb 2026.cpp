class Solution {
public:
    int concatenatedBinary(int n) {
        
        // Sabse pehle MOD define karte hain (10^9 + 7)
        // Ye common hota hai competitive programming mein jab answer bahut bada ho jata hai
        const int MOD = 1000000007;     // ya 1e9+7 likh sakte ho
        
        // res → ab tak jo concatenated binary number bana hai uska decimal value
        // hum ise hamesha MOD ke andar rakhenge
        long long res = 0;
        
        // bits → current number kitne bits ka hai (1,2,3,4,... tak badhega)
        // jaise:
        // 1     → 1 bit
        // 2,3   → 2 bit
        // 4-7   → 3 bit
        // 8-15  → 4 bit
        int bits = 0;

        // 1 se n tak har number ko add karenge (concatenate karne ka matlab)
        for(int i = 1; i <= n; i++) {
            
            // Important observation / trick
            // Jab bhi i power of 2 hota hai (1,2,4,8,16...), tab bits badhte hain
            // i & (i-1) == 0  → ye check batata hai ki number power of 2 hai ya nahi
            // Example:
            // i=1 → 1 & 0 = 0  → bits = 1
            // i=2 → 2 & 1 = 0  → bits = 2
            // i=3 → 3 & 2 = 2  ≠0 → bits same rahega
            // i=4 → 4 & 3 = 0  → bits = 3
            if((i & (i-1)) == 0) {
                bits++;
            }
            
            // Ab asli operation jo hum kar rahe hain:
            //
            // Hum chahte hain ki res ko left shift karein 'bits' position se
            // aur phir usme current number i ko add (OR) kar dein
            //
            // Yani mathematically:
            // new_res = res × (2 ^ bits) + i
            //
            // Kyunki left shift by k bits = multiply by 2^k
            
            // Lekin yahan dikkat hai:
            // res << bits   → agar bits bada ho (jaise 17,20,30) to long long bhi overflow kar jayega
            // Isliye hum directly shift nahi kar sakte
            
            // Is code mein (res << bits) | i   likha hai
            // Ye theoretically sahi hai, lekin practical mein C++ mein
            // long long ke liye shift 63 se zyada nahi kar sakte (undefined behavior)
            // aur MOD ke saath sahi tarike se kaam nahi karega
            
            // Fir bhi is code ka idea samajhna zaroori hai:
            res = ((res << bits) | i) % MOD;
            
            // Sahi aur safe tarika (jo zyadatar log use karte hain):
            // res = (res * mod_pow(2, bits, MOD) + i) % MOD;
            // ya fir loop se 2 se multiply karte jana
            
            // Yani yeh line asal mein galat nahi hai concept ke hisab se,
            // lekin implementation ke hisab se dangerous hai jab bits > 60
        }
        
        // last mein jo res bacha hai wahi answer hai
        return res;
    }
};
