//HW6 by Leah Luo

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class triple {
public:
    int value;
    int row;
    int col;
};

class node {
public:
    int value;
    int r_position;
    int c_position;
    shared_ptr<node> r_next;
    shared_ptr<node> c_next;
    node() { value = -9999; r_position = c_position = -1; }
    node(int v, int r, int c) { value = v; r_position = r; c_position = c; }

};
class matrix {
public:
    int num_rows;
    int num_cols;
    vector<shared_ptr<node>> r_vec;
    vector<shared_ptr<node>> c_vec;

    matrix() {} //default constructor
    matrix(int r, int c);
    //Constructor: to create a matrix of r rows, c cols
    //(r,c) will be randomly generated in the range of (0 …  num_rows -1,   0 … num_cols -1).


    //**********************//
    //You need to implement all the following member function plus overloaded operator<< for "cout << M <<endl; where M is a matrix object.
    void add_node(int v, int r, int c);
    //Create a new node with value v at row r and col c.
    //If there already exist an element at this position, then just update the node
    //value at this position to v, and do not create a new node.

    matrix(int r, int c, int n, int k);
    //Constructor: To create a matrix of r rows, c cols, n nodes, with values randomly in -(k-1) ... (k-1);

    matrix operator+(const matrix& M);//matrix addition
    matrix operator*(const matrix& M); //matrix multiplication

    matrix(const initializer_list < triple>& I);//initializer_list
    //First triple is (-1, num_rows, num_cols), where -1 will be ignored, and all other triples are nodes (value, r_position, c_position).

    matrix(const matrix& M);//copy constructor
    void operator=(const matrix& M);//copy assignment
    ~matrix();//destructor
    //You should do as few operations as possible to best benefit from smart pointers.

    matrix(matrix&& M);//move constructor
    void operator=(matrix&& M);//move assignment
};


// Print out matrix row by row 
ostream& operator<<(ostream& str, const matrix& M) {
    for (int i = 0; i < M.num_rows; i++) {
        auto p = M.r_vec[i];
        bool print = false;
        while (p) {
            print = true;
            str << p->value << " " << p->r_position << " " << p->c_position << "  ";
            p = p->r_next;
        }
        if (print) str << endl;
    }
    return str;
}

// Print out matrix col by col 
ostream& operator<(ostream& str, const matrix& M) {
    for (int j = 0; j < M.num_cols; j++) {
        auto p = M.c_vec[j];
        bool print = false;
        while (p) {
            print = true;
            str << p->value << " " << p->r_position << " " << p->c_position << "  ";
            p = p->c_next;
        }
        if (print) str << endl;
    }
    return str;
}

// Constructor 
matrix::matrix(int r, int c) {
    num_rows = r;
    num_cols = c;
    r_vec.assign(r, nullptr); // r nodes with value of nullptr
    c_vec.assign(c, nullptr);
}

// Constructor
matrix::matrix(int r, int c, int n, int k) {
    num_rows = r;
    num_cols = c;
    r_vec.assign(r, nullptr); // r nodes with value of nullptr
    c_vec.assign(c, nullptr);

    for (int i = 0; i < n; i++) {
        int v = (rand() % (2 * k - 2)) - (k - 1); // number between -(k-1) and (k-1)
        int r = rand() % num_rows;
        int c = rand() % num_cols;
        add_node(v, r, c);
    }
}

// Initializer_list
matrix::matrix(const initializer_list<triple>& I) : matrix() {
    if (I.begin() == nullptr) {
        num_rows = 0;
        num_cols = 0;
        r_vec.assign(num_rows, nullptr);
        c_vec.assign(num_cols, nullptr);
        return;
    }

    auto i = I.begin();
    num_rows = i->row;
    num_cols = i->col;
    r_vec.assign(num_rows, nullptr);
    c_vec.assign(num_cols, nullptr);

    for (auto j = I.begin() + 1; j != I.end(); j++) {
        add_node(j->value, j->row, j->col);
    }
    cout << "initializer_list" << endl;
}

// Destructor
matrix::~matrix() {
    for (int i = 0; i < num_rows; i++) {
        r_vec[i].reset();
    }
    for (int j = 0; j < num_cols; j++) {
        c_vec[j].reset();
    }
    cout << "Destructor" << endl;
}

