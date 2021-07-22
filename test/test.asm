	.file	"test.c"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	_start
	.type	_start, @function
_start:
.LFB0:
	.cfi_startproc
	mov	DWORD PTR -4[rsp], 10
	mov	eax, DWORD PTR -4[rsp]
	add	eax, 1
	mov	DWORD PTR -4[rsp], eax
	mov	eax, DWORD PTR -4[rsp]
	ret
	.cfi_endproc
.LFE0:
	.size	_start, .-_start
	.ident	"GCC: (GNU) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
