//HW4 by Leah Luo

#include <iostream>
#include <list>
#include <string>

using namespace std;
template <class T> class ThreeD {
public:
    T ht;
    T wid;
    T dep;
    ThreeD() :ht(0), wid(0), dep(0) {}
    ThreeD(T i, T j, T k) :ht(i), wid(j), dep(k) {}
    T getVol() const { return ht * wid * dep; }
    bool operator==(const ThreeD<T>& t) const { return getVol() == t.getVol(); }
};

template <class T> class node {
public:
    T value;
    node<T>* next;
    node<T>* previous;
    node<T>() { next = nullptr; previous = nullptr; }
    node<T>(T v) { value = v; next = nullptr; previous = nullptr; }
    bool operator==(const node<T>& t) const { return value == t.value; }
};

template <class T> class linked_list {
public:
    node<T>* head;
    node<T>* tail;
    linked_list() { head = tail = nullptr; }
    linked_list(const initializer_list<T>& V); //initializer_list
    void push_front(T t);//The implementation is given below.
    void push_back(T t);//The implementation is given below.
    bool operator==(const linked_list<T>& L) const;

    linked_list(const linked_list<T>& L); //copy constructor
    linked_list(linked_list<T>&& L); //move constructor
    ~linked_list();//destructor
    void operator=(const linked_list<T>& L);//Lvalue operator= ; i.e., copy assignment
    void operator=(linked_list<T>&& L);//Rvalue operator= ; i.e., move assignment

};

// Initializer_list
template <class T> linked_list<T>::linked_list(const initializer_list<T>& V) : linked_list() {
    if (V.begin() == nullptr) return;
    auto i = V.begin();
    while (i != V.end()) {
        node<T>* p = new node<T>(*i);
        if (head == nullptr) {
            head = tail = p; 
        }
        else {
            p->previous = tail;
            tail->next = p; 
            tail = p; 
        }
        i++; 
    }
    cout << "initializer_list LL" << endl;
}

// Destructor
template <class T> linked_list<T>::~linked_list() {
    //Your code
    node<T>* i = head;
    while (i != nullptr) {
        auto tmp = i->next;
        delete i;
        i = tmp;
    }
    head = tail = nullptr;
    cout << "Destructor LL" << endl;
}

// Copy constructor (Lvalue)
template <class T> linked_list<T>::linked_list(const linked_list<T>& L) : linked_list() { //copy constructor																			  																		  //num_nodes = 0;
    //Your code
    auto i = L.head;
    while (i != nullptr) {
        push_back(i->value);
        i = i->next;
    }
    cout << "Copy Constructor LL" << endl;
}

// Move constructor (Rvalue)
template <class T> linked_list<T>::linked_list(linked_list<T>&& L) {
    //Your code
    head = L.head;
    L.head = nullptr;
    cout << "Move Constructor LL" << endl;
}

// Copy assignment (Lvalue operator =)
template <class T> 
void linked_list<T>::operator=(const linked_list<T>& L) {
    //Your code
    auto i = head;
    while (i != nullptr) {
        auto tmp = i->next;
        delete i;
        i = tmp;
    }
    auto p = L.head;
    while (p != nullptr) {
        push_back(p->value);
        p = p->next;
    }
    cout << "Copy Assignment LL" << endl;
}

// Move assignment (Rvalue operator =)
template<class T> 
void linked_list<T>::operator=(linked_list<T>&& L) {//R-value operator=
    //Your code
    delete head;
    head = L.head;
    L.head = nullptr;
    cout << "Move Assignment LL" << endl;
}

template <class T>
void linked_list<T>::push_front(T t) {
    node<T>* p = new node<T>(t);
    if (head == nullptr) { head = tail = p; }
    else {
        p->next = head;
        head->previous = p;
        head = p;
    }
}

template <class T>
void linked_list<T>::push_back(T t)
{
    node<T>* p = new node<T>(t);
    if (head == nullptr) { head = tail = p; }

    else {
        p->previous = tail;
        tail->next = p;
        tail = p;
    }
    //    cout << "call Push back " << endl;
}