// Copy constructor
matrix::matrix(const matrix& M) : matrix() {
    if (M.num_cols == 0 && M.num_rows == 0) return;
    num_cols = M.num_cols;
    num_rows = M.num_rows;
    r_vec.assign(num_rows, nullptr);
    c_vec.assign(num_cols, nullptr);

    for (auto n : M.r_vec) {
        if (n) {
            while (n) {
                add_node(n->value, n->r_position, n->c_position);
                n = n->r_next; 
            }
        }
    }
    cout << "Copy Constructor" << endl; 
}

// Move constructor
matrix::matrix(matrix&& M) : matrix() {
    num_cols = M.num_cols;
    num_rows = M.num_rows;
    r_vec.assign(num_rows, nullptr); 
    c_vec.assign(num_cols, nullptr);

    for (int i = 0; i < num_rows; i++) {
        if (M.r_vec[i]) {
            auto p = M.r_vec[i];
            r_vec[i] = p; 
        }
    }
    for (int j = 0; j < num_cols; j++) {
        if (M.c_vec[j]) {
            auto p = M.c_vec[j];
            c_vec[j] = p;
        }
    }

    // delete M
    M.num_cols = 0;
    M.num_rows = 0;
    for (int i = 0; i < num_rows; i++) {
        M.r_vec[i].reset();
    }
    for (int j = 0; j < num_cols; j++) {
        M.c_vec[j].reset();
    }

    cout << "Move Constructor" << endl;
}

// Copy assignment (Lvalue operator =)
void matrix::operator=(const matrix& M) {
    // Delete
    for (int i = 0; i < num_rows; i++) {
        r_vec[i].reset();
    }
    for (int j = 0; j < num_cols; j++) {
        c_vec[j].reset();
    }
    num_rows = 0;
    num_cols = 0;

    // Copy
    num_cols = M.num_cols;
    num_rows = M.num_rows;
    r_vec.assign(num_rows, nullptr);
    c_vec.assign(num_cols, nullptr);

    for (auto n : M.r_vec) {
        if (n) {
            while (n) {
                add_node(n->value, n->r_position, n->c_position);
                n = n->r_next; 
            }
        }
    }

    cout << "Copy Assignment" << endl;
}

// Move assignment
void matrix::operator=(matrix&& M) {
    //Delete
    for (int i = 0; i < num_rows; i++) {
        r_vec[i].reset();
    }
    for (int j = 0; j < num_cols; j++) {
        c_vec[j].reset();
    }
    num_rows = 0;
    num_cols = 0;

    //Assign
    num_cols = M.num_cols;
    num_rows = M.num_rows;
    r_vec.assign(num_rows, nullptr); // r nodes with value of nullptr
    c_vec.assign(num_cols, nullptr);

    for (int i = 0; i < num_rows; i++) {
        if (M.r_vec[i]) {
            auto p = M.r_vec[i];
            r_vec[i] = p;
        } 
    }
    for (int j = 0; j < num_cols; j++) {
        if (M.c_vec[j]) {
            auto p = M.c_vec[j];
            c_vec[j] = p;
        }
    }

    M.num_cols = 0;
    M.num_rows = 0;
    for (int i = 0; i < num_rows; i++) {
        M.r_vec[i].reset();
    }
    for (int j = 0; j < num_cols; j++) {
        M.c_vec[j].reset();
    }

    cout << "Move Assignment" << endl;
}

// Add 
matrix matrix::operator+(const matrix& M) {
    matrix temp{ *this };
    if (num_cols == 0 && num_rows == 0) return M;
    if (M.num_cols == 0 && M.num_rows == 0) return temp;

    vector<vector<shared_ptr<node>>> table(num_rows, vector<shared_ptr<node>>(num_cols, nullptr));
    // put all the nodes of matrix
    for (int i = 0; i < num_rows; i++) {
        auto p = r_vec[i];
        while (p) {
            table[p->r_position][p->c_position] = p;
            p = p->r_next;
        }
    }

    // put all the nodes of M
    for (int i = 0; i < num_rows; i++) {
        auto p = M.r_vec[i];
        while (p) {
            // has node already
            if (table[p->r_position][p->c_position]) {
                temp.add_node(table[i][p->c_position]->value + p->value, p->r_position, p->c_position);
            }
            else {
                temp.add_node(p->value, p->r_position, p->c_position);
            }
            p = p->r_next;
        }
    }
    cout << "operator+" << endl;
    return temp;
}

