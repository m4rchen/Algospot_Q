#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

char cache[1 << 25];
vector<int> blocks;

int convert(int i, int j)
{
    return 1 << (i * 5 + j);
}

void precalc()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int tmp = 0;
            tmp = convert(i, j) + convert(i + 1, j) + convert(i, j + 1) + convert(i + 1, j + 1);

            for (int k = 0; k < 2; k++)
            {
                for (int l = 0; l < 2; l++)
                {
                    tmp -= convert(i + k, j + l);
                    blocks.push_back(tmp);
                    tmp += convert(i + k, j + l);
                }
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int tmp = 0;
            tmp = convert(i, j) + convert(i, j + 1);
            blocks.push_back(tmp);
            tmp = convert(j, i) + convert(j + 1, i);
            blocks.push_back(tmp);
        }
    }
}

char game(int board)
{
    char &ret = cache[board];

    if (ret != -1)
    {
        return ret;
    }

    ret = 0;

    for (int i = 0; i < blocks.size(); i++)
    {
        if ((board & blocks[i]) == 0)
        {
            if (game(board + blocks[i]) == 0)
            {
                ret = 1;
                break;
            }
        }
    }

    return ret;
}

int main()
{
    int C;
    cin >> C;
    precalc();

    for (int i = 0; i < (1 << 25); i++)
    {
        cache[i] = -1;
    }

    while (C--)
    {
        int board = 0;

        for (int i = 0; i < 5; i++)
        {
            string tmp;
            cin >> tmp;
            for (int j = 0; j < 5; j++)
            {
                if (tmp[j] == '#')
                {
                    board += convert(i, j);
                }
            }
        }

        char ret = game(board);

        if (ret == 1)
        {
            cout << "WINNING" << endl;
        }
        else
        {
            cout << "LOSING" << endl;
        }
    }
}