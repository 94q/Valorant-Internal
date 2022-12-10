#pragma once
#include "Alignments.h"
#include "FNamePool.h"
#include "decryption.h" 
#include <Windows.h> 
#include <string>


uint64 BaseAddress = (uint64)GetModuleHandleA(0);
class FNamePool* NamePoolData = nullptr;
#define DecryptWideOffset 0x32D05D0
#define DecryptNonWideOffset 0x32D0560 
#define NamePoolDataOffset 0x9095380

static constexpr uint32 FNameMaxBlockBits = 13;
static constexpr uint32 FNameBlockOffsetBits = 16;
static constexpr uint32 FNameMaxBlocks = 1 << FNameMaxBlockBits;
static constexpr uint32 FNameBlockOffsets = 1 << FNameBlockOffsetBits;

struct FNameEntryId
{
	FNameEntryId() : Value(0) {}

	FNameEntryId(uint32 Id) : Value(Id) {}

	explicit operator bool() const { return Value != 0; }

	FORCEINLINE bool operator==(FNameEntryId Other) const
	{
		return Value == Other.Value;
	}

	FORCEINLINE static FNameEntryId FromUnstableInt(uint32 UnstableInt)
	{
		FNameEntryId Id;
		Id.Value = UnstableInt;
		return Id;
	}

	FORCEINLINE uint32 ToUnstableInt() const {
		return Value;
	}

	uint32 Value;
};

struct FNameEntryHandle
{
	uint32 Block = 0;
	uint32 Offset = 0;

	FNameEntryHandle(uint32 InBlock, uint32 InOffset)
		: Block(InBlock)
		, Offset(InOffset)
	{}

	FNameEntryHandle(FNameEntryId Id)
		: Block(Id.ToUnstableInt() >> FNameBlockOffsetBits)
		, Offset(Id.ToUnstableInt()& (FNameBlockOffsets - 1))
	{}

	operator FNameEntryId() const
	{
		return FNameEntryId::FromUnstableInt(Block << FNameBlockOffsetBits | Offset);
	}

	explicit operator bool() const { return Block | Offset; }
};

struct FNameEntryHeader
{
	uint16 bIsWide : 1;
	uint16 Len : 15;
};

struct FNameEntry {
	enum { NAME_SIZE = 1024 };
public:
	FORCEINLINE bool IsWide() const
	{
		return Header.bIsWide;
	}

	FORCEINLINE int32 GetNameLength() const
	{
		return Header.Len;
	}

	FORCEINLINE FNameEntryHeader GetEntryHeader() const
	{
		return Header;
	}

	static int32 GetSize(int32 Length, bool bIsPureAnsi);

	char* DecryptNonWide();

	wchar_t* DecryptWide();

	FORCEINLINE void CopyUnterminatedName(ANSICHAR* Out)
	{
		memcpy(Out, DecryptNonWide(), sizeof(ANSICHAR) * Header.Len);
	}

	FORCEINLINE void CopyUnterminatedName(WIDECHAR* Out)
	{
		memcpy(Out, DecryptWide(), sizeof(WIDECHAR) * Header.Len);
	}

	FORCEINLINE static int32 GetDataOffset()
	{
		return offsetof(FNameEntry, AnsiName);
	}

	void GetAnsiName(ANSICHAR(&Out)[NAME_SIZE]);

	void GetWideName(WIDECHAR(&Out)[NAME_SIZE]);

	WCHAR* Wchar();

	std::string String();

	FNameEntryId ComparisonId;

	FNameEntryHeader Header;

	union
	{
		ANSICHAR	AnsiName[NAME_SIZE];
		WIDECHAR	WideName[NAME_SIZE];
	};

};

void FNameEntry::GetAnsiName(ANSICHAR(&Out)[NAME_SIZE])
{
	if (!IsWide())
	{
		CopyUnterminatedName(Out);
		Out[Header.Len] = '\0';
	}
}

void FNameEntry::GetWideName(WIDECHAR(&Out)[NAME_SIZE])
{
	if (IsWide())
	{
		CopyUnterminatedName(Out);
		Out[Header.Len] = '\0';
	}
}

