// ==================== PROBLEM FULL SUMMARY ====================
/*
PROBLEM (10 saal ke bacche style):
Ek rectangular copy pe sirf 0 aur 1 likhe hain.
Ek 1 "special" tab hai jab:
→ uski poori row mein sirf wahi ek 1 ho
→ uske poore column mein sirf wahi ek 1 ho

Kitne aise special 1 hain? Batao.

CORE SECRET:
Pehle har row aur har column mein kitne 1 hain — yeh count kar lo.
Phir sirf un 1s ko count karo jinke row mein total 1s == 1 aur column mein total 1s == 1.

Yeh secret miss kiya toh O(mn(m+n)) brute force likh doge.

REAL-WORLD ANALOGY:
School attendance register:
Ek din special attendance day tab jab:
→ us din sirf ek hi baccha present tha
→ woh baccha usi ek din hi present tha poore saal mein

REVISION TABLE (markdown style comment mein):
Approach          | Time       | Space   | Rating
------------------|------------|---------|-------
Brute force       | O(mn(m+n)) | O(1)    | Avoid
Precompute sums   | O(mn)      | O(m+n)  | Best

MOTIVATION:
Yeh problem 5-7 min mein solve hona chahiye.
Abhi better code likh, submit kar.
Nahi kiya toh career waste, parents ka sacrifice bekaar.
Iron heart bana, execute kar.
*/

class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        
        // m = rows (kitni lines hain copy pe)
        // n = columns (ek line mein kitne boxes)
        int m = mat.size();
        int n = mat[0].size();
        
        // Har row mein kitne 1 hain — yeh pehle se count kar lenge
        vector<int> rowSum(m, 0);
        
        // Har column mein kitne 1 hain
        vector<int> colSum(n, 0);
        
        // ===================== PHASE 1: Precompute sums =====================
        // Ek baar poori matrix traverse → row aur column dono ka sum nikal lo
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(mat[i][j] == 1) {
                    rowSum[i]++;     // is row mein ek aur 1 mila
                    colSum[j]++;     // is column mein ek aur 1 mila
                }
            }
        }
        
        // ===================== PHASE 2: Count special positions =====================
        int ans = 0;
        
        // Ab doosri baar matrix dekho
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                
                // Sirf tab check karo jab yeh cell 1 ho
                if(mat[i][j] == 1) {
                    
                    // MAGIC CONDITION:
                    // Agar is row mein total sirf 1 hi 1 hai
                    // Aur is column mein bhi sirf 1 hi 1 hai
                    // Toh yeh special hai (kyunki yahi ekmatra 1 hai row aur col dono mein)
                    if(rowSum[i] == 1 && colSum[j] == 1) {
                        ans++;
                    }
                }
            }
        }
        
        return ans;
    }
};
