#include <iostream>
#include <algorithm>

using namespace std;

int N;
int board[50];
int cache[52][52];

int game(int left, int right)
{
    if (left > right)
    {
        return 0;
    }

    int &ret = cache[left][right];

    if (ret != -987654321)
    {
        return ret;
    }

    ret = max(ret, board[left] - game(left + 1, right));
    ret = max(ret, board[right] - game(left, right - 1));

    if (right - left >= 1)
    {
        ret = max(ret, -game(left + 2, right));
        ret = max(ret, -game(left, right - 2));
    }

    return ret;
}

int main()
{
    int C;

    cin >> C;

    while (C--)
    {
        cin >> N;

        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                cache[i][j] = -987654321;
            }
        }

        for (int i = 0; i < N; i++)
        {
            cin >> board[i];
        }

        cout << game(0, N - 1) << endl;
    }
}