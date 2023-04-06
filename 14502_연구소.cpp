#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

int N;
int M;
int xy[8][8] = {0};
int copy_xy[8][8] = {0};
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
enum {safe,wall,virus};
vector<pair<int, int>> v;
vector<pair<int, int>> vir;
bool selects[64] = {false};
int ans = 0;
void spread() {
    
    queue<pair<int, int>> qu;
    for (int i = 0; i < vir.size(); i++) {
        qu.push({ vir[i].first,vir[i].second });
    }
    while (!qu.empty()) {
        int x=qu.front().first ;
        int y = qu.front().second;
        qu.pop();


        for (int i = 0; i < 4; i++) {
            if (x + dx[i] < N && x + dx[i] >= 0 && y + dy[i] < M && y + dy[i] >= 0 && xy[x + dx[i]][y + dy[i]] == 0) {
                xy[x + dx[i]][y + dy[i]] = 2;
                qu.push({ x + dx[i],y + dy[i] });
            }
        }
    }
    int comp = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (xy[i][j] == 0) {
                comp++;
            }
        }
    }
    ans = max(ans, comp);


}


void dfs(int d, int cnt) {
    if (cnt == 3) {
        memcpy(xy, copy_xy, sizeof(copy_xy));
        for (int i = 0; i < v.size(); i++) {
            if (selects[i]) {
                xy[v[i].first][v[i].second] = 1;
            }
        }

        spread();
        return;
    }

    for (int i = d; i < v.size(); i++) {
        if (selects[i])continue;
        selects[i] = true;
            dfs(i, cnt + 1);
        selects[i] = false;
    }

}


int main(int argc, char** argv)
{
    cin >> N;
    cin >> M;    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> xy[i][j];
            if (xy[i][j] == 0) {
                v.push_back({ i,j });
            }
            else if (xy[i][j] == 2) {
                vir.push_back({ i,j });
            }
        }
    }
    memcpy(copy_xy, xy, sizeof(copy_xy));

    dfs(0, 0);

    cout << ans;
    
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
