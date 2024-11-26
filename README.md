# LBYARCH_MP2

This project demonstrates a C program that integrates an external x86-64 assembly function to convert grayscale pixel values from integers to double precision. It includes benchmarking to analyze the performance of the conversion process across different image sizes.
**Execution Time and Performance Analysis**
Observed Execution Times (Average):
For a **10x10 image**, the average execution time is approximately 0.000001 seconds.
For a **100x100 image**, the average execution time is approximately 0.00002 seconds.
For a **1000x1000 image**, the average execution time is approximately 0.005 seconds.

**Performance Analysis**
The x86-64 assembly function demonstrates highly efficient pixel conversion, with execution times remaining extremely low, even for larger image sizes. Execution time increases roughly linearly with the number of pixels, showcasing good scalability. The assembly optimization ensures precise and fast floating-point calculations, making it ideal for high-performance image processing tasks.
