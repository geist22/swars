
#ifdef NEED_UNDERSCORE
# define TRANSFORM_SYMBOLS
# define EXPORT_SYMBOL(sym) _ ## sym
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

.global EXPORT_SYMBOL(lbDisplay__WScreen);
.global EXPORT_SYMBOL(lbDisplay__MLeftButton);
.global EXPORT_SYMBOL(lbDisplay__ScreenMode);
.global EXPORT_SYMBOL(lbDisplay__GraphicsScreenWidth);
.global EXPORT_SYMBOL(lbDisplay__GraphicsScreenHeight);
.global EXPORT_SYMBOL(lbKeyOn);
.global EXPORT_SYMBOL(SmackMSSDigDriver);
.global EXPORT_SYMBOL(_LowSoundVolPanAddr);
.global EXPORT_SYMBOL(_LowUnk_1e86c0);
.global EXPORT_SYMBOL(_LowSoundPurgeAddr);
.global EXPORT_SYMBOL(_LowSoundCheckAddr);
.global EXPORT_SYMBOL(_LowSoundPlayedAddr);
.global EXPORT_SYMBOL(_LowSoundCloseAddr);


/*----------------------------------------------------------------*/
func_139100:
/*----------------------------------------------------------------*/
		mov    $0x80000000,%eax
		push   $0xffffffff
		push   $0xfffffffe
	jump_139109:
		decb   data_1598c0
		jne    jump_13911d
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13911d:
		shr    $0x1,%ebp
		jae    jump_139137
		pop    %ecx
		cmp    $0xfffffffe,%ecx
		je     jump_13912f
		push   %ecx
		push   %edi
		add    $0x4,%edi
		jmp    jump_139109
	jump_13912f:
		push   $0xfffffffe
		push   %edi
		add    $0x4,%edi
		jmp    jump_139109
	jump_139137:
		pop    %ecx
		cmp    $0xffffffff,%ecx
		je     jump_139193
		push   %ecx
		cmpb   $0x9,data_1598c0
		jb     jump_139157
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_13917d
	jump_139157:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_13917d:
		pop    %ecx
		mov    %eax,(%edi)
		add    $0x4,%edi
		cmp    $0xfffffffe,%ecx
		je     jump_139109
		mov    %edi,%edx
		sub    %ecx,%edx
		mov    %edx,(%ecx)
		jmp    jump_139109
	jump_139193:
		ret


/*----------------------------------------------------------------*/
func_1391a0:
/*----------------------------------------------------------------*/
		cmpb   $0x9,data_1598c0
		jb     jump_1391b9
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_1391df
	jump_1391b9:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_1391df:
		mov    %al,%ah
		cmpb   $0x9,data_1598c0
		jb     jump_1391fa
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_139220
	jump_1391fa:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_139220:
		xchg   %ah,%al
		mov    %ax,data_1599e0
		cmpb   $0x9,data_1598c0
		jb     jump_139241
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_139267
	jump_139241:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_139267:
		mov    %al,%ah
		cmpb   $0x9,data_1598c0
		jb     jump_139282
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_1392a8
	jump_139282:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_1392a8:
		xchg   %ah,%al
		mov    %ax,data_1599e2
		cmpb   $0x9,data_1598c0
		jb     jump_1392c9
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_1392ef
	jump_1392c9:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_1392ef:
		mov    %al,%ah
		cmpb   $0x9,data_1598c0
		jb     jump_13930a
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_139330
	jump_13930a:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_139330:
		xchg   %ah,%al
		mov    %ax,data_1599e4
		movl   $0x0,(%edx)
		movl   $0x0,0x4(%edx)
		movl   $0x0,0x8(%edx)
		movl   $0x0,0xc(%edx)
		push   $0xffffffff
		push   $0xfffffffe
	jump_139357:
		decb   data_1598c0
		jne    jump_13936b
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13936b:
		shr    $0x1,%ebp
		jae    jump_139385
		pop    %ecx
		cmp    $0xfffffffe,%ecx
		je     jump_13937d
		push   %ecx
		push   %edi
		add    $0x4,%edi
		jmp    jump_139357
	jump_13937d:
		push   $0xfffffffe
		push   %edi
		add    $0x4,%edi
		jmp    jump_139357
	jump_139385:
		pop    %ecx
		cmp    $0xffffffff,%ecx
		je     jump_139462
		push   %edx
		push   %ecx
		mov    data_15988c,%edx
		mov    (%edx),%ecx
		test   $0x80000000,%ecx
		jne    jump_1393cb
	jump_1393a1:
		decb   data_1598c0
		jne    jump_1393b5
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_1393b5:
		shr    $0x1,%ebp
		jb     jump_1393bf
		mov    $0x4,%ecx
	jump_1393bf:
		add    %ecx,%edx
		mov    (%edx),%ecx
		test   $0x80000000,%ecx
		je     jump_1393a1
	jump_1393cb:
		mov    %cx,%ax
		shl    $0x18,%eax
		mov    data_159890,%edx
		mov    (%edx),%ecx
		test   $0x80000000,%ecx
		jne    jump_13940b
	jump_1393e1:
		decb   data_1598c0
		jne    jump_1393f5
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_1393f5:
		shr    $0x1,%ebp
		jb     jump_1393ff
		mov    $0x4,%ecx
	jump_1393ff:
		add    %ecx,%edx
		mov    (%edx),%ecx
		test   $0x80000000,%ecx
		je     jump_1393e1
	jump_13940b:
		mov    %cx,%ax
		pop    %ecx
		pop    %edx
		rol    $0x8,%eax
		cmp    %ax,data_1599e0
		jne    jump_139423
		xor    %eax,%eax
		mov    %edi,0x4(%edx)
		jmp    jump_139441
	jump_139423:
		cmp    %ax,data_1599e2
		jne    jump_139433
		xor    %eax,%eax
		mov    %edi,0x8(%edx)
		jmp    jump_139441
	jump_139433:
		cmp    %ax,data_1599e4
		jne    jump_139441
		xor    %eax,%eax
		mov    %edi,0xc(%edx)
	jump_139441:
		shl    $0x10,%eax
		mov    $0x1,%al
		mov    %eax,(%edi)
		add    $0x4,%edi
		cmp    $0xfffffffe,%ecx
		je     jump_139357
		mov    %edi,%eax
		sub    %ecx,%eax
		shl    $0xd,%eax
		mov    %eax,(%ecx)
		jmp    jump_139357
	jump_139462:
		cmpl   $0x0,0x4(%edx)
		jne    jump_13946b
		mov    %edi,0x4(%edx)
	jump_13946b:
		cmpl   $0x0,0x8(%edx)
		jne    jump_139477
		add    $0x4,%edi
		mov    %edi,0x8(%edx)
	jump_139477:
		cmpl   $0x0,0xc(%edx)
		jne    jump_139483
		add    $0x4,%edi
		mov    %edi,0xc(%edx)
	jump_139483:
		ret


/*----------------------------------------------------------------*/
func_139490:
/*----------------------------------------------------------------*/
		mov    %edx,data_159878
		push   %ebp
		mov    data_1598b4,%ebp
	jump_13949d:
		push   %ebp
		mov    %bp,%ax
		dec    %ax
		mov    data_1598b0,%cl
		mov    data_159878,%edx
		mov    (%edx),%ebp
		test   $0xffff,%ebp
		jne    jump_1394df
	jump_1394b9:
		shr    $0xd,%ebp
		and    $0xffff8,%ebp
		test   $0xff,%cl
		je     jump_1394df
		dec    %cl
		shr    %ax
		jb     jump_1394d3
		mov    $0x4,%ebp
	jump_1394d3:
		add    %ebp,%edx
		mov    (%edx),%ebp
		test   $0xffff,%ebp
		je     jump_1394b9
	jump_1394df:
		pop    %ebp
		sub    data_1598a4,%edx
		shl    $0x8,%edx
		sub    data_1598b0,%cl
		neg    %cl
		mov    %cl,%dl
		mov    %edx,-0x4(%edi,%ebp,4)
		dec    %ebp
		jne    jump_13949d
		pop    %ebp
		ret


/*----------------------------------------------------------------*/
func_139500:
/*----------------------------------------------------------------*/
		decb   data_1598c0
		jne    jump_139514
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_139514:
		shr    $0x1,%ebp
		jb     jump_13952a
		movl   $0x0,(%edx)
		mov    %eax,0x4(%edx)
		mov    %eax,0x8(%edx)
		mov    %eax,0xc(%edx)
		jmp    jump_139584
	jump_13952a:
		push   %edi
		push   %eax
		push   %edx
		push   %eax
		decb   data_1598c0
		jne    jump_139542
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_139542:
		shr    $0x1,%ebp
		jae    jump_139552
		mov    data_15988c,%edi
		call   func_139100
	jump_139552:
		decb   data_1598c0
		jne    jump_139566
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_139566:
		shr    $0x1,%ebp
		jae    jump_139576
		mov    data_159890,%edi
		call   func_139100
	jump_139576:
		pop    %edi
		pop    %edx
		call   func_1391a0
		pop    %edx
		pop    %edi
		call   func_139490
	jump_139584:
		ret


/*----------------------------------------------------------------*/
GLOBAL_FUNC (func_139590)
/*----------------------------------------------------------------*/
		mov    $0x7468,%eax
		ret


/*----------------------------------------------------------------*/
GLOBAL_FUNC (func_1395a0)
/*----------------------------------------------------------------*/
		push   %ebp
		mov    %esp,%ebp
		push   %es
		push   %ebx
		push   %ecx
		push   %edx
		push   %edi
		push   %esi
		mov    %ds,%ax
		mov    %eax,%es
		cld
		mov    0x8(%ebp),%eax
		mov    %eax,data_159e00
		mov    0xc(%ebp),%eax
		mov    %eax,data_159e04
		mov    0x10(%ebp),%eax
		mov    %eax,data_159e08
		mov    0x14(%ebp),%eax
		mov    %eax,data_159e0c
		mov    0x18(%ebp),%eax
		mov    %eax,data_159e10
		mov    0x1c(%ebp),%eax
		mov    %eax,data_159e14
		mov    data_159e00,%esi
		mov    %esi,data_15988c
		add    $0x800,%esi
		mov    %esi,data_159890
		add    $0x800,%esi
		xor    %ebp,%ebp
		movb   $0x1,data_1598c0
		movl   $0xb,data_1598b0
		movl   $0x800,data_1598b4
		mov    $data_159810,%edx
		mov    data_159e04,%edi
		lea    0x7468(%edi),%eax
		mov    %edi,data_1598a4
		add    $0x10,%edi
		call   func_139500
		movl   $0xa,data_1598b0
		movl   $0x400,data_1598b4
		mov    $data_159820,%edx
		mov    data_159e04,%edi
		lea    0x7468(%edi),%eax
		add    $0x2010,%edi
		add    data_159e08,%eax
		call   func_139500
		movl   $0xc,data_1598b0
		movl   $0x1000,data_1598b4
		mov    $data_159830,%edx
		mov    data_159e04,%edi
		lea    0x7468(%edi),%eax
		add    $0x3010,%edi
		add    data_159e08,%eax
		add    data_159e0c,%eax
		call   func_139500
		movl   $0x8,data_1598b0
		movl   $0x100,data_1598b4
		mov    $data_159840,%edx
		mov    data_159e04,%edi
		lea    0x7468(%edi),%eax
		add    $0x7010,%edi
		add    data_159e08,%eax
		add    data_159e0c,%eax
		add    data_159e10,%eax
		call   func_139500
		mov    data_159e04,%edi
		mov    data_159e08,%eax
		mov    %eax,(%edi)
		mov    data_159e0c,%eax
		mov    %eax,0x4(%edi)
		mov    data_159e10,%eax
		mov    %eax,0x8(%edi)
		mov    data_159e14,%eax
		mov    %eax,0xc(%edi)
		add    $0x7414,%edi
		mov    $data_159810,%esi
		mov    $0x10,%ecx
		rep movsl %ds:(%esi),%es:(%edi)
		mov    data_159e00,%edi
		xor    %eax,%eax
		mov    $0x800,%ecx
		rep stos %eax,%es:(%edi)
		mov    data_159e00,%edi
		mov    data_159e04,%esi
		mov    (%esi),%eax
		call   func_1398e0
		mov    data_159e04,%esi
		mov    0x4(%esi),%eax
		add    (%esi),%esi
		call   func_1398e0
		mov    data_159e04,%esi
		mov    0x4(%esi),%ecx
		mov    0x8(%esi),%eax
		add    (%esi),%esi
		add    %ecx,%esi
		call   func_1398e0
		mov    data_159e04,%esi
		mov    0x4(%esi),%edx
		mov    0x8(%esi),%ecx
		mov    0xc(%esi),%eax
		add    (%esi),%esi
		add    %edx,%esi
		add    %ecx,%esi
		call   func_1398e0
		mov    $0x800,%ecx
		mov    $0xffffffff,%eax
		repz scas %es:(%edi),%eax
		sub    $0x4,%edi
		mov    (%edi),%eax
		sub    data_159e00,%edi
		xor    $0xffffffff,%eax
		shl    $0x3,%edi
		bsf    %eax,%edx
		add    %edx,%edi
		mov    %di,data_1598d0
		mov    data_159e04,%esi
		add    $0x7410,%esi
		mov    %di,(%esi)
		mov    data_159e04,%esi
		mov    (%esi),%eax
		call   func_139910
		mov    data_159e04,%esi
		mov    0x4(%esi),%eax
		add    (%esi),%esi
		call   func_139910
		mov    data_159e04,%esi
		mov    0x4(%esi),%ecx
		mov    0x8(%esi),%eax
		add    (%esi),%esi
		add    %ecx,%esi
		call   func_139910
		mov    data_159e04,%esi
		mov    0x4(%esi),%edx
		mov    0x8(%esi),%ecx
		mov    0xc(%esi),%eax
		add    (%esi),%esi
		add    %edx,%esi
		add    %ecx,%esi
		call   func_139910
		pop    %esi
		pop    %edi
		pop    %edx
		pop    %ecx
		pop    %ebx
		pop    %es
		pop    %ebp
		ret

/*----------------------------------------------------------------*/
	jump_139820:
		push   %esi
		push   %ecx
		push   %edx
		mov    %edi,%edx
		mov    0x2(%edx),%esi
		mov    0x6(%edx),%edi
		movzwl 0xa(%edx),%ebx
		cmp    $0x0,%ebx
		je     jump_139845
	jump_139834:
		mov    data_159874,%ecx
		rep movsl %ds:(%esi),%es:(%edi)
		add    data_159880,%edi
		dec    %ebx
		jne    jump_139834
	jump_139845:
		movzwl 0xc(%edx),%ecx
		rep movsl %ds:(%esi),%es:(%edi)
		mov    0xe(%edx),%ax
		call   *data_15989c
		sub    $0x10000,%edi
		movzwl 0x10(%edx),%ecx
		rep movsl %ds:(%esi),%es:(%edi)
		add    data_159880,%edi
		movzwl 0x12(%edx),%ebx
		cmp    $0x0,%ebx
		je     jump_139881
	jump_139870:
		mov    data_159874,%ecx
		rep movsl %ds:(%esi),%es:(%edi)
		add    data_159880,%edi
		dec    %ebx
		jne    jump_139870
	jump_139881:
		xchg   %edx,%edi
		add    $0x14,%edi
		movzwl (%edi),%eax
		mov    %eax,data_159860
		movzwl 0x2(%edi),%eax
		mov    %eax,data_159874
		mov    %eax,data_159868
		movzwl 0x4(%edi),%eax
		mov    %eax,data_15986c
		movzwl 0x6(%edi),%eax
		mov    %eax,data_159884
		movzwl 0x8(%edi),%eax
		mov    %eax,data_159888
		add    $0xa,%edi
		movzwl (%edi),%eax
		add    $0x2,%edi
		mov    %eax,data_159870
		mov    %edi,data_1598a0
		mov    %edx,%edi
		pop    %edx
		pop    %ecx
		pop    %esi
		ret



/*----------------------------------------------------------------*/
func_1398e0:
/*----------------------------------------------------------------*/
		add    $0x7468,%esi
		shr    $0x2,%eax
	jump_1398e9:
		testb  $0x1,(%esi)
		jne    jump_1398f6
		add    $0x4,%esi
		dec    %eax
		jne    jump_1398e9
		jmp    jump_13990f
	jump_1398f6:
		movzwl 0x2(%esi),%edx
		mov    $0x1,%ch
		mov    %dl,%cl
		shr    $0x3,%edx
		and    $0x7,%cl
		shl    %cl,%ch
		or     %ch,(%edi,%edx,1)
		add    $0x4,%esi
		dec    %eax
		jne    jump_1398e9
	jump_13990f:
		ret


/*----------------------------------------------------------------*/
func_139910:
/*----------------------------------------------------------------*/
		add    $0x7468,%esi
		shr    $0x2,%eax
		push   %ebp
		mov    data_1598d0,%bp
	jump_139921:
		testb  $0x1,(%esi)
		jne    jump_139931
		mov    %bp,(%esi)
		add    $0x4,%esi
		dec    %eax
		jne    jump_139921
		jmp    jump_13993e
	jump_139931:
		mov    0x2(%esi),%dx
		mov    %dx,(%esi)
		add    $0x4,%esi
		dec    %eax
		jne    jump_139921
	jump_13993e:
		pop    %ebp
		ret


/*----------------------------------------------------------------*/
func_139940:
/*----------------------------------------------------------------*/
		add    %edx,data_1599f4
		mov    data_1599f4,%ecx
		cmp    %ecx,data_1599f0
		ja     jump_139990
		mov    data_1599f0,%ebx
		add    $0xf,%ecx
		shr    $0x4,%ecx
		shr    $0x4,%ebx
		cmp    %ecx,%ebx
		je     jump_139981
		add    data_1599f8,%ebx
		add    data_1599f8,%ecx
	jump_139973:
		movb   $0x1,(%ebx)
		inc    %ebx
		cmp    %ecx,%ebx
		jne    jump_139973
		sub    data_1599f8,%ecx
	jump_139981:
		shl    $0x4,%ecx
		mov    %ecx,data_1599f0
		xchg   %ebx,%ebx
		xchg   %ecx,%ecx
		xchg   %ebx,%ebx
	jump_139990:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xa,%al
		ja     jump_1399e0
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159804,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0x3ff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_139a2c
		jmp    jump_139a05
	jump_1399e0:
		mov    %ebp,%edx
		mov    data_159804,%ecx
		and    $0x3ff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_139a2c
	jump_139a05:
		shr    $0xd,%edx
		dec    %al
		jne    jump_139a13
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_139a13:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_139a23
		mov    $0x4,%edx
	jump_139a23:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_139a05
	jump_139a2c:
		mov    data_159824,%ecx
		mov    %al,data_1598c0
		mov    %edx,%eax
		cmp    %edx,(%ecx)
		je     jump_139a5d
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159828,%ebx
		mov    %edx,(%ecx)
		mov    data_15982c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_139a5d:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xb,%al
		ja     jump_139ab0
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159800,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0x7ff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_139afc
		jmp    jump_139ad5
	jump_139ab0:
		mov    %ebp,%edx
		mov    data_159800,%ecx
		and    $0x7ff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_139afc
	jump_139ad5:
		shr    $0xd,%edx
		dec    %al
		jne    jump_139ae3
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_139ae3:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_139af3
		mov    $0x4,%edx
	jump_139af3:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_139ad5
	jump_139afc:
		mov    data_159814,%ecx
		ror    $0x10,%edx
		mov    %al,data_1598c0
		mov    %dx,%ax
		ror    $0x10,%edx
		cmp    %edx,(%ecx)
		je     jump_139b34
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159818,%ebx
		mov    %edx,(%ecx)
		mov    data_15981c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_139b34:
		mov    %eax,%edx
		mov    %eax,%ecx
		ror    $0x10,%eax
		mov    %ax,%dx
		mov    %ecx,%eax
		and    $0xff,%eax
		call   *data_159a00(,%eax,4)
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    %ch,%al
		mov    %ebx,(%edi)
		and    $0xff,%eax
		add    data_159860,%edi
		mov    %ebx,(%edi)
		add    data_159860,%edi
		call   *data_159a00(,%eax,4)
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    %ebx,(%edi)
		add    data_159860,%edi
		mov    %ebx,(%edi)
		sub    data_15986c,%edi
		decl   data_159868
		je     jump_139bc0
		decl   data_159864
		jne    jump_139990
		jmp    jump_13c4c0
	jump_139bc0:
		decl   data_159870
		je     jump_139bf0
		add    data_159888,%edi
	jump_139bce:
		mov    data_159874,%eax
		mov    %eax,data_159868
		decl   data_159864
		jne    jump_139990
		jmp    jump_13c4c0
	jump_139bf0:
		testl  $0x1,data_1598ac
		je     jump_13c5c0
		push   %eax
	jump_139c01:
		mov    data_1598a0,%edi
		mov    (%edi),%ax
		cmp    $0xfffd,%ax
		jb     jump_139c30
		cmp    $0xfffe,%ax
		je     jump_139c36
		ja     jump_13c5c0
		push   $func_139c83
		jmp    jump_139820
	jump_139c30:
		call   *data_15989c
	jump_139c36:
		add    $0x2,%edi
		movzwl (%edi),%eax
		mov    %eax,data_159860
		movzwl 0x2(%edi),%eax
		mov    %eax,data_159874
		mov    %eax,data_159868
		movzwl 0x4(%edi),%eax
		mov    %eax,data_15986c
		movzwl 0x6(%edi),%eax
		mov    %eax,data_159884
		movzwl 0x8(%edi),%eax
		mov    %eax,data_159888
		add    $0xa,%edi
		movzwl 0x4(%edi),%eax
		mov    %eax,data_159870
		mov    (%edi),%eax
		add    $0x6,%edi
		mov    %edi,data_1598a0
		mov    %eax,%edi


/*----------------------------------------------------------------*/
func_139c83:
/*----------------------------------------------------------------*/
		cmpl   $0x0,data_159870
		je     jump_139c01
		pop    %eax
		jmp    jump_139bce


/*----------------------------------------------------------------*/
func_139ca0:
/*----------------------------------------------------------------*/
		add    %edx,data_1599f4
		mov    data_1599f4,%ecx
		cmp    %ecx,data_1599f0
		ja     jump_139cf0
		mov    data_1599f0,%ebx
		add    $0xf,%ecx
		shr    $0x4,%ecx
		shr    $0x4,%ebx
		cmp    %ecx,%ebx
		je     jump_139ce1
		add    data_1599f8,%ebx
		add    data_1599f8,%ecx
	jump_139cd3:
		movb   $0x1,(%ebx)
		inc    %ebx
		cmp    %ecx,%ebx
		jne    jump_139cd3
		sub    data_1599f8,%ecx
	jump_139ce1:
		shl    $0x4,%ecx
		mov    %ecx,data_1599f0
		xchg   %ebx,%ebx
		xchg   %ecx,%ecx
		xchg   %ebx,%ebx
	jump_139cf0:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_139d40
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_139d8c
		jmp    jump_139d65
	jump_139d40:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_139d8c
	jump_139d65:
		shr    $0xd,%edx
		dec    %al
		jne    jump_139d73
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_139d73:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_139d83
		mov    $0x4,%edx
	jump_139d83:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_139d65
	jump_139d8c:
		mov    data_159834,%ecx
		mov    %al,data_1598c0
		mov    %edx,%eax
		cmp    %edx,(%ecx)
		je     jump_139dbd
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_139dbd:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_139e10
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_139e5c
		jmp    jump_139e35
	jump_139e10:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_139e5c
	jump_139e35:
		shr    $0xd,%edx
		dec    %al
		jne    jump_139e43
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_139e43:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_139e53
		mov    $0x4,%edx
	jump_139e53:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_139e35
	jump_139e5c:
		mov    data_159834,%ecx
		ror    $0x10,%edx
		mov    %al,data_1598c0
		mov    %dx,%ax
		ror    $0x10,%edx
		cmp    %edx,(%ecx)
		je     jump_139e94
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_139e94:
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_139ef0
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_139f3c
		jmp    jump_139f15
	jump_139ef0:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_139f3c
	jump_139f15:
		shr    $0xd,%edx
		dec    %al
		jne    jump_139f23
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_139f23:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_139f33
		mov    $0x4,%edx
	jump_139f33:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_139f15
	jump_139f3c:
		mov    data_159834,%ecx
		mov    %al,data_1598c0
		mov    %edx,%eax
		cmp    %edx,(%ecx)
		je     jump_139f6d
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_139f6d:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_139fc0
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13a00c
		jmp    jump_139fe5
	jump_139fc0:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13a00c
	jump_139fe5:
		shr    $0xd,%edx
		dec    %al
		jne    jump_139ff3
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_139ff3:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13a003
		mov    $0x4,%edx
	jump_13a003:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_139fe5
	jump_13a00c:
		mov    data_159834,%ecx
		ror    $0x10,%edx
		mov    %al,data_1598c0
		mov    %dx,%ax
		ror    $0x10,%edx
		cmp    %edx,(%ecx)
		je     jump_13a044
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13a044:
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_13a0a0
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13a0ec
		jmp    jump_13a0c5
	jump_13a0a0:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13a0ec
	jump_13a0c5:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13a0d3
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13a0d3:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13a0e3
		mov    $0x4,%edx
	jump_13a0e3:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13a0c5
	jump_13a0ec:
		mov    data_159834,%ecx
		mov    %al,data_1598c0
		mov    %edx,%eax
		cmp    %edx,(%ecx)
		je     jump_13a11d
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13a11d:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_13a170
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13a1bc
		jmp    jump_13a195
	jump_13a170:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13a1bc
	jump_13a195:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13a1a3
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13a1a3:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13a1b3
		mov    $0x4,%edx
	jump_13a1b3:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13a195
	jump_13a1bc:
		mov    data_159834,%ecx
		ror    $0x10,%edx
		mov    %al,data_1598c0
		mov    %dx,%ax
		ror    $0x10,%edx
		cmp    %edx,(%ecx)
		je     jump_13a1f4
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13a1f4:
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_13a250
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13a29c
		jmp    jump_13a275
	jump_13a250:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13a29c
	jump_13a275:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13a283
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13a283:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13a293
		mov    $0x4,%edx
	jump_13a293:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13a275
	jump_13a29c:
		mov    data_159834,%ecx
		mov    %al,data_1598c0
		mov    %edx,%eax
		cmp    %edx,(%ecx)
		je     jump_13a2cd
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13a2cd:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_13a320
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13a36c
		jmp    jump_13a345
	jump_13a320:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13a36c
	jump_13a345:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13a353
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13a353:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13a363
		mov    $0x4,%edx
	jump_13a363:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13a345
	jump_13a36c:
		mov    data_159834,%ecx
		ror    $0x10,%edx
		mov    %al,data_1598c0
		mov    %dx,%ax
		ror    $0x10,%edx
		cmp    %edx,(%ecx)
		je     jump_13a3a4
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13a3a4:
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    %eax,(%edi)
		sub    data_15986c,%edi
		decl   data_159868
		je     jump_13a3d0
		decl   data_159864
		jne    jump_139cf0
		jmp    jump_13c4c0
	jump_13a3d0:
		decl   data_159870
		je     jump_13a400
		add    data_159888,%edi
	jump_13a3de:
		mov    data_159874,%eax
		mov    %eax,data_159868
		decl   data_159864
		jne    jump_139cf0
		jmp    jump_13c4c0
	jump_13a400:
		testl  $0x1,data_1598ac
		je     jump_13c5c0
		push   %eax
	jump_13a411:
		mov    data_1598a0,%edi
		mov    (%edi),%ax
		cmp    $0xfffd,%ax
		jb     jump_13a440
		cmp    $0xfffe,%ax
		je     jump_13a446
		ja     jump_13c5c0
		push   $func_13a493
		jmp    jump_139820
	jump_13a440:
		call   *data_15989c
	jump_13a446:
		add    $0x2,%edi
		movzwl (%edi),%eax
		mov    %eax,data_159860
		movzwl 0x2(%edi),%eax
		mov    %eax,data_159874
		mov    %eax,data_159868
		movzwl 0x4(%edi),%eax
		mov    %eax,data_15986c
		movzwl 0x6(%edi),%eax
		mov    %eax,data_159884
		movzwl 0x8(%edi),%eax
		mov    %eax,data_159888
		add    $0xa,%edi
		movzwl 0x4(%edi),%eax
		mov    %eax,data_159870
		mov    (%edi),%eax
		add    $0x6,%edi
		mov    %edi,data_1598a0
		mov    %eax,%edi


