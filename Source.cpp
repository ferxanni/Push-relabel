#include "Header.h"

void Priessrautis(Grafas& g, int s)
{
    g.virsune[s].aukstis = g.virsune.size();

    int i = 0;

    while (i < g.lankas.size())
    {
        if (g.lankas[i].virsune_u == s)
        {
            g.lankas[i].srautas = g.lankas[i].talpa;

            g.virsune[g.lankas[i].virsune_v].l_srautas = g.virsune[g.lankas[i].virsune_v].l_srautas + g.lankas[i].srautas;

            g.lankas.push_back(Lankas(-g.lankas[i].srautas, 0, g.lankas[i].virsune_v, s));
        }
        i++;
    }
}

int Pertekl_virsune(vector<Virsune>& virsune)
{  

    for (int i = 1; i < virsune.size() - 1; i++)
    {
        if (virsune[i].l_srautas > 0)
        {
            return i;
        }
    }
    return -1;
}


void L_srautas(Grafas& g, int i, int srautas)
{
    int virsune_u = g.lankas[i].virsune_v;

    int virsune_v = g.lankas[i].virsune_u;

    int j = 0;

    while ( j < g.lankas.size())
    {
        if (g.lankas[j].virsune_v == virsune_v && g.lankas[j].virsune_u == virsune_u)
        {
            g.lankas[j].srautas = g.lankas[j].srautas - srautas;
            return;
        }
        j++;
    }

    Lankas l = Lankas(0, srautas, virsune_u, virsune_v);
    g.lankas.push_back(l);
}

int Stumk(Grafas& g, int virsune_u)
{

    for (int i = 0;  i < g.lankas.size(); i++)
    {
        if (g.lankas[i].virsune_u == virsune_u)
        {
            if (g.lankas[i].srautas == g.lankas[i].talpa)
                continue;

            if (g.virsune[virsune_u].aukstis > g.virsune[g.lankas[i].virsune_v].aukstis)
            {
                int srautas = min(g.lankas[i].talpa - g.lankas[i].srautas,
                    g.virsune[virsune_u].l_srautas);

                g.virsune[virsune_u].l_srautas = g.virsune[virsune_u].l_srautas - srautas;

                g.virsune[g.lankas[i].virsune_v].l_srautas = g.virsune[g.lankas[i].virsune_v].l_srautas + srautas;

                g.lankas[i].srautas = g.lankas[i].srautas + srautas;

                L_srautas(g, i, srautas);

                return 1;
            }
          
        }
        
        
    }
    
    return 0;
}

void Kelk(Grafas& g, int virsune_u)
{
    int i = 0;

    while (i < g.lankas.size())
    {
        if (g.lankas[i].virsune_u == virsune_u)
        {
            if (g.lankas[i].srautas == g.lankas[i].talpa)
                continue;
            int d = INT_MAX;

            if (g.virsune[g.lankas[i].virsune_v].aukstis < d)
            {
                d = g.virsune[g.lankas[i].virsune_v].aukstis;

                g.virsune[virsune_u].aukstis = d + 1;
            }
        }
        i++;
    }
   
}

int main()
{
    
    cout << "ivesti ranka 1, ivesti is failo 2" << endl;

    std::string choice;
    std::cin >> choice;

    do
    {
        if (choice == "1")
        {

            int m;
            int u;
            int n;
            int v;
            int talpa;
            int virsune_u;
            int virsune_v;
            cout << "iveskite virsuniu skaiciu ir lanku skaiciu" << endl;
            cin >> n >> m;
            while (std::cin.fail())
            {
                std::cout << "Blogai ivedete duomenis, turite ivesti skaicius, pvz: 4 4" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> n >> m;
            }

            Grafas g(n);

            cout << "pradekite ivedineti virsunes ir talpa" << endl;

            int k;
            int l;
            while (m--) {
                cin >> k >> l >> talpa;
                while (std::cin.fail())
                {
                    std::cout << "Blogai ivedete duomenis, turite ivesti skaicius, pvz: 1 2 5" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin >> k >> l >> talpa;
                }
                virsune_u = k - 1;
                virsune_v = l - 1;
                Pridedam_Lanka(g, virsune_u, virsune_v, talpa);

            }

            int s, t;
            int a;
            int b;


            cout << "iveskite virsunes tarp kuriu norite rasti didziausia srauta" << endl;
            cin >> a >> b;
            while (std::cin.fail())
            {
                std::cout << "Blogai ivedete duomenis, turite ivesti skaicius, pvz: 1 4" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> a >> b;
            }
            s = a - 1;
            t = b - 1;

            auto start = std::chrono::high_resolution_clock::now();
            auto st = start;

            Priessrautis(g, s);

            while (Pertekl_virsune(g.virsune) != -1)
            {
                int virsune_u = Pertekl_virsune(g.virsune);
                if (!Stumk(g, virsune_u))
                {
                    Kelk(g, virsune_u);
                }
            }
            cout << "Rastas didziausias srautas grafe yra: " << g.virsune.back().l_srautas << endl;

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end - start;
            std::cout << "Programos vykdymo trukme: " << diff.count() << " s\n";
            system("pause");

        }

        if (choice == "2")
        {


            ifstream in("test10.txt");



            int V;
            int m;
            int u, virsune_u;
            int n;
            int v, virsune_v;
            int talpa;
            int k;
            int l;
            int s, t;
            int a;
            int b;

            cout << "iveskite virsuniu skaiciu ir briaunu skaiciu" << endl;
            in >> n >> m;
            cout << n << " " << m << endl;

            Grafas g(n);

            cout << "pradekite vesti virsunes ir talpa" << endl;


            while (m--)
            {
                in >> k >> l >> talpa;
                virsune_u = k - 1;
                virsune_v = l - 1;
                cout << virsune_u << " " << virsune_v << " " << talpa << endl;
                Pridedam_Lanka(g, virsune_u, virsune_v, talpa);

            }


            cout << "iveskite virsunes tarp kuriu norite rasti maxflow" << endl;
            in >> a >> b;
            s = a - 1;
            t = b - 1;
            cout << s << " " << t << endl;


            auto start = std::chrono::high_resolution_clock::now();
            auto st = start;

            Priessrautis(g, s);

            while (Pertekl_virsune(g.virsune) != -1)
            {
                int virsune_u = Pertekl_virsune(g.virsune);
                if (!Stumk(g, virsune_u))
                {
                    Kelk(g, virsune_u);
                }
            }

            cout << "Rastas maksimalus srautas grafe yra: " << g.virsune.back().l_srautas << endl;

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end - start;
            std::cout << "Programos vykdymo trukme: " << diff.count() << " s\n";
            system("pause");

        }



    } while (choice != "1" && choice != "2");

    return 0;
}
