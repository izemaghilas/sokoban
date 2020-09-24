/**
* creer une matrice a partir de niveaux.txt; ecrire un labyrinth dans le fichiers niveaux.txt
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

const string NIVEAUX_FILE = "fichiers/niveaux.txt";
vector<string> levels;

//creer un labyrinth a partir de fichier niveaus.txt
vector< vector<int> > FileToLabyrinth(int level_id){
    int N = 0;
    int LEVEL_SIZE = 0;
    vector< vector<int> > labyrinth;
    ifstream f_niveau(NIVEAUX_FILE.c_str());
    if(f_niveau){
        string lvl = "";
        if(levels.empty()){
            while(getline(f_niveau, lvl))
                levels.push_back(lvl);
        }
        if(level_id < levels.size()){
            lvl = levels[level_id];
            LEVEL_SIZE = lvl.size();
            N = int(sqrt(LEVEL_SIZE));
            if(N == 12){
                //generate labyrinth
                int str_index = 0;
                while(str_index < LEVEL_SIZE){
                    vector<int> row;
                    for(int j=str_index; j<N+str_index; j++){
                        stringstream str;
                        str << lvl[j];
                        int n;
                        str>>n;
                        row.push_back(n);
                    }
                    str_index+=N;
                    labyrinth.push_back(row);
                }

                f_niveau.close();
                return labyrinth;
            }
            else{
                cout<<"Failed not level file : "<< level_id<<endl;
                return vector< vector<int> >();
            }
        }
        else{
            cout<<"Failed to find specified level : "<< level_id<<endl;
            return vector< vector<int> >();
        }
    }
    else{
        cout<<"Failed to load level in file : "<< NIVEAUX_FILE <<endl;
        return vector< vector<int> >();
    }
}

//write labyrinth to 'niveaux.txt' file
void LabyrinthToFile(){
    /**
    * TODO
    */
}
