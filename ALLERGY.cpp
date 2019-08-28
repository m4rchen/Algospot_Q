#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int friendCnt, foodCnt;
int best;
vector<int> canFood[50]; // idx 사림이 먹을 수 있는 음식
vector<int> canPeople[50]; // idx 음식을 먹을수 있는 사람

void search(vector<int> edible, int chosen){

    if (best <= chosen){
        return ;
    }

    int target = -1;

    for (int i = 0; i < edible.size(); i++){
        if (edible[i] == 0){
            target = i;
            break;
        }
    }

    if (target == -1){
        best = chosen;
        return ;
    }


    for (int i = 0; i < canFood[target].size(); i++){
        int choice = canFood[target][i];

        for (int j = 0; j < canPeople[choice].size(); j++){
            edible[canPeople[choice][j]]++;
        }

        search(edible, chosen + 1);

        for (int j = 0; j < canPeople[choice].size(); j++){
            edible[canPeople[choice][j]]--;
        }
    }
}

void clear(){
    for (int i = 0; i < friendCnt; i++){
        canFood[i].clear();
    }
    for (int j = 0; j < foodCnt; j++){
        canPeople[j].clear();
    }
}

int main(){
    int T;
    cin >> T;

    while (T--){
        cin >> friendCnt >> foodCnt;
        
        map<string, int> index;
        best = foodCnt;

        for (int i = 0; i < friendCnt; i++){
            string name;
            cin >> name;
            
            index[name] = i; 
        }

        for (int i = 0; i < foodCnt; i++){
            int cnt;
            cin >> cnt;

            for (int j = 0; j < cnt; j++){
                string name;
                cin >> name;
                canPeople[i].push_back(index[name]);
                canFood[index[name]].push_back(i);
            }
        }

        vector<int> edible(friendCnt, 0);

        search(edible, 0);

        cout << best << endl;;

        clear();
    }
}