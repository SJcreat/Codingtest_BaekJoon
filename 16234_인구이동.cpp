#include<iostream>
#include<cstring>
#include<queue>
#include<cmath>
using namespace std;

int N;
int L;
int R;
int xy[50][50];
int xy_copy[50][50];
int chk_xy[50][50];
int ans = 0;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

void dfs() {
    memset(chk_xy, 0, sizeof(chk_xy));
    memcpy(xy_copy, xy, sizeof(xy_copy));
    queue<pair<int, int>> qu;
    bool chk = false;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            vector<pair<int, int>> v;
             
            if (chk_xy[i][j] == 0) {
                qu.push({ i,j });
                v.push_back({ i,j });          
                
                while (!qu.empty()) {
                    int x = qu.front().first;
                    int y = qu.front().second;
                    chk_xy[x][y] = 1;
                    qu.pop();
                    for (int i = 0; i < 4; i++) {
                        if (chk_xy[x + dx[i]][y + dy[i]] == 0 && x + dx[i] >= 0 && x + dx[i] < N && y + dy[i] >= 0 && y + dy[i] < N) {
                            int dis = abs(xy_copy[x + dx[i]][y + dy[i]] - xy_copy[x][y]);
                            if(dis>=L&&dis<=R){
                                chk_xy[x + dx[i]][y + dy[i]] = 1;
                            qu.push({ x + dx[i],y + dy[i] });
                            v.push_back({ x + dx[i],y + dy[i] });
                            chk = true;
                            }
                        }
                    }
                }
                int avr=0;
                for (int k = 0; k < v.size(); k++) {
                    avr += xy_copy[v[k].first][v[k].second];
                }
                avr = avr / v.size();
                for (int k = 0; k < v.size(); k++) {
                    xy[v[k].first][v[k].second] = avr;
                }


            }
        }
    }
    if (chk) {
        ans++;
        dfs();
    }



}

int main(int argc, char** argv)
{
    cin >> N >> L >> R;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> xy[i][j];
        }
    }
    dfs();
    cout << ans;



    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
