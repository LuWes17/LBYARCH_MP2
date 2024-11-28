#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern double imgCvtGrayIntToDouble(double a);

int randomPixel() {
    return rand() % 256;
}

void populateRandomPixels(int **pixels, int height, int width) {
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            pixels[i][j] = randomPixel();
        }
    }
}

void inputPixels(int **pixels, int height, int width) {
	int i, j;
    printf("Enter pixel values (0 to 255) row by row:\n");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            while (1) {
                printf("Pixel [%d][%d]: ", i, j);
                if (scanf("%d", &pixels[i][j]) == 1 && pixels[i][j] >= 0 && pixels[i][j] <= 255) {
                    break;
                } else {
                    printf("Invalid input. Please enter an integer between 0 and 255.\n");
                    while (getchar() != '\n'); 
                }
            }
        }
    }
}

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

void benchmarkConversion(int height, int width) {
    int i;
    int **pixels = (int **)malloc(height * sizeof(int *));
    double **double_pixels = (double **)malloc(height * sizeof(double *));
    for (i = 0; i < height; i++) {
        pixels[i] = (int *)malloc(width * sizeof(int));
        double_pixels[i] = (double *)malloc(width * sizeof(double));
    }

    srand(time(NULL));
    populateRandomPixels(pixels, height, width);

    int run;
    double total_time = 0.0;
    for (run = 0; run < 30; run++) {
        total_time += measureExecutionTime(pixels, double_pixels, height, width);
    }
    printf("Average execution time for %dx%d image: %.6f seconds\n", height, width, total_time / 30);

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

    int **pixels = (int **)malloc(height * sizeof(int *));
    for (i = 0; i < height; i++) {
        pixels[i] = (int *)malloc(width * sizeof(int));
    }

    double **double_pixels = (double **)malloc(height * sizeof(double *));
    for (i = 0; i < height; i++) {
        double_pixels[i] = (double *)malloc(width * sizeof(double));
    }
	
	int choice;
    printf("Choose pixel input method:\n");
    printf("1. Auto-generate random pixel values\n");
    printf("2. Manually input pixel values\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

	if (choice == 1) {
        srand(time(NULL)); 
        populateRandomPixels(pixels, height, width);
    } else if (choice == 2) {
        inputPixels(pixels, height, width);
    } else {
        printf("Invalid choice. Exiting program.\n");
        for (i = 0; i < height; i++) {
            free(pixels[i]);
            free(double_pixels[i]);
        }
        free(pixels);
        free(double_pixels);
        return 1;
    }

      printf("Pixel values (0-255):\n");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%3d ", pixels[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            double_pixels[i][j] = imgCvtGrayIntToDouble((double)pixels[i][j]);
        }
    }

    printf("Double float pixel values:\n");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%.4lf ", double_pixels[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < height; i++) {
        free(pixels[i]);
        free(double_pixels[i]);
    }
    free(pixels);
    free(double_pixels);
	
	 if ((height == 10 && width == 10) || 
        (height == 100 && width == 100) || 
        (height == 1000 && width == 1000)) {
        printf("Running benchmarks for %dx%d image...\n", height, width);
        benchmarkConversion(height, width);
    }

    return 0;
}