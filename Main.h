#pragma once


// MAKE BY NEEKO (if you see this -> u r gay)
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <tlhelp32.h>
#include <thread>
#include <cmath>
#include <immintrin.h>

//#include "Protect.h"
//#include "config.h"

#include "process.h"

#include <dwmapi.h>
#include <comdef.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <unordered_map>
#include <codecvt>


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx9.h"
#include "Imgui/imgui_impl_win32.h"

#include "font.h"

#include "Text.h"
#include "math.h"
#include "DrawEsp.h"
#include <mutex>
#include "save.h"
#include "Xor.h"
#include "offsets.h"

#include "../driver.h"
#include "HyperV.h"
#include "Xor.hpp"

#define M_PI	3.14159265358979323846264338327950288419716939937510

#define UWORLD 0x7383388

//48 8B 1D ? ? ? ? 48 85 DB 74 33 41 B0 01
#define GNAME 0x7200B40


//48 8B 1D ? ? ? ? ? ? ? ? 48 85 DB 74 3B 41 //uworld
//48 8D 0D ? ? ? ? 48 63 FA 75 0F //Gnames

IDirect3D9Ex* p_Object = NULL;
IDirect3DDevice9Ex* p_Device = NULL;
D3DPRESENT_PARAMETERS p_Params = { NULL };

using namespace std;

const MARGINS Margin = { -1 };

#define M_Name L" "
HWND MyWnd = NULL;

HWND GameWnd = NULL;
RECT GameRect = { NULL };
MSG Message = { NULL };

DWORD ScreenCenterX = NULL;
DWORD ScreenCenterY = NULL;
bool showimgui = true;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define TopWindowGame 11
#define TopWindowMvoe 22

HRESULT DirectXInit(HWND hWnd);
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
void SetupWindow();
WPARAM MainLoop();
void CleanuoD3D(); /*void ChangeClickability(bool canclick, HWND ownd);*/

int isTopwin();
//void Render(int Topwin, bool showimgui);
void SetWindowToTarget();


//HyperV* m_pHyperV = nullptr;

float cachedfov = 0;

uint64_t BaseAddressTemp = 0;

bool Off = false;

//->TARRAYS
template<class T>
class TArray
{
public:
	int Length() const
	{
		return m_nCount;
	}

	bool IsValid() const
	{
		if (m_nCount > m_nMax)
			return false;
		if (!m_Data)
			return false;
		return true;
	}

	bool IsValidIndex(int32_t i) const
	{
		return i < m_nCount;
	}

	template<typename U = T>
	typename std::enable_if<std::is_pointer<U>::value, typename std::remove_pointer<U>::type>::type GetValue(int32_t index) const
	{
		auto offset =read<uintptr_t>(m_Data + sizeof(uintptr_t) * index);
		return read<typename std::remove_pointer<U>::type>(offset);
	}

	template<typename U = T>
	typename std::enable_if<!std::is_pointer<U>::value, U>::type GetValue(int32_t index) const
	{
		return read<U>(m_Data + sizeof(U) * index);
	}

	template<typename U = T, typename std::enable_if<std::is_pointer<U>::value, int32_t>::type = 0>
	uintptr_t GetValuePtr(int32_t index) const
	{
		return read<uintptr_t>(m_Data + sizeof(uintptr_t) * index);
	}

	template<typename U = T, typename std::enable_if<!std::is_pointer<U>::value, int32_t>::type = 0>
	uintptr_t GetValuePtr(int32_t index) const
	{
		return m_Data + sizeof(U) * index;
	}

	template<typename U = T>
	void SetValue(int32_t index, U value) const
	{
		return write(this->GetValuePtr(index), value);
	}

	template<typename U = T>
	typename std::enable_if<std::is_pointer<U>::value, typename std::remove_pointer<U>::type>::type operator[](int32_t index) const
	{
		return GetValue<U>(index);
	}

	template<typename U = T>
	typename std::enable_if<!std::is_pointer<U>::value, U>::type operator[](int32_t index) const
	{
		return GetValue<U>(index);
	}
private:
	uintptr_t m_Data;
	int32_t m_nCount;
	int32_t m_nMax;
};

struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};
struct FTransform
{
	FQuat rot;
	Vector3 translation;
	char pad[4];
	Vector3 scale;
	char pad1[4];
	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

static D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}

FTransform GetBoneIndex(uint64_t mesh, int64_t index)
{
	uint64_t bonearray = read<uint64_t>(mesh + 0x4B0);
	if (!bonearray) {
		bonearray = read<uint64_t>(mesh + 0x4A8);
	}

	return read<FTransform>(bonearray + (index * 0X60/*sizeof(FTransform)*/));
}
Vector3 GetBoneWithRotation(DWORD_PTR mesh, int id)
{
	FTransform bone = GetBoneIndex(mesh, id);
	FTransform ComponentToWorld = read<FTransform>(mesh + 0x1c0);  //0X270 - 240 

	D3DMATRIX Matrix;
	Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

	return Vector3(Matrix._41, Matrix._42, Matrix._43);
}

struct FNameEntry {
	UINT32 ID;
	UINT16 bIsWide : 1;
	UINT16 Len : 15;
};

//EVERYWHERE ONE
//std::string GetName(int key)
//{
//	auto chunkOffset = (UINT)((int)(key) >> 16);
//	auto nameOffset = (USHORT)key;
//
//	auto namePoolChunk = read<UINT64>(BaseAddressTemp + GNAME + ((chunkOffset + 2) * 8));
//	auto entryOffset = namePoolChunk + (ULONG)(2 * nameOffset);
//	auto nameEntry = read<INT16>(entryOffset);
//
//	auto nameLength = nameEntry >> 6;
//	char buff[1028];
//	if ((DWORD)nameLength && nameLength > 0)
//	{
//		m_pHyperV->readwtf(entryOffset + 2, buff, nameLength);
//		buff[nameLength] = '\0';
//		return std::string(buff);
//	}
//	else return "";
//}

//DBD ONE
//std::string GetName(int id) {
//	char name[256];
//	ZeroMemory(name, sizeof(name));
//	uint32_t chunk_offset = id >> 16;
//	uint16_t name_offset = id & 65535;
//	uint64_t fname_pool = (uint64_t)BaseAddressTemp + GNAME;
//
//	uint64_t name_pool_chunk = read<uint64_t>(fname_pool + ((chunk_offset + 2) * 8));
//	if (name_pool_chunk) {
//		uint64_t entry_offset = name_pool_chunk + (uint32_t)(4 * name_offset);
//		if (entry_offset) {
//			//uint16_t name_entry = read<uint64_t>(entry_offset);
//
//			FNameEntry header = read<FNameEntry>(entry_offset);
//			uint32_t name_length = header.Len;
//			if (name_length > 128) {
//				name_length = 128;
//			}
//
//			auto result = m_pHyperV->readwtf(entry_offset + 6, &name, name_length);
//			return std::string(name);
//		}
//	}
//	return std::string(xor ("ERROR"));
//}

//UC ONE

static std::string get_name_by_id(uint32_t actor_id) {
	char name[256];

	uint32_t chunk_offset = actor_id >> 16;
	uint16_t name_offset = (uint16_t)actor_id;
	uint64_t fname_pool = BaseAddressTemp + 0x7200B40; //48 8D 0D ? ? ? ? 48 63 FA 75 0F


	uint64_t name_pool_chunk = read<uint64_t>(fname_pool + ((chunk_offset + 2) * 8));
	if (name_pool_chunk) {
		uint64_t entry_offset = name_pool_chunk + (uint32_t)(2 * name_offset);
		if (entry_offset) {

			uint16_t name_entry = read<uint64_t>(entry_offset);

			uint32_t name_length = (name_entry >> 6);

			if (name_length > 256)
			{
				name_length = 255;
			}

			auto result = readwtf(entry_offset + 0x2, &name, name_length);
			return result;


		}
	}
	return std::string("NULL");
}
//
//string GetName(UINT32 index) {
//	UINT32 Block = index >> 16;//0x10
//	UINT16 Offset = index & 65535;//0xFFFF
//
//	char name[256];
//	ZeroMemory(name, sizeof(name));
//
//	uintptr_t FNamePool = (((uint64_t)BaseAddressTemp + GNAME) + 0x10);
//
//	uintptr_t NamePoolChunk = read<uintptr_t>(FNamePool + (Block * 0x8));
//	uintptr_t FNameEntry = NamePoolChunk + (0x2 * Offset);
//
//	INT16 FNameEntryHeader = read<INT16>(FNameEntry);
//	uintptr_t StrPtr = FNameEntry + 0x2;
//	int StrLength = FNameEntryHeader >> 0x6;
//
//	if (StrLength > 0 && StrLength < 250) {
//		auto result =  readwtf(StrPtr, &name, StrLength);
//		return std::string(name);
//	}
//	return std::string(xor ("ERROR"));
//}



#define M_PI	3.14159265358979323846264338327950288419716939937510
D3DXMATRIX ToMatrix(Vector3 Rotation, Vector3 origin = Vector3(0, 0, 0));
D3DXMATRIX ToMatrix(Vector3 Rotation, Vector3 origin)
{
	float Pitch = (Rotation.x * float(M_PI) / 180.f);
	float Yaw = (Rotation.y * float(M_PI) / 180.f);
	float Roll = (Rotation.z * float(M_PI) / 180.f);

	float SP = sinf(Pitch);
	float CP = cosf(Pitch);
	float SY = sinf(Yaw);
	float CY = cosf(Yaw);
	float SR = sinf(Roll);
	float CR = cosf(Roll);

	D3DXMATRIX Matrix;
	Matrix._11 = CP * CY;
	Matrix._12 = CP * SY;
	Matrix._13 = SP;
	Matrix._14 = 0.f;

	Matrix._21 = SR * SP * CY - CR * SY;
	Matrix._22 = SR * SP * SY + CR * CY;
	Matrix._23 = -SR * CP;
	Matrix._24 = 0.f;

	Matrix._31 = -(CR * SP * CY + SR * SY);
	Matrix._32 = CY * SR - CR * SP * SY;
	Matrix._33 = CR * CP;
	Matrix._34 = 0.f;

	Matrix._41 = origin.x;
	Matrix._42 = origin.y;
	Matrix._43 = origin.z;
	Matrix._44 = 1.f;

	return Matrix;
}

