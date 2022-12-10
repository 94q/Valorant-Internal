#include <Windows.h>
#include <cstdio>
#include "Canvas.h"
#include "decryption.h"
#include "hook.h"
#include "Decryptor.h"
using PostRenderHook = void(*)(uintptr_t _this, UCanvas* canvas);
PostRenderHook pRender = 0;

uintptr_t UWorldXOR;
UWorld* UWorldClass;
UGameInstance* GameInstance;
ULocalPlayer* LocalPlayers;
ULocalPlayer* LocalPlayer;

void DrawTextRGB(UCanvas* canvas, const wchar_t* text, float x, float y, FLinearColor color, bool CenterX = 0)
{
	canvas->K2_DrawText(text, { x, y }, { 1.1, 1.1 }, color, 0.f, { 0, 0, 0, 1 }, { 0, 0 }, CenterX, 0, bOutline, { 0, 0, 0, 1 });
}
void DrawTextRGBWithFString(UCanvas* canvas, FString text, float x, float y, FLinearColor color, bool CenterX = 0)
{
	canvas->K2_DrawText(text, { x, y }, { 1.1, 1.1 }, color, 0.f, { 0, 0, 0, 1 }, { 0, 0 }, CenterX, 0, bOutline, { 0, 0, 0, 1 });
}

void xxDrawTextRGB(UCanvas* canvas, FString text, float x, float y, FLinearColor color)
{
	canvas->K2_DrawText(text, { x, y }, { 1.1, 1.1 }, color, 0.f, { 0, 0, 0, 1 }, { 0, 0 }, 0, 0, false, { 0, 0, 0, 1 });
}
FLinearColor RGBtoFLC(float R, float G, float B)
{
	return { R / 255, G / 255, B / 255, 1 };
}

bool kekIsOff = 0; // debugging purposes ONLY solely for THAT
bool chams = 0;

static FLinearColor test_color{ 2.093f, 0.019f, 20.0f, 5.9f };
static FLinearColor MainESPColor{ 1.0f,1.0f,1.0f,1.0f};
static FLinearColor behind_wall_color = RGBtoFLC(255, 255, 255);
static FLinearColor visible_color = RGBtoFLC(0, 255, 0);
static FLinearColor circlecol = RGBtoFLC(0, 255, 0);
static bool menu_opened = true;
FVector2D pos = { ((float)GetSystemMetrics(SM_CXSCREEN) / 2) - 500, ((float)GetSystemMetrics(SM_CYSCREEN) / 2) - 475 };

static bool ChamsESP = false;
static bool brightchammy = false;
static bool box2d = false;
static bool PlayerNames = false;
static bool chammyteam = false;
static bool fovchanger = false;
static bool thirdperson = false;
static bool flyhack = false;
static bool healthcol = false;
static bool enableaim = false;
static bool memory = false;
static bool test1 = false;
static bool silent = false;
static bool drawfov = false;
int KEKWNOKEY;
static float radius = 100.0f;
static float fovchangur = 80.0f;
int aimbotmode = 0;

float ESPThickness = 1.0f;
float Lineamount = 500.0f;
float kekw = 4.0f;


void DrawBox(UCanvas* can, FVector2D& topleft, FVector2D& downright, FLinearColor clr)
{
	auto h = downright.Y - topleft.Y;
	auto w = downright.X - topleft.X;

	auto downleft = FVector2D{ topleft.X, downright.Y };
	auto topright = FVector2D{ downright.X, topleft.Y };

	auto thicc = ESPThickness;

	FLinearColor xclr = RGBtoFLC(0, 0, 0);

	can->K2_DrawLinex( topleft, { downright.X, topleft.Y }, thicc, clr);
	can->K2_DrawLinex(topleft, { topleft.X , downright.Y }, thicc, clr);
	can->K2_DrawLinex(downright, { topleft.X , downright.Y }, thicc, clr);
	can->K2_DrawLine(downright, { downright.X, topleft.Y }, thicc, clr);
	/*
	* OLD (remove 3 first line integrity)
	can->K2_DrawLine({topleft.X, topleft.Y + 100}, {topleft.X, topleft.Y + h * 1}, thicc, clr);
	can->K2_DrawLine({ topleft.X, topleft.Y + 100 }, { topleft.X + w * 1, topleft.Y }, thicc, clr);

	can->K2_DrawLine({ downright.X, downright.Y - 100 }, { downright.X, downright.Y - h * 1 }, thicc, clr);
	can->K2_DrawLine(downright, { downright.X - w * 1, downright.Y }, thicc, clr);

	can->K2_DrawLine(downleft, { downleft.X, downleft.Y - h * 1 }, thicc, clr);
	can->K2_DrawLine(downleft, { downleft.X + w * 1, downright.Y }, thicc, clr);

	can->K2_DrawLine(topright, { topright.X, topright.Y + h * 1 }, thicc, clr);
	can->K2_DrawLine(topright, { topright.X - w * 1, topright.Y }, thicc, clr);*/
}
uintptr_t OffsetGetActorBounds;
void GetActorBounds(AShooterCharacter* Actor, bool bOnlyCollidingComponents, FVector* Origin, FVector* BoxExtent, bool bIncludeFromChildActors)
{
	reinterpret_cast<void(*)(AShooterCharacter*, bool, FVector * pos, FVector * screen, bool)> ((uintptr_t)GetModuleHandleA(0) + 0x4771E10)(Actor, 0, Origin, BoxExtent, 0);
}
static FVector2D scr[8];

