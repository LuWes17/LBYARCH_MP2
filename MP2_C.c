#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declare the external assembly function
extern double imgCvtGrayIntToDouble(double a);

// Function to generate random pixel values (0 to 255)
int randomPixel() {
    return rand() % 256;
}

// Populate the image with random pixel values
void populateRandomPixels(int **pixels, int height, int width) {
	int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            pixels[i][j] = randomPixel();
        }
    }
}

// Measure execution time of the assembly function
double measureExecutionTime(int **pixels, double **double_pixels, int height, int width) {
    clock_t start, end;
    int i, j;

    start = clock();
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            double_pixels[i][j] = imgCvtGrayIntToDouble((double)pixels[i][j]);
        }
    }
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// Run benchmark for a specific image size
void benchmarkConversion(int height, int width) {
    // Allocate memory for integer pixels
	int i;
    int **pixels = (int **)malloc(height * sizeof(int *));
    double **double_pixels = (double **)malloc(height * sizeof(double *));
    for (i = 0; i < height; i++) {
        pixels[i] = (int *)malloc(width * sizeof(int));
        double_pixels[i] = (double *)malloc(width * sizeof(double));
    }

    // Generate random pixel values
    srand(time(NULL));
    populateRandomPixels(pixels, height, width);

    // Run conversion 30 times and calculate average execution time'
	int run;
    double total_time = 0.0;
    for (run = 0; run < 30; run++) {
        total_time += measureExecutionTime(pixels, double_pixels, height, width);
    }
    printf("Average execution time for %dx%d image: %.6f seconds\n", height, width, total_time / 30);

    // Free allocated memory
    for (i = 0; i < height; i++) {
        free(pixels[i]);
        free(double_pixels[i]);
    }
    free(pixels);
    free(double_pixels);
}

int main() {
    int height, width;
    int i, j;

    printf("Enter height and width of the image: ");
    scanf("%d %d", &height, &width);

    // Allocate memory for integer pixels
    int **pixels = (int **)malloc(height * sizeof(int *));
    for (i = 0; i < height; i++) {
        pixels[i] = (int *)malloc(width * sizeof(int));
    }

    // Allocate memory for double precision pixels
    double **double_pixels = (double **)malloc(height * sizeof(double *));
    for (i = 0; i < height; i++) {
        double_pixels[i] = (double *)malloc(width * sizeof(double));
    }

    // Option to use random or manual input
    printf("Use random pixel values? (1 for yes, 0 for no): ");
    int useRandom;
    scanf("%d", &useRandom);

    if (useRandom) {
        srand(time(NULL)); // Seed random number generator
        populateRandomPixels(pixels, height, width);
		
		 printf("Randomly generated pixel values (0-255):\n");
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                printf("%d ", pixels[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Enter pixel values (integer between 0 and 255):\n");
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                scanf("%d", &pixels[i][j]);
            }
        }
    }

    // Perform conversion
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            double_pixels[i][j] = imgCvtGrayIntToDouble((double)pixels[i][j]);
        }
    }

    // Print results
    printf("Double float pixel values:\n");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%.2lf ", double_pixels[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    for (i = 0; i < height; i++) {
        free(pixels[i]);
        free(double_pixels[i]);
    }
    free(pixels);
    free(double_pixels);

    // Run benchmarks for specific sizes
    printf("Running benchmarks...\n");
    benchmarkConversion(10, 10);
    benchmarkConversion(100, 100);
    benchmarkConversion(1000, 1000);

    return 0;
}
