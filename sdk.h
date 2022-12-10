#pragma once
#include "memory.h"
#include "unrealengine.h"
class UObject
{
public:
	char padding_01[0x18];
	int32_t ComparisonIndex;
	static UObject* StaticFindObject(UObject* Class, UObject* InOuter, const wchar_t* Name, bool ExactClass)
	{
		static uintptr_t StaticFindObjectAddress = VALORANT::Module + Offsets::StaticFindObject;

		auto StaticFindObjectFN = reinterpret_cast<UObject * (__fastcall*)(UObject*, UObject*, const wchar_t*, bool)>(StaticFindObjectAddress);

		return StaticFindObjectFN(Class, InOuter, Name, ExactClass);
	}
	static void ProcessEvent(void* class_, UObject* function, void* params)
	{
		reinterpret_cast<void (*)(void*, UObject*, void*)>(VALORANT::Module + Offsets::ProcessEvent)(class_, function, params);
	}
};

struct UWorld
{

};

struct UFont : UObject
{

};

UObject* DefaultMediumFont;
struct UEngine
{

};
bool bOutline = 1;
struct UCanvas
{
	void K2_DrawLine(struct FVector2D ScreenPositionA, struct FVector2D ScreenPositionB, float Thickness, struct FLinearColor RenderColor)
	{
		UObject* function = UObject::StaticFindObject(nullptr, nullptr, L"Engine.Canvas.K2_DrawLine", false);


		struct {
			FVector2D ScreenPositionA;
			FVector2D ScreenPositionB;
			float Thickness;
			FLinearColor RenderColor;
		}Args;
		Args.ScreenPositionA = ScreenPositionA;
		Args.ScreenPositionB = ScreenPositionB;
		Args.Thickness = Thickness;
		Args.RenderColor = RenderColor; 
		function->ProcessEvent(this, function, &Args);
	}
	void K2_DrawLinex(FVector2D ScreenPositionA, FVector2D ScreenPositionB, float Thickness, FLinearColor RenderColor) // CRT af doe (ironic.)
	{
		if(bOutline)
		{
			K2_DrawLine({ ScreenPositionA.X + 1, ScreenPositionA.Y }, { ScreenPositionB.X, ScreenPositionB.Y }, Thickness, { 0.0f,0.0f,0.0f,1.0f });
			K2_DrawLine({ ScreenPositionA.X - 1, ScreenPositionA.Y }, { ScreenPositionB.X, ScreenPositionB.Y }, Thickness, { 0.0f,0.0f,0.0f,1.0f });
			K2_DrawLine({ ScreenPositionA.X, ScreenPositionA.Y + 1 }, { ScreenPositionB.X, ScreenPositionB.Y }, Thickness, { 0.0f,0.0f,0.0f,1.0f });
			K2_DrawLine({ ScreenPositionA.X, ScreenPositionA.Y - 1 }, { ScreenPositionB.X, ScreenPositionB.Y }, Thickness, { 0.0f,0.0f,0.0f,1.0f });
		}
		K2_DrawLine({ ScreenPositionA.X, ScreenPositionA.Y }, { ScreenPositionB.X, ScreenPositionB.Y }, Thickness, RenderColor);
	}
	void K2_DrawText(struct FString RenderText, struct FVector2D ScreenPosition, struct FVector2D Scale, struct FLinearColor RenderColor, float Kerning, struct FLinearColor ShadowColor, struct FVector2D ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, struct FLinearColor OutlineColor)
	{
		UObject* function = UObject::StaticFindObject(nullptr, nullptr, L"Engine.Canvas.K2_DrawText", false);
		if(!DefaultMediumFont) 
			DefaultMediumFont = UObject::StaticFindObject(nullptr, nullptr, L"/Engine/EngineFonts/Roboto.Roboto", false);
		struct {
			UObject* RenderFont;
			FString RenderText;
			FVector2D ScreenPosition;
			FVector2D Scale;
			FLinearColor RenderColor;
			float Kerning;
			FLinearColor ShadowColor;
			FVector2D ShadowOffset;
			bool bCentreX;
			bool bCentreY;
			bool bOutlined;
			FLinearColor OutlineColor;
		}Args;
		Args.RenderFont = DefaultMediumFont;
		Args.RenderText = RenderText;
		Args.ScreenPosition = ScreenPosition;
		Args.Scale = Scale;
		Args.RenderColor = RenderColor;
		Args.Kerning = Kerning;
		Args.ShadowColor = ShadowColor;
		Args.ShadowOffset = ShadowOffset;
		Args.bCentreX = bCentreX;
		Args.bCentreY = bCentreY;
		Args.bOutlined = bOutlined;
		Args.OutlineColor = OutlineColor; 
		function->ProcessEvent(this, function, &Args);
	}
};

struct UGameInstance
{

};

struct ULocalPlayer
{

};

struct FBoxSphereBounds {
	FVector Origin;
	FVector BoxExtent;
	float SphereRadius;
};

struct FBox {
	FVector Min;
	FVector Max;

	FBox() {

		Min.X = NULL;
		Min.Y = NULL;
		Min.Z = NULL;
		
		Max.X = NULL;
		Max.Y = NULL;
		Max.Z = NULL;
	}
};

struct UStaticMeshComponent
{
	FBox GetBoundingBox()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"Engine.StaticMesh.GetBoundingBox", false);
		if (!Function)
		{
			return FBox();
		}
		struct
		{
			FBox ReturnValue;
		}Parameters;
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.ReturnValue;
	}
};

struct USkeletalMeshComponent
{

	void SetAresOutlineMode(EAresOutlineMode Mode, bool bPropagateToChildren)
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"Engine.MeshComponent.SetAresOutlineMode", false);
		if (!Function)
		{
			return;
		}
		struct
		{
			EAresOutlineMode Mode;
			bool bPropagateToChildren;
		}Parameters;
		Parameters.Mode = Mode;
		Parameters.bPropagateToChildren = bPropagateToChildren;
		Function->ProcessEvent(this, Function, &Parameters);
	}
};

DWORD64 ProjectWorldToScreen;

struct APlayerState
{
	FString GetPlayerName()
	{
		UObject* function = UObject::StaticFindObject(nullptr, nullptr, L"Engine.PlayerState.GetPlayerName", false);
		if (!function)
			return L"AAresPlayerCharacter_PC_C";

		struct {
			FString Return;
		}Args;
		function->ProcessEvent(this, function, &Args);
		return Args.Return;
	}
};


struct FQuat
{
public:

	float X, Y, Z, W;

	FQuat() : X(0.f), Y(0.f), Z(0.f), W(0.f) {};

	FQuat(float InX, float InY, float InZ, float InW) : X(InX), Y(InY), Z(InZ), W(InW) {}

	FQuat(struct FRotator& R);

	FVector RotateVector(const struct FVector& V) const;
};
struct FRotator
{
	float Pitch, Yaw, Roll;

	FRotator()
		: Pitch(0), Yaw(0), Roll(0)
	{ }

	FRotator(float pitch, float yaw, float roll) : Pitch(pitch), Yaw(yaw), Roll(roll) {}

	FRotator operator+ (const FRotator& other) const { return FRotator(Pitch + other.Pitch, Yaw + other.Yaw, Roll + other.Roll); }

	FRotator operator- (const FRotator& other) const { return FRotator(Pitch - other.Pitch, Yaw - other.Yaw, Roll - other.Roll); }

	FRotator operator* (float scalar) const { return FRotator(Pitch * scalar, Yaw * scalar, Roll * scalar); }

	FRotator& operator=  (const FRotator& other) { Pitch = other.Pitch; Yaw = other.Yaw; Roll = other.Roll; return *this; }

	FRotator& operator+= (const FRotator& other) { Pitch += other.Pitch; Yaw += other.Yaw; Roll += other.Roll; return *this; }

	FRotator& operator-= (const FRotator& other) { Pitch -= other.Pitch; Yaw -= other.Yaw; Roll -= other.Roll; return *this; }

	FRotator& operator*= (const float other) { Yaw *= other; Pitch *= other; Roll *= other; return *this; }

	struct FQuat Quaternion() const;
};

constexpr auto PI = 3.1415926535897932f;
constexpr auto FLOAT_NON_FRACTIONAL = 8388608.f /* All single-precision floating point numbers greater than or equal to this have no fractional value. */;
constexpr auto INV_PI = 0.31830988618f;
constexpr auto HALF_PI = 1.57079632679f;
constexpr auto DEG_TO_RAD = PI / 180.f;
constexpr auto RADS_DIVIDED_BY_2 = DEG_TO_RAD / 2.f;

namespace classes {
	namespace defines {
		static UObject* system = nullptr;
		static UObject* game_statics = nullptr;
		static UObject* blueprint = nullptr;
		static UObject* content_library = nullptr;
	}

	static inline void init() {
		defines::system = UObject::StaticFindObject(nullptr, nullptr, L"Engine.Default__KismetSystemLibrary", false);
		defines::game_statics = UObject::StaticFindObject(nullptr, nullptr, L"Engine.Default__GameplayStatics", false);
		defines::blueprint = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.Default__ShooterBlueprintLibrary", false);
		defines::content_library = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.Default__ContentLibrary", false);
	}
}