// Linked lists are equal or not
template <class T>
bool linked_list<T>::operator==(const linked_list<T>& L) const {
    //Your code
    //Two linked lists are equal if they have same number of nodes, and each pair of corresponding nodes have equal values.
    int size_L1 = 0;
    int size_L2 = 0;
    auto l1 = head;
    auto l2 = L.head;

    while (l1 != nullptr) {
        size_L1++;
        l1 = l1->next;
    }
    while (l2 != nullptr) {
        size_L2++;
        l2 = l2->next;
    }
    if (size_L1 != size_L2) {
        cout << "operator== LL" << endl;
        return false; // Different number of nodes
    }

    l1 = head;
    l2 = L.head;
    while (l1 != nullptr) {
        if (l1->value == l2->value) {
            l1 = l1->next;
            l2 = l2->next;
        }
        else {
            cout << "operator== LL" << endl;
            return false;
        }
    }
    cout << "operator== LL" << endl;
    return true;
}

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t) {
    str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
    return str;
}

template <class T>
ostream& operator<<(ostream& str, const linked_list<T>& L) {
    str << "[";
    node<T>* p = L.head;
    while (p) {
        str << p->value << " ";
        p = p->next;
    }
    str << "]";
    return str;
}





template <typename T> class Node { //Your T has to support either int or float
public:
    T* pValue; //pValue is a pointer to an object of type T
    Node<T>* row_next;//Points to the next node in the same row
    Node<T>* col_next;//Points to the next node in the same col
    Node() {}
    Node(T v) { pValue = new T(v); }
};

template <typename T> class Ring2D {
public:
    Node<T>* head;//Points to the node at first row and first column
    T* pValue;

    Ring2D() {};

        //Implement the following functions:
    Ring2D(const initializer_list< initializer_list<T>>& I); //nested initializer_list; will explain in class
    /*
    For example, {{1, 2, 3, 4} , {5, 6, 7, 8},  {9, 10, 11, 12}}: 3 rows and 4 columns; first row: pointers to 1 2 3 4;
    second row: pointers to 5 6 7 8; third row: pointers to 9 10 11 12
    */
    ~Ring2D();//destructor;
    Ring2D(const Ring2D<T>& R);//copy constructor
    void operator=(const Ring2D<T>& R);//Lvalue operator=; i.e., copy assignment
    Ring2D(Ring2D<T>&& R);//move constructor
    void operator=(Ring2D<T>&& R);//Rvalue operator=; i.e.,move assignment
    Ring2D<T> ThreeTimes();//Return a Ring2D with values being three times of the current Ring2D
    bool operator==(const Ring2D<T>& R) const;
};

// If two Ring2Ds are equal or not
template <class T> 
bool Ring2D<T>::operator==(const Ring2D<T>& R) const {
    if (!head || !R.head) {
        cout << "Operator== Ring2D" << endl;
        return false;
    }

    //Find number of cols and rows
    Node<T>* p1 = head;
    Node<T>* pH = head;
    int col_cnt1 = 0;
    int row_cnt1 = 0;
    while (p1) {
        col_cnt1++;
        if (p1->col_next != pH) {
            p1 = p1->col_next;
        }
        else {
            break;
        }
    }
    p1 = head;
    while (p1) {
        row_cnt1++;
        if (p1->row_next != pH) {
            p1 = p1->row_next;
        }
        else {
            break;
        }
    }

    //Find number of cols and rows for R
    p1 = R.head;
    pH = R.head;
    int col_cnt2 = 0;
    int row_cnt2 = 0;
    while (p1) {
        col_cnt2++;
        if (p1->col_next != pH) {
            p1 = p1->col_next;
        }
        else {
            break;
        }
    }
    p1 = R.head;
    while (p1) {
        row_cnt2++;
        if (p1->row_next != pH) {
            p1 = p1->row_next;
        }
        else {
            break;
        }
    }

    // Check size 
    if ((col_cnt1 != col_cnt2) || (row_cnt1 != row_cnt2)) {
        cout << "Operator== Ring2D" << endl;
        return false;
    }

    // Check value 
    p1 = head;
    Node<T>* p2 = R.head;
    for (int i = 0; i < row_cnt1; i++) {
        for (int j = 0; j < col_cnt1; j++) {
            if (*p1->pValue == *p2->pValue) {
                p1 = p1->col_next;
                p2 = p2->col_next;
            }
            else {
                cout << "Operator== Ring2D" << endl;
                return false;
            }
        }
        p1 = p1->row_next;
        p2 = p2->row_next;
    }
    cout << "Operator== Ring2D" << endl;
    return true;
}

