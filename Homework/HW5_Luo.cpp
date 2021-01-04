// HW5 by Leah Luo

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>

using namespace std;


// myCompare1 compares all the keys in map
class myCompare1 {
public:
    bool operator() (const list<int*>* L1, const list<int*>* L2) const {
        int s1 = 0;
        int s2 = 0;
        for (auto i : *L1) {
            s1 += *i;
        }
        for (auto j : *L2) {
            s2 += *j;
        }
        return s1 < s2;
    }
};

// Compares the map
class myCompare2 {
public:
    bool operator() (const map<list<int*>*, vector<int>*, myCompare1> M1, const map<list<int*>*, vector<int>*, myCompare1> M2) const {
        int s1 = 0;
        int s2 = 0;
        for (auto i : M1) {
            // Key
            for (auto j : *i.first) {
                s1 += *j;
            }
            for (auto j : *i.second) {
                s1 += j;
            }
        }
        for (auto i : M2) {
            // Key
            for (auto j : *i.first) {
                s2 += *j;
            }
            for (auto j : *i.second) {
                s2 += j;
            }
        }
        return s1 < s2;
    }
};

bool f1(map < list<int*>*, vector<int*>*, myCompare1 > M1, map < list<int*>*, vector<int*>*, myCompare1 > M2) {
    int s1 = 0;
    int s2 = 0;
    for (auto i : M1) {
        for (auto j : *i.first) {
            s1 += *j;
        }
        for (auto k : *i.second) {
            s1 += *k;
        }
    }
    for (auto i : M2) {
        for (auto j : *i.first) {
            s2 += *j;
        }
        for (auto k : *i.second) {
            s2 += *k;
        }
    }

    return s1 < s2;
}

class f2 {
public:
    bool operator() (map < list<int*>*, vector<int*>*, myCompare1 > M1, map < list<int*>*, vector<int*>*, myCompare1 > M2) const {
        int s1 = 0;
        int s2 = 0;
        for (auto i : M1) {
            for (auto j : *i.first) {
                s1 += *j;
            }
            for (auto k : *i.second) {
                s1 += *k;
            }
        }
        for (auto i : M2) {
            for (auto j : *i.first) {
                s2 += *j;
            }
            for (auto k : *i.second) {
                s2 += *k;
            }
        }
        return s1 < s2;
    }
} f2;



ostream& operator<<(ostream& str, const set<map<list<int*>*, vector<int>*, myCompare1>, myCompare2>& S) {
    str << "{ ";
    for (auto M : S) {
        str << "< ";
        map<list<int*>*, vector<int>*, myCompare1>* m = &M;
        for (auto j : *m) {
            list<int*>* lst = j.first;
            vector<int>* vec = j.second;
            str << "( ";
            for (auto k : *lst) {
                str << *k << " ";
            }
            str << ")";
            str << " [ ";
            for (auto k : *vec) {
                str << k << " ";
            }
            str << "] ";
        }
        str << "> ";
    }
    str << "}";
    return str;
}

ostream& operator<<(ostream& str, const list<map<list<int*>*, vector<int*>*, myCompare1>>& L) {
    str << "( ";
    for (auto i : L) {
        map<list<int*>*, vector<int*>*, myCompare1>* m = &i;
        str << "< ";
        for (auto j : *m) {
            list<int*>* lst = j.first;
            vector<int*>* vec = j.second;
            str << "( ";
            for (auto k : *lst) {
                str << *k << " ";
            }
            str << ")";
            str << " [ ";
            for (auto k : *vec) {
                str << *k << " ";
            }
            str << "] ";
        }
        str << "> ";
    }
    str << ")";
    return str;
}



