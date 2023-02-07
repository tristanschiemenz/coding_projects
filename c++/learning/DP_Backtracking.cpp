#include <iostream>
#include <vector>
#include <string>
using namespace std;

void print_array(vector<vector<int>> MyArray){
    //Wählen von Zeile
    for(int i = 0; i < MyArray.size(); i++){
        //Wählen vom Kästchen
        for(int j = 0; j < MyArray[i].size(); j++){
            cout << to_string(MyArray[i][j]) + " ";
        }
        cout << endl;
    }
}
bool check_field_state(vector<vector<int>> Field){
    
    //Zeilen und Spalten überprüfung
    int HowManyInLine;
    int HowManyInColumn;
    //Reihenauswahl
    for(int i = 0; i < Field.size(); i++){
        
        //Zurücksetzen der Line und Spalte
        HowManyInLine = 0;
        HowManyInColumn = 0;

        for(int j = 0; j < Field[i].size(); j++){
            //Wenn Reihe i Dame hat
            if(Field[i][j] == 1){
                HowManyInLine++;
            }
            //Wenn Spalte j Dame hat
            if(Field[j][i] == 1){
                HowManyInColumn++;
            }
        }
        //mehr als eine Dame pro Zeile
        if (HowManyInLine > 1 || HowManyInColumn > 1){
            return false;
        }
    }
    
    //Diagonalen \ richtung
    int HowManyInDiagonalUpper;
    int HowManyInDiagonalDowner;
    for(int i = 0;i<Field.size();i++){
        HowManyInDiagonalUpper = 0;
        HowManyInDiagonalDowner = 0;
        for(int j = 0;j<Field.size()-i;j++){
            //Recht obere Hälfte des Feldes check
            if(Field[j][j+i] == 1){
                HowManyInDiagonalUpper++;
            }
            if(Field[j+i][j] == 1){
                HowManyInDiagonalDowner++;
            }
        }
        if(HowManyInDiagonalUpper > 1 || HowManyInDiagonalDowner > 1){
            return false;
        }
    }
    //Diagonalen / richtung
    HowManyInDiagonalUpper =0 ;
    HowManyInDiagonalDowner = 0;
    for(int i = 0;i<Field.size();i++){
        HowManyInDiagonalUpper = 0;
        HowManyInDiagonalDowner = 0;
        for(int j = Field.size();j>i;j--){
            //Recht obere Hälfte des Feldes check
            if(Field[j][j+i] == 1){
                HowManyInDiagonalUpper++;
            }
            if(Field[j+i][j] == 1){
                HowManyInDiagonalDowner++;
            }
        }
        if(HowManyInDiagonalUpper > 1 || HowManyInDiagonalDowner > 1){
            return false;
        }
    }
    return true;
}


//0 - keine Dame
//1 - Dame
/*
Field = 
{
{0,0,0,0},
{0,0,0,0},
{0,0,0,0},
{0,0,0,0}
}
*/
int main(){
    int howBigField;
    cout << "Wie groß soll das Spielfeld sein: ";
    cin >> howBigField;
    //Setzung der Größen
    vector<vector<int>> Field(howBigField,vector<int> (howBigField));

    Field[0][4] = 1;
    Field[1][3] = 1;
    print_array(Field);

    if(check_field_state(Field)){
        cout << "Hello";
    }

    return 0;
}