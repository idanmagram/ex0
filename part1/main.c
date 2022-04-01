#include <stdio.h>
#include <stdlib.h>

int getting_size_input();
int power_of_number(double divided_number);


int main()
{
    int size_input;
    int number;
    int power = 0;
    double divided_number;
    int power_sum = 0;
    int i;

    size_input = getting_size_input();

    for (i = 0; i < size_input; i++)
    {
        if (scanf(" %d", &number) != 1)
        {
            return 0;
        }
        else
        {
            divided_number = (double)(number);
            power = power_of_number(divided_number);
            if (power != -1)
            {
                power_sum += power;
                printf("The number %d is a power of 2: %d=2^%d\n",number, number, power);
            }
        }
    }

    return 0;
}

int getting_size_input()
{
    int size_input = 0;
    printf ("Enter size of input:\n");
    scanf ("%d",&size_input);

    if(size_input <= 0)
    {
        printf("Invalid size");
        return 0;
    }
    return size_input;

}

int power_of_number(double divided_number)
{
    int power = 0;

    while(divided_number > 1)
    {
        divided_number /= 2;
        power++;
    }
    if (divided_number == 1)
    {
        return power;
    }
    return -1;
}