D3DXMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

struct FMinimalViewInfo
{
	Vector3 Location;
	Vector3 Rotation;
	float FOV;
};
struct FCameraCacheEntry
{
	float TimeStamp;
	char UnknownData00[0xC];
	FMinimalViewInfo POV;
};
Vector3 WorldToScreenX(Vector3 WorldLocation, FMinimalViewInfo CameraCacheL)
{
	Vector3 Screenlocation = Vector3(0, 0, 0);

	auto POV = CameraCacheL;
	Vector3 Rotation = POV.Rotation;
	D3DMATRIX tempMatrix = Matrix(Rotation);

	Vector3 vAxisX, vAxisY, vAxisZ;

	vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	Vector3 vDelta = WorldLocation - POV.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	float FovAngle = POV.FOV;
	float ScreenCenterX = Width / 2.0f;
	float ScreenCenterY = Height / 2.0f;

	Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

	return Screenlocation;
}


//std::string GetSurvName(std::string retname) {
//
//	string survivorname = xor("SURVIVOR");
//	if (retname.find(xor("BP_CamperFemale01_Character")) != string::npos) survivorname = xor("Meg");
//	else if (retname.find(xor("BP_CamperFemale02_Character")) != string::npos) survivorname = xor("Claudette");
//	else if (retname.find(xor("BP_CamperFemale03_Character")) != string::npos) survivorname = xor("Nea");
//	else if (retname.find(xor("BP_CamperFemale04_Character")) != string::npos) survivorname = xor("Laurie");
//	else if (retname.find(xor("BP_CamperFemale05_Character")) != string::npos) survivorname = xor("Feng");
//	else if (retname.find(xor("BP_CamperFemale06_Character")) != string::npos) survivorname = xor("Kate");
//	else if (retname.find(xor("BP_CamperFemale07_Character")) != string::npos) survivorname = xor("Jane");
//	else if (retname.find(xor("BP_CamperFemale08_Character")) != string::npos) survivorname = xor("Nancy");
//	else if (retname.find(xor("BP_CamperFemale09_Character")) != string::npos) survivorname = xor("Yui");
//	else if (retname.find(xor("BP_CamperFemale10_Character")) != string::npos) survivorname = xor("Zarina");
//	else if (retname.find(xor("BP_CamperFemale11_Character")) != string::npos) survivorname = xor("Cheryl");
//	else if (retname.find(xor("BP_CamperFemale12_Character")) != string::npos) survivorname = xor("Elodie");
//	else if (retname.find(xor("BP_CamperFemale13_Character")) != string::npos) survivorname = xor("Yun-Jin");
//	else if (retname.find(xor("BP_CamperFemale14_Character")) != string::npos) survivorname = xor("Jill");
//	else if (retname.find(xor("BP_CamperFemale15_Character")) != string::npos) survivorname = xor("Mikaela");
//
//	else if (retname.find(xor("BP_CamperMale01")) != string::npos) survivorname = xor("Dwight");
//	else if (retname.find(xor("BP_CamperMale02_Character")) != string::npos) survivorname = xor("Jake");
//	else if (retname.find(xor("BP_CamperMale03_Character")) != string::npos) survivorname = xor("Ace");
//	else if (retname.find(xor("BP_CamperMale04_Character")) != string::npos) survivorname = xor("Bill");
//	else if (retname.find(xor("BP_CamperMale05_Character")) != string::npos) survivorname = xor("David");
//	else if (retname.find(xor("BP_CamperMale06_Character")) != string::npos) survivorname = xor("Quentin");
//	else if (retname.find(xor("BP_CamperMale07_Character")) != string::npos) survivorname = xor("Tapp");
//	else if (retname.find(xor("BP_CamperMale08_Character")) != string::npos) survivorname = xor("Adam");
//	else if (retname.find(xor("BP_CamperMale09_Character")) != string::npos) survivorname = xor("Jeff");
//	else if (retname.find(xor("BP_CamperMale10_Character")) != string::npos) survivorname = xor("Ashley");
//	else if (retname.find(xor("BP_CamperMale11_Character")) != string::npos) survivorname = xor("Steve");
//	else if (retname.find(xor("BP_CamperMale12_Character")) != string::npos) survivorname = xor("Felix");
//	else if (retname.find(xor("BP_CamperMale13_Character")) != string::npos) survivorname = xor("Leon");
//	else if (retname.find(xor("BP_CamperMale14_Character")) != string::npos) survivorname = xor("Jonah");
//	else if (retname.find(xor("BP_CamperMale14_Character")) != string::npos) survivorname = xor("Yoichi");
//
//	return survivorname;
//}

typedef struct _TslEntity
{
	uint64_t pObjPointer;
	int ID;
	uint64_t Mesh;
	uint64_t PlayerController;
	uint64_t PlayerState;
	float health;
	string txt;
}TslEntity;
vector<TslEntity> entityList;

D3DXVECTOR4 Rect;
float AimSpeed = 2.755;

bool Distance = false;
bool Skeleton = false;
bool Fov = false;
int AimFOV = 160;
bool Aimbot = false;
bool aimIng = false;
bool F6 = false;
bool show = false;
ImFont* SkeetFont;
bool menu_key = false;
static int keystatus = 0;
static int realkey = 0;

namespace aimbot
{
	bool aimbot = false;
	bool aimbotmob = false;
	bool smooth = false;
	bool fovcircle = false;

	int smoothscale;
	float aimspeed;
	float aimfov;

	int hitbox = 0;
}

namespace hotkeys
{
	int aimkey;
	int airstuckey;
	int speedkey;
}

enum Bones : int
{
	Pelvis = 1,
	Head = 10,
	Neck = 9
};


struct FBoneNode
{
public:
	int                                                Name;                                                    // 0x0000(0x000C) ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	int32_t                                                    ParentIndex;                                             // 0x000C(0x0004) ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	char pad[0x1];                              // 0x0010(0x0001) Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic
	unsigned char                                              UnknownData_L5SF[0x3];                                   // 0x0011(0x0003) MISSED OFFSET (PADDING)
};


void ClearSpecialCharacters(std::string& strText) {
	const std::string cAllowed = xor ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890,.-");

	// Iterate through the characters in the string and erase any characters
	// that are not in the allowed set of characters.
	for (auto it = strText.begin(); it != strText.end();) {
		if (cAllowed.find(*it) == std::string::npos) {
			it = strText.erase(it);
		}
		else {
			++it;
		}
	}
}

namespace menu
{
	int box_thick;
	float font_size;
}

namespace temp
{
	int tempI;
	float tempF;
	std::string tempS;
	uint64_t tempPo;
}

void print_bones(uint64_t mesh) 
{
	const auto skeletal_mesh = read<uint64_t>(mesh + 0x578);

	const auto bone_names_array =read<uint64_t>(skeletal_mesh + 0x2e8);
	const auto bone_names_array_size =read<uint32_t>(skeletal_mesh + 0x2F0);

	for (auto i = 0u; i < bone_names_array_size; ++i)
	{
		const auto name_index =read<uint32_t>(bone_names_array + 0xC * i);
		std::string name = get_name_by_id(name_index); // c'est bon mais comporte des caractères spéciaux
		//ClearSpecialCharacters(name);

		printf(xor("Index: %i | Bone: %s\n"), i, name.c_str());
	}
}

