#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <glm\gtx\projection.hpp>
#include <glm\gtx\string_cast.hpp>
#include <iostream>

using namespace std;
using namespace glm;

int main() //a b c d e f g h i j k l m n o p q r s t u v w x y z
{
	//2-4D Vectors
	vec2 a(1.0f, 0.0f);
	vec2 b(0.0f, 1.0f);
	vec3 c(1.0f, 0.0f, 0.0f);
	vec3 d(0.0f, 1.0f, 0.0f);
	vec4 ee(1.0f, 0.0f, 0.0f, 0.0f);
	vec4 f(0.0f, 0.0f, 1.0f, 0.0f);

	//Converting vectors
	vec2 g(c);
	vec2 h(ee);
	vec3 i(a, 0.0f);
	vec3 j(f);
	vec4 k(a, 0.0f, 0.0f);
	vec4 l(c, 0.0f);

	//Adding vectors
	vec2 m(a + b);
	vec2 n(a - b);
	vec3 o(c + d);
	vec3 p(c - d);
	vec4 q(ee + f);
	vec4 r(ee - f);

	//Scaling Vectors
	vec2 s(3.0f * a);
	vec2 t(5.0f * b);
	vec3 u(2.0f * c);
	vec3 v(4.0f * d);
	vec4 w(3.0f * ee);
	vec4 x(2.0f * f);

	//Length of vectors
	float aa = length(a);
	float ab = length(c);
	float ac = length(ee);

	//Normalizing vectors
	vec2 ad = normalize(a);
	vec3 ae = normalize(c);
	vec4 af = normalize(ee);

	//Dot Product
	float ba = dot(a, b);
	float bb = dot(c, d);
	float bc = dot(ee, f);

	//Vector projection
	vec2 ca = proj(a, b);
	vec3 cb = proj(c, d);
	vec4 cc = proj(ee, f);

	//Cross products
	vec3 da = cross(c, d);

	//Matrix
	mat4 fa(1.0f);
	mat4 fb(2.0f);
	mat4 fc(3.0f);

	//Matrix Addition
	mat4 fd = (fa + fb);
	mat4 fe = (fc - fa);

	//Matrix Scaling
	mat4 ff = 5.0f * fb;
	mat4 fg = fd / 3.0f;

	//Matrix Multiplication
	mat4 ga = fa * fb;
	mat4 gb = fc * fd;

	//Matrix Vector multiplication
	vec3 ha = vec3(fa * ee);

	//Translation Matrix
	mat4 aaa = translate(mat4(1.0f), vec3(1.0f, 0.0f, 1.0f));
	vec3 aba = aaa * vec4(c, 1.0f);

	//Rotation Matrices
	mat4 Rx = rotate(mat4(1.0f), (3.1415f / 2), vec3(1.0f, 0.0f, 0.0f));
	mat4 Ry = rotate(mat4(1.0f), (3.1415f / 2), vec3(0.0f, 1.0f, 0.0f));
	mat4 Rz = rotate(mat4(1.0f), (3.1415f / 2), vec3(0.0f, 0.0f, 1.0f));

	mat4 Rall = Rz * Rx * Ry;
	vec3 rotatedVector = (Rall * vec4(c, 1.0f));
	//Also able to use eularAngleYXZ function eg eulerAngleYXZ(yaw, pitch, roll);

	//Scaling matrix
	mat4 Sa = scale(mat4(1.0f), vec3(1.0f, 1.0f, 0.0f));
	vec3 ScaledVector = Sa * vec4(c, 1.0f);

	//Combining Matrices
	mat4 trans = aaa * (Rall * Sa);
	vec3 transformedVec = trans * vec4(c, 1.0f);

	//Quarternions
	quat Qa;

	quat Qx = rotate(quat(), (3.1415f / 2), vec3(1.0f, 0.0f, 0.0f));
	quat Qy = rotate(quat(), (3.1415f / 2), vec3(0.0f, 1.0f, 0.0f));
	quat Qz = rotate(quat(), (3.1415f / 2), vec3(0.0f, 0.0f, 1.0f));

	quat QAll = Qz * Qx * Qy;

	mat4 Ra = mat4_cast(QAll);
	vec3 QuatRotated = Ra * vec4(c, 1.0f);
}