int main() {

    set< map< list<int*>*, vector<int>*, myCompare1>, myCompare2> M1
    {
            {   {
                        { new list<int*>{new int{10}, new int{20}, new int{30} }   , new vector<int> {20, 40}   },
                        { new list<int*>{new int{40}, new int{20}, new int{30} }   , new vector<int> {20, 40,100}   }
                }
            },


            {	{
                        { new list<int*>{new int{10}, new int{20}, new int{30} }   , new vector<int> {20, 40}   },
                        { new list<int*>{new int{40}, new int{20}, new int{30} }   , new vector<int> {20, 40, 200}   }
                }
            }
    };
    //Implement the needed overloading operator<< to support the following printing.
    cout << M1 << endl;



    /*
    For the following, implement the functions used
    in sorting the list elements using regular function, functor, and lambda in the three cases.
    In addition, you need to implement the needed overloaded operator<< to supporting the printing.
    */

    cout << endl;
    list<map < list<int*>*, vector<int*>*, myCompare1 >> L1{ {
                                                                      {
                                                                              new list<int*>{new int{10}, new int{20}, new int{30} } ,
                                                                              new vector<int*> {new int{20}, new int{400}}
                                                                      },

                                                                      {
                                                                              new list<int*>{new int{40}, new int{20}, new int{30} }   ,
                                                                              new vector<int*> {new int{20}, new int{40}, new int{100}}
                                                                      }
                                                              } , {
                                                                      {
                                                                              new list<int*>{new int{10}, new int{20}, new int{30} } ,
                                                                              new vector<int*> {new int{20}, new int{40}}
                                                                      },

                                                                      {
                                                                              new list<int*>{new int{40}, new int{20}, new int{30} }   ,
                                                                              new vector<int*> {new int{20}, new int{40}, new int{200}}
                                                                      }
                                                              } };
    cout << L1 << endl;
    L1.sort(f1);//???: use a regular function f1
    cout << L1 << endl;
    cout << endl;
    list<map < list<int*>*, vector<int*>*, myCompare1 >> L2{ {
                                                                     {
                                                                             new list<int*>{new int{10}, new int{20}, new int{30} } ,
                                                                             new vector<int*> {new int{20}, new int{400}}
                                                                     },

                                                                     {
                                                                             new list<int*>{new int{40}, new int{20}, new int{30} }   ,
                                                                             new vector<int*> {new int{20}, new int{40}, new int{100}}
                                                                     }
                                                             } , {
                                                                     {
                                                                             new list<int*>{new int{10}, new int{20}, new int{30} } ,
                                                                             new vector<int*> {new int{20}, new int{40}}
                                                                     },

                                                                     {
                                                                             new list<int*>{new int{40}, new int{20}, new int{30} }   ,
                                                                             new vector<int*> {new int{20}, new int{40}, new int{200}}
                                                                     }
                                                             } };

    cout << L2 << endl;
    L2.sort(f2);//use a functor f2
    cout << L2 << endl;
    cout << endl;

    list<map < list<int*>*, vector<int*>*, myCompare1 >> L3{ {
                                                                     {
                                                                             new list<int*>{new int{10}, new int{20}, new int{30} } ,
                                                                             new vector<int*> {new int{20}, new int{400}}
                                                                     },

                                                                     {
                                                                             new list<int*>{new int{40}, new int{20}, new int{30} }   ,
                                                                             new vector<int*> {new int{20}, new int{40}, new int{100}}
                                                                     }
                                                             } , {
                                                                     {
                                                                             new list<int*>{new int{10}, new int{20}, new int{30} } ,
                                                                             new vector<int*> {new int{20}, new int{40}}
                                                                     },

                                                                     {
                                                                             new list<int*>{new int{40}, new int{20}, new int{30} }   ,
                                                                             new vector<int*> {new int{20}, new int{40}, new int{200}}
                                                                     }
                                                             } };

    //list<map < list<int*>*, vector<int*>*, myCompare1 >> L3
    cout << L3 << endl;
    L3.sort([](map < list<int*>*, vector<int*>*, myCompare1 > M1, map < list<int*>*, vector<int*>*, myCompare1 > M2) {
        int s1 = 0;
        int s2 = 0;
        for (auto i : M1) {
            for (auto j : *i.first) {
                s1 += *j;
            }
            for (auto k : *i.second) {
                s1 += *k;
            }
        }
        for (auto i : M2) {
            for (auto j : *i.first) {
                s2 += *j;
            }
            for (auto k : *i.second) {
                s2 += *k;
            }
        }
        return s1 < s2;
        });//???: use a lambda
    cout << L3 << endl;



    return 0;
}
//The following is a sample display
/*

{ < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 100 ] >  < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] >  }

( < ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] > < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] > )
( < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] > < ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] > )

( < ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] > < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] > )
( < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] > < ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] > )

( < ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] > < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] > )
( < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] > < ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] > )

*/