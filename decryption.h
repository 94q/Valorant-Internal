#ifndef DEFS_H
#define DEFS_H
#pragma once

/*____________________________________________________________________________________________________________

Original Author: skadro
Github: https://github.com/skadro-official
License: See end of file

skCrypter
		Compile-time, Usermode + Kernelmode, safe and lightweight string crypter library for C++11+

							*Not removing this part is appreciated*
____________________________________________________________________________________________________________*/

#ifdef _KERNEL_MODE
namespace std
{
	// STRUCT TEMPLATE remove_reference
	template <class _Ty>
	struct remove_reference {
		using type = _Ty;
	};

	template <class _Ty>
	struct remove_reference<_Ty&> {
		using type = _Ty;
	};

	template <class _Ty>
	struct remove_reference<_Ty&&> {
		using type = _Ty;
	};

	template <class _Ty>
	using remove_reference_t = typename remove_reference<_Ty>::type;

	// STRUCT TEMPLATE remove_const
	template <class _Ty>
	struct remove_const { // remove top-level const qualifier
		using type = _Ty;
	};

	template <class _Ty>
	struct remove_const<const _Ty> {
		using type = _Ty;
	};

	template <class _Ty>
	using remove_const_t = typename remove_const<_Ty>::type;
}
#else
#include <type_traits>
#endif

namespace skc
{
	template<class _Ty>
	using clean_type = typename std::remove_const_t<std::remove_reference_t<_Ty>>;

	template <int _size, char _key1, char _key2, typename T>
	class skCrypter
	{
	public:
		__forceinline constexpr skCrypter(T* data)
		{
			crypt(data);
		}

		__forceinline T* get()
		{
			return _storage;
		}

		__forceinline int size() // (w)char count
		{
			return _size;
		}

		__forceinline  char key()
		{
			return _key1;
		}

		__forceinline  T* encrypt()
		{
			if (!isEncrypted())
				crypt(_storage);

			return _storage;
		}

		__forceinline  T* decrypt()
		{
			if (isEncrypted())
				crypt(_storage);

			return _storage;
		}

		__forceinline bool isEncrypted()
		{
			return _storage[_size - 1] != 0;
		}

		__forceinline void clear() // set full storage to 0
		{
			for (int i = 0; i < _size; i++)
			{
				_storage[i] = 0;
			}
		}

		__forceinline operator T* ()
		{
			decrypt();

			return _storage;
		}

	private:
		__forceinline constexpr void crypt(T* data)
		{
			for (int i = 0; i < _size; i++)
			{
				_storage[i] = data[i] ^ (_key1 + i % (1 + _key2));
			}
		}

		T _storage[_size]{};
	};
}

#define skCrypt(str) skCrypt_key(str, __TIME__[4], __TIME__[7])
#define skCrypt_key(str, key1, key2) []() { \
			constexpr static auto crypted = skc::skCrypter \
				<sizeof(str) / sizeof(str[0]), key1, key2, skc::clean_type<decltype(str[0])>>((skc::clean_type<decltype(str[0])>*)str); \
					return crypted; }()

/*________________________________________________________________________________

MIT License

Copyright (c) 2020 skadro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

________________________________________________________________________________*/
#if defined(__GNUC__)
typedef          long long ll;
typedef unsigned long long ull;
#define __int64 long long
#define __int32 int
#define __int16 short
#define __int8  char
#define MAKELL(num) num ## LL
#define FMT_64 "ll"
#elif defined(_MSC_VER)
typedef          __int64 ll;
typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "I64"
#elif defined (__BORLANDC__)
typedef          __int64 ll;
typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "L"
#else
#error "unknown compiler"
#endif

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef          char   int8;
typedef   signed char   sint8;
typedef unsigned char   uint8;
typedef          short  int16;
typedef   signed short  sint16;
typedef unsigned short  uint16;
typedef          int    int32;
typedef   signed int    sint32;
typedef unsigned int    uint32;
typedef ll              int64;
typedef ll              sint64;
typedef ull             uint64;

// Partially defined types. They are used when the decompiler does not know
// anything about the type except its size.
#define _BYTE  uint8
#define _WORD  uint16
#define _DWORD uint32
#define _QWORD uint64
#if !defined(_MSC_VER)
#define _LONGLONG __int128
#endif

// Non-standard boolean types. They are used when the decompiler can not use
// the standard "bool" type because of the size mistmatch but the possible
// values are only 0 and 1. See also 'BOOL' type below.
typedef int8 _BOOL1;
typedef int16 _BOOL2;
typedef int32 _BOOL4;

