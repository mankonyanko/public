#ifndef __MAZE__
#define __MAZE__
#include<cstdlib>
#include<ctime>
#include<cstdio>
//const int N_maze=2000;

#define MAZE_NOUTH 8
#define MAZE_EAST 4
#define MAZE_SOUTH 2
#define MAZE_WEST 1



struct pointer{
	short x;
	short y;
};



class stack_for_maze
{
private:
	//	extern pointer Stack_for_maze_edit[N_maze*N_maze];
	pointer* Stack_for_maze_edit;
	int i;
	int N_maze;

public:
	stack_for_maze(int num);
	~stack_for_maze();
	void push(int x, int y);
	void push(char x, char y);
	void push(pointer n);
	pointer top();
	char top_x();
	char top_y();
	void pop();
	bool empty();
	int size();
};

stack_for_maze::stack_for_maze(int num)
{
	i = 0;
	N_maze = num;
	Stack_for_maze_edit = new pointer[num*num];
}

stack_for_maze::~stack_for_maze()
{
	delete[] Stack_for_maze_edit;
}

void stack_for_maze::push(int x, int y)
{
	pointer n;
	n.x = x;
	n.y = y;
	Stack_for_maze_edit[i++] = n;
}

void stack_for_maze::push(char x, char y)
{
	pointer n;
	n.x = x;
	n.y = y;
	Stack_for_maze_edit[i++] = n;
}

void stack_for_maze::push(pointer n)
{
	Stack_for_maze_edit[i++] = n;
}

pointer stack_for_maze::top()
{
	return Stack_for_maze_edit[i - 1];
}

char stack_for_maze::top_x()
{
	return Stack_for_maze_edit[i - 1].x;
}

char stack_for_maze::top_y()
{
	return Stack_for_maze_edit[i - 1].y;
}

void stack_for_maze::pop()
{
	i--;
}

bool stack_for_maze::empty()
{
	if (i != 0)
		return false;
	return true;
}

int stack_for_maze::size()
{
	return i;
}


class maze
{
private:
	char** Map_for_view;
	pointer k;
	int N_maze;
	stack_for_maze sta;


public:
	char** map_original;
	char** maze_map;
	maze(int num);
	~maze();
	void mazecreate();
	void mazeviewer2_console();
	void mazeviewer2_file(char str[]);
	void mazechange();   // ÇÑÄ­À» 2*2 ³Ö¾î¼­ maze_map¿¡ ÀúÀåµÊ
	void mazeviewer3_console();
	void mazeviewer3_file(char str[]);
	void mazesave(char str[]);
};

maze::maze(int num)
:sta(num)
{
	N_maze = num;
	map_original = new char*[num];
	for (int i = 0; i<num; i++){
		map_original[i] = new char[num];
	}
	for (int i = 0; i<num; i++){
		for (int j = 0; j<num; j++){
			map_original[i][j] = 0;
		}
	}
}

maze::~maze(){
	for (int i = 0; i<N_maze; i++){
		delete[] map_original[i];
	}
	delete[] map_original;
}

void maze::mazecreate()
{//1111 ºÏµ¿³²¼­
	srand(time(NULL));
	k.x = rand() % N_maze;
	k.y = rand() % N_maze;
	sta.push(k.x, k.y);
	while (!sta.empty()){
		//maze::mazeviewer_console();
		//_sleep(300);
		while ((k.x == 0 || map_original[k.x - 1][k.y] != 0) && (k.y == 0 || map_original[k.x][k.y - 1] != 0) && (k.x == N_maze - 1 || map_original[k.x + 1][k.y] != 0) && (k.y == N_maze - 1 || map_original[k.x][k.y + 1] != 0)){
			if (sta.empty()){
				break;
			}
			k = sta.top();
			sta.pop();
		}
		int i = rand() % 4;   // ºÏ 0 µ¿ 1 ³² 2 ¼­ 3
		if (i == 0){
			if (k.y>0 && map_original[k.x][k.y - 1] == 0){
				map_original[k.x][k.y] += MAZE_NOUTH;
				map_original[k.x][k.y - 1] += MAZE_SOUTH;
				k.y--;
				sta.push(k.x, k.y);
			}
		}
		else if (i == 1){
			if (k.x<N_maze - 1 && map_original[k.x + 1][k.y] == 0){
				map_original[k.x][k.y] += MAZE_EAST;
				map_original[k.x + 1][k.y] += MAZE_WEST;
				k.x++;
				sta.push(k.x, k.y);
			}
		}
		else if (i == 2){
			if (k.y<N_maze - 1 && map_original[k.x][k.y + 1] == 0){
				map_original[k.x][k.y] += MAZE_SOUTH;
				map_original[k.x][k.y + 1] += MAZE_NOUTH;
				k.y++;
				sta.push(k.x, k.y);
			}
		}
		else if (i == 3){
			if (k.x>0 && map_original[k.x - 1][k.y] == 0){
				map_original[k.x][k.y] += MAZE_WEST;
				map_original[k.x - 1][k.y] += MAZE_EAST;
				k.x--;
				sta.push(k.x, k.y);
			}
		}
	}
}