/*
Index: 0 | Bone: Root
Index: 1 | Bone: pelvis
Index: 2 | Bone: spine_01
Index: 3 | Bone: spine_02
Index: 4 | Bone: spine_03
Index: 5 | Bone: clavicle_l
Index: 6 | Bone: upperarm_l
Index: 7 | Bone: lowerarm_l
Index: 8 | Bone: hand_l
Index: 9 | Bone: thumb_01_l
Index: 10 | Bone: thumb_02_l
Index: 11 | Bone: thumb_03_l
Index: 12 | Bone: index_01_l
Index: 13 | Bone: index_02_l
Index: 14 | Bone: index_03_l
Index: 15 | Bone: middle_01_l
Index: 16 | Bone: middle_02_l
Index: 17 | Bone: middle_03_l
Index: 18 | Bone: ring_01_l
Index: 19 | Bone: ring_02_l
Index: 20 | Bone: ring_03_l
Index: 21 | Bone: pinky_01_l
Index: 22 | Bone: pinky_02_l
Index: 23 | Bone: pinky_03_l
Index: 24 | Bone: fk_weapon_l
Index: 25 | Bone: shield_l
Index: 26 | Bone: lowerarm_twist_01_l
Index: 27 | Bone: upperarm_twist_01_l
Index: 28 | Bone: neck_01
Index: 29 | Bone: Head
Index: 30 | Bone: eyelid_l
Index: 31 | Bone: eyelid_r
Index: 32 | Bone: clavicle_r
Index: 33 | Bone: upperarm_r
Index: 34 | Bone: lowerarm_r
Index: 35 | Bone: lowerarm_twist_01_r
Index: 36 | Bone: shield_r
Index: 37 | Bone: hand_r
Index: 38 | Bone: pinky_01_r
Index: 39 | Bone: pinky_02_r
Index: 40 | Bone: pinky_03_r
Index: 41 | Bone: ring_01_r
Index: 42 | Bone: ring_02_r
Index: 43 | Bone: ring_03_r
Index: 44 | Bone: middle_01_r
Index: 45 | Bone: middle_02_r
Index: 46 | Bone: middle_03_r
Index: 47 | Bone: index_01_r
Index: 48 | Bone: index_02_r
Index: 49 | Bone: index_03_r
Index: 50 | Bone: thumb_01_r
Index: 51 | Bone: thumb_02_r
Index: 52 | Bone: thumb_03_r
Index: 53 | Bone: fk_weapon_r
Index: 54 | Bone: upperarm_twist_01_r
Index: 55 | Bone: thigh_l
Index: 56 | Bone: calf_l
Index: 57 | Bone: foot_l
Index: 58 | Bone: ball_l
Index: 59 | Bone: calf_twist_01_l
Index: 60 | Bone: thigh_twist_01_l
Index: 61 | Bone: thigh_r
Index: 62 | Bone: calf_r
Index: 63 | Bone: foot_r
Index: 64 | Bone: ball_r
Index: 65 | Bone: calf_twist_01_r
Index: 66 | Bone: thigh_twist_01_r
Index: 67 | Bone: ik_foot_root
Index: 68 | Bone: ik_foot_l
Index: 69 | Bone: ik_foot_r
Index: 70 | Bone: ik_hand_root
Index: 71 | Bone: ik_hand_gun
Index: 72 | Bone: ik_hand_l
Index: 73 | Bone: weapon_l
Index: 74 | Bone: ik_hand_r
Index: 75 | Bone: weapon_r
Index: 76 | Bone: camera_root
Index: 77 | Bone: camera_rot_root
Index: 78 | Bone: Camera */

//void GetBones(uint64_t mesh, uint32_t* tab)	
//{
//	const auto skeletal_mesh =read<uint64_t>(mesh + 0x4d8);
//	if (!skeletal_mesh)
//		return;
//
//	const auto bone_names_array =read<uint64_t>(skeletal_mesh + 0x1b8);
//	if (!bone_names_array)
//		return;
//	const auto bone_names_array_size =read<uint32_t>(skeletal_mesh + 0x1b8 + sizeof(uintptr_t));
//
//
//	for (auto i = 0; i < bone_names_array_size; ++i)
//	{
//		const auto name_index =read<uint32_t>(bone_names_array + 0x10 * i);
//		std::string name = get_name_by_id(name_index); // c'est bon mais comporte des caractères spéciaux
//		if(name.find(xor("joint_Head_01")) != std::string::npos)
//			tab[0] = i;
//		else if (name.find(xor("joint_NeckA_01")) != std::string::npos)
//			tab[1] = i;
//		else if (name.find(xor ("joint_Pelvis_01")) != std::string::npos)
//			tab[2] = i;
//		else if (name.find(xor ("joint_ShoulderRT_01")) != std::string::npos)
//			tab[3] = i;
//		else if (name.find(xor ("joint_ElbowRT_01")) != std::string::npos)
//			tab[4] = i;
//		else if (name.find(xor ("joint_HandRT_01")) != std::string::npos)
//			tab[5] = i;
//		else if (name.find(xor ("joint_HipRT_01")) != std::string::npos)
//			tab[6] = i;
//		else if (name.find(xor ("joint_KneeRT_01")) != std::string::npos)
//			tab[7] = i;
//		else if (name.find(xor ("joint_FootRT_01")) != std::string::npos)
//			tab[8] = i;
//		else if (name.find(xor ("joint_ShoulderLT_01")) != std::string::npos)
//			tab[9] = i;
//		else if (name.find(xor ("joint_ElbowLT_01")) != std::string::npos)
//			tab[10] = i;
//		else if (name.find(xor ("joint_HandLT_01")) != std::string::npos)
//			tab[11] = i;
//		else if (name.find(xor ("joint_HipLT_01")) != std::string::npos)
//			tab[12] = i;
//		else if (name.find(xor ("joint_KneeLT_01")) != std::string::npos)
//			tab[13] = i;
//		else if (name.find(xor ("joint_FootLT_01")) != std::string::npos)
//			tab[14] = i;
//		
//	}
//}

uint64_t camera_manager;
uint64_t pawn;
Vector3 localrelative_component;
uint64_t playercontroller;