namespace kismentsystemlibrary
{
	UObject* static_class()
	{
		return UObject::StaticFindObject(nullptr, nullptr, L"Engine.Default__KismetSystemLibrary", false);
	}

	FString get_object_name(UObject* obj)
	{
		UObject* functions = UObject::StaticFindObject(nullptr, nullptr, L"Engine.KismentSystemLibrary.GetObjectName", false);
		if (!functions)
			return L"N/A";
		struct
		{
			UObject* obj;
			FString out;
		}Args;
		Args.obj = obj;
		functions->ProcessEvent(static_class(), functions, &Args);
		return Args.out;
	}
}
struct FMath {
	static __forceinline void SinCos(float* ScalarSin, float* ScalarCos, float  Value);
	static __forceinline float Fmod(float X, float Y);
	template<class T>
	static __forceinline T Clamp(const T X, const T Min, const T Max) { return X < Min ? Min : X < Max ? X : Max; }
};

struct FTransform
{
	FQuat Rotation;
	FVector Translation;
	char UnknownData00[0x4];
	FVector Scale3D;
	char UnknownData01[0x4];

	/** Default constructor. */
	FTransform() : Rotation(0.f, 0.f, 0.f, 1.f), Translation(0.f), Scale3D(FVector::OneVector) {};
	 
	FVector TransformPosition(FVector& V) const;

	FTransform(const FRotator& InRotation) : Rotation(InRotation.Quaternion()), Translation(FVector::ZeroVector), Scale3D(FVector::OneVector) {};
};


struct AShooterCharacter : UObject
{
	void ClientFly()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.ShooterCharacter.ClientFly", false);
		if (!Function)
		{
			return;
		}
		struct
		{
		}Parameters;
		Function->ProcessEvent(this, Function, &Parameters);
		return;
	}
	void Set3pMeshVisible(bool val)
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.ShooterCharacter.Set3PMeshVisible", false);
		if (!Function)
		{
			return;
		}
		struct
		{
			bool a1;
		}Parameters;
		Parameters.a1 = val;
		Function->ProcessEvent(this, Function, &Parameters);
		return;
	}
	APlayerState* GetPlayerState()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.ShooterCharacter.GetPlayerState", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			APlayerState* Out;
		}Parameters;
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.Out;
	}

	int32_t GetMaxHealth()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.ShooterCharacter.GetMaxHealth", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			int32_t Out;
		}Parameters;
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.Out;
	}
	float GetHealth()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.ShooterCharacter.GetHealth", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			float Out;
		}Parameters;
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.Out;
	}
	FVector K2_GetActorLocation()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"Engine.Actor.K2_GetActorLocation", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			FVector Out;
		}Parameters;
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.Out;
	}
	FRotator K2_GetActorRotation()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"Engine.Actor.K2_GetActorRotation", false);
		if (!Function)
		{
			return {0,0,0};
		}
		struct
		{
			FRotator Out;
		}Parameters;
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.Out;
	}
	USkeletalMeshComponent* GetPawnMesh()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.ShooterCharacter.GetPawnMesh", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			USkeletalMeshComponent* Out;
		}Parameters;
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.Out;
	}

	APlayerState* GetState()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.ShooterCharacter.GetPlayerState", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			APlayerState* KekState;
		}Parameters;
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.KekState;
	}
	bool IsAlive()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.ShooterCharacter.IsAlive", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			bool Out;
		}Parameters;
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.Out;
	}
};

struct APlayerCameraManager
{
	FVector GetCameraLocation()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"Engine.PlayerCameraManager.GetCameraLocation", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			FVector Out;
		}Parameters; 
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.Out;
	}
};
struct APlayerController : UObject
{
	bool LineOfSightTo(AShooterCharacter* Actor, FVector ViewPoint, bool bAlternateChecks)
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"Engine.Controller.LineOfSightTo", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			AShooterCharacter* Actor;
			FVector ViewPoint;
			bool bAlternateChecks;
			bool Out;
		}Parameters;
		Parameters.Actor = Actor;
		Parameters.ViewPoint = ViewPoint;
		Parameters.bAlternateChecks = bAlternateChecks;
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.Out;
	}
	void ExecSetCameraRotator(FRotator NewRot)
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"Engine.Controller.SetControlRotation", false);
		if (!Function)
		{
			return;
		}
		struct
		{
			FRotator Rot;
		}Parameters;
		Parameters.Rot = NewRot;
		Function->ProcessEvent(this, Function, &Parameters);
		return;
	}
	bool ProjectWorldLocationToScreen(struct FVector WorldLocation, struct FVector2D& ScreenLocation, bool bPlayerViewportRelative)
	{  
		if (!ProjectWorldToScreen)
			ProjectWorldToScreen = (uintptr_t)GetModuleHandleA(0) + 0x4fd7c60;
		auto WorldToScreen = reinterpret_cast<bool(__fastcall*)(uintptr_t pPlayerController, FVector vWorldPos, FVector2D * vScreenPosOut, char)>(ProjectWorldToScreen);

		WorldToScreen((uintptr_t)this, WorldLocation, &ScreenLocation, (char)0);
		 
		return WorldToScreen;
	}
	void set_fov(float fov)
	{
		UObject* function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.AresPlayerController.SetFOV", false);


		struct {
			float fov;
		}Args;
		Args.fov = fov;
		function->ProcessEvent(this, function, &Args);
	}

	AShooterCharacter* GetShooterCharacter()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.AresPlayerController.GetShooterCharacter", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			AShooterCharacter* Out;
		}Parameters;
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.Out;
	}
};

struct AController
{
};
namespace ShooterGameBlueprints
{
	UObject* Static_Class()
	{
		return UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.Default__ShooterBlueprintLibrary", false);
	}

	APlayerController* GetFirstLocalPlayerController(UWorld* WorldContextObject)
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.ShooterBlueprintLibrary.GetFirstLocalPlayerController", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			UWorld* WorldContextObject;
			APlayerController* Out;
		}Parameters;
		Parameters.WorldContextObject = WorldContextObject;
		Function->ProcessEvent(Static_Class(), Function, &Parameters);
		return Parameters.Out;
	}
	TArray<AShooterCharacter*> FindAllShooterCharactersWithAlliance(UWorld* WorldContextObject, AShooterCharacter* LocalViewer, EAresAlliance Alliance, bool OnlyPlayerControlled, bool OnlyAlivePlayers)
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.ShooterBlueprintLibrary.FindAllShooterCharactersWithAlliance", false);
		struct
		{
			UWorld* WorldContextObject;
			AShooterCharacter* LocalViewer;
			EAresAlliance Alliance;
			bool OnlyPlayerControlled;
			bool OnlyAlivePlayers;
			TArray<AShooterCharacter*> Out;
		}Parameters;
		Parameters.WorldContextObject = WorldContextObject;
		Parameters.LocalViewer = LocalViewer;
		Parameters.Alliance = Alliance;
		Parameters.OnlyPlayerControlled = OnlyPlayerControlled;
		Parameters.OnlyAlivePlayers = OnlyAlivePlayers;
		Function->ProcessEvent(Static_Class(), Function, &Parameters);
		return Parameters.Out;
	}
}

namespace AresOutlineRendering
{
	UObject* Static_Class()
	{
		return UObject::StaticFindObject(nullptr, nullptr, L"Renderer.Default__AresOutlineRendering", false);
	}

	void SetOutlineColorsForRender(UWorld* WorldContextObject, FLinearColor AllyColor, FLinearColor EnemyColor)
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"Renderer.AresOutlineRendering.SetOutlineColorsForRender", false);
		if (!Function)
		{
			return;
		}
		struct {
			UWorld* WorldContextObject;
			FLinearColor AllyColor;
			FLinearColor EnemyColor;
		}Parameters;
		Parameters.WorldContextObject = WorldContextObject;
		Parameters.AllyColor = AllyColor;
		Parameters.EnemyColor = EnemyColor;
		Function->ProcessEvent(Static_Class(), Function, &Parameters);
	}
}

namespace BaseTeamComponent
{
	UObject* Static_Class()
	{
		return UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.Default__BaseTeamComponent", false);
	}

	bool IsAlly(AShooterCharacter* Enemy, AShooterCharacter* Self)
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.BaseTeamComponent.IsAlly", false);
		struct {
			AShooterCharacter* Enemy;
			AShooterCharacter* Self;
			bool ReturnValue;
		}Parameters;
		Parameters.Enemy = Enemy;
		Parameters.Self = Self;
		Function->ProcessEvent(Static_Class(), Function, &Parameters);
		return Parameters.ReturnValue;
	}
}
#pragma once
#include <Windows.h>

namespace CWINGui
{
	namespace Input
	{
		bool mouseDown[5];
		bool mouseDownAlready[256];

		bool keysDown[256];
		bool keysDownAlready[256];

		bool IsAnyMouseDown()
		{
			if (mouseDown[0]) return true;
			if (mouseDown[1]) return true;
			if (mouseDown[2]) return true;
			if (mouseDown[3]) return true;
			if (mouseDown[4]) return true;

			return false;
		}