void FMath::SinCos(float* ScalarSin, float* ScalarCos, float Value)
{
	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	float quotient = (INV_PI * 0.5f) * Value;
	if (Value >= 0.0f)
	{
		quotient = (float)((int)(quotient + 0.5f));
	}
	else
	{
		quotient = (float)((int)(quotient - 0.5f));
	}
	float y = Value - (2.0f * PI) * quotient;

	// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
	float sign;
	if (y > HALF_PI)
	{
		y = PI - y;
		sign = -1.0f;
	}
	else if (y < -HALF_PI)
	{
		y = -PI - y;
		sign = -1.0f;
	}
	else
	{
		sign = +1.0f;
	}

	float y2 = y * y;

	// 11-degree minimax approximation
	*ScalarSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

	// 10-degree minimax approximation
	float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
	*ScalarCos = sign * p;
}

float FMath::Fmod(float X, float Y)
{
	const float AbsY = fabsf(Y);
	if (AbsY <= 1.e-8f) { return 0.f; }
	const float Div = (X / Y);
	// All floats where abs(f) >= 2^23 (8388608) are whole numbers so do not need truncation, and avoid overflow in TruncToFloat as they get even larger.
	const float Quotient = fabsf(Div) < FLOAT_NON_FRACTIONAL ? truncf(Div) : Div;
	float IntPortion = Y * Quotient;

	// Rounding and imprecision could cause IntPortion to exceed X and cause the result to be outside the expected range.
	// For example Fmod(55.8, 9.3) would result in a very small negative value!
	if (fabsf(IntPortion) > fabsf(X)) { IntPortion = X; }

	const float Result = X - IntPortion;
	// Clamp to [-AbsY, AbsY] because of possible failures for very large numbers (>1e10) due to precision loss.
	// We could instead fall back to stock fmodf() for large values, however this would diverge from the SIMD VectorMod() which has no similar fallback with reasonable performance.
	return FMath::Clamp(Result, -AbsY, AbsY);
}
FQuat FRotator::Quaternion() const
{
	float SP, SY, SR;
	float CP, CY, CR;
	const float PitchNoWinding = FMath::Fmod(Pitch, 360.0f);
	const float YawNoWinding = FMath::Fmod(Yaw, 360.0f);
	const float RollNoWinding = FMath::Fmod(Roll, 360.0f);
	FMath::SinCos(&SP, &CP, PitchNoWinding * RADS_DIVIDED_BY_2);
	FMath::SinCos(&SY, &CY, YawNoWinding * RADS_DIVIDED_BY_2);
	FMath::SinCos(&SR, &CR, RollNoWinding * RADS_DIVIDED_BY_2);
	FQuat RotationQuat;
	RotationQuat.X = CR * SP * SY - SR * CP * CY;
	RotationQuat.Y = -CR * SP * CY - SR * CP * SY;
	RotationQuat.Z = CR * CP * SY - SR * SP * CY;
	RotationQuat.W = CR * CP * CY + SR * SP * SY;
	return RotationQuat;
}

const FVector FVector::ZeroVector(0.0f, 0.0f, 0.0f);
const FVector FVector::OneVector(1.0f, 1.0f, 1.0f);
FVector FTransform::TransformPosition(FVector& V) const
{
	return Rotation.RotateVector(Scale3D * V) + Translation;
}