void cache()
{
	//printf("9");

	while (true)
	{
		//printf("2");

		vector<TslEntity> tmpList;
		if (BaseAddressTemp == 0)
			continue;

		uint64_t uworld = read<uint64_t>(BaseAddressTemp + UWORLD);
		//147380308
		//printf("3");
		if (uworld == 0 || BaseAddressTemp == 0)
		{
			continue;
			MessageBoxA(0, xor("DARK NEED UPDATE, CONTACT STAFF !"), xor("WAR ERROR"), MB_OK);
		}

		//printf("BaseAddressTemp: %p\n", BaseAddressTemp);
		//printf("uworld: %p\n", uworld);
		uint64_t persislevel =read<uint64_t>(uworld + Offsets::UWorld::PersistentLevel);
		//printf("persislevel: %p\n", persislevel);
		uint64_t gameinstance =read<uint64_t>(uworld + Offsets::UWorld::OwningGameInstance); //UWolrd->OwningGameInstance
		//printf("gameinstance: %p\n", gameinstance);
		uint64_t localplayer =read<uint64_t>(gameinstance + Offsets::UGameInstance::LocalPlayers); //UGameInstance ->LocalPlayers
		//printf("localplayer : %p\n", localplayer);
		uint64_t localplayers =read<uint64_t>(localplayer);
		//printf("localplayers: %p\n", localplayers);
		playercontroller =read<uint64_t>(localplayers + Offsets::UPlayer::PlayerController); //UPlayer->PlayerController
		//printf("playercontroller: %p\n", playercontroller);
		camera_manager = read<uint64_t>(playercontroller + Offsets::UPlayerController::PlayerCameraManager); //APlayerController->PlayerCameraManager
		//printf("camera_manager ->%p\n", camera_manager);
		pawn =read<uint64_t>(playercontroller + Offsets::UPlayerController::Pawn); //APlayerController->AcknowledgePawn
		//printf("pawn: %p\n", pawn);
		if (playercontroller == 0)
		{
			continue;
		}
		if (camera_manager == 0)
		{
			continue;
		}

		uint64_t LocalPlayerName = 0;
		uint64_t LocalPlayerState = 0;
		if (pawn != 0)
		{
			LocalPlayerState =read<uint64_t>(pawn + Offsets::APawn::PlayerState); //APawn->PlayerState
			//printf("LocalPlayerStat: %p\n", LocalPlayerState);
		}

		//if (LocalPlayerState != 0)
		//{
		//	uint64_t LocalPlayerName =read<uint64_t>(LocalPlayerState + Offsets::APlayerState::PlayerName); //APlayerState->PlayerNamePrivate
		//	char Localbuff[64];
		//	if (LocalPlayerName)
		//	{
		//		m_pHyperV->readwtf(LocalPlayerName, Localbuff, 64);
		//	}
		//}

		//if (cachedfov != 0 && camera_manager != 0)
		//{
		//	float cache =read<float>(camera_manager + Offsets::UPlayerCameraManager::FOV + 0x4); //APlayerCameraManager -> DefaultFOV + 0x4
		//	//if (cache >= 0 && cache < 160 && cache != cachedfov)
		//	//{
		//	//	write<float>(camera_manager + Offsets::UPlayerCameraManager::FOV + 0x4, cachedfov);
		//	//}
		//}
		//printf("fov %f \n", read<float>(camera_manager + 0x24c));

		//printf("actor count : %d \n", actor_count);

	/*	write<BYTE>(BaseAddressTemp + m_ThroughWallHook, 116);*/


		//uint64_t actor_array = read<uint64_t>(persislevel + 0x98); //  OwningActor; 
		//int actor_count = read<int>(persislevel + 0xa0); // MaxPacket; 
		//printf("actor_count: %p\n", actor_count);

		uint64_t localroot_component = read<uint64_t>(pawn + 0x130);
		localrelative_component = read<Vector3>(localroot_component + 0x11C);

		TArray<uint64_t> Levels = read<TArray<uint64_t>>(uworld + 0x138);
		//printf("L Count : %d", Levels.Length());

		for (unsigned long j = 0; j < Levels.Length(); ++j)
		{
			uint64_t actor_array = read<uint64_t>(Levels[j] + 0x98);
			int actor_count = read<int>(Levels[j] + 0xa0);
			for (unsigned long i = 0; i < actor_count; ++i)
			{
				uint64_t actor = read<uint64_t>(actor_array + (i * 0x8));
				if (actor == 0x00)
					continue;

				int ID = read<int32>(actor + 0x18);
				if (ID == 0x00)
					continue;

				TslEntity tslEntity{ };
				tslEntity.pObjPointer = actor;
				tslEntity.ID = ID;

				uint64_t mesh = read<uint64_t>(actor + 0x280); //ACharacter->Mesh juste
				uint64_t playerstate = read<uint64>(actor + 0x240);
				uint64_t rootcomponent = read<uint64_t>(actor + 0x130); //AActor	RootComponent
				//printf("rootcomponent : %p\n", rootcomponent);
				//Vector3 relativelocation = read<Vector3>(rootcomponent + 0x128); //USceneComponent->RelativeLocation
				//FCameraCacheEntry camera_cache = read<FCameraCacheEntry>(camera_manager + 0x1AE0); //APlayerCameraManager->CameraCachePrivate    IMPORTANT SI FREEZE

			

				std::string g = get_name_by_id(ID);
				//printf("%s \n", g.c_str());

				//temp::tempS = g;
				
					tmpList.push_back(tslEntity);
				
			
					if (visuals::sentry) {
						if (g.find(xor ("BP_Sentry")) != std::string::npos)
						{
							tmpList.push_back(tslEntity);
						}
					}

				if (g.find(xor ("BPC_Weapon_")) != std::string::npos)
				{
					tmpList.push_back(tslEntity);
				}

				if (g.find(xor ("BP_Weapon_")) != std::string::npos)
				{
					tmpList.push_back(tslEntity);
				}

				if (visuals::mob) {
					if (g.find(xor ("BP_Wolf")) != std::string::npos || g.find(xor ("BP_Bear")) != std::string::npos || g.find(xor ("BP_Chicken")) != std::string::npos || g.find(xor ("BP_Horse2_C")) != std::string::npos)
					{
						tmpList.push_back(tslEntity);
					}
				}
				if (visuals::ghost) {
					if (g.find(xor ("BP_Pickup_01")) != std::string::npos)
					{
						tmpList.push_back(tslEntity);
					}
					if (g.find(xor ("BP_Quad_01")) != std::string::npos)
					{
						tmpList.push_back(tslEntity);
					}

					if (g.find(xor ("SM_Car")) != std::string::npos)
					{
						tmpList.push_back(tslEntity);
					}

					if (g.find(xor ("BP_SUV_01")) != std::string::npos)
					{
						tmpList.push_back(tslEntity);
					}

				}
				if (visuals::drone) {
					if (g.find(xor ("Drone")) != std::string::npos)
					{
						tmpList.push_back(tslEntity);
					}
				}

				if (visuals::bear) {
					if (g.find(xor ("Cal")) != std::string::npos)
					{
						tmpList.push_back(tslEntity);
					}
				}

				if (visuals::chest) {
					if (g.find(xor ("Claymore")) != std::string::npos || g.find(xor ("ImprovisedClaymore")) != std::string::npos || g.find(xor ("Mine_01")) != std::string::npos || g.find(xor ("Mine_02")) != std::string::npos || g.find(xor ("PromTrap")) != std::string::npos || g.find(xor ("Sensor_Detonator")) != std::string::npos || g.find(xor ("PipeBomb")) != std::string::npos || g.find(xor ("StakePitTrap")) != std::string::npos || g.find(xor ("PressureCookerBomb")) != std::string::npos || g.find(xor ("CartridgeTrap")) != std::string::npos)
					{
						tmpList.push_back(tslEntity);
					}
				}

				if (visuals::Explosive) {
					if (g.find(xor ("ImProvised_Metal_Chest_C")) != std::string::npos || g.find(xor ("ImProvised_Wooden_Chest_C")) != std::string::npos || g.find(xor ("BP_Mound_C")) != std::string::npos)
					{
						tmpList.push_back(tslEntity);
					}
				}

		
				

				if (visuals::simplechest) {
					if (g.find(xor ("BP_Zombie_")) != std::string::npos)
					{
						tmpList.push_back(tslEntity);
					}
				}

				if (g.find(xor ("BP_Prisoner_C")) != std::string::npos)
				{
					tslEntity.Mesh = read<uint64_t>(actor + 0x280);
					tslEntity.PlayerState = playerstate;
					tmpList.push_back(tslEntity);

					//voici l exemple de highJump :
					uint64_t CharacterMovement = read<uint64_t>(actor + 0x288); //Class Engine.Character

					float GravityScale = read<float>(CharacterMovement + 0x150); //// Class Engine.CharacterMovementComponent

					// 0x18C

					if (visuals::gravity && GravityScale != 0.5f) {
						write<float>(CharacterMovement + 0x150, 0.5f);
					}
					else if (GravityScale != 1.f) {
						write<float>(CharacterMovement + 0x150, 1.f);
					}

					if (visuals::fov)
						write<float>(camera_manager + 0x23C, visuals::fovvalue);

					if (visuals::speedhackbool) 
						write<float>(actor + 0x98, visuals::speedhack);
					else 
						write<float>(actor + 0x98, 1.f);
					
				
				

					/*if (visuals::lock)*/
					

					//write<float>(BaseAddressTemp + 0x2FC07C7, 1);

					/*uint64_t MovementSettings = read<uint64_t> + 0x7c0
						write MovementSettings + 0xD8, 1500.f);*/

				  }
				//write<float>(actor + 0x2e8, 7);
				
				//}
				/*else if (visuals::print) {
					if (distancia < 7) {
						tmpList.push_back(tslEntity);
					}
				}*/

				//if (visuals::closet) {
				//	if (g.find(xor ("ClosetStandard_C")) != std::string::npos)
				//	{
				//		tmpList.push_back(tslEntity);
				//	}

				//}
				//if (g.find(xor ("BP_Slasher_Character_")) != std::string::npos || g.find(xor ("_20_C")) != std::string::npos) 
				//{
				//	uint64_t playerstate = read<uint64>(actor + Offsets::APawn::PlayerState);
				//	uint64_t PlayerName =read<uint64_t>(playerstate + Offsets::APlayerState::PlayerName);
				//	uint64_t mesh = read<uint64_t>(actor + Offsets::ACharacter::Mesh); 

				//	tslEntity.Mesh = mesh;
				//	tslEntity.PlayerState = playerstate;

				//	tmpList.push_back(tslEntity);
				//}
			}
		}
		entityList = tmpList;

		//others level
		//TArray<uint64_t> Levels = read<TArray<uint64_t>>(uworld + 0x148);
		//for (int l = 1; l < Levels.Length(); l++) {
		//	uint64_t actor_array2 = read<uint64_t>(Levels[l] + 0xa0);
		//	int actor_count2 = read<int>(Levels[l] + 0xa8);
		//	for (unsigned long m = 0; m < actor_count2; ++m) {
		//		uint64_t actor2 = read<uint64_t>(actor_array2 + (m * 0x8));
		//		if (actor2 == 0x00)
		//			continue;
		//		int ID2 = read<int32>(actor2 + 0x18);
		//		std::string g2 = GetName(ID2);
		//		//if(g2.find("fog") != string::npos)
		//			printf("%s \n", g2.c_str());
		//	}
		//}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));  //100

	}
}

struct PlayerName
{
	wchar_t PlayerName[64];
};
bool IsVec3Valid(Vector3 vec3)
{
	return !(vec3.x == 0 && vec3.y == 0 && vec3.z == 0);
}

DWORD_PTR pSavedTarget;
bool LastFrameAimKey = false;
DWORD_PTR pTarget;
DWORD_PTR mob;

float Skelcolor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

INT64 lastTime = 0;
void usleep(unsigned int usec)
{
	HANDLE timer;
	LARGE_INTEGER ft;

	ft.QuadPart = -(10 * (__int64)usec);

	timer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}
int getRandomInt(int min, int max) {
	random_device rd;
	mt19937 mt(rd());
	return mt() % (max - min + 1) + min;
}

bool GetKey(int key)
{
	realkey = key;
	return true;
}
void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}

void ChangeKey2(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::speedkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}

static const char* keyNames[] =
{
	"",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};


inline float Rad2Deg(float rad) {
	return rad * 180.0f / 3.1415927f;
}
const auto hypotenusa = [](float in)
{
	__m128 reg = _mm_load_ss(&in);
	return _mm_mul_ss(reg, _mm_rsqrt_ss(reg)).m128_f32[0];
};



D3DXVECTOR3 CalcAngle(const D3DXVECTOR3& src, const D3DXVECTOR3& dst)
{
	D3DXVECTOR3 angles;
	D3DXVECTOR3 delta = src - dst;
	float hyp = hypotenusa(delta.x * delta.x + delta.y * delta.y);
	angles.x = -Rad2Deg(asinf(delta.z / hyp));
	angles.y = Rad2Deg(atanf(delta.y / delta.x));
	angles.z = 0.0f;
	return angles;
}
float RankTargetByAngleDistance(D3DXVECTOR3 localplayerpos, Vector3 localplayerangles, float targetdistance, D3DXVECTOR3 targetpos)
{
	D3DXVECTOR3 angleto = CalcAngle(localplayerpos, targetpos);
	float distance_weight = 0.40f;
	float angle_weight = 0.60f;

	return targetdistance * distance_weight + (localplayerangles.DistTo(Vector3(angleto.x, angleto.y, angleto.z)) / 100.f) * angle_weight;
}

static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}

void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < 140)
		preview_value = keyNames[aimkey];

	std::string aimkeys;
	if (status == 1)
	{
		aimkeys = xor("Press key");
	}
	else if (preview_value == NULL || preview_value[0] == '\0')
	{
		aimkeys = xor("Select Key");
	}
	else
	{
		aimkeys = preview_value;
	}

	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}

//void SetViewAngles(D3DXVECTOR3 angle)
//{
//	write<D3DXVECTOR3>(playercontroller + 0x2a0, angle); //ControlRotation
//}
void ClampVector(Vector3& Ang) {
	if (Ang.x < -89.f) Ang.x = -89.f;
	else if (Ang.x > 89.f) Ang.x = 89.f;
	while (Ang.y < -180.f) Ang.y += 360.f;
	while (Ang.y > 180.f) Ang.y -= 360.f;
	Ang.z = 0.f;
}

struct textxx
{

	wchar_t word[64];
};

