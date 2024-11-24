nasm -f win64 MP2_asm.asm
gcc -c MP2_C.c -o MP2_C.obj -m64
gcc MP2_C.obj MP2_asm.obj -o MP2_C.exe -m64
MP2_C.exe