/*
 *	VDEngine virtual dimension game engine.
 *	Copyright (C) 2014 - Valdemar Lindberg
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _VD_ENGINE_DEF_H_
#define _VD_ENGINE_DEF_H_ 1
#include <Def.h>
#include <cerrno>
#include <typeinfo>

#ifdef __cplusplus
#include <cstdio>
#include <climits>
#else
#include <stdio.h>
#include <limits.h>
#endif

#define VD_ENGINE_VERSION ( (MAJOR_VERSION  << 24) | (MINOR_VERSION  << 16) | (PATCH_VERSION  << 8) )

/**
 *	Copy virtual table.
 */
#define VD_COPY_VPTR(destination,source) {memcpy((void*)( destination ),(const void*) ( source ), sizeof(const void*));}
#define VD_DECLARE_HANDLE(name) typedef struct name##__ { int unused; } *name

/*
 *	Compiler
 */
#ifdef _MSC_VER 	/*	Visual Studio C++ Compiler.	*/
	#define VD_VC
	#if _MSC_VER >= 1900
		#define VD_V13 _MSC_VER
	#elif _MSC_VER >= 1800
		#define VD_V12 _MSC_VER
	#elif _MSC_VER >= 1700
		#define VD_VC11 _MSC_VER
	#elif _MSC_VER >= 1600
		#define VD_VC10 _MSC_VER
	#elif _MSC_VER >= 1500
		#define VD_VC9 _MSC_VER
	#elif _MSC_VER >= 1400
		#define VD_VC8 _MSC_VER
	#elif _MSC_VER >= 1300
		#define VD_VC7 _MSC_VER
	#else
		#define VD_VC6 _MSC_VER
	#endif
    	#pragma warning(disable : 4201)
	#define VD_COMPILER_NAME "Visual Studio C++/C"

#elif defined(__clang__) || defined(__llvm__)           /*  LLVM, clang   */
    #define VD_LLVM 1
	#define VD_CLANG 1
	#define ENGINE_VD_COMPILER 5
	#define VD_COMPILER_NAME "LLVM/CLANG"
	#define VD_COMPILER_MAJOR_VERSION __clang_major__
	#define VD_COMPILER_MINOR_VERSION __clang_minor__

#elif defined(__GNUC__) || defined(__SNC__) || defined( __GNUC_MINOR__)	/*  GNU C Compiler*/
	#define VD_GNUC 1
	#define ENGINE_VD_COMPILER 2
	#define VD_COMPILER_NAME "GNU C"
	#define VD_COMPILER_MAJOR_VERSION __clang_major__
	#define VD_COMPILER_MINOR_VERSION __clang_minor__
	#if defined(__GNUG__) /*  GNU C++ Compiler*/
		#define VD_GNUCXX
	#endif

#elif defined(__ghs__)		/* GHS	*/
	#define VD_GHS 1
	#define ENGINE_VD_COMPILER 3

#elif defined(__HP_cc) || defined(__HP_aCC)			/*	*/

#elif defined(__PGI)			/*	*/

#elif defined(__ICC) || defined(__INTEL_COMPILER) /*  Intel Compiler  */
	#define VD_INTEL
	#define ENGINE_VD_COMPILER 4
	#define VD_COMPILER_NAME "Intel C++"

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)

#else
	#error Unsupported Compiler.
#endif

/**
 *	Find the arch type.
 */
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__) || defined(__arm64__) || defined(_aarch64_) || defined(__mips64) || defined(__mips64_)
	#define VD_ARCHITECTURE_64
	#define VD_X86
#else
	#define VD_ARCHITECTURE_32
#endif
#if defined(__arm__)
	  #define VD_ARM 1
#endif

/**
 *	Macro definition of Release and Debug build.
 */
#if defined(_DEBUG) || defined(DEBUG)
	#define VD_DEBUG	1
	#define DEBUGMODE	1
#elif defined(NDEBUG)
	#define VD_RELEASE	1
	#define RELEASEMODE	1
#else
	#define VD_RELEASE
	#define RELEASEMODE
#endif

/**
 *	Deprecated macros.
 */
#ifdef VD_MSVC
	#define VDDEPRECATED  __declspec(deprecated)		    // Deprecated deceleration (x = Warning Message)
	#define VDDEPRECATEDMESSAGE(x) __declspec(deprecated(x))
#elif defined(VD_GNUC)
	#define VDDEPRECATED __attribute__(( deprecated ))		    // Deprecated deceleration (x = Warning Message)
    #define VDDEPRECATEDMESSAGE(msg) __attribute__ (( deprecated ( msg ) ))
