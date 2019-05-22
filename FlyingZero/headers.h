#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_PLAYERS=10000;
string vardas;
int eurai;
int eurai=START_EURAI;

struct zaidejas
{
    string vardas;
    int eurai;

} zaidejai[MAX_PLAYERS];

void saveScore()
{
    ofstream scores;
    scores.open("scores.txt", ios::app);

    scores << vardas << " ";
    scores << eurai << endl;

    scores.close();
}

#endif // HEADERS_H_INCLUDED