// Move assignment (Rvalue)
template <class T>
void Ring2D<T>::operator=(Ring2D<T>&& R) {//;//Rvalue operator=; move assignment
    // if needs to delete
    if (pValue) {
        Node<T>* p1 = head;
        Node<T>* pH = head;
        //Find number of cols and rows
        int col_cnt = 0;
        int row_cnt = 0;
        while (p1) {
            col_cnt++;
            if (p1->col_next != pH) {
                p1 = p1->col_next;
            }
            else {
                break;
            }
        }
        p1 = head;
        while (p1) {
            row_cnt++;
            if (p1->row_next != pH) {
                p1 = p1->row_next;
            }
            else {
                break;
            }
        }

        // Delete current Nodes 
        if (pValue)
            delete pValue;
        p1 = head;
        for (int i = 0; i < row_cnt; i++) {
            Node<T>* tmpR = p1->row_next;
            for (int j = 0; j < col_cnt; j++) {
                Node<T>* tmpC = p1->col_next;
                if (p1->pValue) delete p1->pValue; 
                delete p1;
                p1 = tmpC;
            }
            p1 = tmpR;
        }
    }

    head = R.head;
    pValue = R.pValue;
    R.head = nullptr;
    R.pValue = nullptr;

    cout << "Move Assignment Ring2D" << endl;
    //    return *this;
}

// Move constructor (Rvalue)
template<class T>
Ring2D<T>::Ring2D(Ring2D<T>&& R) {//;//move constructor
    head = R.head;
    pValue = R.pValue;
    R.head = nullptr;
    R.pValue = nullptr;
    cout << "Move Constructor Ring2D" << endl;
}


template <class T>
Ring2D<T> Ring2D<T>::ThreeTimes() {//ThreeTimes;
    Ring2D<T> temp{ *this };//copy constructor

    Node<T>* p1 = temp.head;
    Node<T>* pH = temp.head;
    //Find number of cols and rows
    int col_cnt = 0;
    int row_cnt = 0;
    while (p1) {
        col_cnt++;
        if (p1->col_next != pH) {
            p1 = p1->col_next;
        }
        else {
            break;
        }
    }
    p1 = temp.head;
    while (p1) {
        row_cnt++;
        if (p1->row_next != pH) {
            p1 = p1->row_next;
        }
        else {
            break;
        }
    }

    p1 = temp.head;
    for (int i = 0; i < row_cnt; i++) {
        for (int j = 0; j < col_cnt; j++) {
            *(p1->pValue) *= 3;
            p1 = p1->col_next;
        }
        p1 = p1->row_next;
    }
    cout << "ThreeTimes Ring2D" << endl;
    return temp;
}