FVector FQuat::RotateVector(const FVector& V) const
{
	const FVector Q(X, Y, Z);
	const FVector T = (Q ^ V) * 2.f;
	const FVector Result = V + (T * W) + (Q ^ T);
	return Result;
}

bool a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18;
void  Draw3DBox(UCanvas* _this, APlayerController* plc, FVector origin, FVector extends, FLinearColor col)
{
	origin -= extends / 2.f;

	// bottom plane
	FVector one = origin;
	FVector two = origin; two.X += extends.X;
	FVector three = origin; three.X += extends.X; three.Y += extends.Y;
	FVector four = origin; four.Y += extends.Y;

	FVector five = one; five.Z += extends.Z;
	FVector six = two; six.Z += extends.Z;
	FVector seven = three; seven.Z += extends.Z;
	FVector eight = four; eight.Z += extends.Z;



	if (plc->ProjectWorldLocationToScreen(one, scr[0], 0) || plc->ProjectWorldLocationToScreen(two, scr[1], 0) || plc->ProjectWorldLocationToScreen(three, scr[2], 0) || plc->ProjectWorldLocationToScreen(four, scr[3], 0))
	{
		if (plc->ProjectWorldLocationToScreen(five, scr[4], 0) || plc->ProjectWorldLocationToScreen(six, scr[5], 0) || plc->ProjectWorldLocationToScreen(seven, scr[6], 0) || plc->ProjectWorldLocationToScreen(eight, scr[7], 0))
		{
			_this->K2_DrawLine(scr[0], scr[1], ESPThickness, col);
			_this->K2_DrawLine(scr[1], scr[2], ESPThickness, col);
			_this->K2_DrawLine(scr[2], scr[3], ESPThickness, col);
			_this->K2_DrawLine(scr[3], scr[0], ESPThickness, col);

			_this->K2_DrawLine(scr[4], scr[5], ESPThickness, col);
			_this->K2_DrawLine(scr[5], scr[6], ESPThickness, col);
			_this->K2_DrawLine(scr[6], scr[7], ESPThickness, col);
			_this->K2_DrawLine(scr[7], scr[4], ESPThickness, col);

			_this->K2_DrawLine(scr[0], scr[4], ESPThickness, col);
			_this->K2_DrawLine(scr[1], scr[5], ESPThickness, col);
			_this->K2_DrawLine(scr[2], scr[6], ESPThickness, col);
			_this->K2_DrawLine(scr[3], scr[7], ESPThickness, col);
		}
	}
}

bool Render3DBox(APlayerController* controller, UCanvas* Engine, const FVector& origin, const FVector& extent, const FRotator& rotation, const FLinearColor color)
{
	FVector vertex[2][4];
	vertex[0][0] = { -extent.X, -extent.Y,  -extent.Z };
	vertex[0][1] = { extent.X, -extent.Y,  -extent.Z };
	vertex[0][2] = { extent.X, extent.Y,  -extent.Z };
	vertex[0][3] = { -extent.X, extent.Y, -extent.Z };

	vertex[1][0] = { -extent.X, -extent.Y, extent.Z };
	vertex[1][1] = { extent.X, -extent.Y, extent.Z };
	vertex[1][2] = { extent.X, extent.Y, extent.Z };
	vertex[1][3] = { -extent.X, extent.Y, extent.Z };

	FVector2D screen[2][4];
	FTransform const Transform(rotation);
	for (auto k = 0; k < 2; k++)
	{
		for (auto i = 0; i < 4; i++)
		{
			auto& vec = vertex[k][i];
			vec = Transform.TransformPosition(vec) + origin;
			if (!controller->ProjectWorldLocationToScreen(vec, screen[k][i], false)) return false;
		}

	}

	auto SurfaceScreen = reinterpret_cast<FVector2D(&)[2][4]>(screen);

	for (auto i = 0; i < 4; i++)
	{
		Engine->K2_DrawLine(SurfaceScreen[0][i], SurfaceScreen[0][(i + 1) % 4], ESPThickness, color);
		Engine->K2_DrawLine(SurfaceScreen[1][i], SurfaceScreen[1][(i + 1) % 4], ESPThickness, color);
		Engine->K2_DrawLine(SurfaceScreen[0][i], SurfaceScreen[1][i], ESPThickness, color);
	}

	return true;
}
bool healthbar = 0;
bool snaplinenz = 0;
bool weaponesp = 0;
bool aimbotvischeck = 1;
bool shieldbar = 0;

