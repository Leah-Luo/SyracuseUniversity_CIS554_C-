//HW7 by Leah Luo

#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <string>
#include <list>


using namespace std;

class my_hash1 {
    //hash ( sum(matrix element->string->ASCII)   );
    //Will explain in class
public:
    size_t operator()(const vector<vector<int>>& M) const {
        int row = M.size();
        int col = M[0].size();
        int sum = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                string s = to_string(M[i][j]);
                for (auto c : s) {
                    sum += int(c);
                }
            }
        }
        hash<int> theHash;
        return theHash(sum);
    }
};

class my_equal_to1 {
    //equal num_rows && equal num_cols && equal sum(matrix element->string->ASCII);
    //Will explain in class
public:
    bool operator()(const vector<vector<int>>& M1, const vector<vector<int>>& M2) {
        if (M1.size() != M2.size() || M1[0].size() != M2[0].size()) return false;

        int row1 = M1.size();
        int col1 = M1[0].size();
        int sum1 = 0;
        int row2 = M2.size();
        int col2 = M2[0].size();
        int sum2 = 0;
        // M1
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col1; j++) {
                string s = to_string(M1[i][j]);
                for (auto c : s) {
                    sum1 += int(c);
                }
            }
        }
        // M2
        for (int i = 0; i < row2; i++) {
            for (int j = 0; j < col2; j++) {
                string s = to_string(M2[i][j]);
                for (auto c : s) {
                    sum2 += int(c);
                }
            }
        }
        return (sum1 == sum2);
    }
};


class myCompare1 {
    //compare sum(all ints)
public:
    bool operator()(const pair<list<int*>*, vector<int*>>& P1, const pair<list<int*>*, vector<int*>>& P2) {
        int sum1 = 0;
        int sum2 = 0;
        // P1
        for (auto i : *P1.first) sum1 += *i;
        for (auto j : P1.second) sum1 += *j;
        // P2
        for (auto i : *P2.first) sum2 += *i;
        for (auto j : P2.second) sum2 += *j;

        return (sum1 < sum2);
    }
};

class my_hash2 {
    //hash( sum ( int->string->ASCII)  )
    //will explain in class.
public:
    size_t operator()(const set<pair<list<int*>*, vector<int*>>, myCompare1>& S) const{
        int sum = 0;
        for (auto i = S.begin(); i != S.end(); i++) {
            for (auto j : *i->first) {
                string s = to_string(*j);
                for (auto c : s) sum += (int)c;
            }
            for (auto j : i->second) {
                string s = to_string(*j);
                for (auto c : s) sum += (int)c;
            }
        }
        hash<int> theHash;
        return theHash(sum);
    }
};

class my_equal_to2 {
    //equal hash(sum(int->string->ASCII))
public:
    bool operator()(const set<pair<list<int*>*, vector<int*>>, myCompare1>& S1, const set<pair<list<int*>*, vector<int*>>, myCompare1>& S2)const {
        int sum1 = 0;
        int sum2 = 0;
        // S1
        for (auto i = S1.begin(); i != S1.end(); i++) {
            for (auto j : *i->first) {
                string s = to_string(*j);
                for (auto c : s) sum1 += (int)c;
            }
            for (auto j : i->second) {
                string s = to_string(*j);
                for (auto c : s) sum1 += (int)c;
            }
        }
        // S2
        for (auto i = S2.begin(); i != S2.end(); i++) {
            for (auto j : *i->first) {
                string s = to_string(*j);
                for (auto c : s) sum2 += (int)c;
            }
            for (auto j : i->second) {
                string s = to_string(*j);
                for (auto c : s) sum2 += (int)c;
            }
        }
        return (sum1 == sum2);
    }
};

//Also implement all needed overloaded operator<<
// Matrix
ostream& operator<<(ostream& str, const vector<vector<int>> M) {
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M[0].size(); j++) {
            str << M[i][j] << " ";
        }
        str << endl;
    }
    return str;
}

// unordered_set
template<class T>ostream& operator<<(ostream& str, const unordered_set<T, my_hash1, my_equal_to1>& U) {
    for (auto M: U) {
        str << M << endl;
        str << endl;
    }
    return str;
}

// set<pair>
// { [ < 10 20 30 > ( 20 40 ) < 40 20 30 > ( 20 40 100 ) ]   [ < 10 20 30 > ( 20 40 ) < 40 20 30 > ( 20 40 200 ) ]  }
ostream& operator<<(ostream& str, const set<pair<list<int*>*, vector<int*>>, myCompare1>& S) {
    str << "{ ";
    for (auto i = S.begin(); i != S.end(); i++) {
        str << "[ " ;
        str << "< ";
        for (auto j : *i->first) {
            str << *j << " ";
        }
        str << "> ";
        str << "( ";
        for (auto j : i->second) {
            str << *j << " ";
        }
        str << ") ";
    }
    str << "}" << endl;
    return str;
}

// unsorted set
template<class T>ostream& operator<<(ostream& str, const unordered_set<T, my_hash2, my_equal_to2>& U) {
    for (auto S: U) {
        str << S << endl;
        str << endl;
    }
    return str;
}



int main() {
    int n;
    cin >> n;
    vector<vector<vector<int>>> M(n);
    //n matrices of r row and c columns.
    //where r and c are both random numbers in 10-25
    //all matrix elements are random numbers in 0-99.
    //Will explain in class
    for (int i = 0; i < n; i++) {
        int row = 10 + rand() % ((25 + 1) - 10);
        int col = 10 + rand() % ((25 + 1) - 10);
        vector<vector<int>> matrix;
        for (int r = 0; r < row; r++) {
            vector<int> theRow;
            for (int c = 0; c < col; c++) {
                theRow.push_back(rand() % 100);
            }
            matrix.push_back(theRow);
        }
        M[i] = matrix;
    }


    unordered_set<vector<vector<int>>, my_hash1, my_equal_to1> HT1;
    for (int i = 0; i < n; i++) {
        HT1.insert(M[i]);
    }
    cout << HT1 << endl;

    auto it = HT1.find(M[n - 1]);
    if (it != HT1.end()) {
        cout << *it << endl;
    }


    unordered_set<set<
    pair<list<int*>*, vector<int*>>, myCompare1>,
            my_hash2, my_equal_to2> HT2;

    set<pair<list<int*>*, vector<int*>>, myCompare1>
                                         s1{
                                                 { new list<int*>{new int{10}, new int{20}, new int{30} }   , {new int{20}, new int{40}}   },
                                                 { new list<int*>{new int{40}, new int{20}, new int{30} }   , {new int{20}, new int{40}, new int{100}}   }
                                         },
            s2{
                    { new list<int*>{new int{10}, new int{20}, new int{30} }   , {new int{20}, new int{40}} },
                    { new list<int*>{new int{40}, new int{20}, new int{30} }   , {new int{20}, new int{40}, new int{200}}   }
            };
    HT2.insert(s1);
    HT2.insert(s2);

    cout << HT2 << endl;
    cout << endl;
    auto it2 = HT2.find(s1);
    if (it2 != HT2.end())  cout << *it2 << endl;

    return 0;
}