void move_to(float x, float y)
{
	float center_x = Width / 2;
	float center_y = Height / 2;

	float smooth = visuals::Smoothing;

	float target_x = 0.f;
	float target_y = 0.f;

	if (x != 0.f)
	{
		if (x > center_x)
		{
			target_x = -(center_x - x);
			target_x /= smooth;
			if (target_x + center_x > center_x * 2.f) target_x = 0.f;
		}

		if (x < center_x)
		{
			target_x = x - center_x;
			target_x /= smooth;
			if (target_x + center_x < 0.f) target_x = 0.f;
		}
	}

	if (y != 0.f)
	{
		if (y > center_y)
		{
			target_y = -(center_y - y);
			target_y /= smooth;
			if (target_y + center_y > center_y * 2.f) target_y = 0.f;
		}

		if (y < center_y)
		{
			target_y = y - center_y;
			target_y /= smooth;
			if (target_y + center_y < 0.f) target_y = 0.f;
		}
	}

	mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(target_x), static_cast<DWORD>(target_y), 0, 0);
}

DWORD keys[] = { VK_LMENU, VK_MENU, VK_SHIFT, VK_RSHIFT, VK_CONTROL, VK_RCONTROL, VK_LBUTTON, VK_RBUTTON };
const char* keyItems[] = { "LAlt", "RAlt", "LShift", "RShift", "LControl", "RControl", "LMouse", "RMouse" };

bool GetAimKey()
{
	return GetAsyncKeyState(keys[visuals::aimkey]);
}

void AIM() {

	while (true) {
	if (Off)
		return;

	bool isAimbotActive = visuals::aim && GetAimKey();
	if (isAimbotActive) {
		if (camera_manager == NULL) return;
		FCameraCacheEntry camera_cache = read<FCameraCacheEntry>(camera_manager + 0x1aa0); //APlayerCameraManager->CameraCachePrivate    IMPORTANT SI FREEZE

		float distance = 0;
		int count = 0;

		std::vector<TslEntity> entityListCopy = entityList;

		if (entityListCopy.empty())
			return;

		float target_dist = FLT_MAX;

		for (unsigned long i = 0; i < entityListCopy.size(); ++i)
		{
			TslEntity entity = entityListCopy[i];



			uint64_t rootcomponent = read<uint64_t>(entity.pObjPointer + 0x130); //AActor	RootComponent
			Vector3 relativelocation = read<Vector3>(rootcomponent + 0x128); //USceneComponent->RelativeLocation
			if (relativelocation.x == 0) continue;

		/*	if (entity.health == 0)
			   continue;*/

			Vector3 X = WorldToScreenX(relativelocation, camera_cache.POV);
			if (X.x < -Width || X.x > Width) continue;

			//printf("[!] FOV : %f \n", camera_cache.POV.FOV);
			distance = localrelative_component.DistTo(relativelocation) / 100.f;
			/*if (visuals::distance <= distance)
				continue;*/



			//auto vHeadBone = GetBoneWithRotation(entity.Mesh, 29);
			//auto vRootBone = GetBoneWithRotation(entity.Mesh, 0);

			//auto vHeadBoneOut = WorldToScreenX(Vector3(vHeadBone.x, vHeadBone.y, vHeadBone.z), camera_cache.POV);
			//auto vRootBoneOut = WorldToScreenX(vRootBone, camera_cache.POV);

			auto vHeadBone = GetBoneWithRotation(entity.Mesh, 67);
			auto targethead = WorldToScreenX(Vector3(vHeadBone.x, vHeadBone.y, vHeadBone.z + 15), camera_cache.POV);


			float x = targethead.x - Width / 2.0f;
			float y = targethead.y - Height / 2.0f;
			float crosshair_dist = sqrtf((x * x) + (y * y));

			if (crosshair_dist <= FLT_MAX && crosshair_dist <= target_dist)
			{
				if (crosshair_dist > visuals::AimbotFOV) // FOV
					continue;

				target_dist = crosshair_dist;
				entity = entity;
			}


			/*	if (entity.pObjPointer == pawn || entity.pObjPointer == 0)
					continue;*/

			move_to(targethead.x, targethead.y);
		}
	}
		Sleep(1);

	}
}

void HealtBar(float x, float y, float Health)
{
	DWORD HPcol = 0xFF10FF08;
	if (Health < 80)HPcol = 0xFFA9DB05;
	if (Health < 50)HPcol = 0xFFFBDA05;
	if (Health < 30)HPcol = 0xFFFB9505;
	if (Health < 10)HPcol = 0xFFFB2a05;

	Border(x, y, 50, 5, 0xFF000000);
	DrawFilledRect2(ImVec2(x + 1, y + 1), ImVec2(Health / 2, 4), HPcol);
}


static bool mouse_move(int x, int y)
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dx = x;
	input.mi.dy = y;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(input));
	return true;
}


float Calc2D_Distt(const Vector2& Src, const Vector3& Dst)
{
	float dx = Src.x - Dst.x;
	float dy = Src.y - Dst.y;
	return sqrt(dx * dx + dy * dy);
}

float AimFov(Vector3 ScreenPos)
{
	return Calc2D_Distt(Vector2(ScreenCenterX, ScreenCenterY), ScreenPos);
}

Vector3 LocalRelativeLocation; 


Vector3 vHeadBone;
Vector3 vHeadBoneOut;
void ESP() {

	if (Off)
		return;

	//ImRenderer->RenderString(ImVec2(10, 10), ImColor(255, 255, 255, 255), false, CRY_XORSTR_LIGHT("APEX ST | END KEY | FPS %d"), static_cast<int>(round(ImGui::GetIO().Framerate)));
	DrawString(15, 120, 18, &Col.white, true, true, xor ("SCUM ST | END KEY | FPS % d"), static_cast<int>(round(ImGui::GetIO().Framerate)));

	if (camera_manager == NULL) return;
	FCameraCacheEntry camera_cache = read<FCameraCacheEntry>(camera_manager + 0x1AE0); //APlayerCameraManager->CameraCachePrivate    IMPORTANT SI FREEZE
	//printf("camera_cache: %p\n", camera_cache);

	float distance = 0;
	int count = 0;

	std::vector<TslEntity> entityListCopy = entityList;

	if (entityListCopy.empty())
		return;


	for (unsigned long i = 0; i < entityListCopy.size(); ++i)
	{
		TslEntity entity = entityListCopy[i];

		if (entity.pObjPointer == pawn)
		{
			continue;
		}

		/*if (entity.pObjPointer == pawn || entity.pObjPointer == 0)
			continue;*/

		
		uint64_t rootcomponent = read<uint64_t>(entity.pObjPointer + 0x130); //AActor	RootComponent
	/*	printf("rootcomponent: %p\n", rootcomponent);*/
		Vector3 relativelocation = read<Vector3>(rootcomponent + 0x11C); //USceneComponent->RelativeLocation
	/*	printf("relativelocation: %p\n", relativelocation);*/
		if (relativelocation.x == 0) continue;

		//if (entity.health == 0)
		//	continue;

		Vector3 X = WorldToScreenX(relativelocation, camera_cache.POV);
		if (X.x < -Width || X.x > Width) continue;


		//printf("[!] FOV : %f \n", camera_cache.POV.FOV);
		distance = localrelative_component.DistTo(relativelocation) / 100.f;

		std::string g = get_name_by_id(entity.ID);

		/*if (distance < visuals::distance) */
		//	DrawString(menu::font_size, X.x, X.y, &Col.white_, true, true, g.c_str());
		//}

	//	printf("Distance: %f \n", distance);


		if (visuals::distance <= distance)
			continue;


		if (visuals::chest) {
			if (g.find(xor ("Claymore")) != std::string::npos || g.find(xor ("ImprovisedClaymore")) != std::string::npos || g.find(xor ("Mine_01")) != std::string::npos || g.find(xor ("Mine_02")) != std::string::npos || g.find(xor ("PromTrap")) != std::string::npos || g.find(xor ("Sensor_Detonator")) != std::string::npos || g.find(xor ("PipeBomb")) != std::string::npos || g.find(xor ("StakePitTrap")) != std::string::npos || g.find(xor ("PressureCookerBomb")) != std::string::npos || g.find(xor ("CartridgeTrap")) != std::string::npos)
			{
				char name[128];
				sprintf_s(name, "%s [%d m]", entity.txt.c_str(), (int)distance);
				DrawString(menu::font_size, X.x, X.y, &Col.white, true, true, name);
			}
		}

		if (visuals::Explosive) {
			if (g.find(xor ("ImProvised_Metal_Chest_C")) != std::string::npos || g.find(xor ("ImProvised_Wooden_Chest_C")) != std::string::npos || g.find(xor ("BP_Mound_C")) != std::string::npos)
			{
				char name[128];
				sprintf_s(name, "%s [%d m]", entity.txt.c_str(), (int)distance);
				DrawString(menu::font_size, X.x, X.y, &Col.white, true, true, name);
			}
		}

		if (visuals::drone) {
			if (g.find(xor ("Drone")) != std::string::npos) {
				char name[128];
				sprintf_s(name, "Drone[% 2.fm]", distance);
				DrawString(menu::font_size, X.x, X.y, &Col.blue, true, true, name);
			}
		}

		if (visuals::ghost) {
			if (g.find(xor ("SM_Car")) != std::string::npos) {
				char name[128];
				sprintf_s(name, "SM Car[% 2.fm]", distance);
				DrawString(menu::font_size, X.x, X.y, &Col.skyblue_, true, true, name);
			}

			if (g.find(xor ("BP_Quad_01")) != std::string::npos) {
				char name[128];
				sprintf_s(name, "Quad[% 2.fm]", distance);
				DrawString(menu::font_size, X.x, X.y, &Col.white_, true, true, name);
			}

			if (g.find(xor ("BP_Pickup_01")) != std::string::npos) {
				char name[128];
				sprintf_s(name, "Pickup[% 2.fm]", distance);
				DrawString(menu::font_size, X.x, X.y, &Col.white_, true, true, name);
			}
			if (g.find(xor ("BP_SUV_01")) != std::string::npos) {
				char name[128];
				sprintf_s(name, "SUV[% 2.fm]", distance);
				DrawString(menu::font_size, X.x, X.y, &Col.white_, true, true, name);
			}
		}

		if (visuals::bear) {
			if (g.find(xor ("Cal")) != std::string::npos) {
				char name[128];
				sprintf_s(name, "Ammo[% 2.fm]", distance);
				DrawString(menu::font_size, X.x, X.y, &Col.white_, true, true, name);
			}
		}

		if (visuals::simplechest) {
			if (g.find(xor ("BP_Zombie_")) != std::string::npos) {
				char name[128];
				sprintf_s(name, "Zombie[% 2.fm]", distance);
				DrawString(menu::font_size, X.x, X.y, &Col.green, true, true, name);

			}
		}

		if (visuals::mob) {
			if (g.find(xor ("BP_Wolf")) != std::string::npos || g.find(xor ("BP_Bear")) != std::string::npos || g.find(xor ("BP_Chicken")) != std::string::npos || g.find(xor ("BP_Horse2_C")) != std::string::npos)
			{
				char name[128];
				sprintf_s(name, "%s [%d m]", entity.txt.c_str(), (int)distance);
				DrawString(menu::font_size, X.x, X.y, &Col.white, true, true, name);
			}
		}
		if (visuals::ornateechest) {
			if (g.find(xor ("BP_Weapon_")) != std::string::npos) {
				char name[128];
				sprintf_s(name, "Weapon[% 2.fm]", distance);
				DrawString(menu::font_size, X.x, X.y, &Col.orange_, true, true, name);
			}

			if (g.find(xor ("BPC_Weapon_")) != std::string::npos) {
				char name[128];
				sprintf_s(name, "Weapon[% 2.fm]", distance);
				DrawString(menu::font_size, X.x, X.y, &Col.orange_, true, true, name);
			}
		}

		if (visuals::sentry) {
			if (g.find(xor ("BP_Sentry")) != std::string::npos) {
				char name[128];
				sprintf_s(name, "Sentry[% 2.fm]", distance);
				DrawString(menu::font_size, X.x, X.y, &Col.purple_, true, true, name);
			}
		}
		

		if (g.find(xor ("BP_Prisoner_C")) != std::string::npos) {

			char name[128];
			sprintf_s(name, "Player [%d m] life: %d", (int)distance, (int)entity.health);
			DrawPlayerBar(X.x, X.y + 25, &Col.glassblack, &Col.darkblue_, &Col.darkblue_, name);


			//BOX
			vHeadBone = GetBoneWithRotation(entity.Mesh, 67);
			auto vRootBone = GetBoneWithRotation(entity.Mesh, 0);

			vHeadBoneOut = WorldToScreenX(Vector3(vHeadBone.x, vHeadBone.y, vHeadBone.z), camera_cache.POV);
			auto vRootBoneOut = WorldToScreenX(vRootBone, camera_cache.POV);

			if (vHeadBoneOut.y == vHeadBoneOut.y) {  // Guard against undefined behavior.
				vHeadBoneOut.y += 1.0f;
			}
			float BoxHeight = abs(vHeadBoneOut.y - vRootBoneOut.y);
			float BoxWidth = BoxHeight / 1.8f;


			//if (visuals::healthbar) 
				
			
			if (visuals::tracers)
				DrawLine(vHeadBoneOut.x, vHeadBoneOut.y, Width / 2, 10, &Col.red_, 2.f);
		
			if (visuals::box)
				DrawCornerBox(vRootBoneOut.x - (BoxWidth / 2), vHeadBoneOut.y, BoxWidth, BoxHeight, 1, &Col.red);

		}

		if (Aimbot && GetAsyncKeyState(hotkeys::aimkey) && (AimFov(vHeadBoneOut) < AimFOV))
		{
			mouse_event(MOUSEEVENTF_MOVE, (vHeadBoneOut.x - (ScreenCenterX)) / AimSpeed, (vHeadBoneOut.y - (ScreenCenterY)) / AimSpeed, 0, 0);
		}

	}
}


