#include <iostream>

using namespace std;
/*
 * Create classes Rectangle and RectangleArea
 */
class Rectangle{
    public:
        void display(){
            cout << to_string(width) + " " + to_string(height) + "\n";
        }
        int width;
        int height;

};
class RectangleArea: public Rectangle{
    public:
        void read_input(){
            cin >> width;
            cin >> height;
        }
        void display(){
            cout << to_string(width*height);
        }
};

int main()
{
    /*
     * Declare a RectangleArea object
     */
    RectangleArea r_area;
    
    /*
     * Read the width and height
     */
    r_area.read_input();
    
    /*
     * Print the width and height
     */
    r_area.Rectangle::display();
    
    /*
     * Print the area
     */
    r_area.display();
    
    return 0;
}