	.cstring
___func__.2270:
	.ascii "bt_add\0"
LC0:
	.ascii "n\0"
LC1:
	.ascii "bt.c\0"
	.text
.globl _bt_add
_bt_add:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	call	L10
"L00000000001$pb":
L10:
	popl	%ebx
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	testl	%esi, %esi
	jne	L2
	movl	$12, (%esp)
	call	L_malloc$stub
	testl	%eax, %eax
	jne	L4
	leal	LC0-"L00000000001$pb"(%ebx), %eax
	movl	%eax, 12(%esp)
	movl	$7, 8(%esp)
	leal	LC1-"L00000000001$pb"(%ebx), %eax
	movl	%eax, 4(%esp)
	leal	___func__.2270-"L00000000001$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L___assert_rtn$stub
L4:
	movl	16(%ebp), %edx
	movl	%edx, (%eax)
	movl	$0, 8(%eax)
	movl	$0, 4(%eax)
	jmp	L6
L2:
	movl	(%esi), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	*%edi
	testl	%eax, %eax
	jns	L7
	movl	16(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	%edi, 4(%esp)
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	call	_bt_add
	movl	%eax, 4(%esi)
	movl	%esi, %eax
	jmp	L6
L7:
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edi, 4(%esp)
	movl	8(%esi), %eax
	movl	%eax, (%esp)
	call	_bt_add
	movl	%eax, 8(%esi)
	movl	%esi, %eax
L6:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.cstring
___func__.2305:
	.ascii "bt_remove\0"
LC2:
	.ascii "*t_\0"
	.text
.globl _bt_remove
_bt_remove:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%ebx, -12(%ebp)
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	call	L26
"L00000000002$pb":
L26:
	popl	%ebx
	movl	8(%ebp), %edi
	movl	(%edi), %esi
	testl	%esi, %esi
	jne	L12
	leal	LC2-"L00000000002$pb"(%ebx), %eax
	movl	%eax, 12(%esp)
	movl	$34, 8(%esp)
	leal	LC1-"L00000000002$pb"(%ebx), %eax
	movl	%eax, 4(%esp)
	leal	___func__.2305-"L00000000002$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L___assert_rtn$stub
L12:
	movl	(%esi), %eax
	movl	%eax, -28(%ebp)
	movl	8(%esi), %edx
	testl	%edx, %edx
	je	L14
	cmpl	$0, 4(%edx)
	jne	L14
	movl	(%edx), %eax
	movl	%eax, (%esi)
	movl	8(%edx), %eax
	movl	%eax, 8(%esi)
	movl	%edx, (%esp)
	call	L_free$stub
	jmp	L17
L14:
	movl	4(%esi), %ecx
	testl	%ecx, %ecx
	je	L18
	cmpl	$0, 8(%ecx)
	jne	L18
	movl	(%ecx), %eax
	movl	%eax, (%esi)
	movl	4(%ecx), %eax
	movl	%eax, 4(%esi)
	movl	%ecx, (%esp)
	call	L_free$stub
	jmp	L17
L18:
	testl	%edx, %edx
	je	L21
	leal	8(%esi), %eax
	call	_go_left
	movl	%eax, (%esi)
	jmp	L17
L21:
	testl	%ecx, %ecx
	je	L23
	leal	4(%esi), %eax
	call	_go_right
	movl	%eax, (%esi)
	jmp	L17
L23:
	movl	%esi, (%esp)
	call	L_free$stub
	movl	$0, (%edi)
L17:
	movl	-28(%ebp), %eax
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
_go_left:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	(%eax), %edx
	cmpl	$0, 4(%edx)
	je	L29
L32:
	leal	4(%edx), %eax
	movl	4(%edx), %edx
	cmpl	$0, 4(%edx)
	jne	L32
L29:
	movl	%eax, (%esp)
	call	_bt_remove
	leave
	ret
_go_right:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	(%eax), %edx
	cmpl	$0, 8(%edx)
	je	L36
L39:
	leal	8(%edx), %eax
	movl	8(%edx), %edx
	cmpl	$0, 8(%edx)
	jne	L39
L36:
	movl	%eax, (%esp)
	call	_bt_remove
	leave
	ret
.globl _bt_remove_if
_bt_remove_if:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$16, %esp
	movl	8(%ebp), %esi
	movl	16(%ebp), %edi
L55:
	movl	(%esi), %eax
	testl	%eax, %eax
	je	L49
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	*12(%ebp)
	testb	%al, %al
	je	L46
	movl	%esi, (%esp)
	call	_bt_remove
	testl	%edi, %edi
	je	L55
	movl	%eax, (%esp)
	call	*%edi
	jmp	L55
L46:
	movl	%edi, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	(%esi), %eax
	addl	$4, %eax
	movl	%eax, (%esp)
	call	_bt_remove_if
	movl	(%esi), %esi
	addl	$8, %esi
	jmp	L55
L49:
	addl	$16, %esp
	popl	%esi
	popl	%edi
	leave
	ret
.globl _bt_free
_bt_free:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%esi, -8(%ebp)
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %esi
	movl	12(%ebp), %edi
	testl	%esi, %esi
	je	L61
	movl	%edi, 4(%esp)
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	call	_bt_free
	movl	%edi, 4(%esp)
	movl	8(%esi), %eax
	movl	%eax, (%esp)
	call	_bt_free
	testl	%edi, %edi
	je	L59
	movl	(%esi), %eax
	movl	%eax, (%esp)
	call	*%edi
L59:
	movl	%esi, (%esp)
	call	L_free$stub
L61:
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	leave
	ret
	.section __IMPORT,__jump_table,symbol_stubs,self_modifying_code+pure_instructions,5
L_malloc$stub:
	.indirect_symbol _malloc
	hlt ; hlt ; hlt ; hlt ; hlt
L___assert_rtn$stub:
	.indirect_symbol ___assert_rtn
	hlt ; hlt ; hlt ; hlt ; hlt
L_free$stub:
	.indirect_symbol _free
	hlt ; hlt ; hlt ; hlt ; hlt
	.subsections_via_symbols
