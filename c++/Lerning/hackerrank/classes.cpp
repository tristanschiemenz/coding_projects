#include <iostream>
#include <sstream>
using namespace std;

/*
Enter code for class Student here.
Read statement for specification.
*/
class Student{
    private:
        int st_age;
        string st_first;
        string st_last;
        int st_standard;
    public:
        void set_age(int age){
            st_age = age;
        }
        int get_age(){
            return st_age;
        }
        
        void set_standard(int stand){
            st_standard = stand;
        }
        int get_standard(){
            return st_standard;
        }
        
        void set_first_name(string first_name){
            st_first = first_name;
        }
        string get_first_name(){
            return st_first;
        }
        
        void set_last_name(string last_name){
            st_last = last_name;
        }
        string get_last_name(){
            return st_last;
        }
        
        string to_string(){
            return std::to_string(st_age) + "," + st_first + "," + st_last + "," + std::to_string(st_standard);
        }
};

int main() {
    int age, standard;
    string first_name, last_name;
    
    cin >> age >> first_name >> last_name >> standard;
    
    Student st;
    st.set_age(age);
    st.set_standard(standard);
    st.set_first_name(first_name);
    st.set_last_name(last_name);
    
    cout << st.get_age() << "\n";
    cout << st.get_last_name() << ", " << st.get_first_name() << "\n";
    cout << st.get_standard() << "\n";
    cout << "\n";
    cout << st.to_string();
    
    return 0;
}
