#include <iostream>
#include <vector>
#include <array>
#include <fstream>
using namespace std;
#define azCodeSize 15

struct aztec
{
    array<array<bool, azCodeSize>, azCodeSize> azCode;
    int mode, x, y, orientation, numChar;
    bool centerMark[10][11] = {{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                               {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                               {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                               {0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0},
                               {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0},
                               {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                               {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0},
                               {0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0},
                               {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                               {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    enum MODE
    {
        Initial,
        Upper,
        Lower,
        Digit
    };
    enum ORIENTATION
    {
        Left,
        Bot,
        Right,
        Top
    };

    aztec()
    {
        mode = Initial;
        orientation = Left;
        azCode[0].fill(0);
        azCode[1].fill(0);
        azCode[12].fill(0);
        azCode[13].fill(0);
        azCode[14].fill(0);
        for (int i = 2; i < 12; i++)
        {
            azCode[i][0] = azCode[i][1] = azCode[i][13] = azCode[i][14] = 0;
            for (int j = 2; j < 13; j++)
                azCode[i][j] = centerMark[i - 2][j - 2];
        }
    }

    void char2Bin(char c, vector<bool> &code)
    {
        // code[0] is LSB
        int n;
        switch (mode)
        {
        case Upper:
            n = (int)c - 63;
            for (int i = 0; i < 5; i++, n /= 2)
                code.push_back(n & 1);
            break;
        case Lower:
            n = (int)c - 95;
            for (int i = 0; i < 5; i++, n /= 2)
                code.push_back(n & 1);
            break;
        case Digit:
            if (c == ',')
                n = 12;
            else if (c == '.')
                n = 13;
            else
                n = (int)c - 46;
            for (int i = 0; i < 4; i++, n /= 2)
                code.push_back(n & 1);
            break;
        default:
            break;
        }
    }
    void gotoNextGrid()
    {
        switch (orientation)
        {
        case Left:
            if (x == 0)
                x = 1;
            else
            {
                x = 0;
                if (++y == 13)
                {
                    y++;
                    orientation = Bot;
                }
            }
            break;
        case Bot:
            if (y == 14)
                y = 13;
            else
            {
                y = 14;
                if (++x == 13)
                {
                    x++;
                    orientation = Right;
                }
            }
            break;
        case Right:
            if (x == 14)
                x = 13;
            else
            {
                x = 14;
                if (--y == 1)
                {
                    y = 0;
                    orientation = Top;
                }
            }
            break;
        case Top:
            if (y == 0)
                y = 1;
            else
            {
                y = 0;
                if (--x == 1)
                {
                    x = 0;
                    orientation = Left;
                }
            }
            break;
        default:
            break;
        }
    }
    void toUpper()
    {
        vector<bool> code = {0, 1, 1, 1}; // 14
        fillIn(code);
        mode = Upper;
    }
    void toLower()
    {
        vector<bool> code = {0, 0, 1, 1, 1}; // 28
        fillIn(code);
        mode = Lower;
    }
    void toDigit()
    {
        vector<bool> code = {0, 1, 1, 1, 1}; // 30
        fillIn(code);
        mode = Digit;
    }
    void checkMode(char c)
    {
        // Detects whether it is necessary to switch modes
        switch (mode)
        {
        case Upper:
            if ((int)c >= 97 && (int)c <= 122) // ABC to abc
                toLower();
            else if (isdigit(c) || c == ',' || c == '.') // ABC to 123
                toDigit();
            break;
        case Lower:
            if ((int)c >= 65 && (int)c <= 90) // abc to ABC
            {
                toDigit();
                toUpper();
            }
            else if (isdigit(c) || c == ',' || c == '.') // abc to 123
                toDigit();
            break;
        case Digit:
            if ((int)c >= 65 && (int)c <= 90) // 123 to ABC
                toUpper();
            else if ((int)c >= 97 && (int)c <= 122) // 123 to abc
            {
                toUpper();
                toLower();
            }
            break;
        default: // Initial
            x = 1;
            y = 0;
            if ((int)c >= 65 && (int)c <= 90)
                toUpper();
            else if ((int)c >= 97 && (int)c <= 122)
                toLower();
            else if (isdigit(c) || c == ',' || c == '.')
                toDigit();
            break;
        }
    }
    void fillIn(vector<bool> &code)
    {
        while (!code.empty())
        {
            gotoNextGrid();
            azCode[y][x] = code.back();
            code.pop_back();
        }
    }
    void append(char c)
    {
        checkMode(c);

        vector<bool> code;
        char2Bin(c, code);
        fillIn(code);
    }
    void fillInMode1(int n)
    {
        x = (azCodeSize / 2) + 5;
        y = (azCodeSize / 2) - 2;
        while (n > 0)
        {
            azCode[y++][x] = n & 1;
            n /= 2;
        }
    }
    void fillInMode2(int n)
    {
        x = (azCodeSize / 2) - 3;
        y = (azCodeSize / 2) + 5;
        while (n > 0)
        {
            azCode[y][x++] = n & 1;
            n /= 2;
        }
    }
    void fillInMode3(int n)
    {
        x = (azCodeSize / 2) - 5;
        y = (azCodeSize / 2) - 3;
        while (n > 0)
        {
            azCode[y++][x] = n & 1;
            n /= 2;
        }
    }
    void fillInNumChar()
    {
        int n = numChar - 1;

        x = (azCodeSize / 2) + 5;
        y = (azCodeSize / 2) - 3;
        azCode[y][x] = n & 1;
        n /= 2;

        x -= 2;
        y -= 2;
        while (n > 0)
        {
            azCode[y][x--] = n & 1;
            n /= 2;
        }
    }
    void printAzCode()
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
                if (azCode[i][j])
                    cout << "1";
                else
                    cout << "0";
            cout << endl;
        }
        cout << endl;
    }
    void outputAzCode()
    {
        ofstream ofs("output.txt");
        for (int i = 0; i < azCodeSize; i++)
        {
            for (int j = 0; j < azCodeSize; j++)
                if (azCode[i][j])
                    ofs << 1;
                else
                    ofs << 0;
            ofs << endl;
        }
        ofs << endl;
    }
};

int main(int argc, char **argv)
{
    aztec az;
    string inf = argc == 1 ? "test2.txt" : argv[1], line;
    ifstream ifs(inf);
    if (!ifs)
    {
        cerr << "ERROR" << endl;
        return 1;
    }

    ifs >> line; // Message
    az.numChar = line.size();
    az.fillInNumChar();
    for (auto &c : line)
    {
        az.append(c);
        // az.printAzCode();
    }

    ifs >> line; // Error checking message
    for (auto &c : line)
    {
        az.append(c);
        // az.printAzCode();
    }

    ifs >> line; // Mode 1
    az.fillInMode1(stoi(line));
    ifs >> line; // Mode 2
    az.fillInMode2(stoi(line));
    ifs >> line; // Mode 3
    az.fillInMode3(stoi(line));

    az.printAzCode();
    // az.outputAzCode();

    return 0;
}