#include <iostream>
#include <stack>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

struct State {
    int x, y;

    bool operator<(const State& that) const {
        if (x != that.x) return x < that.x;
        return y < that.y;
    }
};

int capacity_x = 4, capacity_y = 3, target = 2;

void printOperation(int operation) {
    switch (operation) {
        case 1: cout << "Fill the first jug"; break;
        case 2: cout << "Fill the second jug"; break;
        case 3: cout << "Empty the first jug"; break;
        case 4: cout << "Empty the second jug"; break;
        case 5: cout << "Pour from second jug into first jug"; break;
        case 6: cout << "Pour from first jug into second jug"; break;
    }
}

void printTree() {
    queue<pair<State, int>> q; // Using a queue of pairs (state, operation)
    map<State, bool> visited;

    cout << "Full Tree:" << endl;

    q.push({{0, 0}, 0}); // Start with no operation
    visited[{0, 0}] = true;

    int currentLevel = 0;

    while (!q.empty()) {
        State current = q.front().first;
        int operation = q.front().second;
        q.pop();

        if (currentLevel != current.x + current.y) {
            cout << endl; // Move to the next line for the next level
            currentLevel = current.x + current.y;
        }

        cout << "(" << current.x << ", " << current.y << ")";
        if (current.x == target || current.y == target) {
            cout << " [TARGET]";
        }

        if (operation != 0) {
            cout << " [";
            printOperation(operation);
            cout << "]";
        }

        cout << " ";

        vector<pair<State, int>> children = {
            {{capacity_x, current.y}, 1},
            {{current.x, capacity_y}, 2},
            {{0, current.y}, 3},
            {{current.x, 0}, 4},
            {{min(current.x + current.y, capacity_x), max(0, current.x + current.y - capacity_x)}, 5},
            {{max(0, current.x + current.y - capacity_y), min(current.x + current.y, capacity_y)}, 6}
        };

        for (const auto& child : children) {
            if (!visited[child.first]) {
                q.push(child);
                visited[child.first] = true;
            }
        }
    }
    cout << endl;
}

void dfs(State start, stack<pair<State, int>>& path) {
    stack<State> s;
    State goal = {-1, -1};

    map<State, pair<State, int>> parentOf;

    s.push(start);
    parentOf[start] = make_pair(start, 0);

    while (!s.empty()) {
        State top = s.top();
        s.pop();

        if (top.x == target || top.y == target) {
            goal = top;
            break;
        }

        if (top.x < capacity_x) {
            State child = {capacity_x, top.y};
            if (parentOf.find(child) == parentOf.end()) {
                s.push(child);
                parentOf[child] = make_pair(top, 1);
            }
        }

        if (top.y < capacity_y) {
            State child = {top.x, capacity_y};
            if (parentOf.find(child) == parentOf.end()) {
                s.push(child);
                parentOf[child] = make_pair(top, 2);
            }
        }

        if (top.x > 0) {
            State child = {0, top.y};
            if (parentOf.find(child) == parentOf.end()) {
                s.push(child);
                parentOf[child] = make_pair(top, 3);
            }
        }

        if (top.y > 0) {
            State child = {top.x, 0};
            if (parentOf.find(child) == parentOf.end()) {
                s.push(child);
                parentOf[child] = make_pair(top, 4);
            }
        }

        if (top.y > 0) {
            State child = {min(top.x + top.y, capacity_x), max(0, top.x + top.y - capacity_x)};
            if (parentOf.find(child) == parentOf.end()) {
                s.push(child);
                parentOf[child] = make_pair(top, 5);
            }
        }

        if (top.x > 0) {
            State child = {max(0, top.x + top.y - capacity_y), min(top.x + top.y, capacity_y)};
            if (parentOf.find(child) == parentOf.end()) {
                s.push(child);
                parentOf[child] = make_pair(top, 6);
            }
        }
    }

    if (goal.x == -1 || goal.y == -1)
        return;

    path.push(make_pair(goal, 0));

    while (parentOf[path.top().first].second != 0)
        path.push(parentOf[path.top().first]);
}

int main() {
    stack<pair<State, int>> path;

    printTree();
    cout << endl;

    dfs({0, 0}, path);

    if (path.empty()) {
        cout << "\nTarget cannot be reached." << endl;
    } else {
        cout << "\nNumber of moves to reach the target: " << path.size() - 1 << endl;
        cout << "One path to the target is as follows:" << endl;

        while (!path.empty()) {
            State top = path.top().first;
            int rule = path.top().second;
            path.pop();

            switch (rule) {
                case 0:
                    cout << "State: (" << top.x << ", " << top.y << ")" << endl << "#" << endl;
                    break;
                case 1:
                    cout << "State: (" << top.x << ", " << top.y << ")" << endl;
                    printOperation(rule);
                    cout << endl;
                    break;
               case 2:
                    cout << "State: (" << top.x << ", " << top.y << ")" << endl;
                    printOperation(rule);
                    cout << endl;
                    break;
                case 3:
                    cout << "State: (" << top.x << ", " << top.y << ")" << endl;
                    printOperation(rule);
                    cout << endl;
                    break;
                case 4:
                    cout << "State: (" << top.x << ", " << top.y << ")" << endl;
                    printOperation(rule);
                    cout << endl;
                    break;
                case 5:
                    cout << "State: (" << top.x << ", " << top.y << ")" << endl;
                    printOperation(rule);
                    cout << endl;
                    break;
                case 6:
                    cout << "State: (" << top.x << ", " << top.y << ")" << endl;
                    printOperation(rule);
                    cout << endl;
                    break;
            }
        }
    }

    return 0;
}