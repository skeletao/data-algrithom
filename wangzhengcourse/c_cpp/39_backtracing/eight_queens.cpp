#include <iostream>

void Display(int a[])
{
    std::cout << "start line" << std::endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (a[i] == j) 
            {
                std::cout << 'Q';
            }
            else
            {
                std::cout << '*';
            }
        }
        std::cout << std::endl;
    }
}

bool IsValid(int a[], int i, int j)
{
    int left_up = j-1, right_up = j+1;
    for (int m = i-1; m >= 0; m--)
    {
        if (a[m] == j) return false;
        if (left_up >= 0 && a[m] == left_up) return false;
        if (right_up < 8 && a[m] == right_up) return false;

        left_up--;
        right_up++;
    }
    return true;
}


void EightQueen(int a[], int i)
{
    if (i == 8) 
    {
        Display(a);
        return; 
    }

    for (int j = 0; j < 8; j++)
    {
        if (IsValid(a, i, j))
        {
            a[i] = j;
            EightQueen(a, i+1);
        }
    }

}


int main(void)
{
    int array[8] = {-1};

    EightQueen(array, 0);

    return 0;
}
