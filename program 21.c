#include <stdio.h>
#include <math.h>

int main()
{
    int original[10] = {100,102,98,105,110,120,115,118,122,125};
    int stego[10]    = {100,103,98,104,111,120,114,118,123,125};

    int i;
    float mse = 0, psnr;

    // Calculate MSE
    for(i = 0; i < 10; i++)
    {
        int diff = original[i] - stego[i];
        mse += diff * diff;
    }

    mse = mse / 10;

    // Calculate PSNR
    if(mse == 0)
        psnr = 99;
    else
        psnr = 10 * log10((255.0 * 255.0) / mse);

    printf("Original Image Pixels:\n");
    for(i = 0; i < 10; i++)
        printf("%d ", original[i]);

    printf("\n\nStego Image Pixels:\n");
    for(i = 0; i < 10; i++)
        printf("%d ", stego[i]);

    printf("\n\nMean Squared Error (MSE) = %.2f", mse);
    printf("\nPeak Signal-to-Noise Ratio (PSNR) = %.2f dB\n", psnr);

    if(psnr > 40)
        printf("Image Quality: Excellent\n");
    else if(psnr > 30)
        printf("Image Quality: Good\n");
    else
        printf("Image Quality: Poor\n");

    return 0;
}