/*----------------------------------------------------------------*/
func_13a493:
/*----------------------------------------------------------------*/
		cmpl   $0x0,data_159870
		je     jump_13a411
		pop    %eax
		jmp    jump_13a3de


/*----------------------------------------------------------------*/
func_13a4b0:
/*----------------------------------------------------------------*/
		add    %edx,data_1599f4
		mov    data_1599f4,%ecx
		cmp    %ecx,data_1599f0
		ja     jump_13a500
		mov    data_1599f0,%ebx
		add    $0xf,%ecx
		shr    $0x4,%ecx
		shr    $0x4,%ebx
		cmp    %ecx,%ebx
		je     jump_13a4f1
		add    data_1599f8,%ebx
		add    data_1599f8,%ecx
	jump_13a4e3:
		movb   $0x1,(%ebx)
		inc    %ebx
		cmp    %ecx,%ebx
		jne    jump_13a4e3
		sub    data_1599f8,%ecx
	jump_13a4f1:
		shl    $0x4,%ecx
		mov    %ecx,data_1599f0
		xchg   %ebx,%ebx
		xchg   %ecx,%ecx
		xchg   %ebx,%ebx
	jump_13a500:
		mov    %ah,%al
		mov    %eax,%ecx
		shl    $0x10,%eax
		mov    %cx,%ax
	jump_13a50a:
		mov    data_159868,%ecx
		cmp    %ecx,data_159864
		jae    jump_13a51e
		mov    data_159864,%ecx
	jump_13a51e:
		mov    data_159860,%ebx
		lea    0x0(,%ecx,4),%edx
		sub    %edx,%ebx
		mov    %ecx,%edx
		rep stos %eax,%es:(%edi)
		add    %ebx,%edi
		mov    %edx,%ecx
		rep stos %eax,%es:(%edi)
		add    %ebx,%edi
		mov    %edx,%ecx
		rep stos %eax,%es:(%edi)
		add    %ebx,%edi
		mov    %edx,%ecx
		rep stos %eax,%es:(%edi)
		add    %ebx,%edi
		mov    %edx,%ecx
		rep stos %eax,%es:(%edi)
		add    %ebx,%edi
		mov    %edx,%ecx
		rep stos %eax,%es:(%edi)
		add    %ebx,%edi
		mov    %edx,%ecx
		rep stos %eax,%es:(%edi)
		add    %ebx,%edi
		mov    %edx,%ecx
		rep stos %eax,%es:(%edi)
		sub    data_159884,%edi
		sub    %edx,data_159868
		je     jump_13a580
		sub    %edx,data_159864
		jne    jump_13a50a
		jmp    jump_13c4c0
	jump_13a580:
		decl   data_159870
		je     jump_13a5b0
		add    data_159888,%edi
	jump_13a58e:
		sub    %edx,data_159864
		mov    data_159874,%ecx
		mov    %ecx,data_159868
		jne    jump_13a50a
		jmp    jump_13c4c0
	jump_13a5b0:
		testl  $0x1,data_1598ac
		je     jump_13c5c0
		push   %eax
	jump_13a5c1:
		mov    data_1598a0,%edi
		mov    (%edi),%ax
		cmp    $0xfffd,%ax
		jb     jump_13a5f0
		cmp    $0xfffe,%ax
		je     jump_13a5f6
		ja     jump_13c5c0
		push   $func_13a643
		jmp    jump_139820
	jump_13a5f0:
		call   *data_15989c
	jump_13a5f6:
		add    $0x2,%edi
		movzwl (%edi),%eax
		mov    %eax,data_159860
		movzwl 0x2(%edi),%eax
		mov    %eax,data_159874
		mov    %eax,data_159868
		movzwl 0x4(%edi),%eax
		mov    %eax,data_15986c
		movzwl 0x6(%edi),%eax
		mov    %eax,data_159884
		movzwl 0x8(%edi),%eax
		mov    %eax,data_159888
		add    $0xa,%edi
		movzwl 0x4(%edi),%eax
		mov    %eax,data_159870
		mov    (%edi),%eax
		add    $0x6,%edi
		mov    %edi,data_1598a0
		mov    %eax,%edi


/*----------------------------------------------------------------*/
func_13a643:
/*----------------------------------------------------------------*/
		cmpl   $0x0,data_159870
		je     jump_13a5c1
		pop    %eax
		jmp    jump_13a58e


/*----------------------------------------------------------------*/
func_13a660:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x10,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a66c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x18,%eax
		mov    %eax,%ebx
		mov    %dl,%bl
		ret


/*----------------------------------------------------------------*/
func_13a678:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x10,%eax
		mov    %eax,%ebx
		mov    %dl,%bh
		ret


/*----------------------------------------------------------------*/
func_13a684:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x10,%eax
		mov    %eax,%ebx
		xchg   %al,%bh
		ret


/*----------------------------------------------------------------*/
func_13a690:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x10,%ebx
		mov    %dl,%bh
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13a6a0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dl,%bh
		ror    $0x8,%eax
		ror    $0x10,%ebx
		mov    %dl,%bh
		ret


/*----------------------------------------------------------------*/
func_13a6b0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x8,%eax
		ror    $0x18,%ebx
		xchg   %ah,%bl
		ret


/*----------------------------------------------------------------*/
func_13a6c0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dl,%bh
		ror    $0x8,%eax
		ror    $0x10,%ebx
		xchg   %ah,%bh
		ret


/*----------------------------------------------------------------*/
func_13a6d0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x10,%ebx
		mov    %dl,%bh
		ret


/*----------------------------------------------------------------*/
func_13a6dc:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x10,%ebx
		xchg   %al,%bh
		ret


/*----------------------------------------------------------------*/
func_13a6e8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dl,%bh
		ror    $0x10,%ebx
		mov    %dl,%bh
		ret


/*----------------------------------------------------------------*/
func_13a6f4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x18,%ebx
		mov    %dl,%bl
		ret


/*----------------------------------------------------------------*/
func_13a700:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x18,%ebx
		xchg   %al,%bl
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13a710:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x8,%eax
		ror    $0x10,%ebx
		mov    %dl,%bh
		ret


/*----------------------------------------------------------------*/
func_13a720:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x10,%eax
		ror    $0x10,%ebx
		mov    %dl,%bh
		ret


/*----------------------------------------------------------------*/
func_13a730:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x8,%eax
		ror    $0x10,%ebx
		xchg   %ah,%bh
		ret


/*----------------------------------------------------------------*/
func_13a740:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x18,%eax
		mov    %eax,%ebx
		mov    %dl,%al
		ret


/*----------------------------------------------------------------*/
func_13a74c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x18,%eax
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a758:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x10,%eax
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a768:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x18,%eax
		mov    %eax,%ebx
		mov    %dh,%ah
		ret


/*----------------------------------------------------------------*/
func_13a774:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x8,%eax
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a784:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dl,%bh
		ror    $0x8,%eax
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a794:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dh,%ah
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a7a4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x18,%eax
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a7b4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a7c0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		mov    %dh,%al
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a7cc:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dl,%bh
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a7d8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a7e4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		mov    %dh,%al
		ror    $0x18,%ebx
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13a7f4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x8,%eax
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a804:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x10,%eax
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a814:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x8,%eax
		ror    $0x18,%ebx
		mov    %dh,%ah
		ret


/*----------------------------------------------------------------*/
func_13a824:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x10,%eax
		mov    %eax,%ebx
		mov    %dl,%ah
		ret


/*----------------------------------------------------------------*/
func_13a830:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x18,%eax
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a840:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x10,%eax
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a84c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x10,%eax
		mov    %eax,%ebx
		mov    %dh,%al
		ret


/*----------------------------------------------------------------*/
func_13a858:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x8,%eax
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a868:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dl,%bh
		ror    $0x8,%eax
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a878:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dh,%ah
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a888:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x18,%eax
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a898:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a8a4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		mov    %dh,%al
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a8b0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dl,%bh
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a8bc:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a8c8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		mov    %dh,%al
		ror    $0x10,%ebx
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13a8d8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x8,%eax
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a8e8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x10,%eax
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a8f8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x8,%eax
		ror    $0x10,%ebx
		mov    %dh,%ah
		ret


/*----------------------------------------------------------------*/
func_13a908:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x10,%eax
		mov    %eax,%ebx
		xchg   %ah,%bl
		ret


/*----------------------------------------------------------------*/
func_13a914:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x18,%eax
		mov    %eax,%ebx
		mov    %dh,%bh
		ret


/*----------------------------------------------------------------*/
func_13a920:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x10,%eax
		mov    %eax,%ebx
		mov    %dh,%bl
		ret


/*----------------------------------------------------------------*/
func_13a92c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %dl,%ah
		ror    $0x18,%eax
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a938:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x18,%eax
		mov    %ax,%bx
		mov    %dl,%al
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a948:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%eax
		mov    %ax,%bx
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a958:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %dx,%ax
		mov    %eax,%ebx
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a968:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x18,%eax
		mov    %ax,%bx
		mov    %dh,%ah
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a978:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x10,%ebx
		mov    %dh,%bl
		ret


/*----------------------------------------------------------------*/
func_13a984:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a990:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dh,%bl
		mov    %dl,%bh
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a99c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		mov    %dl,%bh
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a9a8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %dl,%ah
		ror    $0x18,%eax
		mov    %eax,%ebx
		ror    $0x10,%eax
		ret


/*----------------------------------------------------------------*/
func_13a9b8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %edx,%ebx
		ror    $0x8,%eax
		mov    %ax,%bx
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a9c8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		mov    %dl,%bh
		ror    $0x10,%eax
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a9d8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x8,%eax
		xchg   %ax,%bx
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a9e8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x10,%eax
		mov    %eax,%ebx
		mov    %dl,%ah
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13a9f8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x18,%eax
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13aa08:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x10,%eax
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13aa18:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x10,%eax
		mov    %eax,%ebx
		mov    %dh,%al
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13aa28:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		ror    $0x8,%eax
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13aa34:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dl,%bl
		ret


/*----------------------------------------------------------------*/
func_13aa40:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dx,%ax
		mov    %dl,%bl
		ret


/*----------------------------------------------------------------*/
func_13aa50:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %eax,%ebx
		xchg   %ah,%bl
		ret


/*----------------------------------------------------------------*/
func_13aa5c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13aa68:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dl,%ah
		ror    $0x18,%ebx
		xchg   %al,%bl
		ret


/*----------------------------------------------------------------*/
func_13aa74:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%ebx
		mov    %dl,%bl
		ret


/*----------------------------------------------------------------*/
func_13aa80:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%ebx
		xchg   %al,%bl
		ret


/*----------------------------------------------------------------*/
func_13aa8c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		mov    %dh,%al
		ror    $0x8,%ebx
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13aa9c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x8,%eax
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13aaac:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x10,%eax
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13aabc:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %edx,%ebx
		ror    $0x8,%ebx
		ror    $0x8,%eax
		xchg   %ah,%bl
		ret


/*----------------------------------------------------------------*/
func_13aacc:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %edx,%ebx
		ror    $0x10,%eax
		mov    %dl,%ah
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13aadc:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %edx,%ebx
		ror    $0x18,%eax
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13aaec:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %edx,%ebx
		ror    $0x10,%eax
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13aafc:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dx,%ax
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13ab0c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x18,%eax
		mov    %eax,%ebx
		mov    %dl,%al
		ret


/*----------------------------------------------------------------*/
func_13ab18:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13ab20:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dx,%ax
		ret


/*----------------------------------------------------------------*/
func_13ab2c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dh,%ah
		ret


/*----------------------------------------------------------------*/
func_13ab38:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%ebx
		mov    %dl,%ah
		ret


/*----------------------------------------------------------------*/
func_13ab44:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dh,%al
		ror    $0x8,%ebx
		mov    %dl,%ah
		ret


/*----------------------------------------------------------------*/
func_13ab50:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13ab58:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%ebx
		mov    %dh,%al
		ret


/*----------------------------------------------------------------*/
func_13ab64:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dx,%ax
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13ab74:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %edx,%ebx
		ror    $0x8,%eax
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13ab84:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %edx,%ebx
		ror    $0x8,%ebx
		ror    $0x10,%eax
		ret


/*----------------------------------------------------------------*/
func_13ab94:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %edx,%ebx
		ror    $0x8,%eax
		mov    %dh,%ah
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13aba4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x10,%eax
		ror    $0x8,%ebx
		xchg   %ah,%bh
		ret


/*----------------------------------------------------------------*/
func_13abb4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%ebx
		mov    %dx,%bx
		mov    %dl,%ah
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13abc4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%ebx
		mov    %dx,%bx
		mov    %dl,%ah
		ror    $0x10,%eax
		ret


/*----------------------------------------------------------------*/
func_13abd4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %dx,%ax
		mov    %eax,%ebx
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13abe4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dx,%bx
		mov    %dl,%al
		ret


/*----------------------------------------------------------------*/
func_13abf4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dx,%bx
		ret


/*----------------------------------------------------------------*/
func_13ac00:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %dx,%ax
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13ac0c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dx,%bx
		mov    %dh,%ah
		ret


/*----------------------------------------------------------------*/
func_13ac1c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x18,%ebx
		mov    %ax,%bx
		mov    %dl,%ah
		ret


/*----------------------------------------------------------------*/
func_13ac2c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%ebx
		xchg   %ax,%bx
		ret


/*----------------------------------------------------------------*/
func_13ac38:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%ebx
		mov    %ax,%bx
		ret


/*----------------------------------------------------------------*/
func_13ac44:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x18,%ebx
		mov    %dx,%bx
		mov    %dh,%al
		ret


/*----------------------------------------------------------------*/
func_13ac54:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x18,%eax
		mov    %dx,%ax
		mov    %eax,%ebx
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13ac64:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x18,%ebx
		mov    %dx,%bx
		mov    %dh,%al
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13ac74:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%ebx
		mov    %dx,%bx
		mov    %dh,%al
		ror    $0x10,%eax
		ret


/*----------------------------------------------------------------*/
func_13ac84:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x8,%eax
		ror    $0x18,%ebx
		xchg   %ah,%bl
		ret


/*----------------------------------------------------------------*/
func_13ac94:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %edx,%ebx
		ror    $0x8,%ebx
		ror    $0x10,%eax
		xchg   %ah,%bh
		ret


/*----------------------------------------------------------------*/
func_13aca4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x18,%eax
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13acb4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x10,%eax
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13acc4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		mov    %dl,%ah
		ror    $0x18,%ebx
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13acd4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %eax,%ebx
		xchg   %al,%bh
		ret


/*----------------------------------------------------------------*/
func_13ace0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dh,%bh
		ret


/*----------------------------------------------------------------*/
func_13acec:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dx,%ax
		mov    %dh,%bh
		ret


/*----------------------------------------------------------------*/
func_13acfc:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x18,%eax
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13ad08:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%ebx
		xchg   %ah,%bh
		ret


/*----------------------------------------------------------------*/
func_13ad14:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dh,%al
		ror    $0x18,%ebx
		xchg   %ah,%bh
		ret


/*----------------------------------------------------------------*/
func_13ad20:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%ebx
		mov    %dh,%bh
		ret


/*----------------------------------------------------------------*/
func_13ad2c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13ad38:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dl,%al
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13ad48:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x18,%ebx
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13ad58:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x10,%eax
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13ad68:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dh,%ah
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13ad78:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x10,%eax
		mov    %dl,%ah
		ret


/*----------------------------------------------------------------*/
func_13ad84:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13ad90:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x10,%eax
		ret


/*----------------------------------------------------------------*/
func_13ad9c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x10,%eax
		mov    %dh,%al
		ret


/*----------------------------------------------------------------*/
func_13ada8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13adb4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dl,%bh
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13adc0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x18,%eax
		mov    %dx,%ax
		mov    %dl,%bh
		ret


/*----------------------------------------------------------------*/
func_13add0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%eax
		xchg   %ah,%bh
		ret


/*----------------------------------------------------------------*/
func_13addc:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13ade4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		mov    %dl,%ah
		ret


/*----------------------------------------------------------------*/
func_13adf0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dl,%bh
		ret


/*----------------------------------------------------------------*/
func_13adf8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ret


/*----------------------------------------------------------------*/
func_13ae00:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		mov    %dh,%al
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13ae0c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13ae18:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %al,%bh
		ror    $0x10,%eax
		ret


/*----------------------------------------------------------------*/
func_13ae24:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %edx,%ebx
		ror    $0x8,%eax
		xchg   %ah,%bh
		ret


/*----------------------------------------------------------------*/
func_13ae30:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x10,%eax
		xchg   %ah,%bl
		ret


/*----------------------------------------------------------------*/
func_13ae3c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %edx,%ebx
		ror    $0x18,%eax
		mov    %ax,%bx
		ret


/*----------------------------------------------------------------*/
func_13ae4c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		mov    %dh,%bl
		ror    $0x10,%eax
		ret


/*----------------------------------------------------------------*/
func_13ae58:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13ae64:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%eax
		mov    %ax,%bx
		mov    %dl,%al
		ret


/*----------------------------------------------------------------*/
func_13ae74:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x18,%eax
		mov    %ax,%bx
		ret


/*----------------------------------------------------------------*/
func_13ae80:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%eax
		xchg   %ax,%bx
		ret


/*----------------------------------------------------------------*/
func_13ae8c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x18,%eax
		mov    %ax,%bx
		mov    %dh,%ah
		ret


/*----------------------------------------------------------------*/
func_13ae9c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dl,%bh
		xchg   %ah,%bl
		ret


/*----------------------------------------------------------------*/
func_13aea8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %dh,%al
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13aeb4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dh,%bl
		mov    %dl,%bh
		ret


/*----------------------------------------------------------------*/
func_13aec0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dh,%bl
		xchg   %al,%bh
		ret


/*----------------------------------------------------------------*/
func_13aecc:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13aed8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %edx,%ebx
		ror    $0x8,%eax
		mov    %ax,%bx
		ret


/*----------------------------------------------------------------*/
func_13aee8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		mov    %dl,%bh
		ror    $0x10,%eax
		ret


/*----------------------------------------------------------------*/
func_13aef4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x8,%eax
		xchg   %ah,%bh
		ret


/*----------------------------------------------------------------*/
func_13af00:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %edx,%ebx
		ror    $0x18,%eax
		mov    %dl,%al
		ret


/*----------------------------------------------------------------*/
func_13af0c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %edx,%ebx
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13af18:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %edx,%ebx
		ror    $0x10,%eax
		ret


/*----------------------------------------------------------------*/
func_13af24:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %edx,%ebx
		ror    $0x10,%eax
		mov    %dh,%al
		ret


/*----------------------------------------------------------------*/
func_13af30:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %edx,%ebx
		mov    %dl,%al
		ret


/*----------------------------------------------------------------*/
func_13af3c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13af44:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%eax
		mov    %dx,%ax
		ret


/*----------------------------------------------------------------*/
func_13af50:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %edx,%ebx
		mov    %dh,%ah
		ret


/*----------------------------------------------------------------*/
func_13af5c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dl,%ah
		ret


/*----------------------------------------------------------------*/
func_13af64:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dl,%ah
		mov    %dh,%al
		ret


/*----------------------------------------------------------------*/
func_13af70:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ret


/*----------------------------------------------------------------*/
func_13af78:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dh,%al
		ret


/*----------------------------------------------------------------*/
func_13af80:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %edx,%ebx
		ror    $0x10,%eax
		mov    %dl,%ah
		ret


/*----------------------------------------------------------------*/
func_13af8c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %edx,%ebx
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13af98:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %edx,%ebx
		ror    $0x10,%eax
		ret


/*----------------------------------------------------------------*/
func_13afa4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %edx,%ebx
		ror    $0x8,%eax
		mov    %dh,%ah
		ret


/*----------------------------------------------------------------*/
func_13afb0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %edx,%ebx
		ror    $0x10,%eax
		xchg   %ah,%bl
		ret


/*----------------------------------------------------------------*/
func_13afbc:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13afc8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x10,%eax
		ret


/*----------------------------------------------------------------*/
func_13afd4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		mov    %dl,%ah
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13afe0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%eax
		xchg   %al,%bl
		ret


/*----------------------------------------------------------------*/
func_13afec:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x18,%eax
		mov    %dh,%bl
		ret


/*----------------------------------------------------------------*/
func_13aff8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x18,%eax
		mov    %dx,%ax
		mov    %dh,%bl
		ret


/*----------------------------------------------------------------*/
func_13b008:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13b014:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ret


/*----------------------------------------------------------------*/
func_13b01c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		mov    %dh,%al
		ret


/*----------------------------------------------------------------*/
func_13b028:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dh,%bl
		ret


/*----------------------------------------------------------------*/
func_13b030:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b038:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x8,%eax
		mov    %dl,%al
		ret


/*----------------------------------------------------------------*/
func_13b044:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13b050:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x10,%eax
		ret


/*----------------------------------------------------------------*/
func_13b05c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x8,%eax
		mov    %dh,%ah
		ret


/*----------------------------------------------------------------*/
func_13b068:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x18,%eax
		xchg   %ax,%bx
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b078:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %edx,%ebx
		ror    $0x18,%eax
		mov    %ax,%bx
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b088:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		mov    %dh,%bl
		ror    $0x10,%eax
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b098:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %dh,%al
		ror    $0x8,%eax
		mov    %eax,%ebx
		ror    $0x10,%eax
		ret


/*----------------------------------------------------------------*/
func_13b0a8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%eax
		mov    %ax,%bx
		mov    %dl,%al
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b0b8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x18,%eax
		mov    %ax,%bx
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b0c8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		ror    $0x8,%eax
		mov    %dx,%ax
		mov    %eax,%ebx
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b0d8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		ror    $0x8,%eax
		mov    %ax,%bx
		mov    %dh,%ah
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b0e8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dl,%ah
		mov    %eax,%ebx
		mov    %dh,%bl
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b0f4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %dl,%ah
		mov    %eax,%ebx
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b100:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dl,%bh
		mov    %dh,%bl
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b10c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x8,%ebx
		mov    %dl,%bl
		ret


/*----------------------------------------------------------------*/
func_13b118:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %dl,%ah
		ror    $0x8,%eax
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b124:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dl,%bl
		ret


/*----------------------------------------------------------------*/
func_13b130:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x10,%eax
		mov    %eax,%ebx
		mov    %dl,%bh
		ret


/*----------------------------------------------------------------*/
func_13b13c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x8,%eax
		mov    %eax,%ebx
		xchg   %ah,%bl
		ret


/*----------------------------------------------------------------*/
func_13b148:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x10,%eax
		ror    $0x8,%ebx
		mov    %dl,%ah
		ret


/*----------------------------------------------------------------*/
func_13b158:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x18,%eax
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b168:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x10,%eax
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b178:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		mov    %dl,%ah
		ror    $0x8,%ebx
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13b188:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x8,%eax
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b198:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dh,%bl
		ror    $0x8,%eax
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b1a8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x18,%eax
		mov    %eax,%ebx
		mov    %dl,%al
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b1b8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x18,%eax
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b1c8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b1d4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		mov    %dl,%ah
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b1e0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dh,%bl
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b1ec:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x8,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b1f8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dl,%al
		ret


/*----------------------------------------------------------------*/
func_13b204:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x8,%eax
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b210:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x8,%ebx
		ror    $0x10,%eax
		ret


/*----------------------------------------------------------------*/
func_13b220:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dh,%ah
		ret


/*----------------------------------------------------------------*/
func_13b22c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x10,%eax
		ror    $0x10,%ebx
		mov    %dl,%ah
		ret


/*----------------------------------------------------------------*/
func_13b23c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x18,%eax
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b24c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x10,%eax
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b25c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		mov    %dl,%ah
		ror    $0x10,%ebx
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13b26c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x8,%eax
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b27c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dh,%bl
		ror    $0x8,%eax
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b28c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x18,%eax
		mov    %eax,%ebx
		mov    %dl,%al
		ror    $0x18,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b29c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x10,%ebx
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13b2ac:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b2b8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		mov    %dl,%ah
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b2c4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dh,%bl
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b2d0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x10,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b2dc:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x10,%eax
		mov    %eax,%ebx
		mov    %dl,%ah
		ret


/*----------------------------------------------------------------*/
func_13b2e8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x10,%ebx
		ror    $0x8,%eax
		ret


/*----------------------------------------------------------------*/
func_13b2f8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x10,%eax
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b304:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x10,%eax
		mov    %eax,%ebx
		mov    %dh,%al
		ret


/*----------------------------------------------------------------*/
func_13b310:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x10,%eax
		ror    $0x8,%ebx
		xchg   %ah,%bh
		ret


/*----------------------------------------------------------------*/
func_13b320:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x18,%eax
		ror    $0x8,%ebx
		mov    %dh,%bh
		ret


/*----------------------------------------------------------------*/
func_13b330:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x10,%eax
		ror    $0x8,%ebx
		mov    %dh,%bh
		ret


/*----------------------------------------------------------------*/
func_13b340:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x8,%ebx
		xchg   %ah,%bh
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13b350:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dh,%bl
		ror    $0x8,%eax
		ror    $0x8,%ebx
		xchg   %al,%bh
		ret


/*----------------------------------------------------------------*/
func_13b360:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dh,%bl
		ror    $0x8,%eax
		ror    $0x8,%ebx
		mov    %dh,%bh
		ret


/*----------------------------------------------------------------*/
func_13b370:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x18,%eax
		ror    $0x8,%ebx
		xchg   %al,%bh
		ret


/*----------------------------------------------------------------*/
func_13b380:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x8,%ebx
		mov    %dh,%bh
		ror    $0x18,%eax
		ret


/*----------------------------------------------------------------*/
func_13b390:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		xchg   %ah,%bl
		ror    $0x8,%ebx
		mov    %dh,%bh
		ret


/*----------------------------------------------------------------*/
func_13b39c:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x8,%ebx
		xchg   %ah,%bh
		ret


/*----------------------------------------------------------------*/
func_13b3a8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %edx,%ebx
		mov    %dh,%bl
		ror    $0x8,%ebx
		mov    %dh,%bh
		ret


/*----------------------------------------------------------------*/
func_13b3b4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		mov    %eax,%ebx
		ror    $0x8,%ebx
		mov    %dh,%bh
		ret


/*----------------------------------------------------------------*/
func_13b3c0:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x8,%eax
		mov    %eax,%ebx
		xchg   %al,%bh
		ret


/*----------------------------------------------------------------*/
func_13b3cc:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x8,%eax
		mov    %eax,%ebx
		mov    %dh,%bh
		ret


/*----------------------------------------------------------------*/
func_13b3d8:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x10,%eax
		mov    %eax,%ebx
		mov    %dh,%bl
		ret


/*----------------------------------------------------------------*/
func_13b3e4:
/*----------------------------------------------------------------*/
		mov    %edx,%eax
		mov    %dh,%al
		ror    $0x8,%eax
		mov    %dh,%ah
		mov    %eax,%ebx
		ret