// Multiply
matrix matrix::operator*(const matrix& M) {
    vector<vector<shared_ptr<node>>> result(num_rows, vector<shared_ptr<node>>(M.num_cols, nullptr));
    matrix r;
    r.num_cols = M.num_cols;
    r.num_rows = num_rows;
    r.r_vec.assign(r.num_rows, nullptr);
    r.c_vec.assign(r.num_cols, nullptr);

    // matrix 1
    vector<vector<shared_ptr<node>>> table(num_rows, vector<shared_ptr<node>>(num_cols, nullptr));
    // put all the nodes of matrix
    for (int i = 0; i < num_rows; i++) {
        auto p = r_vec[i];
        while (p) {
            table[p->r_position][p->c_position] = p;
            p = p->r_next;
        }
    }

    // matrix 2
    vector<vector<shared_ptr<node>>> table2(M.num_rows, vector<shared_ptr<node>>(M.num_cols, nullptr));
    // put all the nodes of matrix M
    for (int i = 0; i < M.num_rows; i++) {
        auto p = M.r_vec[i];
        while (p) {
            table2[p->r_position][p->c_position] = p;
            p = p->r_next;
        }
    }

    // *
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < M.num_cols; j++) {
            for (int k = 0; k < num_cols; k++) {
                if (table[i][k] && table2[k][j]) {
                    if (!result[i][j]) {
                        auto p = new node();
                        p->value = table[i][k]->value * table2[k][j]->value;
                        p->r_position = i;
                        p->c_position = j;
                        result[i][j] = static_cast<shared_ptr<node>>(p);
                    }
                    else {
                        result[i][j]->value += table[i][k]->value * table2[k][j]->value;
                    }
                }
            }
        }
    }
    for (auto i = 0; i < num_rows; i++) {
        for (auto j = 0; j < M.num_cols; j++) {
            if (result[i][j]) {
                r.add_node(result[i][j]->value, i, j);
            }
        }
    }

    //Delete result table 
    for (auto i = 0; i < num_rows; i++) {
        for (int j = 0; j < M.num_cols; j++) {
            if (result[i][j]) {
                result[i][j].reset(); 
            }
        }
    }


    cout << "operator*" << endl;
    return r;
}


void matrix::add_node(int v, int r, int c) {
    if (r >= num_rows) return; // out of scope
    if (c >= num_cols) return; // out of scope
    shared_ptr<node> n = make_shared<node>(v, r, c);
    shared_ptr<node> previous = nullptr;
    shared_ptr<node> current = nullptr;
    bool insert = false;
    bool insertC = false;

    // ROW
    // row is empty
    if (r_vec[r] == nullptr) {
        if (v != 0) r_vec[r] = n;
        insert = true;
    }
    // row isn't empty
    else {
        previous = r_vec[r];
        current = previous->r_next;

        // if previous is the only node
        if (!current) {
            // if previous is the node
            if (previous->c_position == c) {
                if (v != 0) previous->value = v; //update
                    // delete
                else r_vec[r].reset();
            }
            // if insert node before previous
            else if (previous->c_position > c) {
                if (v != 0) {
                    auto p = r_vec[r];
                    r_vec[r] = n;
                    n->r_next = p;
                }
                else {};
            }
            // if insert node after previous
            else {
                if (v != 0) previous->r_next = n;
                else {};
            }
            insert = true;
        }

        // if previous isn't the only node
        // if previous is the node
        if (!insert && previous->c_position == c) {
            if (v != 0) previous->value = v; //update
                // delete
            else {
                r_vec[r] = current;
                previous.reset();
            }
            insert = true;
        }
        // if need to insert node before previous
        if (!insert && previous->c_position > c) {
            if (v != 0) {
                auto p = r_vec[r];
                r_vec[r] = n;
                n->r_next = p;
            }
            insert = true;
        }

        // loop entire row
        while (!insert && current) {
            if (current->c_position < c) {
            }
            // if current is the node
            if (current->c_position == c) {
                if (v != 0) current->value = v; //update
                    // delete
                else {
                    //current is the last node
                    if (!current->r_next) {
                        previous->r_next = nullptr;
                        current.reset();
                    }
                    // current isn't the last node
                    else {
                        previous->r_next = current->r_next;
                        current.reset();
                    }
                }
                break;
            }
            // insert node before current node
            if (current->c_position > c) {
                if (v != 0) {
                    previous->r_next = n;
                    n->r_next = current;
                    break;
                }
                else break;
            }
            // if current isn't the last node
            if (current->r_next) {
                previous = current;
                current = current->r_next;
            }
            // end of iteration, insert node at the end
            else {
                if (v != 0) {
                    current->r_next = n;
                    break;
                }
                else break;
            }
        }
    }


    // COLUMN
    // column is empty
    if (c_vec[c] == nullptr) {
        if (v != 0) c_vec[c] = n;
        insertC = true;
    }
    // column isn't empty
    else {
        previous = c_vec[c];
        current = previous->c_next;

        // Only 1 node in the column
        if (!current) {
            // if previous is the node
            if (previous->r_position == r) {
                if (v != 0) previous->value = v; //update
                    // delete
                else c_vec[c].reset();
            }
            // insert node before previous
            else if (previous->r_position > r) {
                if (v != 0) {
                    auto p = c_vec[c];
                    c_vec[c] = n;
                    n->c_next = p;
                }
            }
            // insert node after previous
            else {
                if (v != 0) previous->c_next = n;
            }

            insertC = true;
        }

        // if previous isn't the only node
        // if previous is the node
        if (!insertC && previous->r_position == r) {
            if (v != 0) previous->value = v; //update
                // delete
            else {
                c_vec[c] = current;
                previous.reset();
            }
            insertC = true;
        }
        // if need to insert node before previous
        if (!insertC && previous->r_position > r) {
            if (v != 0) {
                auto p = c_vec[c];
                c_vec[c] = n;
                n->c_next = p;
            }
            insertC = true;
        }

        // loop entire column
        while (!insertC && current) {
            if (current->r_position < r) {
            }
            // if current is the node
            if (current->r_position == r) {
                if (v != 0) current->value = v; //update
                    // delete
                else {
                    // if current is the last node
                    if (!current->c_next) {
                        previous->c_next = nullptr;
                        current.reset();
                    }
                    // current isn't the last node
                    else {
                        previous->c_next = current->c_next;
                        current.reset();
                    }
                }
                break;
            }
            // insert node before current node
            if (current->r_position > r) {
                if (v != 0) {
                    previous->c_next = n;
                    n->c_next = current;
                    break;
                }
                else break;
            }
            // if current isn't the last node, keep looping
            if (current->c_next) {
                previous = current;
                current = current->c_next;
            }
            // end of iteration, insert node at the end
            else {
                if (v != 0) {
                    current->c_next = n;
                    break;
                }
                else break;
            }
        }
    }

    return;
}




