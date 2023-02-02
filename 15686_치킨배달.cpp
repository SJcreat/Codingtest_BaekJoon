#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>


using namespace std;

int N;
int M;
int xy[50][50] = { 0 };
enum {road,home,shop};

vector<pair<int,int>> house;
vector<pair<int,int>> chicken;
bool selects[13];
int ans = 9999999;
void dfs(int d, int cnt) {

    if (cnt == M) {
        vector<pair<int, int>> sel_shop;
        for (int i = 0; i < chicken.size(); i++) {
            if (selects[i])sel_shop.push_back(chicken[i]);
        }

        int comp = 0;
        for (int i = 0; i < house.size(); i++) {
            int distance = 1000;
            for (int j = 0; j < sel_shop.size(); j++) {
                int dis = abs(house[i].first - sel_shop[j].first) + abs(house[i].second - sel_shop[j].second);  
                distance = min(dis,distance);
            }
            comp += distance;
        }
        ans = min(comp, ans);
        return;
    }



    for (int i = d; i < chicken.size(); i++) {
        if (selects[i])continue;
        selects[i] = true;
        dfs(i, cnt + 1);
        selects[i] = false;
    }

}
int main(int argc, char** argv)
{
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> xy[i][j];
            if (xy[i][j] == home)house.push_back({i,j});
            else if (xy[i][j] == shop)chicken.push_back({ i,j });
        }
    }
   

    dfs(0, 0);


    cout << ans;
 
   
    






    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
