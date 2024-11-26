section .data
divisor dq 255.0

section .text
bits 64
default rel
global imgCvtGrayIntToDouble

imgCvtGrayIntToDouble:
	movq xmm1, [divisor] 
    divsd xmm0, xmm1    
    ret                 