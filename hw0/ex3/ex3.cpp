#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
void printMaze(vector<vector<bool>> &maze) // for debug
{
    for (auto &row : maze)
    {
        for (const auto &g : row)
            cout << g;
        cout << endl;
    }
    cout << endl;
}

inline int abs(int n) { return n > 0 ? n : -n; }
struct grid
{
    int row, col;
    grid(int _row, int _col) : row(_row), col(_col) {}
};

struct parser
{
    vector<int> point;
    vector<vector<bool>> maze;

    void loadNextMaze(ifstream &ifs)
    {
        point.clear();
        maze.clear();

        string s;
        getline(ifs, s);
        getline(ifs, s);

        while (s[0] != '[')
        {
            vector<bool> tmp;
            for (const auto &c : s)
                if (isdigit(c))
                    tmp.push_back((int)c - 48);
            maze.push_back(tmp);
            getline(ifs, s);
        }
        for (auto &c : s)
            if (!isdigit(c))
                c = ' ';
        istringstream iss(s);
        string tmp;
        while (iss >> tmp)
            point.push_back(stoi(tmp));
    }
};

struct escapeMaze
{
    vector<grid> path, intersection;
    parser *ps;

    escapeMaze(parser *_ps) : ps(_ps) {}
    bool addAdjGrid(grid &g)
    {
        bool flag = false;
        if (!ps->maze[g.row - 1][g.col])
        {
            grid adj(g.row - 1, g.col);
            intersection.push_back(adj);
            flag = true;
        }
        if (!ps->maze[g.row + 1][g.col])
        {
            grid adj(g.row + 1, g.col);
            intersection.push_back(adj);
            flag = true;
        }
        if (!ps->maze[g.row][g.col - 1])
        {
            grid adj(g.row, g.col - 1);
            intersection.push_back(adj);
            flag = true;
        }
        if (!ps->maze[g.row][g.col + 1])
        {
            grid adj(g.row, g.col + 1);
            intersection.push_back(adj);
            flag = true;
        }
        return flag;
    }
    void turnBack()
    {
        if (intersection.empty()) // no possible path to escape the maze
        {
            while (!path.empty())
                path.pop_back();
            return;
        }

        grid *gp, *gi; // path grid, intersection grid
        do
        {
            gp = &path.back();
            gi = &intersection.back();
            path.pop_back();
        } while (abs(gp->row - gi->row) > 1 || abs(gi->col - gp->col) > 1);
        path.push_back(*gi);
        intersection.pop_back();
        ps->maze[gi->row][gi->col] = 1;
        // printMaze(ps->maze); // for debug
    }
    void outputPath(ofstream &ofs, grid &start)
    {
        ofs << "." << endl
            << "(" << start.row + 1 << ", " << start.col + 1 << ")" << endl
            << "[";
        ofs << "(" << start.row + 1 << ", " << start.col + 1 << ")";
        for (int i = 1; i < path.size(); i++)
            ofs << ", (" << path[i].row + 1 << ", " << path[i].col + 1 << ")";
        ofs << "]" << endl
            << endl;
    }
    void findPath(ofstream &ofs, int i = 0)
    {
        path.clear();
        intersection.clear();

        int ROW = ps->maze.size() - 1, COL = ps->maze[0].size() - 1;
        int length = ps->point.size(), row = ps->point[i++] - 1, col = ps->point[i++] - 1;
        while (ps->maze[row][col] && i != length)
        {
            row = ps->point[i++] - 1;
            col = ps->point[i++] - 1;
        }

        grid start(row, col);
        path.push_back(start);
        ps->maze[start.row][start.col] = 1;
        while (!path.empty() && col != COL && row != ROW)
        {
            if (addAdjGrid(path.back()))
            {
                path.push_back(intersection.back());
                intersection.pop_back();
                col = path.back().col;
                row = path.back().row;
                ps->maze[row][col] = 1;
                // printMaze(ps->maze); // for debug
            }
            else
                turnBack();
        }

        if (!path.empty() || i == ps->point.size())
            outputPath(ofs, start);
        else
            findPath(ofs, i);
    }
};

int main(int argc, char **argv)
{
    string inf = argc == 1 ? "ex3.in" : argv[1];
    string outf = argc == 1 ? "output.txt" : argv[2];
    string s;
    ifstream ifs(inf);
    ofstream ofs(outf);
    parser ps;
    escapeMaze escape(&ps);
    while (ifs >> s)
    {
        ps.loadNextMaze(ifs);
        escape.findPath(ofs);
    }

    return 0;
}
