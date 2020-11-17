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

    float D_vote;
    float R_vote;
    float O_vote;

    int D_electors;
    int R_electors;
    int O_electors;

}
races[] =
{
    { "Wyoming",          3,  26.7, 70.4, 2.9},
    { "Wisconsin",       10,  49.6, 48.9, 1.6},
    { "West Virginia",    5,  29.7, 68.6, 1.6},
    { "Washington",      12,  58.4, 39.0, 2.5},
    { "Virginia",        13,  54.3, 44.3, 1.5},
    { "Vermont",          3,  66.4, 30.8, 1.7},
    { "Utah",             6,  37.8, 58.0, 3.5},
    { "Texas",           38,  46.5, 52.1, 1.4},
    { "Tennessee",       11,  37.4, 60.7, 1.5},
    { "South Dakota",     3,  35.6, 61.8, 2.6},
    { "South Carolina",   9,  43.4, 55.1, 1.5},
    { "Rhode Island",     4,  59.6, 38.9, 1.4},
    { "Pennsylvania",    20,  50.0, 48.9, 1.1},
    { "Oregon",           7,  56.9, 40.6, 2.5},
    { "Oklahoma",         7,  65.4, 32.3, 2.2},
    { "Ohio",            18,  45.2, 53.4, 1.4},
    { "North Dakota",     3,  65.5, 31.9, 2.6},
    { "North Carolina",  15,  48.7, 50.1, 1.2},
    { "New York",        29,  56.1, 42.5, 1.4},
    { "New Mexico",       5,  54.3, 43.5, 2.1},
    { "New Jersey",      14,  57.2, 41.5, 1.1},
    { "New Hampshire",    4,  52.8, 45.6, 1.6},
    { "Nevada",           6,  50.1, 47.7, 2.3},
    { "Nebraska",         5,  39.3, 58.6, 2.1},
    { "Montana",          3,  40.5, 56.9, 2.5},
    { "Missouri",        10,  41.3, 56.9, 1.8},
    { "Mississippi",      6,  40.5, 58.1, 1.4},
    { "Minnesota",       10,  52.6, 45.4, 2.2},
    { "Michigan",        16,  50.6, 47.9, 1.5},
    { "Massachusetts",   11,  65.6, 32.6, 1.8},
    { "Maryland",        10,  65.4, 32.8, 1.8},
    { "Maine",            4,  52.9, 44.2, 2.9},
    { "Louisiana",        8,  39.9, 58.5, 1.6},
    { "Kentucky",         8,  36.2, 62.1, 1.7},
    { "Kansas",           6,  41.3, 56.5, 2.2},
    { "Iowa",             6,  45.0, 53.2, 1.8},
    { "Indiana",         11,  41.0, 57.1, 1.9},
    { "Illinois",        20,  57.6, 40.5, 1.9},
    { "Idaho",            4,  33.1, 63.9, 3.0},
    { "Hawaii",           4,  63.7, 34.3, 2.0},
    { "Georgia",         16,  49.5, 49.2, 1.2},
    { "Florida",         29,  47.9, 51.2, 0.9},
    { "DC",               3,  92.9, 5.5, 1.1},
    { "Delaware",         3,  58.8, 39.8, 1.4},
    { "Connecticut",      7,  59.3, 39.2, 1.5},
    { "Colorado",         9,  55.4, 41.9, 2.7},
    { "California",      55,  63.7, 34.1, 2.2},
    { "Arkansas",         6,  34.8, 62.4, 2.8},
    { "Arizona",         11,  49.4, 49.1, 1.5},
    { "Alaska",           3,  42.9, 53.2, 3.9},
    { "Alabama",          9,  36.6, 62.3, 1.1 }
};


enum class Party { Democrat, Republican, Neither };

Party election(int electors)
{
    int dem_electors = 0;
    for (auto& race : races)
    {
        // ...
    }
    return Party::Democrat; // nyi
}

int main(int argc, char *argv[])
{
    int electors = 0;
    for (auto& race : races)
        electors += race.electors;

    assert (electors == 538);

    election(electors);
}