void maze::mazeviewer2_console(){
	int temp;
	Map_for_view = new char*[N_maze * 2 + 1];
	for (int i = 0; i <= N_maze * 2; i++){
		Map_for_view[i] = new char[N_maze * 2 + 1];
		for (int j = 0; j <= N_maze * 2; j++){
			Map_for_view[i][j] = '*';
		}
	}
	for (int i = 0; i<N_maze; i++){
		for (int j = 0; j<N_maze; j++){
			temp = map_original[i][j];
			if (map_original[i][j] != 0){
				Map_for_view[i * 2 + 1][j * 2 + 1] = ' ';
			}
			if (map_original[i][j] >= MAZE_NOUTH){
				Map_for_view[i * 2 + 1][j * 2] = ' ';
				map_original[i][j] -= MAZE_NOUTH;
			}
			if (map_original[i][j] >= MAZE_EAST){
				map_original[i][j] -= MAZE_EAST;
			}
			if (map_original[i][j] >= MAZE_SOUTH){
				map_original[i][j] -= MAZE_SOUTH;
			}
			if (map_original[i][j] >= MAZE_WEST){
				Map_for_view[i * 2][j * 2 + 1] = ' ';
				map_original[i][j] -= MAZE_WEST;
			}
			map_original[i][j] = temp;
		}
	}
	system("cls");
	for (int i = 0; i <= N_maze * 2; i++){
		for (int j = 0; j <= N_maze * 2; j++){
			printf("%c ", Map_for_view[i][j]);
		}
		printf("\n");
		delete[] Map_for_view[i];
	}
	delete[] Map_for_view;
}
void maze::mazechange(){
	int temp;
	maze_map = new char*[N_maze * 2 + 1];
	for (int i = 0; i <= N_maze * 2; i++){
		maze_map[i] = new char[N_maze * 2 + 1];
		for (int j = 0; j <= N_maze * 2; j++){
			maze_map[i][j] = 1;
		}
	}
	for (int i = 0; i < N_maze; i++){
		for (int j = 0; j < N_maze; j++){
			temp = map_original[i][j];
			if (map_original[i][j] != 0){
				maze_map[i * 2 + 1][j * 2 + 1] = 0;
			}
			if (map_original[i][j] >= MAZE_NOUTH){
				maze_map[i * 2 + 1][j * 2] = 0;
				map_original[i][j] -= MAZE_NOUTH;
			}
			if (map_original[i][j] >= MAZE_EAST){
				map_original[i][j] -= MAZE_EAST;
			}
			if (map_original[i][j] >= MAZE_SOUTH){
				map_original[i][j] -= MAZE_SOUTH;
			}
			if (map_original[i][j] >= MAZE_WEST){
				maze_map[i * 2][j * 2 + 1] = 0;
				map_original[i][j] -= MAZE_WEST;
			}
			map_original[i][j] = temp;
		}
	}
}

void maze::mazeviewer2_file(char str[]){
	int temp;
	Map_for_view = new char*[N_maze * 2 + 1];
	FILE* fp = fopen(str, "w");
	for (int i = 0; i <= N_maze * 2; i++){
		Map_for_view[i] = new char[N_maze * 2 + 1];
		for (int j = 0; j <= N_maze * 2; j++){
			Map_for_view[i][j] = '*';
		}
	}
	for (int i = 0; i<N_maze; i++){
		for (int j = 0; j<N_maze; j++){
			temp = map_original[i][j];
			if (map_original[i][j] != 0){
				Map_for_view[i * 2 + 1][j * 2 + 1] = ' ';
			}
			if (map_original[i][j] >= MAZE_NOUTH){
				Map_for_view[i * 2 + 1][j * 2] = ' ';
				map_original[i][j] -= MAZE_NOUTH;
			}
			if (map_original[i][j] >= MAZE_EAST){
				map_original[i][j] -= MAZE_EAST;
			}
			if (map_original[i][j] >= MAZE_SOUTH){
				map_original[i][j] -= MAZE_SOUTH;
			}
			if (map_original[i][j] >= MAZE_WEST){
				Map_for_view[i * 2][j * 2 + 1] = ' ';
				map_original[i][j] -= MAZE_WEST;
			}
			map_original[i][j] = temp;
		}
	}
	system("cls");
	for (int i = 0; i <= N_maze * 2; i++){
		for (int j = 0; j <= N_maze * 2; j++){
			fprintf(fp, "%c ", Map_for_view[i][j]);
		}
		fprintf(fp, "\n");
		delete[] Map_for_view[i];
	}
	fclose(fp);
	delete[] Map_for_view;
}