FString character_name(FString in)
{
	if (in.ToString().find("Training") != std::string::npos)
		return FString(L"NPC");
	if (in.ToString().find("BountyHunter_PC_C") != std::string::npos)
		return FString(L"Fade");
	if (in.ToString().find("Stealth_PC_C") != std::string::npos)
		return FString(L"Yoru");
	if (in.ToString().find("Pandemic_PC_C") != std::string::npos)
		return FString(L"Viper");
	if (in.ToString().find("Hunter_PC_C") != std::string::npos)
		return FString(L"Sova");
	if (in.ToString().find("Guide_PC_C") != std::string::npos)
		return FString(L"Skye");
	if (in.ToString().find("Thorne_PC_C") != std::string::npos)
		return FString(L"Sage");
	if (in.ToString().find("Vampire_PC_C") != std::string::npos)
		return FString(L"Reyna");
	if (in.ToString().find("Clay_PC_C") != std::string::npos)
		return FString(L"Raze");
	if (in.ToString().find("Phoenix_PC_C") != std::string::npos)
		return FString(L"Phoenix");
	if (in.ToString().find("Wraith_PC_C") != std::string::npos)
		return FString(L"Omen");
	if (in.ToString().find("Sprinter_PC_C") != std::string::npos)
		return FString(L"Neon");
	if (in.ToString().find("Killjoy_PC_C") != std::string::npos)
		return FString(L"Killjoy");
	if (in.ToString().find("Grenadier_PC_C") != std::string::npos)
		return FString(L"Kayo");
	if (in.ToString().find("Wushu_PC_C") != std::string::npos)
		return FString(L"Jett");
	if (in.ToString().find("Gumshoe_PC_C") != std::string::npos)
		return FString(L"Cypher");
	if (in.ToString().find("Deadeye_PC_C") != std::string::npos)
		return FString(L"Chamber");
	if (in.ToString().find("Sarge_PC_C") != std::string::npos)
		return FString(L"Brimstone");
	if (in.ToString().find("Breach_PC_C") != std::string::npos)
		return FString(L"Breach");
	if (in.ToString().find("Rift_TargetingForm_PC_C") != std::string::npos)
		return FString(L"Astra");
	if (in.ToString().find("Rift_PC_C") != std::string::npos)
		return FString(L"Astra");
	if (in.ToString().find("Mage_PC_C") != std::string::npos)
		return FString(L"Harbor");
	else
		return FString(L"N/A");
}
FString weapon_name(FString in)
{
	if (in.ToString().find("Ability_Melee_Base_C") != std::string::npos)
		return FString(L"Melee");
	if (in.ToString().find("BasePistol_C") != std::string::npos)
		return FString(L"Classic");
	if (in.ToString().find("TrainingBotBasePistol_C") != std::string::npos)
		return FString(L"Classic");
	if (in.ToString().find("SawedOffShotgun_C") != std::string::npos)
		return FString(L"Shorty");
	if (in.ToString().find("AutomaticPistol_C") != std::string::npos)
		return FString(L"Frenzy");
	if (in.ToString().find("LugerPistol_C") != std::string::npos)
		return FString(L"Ghost");
	if (in.ToString().find("RevolverPistol_C") != std::string::npos)
		return FString(L"Sheriff");
	if (in.ToString().find("Vector_C") != std::string::npos)
		return FString(L"Stinger");
	if (in.ToString().find("SubMachineGun_MP5_C") != std::string::npos)
		return FString(L"Spectre");
	if (in.ToString().find("PumpShotgun_C") != std::string::npos)
		return FString(L"Bucky");
	if (in.ToString().find("AssaultRifle_Burst_C") != std::string::npos)
		return FString(L"Bulldog");
	if (in.ToString().find("DMR_C") != std::string::npos)
		return FString(L"Guardian");
	if (in.ToString().find("AssaultRifle_ACR_C") != std::string::npos)
		return FString(L"Phantom");
	if (in.ToString().find("AssaultRifle_AK_C") != std::string::npos)
		return FString(L"Vandal");
	if (in.ToString().find("LeverSniperRifle_C") != std::string::npos)
		return FString(L"Marshall");
	if (in.ToString().find("BoltSniper_C") != std::string::npos)
		return FString(L"Operator");
	if (in.ToString().find("LightMachineGun_C") != std::string::npos)
		return FString(L"Ares");
	if (in.ToString().find("HeavyMachineGun_C") != std::string::npos)
		return FString(L"Odin");
	else
		return FString(L"N/A");
}


