//
// * ENGINE-X
//
// + Types.h
// representations of: 2D vector with floats, 2D vector with integers and RBGA color as four bytes
//

#pragma once

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exVector2
{
	float x, y;

	//overloading += (will have to do more)
	exVector2 operator+=(const exVector2& OtherVector)
	{
		x += OtherVector.x;
		y += OtherVector.y;
		return *this;
	}

	exVector2 operator-=(const exVector2& OtherVector)
	{
		x -= OtherVector.x;
		y -= OtherVector.y;
		return *this;
	}

	bool operator>=(const exVector2& OtherVector)
	{

		if (x >= OtherVector.x) return true;
		else return false;
	}

	exVector2 operator+(const exVector2& OtherVector)
	{
		exVector2 Result;
		Result.x = x + OtherVector.x;
		Result.y = y + OtherVector.y;
		return Result;
	}

	exVector2 operator-(const exVector2& OtherVector)
	{
		exVector2 Result;
		Result.x = x - OtherVector.x;
		Result.y = y - OtherVector.y;
		return Result;
	}

	exVector2 operator*(const float& otherFloat)
	{
		exVector2 Result;
		Result.x = x * otherFloat;
		Result.y = y * otherFloat;
		return Result;
	}

	exVector2 operator-(const float& otherFloat)
	{
		exVector2 Result;
		Result.x = x - otherFloat;
		Result.y = y - otherFloat;
		return Result;
	}

	exVector2 operator+(const float& otherFloat)
	{
		exVector2 Result;
		Result.x = x + otherFloat;
		Result.y = y + otherFloat;
		return Result;
	}

};

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exIntegerVector2
{
	int x, y;
};

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exColor
{
	unsigned char mColor[4];
};