//#ifndef _WINDOWS_
//typedef int8 BYTE;
//typedef int16 WORD;
//typedef int32 DWORD;
//typedef int32 LONG;
//typedef int BOOL;       // uppercase BOOL is usually 4 bytes
//#endif
//typedef int64 QWORD;
#ifndef __cplusplus
typedef int bool;       // we want to use bool in our C programs
#endif

#define __pure          // pure function: always returns the same value, has no
						// side effects

// Non-returning function
#if defined(__GNUC__)
#define __noreturn  __attribute__((noreturn))
#else
#define __noreturn  __declspec(noreturn)
#endif


#ifndef NULL
#define NULL 0
#endif

// An ANSI character. 8-bit fixed-width representation of 7-bit characters.
typedef char				ANSICHAR;

// A wide character. In-memory only. ?-bit fixed-width representation of the platform's natural wide character set. Could be different sizes on different platforms.
typedef wchar_t				WIDECHAR;

// An 8-bit character type. In-memory only. 8-bit representation. Should really be char8_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
typedef uint8				CHAR8;

// A 16-bit character type. In-memory only.  16-bit representation. Should really be char16_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
typedef uint16				CHAR16;

// A 32-bit character type. In-memory only. 32-bit representation. Should really be char32_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
typedef uint32				CHAR32;

// A switchable character. In-memory only. Either ANSICHAR or WIDECHAR, depending on a licensee's requirements.
typedef WIDECHAR			TCHAR;
// Some convenience macros to make partial accesses nicer
#define LAST_IND(x,part_type)    (sizeof(x)/sizeof(part_type) - 1)
#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN
#  define LOW_IND(x,part_type)   LAST_IND(x,part_type)
#  define HIGH_IND(x,part_type)  0
#else
#  define HIGH_IND(x,part_type)  LAST_IND(x,part_type)
#  define LOW_IND(x,part_type)   0
#endif
// first unsigned macros:
//#define LODWORD(x)  (*((DWORD*)&(x)))  // low dword
//#define HIDWORD(x)  (*((DWORD*)&(x)+1))

#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define DWORDn(x, n)  (*((_DWORD*)&(x)+n))

#define LOBYTE(x)  BYTEn(x,LOW_IND(x,_BYTE))
#define LOWORD(x)  WORDn(x,LOW_IND(x,_WORD))
#define LODWORD(x) DWORDn(x,LOW_IND(x,_DWORD))
#define HIBYTE(x)  BYTEn(x,HIGH_IND(x,_BYTE))
#define HIWORD(x)  WORDn(x,HIGH_IND(x,_WORD))
#define HIDWORD(x) DWORDn(x,HIGH_IND(x,_DWORD))
#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)
#define BYTE2(x)   BYTEn(x,  2)
#define BYTE3(x)   BYTEn(x,  3)
#define BYTE4(x)   BYTEn(x,  4)
#define BYTE5(x)   BYTEn(x,  5)
#define BYTE6(x)   BYTEn(x,  6)
#define BYTE7(x)   BYTEn(x,  7)
#define BYTE8(x)   BYTEn(x,  8)
#define BYTE9(x)   BYTEn(x,  9)
#define BYTE10(x)  BYTEn(x, 10)
#define BYTE11(x)  BYTEn(x, 11)
#define BYTE12(x)  BYTEn(x, 12)
#define BYTE13(x)  BYTEn(x, 13)
#define BYTE14(x)  BYTEn(x, 14)
#define BYTE15(x)  BYTEn(x, 15)
#define WORD1(x)   WORDn(x,  1)
#define WORD2(x)   WORDn(x,  2)         // third word of the object, unsigned
#define WORD3(x)   WORDn(x,  3)
#define WORD4(x)   WORDn(x,  4)
#define WORD5(x)   WORDn(x,  5)
#define WORD6(x)   WORDn(x,  6)
#define WORD7(x)   WORDn(x,  7)

// now signed macros (the same but with sign extension)
#define SBYTEn(x, n)   (*((int8*)&(x)+n))
#define SWORDn(x, n)   (*((int16*)&(x)+n))
#define SDWORDn(x, n)  (*((int32*)&(x)+n))

