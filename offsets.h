#pragma once
namespace Offsets
{
	constexpr auto
		Key = 0x8FDF578, //uworld_key 
		State = 0x8FDF540,  //uworld_state 
		ProcessEvent = 0x3306FA0,
		StaticFindObject = 0x3347E30,
		TriggerVEH = 0x1B67F90,
		GetActorBounds = 0x4771E10;  //void GetActorBounds(bool bOnlyCollidingComponents, struct FVector& Origin, struct FVector& BoxExtent, bool bIncludeFromChildActors); // Function Engine.Actor.GetActorBounds // (Final|Native|Public|HasOutParms|HasDefaults|BlueprintCallable|BlueprintPure|Const)
}