class FNameEntryAllocator
{
public:
	enum { Stride = alignof(FNameEntry) };
	enum { BlockSizeBytes = Stride * FNameBlockOffsets };

	void* FRWLock;
	uint32 CurrentBlock = 0;
	uint32 CurrentByteCursor = 0;
	uint8* Blocks[FNameMaxBlocks] = {};

	FORCEINLINE uint32 NumBlocks() const
	{
		return CurrentBlock + 1;
	}

	FORCEINLINE FNameEntry& Resolve(FNameEntryHandle Handle) const
	{
		if (Handle.Offset < 0 && Handle.Block > NumBlocks() && Handle.Offset * Stride < FNameBlockOffsets)
			return *reinterpret_cast<FNameEntry*>(Blocks[0] + Stride * 0);

		return *reinterpret_cast<FNameEntry*>(Blocks[Handle.Block] + Stride * Handle.Offset);
	}

};

wchar_t* FNameEntry::DecryptWide()
{

	auto _DecryptWideEntry = (__int64(__fastcall*)(FNameEntry * Entry, wchar_t* Buffer))(BaseAddress + DecryptWideOffset);

	wchar_t Buffer[1024];

	__int64 Result = _DecryptWideEntry(this, Buffer);

	return Buffer;
}

char* FNameEntry::DecryptNonWide()
{
	auto _DecryptNonWideEntry = (__int64(__fastcall*)(FNameEntry * Entry, char* Buffer))(BaseAddress + DecryptNonWideOffset);

	char Buffer[1024];

	__int64 Result = _DecryptNonWideEntry(this, Buffer);

	return Buffer;
}

std::string FNameEntry::String()
{
	if (IsWide()) {
		WCHAR* DecryptedName = DecryptWide();
		std::wstring Wide(DecryptedName, Header.Len);
		return std::string(Wide.begin(), Wide.end());
	}

	char* DecryptedName = DecryptNonWide();
	return std::string(DecryptedName, Header.Len);
}

WCHAR* FNameEntry::Wchar()
{
	if (IsWide())
		return DecryptWide();
	else
		return 0;
}

int32 FNameEntry::GetSize(int32 Length, bool bIsPureAnsi)
{
	int32 Bytes = GetDataOffset() + Length * (bIsPureAnsi ? sizeof(ANSICHAR) : sizeof(WIDECHAR));
	return Align(Bytes, alignof(FNameEntry));
}
 

class FNamePool
{
public:
	enum { MaxENames = 512 };
	FNameEntryAllocator Entries;
	/*
	* Not interested in other members.
	*/
};

struct FName {
	FNameEntryId	ComparisonIndex;

	FNameEntryId	DisplayIndex;

	uint32			Number;

	FORCEINLINE FNameEntryId GetComparisonIndex() const
	{
		return ComparisonIndex;
	}

	FORCEINLINE FNameEntryId GetDisplayIndex() const
	{
		return DisplayIndex;
	}

	FORCEINLINE bool operator==(FName Other) const
	{
		return (ComparisonIndex == Other.ComparisonIndex) && (GetNumber() == Other.GetNumber());
	}

	FORCEINLINE bool operator!=(FName Other) const
	{
		return !(*this == Other);
	}

	FORCEINLINE int32 GetNumber() const
	{
		return Number;
	}

	FName() :
		ComparisonIndex(FNameEntryId()),
		Number(0)
	{ }

	FName(int32 i, int32 n = 0) :
		ComparisonIndex(FNameEntryId(i)),
		Number(n)
	{ }

	const FNameEntry* GetDisplayNameEntry() const;

	std::string GetName();
};

const FNameEntry* FName::GetDisplayNameEntry() const
{
	return &NamePoolData->Entries.Resolve(GetDisplayIndex());
}

std::string FName::GetName()
{
	FNameEntry Entry = NamePoolData->Entries.Resolve(GetDisplayIndex());

	std::string Name = Entry.String();

	if (Number > 0) Name += '_' + std::to_string(Number);

	std::size_t Pos = Name.rfind('/');

	if (Pos != std::string::npos) Name = Name.substr(Pos + 1);

	return Name;
}