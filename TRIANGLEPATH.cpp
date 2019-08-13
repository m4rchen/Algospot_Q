#include <iostream>
#include <algorithm>

using namespace std;

int N;
int S[100][100];
int cache[2][100];

void dp()
{
    for (int i = 0; i < N; i++)
    {
        cache[(N - 1) % 2][i] = S[N - 1][i];
    }

    for (int i = N - 2; i >= 0; i--){
        for (int j = 0; j <= i; j++){
            cache[i%2][j] = max(cache[(i+1)%2][j], cache[(i+1)%2][j+1]) + S[i][j];
        }
    }
    
    cout << cache[0][0] << endl;
}

int main()
{
    int C;
    cin >> C;

    while (C--)
    {
        cin >> N;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                cin >> S[i][j];
            }
        }

        dp();
    }
}