// Destructor
template <class T>
Ring2D<T>::~Ring2D() {//;//destructor
    Node<T>* p1 = head;
    Node<T>* pH = head;

    //Find number of cols and rows
    int col_cnt = 0;
    int row_cnt = 0;
    while (p1) {
        col_cnt++;
        if (p1->col_next != pH) {
            p1 = p1->col_next;
        }
        else {
            break;
        }
    }
    p1 = head;
    while (p1) {
        row_cnt++;
        if (p1->row_next != pH) {
            p1 = p1->row_next;
        }
        else {
            break;
        }
    }

    p1 = head;
    for (int i = 0; i < row_cnt; i++) {
        auto tmpR = p1->row_next; 
        for (int j = 0; j < col_cnt; j++) {
            auto tmpC = p1->col_next;
            if (p1->pValue) delete p1->pValue;
            delete p1;
            p1 = tmpC;
        }
        p1 = tmpR;
    }
    cout << "Destructor Ring2D" << endl;
}

// Copy assignment (Lvalue)
template <class T>
void Ring2D<T>::operator=(const Ring2D<T>& R) {//;//Lvalue operator=; copy assignment
    // if needs to delete
    if (pValue) {
        Node<T>* p1 = head;
        Node<T>* pH = head;
        //Find number of cols and rows
        int col_cnt = 0;
        int row_cnt = 0;
        while (p1) {
            col_cnt++;
            if (p1->col_next != pH) {
                p1 = p1->col_next;
            }
            else {
                break;
            }
        }
        p1 = head;
        while (p1) {
            row_cnt++;
            if (p1->row_next != pH) {
                p1 = p1->row_next;
            }
            else {
                break;
            }
        }

        // Delete current Nodes 
        p1 = head;
        for (int i = 0; i < row_cnt; i++) {
            Node<T>* tmpR = p1->row_next;
            for (int j = 0; j < col_cnt; j++) {
                Node<T>* tmpC = p1->col_next;
                if (p1->pValue) delete p1->pValue;
                delete p1;
                p1 = tmpC;
            }
            p1 = tmpR;
        }
    }

    Node<T>* p1 = R.head;
    Node<T>* pH = R.head;
    Node<T>* p2 = nullptr;
    Node<T>* p3 = nullptr;
    Node<T>* preRow = nullptr;
    //Find number of cols and rows of R
    int col_cnt = 0;
    int row_cnt = 0;
    while (p1->col_next != pH) {
        col_cnt++;
        p1 = p1->col_next;
    }
    col_cnt++;
    p1 = R.head;
    while (p1->row_next != pH) {
        row_cnt++;
        p1 = p1->row_next;
    }
    row_cnt++;
    p1 = R.head;
    // Structure
    for (int i = 0; i < row_cnt; i++) {
        // first row
        if (preRow == nullptr) {
            for (int j = 0; j < col_cnt; j++) {
                p2 = new Node<T>();
                p2->col_next = head;
                head = p2;
            }
            // connect last node to first
            for (int j = 0; j < col_cnt - 1; j++) {
                p2 = p2->col_next;
            }
            p2->col_next = head;
            preRow = head;
        }
        // not first row
        else {
            for (int j = 0; j < col_cnt; j++) {
                p2 = new Node<T>();
                p2->col_next = p3;
                p3 = p2;  //p3 & p2: points to the new row
            }
            for (int j = 0; j < col_cnt - 1; j++) {
                p2 = p2->col_next;
            }
            p2->col_next = p3;   //p2:points to the last node;   p3: points to the first
            // connect current row with previous row
            for (int j = 0; j < col_cnt; j++) {
                preRow->row_next = p3;
                preRow = preRow->col_next;
                p3 = p3->col_next;
            }
            preRow = p3;
            p3 = nullptr;
        }
    }
    // connect last node to first for each col
    Node<T>* t = head;
    for (int j = 0; j < col_cnt; j++) {
        preRow->row_next = t;
        preRow = preRow->col_next;
        t = t->col_next;
    }

    // Assign value
    p2 = head;
    for (int i = 0; i < row_cnt; i++) {
        for (int j = 0; j < col_cnt; j++) {
            auto i = p1->pValue;
            p2->pValue = new T(*i);
            p2 = p2->col_next;
            p1 = p1->col_next;
        }
        p2 = p2->row_next;
        p1 = p1->row_next;
    }
    pValue = head->pValue;

    cout << "Copy Assignment Ring2D" << endl;
}