#define SLOBYTE(x)  SBYTEn(x,LOW_IND(x,int8))
#define SLOWORD(x)  SWORDn(x,LOW_IND(x,int16))
#define SLODWORD(x) SDWORDn(x,LOW_IND(x,int32))
#define SHIBYTE(x)  SBYTEn(x,HIGH_IND(x,int8))
#define SHIWORD(x)  SWORDn(x,HIGH_IND(x,int16))
#define SHIDWORD(x) SDWORDn(x,HIGH_IND(x,int32))
#define SBYTE1(x)   SBYTEn(x,  1)
#define SBYTE2(x)   SBYTEn(x,  2)
#define SBYTE3(x)   SBYTEn(x,  3)
#define SBYTE4(x)   SBYTEn(x,  4)
#define SBYTE5(x)   SBYTEn(x,  5)
#define SBYTE6(x)   SBYTEn(x,  6)
#define SBYTE7(x)   SBYTEn(x,  7)
#define SBYTE8(x)   SBYTEn(x,  8)
#define SBYTE9(x)   SBYTEn(x,  9)
#define SBYTE10(x)  SBYTEn(x, 10)
#define SBYTE11(x)  SBYTEn(x, 11)
#define SBYTE12(x)  SBYTEn(x, 12)
#define SBYTE13(x)  SBYTEn(x, 13)
#define SBYTE14(x)  SBYTEn(x, 14)
#define SBYTE15(x)  SBYTEn(x, 15)
#define SWORD1(x)   SWORDn(x,  1)
#define SWORD2(x)   SWORDn(x,  2)
#define SWORD3(x)   SWORDn(x,  3)
#define SWORD4(x)   SWORDn(x,  4)
#define SWORD5(x)   SWORDn(x,  5)
#define SWORD6(x)   SWORDn(x,  6)
#define SWORD7(x)   SWORDn(x,  7)


// Helper functions to represent some assembly instructions.

#ifdef __cplusplus

// compile time assertion
#define __CASSERT_N0__(l) COMPILE_TIME_ASSERT_ ## l
#define __CASSERT_N1__(l) __CASSERT_N0__(l)
#define CASSERT(cnd) typedef char __CASSERT_N1__(__LINE__) [(cnd) ? 1 : -1]

// check that unsigned multiplication does not overflow
template<class T> bool is_mul_ok(T count, T elsize)
{
	CASSERT((T)(-1) > 0); // make sure T is unsigned
	if (elsize == 0 || count == 0)
		return true;
	return count <= ((T)(-1)) / elsize;
}

// multiplication that saturates (yields the biggest value) instead of overflowing
// such a construct is useful in "operator new[]"
template<class T> bool saturated_mul(T count, T elsize)
{
	return is_mul_ok(count, elsize) ? count * elsize : T(-1);
}

#include <stddef.h> // for size_t
#include <cstdint>

// memcpy() with determined behavoir: it always copies
// from the start to the end of the buffer
// note: it copies byte by byte, so it is not equivalent to, for example, rep movsd
inline void* qmemcpy(void* dst, const void* src, size_t cnt)
{
	char* out = (char*)dst;
	const char* in = (const char*)src;
	while (cnt > 0)
	{
		*out++ = *in++;
		--cnt;
	}
	return dst;
}

// Generate a reference to pair of operands
template<class T>  int16 __PAIR__(int8  high, T low) { return (((int16)high) << sizeof(high) * 8) | uint8(low); }
template<class T>  int32 __PAIR__(int16 high, T low) { return (((int32)high) << sizeof(high) * 8) | uint16(low); }
template<class T>  int64 __PAIR__(int32 high, T low) { return (((int64)high) << sizeof(high) * 8) | uint32(low); }
template<class T> uint16 __PAIR__(uint8  high, T low) { return (((uint16)high) << sizeof(high) * 8) | uint8(low); }
template<class T> uint32 __PAIR__(uint16 high, T low) { return (((uint32)high) << sizeof(high) * 8) | uint16(low); }
template<class T> uint64 __PAIR__(uint32 high, T low) { return (((uint64)high) << sizeof(high) * 8) | uint32(low); }

// rotate left
template<class T> T __ROL__(T value, int count)
{
	const uint nbits = sizeof(T) * 8;

	if (count > 0)
	{
		count %= nbits;
		T high = value >> (nbits - count);
		if (T(-1) < 0)
			high &= ~((T(-1) << count));
		value <<= count;
		value |= high;
	}
	else
	{
		count = -count % nbits;
		T low = value << (nbits - count);
		value >>= count;
		value |= low;
	}
	return value;
}

