#include <bits/stdc++.h>
using namespace std;

class Node
{
    int grid_size;
    vector<vector<int>> grid;
    int g, h;
    Node *parent;
    pair<int, int> blank_position;
    string func;

public:
    Node(int grid_size, vector<vector<int>> grid, Node *parent, string func)
    {
        this->grid_size = grid_size;
        this->grid = grid;
        this->parent = parent;
        if (parent == NULL)
        {
            this->g = 0;
        }
        else
        {
            this->g = parent->get_g() + 1;
        }
        this->set_blank_position();
        this->func = func;
    }

    void set_h()
    {
        if (func == "Hamming Distance")
        {
            h = hamming_distance();
        }
        else if (func == "Manhattan Distance")
        {
            h = manhattan_distance();
        }
        else if (func == "Euclidean Distance")
        {
            h = euclidean_distance();
        }
        else
        {
            h = linear_conflict();
        }
    }

    int get_g()
    {
        return this->g;
    }

    vector<vector<int>> get_grid()
    {
        return grid;
    }

    Node *get_parent()
    {
        return parent;
    }

    int get_h()
    {
        return h;
    }

    void set_blank_position()
    {
        bool valid_input = false;
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                if (grid[i][j] == 0)
                {
                    blank_position.first = i;
                    blank_position.second = j;
                    valid_input = true;
                }
            }
        }
        if (!valid_input)
            cout << "Input not valid, no blank position inserted." << endl;
    }

    bool is_goal_node()
    {
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                if (i == grid_size - 1 && j == grid_size - 1)
                {
                    if (grid[i][j] != 0)
                        return false;
                }
                else
                {
                    if (grid[i][j] != grid_size * i + j + 1)
                        return false;
                }
            }
        }
        return true;
    }

    Node *move_right()
    {
        if (blank_position.second == grid_size - 1)
        {
            return NULL;
        }
        else
        {
            vector<vector<int>> child_grid = grid;
            int temp = child_grid[blank_position.first][blank_position.second + 1];
            child_grid[blank_position.first][blank_position.second + 1] = 0;
            child_grid[blank_position.first][blank_position.second] = temp;

            Node *child = new Node(grid_size, child_grid, this, func);
            child->set_h();
            return child;
        }
    }

    Node *move_left()
    {
        if (blank_position.second == 0)
        {
            return NULL;
        }
        else
        {
            vector<vector<int>> child_grid = grid;
            int temp = child_grid[blank_position.first][blank_position.second - 1];
            child_grid[blank_position.first][blank_position.second - 1] = 0;
            child_grid[blank_position.first][blank_position.second] = temp;

            Node *child = new Node(grid_size, child_grid, this, func);
            child->set_h();
            return child;
        }
    }

    Node *move_up()
    {
        if (blank_position.first == 0)
        {
            return NULL;
        }
        else
        {
            vector<vector<int>> child_grid = grid;
            int temp = child_grid[blank_position.first - 1][blank_position.second];
            child_grid[blank_position.first - 1][blank_position.second] = 0;
            child_grid[blank_position.first][blank_position.second] = temp;

            Node *child = new Node(grid_size, child_grid, this, func);
            child->set_h();
            return child;
        }
    }

    Node *move_down()
    {
        if (blank_position.first == grid_size - 1)
        {
            return NULL;
        }
        else
        {
            vector<vector<int>> child_grid = grid;
            int temp = child_grid[blank_position.first + 1][blank_position.second];
            child_grid[blank_position.first + 1][blank_position.second] = 0;
            child_grid[blank_position.first][blank_position.second] = temp;

            Node *child = new Node(grid_size, child_grid, this, func);
            child->set_h();
            return child;
        }
    }

    vector<Node *> get_children()
    {
        vector<Node *> children;
        Node *right_child = move_right();
        Node *left_child = move_left();
        Node *up_child = move_up();
        Node *down_child = move_down();
        if (right_child != NULL)
        {
            children.push_back(right_child);
        }
        if (left_child != NULL)
        {
            children.push_back(left_child);
        }
        if (up_child != NULL)
        {
            children.push_back(up_child);
        }
        if (down_child != NULL)
        {
            children.push_back(down_child);
        }
        return children;
    }

    int hamming_distance()
    {
        int distance = 0;
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                if (grid[i][j] != 0 && grid[i][j] != i * grid_size + j + 1)
                {
                    distance++;
                }
            }
        }
        return distance-1;
    }
    int manhattan_distance()
    {
        vector<vector<int>> goal(grid_size, vector<int>(grid_size));
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                goal[i][j] = i * grid_size + j + 1;
            }
        }

        int distance = 0;
        vector<pair<int, int>> goal_position(grid_size * grid_size + 1);
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                int value = goal[i][j];
                goal_position[value] = make_pair(i, j);
            }
        }

        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                int value = grid[i][j];
                if (value != 0)
                {
                    pair<int, int> temp = goal_position[value];
                    distance += abs(i - temp.first) + abs(j - temp.second);
                }
            }
        }
        return distance;
    }

    int euclidean_distance()
    {
        vector<vector<int>> goal(grid_size, vector<int>(grid_size));
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                goal[i][j] = i * grid_size + j + 1;
            }
        }

        int distance = 0;
        vector<pair<int, int>> goal_position(grid_size * grid_size + 1);
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                int value = goal[i][j];
                goal_position[value] = make_pair(i, j);
            }
        }

        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                int value = grid[i][j];
                if (value != 0)
                {
                    pair<int, int> temp = goal_position[value];
                    distance += sqrt((i - temp.first) * (i - temp.first) + (j - temp.second) * (j - temp.second));
                }
            }
        }
        return distance;
    }

    int linear_conflict()
    {
        int n = grid.size();
        int conflict = 0;

        for (int row = 0; row < n; ++row)
        {
            for (int i = 0; i < n; ++i)
            {
                int tile1 = grid[row][i];
                if (tile1 == 0)
                    continue;
                int goalRow1 = (tile1 - 1) / n;
                if (goalRow1 != row)
                    continue;

                for (int j = i + 1; j < n; ++j)
                {
                    int tile2 = grid[row][j];
                    if (tile2 == 0)
                        continue;
                    int goalRow2 = (tile2 - 1) / n;
                    if (goalRow2 != row)
                        continue;

                    if (tile1 > tile2)
                    {
                        conflict++;
                    }
                }
            }
        }

        for (int col = 0; col < n; ++col)
        {
            for (int i = 0; i < n; ++i)
            {
                int tile1 = grid[i][col];
                if (tile1 == 0)
                    continue;
                int goalCol1 = (tile1 - 1) % n;
                if (goalCol1 != col)
                    continue;

                for (int j = i + 1; j < n; ++j)
                {
                    int tile2 = grid[j][col];
                    if (tile2 == 0)
                        continue;
                    int goalCol2 = (tile2 - 1) % n;
                    if (goalCol2 != col)
                        continue;

                    if (tile1 > tile2)
                    {
                        conflict++;
                    }
                }
            }
        }

        return manhattan_distance() + 2 * conflict;
    }

    int get_priority()
    {
        return g + h;
    }

    bool equals(vector<vector<int>> new_grid)
    {
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                if (grid[i][j] != new_grid[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    void print()
    {
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int count_inversions(vector<vector<int>> grid)
{
    vector<int> arr;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] != 0)
                arr.push_back(grid[i][j]);
        }
    }

    int inversions = 0;
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                inversions++;
            }
        }
    }
    return inversions;
}

