#include <iostream>


void BaggingMaxWight(int ws[], int n, int wspec, int i, int lw, int &maxw, int loads[], int maxloads[])
{
    if (i == n || lw == wspec) 
    {
        if (lw > maxw) 
        {
            maxw = lw;
            for (int j = 0; j < n; j++)
            {
                maxloads[j] = loads[j];
            }
        }
        return;
    }

    int w = ws[i];
    if ((lw + w) <= wspec)
    {
        loads[i] = 1;
        BaggingMaxWight(ws, n, wspec, i+1, lw+w, maxw, loads, maxloads);
    } 

    for (int j = i; j < n; j++)
    {
        loads[j] = 0;
    }
    BaggingMaxWight(ws, n, wspec, i+1, lw, maxw, loads, maxloads);
}


void BaggingMaxValue(int ws[], int values[], int n, int wspec, int i, int lw, int lv, int &maxv, int loads[], int maxloads[])
{
    if (i == n || lw == wspec) 
    {
        if (lv > maxv) 
        {
            maxv = lv;
            for (int j = 0; j < n; j++)
            {
                maxloads[j] = loads[j];
            }
        }
        return;
    }

    int w = ws[i];
    int v = values[i];
    if ((lw + w) <= wspec)
    {
        loads[i] = 1;
        BaggingMaxValue(ws, values, n, wspec, i+1, lw+w, lv+v, maxv, loads, maxloads);
    } 

    for (int j = i; j < n; j++)
    {
        loads[j] = 0;
    }
    BaggingMaxValue(ws, values, n, wspec, i+1, lw, lv, maxv, loads, maxloads);
}



int main(void)
{
    int ws[10]= {2, 5, 9, 13, 12, 7, 1, 23, 19, 16};
    int values[10] = {9, 7, 6, 4, 5, 8, 10, 1, 2, 3};
    int n = 10;
    int wspec = 31;
    int i = 0;
    int maxw = 0;
    int maxv = 0;
    int loads1[10] = {0};
    int loads2[10] = {0};
    int maxloads[10] = {0};

    // max weight
    BaggingMaxWight(ws, n, wspec, i, 0, maxw, loads1, maxloads);
    std::cout << maxw << ": ";
    for (int j = 0; j < n; j++)
    {
        if (maxloads[j] == 1) std::cout << ws[j] << " ";
    }
    std::cout << std::endl;


    // max value
    BaggingMaxValue(ws, values, n, wspec, i, 0, 0, maxv, loads2, maxloads);
    std::cout << maxv << ": ";
    for (int j = 0; j < n; j++)
    {
        if (maxloads[j] == 1) std::cout << values[j] << " ";
    }
    std::cout << std::endl;

    return 0;
}
