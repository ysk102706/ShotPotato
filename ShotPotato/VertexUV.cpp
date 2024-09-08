#include "Vertex.h"
#include "VertexUV.h"

VertexUV::VertexUV() : VertexUV(0.0f, 0.0f, 0.0f, 0.0f, 0.0f) {

}

VertexUV::VertexUV(float x, float y, float z) : VertexUV(x, y, z, 0.0f, 0.0f) {

}

VertexUV::VertexUV(float x, float y, float z, float u, float v) : x(x), y(y), z(z), u(u), v(v) {

}

VertexUV::VertexUV(Vector3 pos) : VertexUV(pos.x, pos.y, pos.z, 0.0f, 0.0f) {

}

VertexUV::VertexUV(Vector3 pos, Vector2 uv) : VertexUV(pos.x, pos.y, pos.z, uv.x, uv.y) {

}


VertexUV::VertexUV(const VertexUV& oth) : VertexUV(oth.x, oth.y, oth.z, oth.u, oth.v) {

}

VertexUV& VertexUV::operator=(const VertexUV& oth) {
	x = oth.x;
	y = oth.y;
	z = oth.z;
	u = oth.u;
	v = oth.v;
	return *this;
}