/*----------------------------------------------------------------*/
func_13b3f0:
/*----------------------------------------------------------------*/
		add    %edx,data_1599f4
		mov    data_1599f4,%ecx
		cmp    %ecx,data_1599f0
		ja     jump_13b440
		mov    data_1599f0,%ebx
		add    $0xf,%ecx
		shr    $0x4,%ecx
		shr    $0x4,%ebx
		cmp    %ecx,%ebx
		je     jump_13b431
		add    data_1599f8,%ebx
		add    data_1599f8,%ecx
	jump_13b423:
		movb   $0x1,(%ebx)
		inc    %ebx
		cmp    %ecx,%ebx
		jne    jump_13b423
		sub    data_1599f8,%ecx
	jump_13b431:
		shl    $0x4,%ecx
		mov    %ecx,data_1599f0
		xchg   %ebx,%ebx
		xchg   %ecx,%ecx
		xchg   %ebx,%ebx
	jump_13b440:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xa,%al
		ja     jump_13b490
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159804,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0x3ff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13b4dc
		jmp    jump_13b4b5
	jump_13b490:
		mov    %ebp,%edx
		mov    data_159804,%ecx
		and    $0x3ff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13b4dc
	jump_13b4b5:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13b4c3
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13b4c3:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13b4d3
		mov    $0x4,%edx
	jump_13b4d3:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13b4b5
	jump_13b4dc:
		mov    data_159824,%ecx
		mov    %al,data_1598c0
		mov    %edx,%eax
		cmp    %edx,(%ecx)
		je     jump_13b50d
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159828,%ebx
		mov    %edx,(%ecx)
		mov    data_15982c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13b50d:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xb,%al
		ja     jump_13b560
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159800,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0x7ff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13b5ac
		jmp    jump_13b585
	jump_13b560:
		mov    %ebp,%edx
		mov    data_159800,%ecx
		and    $0x7ff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13b5ac
	jump_13b585:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13b593
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13b593:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13b5a3
		mov    $0x4,%edx
	jump_13b5a3:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13b585
	jump_13b5ac:
		mov    data_159814,%ecx
		ror    $0x10,%edx
		mov    %al,data_1598c0
		mov    %dx,%ax
		ror    $0x10,%edx
		cmp    %edx,(%ecx)
		je     jump_13b5e4
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159818,%ebx
		mov    %edx,(%ecx)
		mov    data_15981c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13b5e4:
		mov    %eax,%edx
		mov    %eax,%ecx
		ror    $0x10,%eax
		mov    %ax,%dx
		mov    %ecx,%eax
		and    $0xff,%eax
		call   *data_159a00(,%eax,4)
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    %ch,%al
		mov    %ebx,(%edi)
		and    $0xff,%eax
		add    data_159860,%edi
		call   *data_159a00(,%eax,4)
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    %ebx,(%edi)
		sub    data_15986c,%edi
		decl   data_159868
		je     jump_13b650
		decl   data_159864
		jne    jump_13b440
		jmp    jump_13c4c0
	jump_13b650:
		decl   data_159870
		je     jump_13b680
		add    data_159888,%edi
	jump_13b65e:
		mov    data_159874,%eax
		mov    %eax,data_159868
		decl   data_159864
		jne    jump_13b440
		jmp    jump_13c4c0
	jump_13b680:
		testl  $0x1,data_1598ac
		je     jump_13c5c0
		push   %eax
	jump_13b691:
		mov    data_1598a0,%edi
		mov    (%edi),%ax
		cmp    $0xfffd,%ax
		jb     jump_13b6c0
		cmp    $0xfffe,%ax
		je     jump_13b6c6
		ja     jump_13c5c0
		push   $func_13b713
		jmp    jump_139820
	jump_13b6c0:
		call   *data_15989c
	jump_13b6c6:
		add    $0x2,%edi
		movzwl (%edi),%eax
		mov    %eax,data_159860
		movzwl 0x2(%edi),%eax
		mov    %eax,data_159874
		mov    %eax,data_159868
		movzwl 0x4(%edi),%eax
		mov    %eax,data_15986c
		movzwl 0x6(%edi),%eax
		mov    %eax,data_159884
		movzwl 0x8(%edi),%eax
		mov    %eax,data_159888
		add    $0xa,%edi
		movzwl 0x4(%edi),%eax
		mov    %eax,data_159870
		mov    (%edi),%eax
		add    $0x6,%edi
		mov    %edi,data_1598a0
		mov    %eax,%edi


/*----------------------------------------------------------------*/
func_13b713:
/*----------------------------------------------------------------*/
		cmpl   $0x0,data_159870
		je     jump_13b691
		pop    %eax
		jmp    jump_13b65e


/*----------------------------------------------------------------*/
func_13b730:
/*----------------------------------------------------------------*/
		add    %edx,data_1599f4
		mov    data_1599f4,%ecx
		cmp    %ecx,data_1599f0
		ja     jump_13b780
		mov    data_1599f0,%ebx
		add    $0xf,%ecx
		shr    $0x4,%ecx
		shr    $0x4,%ebx
		cmp    %ecx,%ebx
		je     jump_13b771
		add    data_1599f8,%ebx
		add    data_1599f8,%ecx
	jump_13b763:
		movb   $0x1,(%ebx)
		inc    %ebx
		cmp    %ecx,%ebx
		jne    jump_13b763
		sub    data_1599f8,%ecx
	jump_13b771:
		shl    $0x4,%ecx
		mov    %ecx,data_1599f0
		xchg   %ebx,%ebx
		xchg   %ecx,%ecx
		xchg   %ebx,%ebx
	jump_13b780:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_13b7d0
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13b81c
		jmp    jump_13b7f5
	jump_13b7d0:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13b81c
	jump_13b7f5:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13b803
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13b803:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13b813
		mov    $0x4,%edx
	jump_13b813:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13b7f5
	jump_13b81c:
		mov    data_159834,%ecx
		mov    %al,data_1598c0
		mov    %edx,%eax
		cmp    %edx,(%ecx)
		je     jump_13b84d
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13b84d:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_13b8a0
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13b8ec
		jmp    jump_13b8c5
	jump_13b8a0:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13b8ec
	jump_13b8c5:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13b8d3
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13b8d3:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13b8e3
		mov    $0x4,%edx
	jump_13b8e3:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13b8c5
	jump_13b8ec:
		mov    data_159834,%ecx
		ror    $0x10,%edx
		mov    %al,data_1598c0
		mov    %dx,%ax
		ror    $0x10,%edx
		cmp    %edx,(%ecx)
		je     jump_13b924
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13b924:
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_13b980
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13b9cc
		jmp    jump_13b9a5
	jump_13b980:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13b9cc
	jump_13b9a5:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13b9b3
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13b9b3:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13b9c3
		mov    $0x4,%edx
	jump_13b9c3:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13b9a5
	jump_13b9cc:
		mov    data_159834,%ecx
		mov    %al,data_1598c0
		mov    %edx,%eax
		cmp    %edx,(%ecx)
		je     jump_13b9fd
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13b9fd:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_13ba50
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13ba9c
		jmp    jump_13ba75
	jump_13ba50:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13ba9c
	jump_13ba75:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13ba83
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13ba83:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13ba93
		mov    $0x4,%edx
	jump_13ba93:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13ba75
	jump_13ba9c:
		mov    data_159834,%ecx
		ror    $0x10,%edx
		mov    %al,data_1598c0
		mov    %dx,%ax
		ror    $0x10,%edx
		cmp    %edx,(%ecx)
		je     jump_13bad4
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13bad4:
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_13bb30
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13bb7c
		jmp    jump_13bb55
	jump_13bb30:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13bb7c
	jump_13bb55:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13bb63
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13bb63:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13bb73
		mov    $0x4,%edx
	jump_13bb73:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13bb55
	jump_13bb7c:
		mov    data_159834,%ecx
		mov    %al,data_1598c0
		mov    %edx,%eax
		cmp    %edx,(%ecx)
		je     jump_13bbad
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13bbad:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_13bc00
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13bc4c
		jmp    jump_13bc25
	jump_13bc00:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13bc4c
	jump_13bc25:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13bc33
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13bc33:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13bc43
		mov    $0x4,%edx
	jump_13bc43:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13bc25
	jump_13bc4c:
		mov    data_159834,%ecx
		ror    $0x10,%edx
		mov    %al,data_1598c0
		mov    %dx,%ax
		ror    $0x10,%edx
		cmp    %edx,(%ecx)
		je     jump_13bc84
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13bc84:
		mov    %eax,(%edi)
		add    data_159860,%edi
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_13bce0
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13bd2c
		jmp    jump_13bd05
	jump_13bce0:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13bd2c
	jump_13bd05:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13bd13
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13bd13:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13bd23
		mov    $0x4,%edx
	jump_13bd23:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13bd05
	jump_13bd2c:
		mov    data_159834,%ecx
		mov    %al,data_1598c0
		mov    %edx,%eax
		cmp    %edx,(%ecx)
		je     jump_13bd5d
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13bd5d:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0xc,%al
		ja     jump_13bdb0
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_159808,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xfff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13bdfc
		jmp    jump_13bdd5
	jump_13bdb0:
		mov    %ebp,%edx
		mov    data_159808,%ecx
		and    $0xfff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13bdfc
	jump_13bdd5:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13bde3
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13bde3:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13bdf3
		mov    $0x4,%edx
	jump_13bdf3:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13bdd5
	jump_13bdfc:
		mov    data_159834,%ecx
		ror    $0x10,%edx
		mov    %al,data_1598c0
		mov    %dx,%ax
		ror    $0x10,%edx
		cmp    %edx,(%ecx)
		je     jump_13be34
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159838,%ebx
		mov    %edx,(%ecx)
		mov    data_15983c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13be34:
		mov    %eax,(%edi)
		sub    data_15986c,%edi
		decl   data_159868
		je     jump_13be60
		decl   data_159864
		jne    jump_13b780
		jmp    jump_13c4c0
	jump_13be60:
		decl   data_159870
		je     jump_13be90
		add    data_159888,%edi
	jump_13be6e:
		mov    data_159874,%eax
		mov    %eax,data_159868
		decl   data_159864
		jne    jump_13b780
		jmp    jump_13c4c0
	jump_13be90:
		testl  $0x1,data_1598ac
		je     jump_13c5c0
		push   %eax
	jump_13bea1:
		mov    data_1598a0,%edi
		mov    (%edi),%ax
		cmp    $0xfffd,%ax
		jb     jump_13bed0
		cmp    $0xfffe,%ax
		je     jump_13bed6
		ja     jump_13c5c0
		push   $func_13bf23
		jmp    jump_139820
	jump_13bed0:
		call   *data_15989c
	jump_13bed6:
		add    $0x2,%edi
		movzwl (%edi),%eax
		mov    %eax,data_159860
		movzwl 0x2(%edi),%eax
		mov    %eax,data_159874
		mov    %eax,data_159868
		movzwl 0x4(%edi),%eax
		mov    %eax,data_15986c
		movzwl 0x6(%edi),%eax
		mov    %eax,data_159884
		movzwl 0x8(%edi),%eax
		mov    %eax,data_159888
		add    $0xa,%edi
		movzwl 0x4(%edi),%eax
		mov    %eax,data_159870
		mov    (%edi),%eax
		add    $0x6,%edi
		mov    %edi,data_1598a0
		mov    %eax,%edi


/*----------------------------------------------------------------*/
func_13bf23:
/*----------------------------------------------------------------*/
		cmpl   $0x0,data_159870
		je     jump_13bea1
		pop    %eax
		jmp    jump_13be6e


/*----------------------------------------------------------------*/
func_13bf40:
/*----------------------------------------------------------------*/
		mov    data_1599f4,%ecx
		add    %edx,%ecx
		mov    %ecx,data_1599f4
		mov    data_1599f0,%eax
		cmp    %ecx,%eax
		ja     jump_13bf84
		shr    $0x4,%ecx
		shr    $0x4,%eax
		cmp    %ecx,%eax
		jae    jump_13bf7b
		add    data_1599f8,%eax
		add    data_1599f8,%ecx
	jump_13bf6d:
		movb   $0x0,(%eax)
		inc    %eax
		cmp    %ecx,%eax
		jne    jump_13bf6d
		sub    data_1599f8,%ecx
	jump_13bf7b:
		shl    $0x4,%ecx
		mov    %ecx,data_1599f0
	jump_13bf84:
		mov    data_159868,%ecx
		cmp    %ecx,%edx
		jae    jump_13bf90
		mov    %edx,%ecx
	jump_13bf90:
		lea    (%edi,%ecx,4),%edi
		sub    %ecx,data_159868
		je     jump_13bfb0
		sub    %ecx,%edx
		jne    jump_13bf84
		jmp    jump_13c4c0
	jump_13bfb0:
		decl   data_159870
		je     jump_13bfe0
		add    data_159888,%edi
	jump_13bfbe:
		mov    data_159874,%eax
		mov    %eax,data_159868
		sub    %ecx,%edx
		jne    jump_13bf84
		jmp    jump_13c4c0
	jump_13bfe0:
		testl  $0x1,data_1598ac
		je     jump_13c5c0
		push   %eax
	jump_13bff1:
		mov    data_1598a0,%edi
		mov    (%edi),%ax
		cmp    $0xfffd,%ax
		jb     jump_13c020
		cmp    $0xfffe,%ax
		je     jump_13c026
		ja     jump_13c5c0
		push   $func_13c073
		jmp    jump_139820
	jump_13c020:
		call   *data_15989c
	jump_13c026:
		add    $0x2,%edi
		movzwl (%edi),%eax
		mov    %eax,data_159860
		movzwl 0x2(%edi),%eax
		mov    %eax,data_159874
		mov    %eax,data_159868
		movzwl 0x4(%edi),%eax
		mov    %eax,data_15986c
		movzwl 0x6(%edi),%eax
		mov    %eax,data_159884
		movzwl 0x8(%edi),%eax
		mov    %eax,data_159888
		add    $0xa,%edi
		movzwl 0x4(%edi),%eax
		mov    %eax,data_159870
		mov    (%edi),%eax
		add    $0x6,%edi
		mov    %edi,data_1598a0
		mov    %eax,%edi


/*----------------------------------------------------------------*/
func_13c073:
/*----------------------------------------------------------------*/
		cmpl   $0x0,data_159870
		je     jump_13bff1
		pop    %eax
		jmp    jump_13bfbe


/*----------------------------------------------------------------*/
func_13c090:
/*----------------------------------------------------------------*/
		add    %edx,data_1599f4
		mov    data_1599f4,%ecx
		cmp    %ecx,data_1599f0
		ja     jump_13c0e0
		mov    data_1599f0,%ebx
		add    $0xf,%ecx
		shr    $0x4,%ecx
		shr    $0x4,%ebx
		cmp    %ecx,%ebx
		je     jump_13c0d1
		add    data_1599f8,%ebx
		add    data_1599f8,%ecx
	jump_13c0c3:
		movb   $0x1,(%ebx)
		inc    %ebx
		cmp    %ecx,%ebx
		jne    jump_13c0c3
		sub    data_1599f8,%ecx
	jump_13c0d1:
		shl    $0x4,%ecx
		mov    %ecx,data_1599f0
		xchg   %ebx,%ebx
		xchg   %ecx,%ecx
		xchg   %ebx,%ebx
	jump_13c0e0:
		mov    %ah,%al
		mov    %eax,%ecx
		shl    $0x10,%eax
		mov    %cx,%ax
	jump_13c0ea:
		mov    data_159868,%ecx
		cmp    %ecx,data_159864
		jae    jump_13c0fe
		mov    data_159864,%ecx
	jump_13c0fe:
		mov    data_159860,%ebx
		lea    0x0(,%ecx,4),%edx
		sub    %edx,%ebx
		mov    %ecx,%edx
		rep stos %eax,%es:(%edi)
		add    %ebx,%edi
		mov    %edx,%ecx
		rep stos %eax,%es:(%edi)
		add    %ebx,%edi
		mov    %edx,%ecx
		rep stos %eax,%es:(%edi)
		add    %ebx,%edi
		mov    %edx,%ecx
		rep stos %eax,%es:(%edi)
		sub    data_159884,%edi
		sub    %edx,data_159868
		je     jump_13c140
		sub    %edx,data_159864
		jne    jump_13c0ea
		jmp    jump_13c4c0
	jump_13c140:
		decl   data_159870
		je     jump_13c170
		add    data_159888,%edi
	jump_13c14e:
		sub    %edx,data_159864
		mov    data_159874,%ecx
		mov    %ecx,data_159868
		jne    jump_13c0ea
		jmp    jump_13c4c0
	jump_13c170:
		testl  $0x1,data_1598ac
		je     jump_13c5c0
		push   %eax
	jump_13c181:
		mov    data_1598a0,%edi
		mov    (%edi),%ax
		cmp    $0xfffd,%ax
		jb     jump_13c1b0
		cmp    $0xfffe,%ax
		je     jump_13c1b6
		ja     jump_13c5c0
		push   $func_13c203
		jmp    jump_139820
	jump_13c1b0:
		call   *data_15989c
	jump_13c1b6:
		add    $0x2,%edi
		movzwl (%edi),%eax
		mov    %eax,data_159860
		movzwl 0x2(%edi),%eax
		mov    %eax,data_159874
		mov    %eax,data_159868
		movzwl 0x4(%edi),%eax
		mov    %eax,data_15986c
		movzwl 0x6(%edi),%eax
		mov    %eax,data_159884
		movzwl 0x8(%edi),%eax
		mov    %eax,data_159888
		add    $0xa,%edi
		movzwl 0x4(%edi),%eax
		mov    %eax,data_159870
		mov    (%edi),%eax
		add    $0x6,%edi
		mov    %edi,data_1598a0
		mov    %eax,%edi


/*----------------------------------------------------------------*/
func_13c203:
/*----------------------------------------------------------------*/
		cmpl   $0x0,data_159870
		je     jump_13c181
		pop    %eax
		jmp    jump_13c14e


/*----------------------------------------------------------------*/
GLOBAL_FUNC (Unsmack)
/*----------------------------------------------------------------*/
		push   %ebp
		mov    %esp,%ebp
		push   %es
		push   %ebx
		push   %edi
		push   %esi
		push   %edx
		mov    %ds,%ax
		mov    %eax,%es
		cld
		mov    0xc(%ebp),%esi
		mov    %esi,data_1598a4
		add    $0x7410,%esi
		mov    (%esi),%eax
		add    $0x4,%esi
		mov    %ax,data_1598d0
		mov    $data_159810,%edi
		mov    $0x4,%ecx
	jump_13c252:
		lods   %ds:(%esi),%eax
		stos   %eax,%es:(%edi)
		mov    %eax,%edx
		lods   %ds:(%esi),%eax
		stos   %eax,%es:(%edi)
		mov    %edx,(%eax)
		lods   %ds:(%esi),%eax
		stos   %eax,%es:(%edi)
		mov    %edx,(%eax)
		lods   %ds:(%esi),%eax
		stos   %eax,%es:(%edi)
		mov    %edx,(%eax)
		dec    %ecx
		jne    jump_13c252
		mov    0xc(%ebp),%eax
		add    $0x10,%eax
		mov    %eax,data_159800
		add    $0x2000,%eax
		mov    %eax,data_159804
		add    $0x1000,%eax
		mov    %eax,data_159808
		add    $0x4000,%eax
		mov    %eax,data_15980c
		mov    0x10(%ebp),%edi
		mov    0x8(%ebp),%esi
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x21,data_1598c0
		mov    (%edi),%al
		and    $0x1,%eax
		xor    $0x1,%eax
		mov    %eax,data_1598ac
		testb  $0x1,0x1(%edi)
		jne    jump_13c31d
		testl  $0x1,data_1598ac
		je     jump_13c2e9
		movl   $jump_13b440,data_159850
		movl   $jump_13b780,data_159854
		movl   $jump_13bf84,data_159858
		movl   $jump_13c0e0,data_15985c
		jmp    jump_13c311
	jump_13c2e9:
		movl   $func_13b3f0,data_159850
		movl   $func_13b730,data_159854
		movl   $func_13bf40,data_159858
		movl   $func_13c090,data_15985c
	jump_13c311:
		movl   $0x0,data_1598a8
		jmp    jump_13c385
	jump_13c31d:
		testl  $0x1,data_1598ac
		je     jump_13c353
		movl   $jump_139990,data_159850
		movl   $jump_139cf0,data_159854
		movl   $jump_13bf84,data_159858
		movl   $jump_13a500,data_15985c
		jmp    jump_13c37b
	jump_13c353:
		movl   $func_139940,data_159850
		movl   $func_139ca0,data_159854
		movl   $func_13bf40,data_159858
		movl   $func_13a4b0,data_15985c
	jump_13c37b:
		movl   $0x1,data_1598a8
	jump_13c385:
		testl  $0x1,data_1598ac
		je     jump_13c453
		mov    0x4(%edi),%eax
		mov    %eax,data_15989c
		movzwl 0x8(%edi),%eax
		mov    %eax,data_159880
		add    $0xa,%edi
		mov    %edi,data_1598a0
		nop
		testl  $0x1,data_1598ac
		je     jump_13c5c0
		push   %eax
	jump_13c3c1:
		mov    data_1598a0,%edi
		mov    (%edi),%ax
		cmp    $0xfffd,%ax
		jb     jump_13c3f0
		cmp    $0xfffe,%ax
		je     jump_13c3f6
		ja     jump_13c5c0
		push   $jump_13c443
		jmp    jump_139820
	jump_13c3f0:
		call   *data_15989c
	jump_13c3f6:
		add    $0x2,%edi
		movzwl (%edi),%eax
		mov    %eax,data_159860
		movzwl 0x2(%edi),%eax
		mov    %eax,data_159874
		mov    %eax,data_159868
		movzwl 0x4(%edi),%eax
		mov    %eax,data_15986c
		movzwl 0x6(%edi),%eax
		mov    %eax,data_159884
		movzwl 0x8(%edi),%eax
		mov    %eax,data_159888
		add    $0xa,%edi
		movzwl 0x4(%edi),%eax
		mov    %eax,data_159870
		mov    (%edi),%eax
		add    $0x6,%edi
		mov    %edi,data_1598a0
		mov    %eax,%edi
	jump_13c443:
		cmpl   $0x0,data_159870
		je     jump_13c3c1
		pop    %eax
		jmp    jump_13c4b9
	jump_13c453:
		mov    0x8(%edi),%eax
		mov    %eax,data_159874
		mov    %eax,data_159868
		mov    0xc(%edi),%eax
		mov    %eax,data_159870
		mov    0x10(%edi),%eax
		mov    %eax,data_15986c
		mov    0x14(%edi),%eax
		mov    %eax,data_159884
		mov    0x18(%edi),%eax
		mov    %eax,data_159860
		mov    0x1c(%edi),%eax
		mov    %eax,data_159888
		mov    0x4(%edi),%eax
		movl   $0x0,0x20(%edi)
		movl   $0x0,0x2c(%edi)
		movl   $0x0,0x30(%edi)
		add    $0x38,%edi
		mov    %edi,data_1599f8
		xor    %edi,%edi
		mov    %edi,data_1599f4
		mov    %edi,data_1599f0
		mov    %eax,%edi
	jump_13c4b9:
		jmp    jump_13c4c0

	jump_13c4c0:
		mov    data_1598c0,%al
		mov    data_1598d0,%ebx
		cmp    $0x8,%al
		ja     jump_13c510
		mov    %al,%cl
		mov    (%esi),%edx
		dec    %cl
		add    $0x2,%esi
		shl    %cl,%edx
		mov    data_15980c,%ecx
		or     %ebp,%edx
		mov    %edx,%ebp
		and    $0xff,%edx
		add    $0x10,%al
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13c55c
		jmp    jump_13c535
	jump_13c510:
		mov    %ebp,%edx
		mov    data_15980c,%ecx
		and    $0xff,%edx
		mov    (%ecx,%edx,4),%ecx
		shr    %cl,%ebp
		sub    %cl,%al
		shr    $0x8,%ecx
		add    data_1598a4,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		jne    jump_13c55c
	jump_13c535:
		shr    $0xd,%edx
		dec    %al
		jne    jump_13c543
		mov    (%esi),%ebp
		add    $0x4,%esi
		mov    $0x20,%al
	jump_13c543:
		and    $0xffff8,%edx
		shr    $0x1,%ebp
		jb     jump_13c553
		mov    $0x4,%edx
	jump_13c553:
		add    %edx,%ecx
		mov    (%ecx),%edx
		cmp    %dx,%bx
		je     jump_13c535
	jump_13c55c:
		mov    data_159844,%ecx
		ror    $0x10,%edx
		mov    %al,data_1598c0
		mov    %dx,%ax
		ror    $0x10,%edx
		cmp    %edx,(%ecx)
		je     jump_13c594
		mov    %eax,data_159878
		mov    (%ecx),%eax
		mov    data_159848,%ebx
		mov    %edx,(%ecx)
		mov    data_15984c,%ecx
		mov    (%ebx),%edx
		mov    %eax,(%ebx)
		mov    data_159878,%eax
		mov    %edx,(%ecx)
	jump_13c594:
		mov    %eax,%edx
		mov    %eax,%ecx
		and    $0xfc,%edx
		and    $0x3,%ecx
		mov    data_1598e0(%edx),%edx
		mov    %edx,data_159864
		jmp    *data_159850(,%ecx,4)
	jump_13c5c0:
		testl  $0x1,data_1598ac
		je     jump_13c5cf
		pop    %eax
		jmp    jump_13c5e0
	jump_13c5cf:
		mov    data_1599f0,%eax
		shr    $0x4,%eax
		add    data_1599f8,%eax
		movb   $0x0,(%eax)
	jump_13c5e0:
		pop    %edx
		pop    %esi
		pop    %edi
		pop    %ebx
		pop    %es
		pop    %ebp
		ret


