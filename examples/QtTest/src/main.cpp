   1              		.file	"main.cpp"
   2              		.section	.rodata.str1.1,"aMS",@progbits,1
   3              	.LC0:
   4 0000 48656C6C 		.string	"Hello, world!"
   4      6F2C2077 
   4      6F726C64 
   4      2100
   5              		.section	.text.unlikely,"ax",@progbits
   6              	.LCOLDB1:
   7              		.section	.text.startup,"ax",@progbits
   8              	.LHOTB1:
   9              		.p2align 4,,15
  10              		.globl	main
  12              	main:
  13              	.LFB16176:
  14              		.cfi_startproc
  15 0000 4154     		pushq	%r12
  16              		.cfi_def_cfa_offset 16
  17              		.cfi_offset 12, -16
  18 0002 55       		pushq	%rbp
  19              		.cfi_def_cfa_offset 24
  20              		.cfi_offset 6, -24
  21 0003 4889F2   		movq	%rsi, %rdx
  22 0006 53       		pushq	%rbx
  23              		.cfi_def_cfa_offset 32
  24              		.cfi_offset 3, -32
  25 0007 B9010505 		movl	$328961, %ecx
  25      00
  26 000c 4883EC70 		subq	$112, %rsp
  27              		.cfi_def_cfa_offset 144
  28 0010 488D6C24 		leaq	32(%rsp), %rbp
  28      20
  29 0015 488D7424 		leaq	12(%rsp), %rsi
  29      0C
  30 001a 897C240C 		movl	%edi, 12(%rsp)
  31 001e 64488B04 		movq	%fs:40, %rax
  31      25280000 
  31      00
  32 0027 48894424 		movq	%rax, 104(%rsp)
  32      68
  33 002c 31C0     		xorl	%eax, %eax
  34 002e 4889EF   		movq	%rbp, %rdi
  35 0031 488D5C24 		leaq	48(%rsp), %rbx
  35      30
  36 0036 E8000000 		call	_ZN12QApplicationC1ERiPPci@PLT
  36      00
  37 003b 488D3D00 		leaq	.LC0(%rip), %rdi
  37      000000
  38 0042 BE0D0000 		movl	$13, %esi
  38      00
  39 0047 E8000000 		call	_ZN7QString16fromAscii_helperEPKci@PLT
  39      00
  40 004c 488D7424 		leaq	16(%rsp), %rsi
  40      10
  41 0051 31C9     		xorl	%ecx, %ecx
  42 0053 31D2     		xorl	%edx, %edx
  43 0055 4889DF   		movq	%rbx, %rdi
  44 0058 48894424 		movq	%rax, 16(%rsp)
  44      10
  45 005d E8000000 		call	_ZN6QLabelC1ERK7QStringP7QWidget6QFlagsIN2Qt10WindowTypeEE@PLT
  45      00
  46 0062 488B7C24 		movq	16(%rsp), %rdi
  46      10
  47 0067 8B07     		movl	(%rdi), %eax
  48 0069 85C0     		testl	%eax, %eax
  49 006b 754B     		jne	.L2
  50              	.L6:
  51 006d BA080000 		movl	$8, %edx
  51      00
  52 0072 BE020000 		movl	$2, %esi
  52      00
  53 0077 E8000000 		call	_ZN10QArrayData10deallocateEPS_mm@PLT
  53      00
  54              	.L3:
  55 007c 4889DF   		movq	%rbx, %rdi
  56 007f E8000000 		call	_ZN7QWidget4showEv@PLT
  56      00
  57 0084 E8000000 		call	_ZN12QApplication4execEv@PLT
  57      00
  58 0089 4889DF   		movq	%rbx, %rdi
  59 008c 4189C4   		movl	%eax, %r12d
  60 008f E8000000 		call	_ZN6QLabelD1Ev@PLT
  60      00
  61 0094 4889EF   		movq	%rbp, %rdi
  62 0097 E8000000 		call	_ZN12QApplicationD1Ev@PLT
  62      00
  63 009c 488B4C24 		movq	104(%rsp), %rcx
  63      68
  64 00a1 6448330C 		xorq	%fs:40, %rcx
  64      25280000 
  64      00
  65 00aa 4489E0   		movl	%r12d, %eax
  66 00ad 7520     		jne	.L10
  67 00af 4883C470 		addq	$112, %rsp
  68              		.cfi_remember_state
  69              		.cfi_def_cfa_offset 32
  70 00b3 5B       		popq	%rbx
  71              		.cfi_def_cfa_offset 24
  72 00b4 5D       		popq	%rbp
  73              		.cfi_def_cfa_offset 16
  74 00b5 415C     		popq	%r12
  75              		.cfi_def_cfa_offset 8
  76 00b7 C3       		ret
  77              	.L2:
  78              		.cfi_restore_state
  79 00b8 83C001   		addl	$1, %eax
  80 00bb 74BF     		je	.L3
  81              	#APP
  82              	# 219 "/usr/include/x86_64-linux-gnu/qt5/QtCore/qatomic_x86.h" 1
   1              	/****************************************************************************
   2              	**
   3              	** Copyright (C) 2015 The Qt Company Ltd.
   4              	** Copyright (C) 2011 Thiago Macieira <thiago@kde.org>
   5              	** Contact: http://www.qt.io/licensing/
   6              	**
   7              	** This file is part of the QtCore module of the Qt Toolkit.
   8              	**
   9              	** $QT_BEGIN_LICENSE:LGPL21$
  10              	** Commercial License Usage
  11              	** Licensees holding valid commercial Qt licenses may use this file in
  12              	** accordance with the commercial license agreement provided with the
  13              	** Software or, alternatively, in accordance with the terms contained in
  14              	** a written agreement between you and The Qt Company. For licensing terms
  15              	** and conditions see http://www.qt.io/terms-conditions. For further
  16              	** information use the contact form at http://www.qt.io/contact-us.
  17              	**
  18              	** GNU Lesser General Public License Usage
  19              	** Alternatively, this file may be used under the terms of the GNU Lesser
  20              	** General Public License version 2.1 or version 3 as published by the Free
  21              	** Software Foundation and appearing in the file LICENSE.LGPLv21 and
  22              	** LICENSE.LGPLv3 included in the packaging of this file. Please review the
  23              	** following information to ensure the GNU Lesser General Public License
  24              	** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
  25              	** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
  26              	**
  27              	** As a special exception, The Qt Company gives you certain additional
  28              	** rights. These rights are described in The Qt Company LGPL Exception
  29              	** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
  30              	**
  31              	** $QT_END_LICENSE$
  32              	**
  33              	****************************************************************************/
  34              	
  35              	#ifndef QATOMIC_X86_H
  36              	#define QATOMIC_X86_H
  37              	
  38              	#include <QtCore/qgenericatomic.h>
  39              	
  40              	QT_BEGIN_NAMESPACE
  41              	
  42              	#if 0
  43              	// silence syncqt warnings
  44              	QT_END_NAMESPACE
  45              	#pragma qt_sync_skip_header_check
  46              	#pragma qt_sync_stop_processing
  47              	#endif
  48              	
  49              	#define Q_ATOMIC_INT_REFERENCE_COUNTING_IS_ALWAYS_NATIVE
  50              	#define Q_ATOMIC_INT_REFERENCE_COUNTING_IS_WAIT_FREE
  51              	
  52              	#define Q_ATOMIC_INT_TEST_AND_SET_IS_ALWAYS_NATIVE
  53              	#define Q_ATOMIC_INT_TEST_AND_SET_IS_WAIT_FREE
  54              	
  55              	#define Q_ATOMIC_INT_FETCH_AND_STORE_IS_ALWAYS_NATIVE
  56              	#define Q_ATOMIC_INT_FETCH_AND_STORE_IS_WAIT_FREE
  57              	
  58              	#define Q_ATOMIC_INT_FETCH_AND_ADD_IS_ALWAYS_NATIVE
  59              	#define Q_ATOMIC_INT_FETCH_AND_ADD_IS_WAIT_FREE
  60              	
  61              	#define Q_ATOMIC_INT32_IS_SUPPORTED
  62              	
  63              	#define Q_ATOMIC_INT32_REFERENCE_COUNTING_IS_ALWAYS_NATIVE
  64              	#define Q_ATOMIC_INT32_REFERENCE_COUNTING_IS_WAIT_FREE
  65              	
  66              	#define Q_ATOMIC_INT32_TEST_AND_SET_IS_ALWAYS_NATIVE
  67              	#define Q_ATOMIC_INT32_TEST_AND_SET_IS_WAIT_FREE
  68              	
  69              	#define Q_ATOMIC_INT32_FETCH_AND_STORE_IS_ALWAYS_NATIVE
  70              	#define Q_ATOMIC_INT32_FETCH_AND_STORE_IS_WAIT_FREE
  71              	
  72              	#define Q_ATOMIC_INT32_FETCH_AND_ADD_IS_ALWAYS_NATIVE
  73              	#define Q_ATOMIC_INT32_FETCH_AND_ADD_IS_WAIT_FREE
  74              	
  75              	#define Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
  76              	#define Q_ATOMIC_POINTER_TEST_AND_SET_IS_WAIT_FREE
  77              	
  78              	#define Q_ATOMIC_POINTER_FETCH_AND_STORE_IS_ALWAYS_NATIVE
  79              	#define Q_ATOMIC_POINTER_FETCH_AND_STORE_IS_WAIT_FREE
  80              	
  81              	#define Q_ATOMIC_POINTER_FETCH_AND_ADD_IS_ALWAYS_NATIVE
  82              	#define Q_ATOMIC_POINTER_FETCH_AND_ADD_IS_WAIT_FREE
  83              	
  84              	template <int size> struct QBasicAtomicOps: QGenericAtomicOps<QBasicAtomicOps<size> >
  85              	{
  86              	    static inline Q_DECL_CONSTEXPR bool isReferenceCountingNative() Q_DECL_NOTHROW { return true; }
  87              	    static inline Q_DECL_CONSTEXPR bool isReferenceCountingWaitFree() Q_DECL_NOTHROW { return true;
  88              	    template <typename T> static bool ref(T &_q_value) Q_DECL_NOTHROW;
  89              	    template <typename T> static bool deref(T &_q_value) Q_DECL_NOTHROW;
  90              	
  91              	    static inline Q_DECL_CONSTEXPR bool isTestAndSetNative() Q_DECL_NOTHROW { return true; }
  92              	    static inline Q_DECL_CONSTEXPR bool isTestAndSetWaitFree() Q_DECL_NOTHROW { return true; }
  93              	    template <typename T> static bool testAndSetRelaxed(T &_q_value, T expectedValue, T newValue) Q
  94              	    template <typename T> static bool
  95              	    testAndSetRelaxed(T &_q_value, T expectedValue, T newValue, T *currentValue) Q_DECL_NOTHROW;
  96              	
  97              	    static inline Q_DECL_CONSTEXPR bool isFetchAndStoreNative() Q_DECL_NOTHROW { return true; }
  98              	    static inline Q_DECL_CONSTEXPR bool isFetchAndStoreWaitFree() Q_DECL_NOTHROW { return true; }
  99              	    template <typename T> static T fetchAndStoreRelaxed(T &_q_value, T newValue) Q_DECL_NOTHROW;
 100              	
 101              	    static inline Q_DECL_CONSTEXPR bool isFetchAndAddNative() Q_DECL_NOTHROW { return true; }
 102              	    static inline Q_DECL_CONSTEXPR bool isFetchAndAddWaitFree() Q_DECL_NOTHROW { return true; }
 103              	    template <typename T> static
 104              	    T fetchAndAddRelaxed(T &_q_value, typename QAtomicAdditiveType<T>::AdditiveT valueToAdd) Q_DECL
 105              	};
 106              	
 107              	template <typename T> struct QAtomicOps : QBasicAtomicOps<sizeof(T)>
 108              	{
 109              	    typedef T Type;
 110              	};
 111              	
 112              	#if defined(Q_CC_GNU)
 113              	
 114              	template<> struct QAtomicOpsSupport<1> { enum { IsSupported = 1 }; };
 115              	template<> struct QAtomicOpsSupport<2> { enum { IsSupported = 1 }; };
 116              	template<> struct QAtomicOpsSupport<8> { enum { IsSupported = 1 }; };
 117              	
 118              	/*
 119              	 * Guide for the inline assembly below:
 120              	 *
 121              	 * x86 instructions are in the form "{opcode}{length} {source}, {destination}",
 122              	 * where the length is one of the letters "b" (byte), "w" (word, 16-bit), "l"
 123              	 * (dword, 32-bit), "q" (qword, 64-bit).
 124              	 *
 125              	 * In most cases, we can omit the length because it's inferred from one of the
 126              	 * registers. For example, "xchg %0,%1" doesn't need the length suffix because
 127              	 * we can only exchange data of the same size and one of the operands must be a
 128              	 * register.
 129              	 *
 130              	 * The exception is the increment and decrement functions, where we add and
 131              	 * subtract an immediate value (1). For those, we need to specify the length.
 132              	 * GCC and ICC support the syntax "add%z0 $1, %0", where "%z0" expands to the
 133              	 * length of the operand. Unfortunately, clang as of 3.0 doesn't support that.
 134              	 * For that reason, the ref() and deref() functions are rolled out for all
 135              	 * sizes.
 136              	 *
 137              	 * The functions are also rolled out for the 1-byte operations since those
 138              	 * require a special register constraint "q" to force the compiler to schedule
 139              	 * one of the 8-bit registers. It's probably a compiler bug that it tries to
 140              	 * use a register that doesn't exist.
 141              	 *
 142              	 * Finally, 64-bit operations are supported via the cmpxchg8b instruction on
 143              	 * 32-bit processors, via specialisation below.
 144              	 */
 145              	
 146              	template<> template<typename T> inline
 147              	bool QBasicAtomicOps<1>::ref(T &_q_value) Q_DECL_NOTHROW
 148              	{
 149              	    unsigned char ret;
 150              	    asm volatile("lock\n"
 151              	                 "addb  $1, %0\n"
 152              	                 "setne %1"
 153              	                 : "=m" (_q_value), "=qm" (ret)
 154              	                 : "m" (_q_value)
 155              	                 : "memory");
 156              	    return ret != 0;
 157              	}
 158              	
 159              	template<> template<typename T> inline
 160              	bool QBasicAtomicOps<2>::ref(T &_q_value) Q_DECL_NOTHROW
 161              	{
 162              	    unsigned char ret;
 163              	    asm volatile("lock\n"
 164              	                 "incw %0\n"
 165              	                 "setne %1"
 166              	                 : "=m" (_q_value), "=qm" (ret)
 167              	                 : "m" (_q_value)
 168              	                 : "memory");
 169              	    return ret != 0;
 170              	}
 171              	
 172              	template<> template<typename T> inline
 173              	bool QBasicAtomicOps<4>::ref(T &_q_value) Q_DECL_NOTHROW
 174              	{
 175              	    unsigned char ret;
 176              	    asm volatile("lock\n"
 177              	                 "addl $1, %0\n"
 178              	                 "setne %1"
 179              	                 : "=m" (_q_value), "=qm" (ret)
 180              	                 : "m" (_q_value)
 181              	                 : "memory");
 182              	    return ret != 0;
 183              	}
 184              	
 185              	template<> template <typename T> inline
 186              	bool QBasicAtomicOps<1>::deref(T &_q_value) Q_DECL_NOTHROW
 187              	{
 188              	    unsigned char ret;
 189              	    asm volatile("lock\n"
 190              	                 "subb $1, %0\n"
 191              	                 "setne %1"
 192              	                 : "=m" (_q_value), "=qm" (ret)
 193              	                 : "m" (_q_value)
 194              	                 : "memory");
 195              	    return ret != 0;
 196              	}
 197              	
 198              	template<> template <typename T> inline
 199              	bool QBasicAtomicOps<2>::deref(T &_q_value) Q_DECL_NOTHROW
 200              	{
 201              	    unsigned char ret;
 202              	    asm volatile("lock\n"
 203              	                 "decw %0\n"
 204              	                 "setne %1"
 205              	                 : "=m" (_q_value), "=qm" (ret)
 206              	                 : "m" (_q_value)
 207              	                 : "memory");
 208              	    return ret != 0;
 209              	}
 210              	template<> template <typename T> inline
 211              	bool QBasicAtomicOps<4>::deref(T &_q_value) Q_DECL_NOTHROW
 212              	{
 213              	    unsigned char ret;
 214              	    asm volatile("lock\n"
 215              	                 "subl $1, %0\n"
 216              	                 "setne %1"
 217              	                 : "=m" (_q_value), "=qm" (ret)
 218              	                 : "m" (_q_value)
 219 00bd F0       	                 : "memory");
 220 00be 832F01   	    return ret != 0;
 221 00c1 0F95C0   	}
 222              	
  83              		lock
  84              	subl $1, (%rdi)
  85              	setne %al
  86              	# 0 "" 2
  87              	#NO_APP
  88 00c4 84C0     		testb	%al, %al
  89 00c6 75B4     		jne	.L3
  90 00c8 488B7C24 		movq	16(%rsp), %rdi
  90      10
  91 00cd EB9E     		jmp	.L6
  92              	.L10:
  93 00cf E8000000 		call	__stack_chk_fail@PLT
  93      00
  94              		.cfi_endproc
  95              	.LFE16176:
  97              		.section	.text.unlikely
  98              	.LCOLDE1:
  99              		.section	.text.startup
 100              	.LHOTE1:
 101              		.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
 102              		.section	.note.GNU-stack,"",@progbits
DEFINED SYMBOLS
                            *ABS*:0000000000000000 main.cpp
     /tmp/ccgJVJPB.s:12     .text.startup:0000000000000000 main
     /tmp/ccgJVJPB.s:3      .rodata.str1.1:0000000000000000 .LC0

UNDEFINED SYMBOLS
_GLOBAL_OFFSET_TABLE_
_ZN12QApplicationC1ERiPPci
_ZN7QString16fromAscii_helperEPKci
_ZN6QLabelC1ERK7QStringP7QWidget6QFlagsIN2Qt10WindowTypeEE
_ZN10QArrayData10deallocateEPS_mm
_ZN7QWidget4showEv
_ZN12QApplication4execEv
_ZN6QLabelD1Ev
_ZN12QApplicationD1Ev
__stack_chk_fail