int main() {
    
    matrix M1(7, 5, 11, 8), M2(7, 5, 10, 8), M3(7, 5), M4(5, 6, 13, 9), M5(7, 6);
    cout << M1 << endl << endl;
    cout << M2 << endl << endl;
    M3 = M1 + M2;
    cout << M3 << endl << endl;
    cout << M4 << endl << endl;
    M5 = M1 * M4;
    cout << M5 << endl << endl;
    
    matrix  M6{ {-1,6, 5},{ 300, 4 ,3} , { 200, 4, 2 }, {100, 3, 2}, };
    //M6's num_rows = 6, num_cols = 5, and there are three non-zero nodes in M6.
    cout << M6 << endl << endl;
    matrix M7{ M6 };
    cout << M7 << endl << endl;
    matrix M8;
    M8 = M7;
    cout << M8 << endl;
    return 0;
}

/*
//The following is a sample screenshot

7 0 0  -4 0 2
4 1 4
2 3 3  3 3 4
5 4 1
-5 5 1
4 6 0  -6 6 1  4 6 2


-5 0 0  7 0 1  7 0 2  5 0 3
1 1 2
-5 2 3
2 3 1
-6 4 0
-1 5 3


operator+
Move Constructor
Destructor
Move Assignment
Destructor

2 0 0  7 0 1  3 0 2  5 0 3
1 1 2  4 1 4
-5 2 3
2 3 1  2 3 3  3 3 4
-6 4 0  5 4 1
-5 5 1  -1 5 3
4 6 0  -6 6 1  4 6 2


-3 0 4
8 1 3  7 1 4
-6 2 3  -7 2 4
7 3 3  -2 3 4  -8 3 5
4 4 2  1 4 4

operator*
Move Constructor
Destructor
Move Assignment
Destructor

24 0 3  7 0 4
16 1 2  4 1 4
12 3 2  14 3 3  -1 3 4  -16 3 5
40 4 3  35 4 4
-40 5 3  -35 5 4
-72 6 3  -82 6 4

initializer_list

100 3 2
200 4 2  300 4 3

Copy Constructor

100 3 2
200 4 2  300 4 3

Copy Assignment

100 3 2
200 4 2  300 4 3
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor

*/