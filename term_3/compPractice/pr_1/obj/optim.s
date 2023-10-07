	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	wzr, [x29, #-4]
	str	wzr, [sp, #16]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	mov	x9, sp
	sub	x8, x29, #8
	str	x8, [x9]
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	str	x0, [sp, #8]                    ; 8-byte Folded Spill
	bl	_scanf
	ldur	w9, [x29, #-8]
                                        ; implicit-def: $x8
	mov	x8, x9
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_.str.2@PAGE
	add	x0, x0, l_.str.2@PAGEOFF
	bl	_printf
	adrp	x0, l_.str.3@PAGE
	add	x0, x0, l_.str.3@PAGEOFF
	bl	_printf
	ldr	x0, [sp, #8]                    ; 8-byte Folded Reload
	mov	x9, sp
	sub	x8, x29, #12
	str	x8, [x9]
	bl	_scanf
	ldur	w8, [x29, #-8]
	mov	w10, #4                         ; =0x4
	sdiv	w9, w8, w10
	mul	w9, w9, w10
	subs	w8, w8, w9
	subs	w8, w8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB0_2
	b	LBB0_1
LBB0_1:
	ldur	w9, [x29, #-8]
	mov	w8, #4                          ; =0x4
	sdiv	w10, w9, w8
	mul	w10, w10, w8
	subs	w9, w9, w10
	subs	w9, w8, w9
	ldur	w8, [x29, #-8]
	add	w8, w8, w9
	stur	w8, [x29, #-8]
	b	LBB0_2
LBB0_2:
	b	LBB0_3
LBB0_3:                                 ; =>This Inner Loop Header: Depth=1
	ldur	w8, [x29, #-8]
	ldur	w9, [x29, #-12]
	subs	w8, w8, w9
	cset	w8, gt
	tbnz	w8, #0, LBB0_6
	b	LBB0_4
LBB0_4:                                 ;   in Loop: Header=BB0_3 Depth=1
	ldur	w9, [x29, #-8]
	ldr	w8, [sp, #16]
	add	w8, w8, w9
	str	w8, [sp, #16]
	b	LBB0_5
LBB0_5:                                 ;   in Loop: Header=BB0_3 Depth=1
	ldur	w8, [x29, #-8]
	add	w8, w8, #4
	stur	w8, [x29, #-8]
	b	LBB0_3
LBB0_6:
	ldr	w9, [sp, #16]
                                        ; implicit-def: $x8
	mov	x8, x9
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_.str.4@PAGE
	add	x0, x0, l_.str.4@PAGEOFF
	bl	_printf
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
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