/*----------------------------------------------------------------*/
GLOBAL_FUNC (SmackDoPCM)
/*----------------------------------------------------------------*/
		push   %ebp
		mov    %esp,%ebp
		push   %ebx
		push   %esi
		push   %edi
		push   %es
		cld
		mov    %ds,%ax
		mov    %eax,%es
		mov    0xc(%ebp),%eax
		mov    %eax,data_159e20
		mov    0x10(%ebp),%eax
		mov    %eax,data_159e24
		mov    0x14(%ebp),%eax
		mov    %eax,data_159e28
		mov    0x18(%ebp),%eax
		mov    %eax,data_159e2c
		mov    0x1c(%ebp),%eax
		mov    %eax,data_159e30
		movb   $0x1,data_1598c0
		mov    0x8(%ebp),%esi
		xor    %ebp,%ebp
		decb   data_1598c0
		jne    jump_13c645
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13c645:
		shr    $0x1,%ebp
		jae    jump_13ce12
		decb   data_1598c0
		jne    jump_13c662
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13c662:
		shr    $0x1,%ebp
		jb     jump_13c935
		decb   data_1598c0
		jne    jump_13c67f
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13c67f:
		shr    $0x1,%ebp
		jb     jump_13c780
		decb   data_1598c0
		jne    jump_13c69c
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13c69c:
		shr    $0x1,%ebp
		mov    data_159e24,%edi
		mov    %edi,data_15988c
		call   func_139100
		mov    data_159e20,%edx
		cmp    $0x0,%edx
		je     jump_13ce12
		mov    data_159e30,%edi
		add    %edi,%edx
		cmp    %edx,data_159e2c
		jae    jump_13c6db
		sub    data_159e2c,%edx
		add    data_159e28,%edx
	jump_13c6db:
		mov    %edx,data_1599fc
		cmpb   $0x9,data_1598c0
		jb     jump_13c6fa
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_13c720
	jump_13c6fa:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_13c720:
		mov    %al,%cl
		jmp    jump_13c761
	jump_13c724:
		mov    data_15988c,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		jne    jump_13c75c
	jump_13c733:
		decb   data_1598c0
		jne    jump_13c747
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13c747:
		shr    $0x1,%ebp
		jb     jump_13c751
		mov    $0x4,%eax
	jump_13c751:
		add    %eax,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		je     jump_13c733
	jump_13c75c:
		mov    %ax,%ax
		add    %al,%cl
	jump_13c761:
		mov    %cl,(%edi)
		inc    %edi
		cmp    %edi,data_1599fc
		je     jump_13ce12
		cmp    %edi,data_159e2c
		jne    jump_13c724
		mov    data_159e28,%edi
		jmp    jump_13c724
	jump_13c780:
		decb   data_1598c0
		jne    jump_13c794
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13c794:
		shr    $0x1,%ebp
		mov    data_159e24,%edi
		mov    %edi,data_15988c
		call   func_139100
		decb   data_1598c0
		jne    jump_13c7bc
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13c7bc:
		shr    $0x1,%ebp
		mov    data_159e24,%edi
		add    $0x800,%edi
		mov    %edi,data_159890
		call   func_139100
		mov    data_159e20,%edx
		cmp    $0x0,%edx
		je     jump_13ce12
		mov    data_159e30,%edi
		add    %edi,%edx
		cmp    %edx,data_159e2c
		jae    jump_13c801
		sub    data_159e2c,%edx
		add    data_159e28,%edx
	jump_13c801:
		mov    %edx,data_1599fc
		cmpb   $0x9,data_1598c0
		jb     jump_13c820
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_13c846
	jump_13c820:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_13c846:
		mov    %al,%ah
		cmpb   $0x9,data_1598c0
		jb     jump_13c861
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_13c887
	jump_13c861:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_13c887:
		mov    %ax,%cx
		jmp    jump_13c90c
	jump_13c88f:
		mov    data_15988c,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		jne    jump_13c8c7
	jump_13c89e:
		decb   data_1598c0
		jne    jump_13c8b2
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13c8b2:
		shr    $0x1,%ebp
		jb     jump_13c8bc
		mov    $0x4,%eax
	jump_13c8bc:
		add    %eax,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		je     jump_13c89e
	jump_13c8c7:
		mov    %ax,%ax
		add    %al,%cl
		adc    $0x0,%ch
		mov    data_159890,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		jne    jump_13c907
	jump_13c8de:
		decb   data_1598c0
		jne    jump_13c8f2
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13c8f2:
		shr    $0x1,%ebp
		jb     jump_13c8fc
		mov    $0x4,%eax
	jump_13c8fc:
		add    %eax,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		je     jump_13c8de
	jump_13c907:
		mov    %ax,%ax
		add    %al,%ch
	jump_13c90c:
		mov    %cx,(%edi)
		add    $0x2,%edi
		cmp    %edi,data_1599fc
		je     jump_13ce12
		cmp    %edi,data_159e2c
		jne    jump_13c88f
		mov    data_159e28,%edi
		jmp    jump_13c88f
	jump_13c935:
		decb   data_1598c0
		jne    jump_13c949
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13c949:
		shr    $0x1,%ebp
		jb     jump_13cb01
		decb   data_1598c0
		jne    jump_13c966
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13c966:
		shr    $0x1,%ebp
		mov    data_159e24,%edi
		mov    %edi,data_15988c
		call   func_139100
		decb   data_1598c0
		jne    jump_13c98e
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13c98e:
		shr    $0x1,%ebp
		mov    data_159e24,%edi
		add    $0x800,%edi
		mov    %edi,data_159890
		call   func_139100
		mov    data_159e20,%edx
		cmp    $0x0,%edx
		je     jump_13ce12
		mov    data_159e30,%edi
		add    %edi,%edx
		cmp    %edx,data_159e2c
		jae    jump_13c9d3
		sub    data_159e2c,%edx
		add    data_159e28,%edx
	jump_13c9d3:
		mov    %edx,data_1599fc
		cmpb   $0x9,data_1598c0
		jb     jump_13c9f2
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_13ca18
	jump_13c9f2:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_13ca18:
		mov    %al,%ah
		cmpb   $0x9,data_1598c0
		jb     jump_13ca33
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_13ca59
	jump_13ca33:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_13ca59:
		mov    %ax,%cx
		jmp    jump_13cad8
	jump_13ca5e:
		mov    data_15988c,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		jne    jump_13ca96
	jump_13ca6d:
		decb   data_1598c0
		jne    jump_13ca81
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13ca81:
		shr    $0x1,%ebp
		jb     jump_13ca8b
		mov    $0x4,%eax
	jump_13ca8b:
		add    %eax,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		je     jump_13ca6d
	jump_13ca96:
		mov    %ax,%ax
		add    %al,%cl
		mov    data_159890,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		jne    jump_13cad3
	jump_13caaa:
		decb   data_1598c0
		jne    jump_13cabe
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13cabe:
		shr    $0x1,%ebp
		jb     jump_13cac8
		mov    $0x4,%eax
	jump_13cac8:
		add    %eax,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		je     jump_13caaa
	jump_13cad3:
		mov    %ax,%ax
		add    %al,%ch
	jump_13cad8:
		mov    %cx,(%edi)
		add    $0x2,%edi
		cmp    %edi,data_1599fc
		je     jump_13ce12
		cmp    %edi,data_159e2c
		jne    jump_13ca5e
		mov    data_159e28,%edi
		jmp    jump_13ca5e
	jump_13cb01:
		decb   data_1598c0
		jne    jump_13cb15
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13cb15:
		shr    $0x1,%ebp
		mov    data_159e24,%edi
		mov    %edi,data_15988c
		call   func_139100
		decb   data_1598c0
		jne    jump_13cb3d
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13cb3d:
		shr    $0x1,%ebp
		mov    data_159e24,%edi
		add    $0x800,%edi
		mov    %edi,data_159890
		call   func_139100
		decb   data_1598c0
		jne    jump_13cb6b
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13cb6b:
		shr    $0x1,%ebp
		mov    data_159e24,%edi
		add    $0x1000,%edi
		mov    %edi,data_159894
		call   func_139100
		decb   data_1598c0
		jne    jump_13cb99
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13cb99:
		shr    $0x1,%ebp
		mov    data_159e24,%edi
		add    $0x1800,%edi
		mov    %edi,data_159898
		call   func_139100
		mov    data_159e20,%edx
		cmp    $0x0,%edx
		je     jump_13ce12
		mov    data_159e30,%edi
		add    %edi,%edx
		cmp    %edx,data_159e2c
		jae    jump_13cbde
		sub    data_159e2c,%edx
		add    data_159e28,%edx
	jump_13cbde:
		mov    %edx,data_1599fc
		cmpb   $0x9,data_1598c0
		jb     jump_13cbfd
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_13cc23
	jump_13cbfd:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_13cc23:
		mov    %al,%ah
		cmpb   $0x9,data_1598c0
		jb     jump_13cc3e
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_13cc64
	jump_13cc3e:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_13cc64:
		shl    $0x10,%eax
		cmpb   $0x9,data_1598c0
		jb     jump_13cc80
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_13cca6
	jump_13cc80:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_13cca6:
		mov    %al,%ah
		cmpb   $0x9,data_1598c0
		jb     jump_13ccc1
		mov    %ebp,%ebx
		subb   $0x8,data_1598c0
		shr    $0x8,%ebp
		mov    %bl,%al
		jmp    jump_13cce7
	jump_13ccc1:
		mov    data_1598c0,%cl
		mov    %ebp,%ebx
		addb   $0x18,data_1598c0
		mov    %bl,%al
		mov    (%esi),%ebx
		dec    %cl
		mov    %ebx,%ebp
		shl    %cl,%ebx
		sub    $0x9,%cl
		or     %bl,%al
		xor    $0xff,%cl
		add    $0x4,%esi
		shr    %cl,%ebp
	jump_13cce7:
		mov    %eax,%ecx
		jmp    jump_13cdee
	jump_13ccee:
		mov    data_15988c,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		jne    jump_13cd26
	jump_13ccfd:
		decb   data_1598c0
		jne    jump_13cd11
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13cd11:
		shr    $0x1,%ebp
		jb     jump_13cd1b
		mov    $0x4,%eax
	jump_13cd1b:
		add    %eax,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		je     jump_13ccfd
	jump_13cd26:
		mov    %ax,%ax
		add    %al,%cl
		adc    $0x0,%ch
		mov    data_159890,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		jne    jump_13cd66
	jump_13cd3d:
		decb   data_1598c0
		jne    jump_13cd51
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13cd51:
		shr    $0x1,%ebp
		jb     jump_13cd5b
		mov    $0x4,%eax
	jump_13cd5b:
		add    %eax,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		je     jump_13cd3d
	jump_13cd66:
		mov    %ax,%ax
		add    %al,%ch
		ror    $0x10,%ecx
		mov    data_159894,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		jne    jump_13cda6
	jump_13cd7d:
		decb   data_1598c0
		jne    jump_13cd91
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13cd91:
		shr    $0x1,%ebp
		jb     jump_13cd9b
		mov    $0x4,%eax
	jump_13cd9b:
		add    %eax,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		je     jump_13cd7d
	jump_13cda6:
		mov    %ax,%ax
		add    %al,%cl
		adc    $0x0,%ch
		mov    data_159898,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		jne    jump_13cde6
	jump_13cdbd:
		decb   data_1598c0
		jne    jump_13cdd1
		mov    (%esi),%ebp
		add    $0x4,%esi
		movb   $0x20,data_1598c0
	jump_13cdd1:
		shr    $0x1,%ebp
		jb     jump_13cddb
		mov    $0x4,%eax
	jump_13cddb:
		add    %eax,%edx
		mov    (%edx),%eax
		test   $0x80000000,%eax
		je     jump_13cdbd
	jump_13cde6:
		mov    %ax,%ax
		add    %al,%ch
		ror    $0x10,%ecx
	jump_13cdee:
		mov    %ecx,(%edi)
		add    $0x4,%edi
		cmp    %edi,data_1599fc
		je     jump_13ce12
		cmp    %edi,data_159e2c
		jne    jump_13ccee
		mov    data_159e28,%edi
		jmp    jump_13ccee
	jump_13ce12:
		pop    %es
		pop    %edi
		pop    %esi
		pop    %ebx
		pop    %ebp
		ret


/*----------------------------------------------------------------*/
GLOBAL_FUNC (SmackGetSizeDeltas)
/*----------------------------------------------------------------*/
		push   %ebp
		mov    %esp,%ebp
		push   %edx
		push   %ecx
		mov    0x8(%ebp),%eax
		mov    0xc(%ebp),%ecx
		mul    %ecx
		shr    $0x8,%eax
		add    $0x20,%eax
		pop    %ecx
		pop    %edx
		pop    %ebp
		ret


/*----------------------------------------------------------------*/
GLOBAL_FUNC (SmackRemapTables)
/*----------------------------------------------------------------*/
		push   %ebp
		mov    %esp,%ebp
		push   %edi
		push   %esi
		push   %ebx
		push   %edx
		push   %es
		cld
		mov    0xc(%ebp),%edi
		xor    %ebx,%ebx
		mov    0x8(%ebp),%esi
		lea    0x7410(%esi),%eax
		mov    (%eax),%cx
		add    $0x4,%eax
		mov    %cx,data_1598d0
		mov    (%edi),%cl
		mov    %cl,%ch
		mov    %cx,0x12(%eax)
		mov    %cx,0x22(%eax)
		mov    0x4(%esi),%ecx
		add    (%esi),%esi
		add    $0x7468,%esi
		shr    $0x2,%ecx
		jecxz  jump_13cfbb
	jump_13cfa0:
		lods   %ds:(%esi),%eax
		cmp    %ax,data_1598d0
		je     jump_13cfb8
		mov    %al,%bl
		mov    (%edi,%ebx,1),%al
		mov    %ah,%bl
		mov    (%edi,%ebx,1),%ah
		mov    %ax,-0x2(%esi)
	jump_13cfb8:
		dec    %ecx
		jne    jump_13cfa0
	jump_13cfbb:
		mov    0x8(%ebp),%esi
		mov    (%esi),%eax
		add    0x4(%esi),%eax
		mov    0x8(%esi),%ecx
		add    %eax,%esi
		add    $0x7468,%esi
		shr    $0x2,%ecx
		jecxz  jump_13cfee
	jump_13cfd3:
		lods   %ds:(%esi),%eax
		cmp    %ax,data_1598d0
		je     jump_13cfeb
		mov    %al,%bl
		mov    (%edi,%ebx,1),%al
		mov    %ah,%bl
		mov    (%edi,%ebx,1),%ah
		mov    %ax,-0x2(%esi)
	jump_13cfeb:
		dec    %ecx
		jne    jump_13cfd3
	jump_13cfee:
		mov    0x8(%ebp),%esi
		mov    (%esi),%eax
		add    0x4(%esi),%eax
		add    0x8(%esi),%eax
		mov    0xc(%esi),%ecx
		add    %eax,%esi
		add    $0x7468,%esi
		shr    $0x2,%ecx
		jecxz  jump_13d028
	jump_13d009:
		lods   %ds:(%esi),%eax
		mov    %eax,%edx
		cmp    %ax,data_1598d0
		je     jump_13d025
		and    $0x3,%edx
		cmp    $0x3,%edx
		jne    jump_13d025
		mov    %ah,%bl
		mov    (%edi,%ebx,1),%ah
		mov    %ah,-0x1(%esi)
	jump_13d025:
		dec    %ecx
		jne    jump_13d009
	jump_13d028:
		pop    %es
		pop    %edx
		pop    %ebx
		pop    %esi
		pop    %edi
		pop    %ebp
		ret


/*----------------------------------------------------------------*/
GLOBAL_FUNC (set_smack_malloc)
/*----------------------------------------------------------------*/
		mov    %eax,_smack_malloc
		ret


/*----------------------------------------------------------------*/
GLOBAL_FUNC (set_smack_free)
/*----------------------------------------------------------------*/
		mov    %eax,_smack_free
		ret


/*----------------------------------------------------------------*/
GLOBAL_FUNC (play_smk)
/*----------------------------------------------------------------*/
		push   %ecx
		xor    %cl,%cl
		mov    %cl,EXPORT_SYMBOL(lbDisplay__MLeftButton)
		mov    data_1e5a2c,%ecx
		test   %ecx,%ecx
		jne    jump_eb198
		test   $0x84,%bl
		je     jump_eb1a2
	jump_eb198:
		and    $0xfe,%bh
		call   play_smk_via_buffer
		pop    %ecx
		ret
	jump_eb1a2:
		mov    EXPORT_SYMBOL(lbDisplay__ScreenMode),%cx
		cmp    $0x1,%ecx
		je     jump_eb1b1
		and    $0xfe,%bh
	jump_eb1b1:
		call   play_smk_direct
		pop    %ecx
		ret


/*----------------------------------------------------------------*/
/* long play_smk_direct(char *, long , long)
 */
play_smk_direct:
/*----------------------------------------------------------------*/
		push   %ecx
		push   %esi
		push   %edi
		push   %ebp
		sub    $0x10,%esp
		mov    %eax,%esi
		mov    %ebx,0x4(%esp)
		mov    0x5(%esp),%ah
		mov    $0xffffffff,%ebp
		test   $0x2,%ah
		testb  $0x1,0x4(%esp)
		jne    jump_eb1f0
		call   GetSoundDriver_
		test   %eax,%eax
		je     jump_eb1f0
		call   GetSoundDriver_
		push   %eax
		push   $0x0
		call   SMACKSOUNDUSEMSS
		jmp    jump_eb1f5
	jump_eb1f0:
		orb    $0x1,0x4(%esp)
	jump_eb1f5:
		testb  $0x1,0x4(%esp)
		jne    jump_eb203
		mov    $0xfe000,%eax
		jmp    jump_eb205
	jump_eb203:
		xor    %eax,%eax
	jump_eb205:
		push   %esi
		push   %eax
		push   %ebp
		call   SMACKOPEN
		mov    %eax,%ebp
		test   %eax,%eax
		je     jump_eb37e
		testb  $0x1,0x5(%esp)
		je     jump_eb24a
		mov    $0x140,%esi
		mov    $0xc8,%edx
		mov    0x4(%eax),%ebx
		push   %eax
		sub    %ebx,%esi
		mov    0x8(%eax),%ecx
		shr    %esi
		sub    %ecx,%edx
		push   %esi
		shr    %edx
		push   %edx
		push   $0x140
		push   $0xc8
		push   $0xa0000
		jmp    jump_eb279
	jump_eb24a:
		mov    EXPORT_SYMBOL(lbDisplay__GraphicsScreenWidth),%esi
		sub    0x4(%eax),%esi
		shr    %esi
		mov    EXPORT_SYMBOL(lbDisplay__GraphicsScreenHeight),%edx
		mov    0x8(%eax),%ecx
		push   %eax
		sub    %ecx,%edx
		push   %esi
		shr    %edx
		push   %edx
		mov    EXPORT_SYMBOL(lbDisplay__GraphicsScreenWidth),%esi
		push   %esi
		mov    EXPORT_SYMBOL(lbDisplay__GraphicsScreenHeight),%edi
		push   %edi
		mov    EXPORT_SYMBOL(lbDisplay__WScreen),%eax
		push   %eax
	jump_eb279:
		push   $0x0
		call   SMACKTOBUFFER
		xor    %esi,%esi
		lea    0x6c(%ebp),%eax
		mov    %esi,0x8(%esp)
		mov    %eax,(%esp)
		jmp    jump_eb292
	jump_eb28e:
		incl   0x8(%esp)
	jump_eb292:
		testb  $0x4,0x5(%esp)
		jne    jump_eb2a6
		mov    0x8(%esp),%eax
		cmp    0xc(%ebp),%eax
		jae    jump_eb373
	jump_eb2a6:
		testb  $0x1,0x5(%esp)
		je     jump_eb2e1
		mov    (%esp),%edx
		test   %edx,%edx
		je     jump_eb2d9
		mov    $0x300,%ecx
		mov    $data_1e56dc,%edi
		mov    %edx,%esi
		push   %edi
		mov    %ecx,%eax
		shr    $0x2,%ecx
		repnz movsl %ds:(%esi),%es:(%edi)
		mov    %al,%cl
		and    $0x3,%cl
		repnz movsb %ds:(%esi),%es:(%edi)
		pop    %edi
		push   %edi
		call   ac_LbPaletteSet
		add    $0x4,%esp
	jump_eb2d9:
		push   %ebp
		call   SMACKDOFRAME
		jmp    jump_eb334
	jump_eb2e1:
		xor    %al,%al
		mov    %al,0xc(%esp)
		cmpl   $0x0,(%esp)
		je     jump_eb310
		mov    $0x1,%ah
		mov    $0x300,%ecx
		mov    (%esp),%esi
		mov    $data_1e56dc,%edi
		mov    %ah,0xc(%esp)
		push   %edi
		mov    %ecx,%eax
		shr    $0x2,%ecx
		repnz movsl %ds:(%esi),%es:(%edi)
		mov    %al,%cl
		and    $0x3,%cl
		repnz movsb %ds:(%esi),%es:(%edi)
		pop    %edi
	jump_eb310:
		push   %ebp
		call   SMACKDOFRAME
		cmpb   $0x0,0xc(%esp)
		je     jump_eb32f
		/* call   ac_game_wait_for_vsync XXX: not needed */
		push   $data_1e56dc
		call   ac_LbPaletteSet
		add    $0x4,%esp
	jump_eb32f:
		call   LbScreenSwap_
	jump_eb334:
		push   %ebp
		call   SMACKNEXTFRAME
	jump_eb33a:
		push   %ebp
		call   SMACKWAIT
		test   %eax,%eax
		je     jump_eb28e
		testb  $0x2,0x4(%esp)
		jne    jump_eb33a
		/* XXX: intro loop */
		call   ac_game_handle_sdl_events
		call   ac_game_wait_for_vsync
		cmpb   $0x0,EXPORT_SYMBOL(lbKeyOn)+1
		jne    jump_eb373
		cmpb   $0x0,EXPORT_SYMBOL(lbKeyOn)+28
		jne    jump_eb373
		cmpb   $0x0,EXPORT_SYMBOL(lbKeyOn)+57
		jne    jump_eb373
		cmpb   $0x0,EXPORT_SYMBOL(lbDisplay__MLeftButton)
		je     jump_eb33a
	jump_eb373:
		push   %ebp
		call   SMACKCLOSE
		mov    $0x1,%eax
	jump_eb37e:
		add    $0x10,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		pop    %ecx
		ret


/*----------------------------------------------------------------*/
/* long play_smk_via_buffer(char *, long , long)
 */
play_smk_via_buffer:
/*----------------------------------------------------------------*/
		push   %ecx
		push   %esi
		push   %edi
		push   %ebp
		sub    $0x10,%esp
		mov    %eax,%ebp
		mov    %ebx,0xc(%esp)
		mov    0xd(%esp),%ah
		mov    $0xffffffff,%esi
		test   $0x2,%ah
		testb  $0x1,0xc(%esp)
		jne    jump_eb3c0
		call   GetSoundDriver_
		test   %eax,%eax
		je     jump_eb3c0
		call   GetSoundDriver_
		push   %eax
		push   $0x0
		call   SMACKSOUNDUSEMSS
		jmp    jump_eb3c5
	jump_eb3c0:
		orb    $0x1,0xc(%esp)
	jump_eb3c5:
		testb  $0x1,0xc(%esp)
		jne    jump_eb3d3
		mov    $0xfe000,%eax
		jmp    jump_eb3d5
	jump_eb3d3:
		xor    %eax,%eax
	jump_eb3d5:
		push   %ebp
		push   %eax
		push   %esi
		call   SMACKOPEN
		mov    %eax,%esi
		mov    %eax,%ebp
		test   %eax,%eax
		je     jump_eb4e2
		mov    0x4(%eax),%eax
		imul   0x8(%esi),%eax
		call   ac_LbMemoryAlloc
		mov    %eax,0x4(%esp)
		test   %eax,%eax
		jne    jump_eb40a
		push   %esi
		call   SMACKCLOSE
		xor    %eax,%eax
		jmp    jump_eb4e2
	jump_eb40a:
		push   %esi
		push   $0x0
		push   $0x0
		mov    0x4(%esi),%ebx
		push   %ebx
		mov    0x8(%esi),%ecx
		push   %ecx
		xor    %edi,%edi
		push   %eax
		mov    %edi,0x18(%esp)
		add    $0x6c,%esi
		push   $0x0
		mov    $data_1e56dc,%edi
		mov    %esi,0x24(%esp)
		call   SMACKTOBUFFER
		jmp    jump_eb436
	jump_eb433:
		incl   (%esp)
	jump_eb436:
		testb  $0x4,0xd(%esp)
		jne    jump_eb449
		mov    (%esp),%eax
		cmp    0xc(%ebp),%eax
		jae    jump_eb4ce
	jump_eb449:
		mov    0x8(%esp),%ebx
		test   %ebx,%ebx
		je     jump_eb468
		mov    $0x300,%ecx
		mov    %ebx,%esi
		push   %edi
		mov    %ecx,%eax
		shr    $0x2,%ecx
		repnz movsl %ds:(%esi),%es:(%edi)
		mov    %al,%cl
		and    $0x3,%cl
		repnz movsb %ds:(%esi),%es:(%edi)
		pop    %edi
	jump_eb468:
		push   %ebp
		call   SMACKDOFRAME
		call   ac_game_wait_for_vsync
		push   $data_1e56dc
		call   ac_LbPaletteSet
		add    $0x4,%esp
		mov    0x8(%ebp),%ebx
		mov    0x4(%ebp),%edx
		mov    0xc(%esp),%ecx
		mov    0x4(%esp),%eax
		call   copy_to_screen
		push   %ebp
		call   SMACKNEXTFRAME
	jump_eb499:
		push   %ebp
		call   SMACKWAIT
		test   %eax,%eax
		je     jump_eb433
		testb  $0x2,0xc(%esp)
		jne    jump_eb499
		cmpb   $0x0,EXPORT_SYMBOL(lbKeyOn)+1
		jne    jump_eb4ce
		cmpb   $0x0,EXPORT_SYMBOL(lbKeyOn)+28
		jne    jump_eb4ce
		cmpb   $0x0,EXPORT_SYMBOL(lbKeyOn)+57
		jne    jump_eb4ce
		cmpb   $0x0,EXPORT_SYMBOL(lbDisplay__MLeftButton)
		je     jump_eb499
	jump_eb4ce:
		push   %ebp
		call   SMACKCLOSE
		mov    0x4(%esp),%eax
		call   LbMemoryFree_
		mov    $0x1,%eax
	jump_eb4e2:
		add    $0x10,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		pop    %ecx
		ret


/*----------------------------------------------------------------*/
SMACKSOUNDUSEMSS:
/*----------------------------------------------------------------*/
		push   %esi
		push   %edi
		push   %ebp
		mov    0x10(%esp),%ebx
		cmpl   $0x0,_SmackTimerReadAddr
		jne    jump_fbcd7
		mov    0x14(%esp),%eax
		mov    %eax,EXPORT_SYMBOL(SmackMSSDigDriver)
		cmp    $0xc8,%ebx
		ja     jump_fbc4a
		mov    $0xc8,%ebx
	jump_fbc4a:
		mov    $0x1234dd,%eax
		xor    %edx,%edx
		div    %ebx
		mov    $MSSLOWSOUNDOPEN,%ecx
		mov    $MSSLOWSOUNDCLOSE,%esi
		mov    $MSSLOWSOUNDPLAYED,%edi
		mov    $MSSLOWSOUNDPURGE,%ebp
		mov    %ebx,EXPORT_SYMBOL(_LowUnk_1e86c0)
		mov    %ecx,_LowSoundOpenAddr
		mov    %esi,EXPORT_SYMBOL(_LowSoundCloseAddr)
		mov    %edi,EXPORT_SYMBOL(_LowSoundPlayedAddr)
		mov    %ebp,EXPORT_SYMBOL(_LowSoundPurgeAddr)
		mov    %ebp,_LowSoundOffAddr
		mov    $MSSSMACKTIMERDONE,%ecx
		mov    $ac_MSSSMACKTIMERREAD,%esi
		mov    $MSSSMACKTIMERSETUP,%edi
		mov    %ecx,_SmackTimerSetupAddr
		mov    %esi,_SmackTimerReadAddr
		mov    %edi,_SmackTimerDoneAddr
		mov    $MSSLOWSOUNDCHECK,%ebx
		mov    %eax,EXPORT_SYMBOL(_LowSoundVolPanAddr)
		xor    %edx,%edx
		mov    $0x1,%al
		mov    %ebx,EXPORT_SYMBOL(_LowSoundCheckAddr)
		mov    $MSSLOWSOUNDVOLPAN,%ebx
		mov    %edx,data_1592f8
		mov    %ebx,data_1592fc
		pop    %ebp
		pop    %edi
		pop    %esi
		ret    $0x8
	jump_fbcd7:
		xor    %al,%al
		pop    %ebp
		pop    %edi
		pop    %esi
		ret    $0x8


/*----------------------------------------------------------------*/
GLOBAL_FUNC (RADMALLOC)
/*----------------------------------------------------------------*/
		mov    0x4(%esp),%eax
		test   %eax,%eax
		je     jump_eb504
		cmp    $0xffffffff,%eax
		je     jump_eb502
		call   *_smack_malloc
		ret    $0x4
	jump_eb502:
		xor    %eax,%eax
	jump_eb504:
		ret    $0x4


/*----------------------------------------------------------------*/
GLOBAL_FUNC (RADFREE)
/*----------------------------------------------------------------*/
		mov    0x4(%esp),%eax
		call   *_smack_free
		ret    $0x4


/*----------------------------------------------------------------*/
/* void copy_to_screen(unsigned char *, unsigned long, unsigned long, unsigned long)
 */