int count_row_from_bottom(vector<vector<int>> grid)
{
    int row_from_bottom;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == 0)
            {
                row_from_bottom = grid.size() - i;
                break;
            }
        }
    }
    return row_from_bottom;
}

struct NodeComparator
{
    bool operator()(Node *a, Node *b) const
    {
        return a->get_grid() < b->get_grid();
    }
};

struct CompareNode
{
    bool operator()(Node *a, Node *b)
    {
        return a->get_priority() > b->get_priority();
    }
};

void solve_n_puzzle(int grid_size, vector<vector<int>> grid, string func)
{
    int expanded = 0;
    int explored = 1;
    int inversions = count_inversions(grid);
    if ((grid_size % 2 == 1) && (inversions % 2 == 1))
    {
        cout << "Unsolvable puzzle" << endl;
        return;
    }
    int row_from_bottom = count_row_from_bottom(grid);
    if (grid_size % 2 == 0)
    {
        if ((row_from_bottom % 2 == 0 && inversions % 2 == 0) || (row_from_bottom % 2 == 1 && inversions % 2 == 1))
        {
            cout << "Unsolvable puzzle" << endl;
            return;
        }
    }

    set<Node *, NodeComparator> close_list;
    priority_queue<Node *, vector<Node *>, CompareNode> open_list;
    Node *root_node = new Node(grid_size, grid, NULL, func);
    root_node->set_h();
    open_list.push(root_node);
    while (!open_list.empty())
    {
        Node *new_node = open_list.top();
        open_list.pop();
        if (new_node->is_goal_node())
        {
            cout << "Minimum number of moves = " << new_node->get_g() << endl;
            Node *curr = new_node;
            vector<Node *> path;
            while (curr != NULL)
            {
                path.push_back(curr);
                curr = curr->get_parent();
            }
            reverse(path.begin(), path.end());
            for (int i = 0; i < path.size(); i++)
            {
                path[i]->print();
                cout << endl;
            }
            expanded++;
            break;
        }
        else
        {
            if (close_list.find(new_node) != close_list.end())
            {
                continue;
            }
            else
            {
                expanded++;
                close_list.insert(new_node);
                vector<Node *> children = new_node->get_children();
                for (int i = 0; i < children.size(); i++)
                {
                    if (close_list.find(children[i]) == close_list.end())
                    {
                        explored++;
                        open_list.push(children[i]);
                    }
                }
            }
        }
    }
    cout << "Nodes explored: " << explored << endl;
    cout << "Nodes expanded: " << expanded << endl;
}

int main()
{
    int k;
    cin >> k;
    vector<vector<int>> grid(k, vector<int>(k, 0));
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            cin >> grid[i][j];
        }
    }
    string heuristic = "Linear Conflict";
    solve_n_puzzle(k, grid, heuristic);
}
