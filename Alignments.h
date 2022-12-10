#pragma once

template <typename T>
FORCEINLINE constexpr T Align(T Val, uint64 Alignment)
{
	return (T)(((uint64)Val + Alignment - 1) & ~(Alignment - 1));
}