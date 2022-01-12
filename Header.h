#pragma once
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>
#include <string>
#include <vector>
#include <climits>
#include <chrono>
#include <fstream>
using namespace std;

struct Lankas
{
    int srautas, talpa;

    int virsune_u, virsune_v;

    Lankas(int srautas, int talpa, int virsune_u, int virsune_v)
    {
        this->srautas = srautas;
        this->talpa = talpa;
        this->virsune_u = virsune_u;
        this->virsune_v = virsune_v;
    }
};


struct Virsune
{
    int aukstis, l_srautas;

    Virsune(int aukstis, int l_srautas)
    {
        this->aukstis = aukstis;
        this->l_srautas = l_srautas;
    }
};

struct Grafas
{
    int n;
    vector<Virsune> virsune;
    vector<Lankas> lankas;

    Grafas(int n) {
        this->n = n;

        for (int i = 0; i < n; i++)
            virsune.push_back(Virsune(0, 0));
    }

};

void Pridedam_Lanka(Grafas& g, int virsune_u, int virsune_v, int talpa)
{
    g.lankas.push_back(Lankas(0, talpa, virsune_u, virsune_v));
}
