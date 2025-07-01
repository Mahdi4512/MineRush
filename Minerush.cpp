#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
const int max_size=20;


int main(){
int row,cols,mines;
int coin1=0;
int coin2=0;
bool playagain=true;
while(playagain){
cout << "Enter the row:";
cin >> row;
cout << "Enter the cols:";
cin >> cols;
cout << "Enter the number of mines:";
cin >> mines;
if (row <= 0 || cols <= 0 || mines <= 0 || row > max_size || cols > max_size || mines >= row * cols) {
            cout << "Invalid input!" << endl;
            return 1;
        }
int mode;
cout << "Enter the game mode 1 for single player and 2 for multy player:";
cin >> mode;
if(mode!=1 && mode!=2){
    cout << "INVALID INPUT!";
    return 1;
}
int level;
cout << "Enter the game level(1 for easy and 2 for hard):";
cin >> level;
if(level!=1 && level!=2){
    cout << "INVALID INPUT";
    return 1;
}
int field[max_size][max_size]={0}; // -1 for mines cell and 0 for empty cell
int flag[max_size][max_size]={0};
int reveal[max_size][max_size]={0};
 srand(time(0));
        int placedMines = 0;
        while (placedMines < mines) {
            int r = rand() % row;
            int c = rand() % cols;
            if (field[r][c] != -1) {
                field[r][c] = -1;
                placedMines++;
            }
        }
for (int i = 0; i < row; i++) {
            for (int j = 0; j < cols; j++) {
                if (field[i][j] == -1) continue;
                int count = 0;
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        if (i + x >= 0 && i + x < row && j + y >= 0 && j + y < cols && field[i + x][j + y] == -1)  {
                            count++;
                        }
                    }
                }
                field[i][j] = count;
            }
        }
int marke1=0; 
int marke2=0;
int playerturn=1;
int cell=(level==1) ? (row*cols)/2 : (row*cols)/4;
int re=0;
while(re<cell){
int r=rand() % row;
int c=rand() % cols;
if(reveal[r][c]==0 && field[r][c]!=-1){
    reveal[r][c]=1;
    re++;
}

}
cout << "game field:" << endl;
for(int i=0;i<row;i++){
    for(int j=0;j<cols;j++){
        cout << "* ";
    }
    cout << endl;
}
bool gameover=false;

while(!gameover){
cout << "player" << playerturn << " turn :" << endl;
cout << "player coin 1: " << coin1 << " player coin 2 :" << coin2 << endl;
int e;
cout << "Enter 1 for uncover the cell and 2 for marked the cell and 3 for hint:" << endl;
cin >> e;
if(e==1){
int a,b;
cout << "Enter the row and cols for reveal : " << endl;
cin >> a >> b;
a--; b--;
if(a<0 || a>=row || b<0 || b>=cols){
    cout << "INVALID INPUT!";
    continue;
}
if(field[a][b]==-1)
{
    cout << "player " << playerturn << " lost!!" << endl;
    gameover=true;
    break;
}
if(reveal[a][b]==1){
    cout << "this cell is already opened!" << endl;
    continue;
}
reveal[a][b]=1;
cout << "game field:" << endl;
for(int i=0;i<row;i++){
    for(int j=0;j<cols;j++){
        if(reveal[i][j]==1){
if(field[i][j]==-1){
    cout << "?";
}else {
    cout << field[i][j] << " ";
}
        }else if(flag[i][j]==1){
            cout << "F";
        }else {
            cout << "* ";
        }
    }
    cout << endl;
}
bool win=true;
for(int i=0;i<row;i++){
for(int j=0;j<cols;j++){
if(field[i][j]!=-1 && reveal[i][j]==0){
    win=false;
    break;
}


}
if(!win)
break;
}
if(win){
    cout << "congradulation to player " << playerturn << " for winning the game! " << endl;
if(playerturn==1)
coin1++;
else 
coin2++;
gameover=true;
break;    
}
if(mode==2){
if(playerturn==1){
    playerturn =2;
}else{ 
playerturn =1;
}

}

}else if(e==2){
int r,c;
cout << "Enter the row and cols for marked:" << endl;
cin >> r >> c;
r--;
c--;
if (r < 0 || r >= row || c < 0 || c >= cols) {
                    cout << "Invalid input!" << endl;
                    continue;
                }

if (reveal[r][c] == 1) {
                    cout << "This cell is already revealed." << endl;
                    continue;
                }
flag[r][c]=1;
if(field[r][c]==-1){
if(playerturn==1){
    marke1++;
}else {
    marke2++;
}
}
cout << "game filed:" << endl;
for(int i=0;i<row;i++){
    for(int j=0;j<cols;j++){
if(reveal[i][j]==1){
    if(field[i][j]==-1){
        cout << "? ";
    }else{
    cout << field[i][j] << " ";
    }
}else if(flag[i][j]==1){
    cout << "F ";
}else {
    cout << "* ";
}
    }
    cout << endl;
}

if(mode==2){
if(playerturn==1){
    playerturn=2;
}else{
    playerturn =1;
}
}
}else if(e==3){

int coins=(playerturn ==1) ? coin1 : coin2;
if(coins<1){
    cout << "not enough coin for hint ";
    continue;
}
while (true) {
                    int r = rand() % row;
                    int c = rand() % cols;
                    if (field[r][c] == -1 && flag[r][c] == 0) {
                        field[r][c] = 0; // Remove mine
                        cout << "A mine at (" << r + 1 << ", " << c + 1 << ") was removed." << endl;
                        break;
                    }
                }
if(playerturn ==1)coin1--;
else {
    coin2--;
}




}else {
    cout << "INVALID CHOICES!" << endl;
}

}
char answer;
cout << "do you want to play again(y/n) ?: ";
cin >> answer;
if(answer!='y'){
    playagain=false;
}



}


cout << "thanks for playing " << endl;



return 0;









}