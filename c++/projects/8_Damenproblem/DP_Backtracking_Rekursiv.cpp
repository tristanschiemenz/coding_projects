#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<vector<vector<int>>> PerfectMatches;

int how_many_placed(vector<vector<int>> Field){
    int HowMany = 0;
    //Ein mal duch jede Zelle um zu schaun wie viel 1 es insegesamt gibt
    for(int i = 0;i<Field.size();i++){
        for(int j = 0; j < Field[i].size();j++){
            if(Field[i][j] == 1){
                HowMany++;
            }
        }
    }
    return HowMany;
}
void print_array(vector<vector<int>> MyArray){
    //Check ob die gefunde Liste schon in anderer Anordnung gefunden wurde
    bool inside = false;
    for(int i = 0; i < PerfectMatches.size();i++){
        if(MyArray == PerfectMatches[i]){
            inside = true;
        }
    }
    //Wenn nicht dann Ausgabe und aufnehmen in Liste von gefunden 
    if(!inside){
        PerfectMatches.push_back(MyArray);
        for(int i = 0; i < MyArray.size(); i++){
            //Wählen vom Kästchen
            for(int j = 0; j < MyArray[i].size(); j++){
                cout << to_string(MyArray[i][j]) + " ";
            }
            cout << endl;
        }
        //Trennungsstrich
        for(int i = 0;i<MyArray.size();i++){
            cout<<"--";
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
        if (HowManyInLine > 1){
            return false;
        }else if(HowManyInColumn > 1){
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
            //
            if(Field[j+i][j] == 1){
                HowManyInDiagonalDowner++;
            }
        }
        if(HowManyInDiagonalUpper > 1){
            return false;
        }else if(HowManyInDiagonalDowner > 1){
            return false;
        }
    }
    //Diagonalen /(links unten nach rechts oben) richtung   
    HowManyInDiagonalUpper =0 ;
    HowManyInDiagonalDowner = 0;
    for(int i = 0;i<Field.size();i++){
        HowManyInDiagonalDowner = 0;
        HowManyInDiagonalUpper = 0;
        for(int j = 0; j<Field.size()-i;j++){
            if(Field[j][Field.size()-j-i-1] == 1){
                HowManyInDiagonalUpper++;
            }
            if(Field[Field.size()-j-1][j+i] == 1){
                HowManyInDiagonalDowner++;
            }
        }
        if(HowManyInDiagonalUpper > 1){
            return false;
        }else if(HowManyInDiagonalDowner > 1){
            return false;
        } 
    }
    return true;
}
void NDamen(int N, vector<vector<int>> Field){
    for(int row = 0; row < Field.size(); row++){//Durch Zeilen
        for(int col = 0; col < Field[row].size(); col++){//Druch Spalten
            //Plazier Dame
            if(Field[row][col] != 1){
                Field[row][col] = 1;
                if(check_field_state(Field) && how_many_placed(Field) != N){//Wenn die Dame gesetze werden kann und es aber noch nicht genug Damen sind
                    NDamen(N,Field);

                }else if(check_field_state(Field) && how_many_placed(Field) == N){//Wenn sie gesetz werden kann und es N Damen auf dem Feld sind(Lösung)
                    print_array(Field);

                }
                Field[row][col] = 0;
                    //zurücksetzung der gesetzten Dame
            }
            
        }
    }
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
    int HowBigField;
    cout << "Wie groß soll das Spielfeld sein: ";
    cin >> HowBigField;
    //Setzung der Größen
    vector<vector<int>> Field(HowBigField,vector<int> (HowBigField));

    int HowManyQueens;
    cout << "Wie viele Damen: ";
    cin >> HowManyQueens;
    //Check ob die Eingabe berrechnet werden kann.
    if (HowManyQueens <= HowBigField){
        
        NDamen(HowManyQueens,Field);

        cout << "\nEs gibt " + to_string(PerfectMatches.size()) + " mögliche Lösungen.";

    }else{
        cout << "Die Damen müssen weniger oder gleich viele sein wie die größe des Spielfelds.";
    }
    

    return 0;
}