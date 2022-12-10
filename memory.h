#pragma once
#include <cstdint>
#include "offsets.h"
#include "valorant.h"
namespace Memory
{
	template <typename T>
	T ReadStub(std::uintptr_t Address)
	{
		return reinterpret_cast<T(*)(std::uintptr_t)>(VALORANT::Module + Offsets::TriggerVEH)(Address - 0x8);
	}
	//template <typename T>
	//void WriteStub(std::uintptr_t Address, T other)
	//{
	//	reinterpret_cast<T(*)(std::uintptr_t)>(VALORANT::Module + Offsets::TriggerVEH)(Address - 0x8) = other;
	//}
}