copy_to_screen:
/*----------------------------------------------------------------*/
		push   %esi
		push   %edi
		push   %ebp
		sub    $0x20,%esp
		mov    %eax,0x1c(%esp)
		mov    %edx,0x18(%esp)
		mov    %ebx,0x14(%esp)
		xor    %eax,%eax
		mov    EXPORT_SYMBOL(lbDisplay__ScreenMode),%ax
		cmp    $0x1,%eax
		jne    jump_eb555
		cmpl   $0x0,data_1e5a2c
		jne    jump_eb555
		mov    $0xa0000,%ebp
		mov    $0x140,%ebx
		mov    $0xc8,%edx
		mov    %ebx,0x10(%esp)
		jmp    jump_eb56a
	jump_eb555:
		mov    EXPORT_SYMBOL(lbDisplay__WScreen),%ebp
		mov    EXPORT_SYMBOL(lbDisplay__GraphicsScreenWidth),%eax
		mov    EXPORT_SYMBOL(lbDisplay__GraphicsScreenHeight),%edx
		mov    %eax,0x10(%esp)
	jump_eb56a:
		test   $0x4,%cl
		je     jump_eb582
		mov    0x14(%esp),%eax
		add    %eax,%eax
		sub    %eax,%edx
		mov    0x10(%esp),%eax
		shr    %edx
		imul   %eax,%edx
		jmp    jump_eb58f
	jump_eb582:
		sub    0x14(%esp),%edx
		mov    0x10(%esp),%edi
		shr    %edx
		imul   %edi,%edx
	jump_eb58f:
		add    %edx,%ebp
		test   $0x80,%cl
		je     jump_eb5a6
		mov    0x18(%esp),%eax
		mov    0x10(%esp),%edx
		add    %eax,%eax
		sub    %eax,%edx
		mov    %edx,%eax
		jmp    jump_eb5ae
	jump_eb5a6:
		mov    0x10(%esp),%eax
		sub    0x18(%esp),%eax
	jump_eb5ae:
		shr    %eax
		add    %eax,%ebp
		test   $0x4,%cl
		je     jump_eb6a0
		mov    0x10(%esp),%eax
		add    %eax,%eax
		test   $0x80,%cl
		je     jump_eb64a
		xor    %edx,%edx
		mov    0x14(%esp),%ebx
		mov    %edx,0xc(%esp)
		test   %ebx,%ebx
		jbe    jump_eb75b
		mov    %eax,(%esp)
	jump_eb5df:
		mov    0x10(%esp),%ebx
		mov    0x18(%esp),%ecx
		mov    0x1c(%esp),%esi
		mov    %ebp,%edi
		shr    $0x2,%ecx
	jump_eb5f0:
		mov    (%esi),%edx
		mov    %dh,%al
		mov    %dh,%ah
		shl    $0x10,%eax
		mov    %dl,%al
		mov    %dl,%ah
		mov    %eax,(%edi)
		mov    %eax,(%edi,%ebx,1)
		shr    $0x10,%edx
		mov    %dh,%al
		mov    %dh,%ah
		shl    $0x10,%eax
		mov    %dl,%al
		mov    %dl,%ah
		mov    %eax,0x4(%edi)
		mov    %eax,0x4(%edi,%ebx,1)
		add    $0x4,%esi
		add    $0x8,%edi
		dec    %ecx
		jne    jump_eb5f0
		mov    (%esp),%edx
		mov    0x18(%esp),%eax
		mov    0x1c(%esp),%ebx
		mov    0xc(%esp),%ecx
		mov    0x14(%esp),%esi
		inc    %ecx
		add    %eax,%ebx
		add    %edx,%ebp
		mov    %ebx,0x1c(%esp)
		mov    %ecx,0xc(%esp)
		cmp    %esi,%ecx
		jae    jump_eb75b
		jmp    jump_eb5df
	jump_eb64a:
		mov    0x14(%esp),%edi
		xor    %edx,%edx
		test   %edi,%edi
		jbe    jump_eb75b
		mov    %eax,0x4(%esp)
	jump_eb65c:
		mov    0x10(%esp),%ebx
		mov    0x18(%esp),%ecx
		mov    0x1c(%esp),%esi
		mov    %ebp,%edi
		shr    $0x2,%ecx
	jump_eb66d:
		mov    (%esi),%eax
		mov    %eax,(%edi)
		mov    %eax,(%edi,%ebx,1)
		add    $0x4,%esi
		add    $0x4,%edi
		dec    %ecx
		jne    jump_eb66d
		inc    %edx
		mov    0x4(%esp),%esi
		mov    0x18(%esp),%eax
		mov    0x1c(%esp),%edi
		add    %esi,%ebp
		add    %eax,%edi
		mov    0x14(%esp),%eax
		mov    %edi,0x1c(%esp)
		cmp    %eax,%edx
		jae    jump_eb75b
		jmp    jump_eb65c
	jump_eb6a0:
		test   $0x80,%cl
		je     jump_eb71a
		xor    %ecx,%ecx
		mov    0x14(%esp),%esi
		mov    %ecx,0x8(%esp)
		test   %esi,%esi
		jbe    jump_eb75b
	jump_eb6b7:
		mov    0x18(%esp),%eax
		mov    0x1c(%esp),%esi
		mov    %ebp,%edi
		push   %ebp
		shr    $0x2,%eax
		mov    %eax,%ebp
	jump_eb6c7:
		mov    (%esi),%edx
		mov    %edx,%ecx
		shr    $0x10,%ecx
		mov    %dh,%al
		mov    %ch,%bl
		mov    %dh,%ah
		mov    %ch,%bh
		shl    $0x10,%eax
		shl    $0x10,%ebx
		mov    %dl,%al
		mov    %cl,%bl
		mov    %dl,%ah
		mov    %cl,%bh
		mov    %eax,(%edi)
		mov    %ebx,0x4(%edi)
		add    $0x4,%esi
		add    $0x8,%edi
		dec    %ebp
		jne    jump_eb6c7
		pop    %ebp
		mov    0x10(%esp),%eax
		mov    0x1c(%esp),%edx
		mov    0x8(%esp),%ebx
		mov    0x14(%esp),%ecx
		add    %eax,%ebp
		mov    0x18(%esp),%eax
		inc    %ebx
		add    %eax,%edx
		mov    %ebx,0x8(%esp)
		mov    %edx,0x1c(%esp)
		cmp    %ecx,%ebx
		jae    jump_eb75b
		jmp    jump_eb6b7
	jump_eb71a:
		mov    0x14(%esp),%ebx
		xor    %edx,%edx
		test   %ebx,%ebx
		jbe    jump_eb75b
	jump_eb724:
		mov    0x18(%esp),%ecx
		mov    0x1c(%esp),%esi
		mov    %ebp,%edi
		push   %edi
		mov    %ecx,%eax
		shr    $0x2,%ecx
		repnz movsl %ds:(%esi),%es:(%edi)
		mov    %al,%cl
		and    $0x3,%cl
		repnz movsb %ds:(%esi),%es:(%edi)
		pop    %edi
		inc    %edx
		mov    0x10(%esp),%ecx
		mov    0x18(%esp),%eax
		mov    0x1c(%esp),%esi
		mov    0x14(%esp),%edi
		add    %eax,%esi
		add    %ecx,%ebp
		mov    %esi,0x1c(%esp)
		cmp    %edi,%edx
		jb     jump_eb724
	jump_eb75b:
		xor    %eax,%eax
		mov    EXPORT_SYMBOL(lbDisplay__ScreenMode),%ax
		cmp    $0x1,%eax
		jne    jump_eb772
		mov    data_1e5a2c,%edi
		test   %edi,%edi
		je     jump_eb79d
	jump_eb772:
		cmpl   $0x0,data_1e5a2c
		je     jump_eb796
		mov    EXPORT_SYMBOL(lbDisplay__GraphicsScreenHeight),%edx
		push   %edx
		mov    EXPORT_SYMBOL(lbDisplay__GraphicsScreenWidth),%ebx
		push   %ebx
		mov    EXPORT_SYMBOL(lbDisplay__WScreen),%ecx
		push   %ecx
		call   *data_1e5a2c
	jump_eb796:
		call   LbScreenSwap_
		jmp    jump_eb7b4
	jump_eb79d:
		je     jump_eb7b4
		push   $0xc8
		push   $0x140
		push   $0xa0000
		call   *data_1e5a2c
	jump_eb7b4:
		add    $0x20,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		ret


/*----------------------------------------------------------------*/
GLOBAL_FUNC (SMACKWRAPCOPY)
/*----------------------------------------------------------------*/
		push   %esi
		push   %edi
		push   %ebp
		mov    0x1c(%esp),%edx
		mov    0x14(%esp),%ebp
		mov    0x10(%esp),%ebx
		sub    %edx,%ebp
		cmp    %ebx,%ebp
		ja     jump_fc388
		test   %ebp,%ebp
		je     jump_fc384
		mov    0x20(%esp),%edi
		mov    %ebp,%ecx
		mov    %edx,%esi
		cld
		mov    %cl,%bl
		shr    $0x2,%ecx
		rep movsl %ds:(%esi),%es:(%edi)
		mov    %bl,%cl
		and    $0x3,%cl
		rep movsb %ds:(%esi),%es:(%edi)
		mov    0x20(%esp),%ecx
		mov    0x10(%esp),%esi
		add    %ebp,%ecx
		sub    %ebp,%esi
		mov    %ecx,0x20(%esp)
		mov    %esi,0x10(%esp)
	jump_fc384:
		mov    0x18(%esp),%edx
	jump_fc388:
		mov    0x10(%esp),%edi
		test   %edi,%edi
		je     jump_fc3ad
		mov    %edi,%ecx
		mov    %edx,%esi
		mov    0x20(%esp),%edi
		mov    0x10(%esp),%ebp
		cld
		mov    %cl,%bl
		shr    $0x2,%ecx
		rep movsl %ds:(%esi),%es:(%edi)
		mov    %bl,%cl
		and    $0x3,%cl
		rep movsb %ds:(%esi),%es:(%edi)
		add    %ebp,%edx
	jump_fc3ad:
		mov    %edx,%eax
		pop    %ebp
		pop    %edi
		pop    %esi
		ret    $0x14


/*----------------------------------------------------------------*/
SMACKWAIT: /* 0xfc3c0 */
/*----------------------------------------------------------------*/
		push   %esi
		push   %edi
		mov    0xc(%esp),%esi
		test   %esi,%esi
		jne    jump_fc3d1
		xor    %eax,%eax
		pop    %edi
		pop    %esi
		ret    $0x4
	jump_fc3d1:
		cmpl   $0x0,_sounds
		je     jump_fc3e0
		call   *EXPORT_SYMBOL(_LowSoundCheckAddr)
	jump_fc3e0:
		mov    0x420(%esi),%ebx
		cmp    $0xffffffff,%ebx
		je     jump_fc440
		cmpl   $0x0,0x424(%esi)
		je     jump_fc3fd
		cmpl   $0x0,0x428(%esi)
		je     jump_fc404
	jump_fc3fd:
		xor    %eax,%eax
		pop    %edi
		pop    %esi
		ret    $0x4
	jump_fc404:
		mov    %ebx,%eax
		mov    0x404(%esi,%eax,4),%ebx
		push   %ebx
		call   *EXPORT_SYMBOL(_LowSoundPlayedAddr)
		mov    0x420(%esi),%edx
		mov    0x404(%esi,%edx,4),%edx
		mov    0x20(%edx),%edx
		shr    $0x7,%edx
		cmp    %edx,%eax
		jb     jump_fc4c3
		movl   $0x0,0x424(%esi)
		xor    %eax,%eax
		pop    %edi
		pop    %esi
		ret    $0x4
	jump_fc440:
		cmpl   $0x0,0x3f8(%esi)
		je     jump_fc450
		xor    %eax,%eax
		pop    %edi
		pop    %esi
		ret    $0x4
	jump_fc450:
		call   *_SmackTimerReadAddr
		mov    %eax,%edx
		shl    $0x2,%eax
		sub    %edx,%eax
		shl    $0x3,%eax
		add    %edx,%eax
		mov    0x3fc(%esi),%edi
		shl    $0x2,%eax
		cmp    $0xffffffff,%edi
		jne    jump_fc480
		mov    0x400(%esi),%edx
		add    %edx,%eax
		mov    %eax,0x3fc(%esi)
		jmp    jump_fc4c3
	jump_fc480:
		cmp    %edi,%eax
		jb     jump_fc4c3
		mov    0x400(%esi),%edx
		lea    (%edi,%edx,1),%ebx
		mov    %eax,%edx
		mov    0x400(%esi),%edi
		sub    %ebx,%edx
		mov    %ebx,0x3fc(%esi)
		cmp    %edi,%edx
		jbe    jump_fc4a9
		add    %edi,%eax
		mov    %eax,0x3fc(%esi)
	jump_fc4a9:
		cmpl   $0x0,0x400(%esi)
		je     jump_fc4bc
		movl   $0x1,0x3f8(%esi)
	jump_fc4bc:
		xor    %eax,%eax
		pop    %edi
		pop    %esi
		ret    $0x4
	jump_fc4c3:
		mov    %esi,%eax
		call   backgroundload_
		mov    $0x1,%eax
		pop    %edi
		pop    %esi
		ret    $0x4

vtable_fc970:
		.long   func_fca99
		.long   func_fcbf3
		.long   func_fcae0
		.long   func_fcbf3
		.long   func_fcb42
		.long   func_fcbf3
		.long   func_fcb92
	jump_fca15:
		mov    0x108(%esp),%ecx
		mov    0x108(%esp),%ebp
		mov    $0xffffffff,%edx
		mov    0x104(%esp),%ebx
		inc    %ebp
		mov    %edx,0x114(%esp)
		mov    (%ecx),%cl
		mov    %ebp,0x108(%esp)
		lea    0x1(%ebp),%eax
		mov    0x138(%esp),%edx
		mov    %eax,0x108(%esp)
		mov    (%eax),%al
		mov    0x0(%ebp),%ch
		mov    %al,0x120(%esp)
		mov    0x108(%esp),%eax
		xor    %ebp,%ebp
		inc    %eax
		mov    %ebp,0x118(%esp)
		mov    %eax,0x108(%esp)
		test   %edx,%edx
		jbe    jump_fcca5
	jump_fca7d:
		cmpl   $0x6,0x110(%esp)
		ja     func_fcbf3
		mov    0x10c(%esp),%eax
		jmp    *%cs:vtable_fc970(%eax)


/*----------------------------------------------------------------*/
func_fca99:
/*----------------------------------------------------------------*/
		mov    %ebx,%ebp
		imul   %edi,%ebp
		xor    %edx,%edx
		xor    %eax,%eax
		mov    %cl,%dl
		mov    (%esi,%ebp,1),%al
		sub    %eax,%edx
		mov    %edx,%eax
		mul    %eax
		mov    %eax,0x100(%esp)
		xor    %edx,%edx
		xor    %eax,%eax
		mov    %ch,%dl
		mov    0x1(%esi,%ebp,1),%al
		sub    %eax,%edx
		mov    %edx,%eax
		mul    %eax
		mov    0x100(%esp),%edx
		add    %eax,%edx
		xor    %eax,%eax
		mov    0x2(%esi,%ebp,1),%al
		movzbl 0x120(%esp),%ebp
		jmp    jump_fcc4b


/*----------------------------------------------------------------*/
func_fcae0:
/*----------------------------------------------------------------*/
		mov    %ebx,%ebp
		imul   %edi,%ebp
		xor    %eax,%eax
		xor    %edx,%edx
		mov    (%esi,%ebp,1),%al
		mov    %cl,%dl
		sar    $0x2,%eax
		sub    %eax,%edx
		mov    %edx,%eax
		mul    %eax
		mov    %eax,0x100(%esp)
		xor    %eax,%eax
		xor    %edx,%edx
		mov    0x1(%esi,%ebp,1),%al
		mov    %ch,%dl
		sar    $0x2,%eax
		sub    %eax,%edx
		mov    %edx,%eax
		mul    %eax
		mov    0x100(%esp),%edx
		movzbl 0x2(%esi,%ebp,1),%ebp
		add    %eax,%edx
		xor    %eax,%eax
		sar    $0x2,%ebp
		mov    0x120(%esp),%al
		sub    %ebp,%eax
		mov    %edx,0x100(%esp)
		mul    %eax
		add    0x100(%esp),%eax
		jmp    jump_fcc61


/*----------------------------------------------------------------*/
func_fcb42:
/*----------------------------------------------------------------*/
		mov    %ebx,%ebp
		imul   %edi,%ebp
		xor    %edx,%edx
		xor    %eax,%eax
		mov    %cl,%dl
		mov    0x2(%esi,%ebp,1),%al
		sub    %eax,%edx
		mov    %edx,%eax
		mul    %eax
		mov    %eax,0x100(%esp)
		xor    %edx,%edx
		xor    %eax,%eax
		mov    %ch,%dl
		mov    0x1(%esi,%ebp,1),%al
		sub    %eax,%edx
		mov    %edx,%eax
		mul    %eax
		mov    0x100(%esp),%edx
		add    %eax,%edx
		xor    %eax,%eax
		movzbl (%esi,%ebp,1),%ebp
		mov    0x120(%esp),%al
		mov    %edx,0x100(%esp)
		sub    %ebp,%eax
		jmp    jump_fcc56


/*----------------------------------------------------------------*/
func_fcb92:
/*----------------------------------------------------------------*/
		mov    %ebx,%ebp
		imul   %edi,%ebp
		xor    %eax,%eax
		xor    %edx,%edx
		mov    0x2(%esi,%ebp,1),%al
		mov    %cl,%dl
		sar    $0x2,%eax
		sub    %eax,%edx
		mov    %edx,%eax
		mul    %eax
		mov    %eax,0x100(%esp)
		xor    %eax,%eax
		xor    %edx,%edx
		mov    0x1(%esi,%ebp,1),%al
		mov    %ch,%dl
		sar    $0x2,%eax
		sub    %eax,%edx
		mov    %edx,%eax
		mul    %eax
		mov    0x100(%esp),%edx
		add    %eax,%edx
		xor    %eax,%eax
		mov    (%esi,%ebp,1),%al
		movzbl 0x120(%esp),%ebp
		sar    $0x2,%eax
		sub    %eax,%ebp
		mov    %ebp,%eax
		mov    %edx,0x100(%esp)
		mul    %eax
		add    0x100(%esp),%eax
		jmp    jump_fcc61


/*----------------------------------------------------------------*/
func_fcbf3:
/*----------------------------------------------------------------*/
		mov    %ebx,%ebp
		imul   %edi,%ebp
		xor    %eax,%eax
		mov    0x2(%esi,%ebp,1),%al
		sar    $0x2,%eax
		mov    %eax,0x100(%esp)
		xor    %eax,%eax
		mov    0x100(%esp),%edx
		mov    %cl,%al
		sub    %edx,%eax
		mul    %eax
		mov    %eax,0x100(%esp)
		xor    %eax,%eax
		xor    %edx,%edx
		mov    0x4(%esi,%ebp,1),%al
		mov    %ch,%dl
		sar    $0x2,%eax
		sub    %eax,%edx
		mov    %edx,%eax
		mul    %eax
		mov    0x100(%esp),%edx
		add    %eax,%edx
		xor    %eax,%eax
		mov    0x6(%esi,%ebp,1),%al
		movzbl 0x120(%esp),%ebp
		sar    $0x2,%eax
	jump_fcc4b:
		sub    %eax,%ebp
		mov    %edx,0x100(%esp)
		mov    %ebp,%eax
	jump_fcc56:
		mov    0x100(%esp),%ebp
		mul    %eax
		add    %ebp,%eax
	jump_fcc61:
		cmp    0x114(%esp),%eax
		jae    jump_fcc7c
		mov    %bl,0x11c(%esp)
		mov    %eax,0x114(%esp)
		test   %eax,%eax
		je     jump_fcca5
	jump_fcc7c:
		inc    %ebx
		cmp    $0x100,%ebx
		jne    jump_fcc87
		xor    %ebx,%ebx
	jump_fcc87:
		mov    0x118(%esp),%ebp
		inc    %ebp
		mov    0x138(%esp),%edx
		mov    %ebp,0x118(%esp)
		cmp    %edx,%ebp
		jb     jump_fca7d
	jump_fcca5:
		mov    0x104(%esp),%edx
		mov    0x11c(%esp),%al
		mov    %al,(%esp,%edx,1)
		lea    0x1(%edx),%eax
		mov    %eax,0x104(%esp)
		cmp    $0x100,%eax
		jb     jump_fca15
		mov    %esp,%eax
		push   %eax
		mov    0x144(%esp),%eax
		mov    0x39c(%eax),%ebx
		push   %ebx
		call   SmackRemapTables
		add    $0x8,%esp
		add    $0x124,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		ret    $0x10


/*----------------------------------------------------------------*/
SMACKTOBUFFER:
/*----------------------------------------------------------------*/
		push   %esi
		push   %edi
		push   %ebp
		sub    $0x10,%esp
		mov    0x38(%esp),%esi
		test   %esi,%esi
		je     jump_fcf27
		cmpl   $0x0,0x24(%esp)
		jne    jump_fcd60
		mov    0x3a0(%esi),%ecx
		test   %ecx,%ecx
		je     jump_fcf27
		push   %ecx
		call   RADFREE
		mov    0x3a4(%esi),%eax
		mov    0x45c(%esi),%ebp
		movl   $0x0,0x3a0(%esi)
		sub    %eax,%ebp
		mov    %ebp,0x45c(%esi)
		jmp    jump_fcf27
	jump_fcd60:
		mov    $0x3,%ebx
		mov    0x2c(%esp),%ebp
		mov    0x8(%esi),%eax
		mov    0x386(%esi),%dl
		mov    %ebx,0x8(%esp)
		mov    %eax,0xc(%esp)
		shr    %eax
		test   $0x10,%dl
		je     jump_fcd89
		mov    %eax,0xc(%esp)
		add    %ebp,%ebp
		jmp    jump_fcd9b
	jump_fcd89:
		test   $0x20,%dl
		je     jump_fcd9b
		mov    $0x7,%ecx
		mov    %eax,0xc(%esp)
		mov    %ecx,0x8(%esp)
	jump_fcd9b:
		mov    0x3a0(%esi),%edi
		test   %edi,%edi
		je     jump_fcdc4
		mov    (%edi),%bl
		mov    %edi,%eax
		cmp    $0x1,%bl
		je     jump_fce34
		push   %edi
		call   RADFREE
		mov    0x3a4(%esi),%eax
		sub    %eax,0x45c(%esi)
	jump_fcdc4:
		mov    0xc(%esp),%ebx
		push   %ebx
		mov    0x4(%esi),%ecx
		push   %ecx
		call   SmackGetSizeDeltas
		add    $0x8,%esp
		lea    0x20(%eax),%edi
		mov    0x49c(%esi),%ebx
		mov    0x45c(%esi),%eax
		mov    %edi,0x3a4(%esi)
		add    %edi,%eax
		mov    %edi,%edx
		mov    %eax,0x45c(%esi)
		cmp    %ebx,%eax
		jbe    jump_fcdfe
		mov    %eax,0x49c(%esi)
	jump_fcdfe:
		push   %edx
		call   RADMALLOC
		mov    %eax,0x3a0(%esi)
		test   %eax,%eax
		je     jump_fcf27
		mov    %eax,%edx
		mov    %edi,%ecx
		mov    %edx,%edi
		xor    %al,%al
		cld
		mov    %al,%ah
		mov    %ax,%bx
		shl    $0x10,%eax
		mov    %bx,%ax
		mov    %cl,%bl
		shr    $0x2,%ecx
		rep stos %eax,%es:(%edi)
		mov    %bl,%cl
		and    $0x3,%cl
		rep stos %al,%es:(%edi)
	jump_fce34:
		mov    0x30(%esp),%eax
		mov    %eax,0x38c(%esi)
		mov    0x34(%esp),%eax
		mov    %eax,0x388(%esi)
		mov    0x3a0(%esi),%eax
		movb   $0x1,(%eax)
		testb  $0x20,0x386(%esi)
		setne  %dl
		add    $0x4,%eax
		and    $0xff,%edx
		mov    0x20(%esp),%edi
		mov    %dl,-0x3(%eax)
		test   %edi,%edi
		je     jump_fce7a
		mov    0x28(%esp),%edx
		sub    0x30(%esp),%edx
		dec    %edx
		jmp    jump_fce7e
	jump_fce7a:
		mov    0x30(%esp),%edx
	jump_fce7e:
		mov    0x2c(%esp),%ebx
		imul   %edx,%ebx
		mov    0x34(%esp),%ecx
		mov    0x24(%esp),%edx
		add    %ecx,%edx
		add    %ebx,%edx
		mov    0x8(%esp),%ebx
		imul   %ebp,%ebx
		mov    %edx,(%eax)
		mov    0x4(%esi),%edx
		add    $0x4,%eax
		shr    $0x2,%edx
		mov    %edx,(%eax)
		mov    0xc(%esp),%edx
		add    $0x4,%eax
		shr    $0x2,%edx
		mov    %edx,(%eax)
		lea    0x8(%eax),%edx
		lea    0x4(%edx),%ecx
		lea    0x8(%edx),%edi
		mov    %ecx,0x4(%esp)
		lea    0xc(%edx),%ecx
		mov    %ecx,(%esp)
		mov    0x20(%esp),%ecx
		add    $0x4,%eax
		test   %ecx,%ecx
		je     jump_fcefe
		lea    0x4(%ebx),%ecx
		neg    %ecx
		neg    %ebx
		mov    %ecx,(%eax)
		mov    %ebp,%eax
		mov    %ebx,(%edx)
		mov    0x4(%esp),%edx
		neg    %eax
		mov    %eax,(%edx)
		mov    0x8(%esp),%eax
		add    $0x2,%eax
		imul   %ebp,%eax
		mov    %ebp,%edx
		sub    0x4(%esi),%edx
		sub    %edx,%eax
		neg    %eax
		mov    %eax,(%edi)
		mov    (%esp),%eax
		jmp    jump_fcf15
	jump_fcefe:
		lea    -0x4(%ebx),%ecx
		mov    %ecx,(%eax)
		mov    0x4(%esp),%eax
		mov    %ebx,(%edx)
		mov    %ebp,(%eax)
		sub    0x4(%esi),%ebp
		add    %ebp,%ebx
		mov    (%esp),%eax
		mov    %ebx,(%edi)
	jump_fcf15:
		add    $0x4,%eax
		add    $0x4,%eax
		mov    0x4(%esi),%edx
		mov    %edx,-0x4(%eax)
		mov    0xc(%esp),%edx
		mov    %edx,(%eax)
	jump_fcf27:
		add    $0x10,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		ret    $0x1c


/*----------------------------------------------------------------*/
SMACKNEXTFRAME:
/*----------------------------------------------------------------*/
		push   %esi
		push   %edi
		mov    0xc(%esp),%esi
		test   %esi,%esi
		je     jump_fd56c
		cmpl   $0x0,_sounds
		je     jump_fd4ed
		call   *EXPORT_SYMBOL(_LowSoundCheckAddr)
	jump_fd4ed:
		mov    %esi,%eax
		call   timeframe_
		mov    0x370(%esi),%edx
		mov    0x370(%esi),%ecx
		mov    0x3b8(%esi),%ebx
		inc    %ecx
		mov    (%ebx,%edx,4),%edx
		mov    0x3b0(%esi),%ebx
		mov    %ecx,0x370(%esi)
		add    %edx,%ebx
		mov    0xc(%esi),%edi
		mov    %ebx,0x3b0(%esi)
		cmp    %edi,%ecx
		jae    jump_fd556
		testb  $0x2,0x385(%esi)
		jne    jump_fd556
		mov    0x3ac(%esi),%edx
		mov    %edx,0x3b0(%esi)
		mov    0x3b8(%esi),%ebx
		mov    0x370(%esi),%edx
		mov    %esi,%eax
		mov    (%ebx,%edx,4),%ebx
		mov    0x3ac(%esi),%edx
		call   blockread_
	jump_fd556:
		mov    %esi,%eax
		call   setuptheframe_
		cmpl   $0x0,_sounds
		je     jump_fd56c
		call   *EXPORT_SYMBOL(_LowSoundCheckAddr)
	jump_fd56c:
		pop    %edi
		pop    %esi
		ret    $0x4


