#include<iostream>
#include<string>
#include<queue>
#include<deque>
#include<algorithm>
#include<cstring>

using namespace std;

enum {normal,apple};
enum {Right,Down,Left,Up};
int N;
int K;
int L;
int xy[100][100];
int xy_snake[100][100] = {-1,};
int snake_dir;

int x;
int y;
int times = 0;
bool chk=true;
queue<pair<int, int> > turn;
deque<pair<int, int > > snake;
void move(int d,int t) {
    times++;
    switch (d) {
    case Right:
        y++;
        break;
    case Down:
        x++;
        break;
    case Left:
        y--;
        break;
    case Up:
        x--;
        break;
    }
    
    if (x < 0 || x >= N || y < 0 || y >= N) {
        chk= false;
        return;
    }

    if (xy_snake[x][y] == 1) {
        chk= false;
        return;
    }
    else{     
      
        if (xy[x][y] == apple) {
            xy_snake[x][y] = 1;
            xy[x][y] = 0;
            snake.push_back({ x,y });
        }
        else{
            xy_snake[x][y] = 1; 
            snake.push_back({ x,y });
            xy_snake[snake.front().first][snake.front().second] = 0;
            snake.pop_front();

        }

    }

    if (t != times) {
        move(d, t);      
    }
    else {
        chk=true;
        return;
    }
    
    
}

void run() {
    int t = turn.front().first;
    int d = turn.front().second; 
    turn.pop();
    
   
    move(snake_dir, t);
    if (chk) {       
        snake_dir += d;
        if (snake_dir < 0)snake_dir = Up;
        if (snake_dir > Up)snake_dir = Right;
        
        if(!turn.empty())
        run();
        else {
            move(snake_dir, -1);
        }
    }


}
int main(int argc, char** argv)
{

    cin >> N;
    cin >> K;

    for (int i = 0; i < K; i++) {
        int x_;
        int y_;
        cin >> x_;
        cin >> y_;
        x_--;
        y_--;
        xy[x_][y_] = apple;
    }
    cin >> L;
    for (int i = 0; i < L; i++) {
        int t;
        string dir;
        cin >> t;
        cin >> dir;
        if(dir=="L"){
        turn.push({t,-1});
        }
        else if (dir == "D") {
            turn.push({ t,1 });
        }
    }
    x = 0;
    y = 0;
 
    memset(xy_snake, -1, sizeof(xy_snake));
    xy_snake[0][0] = 1;
    snake.push_back({ 0,0 });
    snake_dir = Right;
    
        run();
        cout << times;

    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
