//https://codeforces.com/group/PVbQ8eK2T4/contest/377095/submission/155154021

#include <iostream>
#include <queue>
#include <unordered_set>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

struct State {//struct for grid state and previous actions made
    uint64_t data;
    std::string actions;
    char prevState;

    State(uint64_t newData, std::string str, char state) : data(newData), actions(std::move(str)), prevState(state) {}

    State(const State &oldState) : data(oldState.data), actions(oldState.actions), prevState(oldState.prevState) {}

    uint64_t getCell(uint64_t pos) {
        return ((15ull << ((15ull - pos) * 4ull)) & data) >> ((15ull - pos) * 4ull);
    }

    void setCell(uint64_t pos, uint64_t value) {
        data = (~(15ull << ((15ull - pos) * 4ull)) & data) | (value << ((15ull - pos) * 4ull));
    }

    void swapCells(uint64_t pos1, uint64_t pos2) {
        uint64_t temp1 = getCell(pos1);
        uint64_t temp2 = getCell(pos2);
        setCell(pos1, temp2);
        setCell(pos2, temp1);
    }
};

bool operator<(const State &leftState, const State &rightState) {
    if (leftState.actions.length() < rightState.actions.length()) return true;
    else return false;
}

int countState(State &state) {//heuristic + steps made
    int manhattan = 0;//manhattan distance from every cell to its destination
    for (int i = 0; i < 16; ++i) {
        int val = static_cast<int>(state.getCell(i)) - 1;
        if (val != -1) manhattan += abs(i / 4 - val / 4) + abs(i % 4 - val % 4);
    }
    int linearConflict = 0;//+2 for every pair of cells that are in a right row/column but are in wrong order pairwise
    for (int i = 0; i < 16; ++i) {
        for (int j = i + 1; j < 16; ++j) {
            int x = static_cast<int>(state.getCell(i)) - 1;
            int y = static_cast<int>(state.getCell(j)) - 1;
            if (i / 4 == j / 4 && i % 4 < j % 4 && x > y && x != -1 && y != -1 && x / 4 == y / 4 && x / 4 == i / 4) {
                linearConflict += 2;
            }
            if (i / 4 < j / 4 && i % 4 == j % 4 && x > y && x != -1 && y != -1 && x % 4 == y % 4 && x % 4 == i % 4) {
                linearConflict += 2;
            }
        }
    }
    return manhattan + linearConflict + state.actions.length();//it is important to have precise heuristic
}

bool isSolvable(const int data[]) {//check if puzzle can be solved
    int inversions = 0;//count inversions
    for (int i = 0; i < 16; ++i) {
        for (int j = i + 1; j < 16; ++j) {
            if (data[j] < data[i] && data[i] != 0 && data[j] != 0) {
                ++inversions;
            }
        }
    }
    int nullPos = -1;//finding empty cell
    for (int i = 0; i < 16; ++i) {
        if (data[i] == 0) {
            nullPos = i;
            break;
        }
    }
    if ((nullPos / 4 + inversions) % 2 == 1) return true;
    else return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    uint64_t init = 0;
    int arr[16];
    for (int i = 0; i < 16; ++i) {
        std::cin >> arr[i];
        init = (init << 4) | arr[i];
    }
    if (isSolvable(arr)) {
        //auto cmp = [](std::pair<int, State> left, std::pair<int, State> right) { return (left.first < right.first); };
        //std::priority_queue<std::pair<int, State>, std::vector<std::pair<int, State>>, decltype(cmp)> states(cmp);
        std::priority_queue<std::pair<int, State>> states;
        std::unordered_set<uint64_t> visitedStates;
        states.push({0, State(init, "", 'A')});
        while (true) {//fix later
            State currState = states.top().second;
            //std::cout << states.top().first << '\n';
            states.pop();
            if (visitedStates.find(currState.data) == visitedStates.end()) {
                visitedStates.insert(currState.data);
                bool Done = true;
                for (int i = 0; i < 15; ++i) { //looking if end
                    if (currState.getCell(i) != i + 1) {
                        Done = false;
                        break;
                    }
                }
                if (Done) { //if end
                    std::cout << currState.actions.length() << '\n' << currState.actions;
                    break;
                }
                int nullPos; //finding empty cell
                for (int i = 0; i < 16; ++i) {
                    if (currState.getCell(i) == 0) {
                        nullPos = i;
                        break;
                    }
                }//looking at adjacent cells
                if (nullPos - 4 >= 0 && currState.prevState != 'U') {
                    State newState(currState);
                    newState.actions += "D";
                    newState.swapCells(nullPos, nullPos - 4);
                    newState.prevState = 'D';
                    states.push({-countState(newState), newState});
                }
                if (nullPos + 4 < 16 && currState.prevState != 'D') {
                    State newState(currState);
                    newState.actions += "U";
                    newState.swapCells(nullPos, nullPos + 4);
                    newState.prevState = 'U';
                    states.push({-countState(newState), newState});
                }
                if ((nullPos + 1) < 16 && ((nullPos % 4) != 3) && currState.prevState != 'R') {
                    State newState(currState);
                    newState.actions += "L";
                    newState.swapCells(nullPos, nullPos + 1);
                    newState.prevState = 'L';
                    states.push({-countState(newState), newState});
                }
                if ((nullPos - 1) >= 0 && ((nullPos % 4) != 0) && currState.prevState != 'L') {
                    State newState(currState);
                    newState.actions += "R";
                    newState.swapCells(nullPos, nullPos - 1);
                    newState.prevState = 'R';
                    states.push({-countState(newState), newState});
                }
            }
        }
    } else std::cout << "-1";
}