void maze::mazeviewer3_console(){
	int temp;
	Map_for_view = new char*[N_maze * 3];
	for (int i = 0; i<N_maze * 3; i++){
		Map_for_view[i] = new char[N_maze * 3];
		for (int j = 0; j<N_maze * 3; j++){
			Map_for_view[i][j] = '*';
		}
	}
	for (int i = 0; i<N_maze; i++){
		for (int j = 0; j<N_maze; j++){
			temp = map_original[i][j];
			if (map_original[i][j] != 0){
				Map_for_view[i * 3 + 1][j * 3 + 1] = ' ';
			}
			if (map_original[i][j] >= MAZE_NOUTH){
				Map_for_view[i * 3 + 1][j * 3] = ' ';
				map_original[i][j] -= MAZE_NOUTH;
			}
			if (map_original[i][j] >= MAZE_EAST){
				Map_for_view[i * 3 + 2][j * 3 + 1] = ' ';
				map_original[i][j] -= MAZE_EAST;
			}
			if (map_original[i][j] >= MAZE_SOUTH){
				Map_for_view[i * 3 + 1][j * 3 + 2] = ' ';
				map_original[i][j] -= MAZE_SOUTH;
			}
			if (map_original[i][j] >= MAZE_WEST){
				Map_for_view[i * 3][j * 3 + 1] = ' ';
				map_original[i][j] -= MAZE_WEST;
			}
			map_original[i][j] = temp;
		}
	}
	system("cls");
	for (int i = 0; i<N_maze * 3; i++){
		for (int j = 0; j<N_maze * 3; j++){
			printf("%c ", Map_for_view[i][j]);
		}
		printf("\n");
		delete[] Map_for_view[i];
	}
	delete[] Map_for_view;
}


void maze::mazeviewer3_file(char str[]){
	int temp;
	Map_for_view = new char*[N_maze * 3];
	FILE* fp = fopen(str, "w");
	for (int i = 0; i<N_maze * 3; i++){
		Map_for_view[i] = new char[N_maze * 3];
		for (int j = 0; j<N_maze * 3; j++){
			Map_for_view[i][j] = '*';
		}
	}
	for (int i = 0; i<N_maze; i++){
		for (int j = 0; j<N_maze; j++){
			temp = map_original[i][j];
			if (map_original[i][j] != 0){
				Map_for_view[i * 3 + 1][j * 3 + 1] = ' ';
			}
			if (map_original[i][j] >= MAZE_NOUTH){
				Map_for_view[i * 3 + 1][j * 3] = ' ';
				map_original[i][j] -= MAZE_NOUTH;
			}
			if (map_original[i][j] >= MAZE_EAST){
				Map_for_view[i * 3 + 2][j * 3 + 1] = ' ';
				map_original[i][j] -= MAZE_EAST;
			}
			if (map_original[i][j] >= MAZE_SOUTH){
				Map_for_view[i * 3 + 1][j * 3 + 2] = ' ';
				map_original[i][j] -= MAZE_SOUTH;
			}
			if (map_original[i][j] >= MAZE_WEST){
				Map_for_view[i * 3][j * 3 + 1] = ' ';
				map_original[i][j] -= MAZE_WEST;
			}
			map_original[i][j] = temp;
		}
	}
	system("cls");
	for (int i = 0; i<N_maze * 3; i++){
		for (int j = 0; j<N_maze * 3; j++){
			fprintf(fp, "%c ", Map_for_view[i][j]);
		}
		fprintf(fp, "\n");
		delete[] Map_for_view[i];
	}
	delete[] Map_for_view;
	fclose(fp);

}


void maze::mazesave(char str[]){
	FILE* fp = fopen(str, "r+");
	for (int i = 0; i<N_maze; i++)
	{
		for (int j = 0; j<N_maze; j++)
		{
			fprintf(fp, "%d ", map_original[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}


#endif
