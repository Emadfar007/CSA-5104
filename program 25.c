#include <stdio.h>

int main()
{
    int pixels[10];
    int even = 0, odd = 0, i;

    printf("Enter 10 Pixel Values:\n");

    for(i = 0; i < 10; i++)
    {
        scanf("%d", &pixels[i]);

        if(pixels[i] % 2 == 0)
            even++;
        else
            odd++;
    }

    printf("\nEven Pixels = %d", even);
    printf("\nOdd Pixels = %d\n", odd);

    if(odd > even)
        printf("Possible Hidden Data Detected.\n");
    else
        printf("No Hidden Data Detected.\n");

    return 0;
}