		bool IsMouseClicked(int button, int element_id, bool repeat)
		{
			if (mouseDown[button])
			{
				if (!mouseDownAlready[element_id])
				{
					mouseDownAlready[element_id] = true;
					return true;
				}
				if (repeat)
					return true;
			}
			else
			{
				mouseDownAlready[element_id] = false;
			}
			return false;
		}
		bool IsKeyPressed(int key, bool repeat)
		{
			if (keysDown[key])
			{
				if (!keysDownAlready[key])
				{
					keysDownAlready[key] = true;
					return true;
				}
				if (repeat)
					return true;
			}
			else
			{
				keysDownAlready[key] = false;
			}
			return false;
		}

		void Handle()
		{
			if (GetAsyncKeyState(0x01))
				mouseDown[0] = true;
			else
				mouseDown[0] = false;
		}
	}
}

wchar_t* s2wc(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

namespace CWINGui
{
	FLinearColor RGBtoFLC69(float R, float G, float B, float A = 255)
	{
		return { R / 255, G / 255, B / 255, A / 255 };
	}
	namespace Colors
	{
		FLinearColor Text{ 1.0f, 1.0f, 1.0f, 1.0f };
		FLinearColor Text_Shadow{ 0.0f, 0.0f, 0.0f, 0.0f };
		FLinearColor Text_Outline{ 0.0f, 0.0f, 0.0f, 0.30f };

		FLinearColor Window_Background{ 0.009f, 0.009f, 0.009f, 1.0f };
		FLinearColor Window_Header{ 0.10f, 0.15f, 0.84f, 1.0f };

		FLinearColor Button_Idle{ 0.10f, 0.15f, 0.84f, 1.0f };
		FLinearColor Button_Hovered{ 0.15f, 0.20f, 0.89f, 1.0f };
		FLinearColor Button_Active{ 0.20f, 0.25f, 0.94f, 1.0f };

		FLinearColor Checkbox_Idle{ 0.0f,0.0f,0.0f,1.0f };
		FLinearColor Checkbox_Hovered{ 1.0f,1.0f,1.0f,1.0f };
		FLinearColor Checkbox_Enabled{ 1.0f,1.0f,1.0f,1.0f };

		FLinearColor Combobox_Idle{ 0.17f, 0.16f, 0.23f, 1.0f };
		FLinearColor Combobox_Hovered{ 0.17f, 0.16f, 0.23f, 1.0f };
		FLinearColor Combobox_Elements{ 0.239f, 0.42f, 0.82f, 1.0f };

		FLinearColor Slider_Idle{ 1.0f,1.0f,1.0f,1.0f };
		FLinearColor Slider_Hovered{ 1.0f,1.0f,1.0f,1.0f };
		FLinearColor Slider_Progress{ 0.0f,0.0f,0.0f,1.0f };
		FLinearColor Slider_Button{ 0.0f,0.0f,0.0f,1.0f };

		FLinearColor ColorPicker_Background{ 0.0f,0.0f,0.0f,1.0f };
	}

	namespace PostRenderer
	{
		struct DrawList
		{
			int type = -1; //1 = FilledRect, 2 = TextLeft, 3 = TextCenter, 4 = Draw_Line
			FVector2D pos;
			FVector2D size;
			FLinearColor color;
			char* name;
			bool outline;

			FVector2D from;
			FVector2D to;
			int thickness;
		};
		DrawList drawlist[128];

		void drawFilledRect(FVector2D pos, float w, float h, FLinearColor color)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 1;
					drawlist[i].pos = pos;
					drawlist[i].size = FVector2D{ w, h };
					drawlist[i].color = color;
					return;
				}
			}
		}
		void TextLeft(char* name, FVector2D pos, FLinearColor color, bool outline)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 2;
					drawlist[i].name = name;
					drawlist[i].pos = pos;
					drawlist[i].outline = outline;
					drawlist[i].color = color;
					return;
				}
			}
		}
		void TextCenter(char* name, FVector2D pos, FLinearColor color, bool outline)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 3;
					drawlist[i].name = name;
					drawlist[i].pos = pos;
					drawlist[i].outline = outline;
					drawlist[i].color = color;
					return;
				}
			}
		}
		void Draw_Line(FVector2D from, FVector2D to, int thickness, FLinearColor color)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 4;
					drawlist[i].from = from;
					drawlist[i].to = to;
					drawlist[i].thickness = thickness;
					drawlist[i].color = color;
					return;
				}
			}
		}
	}

	UCanvas* canvas;


	bool hover_element = false;
	FVector2D menu_pos = FVector2D{ 0, 0 };
	float offset_x = 0.0f;
	float offset_y = 0.0f;

	FVector2D first_element_pos = FVector2D{ 0, 0 };

	FVector2D last_element_pos = FVector2D{ 0, 0 };
	FVector2D last_element_size = FVector2D{ 0, 0 };

	int current_element = -1;
	FVector2D current_element_pos = FVector2D{ 0, 0 };
	FVector2D current_element_size = FVector2D{ 0, 0 };
	int elements_count = 0;

	bool sameLine = false;

	bool pushY = false;
	float pushYvalue = 0.0f;

	void SetupCanvas(UCanvas* _canvas)
	{
		canvas = _canvas;
	}

	FVector2D CursorPos()
	{
		POINT cursorPos;
		GetCursorPos(&cursorPos);
		return FVector2D{ (float)cursorPos.x, (float)cursorPos.y };
	}
	bool MouseInZone(FVector2D pos, FVector2D size)
	{
		FVector2D cursor_pos = CursorPos();

		if (cursor_pos.X > pos.X && cursor_pos.Y > pos.Y)
			if (cursor_pos.X < pos.X + size.X && cursor_pos.Y < pos.Y + size.Y)
				return true;

		return false;
	}

	void Draw_Cursor(bool toogle)
	{
		if (toogle)
		{
			FVector2D cursorPos = CursorPos();
			canvas->K2_DrawLine(FVector2D{ cursorPos.X, cursorPos.Y }, FVector2D{ cursorPos.X + 35, cursorPos.Y + 10 }, 1, FLinearColor{ 0.30f, 0.30f, 0.80f, 1.0f });


			int x = 35;
			int y = 10;
			while (y != 30) //20 steps
			{
				x -= 1; if (x < 15) x = 15;
				y += 1; if (y > 30) y = 30;

				canvas->K2_DrawLine(FVector2D{ cursorPos.X, cursorPos.Y }, FVector2D{ cursorPos.X + x, cursorPos.Y + y }, 1, FLinearColor{ 0.30f, 0.30f, 0.80f, 1.0f });
			}

			canvas->K2_DrawLine(FVector2D{ cursorPos.X, cursorPos.Y }, FVector2D{ cursorPos.X + 15, cursorPos.Y + 30 }, 1, FLinearColor{ 0.30f, 0.30f, 0.80f, 1.0f });
			canvas->K2_DrawLine(FVector2D{ cursorPos.X + 35, cursorPos.Y + 10 }, FVector2D{ cursorPos.X + 15, cursorPos.Y + 30 }, 1, FLinearColor{ 0.30f, 0.30f, 0.80f, 1.0f });
		}
	}

	void SameLine()
	{
		sameLine = true;
	}
	void PushNextElementY(float y, bool from_last_element = true)
	{
		pushY = true;
		if (from_last_element)
			pushYvalue = last_element_pos.Y + last_element_size.Y + y;
		else
			pushYvalue = y;
	}
	void NextColumn(float x)
	{
		offset_x = x;
		PushNextElementY(first_element_pos.Y, false);
	}
	void ClearFirstPos()
	{
		first_element_pos = FVector2D{ 0, 0 };
	}

	void xDrawTextRGB(const wchar_t* text, float x, float y, FLinearColor color)
	{
		canvas->K2_DrawText(text, { x, y }, { 1.1, 1.1 }, { 0.f,0.f,0.f,1.0f }, 0.f, { 0, 0, 0, 1 }, { 0, 0 }, 0, 0, 0, { 0, 0, 0, 1 });
	}
	void yDrawTextRGB(const wchar_t* text, float x, float y, FLinearColor color)
	{
		canvas->K2_DrawText(text, { x, y }, { 1.1, 1.1 }, {0.f,0.f,0.f,1.0f}, 0.f, {0, 0, 0, 1}, {0, 0}, 1, 0, 0, {0, 0, 0, 1});
	}
	void TextLeft(const wchar_t* name, FVector2D pos, FLinearColor color, bool outline)
	{ 
		xDrawTextRGB(name, pos.X, pos.Y, {1,1,1,1});
	}
	void TextCenter(const wchar_t* name, FVector2D pos, FLinearColor color, bool outline, bool kekw = 0)
	{
		if(kekw)
			yDrawTextRGB(name, pos.X, pos.Y - 10, color);
		else
			yDrawTextRGB(name, pos.X, pos.Y - 10, {0.f,0.f,0.f,1.0f});
	}

	void GetColor(FLinearColor* color, float* r, float* g, float* b, float* a)
	{
		*r = color->R;
		*g = color->G;
		*b = color->B;
		*a = color->A;
	}
	UINT32 GetColorUINT(int r, int g, int b, int a)
	{
		UINT32 result = (BYTE(a) << 24) + (BYTE(r) << 16) + (BYTE(g) << 8) + BYTE(b);
		return result;
	}

	void Draw_Line(FVector2D from, FVector2D to, int thickness, FLinearColor color)
	{
		canvas->K2_DrawLine(FVector2D{ from.X, from.Y }, FVector2D{ to.X, to.Y }, thickness, color);
	}
	void drawFilledRect(FVector2D initial_pos, float w, float h, FLinearColor color)
	{
		for (float i = 0.0f; i < h; i += 1.0f)
			canvas->K2_DrawLine(FVector2D{ initial_pos.X, initial_pos.Y + i }, FVector2D{ initial_pos.X + w, initial_pos.Y + i }, 1.0f, color);
	}
	void DrawFilledCircle(FVector2D pos, float r, FLinearColor color)
	{
		float smooth = 0.07f;

		double PI = 3.14159265359;
		int size = (int)(2.0f * PI / smooth) + 1;

		float angle = 0.0f;
		int i = 0;

		for (; angle < 2 * PI; angle += smooth, i++)
		{
			Draw_Line(FVector2D{ pos.X, pos.Y }, FVector2D{ pos.X + cosf(angle) * r, pos.Y + sinf(angle) * r }, 1.0f, color);
		}
	}
	void DrawCircle(FVector2D pos, int radius, int numSides, FLinearColor Color)
	{
		float PI = 3.1415927f;

		float Step = PI * 2.0 / numSides;
		int Count = 0;
		FVector2D V[128];
		for (float a = 0; a < PI * 2.0; a += Step) {
			float X1 = radius * cos(a) + pos.X;
			float Y1 = radius * sin(a) + pos.Y;
			float X2 = radius * cos(a + Step) + pos.X;
			float Y2 = radius * sin(a + Step) + pos.Y;
			V[Count].X = X1;
			V[Count].Y = Y1;
			V[Count + 1].X = X2;
			V[Count + 1].Y = Y2;
			//Draw_Line(FVector2D{ pos.X, pos.Y }, FVector2D{ X2, Y2 }, 1.0f, Color); // Points from Centre to ends of circle
			Draw_Line(FVector2D{ V[Count].X, V[Count].Y }, FVector2D{ X2, Y2 }, 1.0f, Color);// Circle Around
		}
	}

	FVector2D dragPos;
	bool Window(const char* name, FVector2D* pos, FVector2D size, bool isOpen)
	{
		elements_count = 0;

		if (!isOpen)
			return false;

		bool isHovered = MouseInZone(FVector2D{ pos->X, pos->Y }, size);

		//Drop last element
		if (current_element != -1 && !GetAsyncKeyState(0x1))
		{
			current_element = -1;
		}

		//Drag
		if (hover_element && GetAsyncKeyState(0x1))
		{

		}
		else if ((isHovered || dragPos.X != 0) && !hover_element)
		{
			if (Input::IsMouseClicked(0, elements_count, true))
			{
				FVector2D cursorPos = CursorPos();

				cursorPos.X -= size.X;
				cursorPos.Y -= size.Y;

				if (dragPos.X == 0)
				{
					dragPos.X = (cursorPos.X - pos->X);
					dragPos.Y = (cursorPos.Y - pos->Y);
				}
				pos->X = cursorPos.X - dragPos.X;
				pos->Y = cursorPos.Y - dragPos.Y;
			}
			else
			{
				dragPos = FVector2D{ 0, 0 };
			}
		}
		else
		{
			hover_element = false;
		}


		offset_x = 0.0f; offset_y = 0.0f;
		menu_pos = FVector2D{ pos->X, pos->Y };
		first_element_pos = FVector2D{ 0, 0 };
		current_element_pos = FVector2D{ 0, 0 };
		current_element_size = FVector2D{ 0, 0 };

		//Bg
		drawFilledRect(FVector2D{ pos->X, pos->Y }, size.X, size.Y, RGBtoFLC69(255,255,255));
		//drawFilledRect(FVector2D{ pos->X, pos->Y }, 122, size.Y, FLinearColor{ 0.006f, 0.006f, 0.006f, 1.0f });//My tabs bg

		//Header
		//drawFilledRect(FVector2D{ pos->X, pos->Y }, size.X, 25.0f, RGBtoFLC69(255,0,0));

		offset_y += 25.0f;

		//Title
		FVector2D titlePos = FVector2D{ pos->X + size.X / 2, pos->Y + 25 / 2 };
		TextLeft(s2wc(name), titlePos, FLinearColor{0.0f,0.0f,0.0f,0.0f}, false);

		return true;
	}

	void Text(const wchar_t* text, bool center = false, bool outline = false)
	{
		elements_count++;

		float size = 25;
		FVector2D padding = FVector2D{ 10, 10 };
		FVector2D pos = FVector2D{ menu_pos.X + padding.X + offset_x, menu_pos.Y + padding.Y + offset_y };
		if (sameLine)
		{
			pos.X = last_element_pos.X + last_element_size.X + padding.X;
			pos.Y = last_element_pos.Y;
		}
		if (pushY)
		{
			pos.Y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.Y - menu_pos.Y;
		}

		if (!sameLine)
			offset_y += size + padding.Y;

		//Text
		FVector2D textPos = FVector2D{ pos.X + 5.0f, pos.Y + size / 2 };
		if (center)
			TextCenter(text, textPos, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);
		else
			TextLeft(text, textPos, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);

		sameLine = false;
		last_element_pos = pos;
		//last_element_size = size;
		if (first_element_pos.X == 0.0f)
			first_element_pos = pos;
	}
	bool ButtonTab(const wchar_t* name, FVector2D size, bool active)
	{
		elements_count++;

		FVector2D padding = FVector2D{ 5, 10 };
		FVector2D pos = FVector2D{ menu_pos.X + padding.X + offset_x, menu_pos.Y + padding.Y + offset_y };
		if (sameLine)
		{
			pos.X = last_element_pos.X + last_element_size.X ;
			pos.Y = last_element_pos.Y;
		}
		if (pushY)
		{
			pos.Y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.Y - menu_pos.Y;
		}
		bool isHovered = MouseInZone(FVector2D{ pos.X, pos.Y }, size);

		//Bg
		if (active)
		{
			drawFilledRect(FVector2D{ pos.X, pos.Y }, size.X, size.Y,  RGBtoFLC69(255,0,0,160));
		}
		else if (isHovered)
		{
			drawFilledRect(FVector2D{ pos.X, pos.Y }, size.X, size.Y, RGBtoFLC69(255, 0, 0, 180));
			hover_element = true;
		}
		else
		{
			drawFilledRect(FVector2D{ pos.X, pos.Y }, size.X, size.Y, RGBtoFLC69(255, 0, 0, 255));
		}

		if (!sameLine)
			offset_y += size.Y + padding.Y;

		//Text
		FVector2D textPos = FVector2D{ pos.X + size.X / 2, pos.Y + size.Y / 2 };
		if(active)
			TextCenter(name, textPos, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, 1);
		else
			TextCenter(name, textPos, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, 1);


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.X == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			return true;

		return false;
	}
	bool Button(const wchar_t* name, FVector2D size)
	{
		elements_count++;

		FVector2D padding = FVector2D{ 5, 10 };
		FVector2D pos = FVector2D{ menu_pos.X + padding.X + offset_x, menu_pos.Y + padding.Y + offset_y };
		if (sameLine)
		{
			pos.X = last_element_pos.X + last_element_size.X + padding.X;
			pos.Y = last_element_pos.Y;
		}
		if (pushY)
		{
			pos.Y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.Y - menu_pos.Y;
		}
		bool isHovered = MouseInZone(FVector2D{ pos.X, pos.Y }, size);

		//Bg
		if (isHovered)
		{
			drawFilledRect(FVector2D{ pos.X, pos.Y }, size.X, size.Y, Colors::Button_Hovered);
			hover_element = true;
		}
		else
		{
			drawFilledRect(FVector2D{ pos.X, pos.Y }, size.X, size.Y, Colors::Button_Idle);
		}

		if (!sameLine)
			offset_y += size.Y + padding.Y;

		//Text
		FVector2D textPos = FVector2D{ pos.X + size.X / 2, pos.Y + size.Y / 2 };
		//if (!TextOverlapedFromActiveElement(textPos))
		TextCenter(name, textPos, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.X == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			return true;

		return false;
	}
	void Checkbox(const wchar_t* name, bool* value)
	{
		elements_count++;

		float size = 18;
		FVector2D padding = FVector2D{ 10, 10 };
		FVector2D pos = FVector2D{ menu_pos.X + padding.X + offset_x, menu_pos.Y + padding.Y + offset_y };
		if (sameLine)
		{
			pos.X = last_element_pos.X + last_element_size.X + padding.X;
			pos.Y = last_element_pos.Y;
		}
		if (pushY)
		{
			pos.Y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.Y - menu_pos.Y;
		}
		bool isHovered = MouseInZone(FVector2D{ pos.X, pos.Y }, FVector2D{ size, size });

		//Bg
		if (isHovered)
		{
			drawFilledRect(FVector2D{ pos.X, pos.Y }, size, size, Colors::Checkbox_Hovered);
			hover_element = true;
		}
		else
		{
			drawFilledRect(FVector2D{ pos.X + 3, pos.Y + 3 }, size - 6, size - 6, Colors::Checkbox_Enabled);
		}

		if (!sameLine)
			offset_y += size + padding.Y;

		if (*value)
		{
			drawFilledRect(FVector2D{ pos.X, pos.Y }, size, size, Colors::Checkbox_Idle);
			//drawFilledRect(FVector2D{ pos.X + 9, pos.Y + 9 }, size - 18, size - 18, Colors::Checkbox_Hovered);
		}



		//Text
		FVector2D textPos = FVector2D{ pos.X + size + 5.0f, pos.Y  };
		//if (!TextOverlapedFromActiveElement(textPos))
		TextLeft(name, textPos, FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f }, false);


		sameLine = false;
		last_element_pos = pos;
		//last_element_size = size;
		if (first_element_pos.X == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			*value = !*value;
	}
	void SliderInt(char* name, int* value, int min, int max)
	{
		elements_count++;

		FVector2D size = FVector2D{ 240, 50 };
		FVector2D slider_size = FVector2D{ 200, 10 };
		FVector2D padding = FVector2D{ 10, 15 };
		FVector2D pos = FVector2D{ menu_pos.X + padding.X + offset_x, menu_pos.Y + padding.Y + offset_y };
		if (sameLine)
		{
			pos.X = last_element_pos.X + last_element_size.X + padding.X;
			pos.Y = last_element_pos.Y;
		}
		if (pushY)
		{
			pos.Y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.Y - menu_pos.Y;
		}
		bool isHovered = MouseInZone(FVector2D{ pos.X, pos.Y + slider_size.Y + padding.Y }, slider_size);

		if (!sameLine)
			offset_y += size.Y + padding.Y;

		//Bg
		if (isHovered || current_element == elements_count)
		{
			//Drag
			if (Input::IsMouseClicked(0, elements_count, true))
			{
				current_element = elements_count;

				FVector2D cursorPos = CursorPos();
				*value = ((cursorPos.X - pos.X) * ((max - min) / slider_size.X)) + min;
				if (*value < min) *value = min;
				if (*value > max) *value = max;
			}

			drawFilledRect(FVector2D{ pos.X, pos.Y + slider_size.Y + padding.Y }, slider_size.X, slider_size.Y, Colors::Slider_Hovered);
			drawFilledRect(FVector2D{ pos.X, pos.Y + slider_size.Y + padding.Y + 5.0f }, 5.0f, 5.0f, Colors::Slider_Progress);

			hover_element = true;
		}
		else
		{
			drawFilledRect(FVector2D{ pos.X, pos.Y + slider_size.Y + padding.Y }, slider_size.X, slider_size.Y, Colors::Slider_Idle);
			drawFilledRect(FVector2D{ pos.X, pos.Y + slider_size.Y + padding.Y + 5.0f }, 5.0f, 5.0f, Colors::Slider_Progress);
		}


		//Value
		float oneP = slider_size.X / (max - min);
		drawFilledRect(FVector2D{ pos.X, pos.Y + slider_size.Y + padding.Y }, oneP * (*value - min), slider_size.Y, Colors::Slider_Progress);
		//drawFilledRect(FVector2D{ pos.X + oneP * (*value - min) - 10.0f, pos.Y + slider_size.Y - 5.0f + padding.Y }, 20.0f, 20.0f, Colors::Slider_Button);
		DrawFilledCircle(FVector2D{ pos.X + oneP * (*value - min), pos.Y + slider_size.Y + 3.3f + padding.Y }, 10.0f, Colors::Slider_Button);
		DrawFilledCircle(FVector2D{ pos.X + oneP * (*value - min), pos.Y + slider_size.Y + 3.3f + padding.Y }, 5.0f, Colors::Slider_Progress);
		 

		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.X == 0.0f)
			first_element_pos = pos;
	}
	void SliderFloat(const wchar_t* name, float* value, float min, float max, const char* format = "%.0f")
	{
		elements_count++;

		FVector2D size = FVector2D{ 210, 40 };
		FVector2D slider_size = FVector2D{ 170, 7 };
		FVector2D adjust_zone = FVector2D{ 0, 20 };
		FVector2D padding = FVector2D{ 10, 15 };
		FVector2D pos = FVector2D{ menu_pos.X + padding.X + offset_x, menu_pos.Y + padding.Y + offset_y };
		if (sameLine)
		{
			pos.X = last_element_pos.X + last_element_size.X + padding.X;
			pos.Y = last_element_pos.Y;
		}
		if (pushY)
		{
			pos.Y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.Y - menu_pos.Y;
		}
		bool isHovered = MouseInZone(FVector2D{ pos.X, pos.Y + slider_size.Y + padding.Y - adjust_zone.Y }, FVector2D{ slider_size.X, slider_size.Y + adjust_zone.Y * 1.5f });

		if (!sameLine)
			offset_y += size.Y + padding.Y;

		//Bg
		if (isHovered || current_element == elements_count)
		{
			//Drag
			if (Input::IsMouseClicked(0, elements_count, true))
			{
				current_element = elements_count;

				FVector2D cursorPos = CursorPos();
				*value = ((cursorPos.X - pos.X) * ((max - min) / slider_size.X)) + min;
				if (*value < min) *value = min;
				if (*value > max) *value = max;
			}

			drawFilledRect(FVector2D{ pos.X, pos.Y + slider_size.Y + padding.Y }, slider_size.X, slider_size.Y, Colors::Slider_Hovered);
			DrawFilledCircle(FVector2D{ pos.X, pos.Y + padding.Y + 9.3f }, 3.1f, Colors::Slider_Progress);
			DrawFilledCircle(FVector2D{ pos.X + slider_size.X, pos.Y + padding.Y + 9.3f }, 3.1f, Colors::Slider_Hovered);

			hover_element = true;
		}
		else
		{
			drawFilledRect(FVector2D{ pos.X, pos.Y + slider_size.Y + padding.Y }, slider_size.X, slider_size.Y, Colors::Slider_Idle);
			DrawFilledCircle(FVector2D{ pos.X, pos.Y + padding.Y + 9.3f }, 3.1f, Colors::Slider_Progress);
			DrawFilledCircle(FVector2D{ pos.X + slider_size.X, pos.Y + padding.Y + 9.3f }, 3.1f, Colors::Slider_Idle);
		}


		//Text
		FVector2D textPos = FVector2D{ pos.X, pos.Y + 5 };
		TextLeft(name, textPos, FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f }, false);

		//Value
		float oneP = slider_size.X / (max - min);
		drawFilledRect(FVector2D{ pos.X, pos.Y + slider_size.Y + padding.Y }, oneP * (*value - min), slider_size.Y, Colors::Slider_Progress);
		DrawFilledCircle(FVector2D{ pos.X + oneP * (*value - min), pos.Y + slider_size.Y + 2.66f + padding.Y }, 8.0f, Colors::Slider_Button);
		DrawFilledCircle(FVector2D{ pos.X + oneP * (*value - min), pos.Y + slider_size.Y + 2.66f + padding.Y }, 4.0f, Colors::Slider_Progress);
		 
		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.X == 0.0f)
			first_element_pos = pos;
	}



	bool checkbox_enabled[256];
	void Combobox(const wchar_t* name, FVector2D size, int* value, const char* arg, ...)
	{
		elements_count++;

		FVector2D padding = FVector2D{ 5, 10 };
		FVector2D pos = FVector2D{ menu_pos.X + padding.X + offset_x, menu_pos.Y + padding.Y + offset_y };
		if (sameLine)
		{
			pos.X = last_element_pos.X + last_element_size.X + padding.X;
			pos.Y = last_element_pos.Y;
		}
		if (pushY)
		{
			pos.Y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.Y - menu_pos.Y;
		}
		bool isHovered = MouseInZone(FVector2D{ pos.X, pos.Y }, size);

		//Bg
		if (isHovered || checkbox_enabled[elements_count])
		{
			drawFilledRect(FVector2D{ pos.X, pos.Y }, size.X, size.Y, Colors::Combobox_Hovered);

			hover_element = true;
		}
		else
		{
			drawFilledRect(FVector2D{ pos.X, pos.Y }, size.X, size.Y, Colors::Combobox_Idle);
		}

		if (!sameLine)
			offset_y += size.Y + padding.Y;

		//Text
		FVector2D textPos = FVector2D{ pos.X + size.X + 5.0f, pos.Y + size.Y / 2 };
		TextLeft(name, textPos, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

		//Elements
		bool isHovered2 = false;
		FVector2D element_pos = pos;
		int num = 0;

		if (checkbox_enabled[elements_count])
		{
			current_element_size.X = element_pos.X - 5.0f;
			current_element_size.Y = element_pos.Y - 5.0f;
		}
		va_list arguments;
		for (va_start(arguments, arg); arg != NULL; arg = va_arg(arguments, const char*))
		{
			//Selected Element
			if (num == *value)
			{
				FVector2D _textPos = FVector2D{ pos.X + size.X / 2, pos.Y + size.Y / 2 };
				TextCenter((const wchar_t*)arg, _textPos, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
			}

			if (checkbox_enabled[elements_count])
			{
				element_pos.Y += 25.0f;

				isHovered2 = MouseInZone(FVector2D{ element_pos.X, element_pos.Y }, FVector2D{ size.X, 25.0f });
				if (isHovered2)
				{
					hover_element = true;
					PostRenderer::drawFilledRect(FVector2D{ element_pos.X, element_pos.Y }, size.X, 25.0f, Colors::Combobox_Hovered);

					//Click
					if (Input::IsMouseClicked(0, elements_count, false))
					{
						*value = num;
						checkbox_enabled[elements_count] = false;
					}
				}
				else
				{
					PostRenderer::drawFilledRect(FVector2D{ element_pos.X, element_pos.Y }, size.X, 25.0f, Colors::Combobox_Idle);
				}

				PostRenderer::TextLeft((char*)arg, FVector2D{ element_pos.X + 5.0f, element_pos.Y + 15.0f }, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
			}
			num++;
		}
		va_end(arguments);
		if (checkbox_enabled[elements_count])
		{
			current_element_size.X = element_pos.X + 5.0f;
			current_element_size.Y = element_pos.Y + 5.0f;
		}


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.X == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
		{
			checkbox_enabled[elements_count] = !checkbox_enabled[elements_count];
		}
		if (!isHovered && !isHovered2 && Input::IsMouseClicked(0, elements_count, false))
		{
			checkbox_enabled[elements_count] = false;
		}
	}

	int active_hotkey = -1;
	bool already_pressed = false;
	std::string VirtualKeyCodeToString(UCHAR virtualKey)
	{
		UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);

		if (virtualKey == VK_LBUTTON)
		{
			return ("MOUSE0");
		}
		if (virtualKey == VK_RBUTTON)
		{
			return ("MOUSE1");
		}
		if (virtualKey == VK_MBUTTON)
		{
			return ("MBUTTON");
		}
		if (virtualKey == VK_XBUTTON1)
		{
			return ("XBUTTON1");
		}
		if (virtualKey == VK_XBUTTON2)
		{
			return ("XBUTTON2");
		}

		CHAR szName[128];
		int result = 0;
		switch (virtualKey)
		{
		case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
		case VK_RCONTROL: case VK_RMENU:
		case VK_LWIN: case VK_RWIN: case VK_APPS:
		case VK_PRIOR: case VK_NEXT:
		case VK_END: case VK_HOME:
		case VK_INSERT: case VK_DELETE:
		case VK_DIVIDE:
		case VK_NUMLOCK:
			scanCode |= KF_EXTENDED;
		default:
			result = GetKeyNameTextA(scanCode << 16, szName, 128);
		}

		return szName;
	}
	void Hotkey(const char* name, FVector2D size, int* key)
	{
		elements_count++;

		FVector2D padding = FVector2D{ 5, 10 };
		FVector2D pos = FVector2D{ menu_pos.X + padding.X + offset_x, menu_pos.Y + padding.Y + offset_y };
		if (sameLine)
		{
			pos.X = last_element_pos.X + last_element_size.X + padding.X;
			pos.Y = last_element_pos.Y + (last_element_size.Y / 2) - size.Y / 2;
		}
		if (pushY)
		{
			pos.Y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.Y - menu_pos.Y;
		}
		bool isHovered = MouseInZone(FVector2D{ pos.X, pos.Y }, size);

		//Bg
		if (isHovered)
		{
			drawFilledRect(FVector2D{ pos.X, pos.Y }, size.X, size.Y, Colors::Button_Hovered);
			hover_element = true;
		}
		else
		{
			drawFilledRect(FVector2D{ pos.X, pos.Y }, size.X, size.Y, Colors::Button_Idle);
		}

		if (!sameLine)
			offset_y += size.Y + padding.Y;

		if (active_hotkey == elements_count)
		{
			//Text
			FVector2D textPos = FVector2D{ pos.X + size.X / 2, pos.Y + size.Y / 2 };
			TextCenter((const wchar_t*)("[Press Key]"), textPos, FLinearColor{1.0f, 1.0f, 1.0f, 1.0f}, false);

			if (!CWINGui::Input::IsAnyMouseDown())
			{
				already_pressed = false;
			}

			if (!already_pressed)
			{
				for (int code = 0; code < 255; code++)
				{
					if (GetAsyncKeyState(code))
					{
						*key = code;
						active_hotkey = -1;
					}
				}
			}
		}
		else
		{
			//Text
			FVector2D textPos = FVector2D{ pos.X + size.X / 2, pos.Y + size.Y / 2 };
			TextCenter((const wchar_t*)VirtualKeyCodeToString(*key).c_str(), textPos, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

			if (isHovered)
			{
				if (Input::IsMouseClicked(0, elements_count, false))
				{
					already_pressed = true;
					active_hotkey = elements_count;

					//Queue Fix
					for (int code = 0; code < 255; code++)
						if (GetAsyncKeyState(code)) {}
				}
			}
			else
			{
				if (Input::IsMouseClicked(0, elements_count, false))
				{
					active_hotkey = -1;
				}
			}
		}


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.X == 0.0f)
			first_element_pos = pos;
	}

	int active_picker = -1;
	FLinearColor saved_color;
	bool ColorPixel(FVector2D pos, FVector2D size, FLinearColor* original, FLinearColor color)
	{
		PostRenderer::drawFilledRect(FVector2D{ pos.X, pos.Y }, size.X, size.Y, color);

		//Выбранный цвет
		if (original->R == color.R && original->G == color.G && original->B == color.B)
		{
			PostRenderer::Draw_Line(FVector2D{ pos.X, pos.Y }, FVector2D{ pos.X + size.X - 1, pos.Y }, 1.0f, FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
			PostRenderer::Draw_Line(FVector2D{ pos.X, pos.Y + size.Y - 1 }, FVector2D{ pos.X + size.X - 1, pos.Y + size.Y - 1 }, 1.0f, FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
			PostRenderer::Draw_Line(FVector2D{ pos.X, pos.Y }, FVector2D{ pos.X, pos.Y + size.Y - 1 }, 1.0f, FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
			PostRenderer::Draw_Line(FVector2D{ pos.X + size.X - 1, pos.Y }, FVector2D{ pos.X + size.X - 1, pos.Y + size.Y - 1 }, 1.0f, FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
		}

		//Смена цвета
		bool isHovered = MouseInZone(FVector2D{ pos.X, pos.Y }, size);
		if (isHovered)
		{
			if (Input::IsMouseClicked(0, elements_count, false))
				*original = color;
		}

		return true;
	}
	void ColorPicker(const wchar_t* name, FLinearColor* color)
	{
		elements_count++;

		float size = 25;
		FVector2D padding = FVector2D{ 10, 10 };
		FVector2D pos = FVector2D{ menu_pos.X + padding.X + offset_x, menu_pos.Y + padding.Y + offset_y };
		if (sameLine)
		{
			pos.X = last_element_pos.X + last_element_size.X + padding.X;
			pos.Y = last_element_pos.Y;
		}
		if (pushY)
		{
			pos.Y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.Y - menu_pos.Y;
		}
		bool isHovered = MouseInZone(FVector2D{ pos.X, pos.Y }, FVector2D{ size, size });

		if (!sameLine)
			offset_y += size + padding.Y;

		if (active_picker == elements_count)
		{
			hover_element = true;

			float sizePickerX = 250;
			float sizePickerY = 250;
			bool isHoveredPicker = MouseInZone(FVector2D{ pos.X, pos.Y }, FVector2D{ sizePickerX, sizePickerY - 60 });

			//Background
			PostRenderer::drawFilledRect(FVector2D{ pos.X, pos.Y }, sizePickerX, sizePickerY - 65, Colors::ColorPicker_Background);

			//float pixedSize = sizePickerY / pixels;
			//FLinearColor temp_color{1.0f, 1.0f, 1.0f, 1.0f};
			//float iterator = 0.0f;
			//
			//for (int y = 0; y < pixels; y++)
			//{
			//	for (int x = 0; x < pixels; x++)
			//	{
			//		ColorPixel(FVector2D{ pos.X + pixedSize * x, pos.Y + pixedSize * y }, pixedSize, color, temp_color);
			//		temp_color.R -= (1.0f - saved_color.R) / pixels;
			//		temp_color.G -= (1.0f - saved_color.G) / pixels;
			//		temp_color.B -= (1.0f - saved_color.B) / pixels;
			//	}
			//	
			//	iterator += 1.0f / pixels;
			//	temp_color = FLinearColor{ 1.0f - iterator, 1.0f - iterator, 1.0f - iterator, 1.0f };
			//}

			FVector2D pixelSize = FVector2D{ sizePickerX / 12, sizePickerY / 12 };

			//0
			{
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 0, pos.Y + pixelSize.Y * 0 }, pixelSize, color, FLinearColor{ 174 / 255.f, 235 / 255.f, 253 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 0, pos.Y + pixelSize.Y * 1 }, pixelSize, color, FLinearColor{ 136 / 255.f, 225 / 255.f, 251 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 0, pos.Y + pixelSize.Y * 2 }, pixelSize, color, FLinearColor{ 108 / 255.f, 213 / 255.f, 250 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 0, pos.Y + pixelSize.Y * 3 }, pixelSize, color, FLinearColor{ 89 / 255.f, 175 / 255.f, 213 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 0, pos.Y + pixelSize.Y * 4 }, pixelSize, color, FLinearColor{ 76 / 255.f, 151 / 255.f, 177 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 0, pos.Y + pixelSize.Y * 5 }, pixelSize, color, FLinearColor{ 60 / 255.f, 118 / 255.f, 140 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 0, pos.Y + pixelSize.Y * 6 }, pixelSize, color, FLinearColor{ 43 / 255.f, 85 / 255.f, 100 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 0, pos.Y + pixelSize.Y * 7 }, pixelSize, color, FLinearColor{ 32 / 255.f, 62 / 255.f, 74 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 0, pos.Y + pixelSize.Y * 8 }, pixelSize, color, FLinearColor{ 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.0f });
			}
			//1
			{
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 1, pos.Y + pixelSize.Y * 0 }, pixelSize, color, FLinearColor{ 175 / 255.f, 205 / 255.f, 252 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 1, pos.Y + pixelSize.Y * 1 }, pixelSize, color, FLinearColor{ 132 / 255.f, 179 / 255.f, 252 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 1, pos.Y + pixelSize.Y * 2 }, pixelSize, color, FLinearColor{ 90 / 255.f, 152 / 255.f, 250 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 1, pos.Y + pixelSize.Y * 3 }, pixelSize, color, FLinearColor{ 55 / 255.f, 120 / 255.f, 250 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 1, pos.Y + pixelSize.Y * 4 }, pixelSize, color, FLinearColor{ 49 / 255.f, 105 / 255.f, 209 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 1, pos.Y + pixelSize.Y * 5 }, pixelSize, color, FLinearColor{ 38 / 255.f, 83 / 255.f, 165 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 1, pos.Y + pixelSize.Y * 6 }, pixelSize, color, FLinearColor{ 28 / 255.f, 61 / 255.f, 120 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 1, pos.Y + pixelSize.Y * 7 }, pixelSize, color, FLinearColor{ 20 / 255.f, 43 / 255.f, 86 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 1, pos.Y + pixelSize.Y * 8 }, pixelSize, color, FLinearColor{ 247 / 255.f, 247 / 255.f, 247 / 255.f, 1.0f });
			}
			//2
			{
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 2, pos.Y + pixelSize.Y * 0 }, pixelSize, color, FLinearColor{ 153 / 255.f, 139 / 255.f, 250 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 2, pos.Y + pixelSize.Y * 1 }, pixelSize, color, FLinearColor{ 101 / 255.f, 79 / 255.f, 249 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 2, pos.Y + pixelSize.Y * 2 }, pixelSize, color, FLinearColor{ 64 / 255.f, 50 / 255.f, 230 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 2, pos.Y + pixelSize.Y * 3 }, pixelSize, color, FLinearColor{ 54 / 255.f, 38 / 255.f, 175 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 2, pos.Y + pixelSize.Y * 4 }, pixelSize, color, FLinearColor{ 39 / 255.f, 31 / 255.f, 144 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 2, pos.Y + pixelSize.Y * 5 }, pixelSize, color, FLinearColor{ 32 / 255.f, 25 / 255.f, 116 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 2, pos.Y + pixelSize.Y * 6 }, pixelSize, color, FLinearColor{ 21 / 255.f, 18 / 255.f, 82 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 2, pos.Y + pixelSize.Y * 7 }, pixelSize, color, FLinearColor{ 16 / 255.f, 13 / 255.f, 61 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 2, pos.Y + pixelSize.Y * 8 }, pixelSize, color, FLinearColor{ 228 / 255.f, 228 / 255.f, 228 / 255.f, 1.0f });
			}
			//3
			{
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 3, pos.Y + pixelSize.Y * 0 }, pixelSize, color, FLinearColor{ 194 / 255.f, 144 / 255.f, 251 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 3, pos.Y + pixelSize.Y * 1 }, pixelSize, color, FLinearColor{ 165 / 255.f, 87 / 255.f, 249 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 3, pos.Y + pixelSize.Y * 2 }, pixelSize, color, FLinearColor{ 142 / 255.f, 57 / 255.f, 239 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 3, pos.Y + pixelSize.Y * 3 }, pixelSize, color, FLinearColor{ 116 / 255.f, 45 / 255.f, 184 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 3, pos.Y + pixelSize.Y * 4 }, pixelSize, color, FLinearColor{ 92 / 255.f, 37 / 255.f, 154 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 3, pos.Y + pixelSize.Y * 5 }, pixelSize, color, FLinearColor{ 73 / 255.f, 29 / 255.f, 121 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 3, pos.Y + pixelSize.Y * 6 }, pixelSize, color, FLinearColor{ 53 / 255.f, 21 / 255.f, 88 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 3, pos.Y + pixelSize.Y * 7 }, pixelSize, color, FLinearColor{ 37 / 255.f, 15 / 255.f, 63 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 3, pos.Y + pixelSize.Y * 8 }, pixelSize, color, FLinearColor{ 203 / 255.f, 203 / 255.f, 203 / 255.f, 1.0f });
			}
			//4
			{
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 4, pos.Y + pixelSize.Y * 0 }, pixelSize, color, FLinearColor{ 224 / 255.f, 162 / 255.f, 197 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 4, pos.Y + pixelSize.Y * 1 }, pixelSize, color, FLinearColor{ 210 / 255.f, 112 / 255.f, 166 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 4, pos.Y + pixelSize.Y * 2 }, pixelSize, color, FLinearColor{ 199 / 255.f, 62 / 255.f, 135 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 4, pos.Y + pixelSize.Y * 3 }, pixelSize, color, FLinearColor{ 159 / 255.f, 49 / 255.f, 105 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 4, pos.Y + pixelSize.Y * 4 }, pixelSize, color, FLinearColor{ 132 / 255.f, 41 / 255.f, 89 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 4, pos.Y + pixelSize.Y * 5 }, pixelSize, color, FLinearColor{ 104 / 255.f, 32 / 255.f, 71 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 4, pos.Y + pixelSize.Y * 6 }, pixelSize, color, FLinearColor{ 75 / 255.f, 24 / 255.f, 51 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 4, pos.Y + pixelSize.Y * 7 }, pixelSize, color, FLinearColor{ 54 / 255.f, 14 / 255.f, 36 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 4, pos.Y + pixelSize.Y * 8 }, pixelSize, color, FLinearColor{ 175 / 255.f, 175 / 255.f, 175 / 255.f, 1.0f });
			}
			//5
			{
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 5, pos.Y + pixelSize.Y * 0 }, pixelSize, color, FLinearColor{ 235 / 255.f, 175 / 255.f, 176 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 5, pos.Y + pixelSize.Y * 1 }, pixelSize, color, FLinearColor{ 227 / 255.f, 133 / 255.f, 135 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 5, pos.Y + pixelSize.Y * 2 }, pixelSize, color, FLinearColor{ 219 / 255.f, 87 / 255.f, 88 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 5, pos.Y + pixelSize.Y * 3 }, pixelSize, color, FLinearColor{ 215 / 255.f, 50 / 255.f, 36 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 5, pos.Y + pixelSize.Y * 4 }, pixelSize, color, FLinearColor{ 187 / 255.f, 25 / 255.f, 7 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 5, pos.Y + pixelSize.Y * 5 }, pixelSize, color, FLinearColor{ 149 / 255.f, 20 / 255.f, 6 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 5, pos.Y + pixelSize.Y * 6 }, pixelSize, color, FLinearColor{ 107 / 255.f, 14 / 255.f, 4 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 5, pos.Y + pixelSize.Y * 7 }, pixelSize, color, FLinearColor{ 77 / 255.f, 9 / 255.f, 3 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 5, pos.Y + pixelSize.Y * 8 }, pixelSize, color, FLinearColor{ 144 / 255.f, 144 / 255.f, 144 / 255.f, 1.0f });
			}
			//6
			{
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 6, pos.Y + pixelSize.Y * 0 }, pixelSize, color, FLinearColor{ 241 / 255.f, 187 / 255.f, 171 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 6, pos.Y + pixelSize.Y * 1 }, pixelSize, color, FLinearColor{ 234 / 255.f, 151 / 255.f, 126 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 6, pos.Y + pixelSize.Y * 2 }, pixelSize, color, FLinearColor{ 229 / 255.f, 115 / 255.f, 76 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 6, pos.Y + pixelSize.Y * 3 }, pixelSize, color, FLinearColor{ 227 / 255.f, 82 / 255.f, 24 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 6, pos.Y + pixelSize.Y * 4 }, pixelSize, color, FLinearColor{ 190 / 255.f, 61 / 255.f, 15 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 6, pos.Y + pixelSize.Y * 5 }, pixelSize, color, FLinearColor{ 150 / 255.f, 48 / 255.f, 12 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 6, pos.Y + pixelSize.Y * 6 }, pixelSize, color, FLinearColor{ 107 / 255.f, 34 / 255.f, 8 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 6, pos.Y + pixelSize.Y * 7 }, pixelSize, color, FLinearColor{ 79 / 255.f, 25 / 255.f, 6 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 6, pos.Y + pixelSize.Y * 8 }, pixelSize, color, FLinearColor{ 113 / 255.f, 113 / 255.f, 113 / 255.f, 1.0f });
			}
			//7
			{
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 7, pos.Y + pixelSize.Y * 0 }, pixelSize, color, FLinearColor{ 245 / 255.f, 207 / 255.f, 169 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 7, pos.Y + pixelSize.Y * 1 }, pixelSize, color, FLinearColor{ 240 / 255.f, 183 / 255.f, 122 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 7, pos.Y + pixelSize.Y * 2 }, pixelSize, color, FLinearColor{ 236 / 255.f, 159 / 255.f, 74 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 7, pos.Y + pixelSize.Y * 3 }, pixelSize, color, FLinearColor{ 234 / 255.f, 146 / 255.f, 37 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 7, pos.Y + pixelSize.Y * 4 }, pixelSize, color, FLinearColor{ 193 / 255.f, 111 / 255.f, 28 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 7, pos.Y + pixelSize.Y * 5 }, pixelSize, color, FLinearColor{ 152 / 255.f, 89 / 255.f, 22 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 7, pos.Y + pixelSize.Y * 6 }, pixelSize, color, FLinearColor{ 110 / 255.f, 64 / 255.f, 16 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 7, pos.Y + pixelSize.Y * 7 }, pixelSize, color, FLinearColor{ 80 / 255.f, 47 / 255.f, 12 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 7, pos.Y + pixelSize.Y * 8 }, pixelSize, color, FLinearColor{ 82 / 255.f, 82 / 255.f, 82 / 255.f, 1.0f });
			}
			//8
			{
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 8, pos.Y + pixelSize.Y * 0 }, pixelSize, color, FLinearColor{ 247 / 255.f, 218 / 255.f, 170 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 8, pos.Y + pixelSize.Y * 1 }, pixelSize, color, FLinearColor{ 244 / 255.f, 200 / 255.f, 124 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 8, pos.Y + pixelSize.Y * 2 }, pixelSize, color, FLinearColor{ 241 / 255.f, 182 / 255.f, 77 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 8, pos.Y + pixelSize.Y * 3 }, pixelSize, color, FLinearColor{ 239 / 255.f, 174 / 255.f, 44 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 8, pos.Y + pixelSize.Y * 4 }, pixelSize, color, FLinearColor{ 196 / 255.f, 137 / 255.f, 34 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 8, pos.Y + pixelSize.Y * 5 }, pixelSize, color, FLinearColor{ 154 / 255.f, 108 / 255.f, 27 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 8, pos.Y + pixelSize.Y * 6 }, pixelSize, color, FLinearColor{ 111 / 255.f, 77 / 255.f, 19 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 8, pos.Y + pixelSize.Y * 7 }, pixelSize, color, FLinearColor{ 80 / 255.f, 56 / 255.f, 14 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 8, pos.Y + pixelSize.Y * 8 }, pixelSize, color, FLinearColor{ 54 / 255.f, 54 / 255.f, 54 / 255.f, 1.0f });
			}
			//9
			{
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 9, pos.Y + pixelSize.Y * 0 }, pixelSize, color, FLinearColor{ 254 / 255.f, 243 / 255.f, 187 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 9, pos.Y + pixelSize.Y * 1 }, pixelSize, color, FLinearColor{ 253 / 255.f, 237 / 255.f, 153 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 9, pos.Y + pixelSize.Y * 2 }, pixelSize, color, FLinearColor{ 253 / 255.f, 231 / 255.f, 117 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 9, pos.Y + pixelSize.Y * 3 }, pixelSize, color, FLinearColor{ 254 / 255.f, 232 / 255.f, 85 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 9, pos.Y + pixelSize.Y * 4 }, pixelSize, color, FLinearColor{ 242 / 255.f, 212 / 255.f, 53 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 9, pos.Y + pixelSize.Y * 5 }, pixelSize, color, FLinearColor{ 192 / 255.f, 169 / 255.f, 42 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 9, pos.Y + pixelSize.Y * 6 }, pixelSize, color, FLinearColor{ 138 / 255.f, 120 / 255.f, 30 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 9, pos.Y + pixelSize.Y * 7 }, pixelSize, color, FLinearColor{ 101 / 255.f, 87 / 255.f, 22 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 9, pos.Y + pixelSize.Y * 8 }, pixelSize, color, FLinearColor{ 29 / 255.f, 29 / 255.f, 29 / 255.f, 1.0f });
			}
			//10
			{
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 10, pos.Y + pixelSize.Y * 0 }, pixelSize, color, FLinearColor{ 247 / 255.f, 243 / 255.f, 185 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 10, pos.Y + pixelSize.Y * 1 }, pixelSize, color, FLinearColor{ 243 / 255.f, 239 / 255.f, 148 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 10, pos.Y + pixelSize.Y * 2 }, pixelSize, color, FLinearColor{ 239 / 255.f, 232 / 255.f, 111 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 10, pos.Y + pixelSize.Y * 3 }, pixelSize, color, FLinearColor{ 235 / 255.f, 229 / 255.f, 76 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 10, pos.Y + pixelSize.Y * 4 }, pixelSize, color, FLinearColor{ 208 / 255.f, 200 / 255.f, 55 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 10, pos.Y + pixelSize.Y * 5 }, pixelSize, color, FLinearColor{ 164 / 255.f, 157 / 255.f, 43 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 10, pos.Y + pixelSize.Y * 6 }, pixelSize, color, FLinearColor{ 118 / 255.f, 114 / 255.f, 31 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 10, pos.Y + pixelSize.Y * 7 }, pixelSize, color, FLinearColor{ 86 / 255.f, 82 / 255.f, 21 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 10, pos.Y + pixelSize.Y * 8 }, pixelSize, color, FLinearColor{ 9 / 255.f, 9 / 255.f, 9 / 255.f, 1.0f });
			}
			//11
			{
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 11, pos.Y + pixelSize.Y * 0 }, pixelSize, color, FLinearColor{ 218 / 255.f, 232 / 255.f, 182 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 11, pos.Y + pixelSize.Y * 1 }, pixelSize, color, FLinearColor{ 198 / 255.f, 221 / 255.f, 143 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 11, pos.Y + pixelSize.Y * 2 }, pixelSize, color, FLinearColor{ 181 / 255.f, 210 / 255.f, 103 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 11, pos.Y + pixelSize.Y * 3 }, pixelSize, color, FLinearColor{ 154 / 255.f, 186 / 255.f, 76 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 11, pos.Y + pixelSize.Y * 4 }, pixelSize, color, FLinearColor{ 130 / 255.f, 155 / 255.f, 64 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 11, pos.Y + pixelSize.Y * 5 }, pixelSize, color, FLinearColor{ 102 / 255.f, 121 / 255.f, 50 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 11, pos.Y + pixelSize.Y * 6 }, pixelSize, color, FLinearColor{ 74 / 255.f, 88 / 255.f, 36 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 11, pos.Y + pixelSize.Y * 7 }, pixelSize, color, FLinearColor{ 54 / 255.f, 64 / 255.f, 26 / 255.f, 1.0f });
				ColorPixel(FVector2D{ pos.X + pixelSize.X * 11, pos.Y + pixelSize.Y * 8 }, pixelSize, color, FLinearColor{ 0 / 255.f, 0 / 255.f, 0 / 255.f, 1.0f });
			}



			if (isHoveredPicker)
			{
				if (Input::IsMouseClicked(0, elements_count, false))
				{

				}
			}
			else
			{
				if (Input::IsMouseClicked(0, elements_count, false))
				{
					active_picker = -1;
					//hover_element = false;
				}
			}
		}
		else
		{
			//Bg
			if (isHovered)
			{
				drawFilledRect(FVector2D{ pos.X, pos.Y }, size, size, Colors::Checkbox_Hovered);
				hover_element = true;
			}
			else
			{
				drawFilledRect(FVector2D{ pos.X, pos.Y }, size, size, Colors::Checkbox_Idle);
			}

			//Color
			drawFilledRect(FVector2D{ pos.X + 4, pos.Y + 4 }, size - 8, size - 8, *color);

			//Text
			FVector2D textPos = FVector2D{ pos.X + size + 5.0f, pos.Y - 5 };
			TextLeft(name, textPos, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

			if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			{
				saved_color = *color;
				active_picker = elements_count;
			}
		}


		sameLine = false;
		last_element_pos = pos;
		//last_element_size = size;
		if (first_element_pos.X == 0.0f)
			first_element_pos = pos;
	}


	void Render()
	{
		for (int i = 0; i < 128; i++)
		{
			if (PostRenderer::drawlist[i].type != -1)
			{
				//Filled Rect
				if (PostRenderer::drawlist[i].type == 1)
				{
					CWINGui::drawFilledRect(PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].size.X, PostRenderer::drawlist[i].size.Y, PostRenderer::drawlist[i].color);
				}
				//TextLeft
				else if (PostRenderer::drawlist[i].type == 2)
				{
					CWINGui::TextLeft((const wchar_t*)PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color, PostRenderer::drawlist[i].outline);
				}
				//TextCenter
				else if (PostRenderer::drawlist[i].type == 3)
				{
					CWINGui::TextCenter((const wchar_t*)PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color, PostRenderer::drawlist[i].outline);
				}
				//Draw_Line
				else if (PostRenderer::drawlist[i].type == 4)
				{
					Draw_Line(PostRenderer::drawlist[i].from, PostRenderer::drawlist[i].to, PostRenderer::drawlist[i].thickness, PostRenderer::drawlist[i].color);
				}

				PostRenderer::drawlist[i].type = -1;
			}
		}
	}
}