#endif

/**
 *	Calling function convention.
 */
#ifdef VD_WINDOWS	        /*	Windows Calling Convention.	*/
	#define VDAPIENTRY     __cdecl
	#define VDAPIFASTENTRY __fastcall
	#define VDAPITHISENTRY __thiscall
	#define VDAPISTDENTRY  __stdcall
#elif defined(VD_ANDROID)   /*	Android Calling Convention	*/
    #define VDAPIENTRY JNICALL
    #define VDAPIFASTENTRY JNICALL
    #define VDAPITHISENTRY JNICALL
    #define VDAPISTDENTRY JNICALL
#else
#   ifndef __cdecl
        #define __cdecl  __attribute__ ((__cdecl__))
        #define __stdcall  __attribute__ ((stdcall))
		#define __fastcall __attribute__((fastcall))
#   endif
	#define VDAPIENTRY     __cdecl
	#define VDAPISTDENTRY  __stdcall
	#define VDAPIFASTENTRY __fastcall
#endif

/**
 *	Alignment
 */
#ifndef VD_ALIGN
        #if defined(VD_MSVC)
                #define VD_ALIGN(alignment, decl) __declspec(align(alignment)) decl
                #define VD_ALIGN_PREFIX(alignment) __declspec(align(alignment))
                #define VD_ALIGN_VECTOR(alignment)  __declspec ((__vector_size__ (alignment), __may_alias__))
        #elif defined(VD_GNUC)
                #define VD_ALIGN(alignment, decl) decl __attribute__ ((aligned(alignment)))
                #define VD_ALIGN_PREFIX(alignment) __attribute__ ((aligned(alignment)))
                #define VD_ALIGN_VECTOR(alignment)  __attribute__ ((__vector_size__ (alignment), __may_alias__))
        #elif defined(VD_CLANG)
                #define VD_ALIGN(alignment, decl) decl __attribute__ ((aligned(alignment)))
                #define VD_ALIGN_PREFIX(alignment) __attribute__ ((aligned(alignment)))
#define VD_ALIGN_VECTOR(alignment)  __attribute__ ((__vector_size__ (alignment), __may_alias__))
        #else
                #pragma message("Warning: You'd need to add VD_ALIGN, VD_ALIGN_PREFIX, VD_ALIGN_VECTOR for this compiler.")
                #define VD_ALIGN(alignment, decl)
                #define VD_ALIGN_PREFIX(alignment)
                #define VD_ALIGN_VECTOR(alignment)
        #endif
#endif

/**
 *
 */
#ifdef VD_GNUC
        #define VDDECLSPEC  __attribute__((visibility("default")))
#elif defined(VD_MSVC)
        #define VDDECLSPEC __declspec(dllimport)
#endif

/**
 *	Pointer restriction
 */
#ifdef VD_GNUC
	#define VD_RESTRICT __restrict
#else
#endif

/**
 *	Type
 */
#ifdef __cplusplus	/*	C++	Environment	*/
	#define VDTYPE(x) typeid(x)
	#define VDTYPEX(x) VDTypeInfo(typeid(x),sizeof(x))
	#define VDTYPE_EQUAL(x,y) ( (typeid( ( x ) ) == typeid( ( y ) )) ? SDL_TRUE : SDL_FALSE )
	#define VDTYPEX_EQUAL(x,y)
	#define VDTYPEBASE(current,base) typeid(current).before(base)
	#define VDTYPENAME(x) typeid(x).name()
#endif

/**
 *	Casting data types.
 */
#ifdef __cplusplus	/*	C++	Environment	*/
	#define VDCASTP(type,y) reinterpret_cast<type>( ( y ) )
	#define VDCAST(type,y) static_cast<type>( ( y ) )
	#define VDCASTD(type,y) dynamic_cast<type>( ( y ) )
#endif

/**
 *
 */
#ifdef VD_MSVC
	#pragma warning(disable : 4390)
#endif


/**
 *	Converting character into a constant string in the precompiling stage.
 */
#define VD_STR_HELPER(x) #x
#define VD_STR(x) VD_STR_HELPER(x)

/**
 *	Unicode macro for converting constant string to
 */
#ifdef UNICODE  /*  UTF-16*/
	#define VD_UNICODE
	#define _VD_TEXT(quote) L##quote
	#define VD_TEXT(quote)  _EX_TEXT(quote)
#else           /*	ASCII / UTF-8	*/
	#define VD_ANSI
	#define VD_TEXT(quote) quote
#endif


#endif
