#include <iostream>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
using namespace std;

class node;
vector <node> SK;
int d = 0;

class node{
	public:
		int x;
		int y;
		int FNB;
		
		node(int lnb){
			FNB = lnb;
			if(lnb!=(-1)){
				FNB--;
				x = SK[FNB].x;
				y = SK[FNB].y;
			} 
		}
		void update(int** map,int D){
			if(FNB == (-1)){
				switch(D){
					case 2: // up
						y--;
						break;
					case 1: // left
						x--;
						break;
					case 3: // right
						x++;
						break;
					case 4: // down
						y++;
						break;
				}
			}
			else{
				x = SK[FNB].x;
				y = SK[FNB].y;
			}
			if(x<0)
				x = 24;
			else if(y<0)
				y = 24;
			else if(x>24)
				x = 0;
			else if(y>24) 
				y = 0;
			if(map[y][x] == 1){
				cout << "game over\n";
				exit(0);
			}
			map[y][x] = 1;
		}
};

class food{
	public:
		int x,y;
		food(int **map){
			srand((unsigned)time(NULL));
			x = rand()%25;
			y = rand()%25;
			while(map[y][x] != 0){
				x = rand()%25;
				y = rand()%25;
			}
			map[y][x] = 2;
		}
		
		void to_food(int **map){
			srand((unsigned)time(NULL));
			x = rand()%25;
			y = rand()%25;
			while(map[y][x] != 0){
				x = rand()%25;
				y = rand()%25;
			}
			map[y][x] = 2;
		}
		
		void update(int**map){
			map[y][x] = 2;
		}
		
		bool check(){
			if(SK[0].x == x && SK[0].y == y){
				return true;
			}
			else{
				return false; 
			}
		}
};

void clean_map(int** map){
	for(int i=0;i<25;i++)
		for(int j=0;j<25;j++)
			map[i][j] = 0;
}

void update_map(int** map,food tmp){
	clean_map(map);
    for(int i=SK.size()-1;i>=0;i--){
		SK[i].update(map,d);
	}
	tmp.update(map);
}

int main(){
	int** map = new int* [25];
	for(int i=0;i<25;i++)
		map[i] = new int [25];
	for(int i=0;i<25;i++)
		for(int j=0;j<25;j++)
			map[i][j] = 0;

	node temp(-1);
	temp.x = 12;
	temp.y = 12;
	SK.push_back(temp); 
	map[12][12] = 1;

	char C;
	char *ch;
	
	food FD(map);

	while(1){
		
        if (GetAsyncKeyState(87) == -32767 && d!=4)
        	d = 2;
        if (GetAsyncKeyState(65) == -32767 && d!=3)
        	d = 1;
        if (GetAsyncKeyState(83) == -32767 && d!=2)
        	d = 4;
        if (GetAsyncKeyState(68) == -32767 && d!=1)
        	d = 3;
        /*	
        if (GetAsyncKeyState(48) == -32767){
        	temp.FNB = SK.size()-1;
        	SK.push_back(temp);
			update_map(map,FD);
        }
        */
        if(FD.check()){
        	temp.FNB = SK.size()-1;
        	SK.push_back(temp);
			update_map(map,FD);
			FD.to_food(map);
        }
        
		update_map(map,FD);
		
		string str;
		ch = "╔";
		str.push_back(ch[0]);
		str.push_back(ch[1]);
		for(int i=0;i<12;i++){
			ch = "═";
			str.push_back(ch[0]);
			str.push_back(ch[1]);
		}
		ch = "╗";
		str.push_back(ch[0]);
		str.push_back(ch[1]);
		
		str.push_back('\n');
		
		for(int i=0;i<25;i++){
			
			str.push_back('*');
			
			for(int j=0;j<25;j++){
				
				switch(map[i][j]){
					case 0:
						str.push_back(' ');
						break;
					case 1:
						str.push_back('S');
						break;
					case 2:
						str.push_back('F');
						break;	
				}
			}
			
			str.push_back('*');
			
			str.push_back('\n');
		}
		
		ch = "╚";
		str.push_back(ch[0]);
		str.push_back(ch[1]);
		
		for(int i=0;i<12;i++){
			ch = "═";
			str.push_back(ch[0]);
			str.push_back(ch[1]);
		}
		
		ch = "╝";
		str.push_back(ch[0]);
		str.push_back(ch[1]);
		
		str.push_back('\n');
		
		cout << str << SK.size() << endl;
		
		/*
		for(int i = 0;i<25;i++){
			for(int j = 0;j<25;j++){
				cout << map[i][j];
			}
			cout << endl;
		}
		*/
		
		usleep(50000);
		system("cls");	
	} 
} 