//					//print_bones(entity.Mesh);
//				}
//			}
//		
//			//else {
//			//	char nam[128];
//			//	sprintf_s(nam, "%s [%.2f]", g.c_str(), distance);
//
//			//	DrawString(menu::font_size, X.x, X.y, &Col.white_, true, true, nam);
//			//	//printf("locX :	%ld , print X: %lf \n", relativelocation.x, X.x);
//			//}
//		
//		/*else if (visuals::print) {
//			char name[128];
//			sprintf_s(name, "%s [%d m]", g.c_str(), (int)distance);
//			DrawString(menu::font_size, X.x, X.y, &Col.white_, true, true, name);
//		}*/
//
//		
//
//
//		//if (g.find(xor ("BearTrap_C")) != std::string::npos || g.find(xor ("BP_BearTrap_001_C")) != std::string::npos && !(g.find(xor ("Trigger")) != std::string::npos) /*&& !(g.find(xor ("001")) != std::string::npos)*/) {
//
//		//		char name[64];
//		//		sprintf_s(name, xor ("BearTrap[%2.fm]"), distance);
//		//		DrawString(menu::font_size, X.x, X.y, &Col.white_, true, true, name);
//		//}
//
//		////-> KILLERS
//		//if (g.find(xor ("BP_Slasher_Character_")) != std::string::npos || g.find(xor ("Twin")) != std::string::npos || g.find(xor ("_20_C")) != std::string::npos)
//		//{
//		//	if (visuals::slasher)
//		//	{
//		//		if (g.find(xor ("BP_Slasher_Character_01")) != std::string::npos) {
//		//			char name[64];
//		//			sprintf_s(name, xor("Trapper[%2.fm]"), distance);
//		//			DrawPlayerBar(X.x, X.y + 25, &Col.glassblack, &Col.red_, &Col.red_, name);
//		//		}
//		//	}
//		//} 
//
//
//		//else if (g.find(xor("PlayerState")) != std::string::npos) {
//		//	if (visuals::teaminfo)
//		//	{
//		//		uint64_t PlayerName =read<uint64_t>(entity.pObjPointer + Offsets::APlayerState::PlayerName); //PlayerNamePrivate
//		//		textxx nm;
//		//		if (PlayerName)
//		//		{
//		//			//readwtf(PlayerName, buff, 64);
//		//			nm = read<textxx>(PlayerName); //PlayerNamePrivate
//
//		//		}
//		//		// Get the required buffer size for the converted string
//		//		int bufferSize = WideCharToMultiByte(CP_UTF8, 0, nm.word, -1, NULL, 0, NULL, NULL);
//
//		//		// Allocate a buffer for the converted string
//		//		char* buffer = new char[bufferSize];
//
//		//		// Convert the wchar_t string to a UTF-8 encoded string
//		//		WideCharToMultiByte(CP_UTF8, 0, nm.word, -1, buffer, bufferSize, NULL, NULL);
//
//		//		// Create a std::string from the converted string
//		//		std::string strus(buffer);
//
//
//		//		// Free the buffer
//		//		delete[] buffer;
//
//		//		
//		//		//if (entity.Prestige == 0) //isspectator
//		//		//{
//		//		//	Total = "SURV: " + entity.perk1 + " | " + entity.perk2 + " | " + entity.perk3 + " | " + entity.perk4;
//		//		//}
//		//		//else
//		//		//{
//		//		//	Total = "(SPEC)SURV: " + entity.perk1 + " | " + entity.perk2 + " | " + entity.perk3 + " | " + entity.perk4;
//		//		//}
//
//		//		count++;
//		//	}
//		//}
//
//		
//	}
//}

