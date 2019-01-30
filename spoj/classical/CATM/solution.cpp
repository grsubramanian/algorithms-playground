#include <iostream>

using namespace std;

bool can_escape(int mr, int mc, int c1r, int c1c, int c2r, int c2c) {

    // If the mouse is at the same position as either cat, then mouse
    // can't escape.
    if ((mr == c1r && mc == c1c) || (mr == c2r && mc == c2c)) {
        return false;
    }

    // If mouse is on the diagonal of a square where the two cats are
    // at the corresponding diagonal endpoints, then the mouse can't escape.
    int bcr = c1r - c2r;
    int bcc = c1c - c2c;

    int bcmr = c1r - mr;
    int bcmc = c1c - mc;

    if (bcr != 0                                        // else we don't have a non-trivial enclosure.
            && abs(bcr) == abs(bcc)                     // else we don't have a square enclosure (but a non-square rectangle enclosure).
            && bcr * bcmc == bcc * bcmr                 // else the mouse is not on the diagonal.
            && (bcmc / abs(bcmc)) == (bcc / abs(bcc))   // else the mouse is not inside the square.
        ) {
        return false;
    }
    return true;
}

int main() {

    int n, m, k; cin >> n >> m >> k;
    while (k--) {
        int mr, mc, c1r, c1c, c2r, c2c;
        cin >> mr >> mc >> c1r >> c1c >> c2r >> c2c;

        if (can_escape(mr, mc, c1r, c1c, c2r, c2c)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