// Copy constructor
template<class T>
Ring2D<T>::Ring2D(const Ring2D<T>& R) {//copy constructor
    if (!R.pValue) return;

    Node<T>* p1 = R.head;
    Node<T>* pH = R.head;

    Node<T>* p2 = nullptr;
    Node<T>* p3 = nullptr;
    Node<T>* preRow = nullptr;

    //Find number of cols and rows
    int col_cnt = 0;
    int row_cnt = 0;
    while (p1->col_next != pH) {
        col_cnt++;
        p1 = p1->col_next;
    }
    col_cnt++;
    p1 = R.head;
    while (p1->row_next != pH) {
        row_cnt++;
        p1 = p1->row_next;
    }
    row_cnt++;
    p1 = R.head;

    // Structure
    for (int i = 0; i < row_cnt; i++) {
        // first row
        if (preRow == nullptr) {
            for (int j = 0; j < col_cnt; j++) {
                p2 = new Node<T>();
                p2->col_next = head;
                head = p2;
            }
            // connect last node to first
            for (int j = 0; j < col_cnt - 1; j++) {
                p2 = p2->col_next;
            }
            p2->col_next = head;
            preRow = head;
        }
        // not first row
        else {
            for (int j = 0; j < col_cnt; j++) {
                p2 = new Node<T>();
                p2->col_next = p3;
                p3 = p2;  //p3 & p2: points to the new row
            }
            for (int j = 0; j < col_cnt - 1; j++) {
                p2 = p2->col_next;
            }
            p2->col_next = p3;   //p2:points to the last node;   p3: points to the first
            // connect current row with previous row
            for (int j = 0; j < col_cnt; j++) {
                preRow->row_next = p3;
                preRow = preRow->col_next;
                p3 = p3->col_next;
            }
            preRow = p3;
            p3 = nullptr;
        }
    }
    // connect last node to first for each col
    Node<T>* t = head;
    for (int j = 0; j < col_cnt; j++) {
        preRow->row_next = t;
        preRow = preRow->col_next;
        t = t->col_next;
    }

    // Assign value
    p2 = head;
    for (int i = 0; i < row_cnt; i++) {
        for (int j = 0; j < col_cnt; j++) {
            auto i = p1->pValue;
            p2->pValue = new T(*i);
            p2 = p2->col_next;
            p1 = p1->col_next;
        }
        p2 = p2->row_next;
        p1 = p1->row_next;
    }
    pValue = head->pValue;

    cout << "Copy Constructor Ring2D" << endl;
}

// Initializer_list
template <class T>
Ring2D<T>::Ring2D(const initializer_list< initializer_list<T> >& I) {
    if (I.begin() == nullptr) {
        head = nullptr;
        pValue = nullptr;
        return;
    }
    if (I.begin()->begin() == nullptr) {
        head = nullptr;
        pValue = nullptr;
        return;
    }

    int row_cnt = I.size();
    int col_cnt = (*I.begin()).size();

    if (row_cnt == 0) return;


    Node<T>* p1 = nullptr;
    Node<T>* preRow = nullptr; 
    Node<T>* p3 = nullptr; 

    for (auto i = I.begin(); i != I.end(); i++) {  // Loop list
        // First row
        if (preRow == nullptr) {
        //if (preRow->pValue == nullptr) {
            auto j = i->end();
            j--;
            while (j != i->begin()) {
                Node<T>* p2 = new Node<T>();
                p2->pValue = new T(*j);
                p2->col_next = p1;
                p1 = p2;
                j--;
            }
            Node<T>* p2 = new Node<T>();
            p2->pValue = new T(*j);
            p2->col_next = p1;
            p1 = p2;
            preRow = p1;
            // Last node connects the first node
            Node<T>* t = p1;
            for (int k = 0; k < col_cnt - 1; k++) {
                t = t->col_next;
            }
            t->col_next = p1;
        }
        // Not first row
        else {
            auto j = i->end();
            j--;
            while (j != i->begin()) {
                Node<T>* p2 = new Node<T>();
                p2->pValue = new T(*j);
                p2->col_next = p3;
                p3 = p2;
                j--;
            }
            Node<T>* p2 = new Node<T>();
            p2->pValue = new T(*j);
            p2->col_next = p3;
            p3 = p2;
            // last node connects the first node
            Node<T>* t = p3;
            for (int k = 0; k < col_cnt - 1; k++) {
                t = t->col_next;
            }
            t->col_next = p3;
            // connect with previous row
            for (int k = 0; k < col_cnt; k++) {
                preRow->row_next = p3;
                preRow = preRow->col_next;
                p3 = p3->col_next;
            }
            preRow = p3;
            p3 = nullptr;
        }
    }
    // connect last node with first for each col
    Node<T>* t2 = p1;
    for (int k = 0; k < col_cnt; k++) {
        Node<T>* t3 = t2->col_next;
        for (int j = 0; j < row_cnt - 1; j++) {
            t3 = t3->row_next;
        }
        t3->row_next = t2->col_next;
        t2 = t2->col_next;
    }
    head = p1;
    pValue = head->pValue;
    cout << "initializer_list Ring2D" << endl;
}

