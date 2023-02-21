#include <iostream>
#include <vector>
#include <string>
#include <fstream>


using namespace std;


struct dal
{
    string name = "";
    int points = 0;
    int uzd = 0;
    int t = 0;
    vector<int> laikai;
};

void fill(dal dalyviai[5], vector<int> limitai, vector<int> taskai);

int main()
{
    dal dalyviai[5];
    ifstream duom("Duomenys.txt");
    ofstream rez("Rezultatai.txt");
    int N = 0;
    vector<int> limitai;
    vector<int> taskai;
    duom >> N;
    for (int i = 0; i < N; i++)
    {
        int temp;
        duom >> temp;
        limitai.push_back(temp);
    }
    for (int i = 0; i < N; i++)
    {
        int temp;
        duom >> temp;
        taskai.push_back(temp);
    }
    for (int i = 0; i < 5; i++)
    {
        duom.ignore();
        for (int j = 0; j < 10; j++)
        {
            char G;
            duom.get(G);
            dalyviai[i].name += G;
        }
        for (int j = 0; j < N; j++)
        {
            int temp;
            duom >> temp;
            dalyviai[i].laikai.push_back(temp);
        }
    }

    fill(dalyviai, limitai, taskai);

    int max_taskai = 0;
    for (int i = 0; i < 5; i++)
    {
        if (dalyviai[i].points > max_taskai)
        {
            max_taskai = dalyviai[i].points;
        }
    }
    rez << max_taskai << '\n';


    for (int i = 0; i < 5; i++)
    {
        for (int j = i; j < 5; j++)
        {
            if (dalyviai[i].uzd < dalyviai[j].uzd)
            {
                swap(dalyviai[i], dalyviai[j]);
            }
        }
    }


    for (int i = 0; i < 5; i++)
    {
        if (dalyviai[i].points == max_taskai)
        {
            rez << dalyviai[i].name << ' ' << dalyviai[i].uzd << ' ' << dalyviai[i].t << '\n';
        }
    }
    duom.close();
    rez.close();
    return 0;
}

void fill(dal dalyviai[5], vector<int> limitai, vector<int> taskai)
{
    for (int i = 0; i < 5; i++)
    {
        //teisingai isspresti uzdviniai
        for (int j = 0; j < dalyviai[i].laikai.size(); j++)
        {
            if (dalyviai[i].laikai[j]>0)
            {
                dalyviai[i].uzd++;
            }
        }
        //uztrukes laikas
        for (int j = 0; j < dalyviai[i].laikai.size(); j++)
        {
            dalyviai[i].t+=dalyviai[i].laikai[j];
        }
        //surinkti taskai
        for (int j = 0; j < dalyviai[i].laikai.size(); j++)
        {
            if (dalyviai[i].laikai[j] > 0)
            {
                if (dalyviai[i].laikai[j] > limitai[j])
                {
                    dalyviai[i].points += taskai[j] / 2;
                }
                else
                {
                    dalyviai[i].points += taskai[j];
                }
            }
        }
    }
}