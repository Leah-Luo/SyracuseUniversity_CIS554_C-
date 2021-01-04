//HW3 by Leah Luo

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <iomanip>
using namespace std;

class course {
public:
    string name;
    int section;
    int credits;
    string grade;
    course() {}
    course(string n, int s, int c, string g) { name = n; section = s; credits = c; grade = g; }

    //You might need to implement some overloaded operators here.
    bool operator==(const course& c) const {
        return name == c.name && section == c.section && credits == c.credits && grade == c.grade;
    }

    bool operator>(const course& c) const {
        return name > c.name;
    }

};
//Implement the following functions.
//When adding a student, if the student is already in DB, then ignore the operation.
//When adding a course, if the course is already in DB, then ignore the operation.
//When dropping a course, if the course does not exist, then ignore the operation.
//When removing a student, if the student does not exist, then ignore the operation.
//All courses in a semester need to be sorted.
//When dropping or adding a course, overall GPA, semester GPA, overall credits and semester credits all need to be updated.

//Semeser numbers:  Spring 2019: 20191; Fall 2019: 20192, etc.

void add_student(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int id);
void remove_student(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int id);
void add_course(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
//All courses in the list should be sorted according to name (increasing order)
void drop_course(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int semester, int id, course c);
void print_student_semester_courses(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int semester, int id);
void print_student_all_courses(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int id);

//Implement additional functions such that you can do
//cout << DB << endl;

//You might need to implement some overloaded operators in the course class.


// To do cout << DB << endl;
ostream& operator<<(ostream& str, const  list< tuple<int, int, float, map<int, pair< pair<int, float>*, list<course*> *> *> *> >& DB) {
    str << "DB: " << endl;
    for (auto i : DB) {
        str << "ID: " << get<0>(i) << endl;
        str << "Overall GPA: " << setprecision(2) << fixed << get<2>(i) << endl;
        str << "Overall Credits: " << get<1>(i) << endl;
        auto M = *get<3>(i);
        for (auto sem : M) {
            str << "Semester: " << sem.first << endl;
            str << "GPA: " << setprecision(2) << fixed << sem.second->first->second << endl;
            str << "Credits " << sem.second->first->first << endl;
            auto lst = *sem.second->second;
            str << "( ";
            for (auto itr = lst.begin(); itr != lst.end(); itr++) {
                str << "(";
                str << (*itr)->name << " " << (*itr)->section << " " << (*itr)->credits << " " << (*itr)->grade;
                str << ") ";
            }
            str << ")" << endl;
        }
    }
    return str;
}




int main() {

    list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*> *> *> > DB;



    add_student(DB, 11111);
    course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");

    add_course(DB, 20171, 11111, C1);
    add_course(DB, 20171, 11111, C4);
    add_course(DB, 20171, 11111, C3);
    add_course(DB, 20171, 11111, C2);
    print_student_semester_courses(DB, 20171, 11111);

    drop_course(DB, 20171, 11111, C1);
    print_student_semester_courses(DB, 20171, 11111); //sorted according to course name

    course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");
    add_course(DB, 20172, 11111, C5);
    add_course(DB, 20172, 11111, C6);
    add_course(DB, 20172, 11111, C7);
    add_course(DB, 20172, 11111, C8);
    add_course(DB, 20172, 11111, C3);
    print_student_all_courses(DB, 11111);//ID GPA

    add_student(DB, 11112);
    add_course(DB, 20171, 11112, C2);
    add_course(DB, 20171, 11112, C5);
    add_course(DB, 20171, 11112, C7);
    add_course(DB, 20171, 11112, C4);
    print_student_semester_courses(DB, 20171, 11112);

    add_course(DB, 20172, 11112, C8);
    add_course(DB, 20172, 11112, C3);
    add_course(DB, 20172, 11112, C5);
    add_course(DB, 20172, 11112, C1);
    print_student_semester_courses(DB, 20172, 11112);

    print_student_all_courses(DB, 11112);

    cout << DB << endl;
    remove_student(DB, 11111);
    cout << DB << endl;
    getchar();
    getchar();
    return 0;
}

void add_student(list< tuple< int, int, float, map<int, pair< pair<int, float>*, list<course*>* > *> * > >& DB, int id) {

    // if student exists, ignore the operation
    for (auto& tup : DB) {
        if (get<0>(tup) == id) return;
    }
    tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> T { id, 0, 0.00,  new map<int, pair<pair<int, float>*, list<course*>*>*> };
    DB.push_back(T);
}

void remove_student(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int id) {
    for (auto i = DB.begin(); i != DB.end(); i++) {
        // find student
        if (get<0>(*i) == id) {
            map<int, pair<pair<int, float>*, list<course*>*>*>* M = get<3>(*i);
            // map is empty
            if (M->size() == 0) {
                delete M; // delete pointer
                DB.erase(i);
            }
            // map is not empty
            else {
                // loop semester
                auto sem = M->begin();
                while (sem != M->end()) {
                    auto P1 = sem->second;
                    auto P2 = P1->first;
                    //loop course list, delete courses
                    list<course*>* lst = P1->second;
                    list<course*> :: iterator itr;
                    itr = lst->begin();
                    while (itr != lst->end()) {
                        delete *itr;
                        auto tmp = next(itr);
                        lst->erase(itr);
                        itr = tmp;
                    }
                    delete P1->second;  //delete course list
                    delete P2;  // delete pair<int, float>*
                    delete P1;  // release pointer
                    sem = M->erase(sem);  // delete semester
                }
                M->clear();
                delete M;   // delete map
                i = DB.erase(i);  //delete student
            }
        break;
        }
    }
}

void add_course(list< tuple< int, int, float, map<int, pair< pair<int, float>*, list<course*> * >* >* > >& DB, int semester, int id, course c) {
    for (auto& i : DB){
        // find student
        if (get<0>(i) == id) {
            map<string, float> cal = { {"A+", 4.0}, {"A", 4.0},
                                       {"A-", 3.667}, {"B+", 3.333},
                                       {"B", 3.000}, {"B-", 2.667},
                                       {"C+", 2.333}, {"C", 2.0},
                                       {"C-", 1.667}, {"D+", 1.0},
                                       {"D", 1.0}, {"D-", 0.667}, {"F", 0.0}  };

            auto& M = *get<3>(i); // type: map
            // map is empty (no course / semester)
            if (M.size() == 0) {
                pair<pair<int, float>*, list<course*>*>* ptr_P1 { new pair<pair<int, float>*, list<course*>*> };
                pair<int, float>* ptr_P2 { new pair<int, float> };
                list<course*>* ptr_lst { new list<course*> };
                auto crs = new course(c);
                auto& lst = *ptr_lst; // type: list
                lst.push_front(crs);  // add course
                // calculate GPA
                float curGPA = (cal[c.grade] * c.credits) / c.credits;
                auto& P2 = *ptr_P2;
                P2.first = c.credits;
                P2.second = curGPA;
                auto& P1 = *ptr_P1;
                P1.first = ptr_P2;
                P1.second = ptr_lst;
                M[semester] = ptr_P1;
                get<1>(i) = c.credits;
                get<2>(i) = curGPA;
            }
            // map is not empty
            else {
                // loop through each semester, do nothing if course exists
                for (auto sem : M) {
                    auto& p = *sem.second;
                    auto& crslst = *p.second;

                    for (auto i = crslst.begin(); i != crslst.end(); i++) {
                        if (*(*i) == c) return; // course exists. do nothing
//                        if ((*i)->name == c.name) return; // course exists. do nothing
                    }
                }

                auto sem = M.find(semester);
                // find semester
                if (sem != M.end()) {
                    auto& L = *sem->second->second;
                    auto crs = new course(c);
                    // Add course with order
                    auto itr = L.begin();
                    bool addcrs = false;
                    while (itr != L.end()) {
                        auto itr_crs = *itr;
                        if (c.name < itr_crs->name) {
//                            L.push_front(crs);
                            L.insert(itr, crs);
                            addcrs = true;
                            break;
                        }
                        else {
                            itr ++;
                        }
                    }
                    if (addcrs == false) L.push_back(crs);   // add course at the end

                    // calculate GPA (semester)
                    float semGPA = 0;
                    int totalCR = 0;
                    float totalGPA = 0;
                    for (auto i : L) {
                        totalCR += i->credits;
                        totalGPA += i->credits * cal[i->grade];
                    }
                    semGPA = totalGPA / totalCR;
                    auto& grade = *sem->second->first;
                    grade.first += crs->credits;
                    grade.second = semGPA;
                }
                // no semester, create new semester
                else {
                    pair<pair<int, float>*, list<course*>*>* ptr_P1 { new pair<pair<int, float>*, list<course*>*> };
                    pair<int, float>* ptr_P2 { new pair<int, float> };
                    list<course*>* ptr_lst { new list<course*> };
                    auto crs = new course(c);

                    auto& lst = *ptr_lst; // type: list
                    lst.push_front(crs);
                    float curGPA = (cal[c.grade] * c.credits) / c.credits;

                    auto& P2 = *ptr_P2;
                    P2.first = c.credits;
                    P2.second = curGPA;

                    auto& P1 = *ptr_P1;
                    P1.first = ptr_P2;
                    P1.second = ptr_lst;

                    M[semester] = ptr_P1;
                }

                //calculate overall GPA
                int totalCR = 0;
                float totalGPA = 0;
                for (auto s : M) {
                    auto& L = s.second->second;
                    for (auto i : *L) {
                        totalCR += i->credits;
                        totalGPA += i->credits * cal[i->grade];
                    }
                }
                get<1>(i) = totalCR;
                get<2>(i) = totalGPA / totalCR;
            }
            break;
        }
    }
}

void drop_course(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int semester, int id, course c) {
    // find student
    for (auto& i : DB) {
        if (get<0>(i) == id) {
            auto& M = *get<3>(i);

            map<string, float> cal = { {"A+", 4.0}, {"A", 4.0},
                                       {"A-", 3.667}, {"B+", 3.333},
                                       {"B", 3.000}, {"B-", 2.667},
                                       {"C+", 2.333}, {"C", 2.0},
                                       {"C-", 1.667}, {"D+", 1.0},
                                       {"D", 1.0}, {"D-", 0.667}, {"F", 0.0}  };

            // map is empty (no course / semester), do nothing
            if (M.size() == 0) return;
            else {
                //find semester
                auto sem = M.find(semester);
                if (sem == M.end()) return;
                else {
                    auto &L = *sem->second->second;
                    auto itr = L.begin();
                    //loop through course list
                    while (itr != L.end()) {
                        if (*(*itr) == c) {
//                        if ((*itr)->name == c.name) {
                            delete *itr;
                            L.erase(itr);
                            break;
                        }
                    }
                    //re-calculate GPA (semester)
                    int totalCR = 0;
                    float totalGPA = 0;
                    for (auto i : L) {
                        totalCR += i->credits;
                        totalGPA += i->credits * cal[i->grade];
                    }
                    auto& grade = *sem->second->first;
                    grade.first = totalCR;
                    grade.second = totalGPA / totalCR;
                }
            }
            //re-calculate overall GPA
            int totalCR = 0;
            float totalGPA = 0;
            for (auto s : M) {
                auto& L = s.second->second;
                // loop through course list
                for (auto i : *L) {
                    totalCR += i->credits;
                    totalGPA += i->credits * cal[i->grade];
                }
            }
            get<1>(i) = totalCR;
            get<2>(i) = totalGPA / totalCR;
        }
    }
}

void print_student_semester_courses(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int semester, int id) {

    for (auto i : DB) {
        //find student
        if (get<0>(i) == id) {
            cout << "ID: " << id << endl;
            // find semester
            auto M = *get<3>(i);
            auto sem = M.find(semester);
            if (sem != M.end()) {
                cout << "Semester: " << semester << endl;
                cout << "GPA: " << setprecision(2) << fixed << sem->second->first->second << endl;
                cout << "Credits " << sem->second->first->first << endl;
                auto lst = *sem->second->second;
                cout << "( ";
                for (auto itr = lst.begin(); itr != lst.end(); itr++) {
                    cout << "(";
                    cout << (*itr)->name << " " << (*itr)->section << " " << (*itr)->credits << " " << (*itr)->grade;
                    cout << ") ";
                }
                cout << ")" << endl;
            }
            cout << endl;
        }
    }
}

void print_student_all_courses(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int id) {
    for (auto i : DB) {
        //find student
        if (get<0>(i) == id) {
            cout << "ID: " << id << endl;
            cout << "Overall GPA: " << setprecision(2) << fixed << get<2>(i) << endl;
            cout << "Overall Credits: " << get<1>(i) << endl;
            auto M = *get<3>(i);
            for (auto sem : M) {
                cout << "Semester: " << sem.first << endl;
                cout << "GPA: " << setprecision(2) << fixed << sem.second->first->second << endl;
                cout << "Credits " << sem.second->first->first << endl;
                auto lst = *sem.second->second;
                cout << "( ";
                for (auto itr = lst.begin(); itr != lst.end(); itr++) {
                    cout << "(";
                    cout << (*itr)->name << " " << (*itr)->section << " " << (*itr)->credits << " " << (*itr)->grade;
                    cout << ") ";
                }
                cout << ")" << endl;
            }
            cout << endl;
        }
    }
}
