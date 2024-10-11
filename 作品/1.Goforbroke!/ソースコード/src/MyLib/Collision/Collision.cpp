#include "Collision.h"

// ƒ{ƒbƒNƒX“¯Žm
bool CCollision::CheckHitBoxToBox(VECTOR pos1, VECTOR pos2, VECTOR size1, VECTOR size2)
{
	VECTOR halfSize1 = { size1.x * 0.5f, size1.y * 0.5f, size1.z * 0.5f };
	VECTOR halfSize2 = { size2.x * 0.5f, size2.y * 0.5f, size2.z * 0.5f };

	if (pos1.x - halfSize1.x < pos2.x + halfSize2.x
		&& pos1.x + halfSize1.x > pos2.x - halfSize2.x
		&& pos1.y - halfSize1.y < pos2.y + halfSize2.y
		&& pos1.y + halfSize1.y > pos2.y - halfSize2.y
		&& pos1.z - halfSize1.z < pos2.z + halfSize2.z
		&& pos1.z + halfSize1.z > pos2.z - halfSize2.z)
	{
		return true;
	}
	return false;
}

// ‹…“¯Žm
bool CCollision::CheckHitSphereToSphere(VECTOR pos1, VECTOR pos2, float r1, float r2)
{
	VECTOR dist = VSub(pos1, pos2);
	float length = (dist.x * dist.x) + (dist.y * dist.y)
		+ (dist.z * dist.z);
	float radius = (r1 + r2) * (r1 + r2);

	if (length < radius) return true;
	else return false;
}

//‹éŒ`‚Ç‚¤‚µ
bool CCollision::IsHitRect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh)
{
	if (Bx < Ax + Aw && Bx + Bw > Ax && By + Bh > Ay && By < Ay + Ah)
	{
		return true;
	}

	return false;
}

//‰~‚Ç‚¤‚µ
bool CCollision::IsHitCircle(int Xa, int Xb, int Ya, int Yb, int Ra, int Rb)
{
	if ((Ra + Rb) * (Ra + Rb) > (Xa - Xb) * (Xa - Xb) + (Ya - Yb) * (Ya + Yb))
	{
		return true;
	}

	return false;
}