void PostRender(uintptr_t _this, UCanvas* canvas)
{
	if (!canvas)
		return PostRender(_this, canvas);

	if (kekIsOff)return PostRender(_this, canvas);
	CWINGui::SetupCanvas(canvas);
	UWorld* World = Memory::ReadStub<UWorld*>(_this + 0x80);
	APlayerController* MyController = ShooterGameBlueprints::GetFirstLocalPlayerController(World);
	AShooterCharacter* MyShooter = MyController->GetShooterCharacter();
	TArray<AShooterCharacter*> Actors = ShooterGameBlueprints::FindAllShooterCharactersWithAlliance(World, MyShooter, EAresAlliance::Alliance_Any, false, true); 
	CWINGui::Input::Handle();

	if (GetAsyncKeyState(VK_INSERT) & 1) menu_opened = !menu_opened; //Our menu key 
	if (enableaim && drawfov)
	{
		CWINGui::DrawCircle({ (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN) / 2 }, radius, Lineamount, circlecol);
	}
	if (CWINGui::Window(skCrypt("DaddyKermit Internal"), &pos, FVector2D{ 500.0f, 475.0f }, menu_opened))
	{
		//Simple Tabs
		static int tab = 0;
		if (CWINGui::ButtonTab(L"Aimbot", FVector2D{ 110, 35 }, tab == 0)) tab = 0; 
		if (CWINGui::ButtonTab(L"Visuals", FVector2D{ 110, 35 }, tab == 1)) tab = 1;
		if (CWINGui::ButtonTab(L"Exploits", FVector2D{ 110, 35 }, tab == 2)) tab = 2; 
		if (CWINGui::ButtonTab(L"Misc", FVector2D{ 110, 35 }, tab == 4)) tab = 4; 
		CWINGui::NextColumn(140.0f);
		//Some Elements


		if (tab == 0)
		{
			CWINGui::Checkbox(L"Toggle", &enableaim); 
			CWINGui::Checkbox(L"Memory Mode", &memory);
			CWINGui::Checkbox(L"Silent test (beta)", &test1);
			CWINGui::Checkbox(L"Only aim when player is visible", &aimbotvischeck); 
			CWINGui::Checkbox(L"Draw FOV", &drawfov); 
			CWINGui::Hotkey("Keybind", {132,32}, &KEKWNOKEY); 
			CWINGui::SliderFloat(L"Radius", &radius, 1, 2000); 
			CWINGui::ColorPicker(L"Circle color", &circlecol); 
			CWINGui::SliderFloat(L"Amount of lines in circle", &Lineamount, 10, 1000);
		}

		if (tab == 1)
		{
			CWINGui::Checkbox(L"Chams", &ChamsESP); 
			CWINGui::Checkbox(L"Bounding Boxes", &box2d); 
			CWINGui::Checkbox(L"Player Names", &PlayerNames); 
			CWINGui::Checkbox(L"Health Bar", &healthbar);
			CWINGui::Checkbox(L"Shield Bar", &shieldbar);
			CWINGui::Checkbox(L"Snap Line", &snaplinenz);
			CWINGui::Checkbox(L"Draw Allies", &chammyteam); 
			CWINGui::Checkbox(L"Outline", &bOutline); 
			CWINGui::Checkbox(L"Replace text by health", &healthcol);
			CWINGui::Checkbox(L"Current weapon", &weaponesp);
			CWINGui::ColorPicker(L"Chams Color", &MainESPColor); 
			CWINGui::ColorPicker(L"Behind Wall Color", &behind_wall_color); 
			CWINGui::ColorPicker(L"Visible Color", &visible_color); 
			CWINGui::SliderFloat(L"ESP Thickness", &ESPThickness, 1, 10);
		}

		if (tab == 2)
		{
			CWINGui::Checkbox(L"Fly (training range only)", &flyhack); 
			CWINGui::Checkbox(L"Third Person Viewmode", &thirdperson); 
		}
		 
		if (tab == 4)
		{
			CWINGui::Checkbox(L"Visible Check (Line of sight to)", &vischeck);
			CWINGui::Checkbox(L"Camera Slider", &fovchanger);
			CWINGui::SliderFloat(L"FOV", &fovchangur, 0, 300);
			CWINGui::Text(L"t.me/Nutware");
		} 

		if (InGame)
			CWINGui::Text(L"-> IN GAME");
		else
			CWINGui::Text(L"-> IN LOBBY");
		//Color Picker
	}
	//CWINGui::Draw_Cursor(menu_opened); // Dont need this ugly ass cursor
	CWINGui::Render();//Custom Render. I use it for drawing Combobox and ColorPicker over the menu 
	if (fovchanger)
		MyController->set_fov(fovchangur);
	for (int Index = 0; Index < Actors.Num(); Index++)
	{
		if (!Actors.IsValidIndex(Index) )
			continue;

		AShooterCharacter* Actor = Actors[Index];

		if (Actor->GetHealth() == 0)
			continue;

		if (!MyShooter) continue;

		if (kismentsystemlibrary::get_object_name(Actor).ToString().find("_PC") != std::string::npos)
			InGame = 1;
		else
			InGame = 0;

		USkeletalMeshComponent* Mesh = Actor->GetPawnMesh(); 
		//if (Actor->IsAlive()) continue;

		if (BaseTeamComponent::IsAlly(Actor, MyShooter))
			continue;

		if (!InGame) continue;

		if (Mesh && Actor->IsAlive())
		{ 
			FLinearColor MainColor;
			if(vischeck)
			{
				if (MyController->LineOfSightTo(Actor, { 0,0,0 }, false))
					MainColor = visible_color;
				else
					MainColor = behind_wall_color;
			}
			else
			{
				MainColor = visible_color;
			}

			if (flyhack)
			{ 
				MyShooter->ClientFly();
			}

			if (box2d)
			{
				FVector Origin, Extend;
				GetActorBounds(Actor, 1, &Origin, &Extend, 0);

				//Render3DBox(MyController, canvas, Origin, Extend, Actor->K2_GetActorRotation(), xtest_color);
				//Draw3DBox(canvas, MyController, Origin, Extend, xtest_color);
				auto location = Actor->K2_GetActorLocation(); FVector2D footPos;
				if (!MyController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z + (Extend.Z / 2) }, footPos, 0)) continue;

				FVector2D headPos;
				if (!MyController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z - (Extend.Z / 2) }, headPos, 0)) continue;


				const float height = abs(footPos.Y - headPos.Y);
				const float width = height * 0.4f;
				FVector2D top = { headPos.X - width * 0.5f, headPos.Y };
				FVector2D bottom = { headPos.X + width * 0.5f, footPos.Y };
				DrawBox(canvas, top, bottom, MainColor);
			}

			if (thirdperson)
			{
				MyShooter->Set3pMeshVisible(1);
			}
			else 	
			{
				MyShooter->Set3pMeshVisible(0);
			}

			if (enableaim)
			{
				if (memory) // SHIT AIMBOT
				{
					static AShooterCharacter* closestEnemy = nullptr;
					static float closestDistance = 999999.9f;
					if (closestEnemy)
					{
						/* Obtain health and RelativeLocation */
						auto Health = Actor->GetHealth();
						auto RelativeLocation = Actor->K2_GetActorLocation();

						/* Define vectors */
						FVector Origin, Extend;
						GetActorBounds(Actor, 1, &Origin, &Extend, 0);

						/* W2S the vectors */
						auto location = Actor->K2_GetActorLocation(); FVector2D footPos;
						if (!MyController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z + (Extend.Z) }, footPos, 0)) continue;

						FVector original_rotation = MyController->GetControlRotation();
						FVector kek3 = { location.X, location.Y, location.Z + (Extend.Z / 2) };
						FVector vector_pos =  kek3 - MyShooter->K2_GetActorLocation();
						float distance = (double)(sqrtf(vector_pos.X * vector_pos.X + vector_pos.Y * vector_pos.Y + vector_pos.Z * vector_pos.Z));
						float X, Y, Z;
						X = -((acosf(vector_pos.Z / distance) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510)) - 90.f);
						Y = atan2f(vector_pos.Y, vector_pos.X) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510);
						Z = 0; 
						{
							if (vischeck)
							{
								if(MyController->LineOfSightTo(Actor, {0,0,0}, false))
								{
									if (test1)
									{
										if (GetAsyncKeyState(KEKWNOKEY))
											MyController->SetControlRotation({ X - kekw ,Y ,Z });
										MyController->SetControlRotation(original_rotation);

									}
									else
									{
										if (GetAsyncKeyState(KEKWNOKEY))
											MyController->SetControlRotation({ X - kekw ,Y ,Z });
									}
								}
							}
							else
							{
								if (test1)
								{
									if (GetAsyncKeyState(KEKWNOKEY))
										MyController->SetControlRotation({ X - kekw ,Y ,Z });
									MyController->SetControlRotation(original_rotation);

								}
								else
								{
									if (GetAsyncKeyState(KEKWNOKEY))
										MyController->SetControlRotation({ X - kekw ,Y ,Z });
								}
							}
						}
					}
					else if (Actor)
					{
						closestEnemy = Actor;
					}
				}
			}

			if(snaplinenz)
			{
				FVector Origin, Extend;
				GetActorBounds(Actor, 1, &Origin, &Extend, 0);

				auto location = Actor->K2_GetActorLocation(); FVector2D footPos;
				if (!MyController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z - (Extend.Z / 2) }, footPos, 0)) continue;

				FVector2D headPos;
				if (!MyController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z + (Extend.Z / 2) }, headPos, 0)) continue;

				canvas->K2_DrawLine({ (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN) }, headPos, ESPThickness, MainColor);
			}

			if (healthbar)
			{
				FVector Origin, Extend;
				GetActorBounds(Actor, 1, &Origin, &Extend, 0);

				auto location = Actor->K2_GetActorLocation(); FVector2D footPos;
				if (!MyController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z - (Extend.Z / 2) }, footPos, 0)) continue;

				FVector2D headPos;
				if (!MyController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z + (Extend.Z / 2) }, headPos, 0)) continue;

				auto maxhealth = Actor->GetMaxHealth();
				if (maxhealth >= 100)maxhealth = 100;
				const float hp = Actor->GetHealth() / maxhealth;

				const float height = abs(footPos.Y - headPos.Y);
				const float width = height * 0.4f;
				const float width2 = width * 0.5f;
				const float adjust = height * 0.025f;
				const float len = width * hp;

				FVector2D top = { headPos.X - width * 0.5f, headPos.Y };
				FVector2D bottom = { headPos.X + width * 0.5f, footPos.Y };
				auto downleft = FVector2D{ top.X, bottom.Y };
				auto topright = FVector2D{ bottom.X, top.Y };

				auto h = bottom.Y - top.Y;
				auto w = bottom.X - top.X;
				auto thicc = ESPThickness;

				canvas->K2_DrawLinex({ headPos.X - width2, footPos.Y + adjust }, { headPos.X - width2 + len, footPos.Y + adjust * 2.f }, 5, RGBtoFLC(0, 255, 0));

			}

			if (shieldbar)
			{
				FVector Origin, Extend;
				GetActorBounds(Actor, 1, &Origin, &Extend, 0);

				auto location = Actor->K2_GetActorLocation(); FVector2D footPos;
				if (!MyController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z - (Extend.Z / 2) }, footPos, 0)) continue;

				FVector2D headPos;
				if (!MyController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z + (Extend.Z / 2) }, headPos, 0)) continue;

				auto maxhealth = Actor->GetMaxShield();
				if (maxhealth >= 100)maxhealth = 100;
				const float hp = Actor->GetShield() / maxhealth;

				const float height = abs(footPos.Y - headPos.Y);
				const float width = height * 0.4f;
				const float width2 = width * 0.5f;
				const float adjust = height * 0.025f;
				const float len = width * hp;

				FVector2D top = { headPos.X - width * 0.5f, headPos.Y };
				FVector2D bottom = { headPos.X + width * 0.5f, footPos.Y };
				auto downleft = FVector2D{ top.X, bottom.Y };
				auto topright = FVector2D{ bottom.X, top.Y };

				auto h = bottom.Y - top.Y;
				auto w = bottom.X - top.X;
				auto thicc = ESPThickness;

				canvas->K2_DrawLinex({ headPos.X - width2, footPos.Y + adjust }, { headPos.X - width2 + len, footPos.Y + adjust * 2.f }, 5, RGBtoFLC(0, 0, 255));

			}

			if (PlayerNames)
			{
				/* Define vectors */
				FVector Origin, Extend;
				FVector2D rel2d, footPos;

				/* Get bouuuuuuunds */
				GetActorBounds(Actor, 1, &Origin, &Extend, 0);

				/* Obtain health and RelativeLocation */ 
				auto RelativeLocation = Actor->K2_GetActorLocation();

				/* W2S the vectors */
				if (MyController->ProjectWorldLocationToScreen({ RelativeLocation.X, RelativeLocation.Y, RelativeLocation.Z - (Extend.Z / 2) }, footPos, 0))
				{
					if (MyController->ProjectWorldLocationToScreen(Actor->K2_GetActorLocation(), rel2d, true))
					{
						DrawTextRGBWithFString(canvas, character_name(kismentsystemlibrary::get_object_name(Actor)), footPos.X, footPos.Y + 10, MainColor, 1);
					}
				}
			}

			if (weaponesp)
			{
				/* Define vectors */
				FVector Origin, Extend;
				FVector2D rel2d, footPos;

				/* Get bouuuuuuunds */
				GetActorBounds(Actor, 1, &Origin, &Extend, 0);

				/* Obtain health and RelativeLocation */ 
				auto RelativeLocation = Actor->K2_GetActorLocation();

				/* W2S the vectors */
				if (MyController->ProjectWorldLocationToScreen({ RelativeLocation.X, RelativeLocation.Y, RelativeLocation.Z + (Extend.Z / 2) }, footPos, 0))
				{
					if (MyController->ProjectWorldLocationToScreen(Actor->K2_GetActorLocation(), rel2d, true))
					{
						DrawTextRGBWithFString(canvas, weapon_name(kismentsystemlibrary::get_object_name(Actor->GetInventory()->GetCurrentWeapon())), footPos.X, footPos.Y - 30, MainColor, 1);
					}
				}
			}

			if (ChamsESP)
			{
				Mesh->SetAresOutlineMode(EAresOutlineMode::Outline, true);
				AresOutlineRendering::SetOutlineColorsForRender(World, {MainESPColor.R * 2, MainESPColor.G * 2, MainESPColor.B * 2, MainESPColor.A * 5.9f}, { MainESPColor.R * 2, MainESPColor.G * 2, MainESPColor.B * 2, MainESPColor.A * 5.9f });
			}
			else
			{
				Mesh->SetAresOutlineMode(EAresOutlineMode::None, true);
			}

		}
	}

	return pRender(_this, canvas);
}



