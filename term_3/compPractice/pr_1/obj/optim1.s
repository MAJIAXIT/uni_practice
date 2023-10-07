	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x20, x19, [sp, #16]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
Lloh0:
	adrp	x0, l_.str@PAGE
Lloh1:
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	add	x8, sp, #12
	str	x8, [sp]
Lloh2:
	adrp	x19, l_.str.1@PAGE
Lloh3:
	add	x19, x19, l_.str.1@PAGEOFF
	mov	x0, x19
	bl	_scanf
	ldr	w8, [sp, #12]
	str	x8, [sp]
Lloh4:
	adrp	x0, l_.str.2@PAGE
Lloh5:
	add	x0, x0, l_.str.2@PAGEOFF
	bl	_printf
Lloh6:
	adrp	x0, l_.str.3@PAGE
Lloh7:
	add	x0, x0, l_.str.3@PAGEOFF
	bl	_printf
	add	x8, sp, #8
	str	x8, [sp]
	mov	x0, x19
	bl	_scanf
	ldr	w8, [sp, #12]
	negs	w9, w8
	and	w9, w9, #0x3
	and	w10, w8, #0x3
	csneg	w9, w10, w9, mi
	cbz	w9, LBB0_2
; %bb.1:
	sub	w8, w8, w9
	add	w8, w8, #4
	str	w8, [sp, #12]
LBB0_2:
	ldp	w9, w8, [sp, #8]
	cmp	w8, w9
	b.le	LBB0_4
; %bb.3:
	mov	w8, #0                          ; =0x0
	b	LBB0_5
LBB0_4:
	add	w10, w8, #4
	add	w11, w9, #1
	cmp	w10, w11
	csinc	w9, w10, w9, gt
	mvn	w11, w8
	add	w9, w9, w11
	and	w11, w9, #0xfffffffc
	add	w11, w8, w11
	lsr	w9, w9, #2
	sub	w12, w9, #1
	mul	w12, w9, w12
	lsr	w12, w12, #1
	madd	w8, w9, w10, w8
	add	w8, w8, w12, lsl #2
	add	w9, w11, #4
	str	w9, [sp, #12]
LBB0_5:
	str	x8, [sp]
Lloh8:
	adrp	x0, l_.str.4@PAGE
Lloh9:
	add	x0, x0, l_.str.4@PAGEOFF
	bl	_printf
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.loh AdrpAdd	Lloh6, Lloh7
	.loh AdrpAdd	Lloh4, Lloh5
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.loh AdrpAdd	Lloh8, Lloh9
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Enter left border  A >= 0: "

l_.str.1:                               ; @.str.1
	.asciz	"%d"

l_.str.2:                               ; @.str.2
	.asciz	"\n%d "

l_.str.3:                               ; @.str.3
	.asciz	"Enter right border B >= 0: "

l_.str.4:                               ; @.str.4
	.asciz	"\nSum: %d\n"

.subsections_via_symbols