inline uint8  __ROL1__(uint8  value, int count) { return __ROL__((uint8)value, count); }
inline uint16 __ROL2__(uint16 value, int count) { return __ROL__((uint16)value, count); }
inline uint32 __ROL4__(uint32 value, int count) { return __ROL__((uint32)value, count); }
inline uint64 __ROL8__(uint64 value, int count) { return __ROL__((uint64)value, count); }
inline uint8  __ROR1__(uint8  value, int count) { return __ROL__((uint8)value, -count); }
inline uint16 __ROR2__(uint16 value, int count) { return __ROL__((uint16)value, -count); }
inline uint32 __ROR4__(uint32 value, int count) { return __ROL__((uint32)value, -count); }
inline uint64 __ROR8__(uint64 value, int count) { return __ROL__((uint64)value, -count); }

// carry flag of left shift
template<class T> int8 __MKCSHL__(T value, uint count)
{
	const uint nbits = sizeof(T) * 8;
	count %= nbits;

	return (value >> (nbits - count)) & 1;
}

// carry flag of right shift
template<class T> int8 __MKCSHR__(T value, uint count)
{
	return (value >> (count - 1)) & 1;
}

// sign flag
template<class T> int8 __SETS__(T x)
{
	if (sizeof(T) == 1)
		return int8(x) < 0;
	if (sizeof(T) == 2)
		return int16(x) < 0;
	if (sizeof(T) == 4)
		return int32(x) < 0;
	return int64(x) < 0;
}

// overflow flag of subtraction (x-y)
template<class T, class U> int8 __OFSUB__(T x, U y)
{
	if (sizeof(T) < sizeof(U))
	{
		U x2 = x;
		int8 sx = __SETS__(x2);
		return (sx ^ __SETS__(y)) & (sx ^ __SETS__(x2 - y));
	}
	else
	{
		T y2 = y;
		int8 sx = __SETS__(x);
		return (sx ^ __SETS__(y2)) & (sx ^ __SETS__(x - y2));
	}
}

// overflow flag of addition (x+y)
template<class T, class U> int8 __OFADD__(T x, U y)
{
	if (sizeof(T) < sizeof(U))
	{
		U x2 = x;
		int8 sx = __SETS__(x2);
		return ((1 ^ sx) ^ __SETS__(y)) & (sx ^ __SETS__(x2 + y));
	}
	else
	{
		T y2 = y;
		int8 sx = __SETS__(x);
		return ((1 ^ sx) ^ __SETS__(y2)) & (sx ^ __SETS__(x + y2));
	}
}

// carry flag of subtraction (x-y)
template<class T, class U> int8 __CFSUB__(T x, U y)
{
	int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
	if (size == 1)
		return uint8(x) < uint8(y);
	if (size == 2)
		return uint16(x) < uint16(y);
	if (size == 4)
		return uint32(x) < uint32(y);
	return uint64(x) < uint64(y);
}

// carry flag of addition (x+y)
template<class T, class U> int8 __CFADD__(T x, U y)
{
	int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
	if (size == 1)
		return uint8(x) > uint8(x + y);
	if (size == 2)
		return uint16(x) > uint16(x + y);
	if (size == 4)
		return uint32(x) > uint32(x + y);
	return uint64(x) > uint64(x + y);
}



#else
// The following definition is not quite correct because it always returns
// uint64. The above C++ functions are good, though.
#define __PAIR__(high, low) (((uint64)(high)<<sizeof(high)*8) | low)
// For C, we just provide macros, they are not quite correct.
#define __ROL__(x, y) __rotl__(x, y)      // Rotate left
#define __ROR__(x, y) __rotr__(x, y)      // Rotate right
#define __CFSHL__(x, y) invalid_operation // Generate carry flag for (x<<y)
#define __CFSHR__(x, y) invalid_operation // Generate carry flag for (x>>y)
#define __CFADD__(x, y) invalid_operation // Generate carry flag for (x+y)
#define __CFSUB__(x, y) invalid_operation // Generate carry flag for (x-y)
#define __OFADD__(x, y) invalid_operation // Generate overflow flag for (x+y)
#define __OFSUB__(x, y) invalid_operation // Generate overflow flag for (x-y)
#endif

// No definition for rcl/rcr because the carry flag is unknown
#define __RCL__(x, y)    invalid_operation // Rotate left thru carry
#define __RCR__(x, y)    invalid_operation // Rotate right thru carry
#define __MKCRCL__(x, y) invalid_operation // Generate carry flag for a RCL
#define __MKCRCR__(x, y) invalid_operation // Generate carry flag for a RCR
#define __SETP__(x, y)   invalid_operation // Generate parity flag for (x-y)

