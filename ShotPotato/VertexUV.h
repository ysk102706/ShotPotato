#pragma once
#include "Vector2.h"
#include "Vector3.h"

class VertexUV {
public:
	float x, y, z;
	float u, v;

	VertexUV();
	VertexUV(float x, float y, float z);
	VertexUV(float x, float y, float z, float u, float v);
	VertexUV(Vector3 pos);
	VertexUV(Vector3 pos, Vector2 uv);
	VertexUV(const VertexUV& oth);

	VertexUV& operator=(const VertexUV& oth);
};