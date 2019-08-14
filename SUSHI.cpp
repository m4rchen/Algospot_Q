#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int N, M;
int price[20], pref[20];
int cache[201];

int dp()
{
    cache[0] = 0;
   
    for (int money = 1; money <= M; money++)
    {
        int cand = 0;
        for (int menu = 0; menu < N; menu++)
        {
            if (money >= price[menu])
            {
                cand = max(cand, pref[menu] + cache[(money - price[menu])%201]);
            }
        }

        cache[money%201] = cand;
    }

    return cache[M%201];
}

int main()
{
    int C;
    cin >> C;

    while (C--)
    {
        memset(cache, 0, sizeof(cache));

        cin >> N >> M;

        M /= 100;

        for (int i = 0; i < N; i++)
        {
            cin >> price[i] >> pref[i];
            price[i] /= 100;
        }

        cout << dp() << endl;
    }
}