void Init()
{
	//AllocConsole();
	//freopen("CONIN$", "r", stdin);
	//freopen("CONOUT$", "w", stdout);
	VALORANT::Module = (uintptr_t)GetModuleHandleA(0);
	uintptr_t WorldKey = *(uintptr_t*)(VALORANT::Module + Offsets::Key);
	State StateKey = *(State*)(VALORANT::Module + Offsets::State);
	UWorldXOR = Decryption::Decrypt_UWorld(WorldKey, (uintptr_t*)&StateKey);
	UWorldClass = Memory::ReadStub<UWorld*>(UWorldXOR);
	GameInstance = Memory::ReadStub<UGameInstance*>((uintptr_t)UWorldClass + 0x1A0);
	LocalPlayers = Memory::ReadStub<ULocalPlayer*>((uintptr_t)GameInstance + 0x40); //this is tarray but im paster lol
	LocalPlayer = Memory::ReadStub<ULocalPlayer*>((uintptr_t)LocalPlayers); //
	APlayerController* LocalController = Memory::ReadStub<APlayerController*>((uintptr_t)LocalPlayer + 0x38);
	uintptr_t ViewportClient = Memory::ReadStub<uintptr_t>((uintptr_t)LocalPlayer + 0x78);
	uintptr_t Engine = Memory::ReadStub<uintptr_t>((uintptr_t)GameInstance + 0x28);
	DefaultMediumFont = Memory::ReadStub<UObject*>(Engine + 0xd8);
	NamePoolData = reinterpret_cast<FNamePool*>(VALORANT::Module + NamePoolDataOffset);
	Hook::VMT((void*)ViewportClient, PostRender, 0x68, (void**)&pRender);
}
extern "C" __declspec(dllexport) int NextHook(int code, WPARAM wParam, LPARAM lParam) { return CallNextHookEx(NULL, code, wParam, lParam); }


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		Init();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
// Unknownskids.me