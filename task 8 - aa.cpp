#include <iostream>
#include <vector>
#include <set>

using namespace std;

// basic puzzle settings used everywhere
int n;     
int cap;    

// checks if every stack is either empty or full of one color
bool checkWin (vector<vector<int>> &b) {
    for (int i = 0; i < n; i++ ) {
        if (b[i].empty())  continue;
        if (b[i].size() != cap) return false;

        int color = b[i][0];
        for (int ball : b[i]) {
            if (ball != color)  return false;
        }
    }
    return true;
}

// dfs solver with backtracking
bool solve(vector<vector<int>> b , vector<pair<int,int>> &path, set<vector<vector<int>>> &visited) {
    if (checkWin(b))  return true;
    if (visited.count(b)) return false;
    visited.insert(b);

    // try every valid move from i to j
    for (int i = 0; i < n; i++) {
        if (b[i].empty()) continue;

        for (int j = 0; j < n; j++ ) {
            if (i == j) continue;

            // move is allowed only if j has room and matches color or is empty
            if (b[j].size() < cap && (b[j].empty() || b[j].back() == b[i].back())) {

                int ball = b[i].back(); 

                b[i].pop_back();
                b[j].push_back( ball );
                path.push_back( {i + 1, j + 1} );

                if (solve(b , path , visited)) return true;

                // undo failed move
                path.pop_back();
                b[j].pop_back();
                b[i].push_back(ball);
            }
        }
    }
    return false;
}

int main() {
    // read puzzle size
    cout << "enter total number of stacks: ";
    cin >> n;
    cout << "enter max balls per stack: ";
    cin >> cap;

    vector<vector<int>> board (n);

    // read stack inputs
    cout << "enter balls from bottom to top & use 0 for empty slots" << endl;
    cout << "use spaces to separate numbers like (1 2 0 0)" << endl;

    for (int i = 0; i < n; i++ ) {
        cout << "stack " << i + 1 << ": ";
        for (int k = 0; k < cap; k++) {
            int c; 
            cin >> c;
            if (c != 0)  board[i].push_back(c);
        }
    }

    // solve and show results
    vector<pair<int,int>> path;
    set<vector<vector<int>>> visited;

    if (solve(board , path , visited)) {
        cout << "solved in " << path.size() << " moves\n";
        for (int i = 0; i < path.size(); i++ ) {
            cout << "Move from stack " << path[i].first << " to " << path[i].second << endl;
        }
    } 
    else {
        cout << "no solution\n";
    }

    return 0;
}
