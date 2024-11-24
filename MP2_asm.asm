section .data
divisor dq 255.0 ; Define the divisor as a double-precision constant

section .text
bits 64
default rel
global imgCvtGrayIntToDouble

imgCvtGrayIntToDouble:
	movq xmm1, [divisor] ; Load the value of 'divisor' into the SIMD register xmm1
    divsd xmm0, xmm1     ; Perform scalar double-precision division: xmm0 = xmm0 / xmm1
    ret                  ; Return