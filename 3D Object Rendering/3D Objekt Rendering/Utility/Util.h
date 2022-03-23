#pragma once
#include <math.h>
#include <cmath>
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>

using namespace std;
using namespace DirectX;

/// <summary>
/// Clamps a float value between two other values and returns it.
/// </summary>
/// <param name="value">The value that is clamped.</param>
/// <param name="min">The minimum value.</param>
/// <param name="max">The maximum value.</param>
static float Clamp(float value, float min, float max) 
{
	if (value < min) return min;
	else if (value > max) return max;
	else return value;
}

/// <summary>
/// Linearly interpolates a float value between two values and returns it.
/// </summary>
/// <param name="a">The minimum value.</param>
/// <param name="b">The maximum value.</param>
/// <param name="t">The t between 0 and 1.</param>
static float Lerp(float a, float b, float t) { return (b - a) * t + a; }

/// <summary>
/// Translates a sine from arc measure to angular measure.
/// </summary>
/// <param name="angle">The value that is being translated.</param>
static float DegSin(float angle) { return sin((angle / 180.0) * XM_PI); }

/// <summary>
/// Translates a cosine from arc measure to angular measure.
/// </summary>
/// <param name="angle">The value that is being translated.</param>
static float DegCos(float angle) { return cos((angle / 180.0) * XM_PI); }

/// <summary>
/// Adds two XMFLOAT3 vectors and returns the result.
/// </summary>
/// <param name="a">The first vector.</param>
/// <param name="b">The second vector.</param>
static XMFLOAT3 Add(XMFLOAT3 a, XMFLOAT3 b) { return { a.x + b.x, a.y + b.y, a.z + b.z };}

/// <summary>
/// Subtracts two XMFLOAT3 vectors and returns the result.
/// </summary>
/// <param name="a">The first vector.</param>
/// <param name="b">The second vector.</param>
static XMFLOAT3 Sub(XMFLOAT3 a, XMFLOAT3 b) { return { a.x - b.x, a.y - b.y, a.z - b.z };}

/// <summary>
/// Multiplies an XMFLOAT3 vector with a float value and returns the result.
/// </summary>
/// <param name="a">The vector.</param>
/// <param name="b">The float value.</param>
static XMFLOAT3 Mult(XMFLOAT3 a, float b) { return { a.x * b, a.y * b, a.z * b};}

/// <summary>
/// Returns the length of an XMFLOAT3 vector.
/// </summary>
/// <param name="v">The vector.</param>
static float Length(XMFLOAT3 v) { return sqrt((double)v.x * (double)v.x + (double)v.y * (double)v.y + (double)v.z * (double)v.z); }

/// <summary>
/// Normalizes a vector and returns it.
/// </summary>
/// <param name="v">The vector</param>
static XMFLOAT3 Normalize(XMFLOAT3 v) 
{
	if (v.x == 0 && v.y == 0 && v.z == 0) return { 0, 0, 0 };
	return Mult(v, 1.0f / Length(v));
}

/// <summary>
/// Prints a wstring into the output console.
/// </summary>
/// <param name="out">The wstring that is printed.</param>
static void Print(wstring out) 
{
	out += L"\n";
	OutputDebugString(out.c_str());
}

/// <summary>
/// Prints a string into the output console.
/// </summary>
/// <param name="out">The string that is printed.</param>
static void Print(string out)
{
	out += "\n";
	OutputDebugStringA(out.c_str());
}