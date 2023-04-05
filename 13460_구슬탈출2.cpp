#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

int N;
int M;
int xy[10][10] = {0};

enum {emptys,wall,goal,red,blue};
enum {down,up,rights,lefts};
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
bool R_goal = false;
bool B_goal = false;
int ans=-1;
typedef struct {
    int R_x;
    int R_y;
    int B_x;
    int B_y;
    int cnt;
    vector<pair<pair<int, int>, pair<int, int>>> chk;
}qu;
qu info;
queue<qu> run;
int main(int argc, char** argv)
{
    cin >> N;
    cin >> M;
    char tr;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> tr;
            if (tr == '.')xy[i][j] = emptys;
            else if (tr == '#')xy[i][j] = wall;
            else if (tr == 'O')xy[i][j] = goal;
            else if (tr == 'R') {
                info.R_x = i;
                info.R_y = j;

            }
            else if (tr == 'B') {
                info.B_x = i;
                info.B_y = j;

            }
        }
    }
    info.cnt = 0;
    info.chk.push_back({{ info.R_x,info.R_y }, { info.B_x,info.B_y }});
    run.push(info);
    while (!run.empty()) {
        int R_x = run.front().R_x;
        int R_y = run.front().R_y;
        int B_x = run.front().B_x;
        int B_y = run.front().B_y;
        int cnt = run.front().cnt;
        vector<pair<pair<int, int>, pair<int, int>>> chk(run.front().chk);
       


        pair<int, int> ori_R;
        pair<int, int> ori_B;
        ori_R = { R_x,R_y };
        ori_B = { B_x,B_y };
        run.pop();
       // cout << R_x << " " << R_y << "//" << B_x << " " << B_y << " " << cnt << "\n";
     
        for (int i = 0; i < 4; i++) {
            bool R_first = false;
            R_x = ori_R.first;
            R_y = ori_R.second;
            B_x = ori_B.first;
            B_y = ori_B.second;
           
            switch (i) {
            case down:
                if (R_x > B_x) {
                    R_first = true;
                }  
                break;
            case up:
                if (R_x < B_x) {
                    R_first = true;
                }
                break;
            case rights:
                if (R_y > B_y) {
                    R_first = true;
                }
                break;
            case lefts:
                if (R_y < B_y) {
                    R_first = true;
                }
                break;
            }

            if(R_first){
            while (1) {
                if (R_x + dx[i] >= N || R_x + dx[i] <0|| R_y + dy[i] >= M || R_y + dy[i] < 0 || xy[R_x + dx[i]][R_y + dy[i]] == wall || (R_x+dx[i]==B_x&&R_y+dy[i] ==B_y)) {
                    break;
                }
                else if (xy[R_x + dx[i]][R_y+dy[i]] == goal) {
                    R_goal = true;
                    R_x = N;
                    R_y = M;
                    break;
                }
                R_x = R_x + dx[i];
                R_y = R_y + dy[i];
            }

            while (1) {
                if (B_x + dx[i] >= N || B_x + dx[i] < 0 || B_y + dy[i] >= M || B_y + dy[i] < 0 || xy[B_x + dx[i]][B_y + dy[i]] == wall || (B_x + dx[i] == R_x && B_y + dy[i] == R_y)) {
                    break;
                }
                else if (xy[B_x + dx[i]][B_y + dy[i]] == goal) {
                    B_goal = true;
                    break;
                }
                B_x = B_x + dx[i];
                B_y = B_y + dy[i];
                }
            }
            else {
                while (1) {
                    if (B_x + dx[i] >= N || B_x + dx[i] < 0 || B_y + dy[i] >= M || B_y + dy[i] < 0 || xy[B_x + dx[i]][B_y + dy[i]] == wall || (B_x + dx[i] == R_x && B_y + dy[i] == R_y)) {
                        break;
                    }
                    else if (xy[B_x + dx[i]][B_y + dy[i]] == goal) {
                        B_goal = true;
                        break;
                    }
                    B_x = B_x + dx[i];
                    B_y = B_y + dy[i];
                }
                while (1) {
                    if (R_x + dx[i] >= N || R_x + dx[i] < 0 || R_y + dy[i] >= M || R_y + dy[i] < 0 || xy[R_x + dx[i]][R_y + dy[i]] == wall || (R_x + dx[i] == B_x && R_y + dy[i] == B_y)) {
                        break;
                    }
                    else if (xy[R_x + dx[i]][R_y + dy[i]] == goal) {
                        R_goal = true;
                        break;
                    }
                    R_x = R_x + dx[i];
                    R_y = R_y + dy[i];
                }
            }
            if (R_goal && !B_goal) {
                ans = cnt + 1;
                break;
            }

            if (cnt < 9 && !R_goal && !B_goal) {
                qu s;
                s.B_x = B_x;
                s.R_x = R_x;
                s.B_y = B_y;
                s.R_y = R_y;
                s.cnt = cnt + 1;
               
                run.push(s);

            }
            if (B_goal) {
                R_goal = false;
                B_goal = false;
            }
        }
        if (R_goal){
            break;
        }
        

    }


    std::cout << ans;
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
