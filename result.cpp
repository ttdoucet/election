#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <cassert>

using namespace std;

/* Compare winner-take-all allocation of electors to the Jefferson
 * method of allocating seats according the the share of the popular
 * vote, in each state.  This latter is also called the D'Hondt
 * method.
 *
 * The percentages are the current estimates reported by the
 * Associated Press for the 2020 Presidential election, not likely to
 * change much.
 */

struct race
{
    const char *state;
    int electors;

    float D_vote;
    float R_vote;
    float O_vote;
}
races[] =
{
    { "WY",   3,  26.7, 70.4, 2.9},
    { "WI",  10,  49.6, 48.9, 1.6},
    { "WV",   5,  29.7, 68.6, 1.6},
    { "WA",  12,  58.4, 39.0, 2.5},
    { "VA",  13,  54.3, 44.3, 1.5},
    { "VT",   3,  66.4, 30.8, 1.7},
    { "UT",   6,  37.8, 58.0, 3.5},
    { "TX",  38,  46.5, 52.1, 1.4},
    { "TN",  11,  37.4, 60.7, 1.5},
    { "SD",   3,  35.6, 61.8, 2.6},
    { "SC",   9,  43.4, 55.1, 1.5},
    { "RI",   4,  59.6, 38.9, 1.4},
    { "PA",  20,  50.0, 48.9, 1.1},
    { "OR",   7,  56.9, 40.6, 2.5},
    { "OK",   7,  32.3, 65.4, 2.2},
    { "OH",  18,  45.2, 53.4, 1.4},
    { "ND",   3,  31.9, 65.5, 2.6},
    { "NC",  15,  48.7, 50.1, 1.2},
    { "NY",  29,  56.1, 42.5, 1.4},
    { "NM",   5,  54.3, 43.5, 2.1},
    { "NJ",  14,  57.2, 41.5, 1.1},
    { "NH",   4,  52.8, 45.6, 1.6},
    { "NV",   6,  50.1, 47.7, 2.3},
    { "NE",   5,  39.3, 58.6, 2.1},
    { "MT",   3,  40.5, 56.9, 2.5},
    { "MO",  10,  41.3, 56.9, 1.8},
    { "MS",   6,  40.5, 58.1, 1.4},
    { "MN",  10,  52.6, 45.4, 2.2},
    { "MI",  16,  50.6, 47.9, 1.5},
    { "MA",  11,  65.6, 32.6, 1.8},
    { "MD",  10,  65.4, 32.8, 1.8},
    { "ME",   4,  52.9, 44.2, 2.9},
    { "LA",   8,  39.9, 58.5, 1.6},
    { "KY",   8,  36.2, 62.1, 1.7},
    { "KS",   6,  41.3, 56.5, 2.2},
    { "IA",   6,  45.0, 53.2, 1.8},
    { "IN",   11,  41.0, 57.1, 1.9},
    { "IL",   20,  57.6, 40.5, 1.9},
    { "ID",    4,  33.1, 63.9, 3.0},
    { "HI",    4,  63.7, 34.3, 2.0},
    { "GA",   16,  49.5, 49.2, 1.2},
    { "FL",   29,  47.9, 51.2, 0.9},
    { "DC",    3,  92.9, 5.5, 1.1},
    { "DE",    3,  58.8, 39.8, 1.4},
    { "CT",    7,  59.3, 39.2, 1.5},
    { "CO",    9,  55.4, 41.9, 2.7},
    { "CA",   55,  63.7, 34.1, 2.2},
    { "AK",    6,  34.8, 62.4, 2.8},
    { "AZ",   11,  49.4, 49.1, 1.5},
    { "AK",    3,  42.9, 53.2, 3.9},
    { "AL",    9,  36.6, 62.3, 1.1 }
};

void election_jefferson()
{
    int dem = 0;
    int rep = 0;
    int oth = 0;

    cout << "Jefferson allocation:\n\n";

    for (auto& race : races)
    {
        int Dem = 0;
        int Rep = 0;
        int Oth = 0;

        while (Dem + Rep + Oth < race.electors)
        {
            auto dd = race.D_vote / (Dem + 1);
            auto rr = race.R_vote / (Rep + 1);
            auto oo = race.O_vote / (Oth + 1);
            
            auto winning = max( max(dd, rr), oo);

            if (winning == dd)
                Dem++;
            else if (winning == rr)
                Rep++;
            else
                Oth++;
        }

        dem += Dem;
        rep += Rep;
        oth += Oth;

        cout << "    " << race.state
             << "  d: " << Dem
             << "  r: " << Rep;

        if (Oth)
            cout << "  other: " << Oth;

        cout << "\n";
    }

    cout << "\n";
    cout << "    Democratic: " << dem << "\n";
    cout << "    Republican: " << rep << "\n";
    cout << "         Other: " << oth << "\n";
    cout << "\n";
}

void election_wta()
{

    int dem = 0;
    int rep = 0;
    int oth = 0;

    for (auto& race : races)
    {
        auto w_pct = max(max(race.D_vote, race.R_vote), race.O_vote);

        if (w_pct == race.D_vote)
            dem += race.electors;
        else if (w_pct == race.R_vote)
            rep += race.electors;
        else if (w_pct == race.O_vote)
            oth += race.electors;
    }

    cout << "Winner take all:\n";
    cout << "  Democratic: " << dem << "\n";
    cout << "  Republican: " << rep << "\n";
    cout << "       Other: " << oth << "\n";
    cout << "\n";
}

int main(int argc, char *argv[])
{
    int electors = 0;
    for (auto& race : races)
        electors += race.electors;
    assert (electors == 538);

    election_wta();
    cout << "\n";
    election_jefferson();
}
