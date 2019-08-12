#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string board[3];
int cache[19683];

bool isFinish(char turn)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != turn)
            {
                break;
            }

            if (j == 2)
            {
                return true;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[j][i] != turn)
            {
                break;
            }

            if (j == 2)
            {
                return true;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (board[i][i] != turn)
        {
            break;
        }

        if (i == 2)
        {
            return true;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (board[i][2 - i] != turn)
        {
            break;
        }

        if (i == 2)
        {
            return true;
        }
    }

    return false;
}

int convert()
{
    int result = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            result *= 3;

            if (board[i][j] == 'x')
            {
                result++;
            }
            else if (board[i][j] == 'o')
            {
                result += 2;
            }
        }
    }

    return result;
}

int game(char turn)
{

    int &ret = cache[convert()];

    if (ret != -2)
    {
        return ret;
    }

    char opturn = 'o' + 'x' - turn;

    if (isFinish(opturn))
    {
        return ret = -1;
    }

    int Val = 2;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '.')
            {
                board[i][j] = turn;
                Val = min(Val, game(opturn));
                board[i][j] = '.';
            }
        }
    }

    if (Val == 2 || Val == 0)
    {
        return ret = 0;
    }

    return ret = -Val;
}

int main()
{
    int C;

    cin >> C;

    for (int i = 0; i < 19683; i++)
    {
        cache[i] = -2;
    }

    while (C--)
    {
        int turnCnt = 0;

        for (int i = 0; i < 3; i++)
        {
            string tmp;

            cin >> tmp;

            board[i] = tmp;

            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] != '.')
                {
                    turnCnt++;
                }
            }
        }

        char marker;
        char opmarker;

        if (turnCnt % 2 == 1)
        {
            turnCnt = 1;
            marker = 'o';
            opmarker = 'x';
        }
        else if (turnCnt % 2 == 0)
        {
            turnCnt = 0;
            marker = 'x';
            opmarker = 'o';
        }

        int result = game(marker);

        if (result == 0)
        {
            cout << "TIE" << endl;
        }
        else if (result == -1)
        {
            cout << opmarker << endl;
        }
        else if (result == 1)
        {
            cout << marker << endl;
        }
    }
}