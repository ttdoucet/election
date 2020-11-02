#include <iostream>
#include <iomanip>
#include <random>
#include <cassert>
using namespace std;

/* For each state, the estimate of the Democrat's chances is from the
 * set of Nate Silver's predictions, published during the afternoon of
 * November 2, 2020.
 *
 * Here we apply the strong assumption that each such estimate is
 * correct, and is independent of any of the others.  In other words,
 * we assume that there is no systematic error in the estimates (or
 * for that matter, no error of any kind).
 *
 * We do this not because it is bad to model such things, but simply to
 * compare it to Nate Silver's estimate of the race overall.  Any difference
 * between what we compute with a simple set of Monte Carlo trials, and Nate's
 * prediction, would seem to be due to the model either directly or indirectly
 * trying to take into account these "polling errors" in some way.
 */

struct race
{
    const char *state;
    int electors;
    double democrat_chance;
}
races[] =
{
    "Wyoming",          3,  0.001675,
    "Wisconsin",       10,  0.93875,
    "West Virginia",    5,  0.0088,
    "Washington",      12,  0.991325,
    "Virginia",        13,  0.989425,
    "Vermont",          3,  0.995325,
    "Utah",             6,  0.041225,
    "Texas",           38,  0.39105,
    "Tennessee",       11,  0.02965,
    "South Dakota",     3,  0.053075,
    "South Carolina",   9,  0.090475,
    "Rhode Island",     4,  0.999125,
    "Pennsylvania",    20,  0.8474,
    "Oregon",           7,  0.9777,
    "Oklahoma",         7,  0.0057,
    "Ohio",            18,  0.456025,
    "North Dakota",     3,  0.022725,
    "North Carolina",  15,  0.645225,
    "New York",        29,  0.9999,
    "New Mexico",       5,  0.975575,
    "New Jersey",      14,  0.992475,
    "New Hampshire",    4,  0.8886,
    "Nevada",           6,  0.870525,
    "Nebraska",         2,  0.00575,
    "NE-3",             1,  0.00025,
    "NE-2",             1,  0.741875,
    "NE-1",             1,  0.04,
    "Montana",          3,  0.151525,
    "Missouri",        10,  0.0705,
    "Mississippi",      6,  0.0852,
    "Minnesota",       10,  0.958925,
    "Michigan",        16,  0.949275,
    "Massachusetts",   11,  0.999575,
    "Maryland",        10,  0.999525,
    "Maine",            2,  0.904725,
    "ME-2",             1,  0.580675,
    "ME-1",             1,  0.9728,
    "Louisiana",        8,  0.0264,
    "Kentucky",         8,  0.014375,
    "Kansas",           6,  0.02855,
    "Iowa",             6,  0.38405,
    "Indiana",         11,  0.044175,
    "Illinois",        20,  0.9993,
    "Idaho",            4,  0.0055,
    "Hawaii",           4,  0.993375,
    "Georgia",         16,  0.5833,
    "Florida",         29,  0.682075,
    "DC",               3,  1,
    "Delaware",         3,  0.99995,
    "Connecticut",      7,  0.998975,
    "Colorado",         9,  0.963825,
    "California",      55,  0.998325,
    "Arkansas",         6,  0.009175,
    "Arizona",         11,  0.677375,
    "Alaska",           3,  0.149875,
    "Alabama",          9,  0.016575,
};

/* Sample the distribution uniformly distributed
 * between zero and one.
 */
double uniform()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0,1);
    return dis(gen);
}

enum class Party { Democrat, Republican, Neither };

Party election(int electors)
{
    int dem_electors = 0;
    for (auto& race : races)
        if (uniform() < race.democrat_chance)
            dem_electors += race.electors;

    if (dem_electors > electors / 2)
        return Party::Democrat;
    else if (dem_electors < electors / 2)
        return Party::Republican;
    else
        return Party::Neither;
}

int main(int argc, char *argv[])
{
    int electors = 0;
    for (auto& race : races)
        electors += race.electors;
    assert (electors == 538);

    const int elections = 40'000;
    int dem = 0, rep = 0, tie = 0;

    for (int i = 0; i < elections; i++)
    {
        Party winner = election(electors);
        if (winner == Party::Democrat)
            dem++;
        else if (winner == Party::Republican)
            rep++;
        else
            tie++;
    }

    // Fun with lambdas.
    auto pct = [](int num, int denom) { return 100.0 * num / denom; };
    auto rpt = [=](string party, int wins) {
                   cout << party << ": " << setw(8) << wins << "    "
                        << fixed << setw(8) << setprecision(4)
                        << pct(wins, elections) << "%\n";
               };

    rpt("Dem", dem);
    rpt("Rep", rep);
    rpt("Tie", tie);
}