/*----------------------------------------------------------------*/
timeframe_: /* 0xfd680 */
/*----------------------------------------------------------------*/
		push   %ebx
		push   %ecx
		push   %edx
		push   %esi
		push   %edi
		push   %ebp
		mov    %eax,%esi
		mov    0x460(%esi),%edx
		mov    $0xffffffff,%eax
		test   %edx,%edx
		je     jump_fd721
		call   *_SmackTimerReadAddr
		mov    %eax,%edx
		mov    0x460(%esi),%ebx
		mov    0x488(%esi),%ecx
		sub    %ebx,%edx
		movl   $0x0,0x460(%esi)
		cmp    %ecx,%edx
		jbe    jump_fd6f9
		mov    0x490(%esi),%ebx
		cmp    0x370(%esi),%ebx
		je     jump_fd6f1
		mov    0x488(%esi),%ebx
		mov    %ebx,0x48c(%esi)
		mov    0x490(%esi),%ebx
		mov    %ebx,0x494(%esi)
		mov    0x370(%esi),%ebx
		mov    %ebx,0x490(%esi)
	jump_fd6f1:
		mov    %edx,0x488(%esi)
		jmp    jump_fd721
	jump_fd6f9:
		cmp    0x48c(%esi),%edx
		jbe    jump_fd721
		mov    0x490(%esi),%ebx
		cmp    0x370(%esi),%ebx
		je     jump_fd721
		mov    %edx,0x48c(%esi)
		mov    0x370(%esi),%edx
		mov    %edx,0x494(%esi)
	jump_fd721:
		cmpl   $0x0,0x468(%esi)
		je     jump_fd757
		cmp    $0xffffffff,%eax
		jne    jump_fd735
		call   *_SmackTimerReadAddr
	jump_fd735:
		mov    %eax,%edx
		mov    0x468(%esi),%ebp
		mov    0x480(%esi),%ebx
		sub    %ebp,%edx
		movl   $0x0,0x468(%esi)
		add    %edx,%ebx
		mov    %ebx,0x480(%esi)
	jump_fd757:
		cmpl   $0x0,0x464(%esi)
		je     jump_fd78b
		cmp    $0xffffffff,%eax
		jne    jump_fd76b
		call   *_SmackTimerReadAddr
	jump_fd76b:
		mov    0x464(%esi),%edi
		mov    0x484(%esi),%ebp
		sub    %edi,%eax
		movl   $0x0,0x464(%esi)
		add    %eax,%ebp
		mov    %ebp,0x484(%esi)
	jump_fd78b:
		pop    %ebp
		pop    %edi
		pop    %esi
		pop    %edx
		pop    %ecx
		pop    %ebx
		ret


/*----------------------------------------------------------------*/
SMACKDOFRAME: /* 0xfd7a0 */
/*----------------------------------------------------------------*/
		push   %esi
		push   %ebp
		sub    $0x4,%esp
		mov    0x10(%esp),%esi
		test   %esi,%esi
		jne    jump_fd7b4
		xor    %eax,%eax
		jmp    jump_fd86d
	jump_fd7b4:
		call   *_SmackTimerReadAddr
		mov    %eax,0x464(%esi)
		mov    0x46c(%esi),%edx
		mov    %eax,0x460(%esi)
		test   %edx,%edx
		jne    jump_fd7d6
		mov    %eax,0x46c(%esi)
	jump_fd7d6:
		cmpl   $0x0,0x68(%esi)
		je     jump_fd7e8
		mov    0x370(%esi),%eax
		mov    %eax,0x3b4(%esi)
	jump_fd7e8:
		mov    0x478(%esi),%ecx
		inc    %ecx
		mov    %esi,%eax
		mov    %ecx,0x478(%esi)
		call   soundnext_
		testb  $0x4,0x385(%esi)
		jne    jump_fd80e
		cmpl   $0x0,0x400(%esi)
		jne    jump_fd812
	jump_fd80e:
		xor    %al,%al
		jmp    jump_fd819
	jump_fd812:
		mov    %esi,%eax
		call   doskip_
	jump_fd819:
		mov    0x3a0(%esi),%ebp
		mov    %al,(%esp)
		test   %ebp,%ebp
		je     jump_fd859
		test   %al,%al
		je     jump_fd832
		incl   0x47c(%esi)
		jmp    jump_fd859
	jump_fd832:
		mov    0x3a0(%esi),%eax
		push   %eax
		mov    0x39c(%esi),%edx
		push   %edx
		mov    0x3e0(%esi),%ebx
		push   %ebx
		movl   $0x1,0x3e4(%esi)
		call   Unsmack
		add    $0xc,%esp
	jump_fd859:
		cmpl   $0x0,_sounds
		je     jump_fd868
		call   *EXPORT_SYMBOL(_LowSoundCheckAddr)
	jump_fd868:
		xor    %eax,%eax
		mov    (%esp),%al
	jump_fd86d:
		add    $0x4,%esp
		pop    %ebp
		pop    %esi
		ret    $0x4


/*----------------------------------------------------------------*/
doskip_:
/*----------------------------------------------------------------*/
		push   %ebx
		push   %ecx
		push   %edx
		push   %esi
		push   %edi
		mov    %eax,%esi
		mov    0x420(%eax),%edx
		cmp    $0xffffffff,%edx
		je     jump_fd8e0
		cmpl   $0x0,0x428(%eax)
		jne    jump_fd8e0
		cmpl   $0x0,0x424(%eax)
		jne    jump_fd8a8
		mov    $0x1,%al
		jmp    jump_fd8e2
	jump_fd8a8:
		mov    %edx,%eax
		mov    0x404(%esi,%eax,4),%eax
		mov    0x44(%eax),%edi
		test   %edi,%edi
		jne    jump_fd8e0
		push   %eax
		call   *EXPORT_SYMBOL(_LowSoundPlayedAddr)
		mov    0x420(%esi),%edx
		mov    0x404(%esi,%edx,4),%edx
		mov    0x24(%edx),%edx
		shr    $0x7,%edx
		cmp    %edx,%eax
		jb     jump_fd8e0
		mov    $0x1,%al
		mov    %edi,0x424(%esi)
		jmp    jump_fd8e2
	jump_fd8e0:
		xor    %al,%al
	jump_fd8e2:
		pop    %edi
		pop    %esi
		pop    %edx
		pop    %ecx
		pop    %ebx
		ret


/*----------------------------------------------------------------*/
soundnext_:
/*----------------------------------------------------------------*/
		push   %ebx
		push   %ecx
		push   %edx
		push   %esi
		push   %edi
		push   %ebp
		sub    $0x14,%esp
		mov    %eax,0x8(%esp)
		cmpl   $0xffffffff,0x420(%eax)
		je     jump_fdb32
		cmpl   $0x0,0x428(%eax)
		jne    jump_fdb32
		cmpl   $0x0,0x400(%eax)
		je     jump_fd92a
		movl   $0x1,0x424(%eax)
	jump_fd92a:
		mov    0x8(%esp),%eax
		mov    0x420(%eax),%eax
		mov    0x8(%esp),%esi
		shl    $0x2,%eax
		add    %esi,%eax
		mov    0x404(%eax),%eax
		mov    %eax,0x4(%esp)
		mov    0x4(%esp),%edx
		mov    0x1c(%eax),%eax
		mov    0x20(%edx),%edi
		mov    0x24(%edx),%ebp
		add    %eax,%edi
		mov    0x1c(%edx),%eax
		mov    %edi,0x20(%edx)
		add    %eax,%ebp
		mov    %ebp,0x24(%edx)
		mov    0x384(%esi),%eax
		mov    %eax,(%esp)
		mov    %esp,%eax
		call   GetFirstTrack_
		mov    %al,0x10(%esp)
		and    $0xff,%eax
		shl    $0x2,%eax
		add    %esi,%eax
		mov    0x3c4(%eax),%esi
		test   %esi,%esi
		jne    jump_fd98d
		xor    %eax,%eax
		jmp    jump_fd99d
	jump_fd98d:
		testb  $0x80,0x4b(%eax)
		je     jump_fd998
		mov    0x4(%esi),%eax
		jmp    jump_fd99d
	jump_fd998:
		mov    (%esi),%eax
		sub    $0x4,%eax
	jump_fd99d:
		mov    %eax,0xc(%esp)
		test   %eax,%eax
		sete   %al
		mov    %eax,%edx
		xor    %eax,%eax
		mov    0x10(%esp),%al
		mov    0x8(%esp),%ebx
		shl    $0x2,%eax
		add    %ebx,%eax
		mov    0x404(%eax),%eax
		and    $0xff,%edx
		mov    %edx,0x44(%eax)
		test   %edx,%edx
		jne    jump_fdb15
		cmpl   $0x0,_sounds
		je     jump_fd9dd
		call   *EXPORT_SYMBOL(_LowSoundCheckAddr)
	jump_fd9dd:
		movzbl 0x10(%esp),%ebp
		mov    0x8(%esp),%edi
		shl    $0x2,%ebp
		add    %edi,%ebp
		mov    0x404(%ebp),%ebp
		mov    0xc(%esp),%edx
		mov    0x10(%ebp),%eax
		mov    0x18(%ebp),%ebx
		add    %edx,%eax
		cmp    %ebx,%eax
		jbe    jump_fda13
		mov    %ebx,%eax
		mov    0x10(%ebp),%ecx
		mov    0x2c(%ebp),%edi
		sub    %ecx,%eax
		inc    %edi
		mov    %eax,0xc(%esp)
		mov    %edi,0x2c(%ebp)
	jump_fda13:
		xor    %eax,%eax
		mov    0x10(%esp),%al
		mov    0x8(%esp),%edx
		shl    $0x2,%eax
		add    %edx,%eax
		testb  $0x80,0x4b(%eax)
		je     jump_fda4e
		mov    0xc(%ebp),%edi
		push   %edi
		mov    0x4(%ebp),%eax
		push   %eax
		mov    0x0(%ebp),%edx
		push   %edx
		mov    _trackbuf,%ebx
		push   %ebx
		mov    0x1c(%esp),%ecx
		push   %ecx
		add    $0x8,%esi
		push   %esi
		call   SmackDoPCM
		add    $0x18,%esp
		jmp    jump_fdaa2
	jump_fda4e:
		mov    0xc(%esp),%eax
		mov    0xc(%ebp),%edi
		mov    0x4(%ebp),%ebx
		add    %edi,%eax
		lea    0x4(%esi),%edx
		cmp    %ebx,%eax
		jbe    jump_fda8d
		mov    %ebx,%ecx
		mov    %edx,%esi
		sub    %edi,%ecx
		cld
		mov    %cl,%bl
		shr    $0x2,%ecx
		rep movsl %ds:(%esi),%es:(%edi)
		mov    %bl,%cl
		and    $0x3,%cl
		rep movsb %ds:(%esi),%es:(%edi)
		mov    0x4(%ebp),%eax
		sub    0xc(%ebp),%eax
		mov    0xc(%esp),%ecx
		sub    %eax,%ecx
		shl    $0x2,%eax
		mov    0x0(%ebp),%edi
		lea    (%edx,%eax,1),%esi
		jmp    jump_fda93
	jump_fda8d:
		mov    0xc(%esp),%ecx
		mov    %edx,%esi
	jump_fda93:
		cld
		mov    %cl,%bl
		shr    $0x2,%ecx
		rep movsl %ds:(%esi),%es:(%edi)
		mov    %bl,%cl
		and    $0x3,%cl
		rep movsb %ds:(%esi),%es:(%edi)
	jump_fdaa2:
		mov    0xc(%esp),%eax
		mov    0x28(%ebp),%esi
		add    %eax,%esi
		mov    0x10(%ebp),%edi
		mov    %esi,0x28(%ebp)
		add    %eax,%edi
		mov    0xc(%ebp),%edx
		mov    %edi,0x10(%ebp)
		add    %eax,%edx
		mov    0x4(%ebp),%ebx
		mov    %edx,0xc(%ebp)
		cmp    %ebx,%edx
		jb     jump_fdad1
		mov    %edx,%eax
		mov    0x0(%ebp),%edx
		sub    %ebx,%eax
		add    %eax,%edx
		mov    %edx,0xc(%ebp)
	jump_fdad1:
		mov    %esp,%eax
		call   GetFirstTrack_
		mov    %al,0x10(%esp)
		cmp    $0xff,%al
		je     jump_fdb15
		and    $0xff,%eax
		mov    0x8(%esp),%esi
		shl    $0x2,%eax
		add    %esi,%eax
		mov    0x3c4(%eax),%esi
		test   %esi,%esi
		jne    jump_fdafc
		xor    %eax,%eax
		jmp    jump_fdb0c
	jump_fdafc:
		testb  $0x80,0x4b(%eax)
		je     jump_fdb07
		mov    0x4(%esi),%eax
		jmp    jump_fdb0c
	jump_fdb07:
		mov    (%esi),%eax
		sub    $0x4,%eax
	jump_fdb0c:
		mov    %eax,0xc(%esp)
		jmp    jump_fd9dd
	jump_fdb15:
		mov    0x4(%esp),%eax
		mov    0x4(%esp),%edx
		mov    0x20(%eax),%eax
		mov    0x28(%edx),%edi
		shr    $0x7,%eax
		cmp    %edi,%eax
		jbe    jump_fdb32
		mov    %edi,%eax
		shl    $0x7,%eax
		mov    %eax,0x20(%edx)
	jump_fdb32:
		add    $0x14,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		pop    %edx
		pop    %ecx
		pop    %ebx
		ret


/*----------------------------------------------------------------*/
SMACKCLOSE:
/*----------------------------------------------------------------*/
		push   %esi
		push   %edi
		push   %ebp
		mov    0x10(%esp),%ebp
		test   %ebp,%ebp
		je     jump_fdc6c
		cmpl   $0xffffffff,0x420(%ebp)
		je     jump_fdbb0
		mov    %ebp,%esi
		lea    0x1c(%ebp),%edi
	jump_fdb5d:
		mov    0x404(%esi),%ebx
		test   %ebx,%ebx
		je     jump_fdb9f
		push   %ebx
		call   *EXPORT_SYMBOL(_LowSoundCloseAddr)
		mov    0x404(%esi),%eax
		mov    (%eax),%edx
		push   %edx
		call   RADFREE
		mov    0x404(%esi),%ebx
		push   %ebx
		call   RADFREE
		mov    _sounds,%ecx
		dec    %ecx
		movl   $0x0,0x404(%esi)
		mov    %ecx,_sounds
	jump_fdb9f:
		add    $0x4,%esi
		cmp    %edi,%esi
		jne    jump_fdb5d
		movl   $0xffffffff,0x420(%ebp)
	jump_fdbb0:
		mov    _sounds,%esi
		test   %esi,%esi
		jne    jump_fdbd0
		mov    _trackbuf,%edi
		test   %edi,%edi
		je     jump_fdbd0
		push   %edi
		call   RADFREE
		mov    %esi,_trackbuf
	jump_fdbd0:
		mov    0x394(%ebp),%ebx
		cmp    $0xffffffff,%ebx
		je     jump_fdbed
		testb  $0x10,0x385(%ebp)
		jne    jump_fdbed
		push   %ebx
		call   ac_dos_low_level_close
		add    $0x4,%esp
	jump_fdbed:
		mov    0x3a0(%ebp),%esi
		test   %esi,%esi
		je     jump_fdbfd
		push   %esi
		call   RADFREE
	jump_fdbfd:
		mov    0x39c(%ebp),%eax
		test   %eax,%eax
		je     jump_fdc0d
		push   %eax
		call   RADFREE
	jump_fdc0d:
		mov    0x3bc(%ebp),%ebx
		test   %ebx,%ebx
		je     jump_fdc1d
		push   %ebx
		call   RADFREE
	jump_fdc1d:
		mov    0x3ac(%ebp),%esi
		test   %esi,%esi
		je     jump_fdc2d
		push   %esi
		call   RADFREE
	jump_fdc2d:
		mov    0x42c(%ebp),%eax
		test   %eax,%eax
		je     jump_fdc3d
		push   %eax
		call   RADFREE
	jump_fdc3d:
		mov    $0x4ac,%ecx
		mov    %ebp,%edi
		xor    %al,%al
		cld
		mov    %al,%ah
		mov    %ax,%bx
		shl    $0x10,%eax
		mov    %bx,%ax
		mov    %cl,%bl
		shr    $0x2,%ecx
		rep stos %eax,%es:(%edi)
		mov    %bl,%cl
		and    $0x3,%cl
		rep stos %al,%es:(%edi)
		push   %ebp
		call   RADFREE
		call   *_SmackTimerDoneAddr
	jump_fdc6c:
		pop    %ebp
		pop    %edi
		pop    %esi
		ret    $0x4


/*----------------------------------------------------------------*/
SMACKOPEN:
/*----------------------------------------------------------------*/
		push   %esi
		push   %edi
		push   %ebp
		sub    $0x1c,%esp
		xor    %edx,%edx
		mov    %edx,0x18(%esp)
		call   *_SmackTimerSetupAddr
		call   *_SmackTimerReadAddr
		push   $0x4ac
		xor    %ebp,%ebp
		mov    %eax,0x8(%esp)
		call   RADMALLOC
		mov    %eax,%esi
		test   %eax,%eax
		jne    jump_fdefb
		call   *_SmackTimerDoneAddr
		xor    %eax,%eax
		jmp    jump_fe6b4
	jump_fdefb:
		mov    $0x4ac,%ecx
		mov    %esi,%edi
		xor    %al,%al
		cld
		mov    %al,%ah
		mov    %ax,%bx
		shl    $0x10,%eax
		mov    %bx,%ax
		mov    %cl,%bl
		shr    $0x2,%ecx
		rep stos %eax,%es:(%edi)
		mov    %bl,%cl
		and    $0x3,%cl
		rep stos %al,%es:(%edi)
		mov    %esi,%eax
		addl   $0x4ac,0x45c(%eax)
		testb  $0x10,0x31(%esp)
		je     jump_fdf51
		push   %ebp
		mov    0x38(%esp),%eax
		mov    %esi,%edx
		push   %eax
		mov    %eax,0x394(%edx)
		call   ac_dos_low_level_seek_relative
		mov    %esi,%edx
		add    $0x8,%esp
		mov    %eax,0x3a8(%edx)
		jmp    jump_fdf6f
	jump_fdf51:
		push   %ebp
		mov    %ds,%eax
		and    $0xffff,%eax
		push   %eax
		mov    0x3c(%esp),%edi
		push   %edi
		call   ac_dos_low_level_open
		mov    %esi,%edx
		add    $0xc,%esp
		mov    %eax,0x394(%edx)
	jump_fdf6f:
		cmpl   $0xffffffff,0x394(%esi)
		je     jump_fdfc0
		testb  $0x8,0x31(%esp)
		je     jump_fdf8a
		mov    data_1592e8,%eax
		mov    %eax,0x4a0(%esi)
	jump_fdf8a:
		lea    0x64(%esi),%eax
		xor    %ecx,%ecx
		sub    %esi,%eax
		mov    %ecx,(%esp)
		lea    0x4(%eax),%ebx
		mov    %esi,%edx
		mov    %esi,%eax
		mov    %ecx,(%esi)
		call   blockread_
		cmpl   $0x324b4d53,(%esi)
		je     jump_fdfd7
	jump_fdfaa:
		testb  $0x10,0x31(%esp)
		jne    jump_fdfc0
		mov    0x394(%esi),%eax
		push   %eax
		call   ac_dos_low_level_close
		add    $0x4,%esp
	jump_fdfc0:
		push   %esi
		call   RADFREE
		call   *_SmackTimerDoneAddr
		xor    %eax,%eax
		add    $0x1c,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		ret    $0xc
	jump_fdfd7: /* XXX: abc */
		testb  $0x80,0x30(%esp)
		je     jump_fdfe6
		mov    data_1592ec,%eax
		mov    %eax,0x10(%esi)
	jump_fdfe6:
		mov    0x10(%esi),%eax
		test   %eax,%eax
		jge    jump_fdff1
		neg    %eax
		jmp    jump_fe000
	jump_fdff1:
		mov    %eax,%edx
		shl    $0x2,%eax
		sub    %edx,%eax
		shl    $0x3,%eax
		add    %edx,%eax
		shl    $0x2,%eax
	jump_fe000:
		mov    %eax,0x400(%esi)
		test   %eax,%eax
		je     jump_fe01b
		mov    $0x186a0,%eax
		mov    0x400(%esi),%ebx
		xor    %edx,%edx
		div    %ebx
		jmp    jump_fe020
	jump_fe01b:
		mov    $0x186a0,%eax
	jump_fe020:
		mov    %eax,0x10(%esp)
		test   %eax,%eax
		jne    jump_fe02d
		inc    %eax
		mov    %eax,0x10(%esp)
	jump_fe02d: /* XXX: abc no */
		mov    0x14(%esi),%eax
		mov    0xc(%esi),%edx
		and    $0x1,%eax
		add    %eax,%edx
		mov    %edx,(%esp)
		lea    0x0(,%edx,4),%eax
		add    %edx,%eax
		mov    0x45c(%esi),%edi
		add    $0x4,%eax
		mov    0x49c(%esi),%ebx
		add    %eax,%edi
		mov    %eax,%edx
		mov    %edi,%eax
		mov    %edi,0x45c(%esi)
		cmp    %ebx,%edi
		jbe    jump_fe069
		mov    %edi,0x49c(%esi)
	jump_fe069: /* XXX: abc no */
		push   %edx
		call   RADMALLOC
		mov    %eax,0x3bc(%esi)
		test   %eax,%eax
		je     jump_fdfaa
		mov    (%esp),%edx
		add    %eax,%edx
		mov    %edx,0x3b8(%esi)
		mov    (%esp),%ebx
		mov    %esi,%eax
		shl    $0x2,%ebx
		call   blockread_
		mov    (%esp),%ebx
		mov    %esi,%eax
		mov    0x3bc(%esi),%edx
		call   blockread_
		mov    (%esp),%eax
		mov    (%esp),%edi
		shl    $0x2,%eax
		mov    0x3a8(%esi),%edx
		add    %edi,%eax
		add    %eax,%edx
		mov    %edx,0x3a8(%esi)
		call   func_139590
		mov    0x38(%esi),%ebx
		mov    0x3c(%esi),%ecx
		add    %ebx,%eax
		mov    0x40(%esi),%edi
		add    %ecx,%eax
		mov    0x44(%esi),%edx
		add    %edi,%eax
		mov    0x45c(%esi),%ebx
		add    %edx,%eax
		mov    0x49c(%esi),%ecx
		add    %eax,%ebx
		mov    %eax,%edx
		mov    %ebx,%eax
		mov    %ebx,0x45c(%esi)
		cmp    %ecx,%ebx
		jbe    jump_fe0f9
		mov    %ebx,0x49c(%esi)
	jump_fe0f9: /* XXX: abc no */
		push   %edx
		call   RADMALLOC
		mov    %eax,0x39c(%esi)
		test   %eax,%eax
		jne    jump_fe11a
		mov    0x3bc(%esi),%ebp
		push   %ebp
		call   RADFREE
		jmp    jump_fdfaa
	jump_fe11a:
		mov    0x34(%esi),%edx
		add    $0x1003,%edx
		and    $0xfc,%dl
		mov    %esi,%eax
		cmp    $0x2000,%edx
		jae    jump_fe135
		mov    $0x2000,%edx
	jump_fe135:
		mov    0x45c(%eax),%ecx
		mov    %edx,%ebx
		add    %edx,%ecx
		mov    0x49c(%eax),%edi
		mov    %ecx,%edx
		mov    %ecx,0x45c(%eax)
		cmp    %edi,%ecx
		jbe    jump_fe157
		mov    %ecx,0x49c(%eax)
	jump_fe157:
		push   %ebx
		call   RADMALLOC
		mov    %eax,%edi
		test   %eax,%eax
		jne    jump_fe180
	jump_fe163: /* XXX: abc - - */
		mov    0x39c(%esi),%edi
		push   %edi
		call   RADFREE
		mov    0x3bc(%esi),%ebp
		push   %ebp
		call   RADFREE
		jmp    jump_fdfaa
	jump_fe180:
		lea    0x1000(%eax),%edx
		mov    0x34(%esi),%ebx
		mov    %esi,%eax
		call   blockread_
		mov    0x44(%esi),%eax
		push   %eax
		mov    0x40(%esi),%edx
		push   %edx
		mov    0x3c(%esi),%ebx
		push   %ebx
		mov    0x38(%esi),%ecx
		push   %ecx
		mov    0x39c(%esi),%eax
		push   %eax
		push   %edi
		call   func_1395a0
		add    $0x18,%esp
		push   %edi
		call   RADFREE
		mov    0x34(%esi),%eax
		mov    0x45c(%esi),%edx
		add    $0x1000,%eax
		sub    %eax,%edx
		lea    0x64(%esi),%eax
		mov    0x34(%esi),%ebx
		sub    %esi,%eax
		mov    0x3a8(%esi),%ecx
		add    $0x4,%eax
		mov    %edx,0x45c(%esi)
		add    %ebx,%eax
		mov    0xc(%esi),%edx
		add    %eax,%ecx
		mov    0x14(%esi),%eax
		dec    %edx
		and    $0x1,%eax
		mov    %ecx,0x3a8(%esi)
		add    %eax,%edx
		mov    0x10(%esp),%edi
		mov    %edx,(%esp)
		xor    %ecx,%ecx
		mov    0x3b8(%esi),%eax
		cmp    %edi,%edx
		jae    jump_fe231
		mov    %ecx,0xc(%esp)
		xor    %ebx,%ebx
	jump_fe20c:
		mov    (%eax),%edi
		mov    %edi,%edx
		add    %edi,%ecx
		cmp    0x18(%esp),%edx
		jbe    jump_fe21c
		mov    %edx,0x18(%esp)
	jump_fe21c:
		mov    (%esp),%edx
		mov    (%eax),%edi
		add    $0x4,%eax
		inc    %ebx
		add    %edi,%ebp
		cmp    %edx,%ebx
		ja     jump_fe2bf
		jmp    jump_fe20c
	jump_fe231:
		xor    %edx,%edx
		xor    %ebx,%ebx
		test   %edi,%edi
		jbe    jump_fe249
	jump_fe239:
		mov    %eax,%edi
		inc    %ebx
		add    (%edi),%edx
		mov    0x10(%esp),%edi
		add    $0x4,%eax
		cmp    %edi,%ebx
		jb     jump_fe239
	jump_fe249:
		mov    (%esp),%ebx
		mov    0x10(%esp),%edi
		sub    %edi,%ebx
		mov    0x3b8(%esi),%eax
		mov    %ebx,0x8(%esp)
		xor    %ebx,%ebx
		shl    $0x2,%edi
		add    %eax,%edi
		mov    %edi,0x14(%esp)
	jump_fe267:
		cmp    %ecx,%edx
		jbe    jump_fe275
		test   %ebx,%ebx
		je     jump_fe275
		mov    %edx,%ecx
		mov    %ebx,0xc(%esp)
	jump_fe275:
		sub    (%eax),%edx
		mov    0x14(%esp),%edi
		add    (%edi),%edx
		mov    (%eax),%edi
		cmp    0x18(%esp),%edi
		jbe    jump_fe289
		mov    %edi,0x18(%esp)
	jump_fe289:
		add    (%eax),%ebp
		mov    0x14(%esp),%edi
		add    $0x4,%edi
		inc    %ebx
		mov    %edi,0x14(%esp)
		mov    0x8(%esp),%edi
		add    $0x4,%eax
		cmp    %edi,%ebx
		ja     jump_fe2ba
		jmp    jump_fe267
	jump_fe2a4:
		mov    0x18(%esp),%edi
		mov    (%eax),%edx
		cmp    %edi,%edx
		jbe    jump_fe2b2
		mov    %edx,0x18(%esp)
	jump_fe2b2:
		mov    (%eax),%edx
		add    $0x4,%eax
		inc    %ebx
		add    %edx,%ebp
	jump_fe2ba:
		cmp    (%esp),%ebx
		jbe    jump_fe2a4
	jump_fe2bf:
		mov    0xc(%esp),%eax
		xor    %edx,%edx
		mov    %eax,0x4a8(%esi)
		mov    %ebp,%eax
		div    %ebx
		mov    %ecx,0x4a4(%esi)
		mov    %eax,0x498(%esi)
		testb  $0x2,0x31(%esp)
		je     jump_fe2ed
		mov    %ebp,0x398(%esi)
		jmp    jump_fe3e0
	jump_fe2ed:
		cmpl   $0xffffffff,0x2c(%esp)
		jne    jump_fe32d
		cmpl   $0x0,0x400(%esi)
		je     jump_fe305
		mov    0x4a4(%esi),%eax
		jmp    jump_fe30a
	jump_fe305:
		mov    $0x3000,%eax
	jump_fe30a:
		mov    %ebp,%edx
		shr    $0x2,%edx
		mov    %eax,0x2c(%esp)
		cmp    %edx,%eax
		jbe    jump_fe31b
		mov    %edx,0x2c(%esp)
	jump_fe31b:
		cmpl   $0x3000,0x2c(%esp)
		jae    jump_fe32d
		movl   $0x3000,0x2c(%esp)
	jump_fe32d:
		mov    0x2c(%esp),%eax
		add    $0xfff,%eax
		shr    $0xc,%eax
		shl    $0xc,%eax
		mov    %eax,0x2c(%esp)
		cmp    $0x2000,%eax
		jae    jump_fe34f
		movl   $0x2000,0x2c(%esp)
	jump_fe34f:
		mov    $0x5,%ebx
		lea    0x0(,%ebp,4),%eax
		xor    %edx,%edx
		div    %ebx
		mov    0x2c(%esp),%edx
		cmp    %edx,%eax
		ja     jump_fe374
		orb    $0x2,0x31(%esp)
		mov    %ebp,0x398(%esi)
		jmp    jump_fe3e0
	jump_fe374:
		mov    0x18(%esp),%eax
		mov    %edx,0x440(%esi)
		mov    %eax,0x398(%esi)
		test   %edx,%edx
		je     jump_fe3e0
		lea    0x1000(%edx),%eax
		mov    0x45c(%esi),%ecx
		mov    0x49c(%esi),%edi
		add    %eax,%ecx
		mov    %eax,%edx
		mov    %ecx,%eax
		mov    %ecx,0x45c(%esi)
		cmp    %edi,%ecx
		jbe    jump_fe3b0
		mov    %ecx,0x49c(%esi)
	jump_fe3b0:
		push   %edx
		call   RADMALLOC
		mov    %eax,0x42c(%esi)
		mov    %eax,0x434(%esi)
		mov    %eax,0x438(%esi)
		test   %eax,%eax
		je     jump_fe163
		mov    %eax,%edx
		mov    0x440(%esi),%eax
		add    %eax,%edx
		mov    %edx,0x430(%esi)
	jump_fe3e0:
		mov    0x398(%esi),%eax
		mov    0x45c(%esi),%ebx
		add    $0x8,%eax
		mov    0x49c(%esi),%ecx
		add    %eax,%ebx
		mov    %eax,%edx
		mov    %ebx,%eax
		mov    %ebx,0x45c(%esi)
		cmp    %ecx,%ebx
		jbe    jump_fe40b
		mov    %ebx,0x49c(%esi)
	jump_fe40b:
		push   %edx
		call   RADMALLOC
		mov    %eax,0x3ac(%esi)
		test   %eax,%eax
		jne    jump_fe434
		mov    0x42c(%esi),%ebp
		test   %ebp,%ebp
		je     jump_fe163
		push   %ebp
		call   RADFREE
		jmp    jump_fe163
	jump_fe434:
		mov    0x3a8(%esi),%eax
		mov    %eax,0x444(%esi)
		testb  $0x2,0x31(%esp)
		je     jump_fe487
		mov    %ebp,%ebx
		mov    %esi,%eax
		mov    0x3ac(%esi),%edx
		call   blockread_
		testb  $0x10,0x31(%esp)
		jne    jump_fe46c
		mov    0x394(%esi),%ecx
		push   %ecx
		call   ac_dos_low_level_close
		add    $0x4,%esp
	jump_fe46c:
		movl   $0xffffffff,0x394(%esi)
		mov    0x3ac(%esi),%eax
		mov    %eax,0x3b0(%esi)
		jmp    jump_fe508
	jump_fe487:
		and    $0xfff,%eax
		mov    %eax,(%esp)
		je     jump_fe4d7
		mov    %esp,%eax
		mov    (%esp),%edx
		push   %eax
		mov    $0x1000,%eax
		sub    %edx,%eax
		push   %eax
		mov    0x42c(%esi),%edx
		mov    %ds,%eax
		and    $0xffff,%eax
		push   %eax
		push   %edx
		mov    0x394(%esi),%ebx
		push   %ebx
		call   ac_dos_low_level_read
		add    $0x14,%esp
		mov    0x42c(%esi),%eax
		mov    (%esp),%edx
		add    %eax,%edx
		mov    %edx,0x438(%esi)
		mov    (%esp),%eax
		mov    %eax,0x43c(%esi)
	jump_fe4d7:
		testb  $0x2,0x385(%esi)
		jne    jump_fe508
		mov    0x3ac(%esi),%eax
		mov    %eax,0x3b0(%esi)
		mov    0x3b8(%esi),%edx
		mov    0x370(%esi),%eax
		mov    (%edx,%eax,4),%ebx
		mov    %esi,%eax
		mov    0x3ac(%esi),%edx
		call   blockread_
	jump_fe508: /* XXX: abc no */
		mov    %esi,%eax
		movl   $0xffffffff,0x3b4(%esi)
		call   setuptheframe_
		movl   $0xffffffff,0x420(%esi)
		mov    0x30(%esp),%eax
		and    $0xffc01fff,%eax
		mov    %eax,0x384(%esi)
		testl  $0xfe000,0x30(%esp)
		je     jump_fe5d4
	jump_fe540: /* XXX: abc - yes */
		lea    0x30(%esp),%eax
		call   GetFirstTrack_
		and    $0xff,%eax
		mov    $0x70,%edx
		mov    %eax,(%esp)
		mov    %esi,%eax
		call   smkmalloc_
		mov    (%esp),%edx
		mov    %eax,0x404(%esi,%edx,4)
		mov    (%esp),%eax
		cmpl   $0x0,0x404(%esi,%eax,4)
		je     jump_fe5c6
		xor    %edx,%edx
		mov    %esi,%eax
		mov    (%esp),%dl
		call   soundopen_
		test   %al,%al
		je     jump_fe5a1
		mov    (%esp),%ecx
		mov    $0x1,%eax
		add    $0xd,%ecx
		mov    0x384(%esi),%ebp
		shl    %cl,%eax
		or     %eax,%ebp
		mov    %ebp,0x384(%esi)
		jmp    jump_fe5c6
	jump_fe5a1:
		mov    (%esp),%eax
		mov    0x404(%esi,%eax,4),%ecx
		push   %ecx
		call   RADFREE
		subl   $0x70,0x45c(%esi)
		mov    (%esp),%eax
		movl   $0x0,0x404(%esi,%eax,4)
	jump_fe5c6:
		testl  $0xfe000,0x30(%esp)
		jne    jump_fe540
	jump_fe5d4: /* XXX: abc no(once) */
		movl   $0xffffffff,0x3fc(%esi)
		testb  $0x1,0x31(%esp)
		je     jump_fe5f0
	jump_fe5e5:
		mov    %esi,%eax
		call   backgroundload_
		test   %eax,%eax
		jne    jump_fe5e5
	jump_fe5f0:
		mov    0x30(%esp),%eax
		and    $0x300000,%eax
		cmp    $0x200000,%eax
		jb     jump_fe60b
		jbe    jump_fe623
		cmp    $0x300000,%eax
		je     jump_fe614
		jmp    jump_fe62d
	jump_fe60b:
		cmp    $0x100000,%eax
		je     jump_fe61a
		jmp    jump_fe62d
	jump_fe614:
		andb   $0xf9,0x14(%esi)
		jmp    jump_fe62d
	jump_fe61a:
		mov    0x14(%esi),%eax
		and    $0xf9,%al
		or     $0x2,%al
		jmp    jump_fe62a
	jump_fe623:
		mov    0x14(%esi),%eax
		and    $0xf9,%al
		or     $0x4,%al
	jump_fe62a:
		mov    %eax,0x14(%esi)
	jump_fe62d:
		mov    0x14(%esi),%eax
		and    $0x6,%eax
		cmp    $0x2,%eax
		jb     jump_fe651
		jbe    jump_fe641
		cmp    $0x4,%eax
		je     jump_fe64a
		jmp    jump_fe651
	jump_fe641:
		orb    $0x10,0x386(%esi)
		jmp    jump_fe651
	jump_fe64a:
		orb    $0x20,0x386(%esi)
	jump_fe651:
		testb  $0x30,0x386(%esi)
		je     jump_fe662
		mov    0x8(%esi),%eax
		add    %eax,%eax
		mov    %eax,0x8(%esi)
	jump_fe662:
		call   *_SmackTimerReadAddr
		mov    0x4(%esp),%edx
		sub    %edx,%eax
		mov    %eax,0x470(%esi)
		mov    0x44c(%esi),%ebx
		mov    0x448(%esi),%ecx
		mov    0x454(%esi),%eax
		movl   $0x0,0x454(%esi)
		add    %eax,%ebx
		mov    0x450(%esi),%eax
		mov    %ebx,0x44c(%esi)
		add    %eax,%ecx
		mov    0x44c(%esi),%eax
		mov    %ecx,0x448(%esi)
		mov    %eax,0x474(%esi)
		mov    %esi,%eax
	jump_fe6b4:
		add    $0x1c,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		ret    $0xc


