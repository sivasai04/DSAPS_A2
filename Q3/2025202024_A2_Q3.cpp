#include <iostream>

using namespace std;

using ll = long long;

int n;
ll F[85];
ll pref[85]; 
ll alpha, beeta, gamma_cost;



ll dp1[85][85];
ll dp2[85][85][85]; 
ll dp3[85][85][85][2]; 


ll sum_freq(int i, int j) {
    if (i > j) {
        return 0;
    }
    return pref[j] - pref[i - 1];
}

///////////------------- part one solving function.
ll solve_part1(int i, int j) {
    if (i > j) return 0; 
    if (dp1[i][j] != -1) return dp1[i][j];

    ll min_cost = -1;

    for (int k = i; k <= j; ++k) {
        ll current_cost = solve_part1(i, k - 1) + solve_part1(k + 1, j) + sum_freq(i, j);
        if (min_cost == -1 || current_cost < min_cost) {
            min_cost = current_cost;
        }
    }
    return dp1[i][j] = min_cost;
}

///////////------------- part two solving function.
ll solve_part2(int i, int j, int parent_pos) {
    if (i > j){
        return 0;
    } 
    if (dp2[i][j][parent_pos] != -1){
        return dp2[i][j][parent_pos];
    } 

    ll min_cost = -1;

    for (int k = i; k <= j; ++k) {
        ll move_cost = abs(k - parent_pos) * sum_freq(i, j);
        ll sub_cost = solve_part2(i, k - 1, k) + solve_part2(k + 1, j, k);
        ll current_cost = move_cost + sub_cost;
        if (min_cost == -1 || current_cost < min_cost) {
            min_cost = current_cost;
        }
    }
    return dp2[i][j][parent_pos] = min_cost;
}

///////////------------- part three solving function.
ll solve_part3(int i, int j, int parent_pos, int dir) {
    if (i > j){
        return 0;
    } 
    if (dp3[i][j][parent_pos][dir] != -1){
        return dp3[i][j][parent_pos][dir];
    } 
    

    ll min_cost = -1;

    for (int k = i; k <= j; ++k) {
        ll reversal_penalty = 0;
        if ((dir == 0 && k < parent_pos) || (dir == 1 && k > parent_pos)) {
            reversal_penalty = gamma_cost;
        }
        
        ll cost_at_this_level = (alpha * abs(k - parent_pos) + beeta + reversal_penalty) * sum_freq(i, j);
        int next_dir = (k > parent_pos) ? 0 : 1;
        ll sub_cost = solve_part3(i, k - 1, k, next_dir) + solve_part3(k + 1, j, k, next_dir);
        ll current_cost = cost_at_this_level + sub_cost;
        if (min_cost == -1 || current_cost < min_cost) {
            min_cost = current_cost;
        }
    }
    return dp3[i][j][parent_pos][dir] = min_cost;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    cin >> n;

    pref[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> F[i];
        pref[i] = pref[i - 1] + F[i];
    }

    for (int i = 0; i < 85; ++i) {
        for (int j = 0; j < 85; ++j) {
            dp1[i][j] = -1;
            for (int k = 0; k < 85; ++k) {
                dp2[i][j][k] = -1;
                dp3[i][j][k][0] = -1;
                dp3[i][j][k][1] = -1;
            }
        }
    }

    if (q == 1) {
        cout << solve_part1(1, n) << endl;
    } 
    else if (q == 2) {
        cout << solve_part2(1, n, 0) << endl;
    } 
    else if (q == 3) {
        cin >> alpha >> beeta >> gamma_cost;
        ll fixed_return_cost = 0;
        for (int i = 1; i <= n; ++i) {
            fixed_return_cost += F[i] * (alpha * i);
        }
        ll search_cost = solve_part3(1, n, 0, 0);
        cout << search_cost + fixed_return_cost << endl;
    }
    return 0;
}