// In the decompilation listing there are some objects declarared as _UNKNOWN
// because we could not determine their types. Since the C compiler does not
// accept void item declarations, we replace them by anything of our choice,
// for example a char:

#define _UNKNOWN char

//#ifdef _MSC_VER
//#define snprintf _snprintf
//#define vsnprintf _vsnprintf
//#endif
struct State {
	uintptr_t keys[7];
};
namespace Decryption
{

	__forceinline __int64 Decrypt_UWorld(const uint32_t key, const uintptr_t* state)
	{

		unsigned __int64 v19; // r11
		unsigned __int64 v20; // r8
		unsigned __int64 v21; // r9
		unsigned int v22; // er10
		unsigned __int64 v23; // rcx
		unsigned __int64 v24; // rdx
		unsigned __int64 v25; // rcx
		int v26; // ebx
		unsigned int v27; // ecx
		__int64 v28; // rax
		unsigned __int64 v29; // r8
		unsigned __int64 v30; // r8
		unsigned __int64 v31; // rcx
		unsigned __int64 v32; // rdx
		unsigned __int64 v33; // rcx

		v19 = 2685821657736338717i64
			* ((unsigned int)key ^ (unsigned int)(key << 25) ^ (((unsigned int)key ^ ((unsigned __int64)(unsigned int)key >> 15)) >> 12))
			% 7;
		v20 = state[v19];
		v21 = (2685821657736338717i64
			* ((unsigned int)key ^ (unsigned int)(key << 25) ^ (((unsigned int)key ^ ((unsigned __int64)(unsigned int)key >> 15)) >> 12))) >> 32;
		v22 = (unsigned int)v19 % 7;
		if (!((unsigned int)v19 % 7))
		{
			v23 = (2 * (v20 - (unsigned int)(v21 - 1))) ^ ((2 * (v20 - (unsigned int)(v21 - 1))) ^ ((v20
				- (unsigned int)(v21 - 1)) >> 1)) & 0x5555555555555555i64;
			v24 = (4 * v23) ^ ((4 * v23) ^ (v23 >> 2)) & 0x3333333333333333i64;
			v25 = (16 * v24) ^ ((16 * v24) ^ (v24 >> 4)) & 0xF0F0F0F0F0F0F0Fi64;
			v20 = __ROL8__((v25 << 8) ^ ((v25 << 8) ^ (v25 >> 8)) & 0xFF00FF00FF00FFi64, 32);
		LABEL_26:
			v26 = 2 * v19;
			goto LABEL_27;
		}
		if (v22 != 1)
			goto LABEL_26;
		v26 = 2 * v19;
		v20 = __ROL8__(v20 - (unsigned int)(2 * v19 + v21), (unsigned __int8)(((int)v21 + (int)v19) % 0x3Fu) + 1);
	LABEL_27:
		v27 = v26 + v21;
		if (v22 == 2)
			v20 = ~(v20 - v27);
		switch (v22)
		{
		case 3u:
			v28 = 2 * ((2 * v20) ^ ((2 * v20) ^ (v20 >> 1)) & 0x5555555555555555i64);
			v20 = v28 ^ (v28 ^ (((2 * v20) ^ ((2 * v20) ^ (v20 >> 1)) & 0x5555555555555555i64) >> 1)) & 0x5555555555555555i64;
			break;
		case 4u:
			v29 = __ROR8__(v20, (unsigned __int8)(v27 % 0x3F) + 1);
			v20 = (2 * v29) ^ ((2 * v29) ^ (v29 >> 1)) & 0x5555555555555555i64;
			break;
		case 5u:
			v30 = __ROR8__(v20, (unsigned __int8)(v27 % 0x3F) + 1);
			v31 = (2 * v30) ^ ((2 * v30) ^ (v30 >> 1)) & 0x5555555555555555i64;
			v32 = (4 * v31) ^ ((4 * v31) ^ (v31 >> 2)) & 0x3333333333333333i64;
			v33 = (16 * v32) ^ ((16 * v32) ^ (v32 >> 4)) & 0xF0F0F0F0F0F0F0Fi64;
			v20 = __ROL8__((v33 << 8) ^ ((v33 << 8) ^ (v33 >> 8)) & 0xFF00FF00FF00FFi64, 32);
			break;
		case 6u:
			v20 = ~v20 - (unsigned int)(v21 + v19);
			break;
		}
		return v20 ^ (unsigned int)key;
	}

}
#endif