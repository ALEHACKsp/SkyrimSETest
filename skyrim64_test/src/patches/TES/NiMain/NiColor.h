#pragma once

#include <DirectXMath.h>

class NiColorA
{
public:
	const static NiColorA BLACK;
	const static NiColorA WHITE;

	float r;
	float g;
	float b;
	float a;

	inline NiColorA(float initR = 0.0f, float initG = 0.0f, float initB = 0.0f, float initA = 0.0f)
	{
		r = initR;
		g = initG;
		b = initB;
		a = initA;
	}

	/*
	inline NiColorA(const NiColor& Src, float A)
	{
		r = Src.r;
		g = Src.g;
		b = Src.b;
		a = A;
	}*/

	inline void Set(float R = 0.0f, float G = 0.0f, float B = 0.0f, float A = 0.0f)
	{
		// Don't know why they have a separate function for this
		r = R;
		g = G;
		b = B;
		a = A;
	}

	inline DirectX::XMVECTOR XmmVector() const
	{
		// This should only be in BSGraphics::Utility::CopyNiColorAToFloat but there's so
		// much abstraction I don't care anymore.
		return _mm_load_ps(&r);
	}
};
static_assert(sizeof(NiColorA) == 0x10);
static_assert(offsetof(NiColorA, r) == 0x0);
static_assert(offsetof(NiColorA, g) == 0x4);
static_assert(offsetof(NiColorA, b) == 0x8);
static_assert(offsetof(NiColorA, a) == 0xC);