HRESULT DirectXInit(HWND hWnd)
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = hWnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = Width;
	p_Params.BackBufferHeight = Height;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;
	p_Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device)))
	{
		p_Object->Release();
		exit(4);
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImFontConfig FontConfig{};
	FontConfig.PixelSnapH = false;
	FontConfig.OversampleH = 5;
	FontConfig.OversampleV = 5;
	FontConfig.RasterizerMultiply = 1.2f;
	FontConfig.GlyphRanges = io.Fonts->GetGlyphRangesCyrillic();

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF,
		0x0400, 0x044F,
		0,
	};

	io.Fonts->AddFontFromFileTTF(CRY_XORSTR_LIGHT("C:\\Windows\\Fonts\\Verdana.ttf"), 18.f);
	SkeetFont = io.Fonts->AddFontFromFileTTF(CRY_XORSTR_LIGHT("C:\\Windows\\Fonts\\Verdana.ttf"), 18.f, nullptr, io.Fonts->GetGlyphRangesChineseFull());


	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(p_Device);


	ImGuiStyle& s = ImGui::GetStyle();


	const ImColor accentCol = ImColor(22, 23, 28, 255);
	const ImColor bgSecondary = ImColor(22, 23, 28, 255);
	s.Colors[ImGuiCol_WindowBg] = ImColor(22, 23, 28, 255);
	s.Colors[ImGuiCol_ChildBg] = bgSecondary;
	s.Colors[ImGuiCol_FrameBg] = ImColor(22, 23, 28, 255);
	s.Colors[ImGuiCol_FrameBgActive] = ImColor(35, 37, 39, 255);
	s.Colors[ImGuiCol_Border] = ImColor(1, 1, 1, 255);
	s.Colors[ImGuiCol_CheckMark] = ImColor(150, 147, 147, 255);
	s.Colors[ImGuiCol_SliderGrab] = ImColor(150, 147, 147, 255);
	s.Colors[ImGuiCol_SliderGrab] = ImColor(150, 147, 147, 255);
	s.Colors[ImGuiCol_SliderGrabActive] = ImColor(150, 147, 147, 255);
	s.Colors[ImGuiCol_ResizeGrip] = ImColor(24, 24, 24, 255);
	s.Colors[ImGuiCol_Header] = ImColor(22, 23, 28, 255);
	s.Colors[ImGuiCol_HeaderHovered] = ImColor(22, 23, 28, 255);
	s.Colors[ImGuiCol_HeaderActive] = ImColor(22, 23, 28, 255);
	s.Colors[ImGuiCol_TitleBg] = ImColor(39, 40, 48, 255);
	s.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(39, 40, 48, 255);
	s.Colors[ImGuiCol_TitleBgActive] = ImColor(39, 40, 48, 255);
	s.Colors[ImGuiCol_FrameBgHovered] = ImColor(22, 23, 28, 255);
	s.Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	s.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	s.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	s.Colors[ImGuiCol_Header] = ImColor(22, 23, 28, 255);
	s.Colors[ImGuiCol_HeaderHovered] = ImColor(50, 50, 50, 255);
	s.Colors[ImGuiCol_HeaderActive] = ImColor(50, 50, 50, 255);
	s.Colors[ImGuiCol_PopupBg] = ImColor(15, 15, 15, 255);
	s.Colors[ImGuiCol_Button] = ImColor(22, 23, 28, 255);
	s.Colors[ImGuiCol_ButtonHovered] = ImColor(22, 23, 28, 255);
	s.Colors[ImGuiCol_ButtonActive] = ImColor(22, 23, 28, 255);
	s.Colors[ImGuiCol_Text] = ImColor(150, 147, 147, 255);

	s.AntiAliasedFill = true;
	s.AntiAliasedLines = true;

	s.ChildRounding = 0.0f;
	s.FrameBorderSize = 1.0f;
	s.FrameRounding = 0.0f;
	s.PopupRounding = 0.0f;
	s.ScrollbarRounding = 0.0f;
	s.ScrollbarSize = 0.0f;
	s.TabRounding = 0.0f;
	s.WindowRounding = 0.0f;

	p_Object->Release();
	return S_OK;
}


std::wstring Randomxstring(size_t length)
{
	std::wstring r;
	static const char bet[] = { "1234567890" };
	srand((unsigned)time(NULL) * 5);
	for (int i = 0; i < length; ++i)
		r += bet[rand() % (sizeof(bet) - 1)];
	return r;
}

inline uintptr_t get_module_base(uint32_t process_id, const wchar_t* module_name)
{
	uintptr_t base_address = 0;
	const HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process_id);
	if (snapshot_handle != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 module_entry;
		module_entry.dwSize = sizeof(module_entry);
		if (Module32First(snapshot_handle, &module_entry))
		{
			do
			{
				if (!_wcsicmp(module_entry.szModule, module_name))
				{
					base_address = reinterpret_cast<uintptr_t>(module_entry.modBaseAddr);
					break;
				}
			} while (Module32Next(snapshot_handle, &module_entry));
		}
	}
	CloseHandle(snapshot_handle);
	return base_address;
}


void SetupWindow()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);

	//char randomtitle[] = ("XXXXXXXXX293");

	static std::wstring strOverlayClass = CRY_XORSTR_LIGHT_W(L" ");
	static std::wstring strOverlayTitle = CRY_XORSTR_LIGHT_W(L" ");

	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX),
		0,
		DefWindowProcA,
		0,
		0,
		nullptr,
		LoadIcon(nullptr, IDI_APPLICATION),
		LoadCursor(nullptr, IDC_ARROW),
		nullptr,
		nullptr,
		strOverlayClass.c_str(),
		LoadIcon(nullptr, IDI_APPLICATION)
	};

	RECT Rect;
	GetWindowRect(GetDesktopWindow(), &Rect);

	RegisterClassEx(&wc);

	MyWnd = CreateWindowEx(NULL, strOverlayClass.c_str(), strOverlayTitle.c_str(), WS_POPUP, Rect.left, Rect.top, Rect.right, Rect.bottom, 0, NULL, wc.hInstance, NULL);
	SetWindowLong(MyWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	SetLayeredWindowAttributes(MyWnd, RGB(0, 0, 0), 255, LWA_ALPHA);

	//LONG_PTR style = GetWindowLongPtr(MyWnd, GWL_EXSTYLE);
	//style |= WS_EX_TOOLWINDOW;
	//SetWindowLongPtr(MyWnd, GWL_EXSTYLE, style);
	int windowWidth = Rect.right - Rect.left;
	int windowHeight = Rect.bottom - Rect.top;
	int holeLeft = windowWidth / 2 - 1;  // center of the window minus 1 pixel
	int holeTop = windowHeight / 2 - 1;  // center of the window minus 1 pixel
	int holeRight = holeLeft + 2;  // center of the window plus 1 pixel
	int holeBottom = holeTop + 2;  // center of the window plus 1 pixel
	HRGN hWholeRegion = CreateRectRgn(0, 0, windowWidth, windowHeight);
	HRGN hHoleRegion = CreateRectRgn(holeLeft, holeTop, holeRight, holeBottom);
	CombineRgn(hWholeRegion, hWholeRegion, hHoleRegion, RGN_DIFF);

	// Apply the region to the window, which will create a hole in it
	SetWindowRgn(MyWnd, hWholeRegion, TRUE);

	// Clean up
	DeleteObject(hHoleRegion);

	MARGINS margin = { -1 };
	DwmExtendFrameIntoClientArea(MyWnd, &margin);

	ShowWindow(MyWnd, SW_SHOW);

	UpdateWindow(MyWnd);	

}
float colorNameBot[3] = { 1.00f, 1.00f, 1.00f };
//void background()
//{
//	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
//	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Once);
//
//	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.09f, 0.09f, 0.09f, 0.40f / 1.f * 2.f));
//	static const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove;
//	ImGui::Begin(xor("##background"), nullptr, flags);
//	ImGui::End();
//	ImGui::PopStyleColor();
//}



void HelpMarker(const char* desc, bool useImage, const char* imageName, float imageXSize = 0.f, float imageYSize = 0.f)
{
	ImGui::SameLine();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 2.f);
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 3.f);
	ImGui::TextDisabled(xor("[ ? ]"));

	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextUnformatted(desc);
		ImGui::Dummy(ImVec2(0.f, 5.f));
		if (useImage)
		{
			IDirect3DTexture9* additionalImage = nullptr;
			D3DXCreateTextureFromFile(p_Device, LPCWSTR(imageName), &additionalImage);
			ImGui::Image(additionalImage, ImVec2(imageXSize, imageYSize));
		}
		ImGui::EndTooltip();
	}
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.f);
}

void draw_abigsquare()
{
	float
		TextSpaceLine = 90.f,
		SpaceLineOne = 120.f,
		SpaceLineTwo = 280.f,
		SpaceLineThr = 420.f;
	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::SetNextWindowSize(ImVec2(350, 400), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(500, 100), ImGuiCond_FirstUseEver);
	ImGui::Begin(CRY_XORSTR_LIGHT("AIMBOT"), NULL, ImGuiWindowFlags_NoCollapse);
	{
		ImGui::Checkbox(xor ("Aimbot [BETA]"), &visuals::aim);
		ImGui::Combo(xor ("Aim Key"), &visuals::aimkey, keyItems, IM_ARRAYSIZE(keyItems));
		ImGui::SliderFloat(xor ("Fov"), &visuals::AimbotFOV, 1.0f, 40.0f);
		ImGui::SliderFloat(xor ("Smooth"), &visuals::Smoothing, 1.0f, 10.0f);
		ImGui::Checkbox(xor ("Show FOV"), &aimbot::fovcircle);
		ImGui::Spacing();
	}
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(350, 400), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(500, 100), ImGuiCond_FirstUseEver);
	ImGui::Begin(CRY_XORSTR_LIGHT("VISUAL"), NULL, ImGuiWindowFlags_NoCollapse);
	{
			/*ImGui::Checkbox(xor ((const char*)u8"播放器ESP"), &visuals::player);*/
			ImGui::Checkbox(xor ("Player Tracers"), &visuals::tracers);
			ImGui::Checkbox(xor ("Player Box"), &visuals::box);
			ImGui::Checkbox(xor ("Show Zombie"), &visuals::simplechest);
			ImGui::Checkbox(xor ("Show Car"), &visuals::ghost);
			ImGui::Checkbox(xor ("Show Weapon"), &visuals::ornateechest);
			ImGui::Checkbox(xor ("Show Mob"), &visuals::mob);
			ImGui::Checkbox(xor ("Show Ammo"), &visuals::bear);
			ImGui::Checkbox(xor ("Show Drone"), &visuals::drone);
			ImGui::Checkbox(xor ("Show Explosive"), &visuals::Explosive);
			ImGui::Checkbox(xor ("Show Box"), &visuals::chest);
			ImGui::Text(xor ("Max Distance: ")); ImGui::SameLine(TextSpaceLine);
			ImGui::SliderFloat(xor ("##MaxDistance"), &visuals::distance, 0.f, 1000.f);
	}
	ImGui::End();
		/*	else if (MenuTab == 1)
			{
				ImGui::Checkbox(xor ("Aimbot [BETA]"), &visuals::aim);
				ImGui::Combo(xor ("Aim Key"), &visuals::aimkey, keyItems, IM_ARRAYSIZE(keyItems));
				ImGui::SliderFloat(xor("Fov"), &visuals::AimbotFOV, 1.0f, 40.0f);
				ImGui::SliderFloat(xor("Smooth"), &visuals::Smoothing, 1.0f, 10.0f);
				ImGui::Checkbox(xor ("Show FOV"), &aimbot::fovcircle);
				ImGui::Spacing();
				ImGui::Text(xor ("Max Distance: ")); ImGui::SameLine(TextSpaceLine);
				ImGui::SliderFloat(xor ("##MaxDistance"), &visuals::distanceaim, 0.f, 300.f);
			}
			*/
	ImGui::SetNextWindowSize(ImVec2(350, 400), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(500, 100), ImGuiCond_FirstUseEver);
	ImGui::Begin(CRY_XORSTR_LIGHT("MISC"), NULL, ImGuiWindowFlags_NoCollapse);
	{
	     	ImGui::Checkbox(xor ("Jump Gravity"), &visuals::gravity);
		    ImGui::Checkbox(xor ("Fov Changer"), &visuals::fov);
			if(visuals::fov)
			ImGui::SliderFloat(xor ("Fov Value"), &visuals::fovvalue, 60.f, 150.f);
	/*		ImGui::Checkbox(xor ("Instant Unlock"), &visuals::lock);*/
			ImGui::Checkbox(xor ("Speed Hack [RISK]"), &visuals::speedhackbool);
			if (visuals::speedhackbool)
				ImGui::SliderFloat(xor ("Speed"), &visuals::speedhack, 1.f, 15.f);

			/*ImGui::Checkbox(xor ("FullBright"), &visuals::fullbright);*/
			ImGui::Spacing();
			ImGui::Text(xor ("Font Size: ")); ImGui::SameLine(TextSpaceLine);
			ImGui::SliderFloat(xor ("##FontSize"), &menu::font_size, 0.f, 30.f);
	}
	ImGui::End();
}


