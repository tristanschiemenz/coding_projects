#include<bits/stdc++.h>

using namespace std;
//Implement the class Box  
//l,b,h are integers representing the dimensions of the box

// The class should have the following functions : 

// Constructors: 
// Box();
// Box(int,int,int);
// Box(Box);


// int getLength(); // Return box's length
// int getBreadth (); // Return box's breadth
// int getHeight ();  //Return box's height
// long long CalculateVolume(); // Return the volume of the box

//Overload operator < as specified
//bool operator<(Box& b)

//Overload operator << as specified
//ostream& operator<<(ostream& out, Box& B)
class Box{
    public:
    //init cunsotructer
    Box(){
        l = 0;
        b = 0;
        h = 0;
    }
    Box(int gl, int gb, int gh){
        l = gl;
        b = gb;
        h = gh;
    }
    Box(Box &gbox){
        l = gbox.getLength();
        b = gbox.getBreadth();
        h = gbox.getHeight();
    }
    //functions
    int getLength(){
        return l;
    }
    int getBreadth(){
        return b;
    }
    int getHeight(){
        return h;
    }
    
    long long CalculateVolume(){
        return (long long) l*b*h;
    }
    
    bool operator<(Box &b2){
        if(l < b2.getLength()){
            return true;
        }else if(b < b2.getBreadth() && l == b2.getLength()){
            return true;
        }else if(h < b2.getHeight() && l == b2.getLength() && b == b2.getBreadth()){
            return true;
        }else {
            return false;
        }
    }
    
    private:
    int l;
    int b;
    int h;
};
std::ostream& operator<<(ostream& out,Box &myBox){
        out << to_string(myBox.getLength()) + " " + to_string(myBox.getBreadth()) + " " + to_string(myBox.getHeight());
        return out;
}

void check2()
{
	int n;
	cin>>n;
	Box temp;
	for(int i=0;i<n;i++)
	{
		int type;
		cin>>type;
		if(type ==1)
		{
			cout<<temp<<endl;
		}
		if(type == 2)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			temp=NewBox;
			cout<<temp<<endl;
		}
		if(type==3)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			if(NewBox<temp)
			{
				cout<<"Lesser\n";
			}
			else
			{
				cout<<"Greater\n";
			}
		}
		if(type==4)
		{
			cout<<temp.CalculateVolume()<<endl;
		}
		if(type==5)
		{
			Box NewBox(temp);
			cout<<NewBox<<endl;
		}

	}
}

int main()
{
	check2();
}