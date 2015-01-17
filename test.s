	.text
_cmp:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	leave
	ret
_test:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	cmpl	$2, %eax
	setle	%al
	movzbl	%al, %eax
	leave
	ret
	.cstring
LC0:
	.ascii "%d\12\0"
	.text
_bt_print_:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	call	L12
"L00000000001$pb":
L12:
	popl	%ebx
	cmpl	$0, 8(%ebp)
	je	L11
	movl	$0, -12(%ebp)
	jmp	L8
L9:
	movl	$32, (%esp)
	call	L_putchar$stub
	leal	-12(%ebp), %eax
	incl	(%eax)
L8:
	movl	-12(%ebp), %eax
	cmpl	12(%ebp), %eax
	jb	L9
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	LC0-"L00000000001$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
	movl	12(%ebp), %edx
	incl	%edx
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_bt_print_
	movl	12(%ebp), %edx
	incl	%edx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_bt_print_
L11:
	addl	$36, %esp
	popl	%ebx
	leave
	ret
_bt_print:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bt_print_
	leave
	ret
.globl _main
_main:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	call	L17
"L00000000002$pb":
L17:
	popl	%ebx
	movl	$0, -12(%ebp)
	movl	-12(%ebp), %edx
	movl	$5, 8(%esp)
	leal	_cmp-"L00000000002$pb"(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_bt_add$stub
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %edx
	movl	$2, 8(%esp)
	leal	_cmp-"L00000000002$pb"(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_bt_add$stub
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %edx
	movl	$4, 8(%esp)
	leal	_cmp-"L00000000002$pb"(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_bt_add$stub
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %edx
	movl	$1, 8(%esp)
	leal	_cmp-"L00000000002$pb"(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_bt_add$stub
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %edx
	movl	$3, 8(%esp)
	leal	_cmp-"L00000000002$pb"(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	L_bt_add$stub
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bt_print
	movl	$0, 8(%esp)
	leal	_test-"L00000000002$pb"(%ebx), %eax
	movl	%eax, 4(%esp)
	leal	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	L_bt_remove_if$stub
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bt_print
	movl	-12(%ebp), %eax
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	L_bt_free$stub
	movl	$0, %eax
	addl	$36, %esp
	popl	%ebx
	leave
	ret
	.section __IMPORT,__jump_table,symbol_stubs,self_modifying_code+pure_instructions,5
L_bt_remove_if$stub:
	.indirect_symbol _bt_remove_if
	hlt ; hlt ; hlt ; hlt ; hlt
L_bt_add$stub:
	.indirect_symbol _bt_add
	hlt ; hlt ; hlt ; hlt ; hlt
L_putchar$stub:
	.indirect_symbol _putchar
	hlt ; hlt ; hlt ; hlt ; hlt
L_printf$stub:
	.indirect_symbol _printf
	hlt ; hlt ; hlt ; hlt ; hlt
L_bt_free$stub:
	.indirect_symbol _bt_free
	hlt ; hlt ; hlt ; hlt ; hlt
	.subsections_via_symbols