//bool draw_abigsquare()
//{
//	//static int MenuTab = 1;
//	//static int VisualTab = 0;
//
//	static short tab = 0;
//	float
//		TextSpaceLine = 90.f,
//		SpaceLineOne = 120.f,
//		SpaceLineTwo = 280.f,
//		SpaceLineThr = 420.f;
//	ImGuiStyle* style = &ImGui::GetStyle();
//
//	ImGui::SetNextWindowSize(ImVec2(460, 600), ImGuiCond_FirstUseEver);
//
//	if (ImGui::Begin(xor ("Dark And Darker"), NULL, ImGuiWindowFlags_NoCollapse)) {
//
//		ImGui::Columns(2); // Créez deux colonnes pour organiser les boutons à gauche et les fonctions à droite
//		ImGui::SetColumnOffset(1, 120); // Définissez la largeur de la première colonne
//		ImGui::Separator();
//		static short MenuTab = 0;
//
//				if (ImGui::Button(xor("VISUAL"), ImVec2(100, 40)))
//						MenuTab = 0;
//			/*
//				if (ImGui::Button(xor("AIMBOT"), ImVec2(100, 40)))
//					MenuTab = 1;*/
//			
//				if (ImGui::Button(xor("MISC"), ImVec2(100, 40)))
//					MenuTab = 2;
//
//
//
//				ImGui::Spacing(); // Ajoutez de l'espace pour aligner avec les boutons à gauche
//				ImGui::NextColumn(); // Passez à la colonne de droite
//			if (MenuTab == 0)
//			{
//				ImGui::Checkbox(xor ("Player Esp"), &visuals::player);
//				ImGui::Checkbox(xor ("Player Tracers"), &visuals::tracers);
//				ImGui::Checkbox(xor ("Player Box"), &visuals::box);
//				ImGui::Checkbox(xor ("Player Skeleton"), &visuals::skeleton);
//				ImGui::Checkbox(xor ("Player HealthBar"), &visuals::healthbar);
//				ImGui::Checkbox(xor ("Simple Chest"), &visuals::simplechest);
//				ImGui::Checkbox(xor ("Ornate Chest"), &visuals::ornateechest);
//				ImGui::Checkbox(xor ("Gold Chest"), &visuals::goldchest);
//				ImGui::Checkbox(xor ("Death Skull"), &visuals::skillcheck);
//				ImGui::Checkbox(xor ("Trap"), &visuals::trap);
//				ImGui::Checkbox(xor ("Mummy"), &visuals::mummy);
//				ImGui::Checkbox(xor ("Giant"), &visuals::giant);
//				ImGui::Checkbox(xor ("Zombie"), &visuals::zombie);
//				ImGui::Checkbox(xor ("Ghost King"), &visuals::ghost);
//				ImGui::Checkbox(xor ("Demon Dog"), &visuals::demon);
//				ImGui::Checkbox(xor ("Goblin"), &visuals::goblin);
//				ImGui::Checkbox(xor ("Item"), &visuals::item);
//				ImGui::Text(xor ("Max Distance: ")); ImGui::SameLine(TextSpaceLine);
//				ImGui::SliderFloat(xor ("##MaxDistance"), &visuals::distance, 0.f, 300.f);
//
//
//			}
//		/*	else if (MenuTab == 1)
//			{
//				ImGui::Checkbox(xor ("Aimbot [BETA]"), &visuals::aim);
//				ImGui::Combo(xor ("Aim Key"), &visuals::aimkey, keyItems, IM_ARRAYSIZE(keyItems));
//				ImGui::SliderFloat(xor("Fov"), &visuals::AimbotFOV, 1.0f, 40.0f);
//				ImGui::SliderFloat(xor("Smooth"), &visuals::Smoothing, 1.0f, 10.0f);
//				ImGui::Checkbox(xor ("Show FOV"), &aimbot::fovcircle);
//				ImGui::Spacing();
//				ImGui::Text(xor ("Max Distance: ")); ImGui::SameLine(TextSpaceLine);
//				ImGui::SliderFloat(xor ("##MaxDistance"), &visuals::distanceaim, 0.f, 300.f);
//			}
//			*/
//			else if (MenuTab == 2)
//			{
//				ImGui::Checkbox(xor ("FullBright"), &visuals::fullbright);
//				ImGui::Spacing();
//				ImGui::Text(xor ("Font Size: ")); ImGui::SameLine(TextSpaceLine);
//				ImGui::SliderFloat(xor ("##FontSize"), &menu::font_size, 0.f, 30.f);
//
//		}
//		ImGui::End();
//	}
//	return true;
//}

void shortcurts()
{
	if (GetAsyncKeyState(VK_INSERT))
	{
		if (menu_key == false)
		{
			menu_key = true;
		}
		else if (menu_key == true)
		{
			menu_key = false;
		}
		Sleep(200);
	}
}

void render() {
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	shortcurts();

	if (menu_key)
	{
		/*background();*/
		draw_abigsquare();
		ImGui::GetIO().MouseDrawCursor = 1;
	}
	else {
		ImGui::GetIO().MouseDrawCursor = 0;
	}

	if (aimbot::fovcircle && !Off)
	{
		float radiusx = visuals::AimbotFOV * (ScreenCenterX / 100);
		float radiusy = visuals::AimbotFOV * (ScreenCenterY / 100);

		float calcradius = (radiusx + radiusy) / 2;
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), calcradius, 0xFFFFFFFF, 25);
	}

	ESP();
	//AIM();

	ImGui::EndFrame();
	p_Device->SetRenderState(D3DRS_ZENABLE, false);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	p_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	if (p_Device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		p_Device->EndScene();
	}
	HRESULT result = p_Device->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		p_Device->Reset(&p_Params);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

WPARAM MainLoop()
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, MyWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();
		if (GetAsyncKeyState(0x23) & 1)
			exit(8);

		if (hwnd_active == GameWnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);

			SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			

		}
		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(GameWnd, &rc);
		ClientToScreen(GameWnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = GameWnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			p_Params.BackBufferWidth = Width;
			p_Params.BackBufferHeight = Height;
			SetWindowPos(MyWnd, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}
		render();
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	CleanuoD3D();
	DestroyWindow(MyWnd);

	return Message.wParam;
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message)
	{
	case WM_DESTROY:
		CleanuoD3D();
		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (p_Device != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			p_Params.BackBufferWidth = LOWORD(lParam);
			p_Params.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = p_Device->Reset(&p_Params);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}
void CleanuoD3D()
{
	if (p_Device != NULL)
	{
		p_Device->EndScene();
		p_Device->Release();
		p_Device = NULL; // Set the pointer to NULL after releasing
	}

	if (p_Object != NULL)
	{
		p_Object->Release();
		p_Object = NULL; // Set the pointer to NULL after releasing
	}
}
int isTopwin()
{
	HWND hWnd = GetForegroundWindow();
	if (hWnd == GameWnd)
		return TopWindowGame;
	if (hWnd == MyWnd)
		return TopWindowMvoe;

	return 0;
}
void SetWindowToTarget()
{
	while (true)
	{
		GameWnd = FindWindowW(TEXT("UnrealWindow"), NULL);
		if (GameWnd)
		{
			ZeroMemory(&GameRect, sizeof(GameRect));
			GetWindowRect(GameWnd, &GameRect);
			Width = GameRect.right - GameRect.left;
			Height = GameRect.bottom - GameRect.top;
			DWORD dwStyle = GetWindowLong(GameWnd, GWL_STYLE);
			if (dwStyle & WS_BORDER)
			{
				GameRect.top += 32;
				Height -= 39;
			}
			ScreenCenterX = Width / 2;
			ScreenCenterY = Height / 2;
			MoveWindow(MyWnd, GameRect.left, GameRect.top, Width, Height, true);

		}
	}
}