#include <iostream>
#include <vector>

using namespace std;

typedef long long L;
typedef vector<L> VL;
typedef vector<int> VI;
typedef vector< VI > VVI;

void precompute(VVI const & reportees, VI const & salary, int emp, VL & cum_salary, VL & min_salary, VI & org_size) {

    cum_salary[emp] = salary[emp];
    min_salary[emp] = salary[emp];
    org_size[emp] = 1;
    
    for (int reportee : reportees[emp]) {
        precompute(reportees, salary, reportee, cum_salary, min_salary, org_size);
        cum_salary[emp] += cum_salary[reportee];
        min_salary[emp] = min(min_salary[emp], min_salary[reportee]);
        org_size[emp] += org_size[reportee];
    }
}

int main() {

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        int N, Q; cin >> N >> Q;

        VI manager(N + 1), salary(N + 1);
        VVI reportees(N + 1, VI());
        for (int i = 1; i <= N; i++) {
            cin >> manager[i] >> salary[i];
            reportees[manager[i]].push_back(i);
        }

        VL cum_salary(N + 1);
        VL min_salary(N + 1);
        VI org_size(N + 1);
        precompute(reportees, salary, 0, cum_salary, min_salary, org_size);

        VL increments(N + 1); // a log of all increments made for an employee and his/her reportees.
        for (int q = 0; q < Q; q++) {
            int c, v; cin >> c >> v;
            L total_increments_in_past = 0;
            int emp = v;
            while (emp != 0) {
                total_increments_in_past += increments[emp];
                emp = manager[emp];
            }
            if (c == 1) {
                cout << (cum_salary[v] + total_increments_in_past * org_size[v]) << "\n";
            } else {
                L incr = min(min_salary[v] + total_increments_in_past, (L) 1000);

                total_increments_in_past -= increments[v]; // now, applies to v's manager.
                increments[v] += incr;
                
                emp = manager[v];
                while (emp != 0) {
                    cum_salary[emp] += incr * org_size[v];
                    min_salary[emp] = salary[emp] + total_increments_in_past;
                    for (int reportee : reportees[emp]) {
                        min_salary[emp] = min(min_salary[emp],
                                              min_salary[reportee]
                                                    + total_increments_in_past
                                                    + increments[reportee]);
                    }
                    total_increments_in_past -= increments[emp];
                    emp = manager[v];
                }
            }
        }
    }

    return 0;
}