template<class T> ostream& operator<<(ostream& str, const Ring2D<T>& R) {
    if (!R.pValue) return str;
    Node<T>* p1 = R.head;
    Node<T>* pH = R.head;

    //Find number of cols and rows
    int col_cnt = 0;
    int row_cnt = 0;
    while (p1->col_next != pH) {
        col_cnt++;
        p1 = p1->col_next;
    }
    col_cnt++;
    p1 = R.head;
    while (p1->row_next != pH) {
        row_cnt++;
        p1 = p1->row_next;
    }
    row_cnt++;
    p1 = R.head;

    for (int i = 0; i < row_cnt; i++) {
        str << "{ ";
        for (int j = 0; j < col_cnt; j++) {
            str << *(p1->pValue) << " ";
            p1 = p1->col_next;
        }
        str << "}" << endl;
        p1 = p1->row_next;
    }
    return str;
}



int main() {


    Ring2D<int> R1{ {1, 2, 3, 4},  {5, 6, 7, 8},  {9, 10, 11, 12} };//initializer_list
    cout << R1 << endl << endl;
    Ring2D<int> R2{ R1 };
    cout << R2 << endl;
    Ring2D<int> R3;
    R3 = R1;
    cout << R3 << endl;
    Ring2D<int> R4;
    R4 = R1.ThreeTimes();
    cout << R4 << endl;
    Ring2D<linked_list<ThreeD<int>>> R5{ {{{3,4,5},{7,1,4},{6,7,3}},{{8,4,2},{8,8,2}}},
        {{{9,5,4},{10,3,2},{7,9,1},{2,2,3}}, { {5,4,8 },{4,2,16  }, {7, 8, 4} } } };
    cout << R5 << endl;
    Ring2D<linked_list<ThreeD<int>>> R6{ {{{5,3,4,},{14,2,1},{6,7,3}},{{8,2,4},{8,4,4}}},
        {{{9,4,5},{10,3,2},{7,3,3},{2,3,2}}, { {4, 5,8 },{8,2,8  }, {2, 16, 7} } } };
    cout << R6 << endl;

    if (R5 == R6) cout << "EQUAL" << endl;
    else cout << "NOT EQUQL" << endl;

    Ring2D<linked_list<ThreeD<int>>>* p1 = new Ring2D<linked_list<ThreeD<int>>>
    { {{{5,3,4,},{14,2,1},{6,7,3}},{{8,2,4},{8,4,4}}},
        {{{9,4,5},{10,3,2},{7,3,3},{2,3,2}}, { {4, 5,8 },{8,2,8  }, {2, 16, 7} } } };
    cout << *p1 << endl;
    delete p1;

    return 0;
}