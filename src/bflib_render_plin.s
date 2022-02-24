
#ifdef NEED_UNDERSCORE
# define TRANSFORM_SYMBOLS
# define EXPORT_SYMBOL(sym) _ ## sym
#else
# define EXPORT_SYMBOL(sym) sym
#endif

#ifndef TRANSFORM_SYMBOLS

# define GLOBAL(sym) \
  .global sym; \
  sym ##:

# define GLOBAL_FUNC(sym) \
  GLOBAL (sym)

#else

# define GLOBAL(sym) \
  .global EXPORT_SYMBOL (sym); \
  EXPORT_SYMBOL (sym) ##: \
  sym ##:

# define GLOBAL_FUNC(sym) \
  .global sym; \
  GLOBAL (sym)

#endif


.text

.global EXPORT_SYMBOL(vec_screen);
.global EXPORT_SYMBOL(vec_screen_width);
.global EXPORT_SYMBOL(vec_colour);
.global EXPORT_SYMBOL(vec_window_height);
.global EXPORT_SYMBOL(vec_window_width);

/*----------------------------------------------------------------*/
GLOBAL_FUNC (poly_line_)
/*----------------------------------------------------------------*/
		push   %ebp
		mov    %esp,%ebp
		add    $0xffffffe8,%esp
		push   %eax
		push   %ebx
		push   %ecx
		push   %edx
		push   %esi
		push   %edi
		mov    %eax,-0x4(%ebp)
		mov    %edx,-0x8(%ebp)
		mov    -0x4(%ebp),%esi
		mov    (%esi),%eax
		mov    %ax,-0x14(%ebp)
		mov    0x4(%esi),%eax
		mov    %ax,-0x12(%ebp)
		mov    -0x8(%ebp),%esi
		mov    (%esi),%eax
		mov    %ax,-0x18(%ebp)
		mov    0x4(%esi),%eax
		mov    %ax,-0x16(%ebp)
		mov    -0x12(%ebp),%bx
		or     %bx,%bx
		jge    jump_127e64
		mov    -0x16(%ebp),%cx
	jump_127dee:
		or     %cx,%cx
		js     jump_1281c3
		sub    %bx,%cx
		mov    -0x18(%ebp),%ax
		sub    -0x14(%ebp),%ax
		neg    %bx
		imul   %bx
		idiv   %cx
		add    %ax,-0x14(%ebp)
		movw   $0x0,-0x12(%ebp)
		mov    -0x16(%ebp),%cx
		mov    EXPORT_SYMBOL(vec_window_height),%bx
		cmp    %bx,%cx
		js     jump_127ee6
	jump_127e29:
		mov    -0x18(%ebp),%ax
		sub    -0x14(%ebp),%ax
		mov    EXPORT_SYMBOL(vec_window_height),%cx
		sub    -0x12(%ebp),%cx
		imul   %cx
		mov    -0x16(%ebp),%cx
		sub    -0x12(%ebp),%cx
		idiv   %cx
		add    -0x14(%ebp),%ax
		mov    %ax,-0x18(%ebp)
		mov    EXPORT_SYMBOL(vec_window_height),%bx
		dec    %bx
		mov    %bx,-0x16(%ebp)
		jmp    jump_127ee6
	jump_127e64:
		mov    -0x16(%ebp),%cx
		or     %cx,%cx
		jge    jump_127e8d
		mov    %cx,-0x12(%ebp)
		mov    %bx,-0x16(%ebp)
		xchg   %bx,%cx
		mov    -0x14(%ebp),%ax
		mov    -0x18(%ebp),%dx
		mov    %dx,-0x14(%ebp)
		mov    %ax,-0x18(%ebp)
		jmp    jump_127dee
	jump_127e8d:
		cmp    %cx,%bx
		je     jump_1280f9
		js     jump_127ecc
		cmp    EXPORT_SYMBOL(vec_window_height),%cx
		jge    jump_1281c3
		mov    %bx,-0x16(%ebp)
		mov    %cx,-0x12(%ebp)
		mov    -0x14(%ebp),%ax
		mov    -0x18(%ebp),%dx
		mov    %dx,-0x14(%ebp)
		mov    %ax,-0x18(%ebp)
		cmp    EXPORT_SYMBOL(vec_window_height),%bx
		jge    jump_127e29
		jmp    jump_127ee6
	jump_127ecc:
		cmp    EXPORT_SYMBOL(vec_window_height),%bx
		jge    jump_1281c3
		cmp    EXPORT_SYMBOL(vec_window_height),%cx
		jge    jump_127e29
	jump_127ee6:
		movl   $0x0,-0xc(%ebp)
		mov    -0x14(%ebp),%bx
		or     %bx,%bx
		jge    jump_127f61
		mov    -0x18(%ebp),%cx
		or     %cx,%cx
		js     jump_1281c3
		movl   $0x1,-0xc(%ebp)
		mov    -0x16(%ebp),%ax
		sub    -0x12(%ebp),%ax
		sub    %bx,%cx
		neg    %bx
		imul   %bx
		idiv   %cx
		add    %ax,-0x12(%ebp)
		movw   $0x0,-0x14(%ebp)
		mov    -0x18(%ebp),%cx
		mov    EXPORT_SYMBOL(vec_window_width),%bx
		cmp    %bx,%cx
		js     jump_128069
		mov    -0x16(%ebp),%ax
		sub    -0x12(%ebp),%ax
		sub    -0x14(%ebp),%bx
		imul   %bx
		idiv   %cx
		add    -0x12(%ebp),%ax
		mov    %ax,-0x16(%ebp)
		dec    %bx
		mov    %bx,-0x18(%ebp)
		jmp    jump_128069
	jump_127f61:
		cmp    EXPORT_SYMBOL(vec_window_width),%bx
		js     jump_127fde
		mov    -0x18(%ebp),%cx
		cmp    EXPORT_SYMBOL(vec_window_width),%cx
		jge    jump_1281c3
		movl   $0xffffffff,-0xc(%ebp)
		mov    -0x16(%ebp),%ax
		sub    -0x12(%ebp),%ax
		mov    %bx,%dx
		sub    EXPORT_SYMBOL(vec_window_width),%dx
		imul   %dx
		sub    %cx,%bx
		idiv   %bx
		add    %ax,-0x12(%ebp)
		mov    EXPORT_SYMBOL(vec_window_width),%ax
		dec    %ax
		mov    %ax,-0x14(%ebp)
		or     %cx,%cx
		jge    jump_128069
		mov    -0x16(%ebp),%ax
		sub    -0x12(%ebp),%ax
		mov    -0x18(%ebp),%bx
		neg    %bx
		imul   %bx
		add    -0x14(%ebp),%bx
		idiv   %bx
		sub    %ax,-0x16(%ebp)
		movw   $0x0,-0x18(%ebp)
		jmp    jump_128069
	jump_127fde:
		mov    -0x18(%ebp),%cx
		or     %cx,%cx
		jge    jump_12800f
		movl   $0xffffffff,-0xc(%ebp)
		mov    -0x16(%ebp),%ax
		sub    -0x12(%ebp),%ax
		imul   %bx
		sub    %cx,%bx
		idiv   %bx
		add    -0x12(%ebp),%ax
		mov    %ax,-0x16(%ebp)
		movw   $0x0,-0x18(%ebp)
		jmp    jump_128069
	jump_12800f:
		cmp    EXPORT_SYMBOL(vec_window_width),%cx
		js     jump_128050
		movl   $0x1,-0xc(%ebp)
		mov    -0x16(%ebp),%ax
		sub    -0x12(%ebp),%ax
		mov    EXPORT_SYMBOL(vec_window_width),%dx
		sub    %bx,%dx
		imul   %dx
		sub    %bx,%cx
		idiv   %cx
		add    -0x12(%ebp),%ax
		mov    %ax,-0x16(%ebp)
		mov    EXPORT_SYMBOL(vec_window_width),%ax
		dec    %ax
		mov    %ax,-0x18(%ebp)
		jmp    jump_128069
	jump_128050:
		movl   $0x1,-0xc(%ebp)
		cmp    %cx,%bx
		je     jump_12817f
		js     jump_128069
		movl   $0xffffffff,-0xc(%ebp)
	jump_128069:
		movzwl -0x14(%ebp),%edi
		movzwl -0x12(%ebp),%eax
		mov    EXPORT_SYMBOL(vec_screen_width),%ebx
		imul   %ebx
		add    %eax,%edi
		add    EXPORT_SYMBOL(vec_screen),%edi
		mov    -0x18(%ebp),%ax
		sub    -0x14(%ebp),%ax
		mov    -0xc(%ebp),%esi
		imul   %si,%ax
		mov    -0x16(%ebp),%cx
		sub    -0x12(%ebp),%cx
		je     jump_128142
		cmp    %ax,%cx
		jbe    jump_1280ad
		xchg   %ax,%cx
		mov    %ebx,-0xc(%ebp)
		mov    %esi,-0x10(%ebp)
		jmp    jump_1280b0
	jump_1280ad:
		mov    %ebx,-0x10(%ebp)
	jump_1280b0:
		mov    %ax,%si
		mov    %cx,%bx
		add    %bx,%bx
		mov    %bx,%dx
		sub    %ax,%bx
		sub    %ax,%cx
		add    %cx,%cx
		mov    EXPORT_SYMBOL(vec_colour),%al
		mov    %al,(%edi)
	jump_1280cc:
		add    -0xc(%ebp),%edi
		or     %bx,%bx
		jge    jump_1280e5
		add    %dx,%bx
		mov    %al,(%edi)
		dec    %si
		jne    jump_1280cc
		pop    %edi
		pop    %esi
		pop    %edx
		pop    %ecx
		pop    %ebx
		pop    %eax
		leave
		ret
	jump_1280e5:
		add    -0x10(%ebp),%edi
		add    %cx,%bx
		mov    %al,(%edi)
		dec    %si
		jne    jump_1280cc
		pop    %edi
		pop    %esi
		pop    %edx
		pop    %ecx
		pop    %ebx
		pop    %eax
		leave
		ret
	jump_1280f9:
		cmp    EXPORT_SYMBOL(vec_window_height),%bx
		jge    jump_1281c3
		movswl -0x14(%ebp),%edi
		movswl -0x18(%ebp),%ecx
		cmp    %edi,%ecx
		jge    jump_128114
		xchg   %ecx,%edi
	jump_128114:
		mov    EXPORT_SYMBOL(vec_window_width),%eax
		dec    %eax
		or     %edi,%edi
		jns    jump_128130
		or     %ecx,%ecx
		jle    jump_1281c3
		xor    %edi,%edi
		cmp    %eax,%ecx
		jle    jump_12813e
		mov    %eax,%ecx
		jmp    jump_12813e
	jump_128130:
		cmp    %eax,%edi
		jg     jump_1281c3
		cmp    %eax,%ecx
		jle    jump_12813e
		mov    %eax,%ecx
	jump_12813e:
		sub    %edi,%ecx
		jmp    jump_12815a
	jump_128142:
		movzwl -0x14(%ebp),%edi
		movzwl -0x18(%ebp),%ecx
		cmp    %di,%cx
		jae    jump_128157
		sub    %cx,%di
		xchg   %di,%cx
		jmp    jump_12815a
	jump_128157:
		sub    %di,%cx
	jump_12815a:
		movzwl -0x12(%ebp),%eax
		mov    EXPORT_SYMBOL(vec_screen_width),%ebx
		imul   %ebx
		add    %eax,%edi
		add    EXPORT_SYMBOL(vec_screen),%edi
		inc    %cx
		mov    EXPORT_SYMBOL(vec_colour),%al
		rep stos %al,%es:(%edi)
		pop    %edi
		pop    %esi
		pop    %edx
		pop    %ecx
		pop    %ebx
		pop    %eax
		leave
		ret
	jump_12817f:
		movzwl -0x14(%ebp),%edi
		movzwl -0x12(%ebp),%eax
		movzwl -0x16(%ebp),%ecx
		cmp    %ax,%cx
		jae    jump_128197
		sub    %cx,%ax
		xchg   %ax,%cx
		jmp    jump_12819a
	jump_128197:
		sub    %ax,%cx
	jump_12819a:
		mov    EXPORT_SYMBOL(vec_screen_width),%ebx
		imul   %ebx
		add    %eax,%edi
		add    EXPORT_SYMBOL(vec_screen),%edi
		inc    %cx
		mov    EXPORT_SYMBOL(vec_colour),%al
	jump_1281b1:
		mov    %al,(%edi)
		add    EXPORT_SYMBOL(vec_screen_width),%edi
		loop   jump_1281b1
		pop    %edi
		pop    %esi
		pop    %edx
		pop    %ecx
		pop    %ebx
		pop    %eax
		leave
		ret
	jump_1281c3:
		pop    %edi
		pop    %esi
		pop    %edx
		pop    %ecx
		pop    %ebx
		pop    %eax
		leave
		ret