/*----------------------------------------------------------------*/
GetFirstTrack_:
/*----------------------------------------------------------------*/
		push   %ebx
		push   %ecx
		push   %edx
		push   %esi
		mov    %eax,%ebx
		mov    $0x2000,%edx
		xor    %al,%al
	jump_fe6cd:
		mov    (%ebx),%ecx
		test   %ecx,%edx
		je     jump_fe6e0
		not    %edx
		mov    %ecx,%esi
		and    %edx,%esi
		mov    %esi,(%ebx)
		pop    %esi
		pop    %edx
		pop    %ecx
		pop    %ebx
		ret
	jump_fe6e0:
		inc    %al
		add    %edx,%edx
		cmp    $0x7,%al
		jb     jump_fe6cd
		mov    $0xff,%al
		pop    %esi
		pop    %edx
		pop    %ecx
		pop    %ebx
		ret


/*----------------------------------------------------------------*/
soundopen_:
/*----------------------------------------------------------------*/
		push   %ebx
		push   %ecx
		push   %esi
		push   %edi
		push   %ebp
		sub    $0x14,%esp
		mov    %eax,%esi
		mov    %dl,0x10(%esp)
		cmpl   $0x0,_LowSoundOpenAddr
		jne    jump_fe70e
		xor    %al,%al
		jmp    jump_fe966
	jump_fe70e:
		xor    %eax,%eax
		mov    0x10(%esp),%al
		shl    $0x2,%eax
		add    %esi,%eax
		mov    0x48(%eax),%edx
		shr    $0x18,%edx
		test   $0x40,%dl
		je     jump_fe72e
		mov    0x48(%eax),%eax
		and    $0xffffff,%eax
		jmp    jump_fe730
	jump_fe72e:
		xor    %eax,%eax
	jump_fe730:
		mov    %eax,(%esp)
		jne    jump_fe740
		xor    %al,%al
		add    $0x14,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		pop    %ecx
		pop    %ebx
		ret
	jump_fe740:
		xor    %edx,%edx
		mov    0x10(%esp),%dl
		shl    $0x2,%edx
		lea    (%esi,%edx,1),%edi
		mov    0x48(%edi),%edx
		shr    $0x1c,%edx
		and    $0x1,%edx
		mov    %dl,0xc(%esp)
		mov    0x48(%edi),%edx
		shr    $0x1d,%edx
		and    $0x1,%edx
		mov    %dl,0x8(%esp)
		xor    %edx,%edx
		mov    0x8(%esp),%dl
		inc    %edx
		imul   %eax,%edx
		xor    %eax,%eax
		mov    0xc(%esp),%al
		inc    %eax
		imul   %eax,%edx
		mov    _trackbuf,%ebx
		mov    %edx,0x4(%esp)
		test   %ebx,%ebx
		jne    jump_fe7c5
		mov    $0x2000,%edx
		mov    0x45c(%esi),%ecx
		add    %edx,%ecx
		mov    0x49c(%esi),%edi
		mov    %ecx,0x45c(%esi)
		cmp    %edi,%ecx
		jbe    jump_fe7ab
		mov    %ecx,0x49c(%esi)
	jump_fe7ab:
		push   %edx
		call   RADMALLOC
		mov    %eax,_trackbuf
		test   %eax,%eax
		jne    jump_fe7c5
		xor    %al,%al
		add    $0x14,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		pop    %ecx
		pop    %ebx
		ret
	jump_fe7c5:
		movzbl 0x10(%esp),%ebp
		mov    $0x70,%ecx
		xor    %al,%al
		mov    0x404(%esi,%ebp,4),%edi
		cld
		mov    %al,%ah
		mov    %ax,%bx
		shl    $0x10,%eax
		mov    %bx,%ax
		mov    %cl,%bl
		shr    $0x2,%ecx
		rep stos %eax,%es:(%edi)
		mov    %bl,%cl
		and    $0x3,%cl
		rep stos %al,%es:(%edi)
		mov    $0x186a0,%ebx
		mov    0x400(%esi),%ecx
		mov    0x4(%esp),%eax
		shl    $0x7,%ecx
		mul    %ecx
		div    %ebx
		mov    0x404(%esi,%ebp,4),%edx
		mov    %eax,0x1c(%edx)
		mov    0x4(%esp),%eax
		mov    0x404(%esi,%ebp,4),%edx
		shl    $0x6,%eax
		mov    %eax,0x24(%edx)
		mov    0x404(%esi,%ebp,4),%eax
		mov    0x1c(%eax),%edx
		mov    0x4(%esp),%ebx
		shr    $0x6,%edx
		add    %ebx,%edx
		add    $0xfff,%edx
		xor    %dl,%dl
		and    $0xf0,%dh
		mov    %edx,0x18(%eax)
		mov    0x404(%esi,%ebp,4),%eax
		cmpl   $0x2000,0x18(%eax)
		jae    jump_fe85b
		movl   $0x2000,0x18(%eax)
	jump_fe85b:
		xor    %eax,%eax
		mov    0x10(%esp),%al
		shl    $0x2,%eax
		lea    (%esi,%eax,1),%edi
		mov    0x404(%edi),%edx
		mov    %esi,%eax
		mov    0x18(%edx),%edx
		call   smkmalloc_
		mov    %eax,%edx
		mov    0x404(%edi),%eax
		mov    %edx,0x8(%eax)
		mov    0x404(%edi),%eax
		mov    %edx,0xc(%eax)
		mov    0x404(%edi),%eax
		mov    %edx,(%eax)
		mov    0x404(%edi),%eax
		mov    0x18(%eax),%ebp
		add    %ebp,%edx
		mov    %edx,0x4(%eax)
		mov    0x404(%edi),%eax
		cmpl   $0x0,(%eax)
		jne    jump_fe8b7
		xor    %al,%al
		add    $0x14,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		pop    %ecx
		pop    %ebx
		ret
	jump_fe8b7:
		mov    0x4(%esp),%edx
		mov    %edx,0x14(%eax)
		mov    0x404(%edi),%eax
		mov    (%esp),%edx
		mov    %edx,0x40(%eax)
		xor    %eax,%eax
		mov    0x404(%edi),%edx
		mov    0x8(%esp),%al
		mov    %eax,0x48(%edx)
		xor    %edx,%edx
		mov    0x404(%edi),%eax
		mov    0xc(%esp),%dl
		mov    %edx,0x4c(%eax)
		mov    0x404(%edi),%ebx
		push   %ebx
		mov    0x384(%esi),%ecx
		push   %ecx
		call   *_LowSoundOpenAddr
		test   %al,%al
		jne    jump_fe92e
		mov    0x404(%edi),%eax
		mov    (%eax),%edx
		push   %edx
		call   RADFREE
		mov    0x404(%edi),%eax
		mov    0x45c(%esi),%ebx
		sub    0x18(%eax),%ebx
		xor    %al,%al
		mov    %ebx,0x45c(%esi)
		add    $0x14,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		pop    %ecx
		pop    %ebx
		ret
	jump_fe92e:
		mov    0x404(%edi),%eax
		mov    0x1c(%eax),%edx
		mov    0x18(%edi),%ecx
		shr    $0x7,%edx
		sub    %edx,%ecx
		mov    %ecx,0x30(%eax)
		cmpl   $0xffffffff,0x420(%esi)
		jne    jump_fe957
		xor    %eax,%eax
		mov    0x10(%esp),%al
		mov    %eax,0x420(%esi)
	jump_fe957:
		mov    _sounds,%ebp
		inc    %ebp
		mov    $0x1,%al
		mov    %ebp,_sounds
	jump_fe966:
		add    $0x14,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		pop    %ecx
		pop    %ebx
		ret


/*----------------------------------------------------------------*/
setuptheframe_:
/*----------------------------------------------------------------*/
		push   %ebx
		push   %ecx
		push   %edx
		push   %esi
		push   %edi
		push   %ebp
		sub    $0x318,%esp
		mov    %eax,0x300(%esp)
		mov    0x370(%eax),%edx
		sub    0xc(%eax),%edx
		movl   $0x0,0x3f8(%eax)
		test   %edx,%edx
		jl     jump_fea25
		testb  $0x1,0x14(%eax)
		je     jump_fea08
		test   %edx,%edx
		jne    jump_fe9f5
		mov    0x300(%esp),%edx
		testb  $0x2,0x385(%edx)
		jne    jump_fea25
		mov    0x300(%esp),%ebx
		mov    0x3ac(%edx),%edx
		mov    %edx,0x3b0(%ebx)
		mov    0x370(%ebx),%edx
		mov    0x3b8(%ebx),%ebx
		mov    (%ebx,%edx,4),%ebx
		mov    0x300(%esp),%edx
		mov    0x300(%esp),%eax
		mov    0x3ac(%edx),%edx
		call   blockread_
		jmp    jump_fea25
	jump_fe9f5:
		mov    0x300(%esp),%edx
		movl   $0x1,0x370(%edx)
		jmp    jump_fea19
	jump_fea08:
		mov    0x300(%esp),%edx
		movl   $0x0,0x370(%edx)
	jump_fea19:
		mov    0x300(%esp),%eax
		call   gotoframe_
	jump_fea25:
		mov    0x300(%esp),%edx
		mov    0x300(%esp),%ebx
		mov    0x3b0(%edx),%edx
		mov    %edx,0x3c0(%ebx)
		mov    0x300(%esp),%esi
		mov    0x3bc(%ebx),%ebx
		add    0x370(%esi),%ebx
		mov    (%ebx),%al
		test   $0x1,%al
		je     jump_fea61
		xor    %ebx,%ebx
		mov    (%edx),%bl
		shl    $0x2,%ebx
		add    %ebx,%edx
	jump_fea61:
		test   $0x2,%al
		je     jump_fea69
		mov    %edx,%esi
		jmp    jump_fea6b
	jump_fea69:
		xor    %esi,%esi
	jump_fea6b:
		mov    0x300(%esp),%ebx
		mov    %esi,0x3c4(%ebx)
		test   %esi,%esi
		je     jump_fea7e
		add    (%edx),%edx
	jump_fea7e:
		test   $0x4,%al
		je     jump_fea86
		mov    %edx,%esi
		jmp    jump_fea88
	jump_fea86:
		xor    %esi,%esi
	jump_fea88:
		mov    0x300(%esp),%ebx
		mov    %esi,0x3c8(%ebx)
		test   %esi,%esi
		je     jump_fea9b
		add    (%edx),%edx
	jump_fea9b:
		test   $0x8,%al
		je     jump_feaa3
		mov    %edx,%esi
		jmp    jump_feaa5
	jump_feaa3:
		xor    %esi,%esi
	jump_feaa5:
		mov    0x300(%esp),%ebx
		mov    %esi,0x3cc(%ebx)
		test   %esi,%esi
		je     jump_feab8
		add    (%edx),%edx
	jump_feab8:
		test   $0x10,%al
		je     jump_feac0
		mov    %edx,%esi
		jmp    jump_feac2
	jump_feac0:
		xor    %esi,%esi
	jump_feac2:
		mov    0x300(%esp),%ebx
		mov    %esi,0x3d0(%ebx)
		test   %esi,%esi
		je     jump_fead5
		add    (%edx),%edx
	jump_fead5:
		test   $0x20,%al
		je     jump_feadd
		mov    %edx,%esi
		jmp    jump_feadf
	jump_feadd:
		xor    %esi,%esi
	jump_feadf:
		mov    0x300(%esp),%ebx
		mov    %esi,0x3d4(%ebx)
		test   %esi,%esi
		je     jump_feaf2
		add    (%edx),%edx
	jump_feaf2:
		test   $0x40,%al
		je     jump_feafa
		mov    %edx,%esi
		jmp    jump_feafc
	jump_feafa:
		xor    %esi,%esi
	jump_feafc:
		mov    0x300(%esp),%ebx
		mov    %esi,0x3d8(%ebx)
		test   %esi,%esi
		je     jump_feb0f
		add    (%edx),%edx
	jump_feb0f:
		test   $0x80,%al
		je     jump_feb17
		mov    %edx,%esi
		jmp    jump_feb19
	jump_feb17:
		xor    %esi,%esi
	jump_feb19:
		mov    0x300(%esp),%ebx
		mov    %esi,0x3dc(%ebx)
		test   %esi,%esi
		je     jump_feb2c
		add    (%edx),%edx
	jump_feb2c:
		mov    0x300(%esp),%ebx
		mov    %edx,0x3e0(%ebx)
		test   $0x1,%al
		je     jump_fecb0
		mov    0x300(%esp),%ebp
		mov    $0x300,%ecx
		mov    %esp,%edi
		mov    0x3b0(%ebx),%edx
		add    $0x6c,%ebp
		xor    %ebx,%ebx
		mov    %ebp,%esi
		mov    %ebx,0x30c(%esp)
		cld
		mov    %cl,%bl
		shr    $0x2,%ecx
		rep movsl %ds:(%esi),%es:(%edi)
		mov    %bl,%cl
		and    $0x3,%cl
		rep movsb %ds:(%esi),%es:(%edi)
		mov    %esp,%ebx
		inc    %edx
		mov    %ebx,0x304(%esp)
	jump_feb7c:
		mov    (%edx),%bh
		test   $0x80,%bh
		je     jump_febf3
		mov    %bh,%al
		and    $0x7f,%al
		inc    %al
		movzbl %al,%esi
		lea    (%esi,%esi,2),%esi
		mov    %esi,0x308(%esp)
		xor    %esi,%esi
		mov    0x30c(%esp),%si
		mov    0x304(%esp),%edi
		lea    (%esi,%esi,2),%esi
		mov    0x308(%esp),%ecx
		add    %edi,%esi
		mov    %ebp,%edi
		mov    %al,0x314(%esp)
		cld
		mov    %cl,%bl
		shr    $0x2,%ecx
		rep movsl %ds:(%esi),%es:(%edi)
		mov    %bl,%cl
		and    $0x3,%cl
		rep movsb %ds:(%esi),%es:(%edi)
		mov    0x308(%esp),%eax
		movzbw 0x314(%esp),%si
		add    %eax,%ebp
		mov    0x30c(%esp),%eax
		add    %esi,%eax
		inc    %edx
		mov    %eax,0x30c(%esp)
		jmp    jump_fec7b
	jump_febf3:
		test   $0x40,%bh
		je     jump_fec61
		mov    %bh,%al
		and    $0x3f,%al
		inc    %al
		movzbl %al,%esi
		lea    (%esi,%esi,2),%esi
		mov    %esi,0x308(%esp)
		movzbl 0x1(%edx),%esi
		mov    0x304(%esp),%ecx
		lea    (%esi,%esi,2),%esi
		mov    %ebp,%edi
		add    %ecx,%esi
		mov    0x308(%esp),%ecx
		mov    %al,0x310(%esp)
		cld
		mov    %cl,%bl
		shr    $0x2,%ecx
		rep movsl %ds:(%esi),%es:(%edi)
		mov    %bl,%cl
		and    $0x3,%cl
		rep movsb %ds:(%esi),%es:(%edi)
		mov    0x308(%esp),%esi
		mov    0x30c(%esp),%edi
		add    %esi,%ebp
		movzbw 0x310(%esp),%si
		add    %esi,%edi
		add    $0x2,%edx
		mov    %edi,0x30c(%esp)
		jmp    jump_fec7b
	jump_fec61:
		mov    0x30c(%esp),%ecx
		add    $0x3,%ebp
		mov    (%edx),%esi
		add    $0x3,%edx
		inc    %ecx
		mov    %esi,-0x3(%ebp)
		mov    %ecx,0x30c(%esp)
	jump_fec7b:
		cmpw   $0x100,0x30c(%esp)
		jb     jump_feb7c
		mov    0x300(%esp),%edx
		mov    0x300(%esp),%ebx
		mov    0x3b4(%edx),%edx
		cmp    0x370(%ebx),%edx
		je     jump_fecb0
		movl   $0x1,0x68(%ebx)
		jmp    jump_fecbe
	jump_fecb0:
		mov    0x300(%esp),%edx
		movl   $0x0,0x68(%edx)
	jump_fecbe:
		add    $0x318,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		pop    %edx
		pop    %ecx
		pop    %ebx
		ret


/*----------------------------------------------------------------*/
gotoframe_:
/*----------------------------------------------------------------*/
		push   %ebx
		push   %ecx
		push   %edx
		push   %esi
		push   %edi
		push   %ebp
		sub    $0x4,%esp
		mov    %eax,%ebp
		cmpl   $0x0,0x370(%eax)
		jne    jump_fedac
		lea    0x6c(%eax),%edi
		mov    $0x304,%ecx
		xor    %al,%al
		cld
		mov    %al,%ah
		mov    %ax,%bx
		shl    $0x10,%eax
		mov    %bx,%ax
		mov    %cl,%bl
		shr    $0x2,%ecx
		rep stos %eax,%es:(%edi)
		mov    %bl,%cl
		and    $0x3,%cl
		rep stos %al,%es:(%edi)
		mov    0x420(%ebp),%ebx
		cmp    $0xffffffff,%ebx
		je     jump_fedac
		mov    %ebx,%eax
		mov    0x404(%ebp,%eax,4),%eax
		cmpl   $0x0,0x28(%eax)
		je     jump_fedac
		mov    $0x1,%edx
		lea    (%ebx,%edx,1),%eax
		cmp    $0x7,%eax
		jae    jump_fed59
		lea    0x0(,%eax,4),%edi
		add    %ebp,%edi
		lea    0x1c(%ebp),%esi
	jump_fed47:
		cmpl   $0x0,0x404(%edi)
		je     jump_fed51
		inc    %edx
	jump_fed51:
		add    $0x4,%edi
		inc    %eax
		cmp    %esi,%edi
		jb     jump_fed47
	jump_fed59:
		cmp    _sounds,%edx
		jne    jump_fedac
		mov    %ebp,%edi
		lea    0x1c(%ebp),%eax
		mov    %eax,(%esp)
	jump_fed69:
		mov    0x404(%edi),%esi
		test   %esi,%esi
		je     jump_feda2
		push   %esi
		call   *EXPORT_SYMBOL(_LowSoundPurgeAddr)
		movl   $0x0,0x10(%esi)
		mov    (%esi),%eax
		movl   $0x0,0x28(%esi)
		mov    %eax,0xc(%esi)
		mov    %eax,0x8(%esi)
		mov    0x24(%esi),%edx
		mov    0x20(%esi),%eax
		movl   $0x0,0x20(%esi)
		sub    %eax,%edx
		mov    %edx,0x24(%esi)
	jump_feda2:
		mov    (%esp),%ecx
		add    $0x4,%edi
		cmp    %ecx,%edi
		jne    jump_fed69
	jump_fedac:
		mov    0x370(%ebp),%ebx
		xor    %esi,%esi
		xor    %edx,%edx
		test   %ebx,%ebx
		jbe    jump_fedd2
		mov    0x3b8(%ebp),%eax
	jump_fedc0:
		inc    %edx
		mov    (%eax),%ecx
		add    $0x4,%eax
		mov    0x370(%ebp),%edi
		add    %ecx,%esi
		cmp    %edi,%edx
		jb     jump_fedc0
	jump_fedd2:
		testb  $0x2,0x385(%ebp)
		je     jump_fedf0
		mov    0x3ac(%ebp),%eax
		add    %esi,%eax
		mov    %eax,0x3b0(%ebp)
		xor    %eax,%eax
		jmp    jump_fef2a
	jump_fedf0:
		mov    0x3a8(%ebp),%eax
		mov    0x444(%ebp),%edx
		add    %eax,%esi
		cmp    %edx,%esi
		jb     jump_fee62
		mov    0x43c(%ebp),%ebx
		lea    (%edx,%ebx,1),%eax
		cmp    %esi,%eax
		jb     jump_fee62
		mov    %esi,%eax
		sub    %edx,%eax
		sub    %eax,%ebx
		mov    0x434(%ebp),%ecx
		mov    %ebx,0x43c(%ebp)
		add    %eax,%ecx
		mov    0x430(%ebp),%edi
		mov    %ecx,0x434(%ebp)
		cmp    %edi,%ecx
		jb     jump_feee5
		mov    %ecx,%eax
		mov    0x42c(%ebp),%edx
		sub    %edi,%eax
		add    %eax,%edx
		mov    %edx,0x434(%ebp)
		mov    0x440(%ebp),%eax
		mov    0x42c(%ebp),%edx
		add    %eax,%edx
		mov    %edx,0x430(%ebp)
		jmp    jump_feee5
	jump_fee62:
		mov    0x42c(%ebp),%eax
		movl   $0x0,0x43c(%ebp)
		mov    %eax,0x438(%ebp)
		push   %esi
		mov    %eax,0x434(%ebp)
		mov    %eax,%edx
		mov    0x440(%ebp),%eax
		mov    0x394(%ebp),%ecx
		add    %eax,%edx
		push   %ecx
		mov    %edx,0x430(%ebp)
		call   ac_dos_low_level_seek
		mov    %esi,%eax
		add    $0x8,%esp
		and    $0xfff,%eax
		je     jump_feee5
		mov    $0x1000,%ebx
		mov    0x434(%ebp),%edx
		sub    %eax,%ebx
		mov    %ebp,%eax
		movl   $0x0,0x42c(%ebp)
		call   blockread_
		mov    0x438(%ebp),%edi
		mov    %eax,0x43c(%ebp)
		add    %eax,%edi
		mov    0x434(%ebp),%eax
		mov    %edi,0x438(%ebp)
		mov    %eax,0x42c(%ebp)
	jump_feee5:
		mov    0x385(%ebp),%dl
		mov    %esi,0x444(%ebp)
		test   $0x2,%dl
		je     jump_fef02
		xor    %eax,%eax
		add    $0x4,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		pop    %edx
		pop    %ecx
		pop    %ebx
		ret
	jump_fef02:
		mov    0x3ac(%ebp),%eax
		mov    %eax,0x3b0(%ebp)
		mov    0x370(%ebp),%edx
		mov    0x3b8(%ebp),%eax
		mov    (%eax,%edx,4),%ebx
		mov    %ebp,%eax
		mov    0x3ac(%ebp),%edx
		call   blockread_
	jump_fef2a:
		add    $0x4,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		pop    %edx
		pop    %ecx
		pop    %ebx
		ret


/*----------------------------------------------------------------*/
blockread_:
/*----------------------------------------------------------------*/
		push   %ecx
		push   %esi
		push   %edi
		push   %ebp
		sub    $0x18,%esp
		mov    %eax,%ebp
		mov    %edx,0x14(%esp)
		mov    %ebx,0xc(%esp)
		xor    %edx,%edx
		mov    %edx,0x10(%esp)
		mov    %edx,(%esp)
		call   *_SmackTimerReadAddr
		mov    0x42c(%ebp),%ecx
		mov    %eax,0x8(%esp)
		test   %ecx,%ecx
		jne    jump_fefde
		mov    %esp,%eax
		push   %eax
		mov    0x10(%esp),%esi
		push   %esi
		mov    %ds,%eax
		and    $0xffff,%eax
		push   %eax
		mov    0x20(%esp),%edi
		push   %edi
		mov    0x394(%ebp),%eax
		push   %eax
		call   ac_dos_low_level_read
		add    $0x14,%esp
		mov    (%esp),%eax
		mov    %eax,0x10(%esp)
		jmp    jump_ff1cd
	jump_fefde:
		cmpl   $0x0,0x43c(%ebp)
		je     jump_ff0c6
		mov    0x430(%ebp),%eax
		sub    0x434(%ebp),%eax
		mov    0xc(%esp),%ecx
		mov    %eax,0x4(%esp)
		cmp    %ecx,%eax
		jbe    jump_ff007
		mov    %ecx,0x4(%esp)
	jump_ff007:
		mov    0x4(%esp),%esi
		mov    0x43c(%ebp),%eax
		cmp    %esi,%eax
		jae    jump_ff019
		mov    %eax,0x4(%esp)
	jump_ff019:
		mov    0x4(%esp),%ecx
		mov    0x14(%esp),%edi
		mov    0x434(%ebp),%esi
		cld
		mov    %cl,%bl
		shr    $0x2,%ecx
		rep movsl %ds:(%esi),%es:(%edi)
		mov    %bl,%cl
		and    $0x3,%cl
		rep movsb %ds:(%esi),%es:(%edi)
		mov    0x4(%esp),%eax
		sub    %eax,0x43c(%ebp)
		mov    0x444(%ebp),%edx
		mov    0x4(%esp),%eax
		add    %eax,%edx
		mov    %edx,0x444(%ebp)
		mov    0x434(%ebp),%ebx
		add    0x4(%esp),%ebx
		mov    0x430(%ebp),%ecx
		mov    %ebx,0x434(%ebp)
		cmp    %ecx,%ebx
		jb     jump_ff09c
		mov    0x42c(%ebp),%eax
		mov    0x440(%ebp),%esi
		mov    %eax,0x434(%ebp)
		add    %esi,%eax
		mov    0x43c(%ebp),%esi
		mov    %eax,0x430(%ebp)
		test   %esi,%esi
		jne    jump_ff09c
		mov    0x434(%ebp),%eax
		mov    %eax,0x438(%ebp)
	jump_ff09c:
		mov    0x4(%esp),%eax
		mov    0x10(%esp),%edi
		mov    0xc(%esp),%edx
		mov    0x14(%esp),%ebx
		add    %eax,%edi
		sub    %eax,%edx
		add    %eax,%ebx
		mov    %edi,0x10(%esp)
		mov    %edx,0xc(%esp)
		mov    %ebx,0x14(%esp)
		test   %edx,%edx
		jne    jump_fefde
	jump_ff0c6:
		cmpl   $0x0,_sounds
	jump_ff0cd:
		je     jump_ff0d5
		call   *EXPORT_SYMBOL(_LowSoundCheckAddr)
	jump_ff0d5:
		mov    0xc(%esp),%edi
		cmp    $0x1000,%edi
		jbe    jump_ff163
		cmp    $0x4000,%edi
		jbe    jump_ff0f4
		mov    $0x4000,%eax
		jmp    jump_ff0fc
	jump_ff0f4:
		mov    %edi,%eax
		shr    $0xc,%eax
		shl    $0xc,%eax
	jump_ff0fc:
		lea    0x4(%esp),%esi
		push   %esi
		mov    %eax,0x8(%esp)
		push   %eax
		mov    %ds,%eax
		and    $0xffff,%eax
		push   %eax
		mov    0x20(%esp),%edi
		push   %edi
		mov    0x394(%ebp),%eax
		push   %eax
		call   ac_dos_low_level_read
		add    $0x14,%esp
		mov    0x4(%esp),%eax
		mov    0xc(%esp),%edx
		mov    0x10(%esp),%ecx
		mov    (%esp),%esi
		sub    %eax,%edx
		lea    (%edi,%eax,1),%ebx
		add    %eax,%ecx
		add    %eax,%esi
		mov    %edx,0xc(%esp)
		mov    %esi,(%esp)
		mov    %ebx,0x14(%esp)
		mov    0x444(%ebp),%edi
		mov    %ecx,0x10(%esp)
		add    %eax,%edi
		mov    _sounds,%eax
		mov    %edi,0x444(%ebp)
		test   %eax,%eax
		jmp    jump_ff0cd
	jump_ff163:
		test   %edi,%edi
		je     jump_ff1cd
		lea    0xfff(%edi),%eax
		shr    $0xc,%eax
		shl    $0xc,%eax
		mov    %eax,0x4(%esp)
		lea    0x4(%esp),%eax
		push   %eax
		mov    0x8(%esp),%edx
		mov    0x42c(%ebp),%esi
		push   %edx
		mov    %ds,%eax
		and    $0xffff,%eax
		push   %eax
		push   %esi
		mov    0x394(%ebp),%ebx
		push   %ebx
		call   ac_dos_low_level_read
		add    $0x14,%esp
		mov    0x4(%esp),%eax
		add    %eax,(%esp)
		mov    0x42c(%ebp),%eax
		mov    %eax,0x434(%ebp)
		mov    0x4(%esp),%ebx
		add    %eax,%ebx
		mov    %ebx,0x438(%ebp)
		mov    0x4(%esp),%eax
		mov    %eax,0x43c(%ebp)
		jmp    jump_fefde
	jump_ff1cd:
		mov    (%esp),%eax
		mov    0x448(%ebp),%edx
		add    %eax,%edx
		mov    0x4a0(%ebp),%ebx
		mov    %edx,0x448(%ebp)
		test   %ebx,%ebx
		je     jump_ff20a
		mov    $0x3e8,%ecx
		mov    (%esp),%eax
		mul    %ecx
		div    %ebx
		mov    0x8(%esp),%ebx
		add    %eax,%ebx
		mov    %ebx,(%esp)
	jump_ff1fd:
		call   *_SmackTimerReadAddr
		cmp    (%esp),%eax
		jb     jump_ff1fd
		jmp    jump_ff210
	jump_ff20a:
		call   *_SmackTimerReadAddr
	jump_ff210:
		mov    0x8(%esp),%esi
		mov    0x44c(%ebp),%edi
		sub    %esi,%eax
		add    %eax,%edi
		mov    0x10(%esp),%eax
		mov    %edi,0x44c(%ebp)
		add    $0x18,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		pop    %ecx
		ret


/*----------------------------------------------------------------*/
backgroundload_:
/*----------------------------------------------------------------*/
		push   %ebx
		push   %ecx
		push   %edx
		push   %esi
		push   %edi
		push   %ebp
		sub    $0x4,%esp
		mov    %eax,%esi
		xor    %edx,%edx
		mov    %edx,(%esp)
		mov    0x370(%eax),%eax
		cmp    0xc(%esi),%eax
		jae    jump_ff332
		mov    0x440(%esi),%eax
		sub    0x43c(%esi),%eax
		cmp    $0x1000,%eax
		jl     jump_ff332
		call   *_SmackTimerReadAddr
		mov    %eax,%ebp
		mov    %esp,%eax
		push   %eax
		mov    0x438(%esi),%ebx
		push   $0x1000
		mov    %ds,%eax
		and    $0xffff,%eax
		push   %eax
		push   %ebx
		mov    0x394(%esi),%edi
		push   %edi
		call   ac_dos_low_level_read
		add    $0x14,%esp
		mov    0x43c(%esi),%edx
		mov    (%esp),%eax
		add    %eax,%edx
		mov    %edx,0x43c(%esi)
		mov    0x438(%esi),%ebx
		add    (%esp),%ebx
		mov    0x430(%esi),%ecx
		mov    %ebx,%eax
		mov    %ebx,0x438(%esi)
		cmp    %ecx,%ebx
		jbe    jump_ff2d2
		mov    0x42c(%esi),%eax
		mov    %ebx,0x430(%esi)
		mov    %eax,0x438(%esi)
	jump_ff2d2:
		mov    0x43c(%esi),%eax
		cmp    0x458(%esi),%eax
		jbe    jump_ff2e6
		mov    %eax,0x458(%esi)
	jump_ff2e6:
		mov    (%esp),%eax
		mov    0x450(%esi),%edx
		add    %eax,%edx
		mov    0x4a0(%esi),%ebx
		mov    %edx,0x450(%esi)
		test   %ebx,%ebx
		je     jump_ff31c
		mov    $0x3e8,%ecx
		mov    (%esp),%eax
		mul    %ecx
		div    %ebx
		lea    (%eax,%ebp,1),%edi
	jump_ff310:
		call   *_SmackTimerReadAddr
		cmp    %edi,%eax
		jb     jump_ff310
		jmp    jump_ff322
	jump_ff31c:
		call   *_SmackTimerReadAddr
	jump_ff322:
		mov    0x454(%esi),%ecx
		sub    %ebp,%eax
		add    %eax,%ecx
		mov    %ecx,0x454(%esi)
	jump_ff332:
		mov    (%esp),%eax
		add    $0x4,%esp
		pop    %ebp
		pop    %edi
		pop    %esi
		pop    %edx
		pop    %ecx
		pop    %ebx
		ret


/*----------------------------------------------------------------*/
smkmalloc_:
/*----------------------------------------------------------------*/
		push   %ebx
		push   %ecx
		mov    0x45c(%eax),%ebx
		add    %edx,%ebx
		mov    0x49c(%eax),%ecx
		mov    %ebx,0x45c(%eax)
		cmp    %ecx,%ebx
		jbe    jump_ff360
		mov    %ebx,0x49c(%eax)
	jump_ff360:
		push   %edx
		call   RADMALLOC
		pop    %ecx
		pop    %ebx
		ret


/*----------------------------------------------------------------*/
DEFSMACKTIMERSETUP:	/* 10f110 */
/*----------------------------------------------------------------*/
		mov    $DEFSMACKTIMERREAD,%edx
		mov    $0x46c,%eax
		mov    $__nullsub_12,%ebx
		mov    %edx,_SmackTimerReadAddr

		/* XXX: mov    (%eax),%eax */
		call   ac_timer_get_18_2_hz_ticks

		mov    %ebx,_SmackTimerDoneAddr
		mov    %eax,%ecx
		mov    %eax,_timeradjust
		neg    %ecx
		xor    %ebx,%ebx
		mov    %ecx,_timeradjust
/* XXX: cut out */
#if 0
		mov    $0x34,%al
		out    %al,$0x43
		jmp    jump_10f144
	jump_10f144:
		mov    %bl,%al
		out    %al,$0x40
		jmp    jump_10f14a
	jump_10f14a:
		mov    %bh,%al
		out    %al,$0x40
#endif
		ret


/*----------------------------------------------------------------*/
__nullsub_12:	/* 0x10f150 */
/*----------------------------------------------------------------*/
		ret


/*----------------------------------------------------------------*/
DEFSMACKTIMERREAD:
/*----------------------------------------------------------------*/
		mov    $0x46c,%eax
		mov    data_1ed5e4,%edx

		/* mov    (%eax),%eax */
		call   ac_timer_get_18_2_hz_ticks

		cmp    %edx,%eax
		jae    jump_10f181
		mov    _timeradjust,%ebx
		sub    %eax,%edx
		add    %edx,%ebx
		mov    %ebx,_timeradjust
	jump_10f181:
		mov    $0x32,%ebx
		mov    _timeradjust,%ecx
		mov    %eax,data_1ed5e4
		add    %ecx,%eax
		mov    $0xaba,%ecx
		mul    %ecx
		div    %ebx
		ret


.data

_smack_malloc:
		.long   ac_LbMemoryAlloc
_smack_free:
		.long   LbMemoryFree_

data_159800:
		.long	0x0
data_159804:
		.long	0x0
data_159808:
		.long	0x0
data_15980c:
		.long	0x0
data_159810:
		.long	0x0
data_159814:
		.long	0x0
data_159818:
		.long	0x0
data_15981c:
		.long	0x0
data_159820:
		.long	0x0
data_159824:
		.long	0x0
data_159828:
		.long	0x0
data_15982c:
		.long	0x0
data_159830:
		.long	0x0
data_159834:
		.long	0x0
data_159838:
		.long	0x0
data_15983c:
		.long	0x0
data_159840:
		.long	0x0
data_159844:
		.long	0x0
data_159848:
		.long	0x0
data_15984c:
		.long	0x0
data_159850:
		.long	0x0
data_159854:
		.long	0x0
data_159858:
		.long	0x0
data_15985c:
		.long	0x0
data_159860:
		.long	0x0
data_159864:
		.long	0x0
data_159868:
		.long	0x0
data_15986c:
		.long	0x0
data_159870:
		.long	0x0
data_159874:
		.long	0x0
data_159878:
		.fill   0x8
data_159880:
		.long	0x0
data_159884:
		.long	0x0
data_159888:
		.long	0x0
data_15988c:
		.long	0x0
data_159890:
		.long	0x0
data_159894:
		.long	0x0
data_159898:
		.long	0x0
data_15989c:
		.long	0x0
data_1598a0:
		.long	0x0
data_1598a4:
		.long	0x0
data_1598a8:
		.long	0x0
data_1598ac:
		.long	0x0
data_1598b0:
		.long	0x0
data_1598b4:
		.fill   0xc
data_1598c0:
		.fill   0x10
data_1598d0:
		.fill   0x10
data_1598e0:
		.ascii  "\x01\x00\x00\x00\x02\x00\x00\x00"
		.ascii  "\x03\x00\x00\x00\x04\x00\x00\x00"
		.ascii  "\x05\x00\x00\x00\x06\x00\x00\x00"
		.ascii  "\x07\x00\x00\x00\x08\x00\x00\x00"
		.ascii  "\x09\x00\x00\x00\x0a\x00\x00\x00"
		.ascii  "\x0b\x00\x00\x00\x0c\x00\x00\x00"
		.ascii  "\x0d\x00\x00\x00\x0e\x00\x00\x00"
		.ascii  "\x0f\x00\x00\x00\x10\x00\x00\x00"
		.ascii  "\x11\x00\x00\x00\x12\x00\x00\x00"
		.ascii  "\x13\x00\x00\x00\x14\x00\x00\x00"
		.ascii  "\x15\x00\x00\x00\x16\x00\x00\x00"
		.ascii  "\x17\x00\x00\x00\x18\x00\x00\x00"
		.ascii  "\x19\x00\x00\x00\x1a\x00\x00\x00"
		.ascii  "\x1b\x00\x00\x00\x1c\x00\x00\x00"
		.ascii  "\x1d\x00\x00\x00\x1e\x00\x00\x00"
		.ascii  "\x1f\x00\x00\x00\x20\x00\x00\x00"
		.ascii  "\x21\x00\x00\x00\x22\x00\x00\x00"
		.ascii  "\x23\x00\x00\x00\x24\x00\x00\x00"
		.ascii  "\x25\x00\x00\x00\x26\x00\x00\x00"
		.ascii  "\x27\x00\x00\x00\x28\x00\x00\x00"
		.ascii  "\x29\x00\x00\x00\x2a\x00\x00\x00"
		.ascii  "\x2b\x00\x00\x00\x2c\x00\x00\x00"
		.ascii  "\x2d\x00\x00\x00\x2e\x00\x00\x00"
		.ascii  "\x2f\x00\x00\x00\x30\x00\x00\x00"
		.ascii  "\x31\x00\x00\x00\x32\x00\x00\x00"
		.ascii  "\x33\x00\x00\x00\x34\x00\x00\x00"
		.ascii  "\x35\x00\x00\x00\x36\x00\x00\x00"
		.ascii  "\x37\x00\x00\x00\x38\x00\x00\x00"
		.ascii  "\x39\x00\x00\x00\x3a\x00\x00\x00"
		.ascii  "\x3b\x00\x00\x00\x80"
		.long	0x0
		.ascii  "\x01\x00\x00\x00\x02\x00\x00\x00"
		.ascii  "\x04\x00\x00\x00\x08\x00\x00"


data_1599e0:
		.short  0x0
data_1599e2:
		.short  0x0
data_1599e4:
		.fill   0xc

data_1599f0:
		.long	0x0
data_1599f4:
		.long	0x0
data_1599f8:
		.long	0x0
data_1599fc:
		.long	0x0
data_159a00:
		.long   func_13a660
		.long   func_13a66c
		.long   func_13a678
		.long   func_13a684
		.long   func_13a690
		.long   func_13a6a0
		.long   func_13a6b0
		.long   func_13a6c0
		.long   func_13a6d0
		.long   func_13a6dc
		.long   func_13a6e8
		.long   func_13a6f4
		.long   func_13a700
		.long   func_13a710
		.long   func_13a720
		.long   func_13a730
		.long   func_13a740
		.long   func_13a74c
		.long   func_13a758
		.long   func_13a768
		.long   func_13a774
		.long   func_13a784
		.long   func_13a794
		.long   func_13a7a4
		.long   func_13a7b4
		.long   func_13a7c0
		.long   func_13a7cc
		.long   func_13a7d8
		.long   func_13a7e4
		.long   func_13a7f4
		.long   func_13a804
		.long   func_13a814
		.long   func_13a824
		.long   func_13a830
		.long   func_13a840
		.long   func_13a84c
		.long   func_13a858
		.long   func_13a868
		.long   func_13a878
		.long   func_13a888
		.long   func_13a898
		.long   func_13a8a4
		.long   func_13a8b0
		.long   func_13a8bc
		.long   func_13a8c8
		.long   func_13a8d8
		.long   func_13a8e8
		.long   func_13a8f8
		.long   func_13a908
		.long   func_13a914
		.long   func_13a920
		.long   func_13a92c
		.long   func_13a938
		.long   func_13a948
		.long   func_13a958
		.long   func_13a968
		.long   func_13a978
		.long   func_13a984
		.long   func_13a990
		.long   func_13a99c
		.long   func_13a9a8
		.long   func_13a9b8
		.long   func_13a9c8
		.long   func_13a9d8
		.long   func_13a9e8
		.long   func_13a9f8
		.long   func_13aa08
		.long   func_13aa18
		.long   func_13aa28
		.long   func_13aa34
		.long   func_13aa40
		.long   func_13aa50
		.long   func_13aa5c
		.long   func_13aa68
		.long   func_13aa74
		.long   func_13aa80
		.long   func_13aa8c
		.long   func_13aa9c
		.long   func_13aaac
		.long   func_13aabc
		.long   func_13aacc
		.long   func_13aadc
		.long   func_13aaec
		.long   func_13aafc
		.long   func_13ab0c
		.long   func_13ab18
		.long   func_13ab20
		.long   func_13ab2c
		.long   func_13ab38
		.long   func_13ab44
		.long   func_13ab50
		.long   func_13ab58
		.long   func_13ab64
		.long   func_13ab74
		.long   func_13ab84
		.long   func_13ab94
		.long   func_13aba4
		.long   func_13abb4
		.long   func_13abc4
		.long   func_13abd4
		.long   func_13abe4
		.long   func_13abf4
		.long   func_13ac00
		.long   func_13ac0c
		.long   func_13ac1c
		.long   func_13ac2c
		.long   func_13ac38
		.long   func_13ac44
		.long   func_13ac54
		.long   func_13ac64
		.long   func_13ac74
		.long   func_13ac84
		.long   func_13ac94
		.long   func_13aca4
		.long   func_13acb4
		.long   func_13acc4
		.long   func_13acd4
		.long   func_13ace0
		.long   func_13acec
		.long   func_13acfc
		.long   func_13ad08
		.long   func_13ad14
		.long   func_13ad20
		.long   func_13ad2c
		.long   func_13ad38
		.long   func_13ad48
		.long   func_13ad58
		.long   func_13ad68
		.long   func_13ad78
		.long   func_13ad84
		.long   func_13ad90
		.long   func_13ad9c
		.long   func_13ada8
		.long   func_13adb4
		.long   func_13adc0
		.long   func_13add0
		.long   func_13addc
		.long   func_13ade4
		.long   func_13adf0
		.long   func_13adf8
		.long   func_13ae00
		.long   func_13ae0c
		.long   func_13ae18
		.long   func_13ae24
		.long   func_13ae30
		.long   func_13ae3c
		.long   func_13ae4c
		.long   func_13ae58
		.long   func_13ae64
		.long   func_13ae74
		.long   func_13ae80
		.long   func_13ae8c
		.long   func_13ae9c
		.long   func_13aea8
		.long   func_13aeb4
		.long   func_13aec0
		.long   func_13aecc
		.long   func_13aed8
		.long   func_13aee8
		.long   func_13aef4
		.long   func_13af00
		.long   func_13af0c
		.long   func_13af18
		.long   func_13af24
		.long   func_13af30
		.long   func_13af3c
		.long   func_13af44
		.long   func_13af50
		.long   func_13af5c
		.long   func_13af64
		.long   func_13af70
		.long   func_13af78
		.long   func_13af80
		.long   func_13af8c
		.long   func_13af98
		.long   func_13afa4
		.long   func_13afb0
		.long   func_13afbc
		.long   func_13afc8
		.long   func_13afd4
		.long   func_13afe0
		.long   func_13afec
		.long   func_13aff8
		.long   func_13b008
		.long   func_13b014
		.long   func_13b01c
		.long   func_13b028
		.long   func_13b030
		.long   func_13b038
		.long   func_13b044
		.long   func_13b050
		.long   func_13b05c
		.long   func_13b068
		.long   func_13b078
		.long   func_13b088
		.long   func_13b098
		.long   func_13b0a8
		.long   func_13b0b8
		.long   func_13b0c8
		.long   func_13b0d8
		.long   func_13b0e8
		.long   func_13b0f4
		.long   func_13b100
		.long   func_13b10c
		.long   func_13b118
		.long   func_13b124
		.long   func_13b130
		.long   func_13b13c
		.long   func_13b148
		.long   func_13b158
		.long   func_13b168
		.long   func_13b178
		.long   func_13b188
		.long   func_13b198
		.long   func_13b1a8
		.long   func_13b1b8
		.long   func_13b1c8
		.long   func_13b1d4
		.long   func_13b1e0
		.long   func_13b1ec
		.long   func_13b1f8
		.long   func_13b204
		.long   func_13b210
		.long   func_13b220
		.long   func_13b22c
		.long   func_13b23c
		.long   func_13b24c
		.long   func_13b25c
		.long   func_13b26c
		.long   func_13b27c
		.long   func_13b28c
		.long   func_13b29c
		.long   func_13b2ac
		.long   func_13b2b8
		.long   func_13b2c4
		.long   func_13b2d0
		.long   func_13b2dc
		.long   func_13b2e8
		.long   func_13b2f8
		.long   func_13b304
		.long   func_13b310
		.long   func_13b320
		.long   func_13b330
		.long   func_13b340
		.long   func_13b350
		.long   func_13b360
		.long   func_13b370
		.long   func_13b380
		.long   func_13b390
		.long   func_13b39c
		.long   func_13b3a8
		.long   func_13b3b4
		.long   func_13b3c0
		.long   func_13b3cc
		.long   func_13b3d8
		.long   func_13b3e4


GLOBAL (_SmackTimerReadAddr)	/* 0x159780 */
		.long	0x0
GLOBAL (_SmackTimerSetupAddr)
		.long   DEFSMACKTIMERSETUP
_SmackTimerDoneAddr:
		.long	0x0

_LowSoundOpenAddr:
		.long	0x0
_LowSoundOffAddr:
		.long	0x0

_sounds:
		.long	0x0
_trackbuf:
		.long	0x0

data_1592e8:
		.long	0x0
data_1592ec:
		.long	0x0
data_1592f8:
		.long	0x0
data_1592fc:
		.long	0x0

data_159e00:
		.long	0x0
data_159e04:
		.long	0x0
data_159e08:
		.long	0x0
data_159e0c:
		.long	0x0
data_159e10:
		.long	0x0
data_159e14:
		.fill   0xc
data_159e20:
		.long	0x0
data_159e24:
		.long	0x0
data_159e28:
		.long	0x0
data_159e2c:
		.long	0x0
data_159e30:
		.fill   0x10

data_1e56dc:
		.fill   0x350
data_1e5a2c:
		.long	0x0
_timeradjust:
		.long	0x0
data_1ed5e4:
		.long	0x0

