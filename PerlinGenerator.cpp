#include "PerlinGenerator.h"

#include <random>
#include <unordered_set>


void PerlinGenerator::genRandPermutation()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 256);

	std::unordered_set<int> set;
	while (set.size() < 256)
	{
		set.insert(dist(mt));
	}

	int itr = 0;
	for (int x : set)
	{
		originalPermutation[itr] = x;
		itr++;
	}
}

PerlinGenerator::PerlinGenerator(int height, int width)
{
	mapHeight = height;
	mapWidth = width;
	genRandPermutation();

	// Repeat the Permutation Array so as to avoid Buffer Overflow later on.
	for (int idx = 0; idx < 512; idx++) {
		perm[idx] = originalPermutation[idx % 256];
	}
}

float PerlinGenerator::perlinFade(float t) {
	return t * t * t * (t * (t * 6 - 15) + 10); // 6t^5 - 15t^4 + 10t^3
}

float PerlinGenerator::perlinGradientFunc(int hash, float x, float y) {
	switch (hash & 0xF)
	{
	case 0x0: return  x;						// Dot Prod with (1, 0)
	case 0x1: return  x + y;				        // Dot Prod with (1, 1)
	case 0x2: return  y;						// Dot Prod with (0, 1)
	case 0x3: return -x + y;				        // Dot Prod with (-1, 1)
	case 0x4: return -x;						// Dot Prod with (-1, 0)
	case 0x5: return -x - y;				        // Dot Prod with (-1,-1)
	case 0x6: return  -y;						// Dot Prod with (0, -1)
	case 0x7: return x - y;					        // Dot Prod with (1, -1)

	// Repeat
	case 0x8: return  x;
	case 0x9: return  x + y;
	case 0xA: return  y;
	case 0xB: return -x + y;
	case 0xC: return -x;
	case 0xD: return -x - y;
	case 0xE: return  -y;
	case 0xF: return x - y;

	default: return 0; // Never occurs
	}
}

// Linear Interpolate
float PerlinGenerator::perlinLerp(float a, float b, float x) {
	return ((1.0f - x) * a) + (x * b);
}

float PerlinGenerator::generatePerlin(float x, float y)
{
	// Determine the Integral Cell Coordinates
	int x0 = (int)x & 255;
	int y0 = (int)y & 255;

	int x1 = x0 + 1;
	int y1 = y0 + 1;

	// Determine relative distance from x0, y0
	float sx = x - (float)x0; // Value between 0.0 to 1.0
	float sy = y - (float)y0; // Value between 0.0 to 1.0

	float u = perlinFade(sx);
	float v = perlinFade(sy);

	// Hash Values for determining the Gradient Vector
	int aa, ab, ba, bb;
	aa = perm[perm[x0] + y0];
	ab = perm[perm[x0] + y1];
	ba = perm[perm[x1] + y0];
	bb = perm[perm[x1] + y1];

	float x1f, x2f, n0, n1;

	// Calc Dot Product
	n0 = perlinGradientFunc(aa, sx, sy);
	n1 = perlinGradientFunc(ba, sx - 1, sy);
	// Linear Interpolate
	x1f = perlinLerp(n0, n1, u);

	// Calc Dot Product
	n0 = perlinGradientFunc(ab, sx, sy - 1);
	n1 = perlinGradientFunc(bb, sx - 1, sy - 1);
	// Linear Interpolate
	x2f = perlinLerp(n0, n1, u);

	auto value = (perlinLerp(x1f, x2f, v) + 1) / 2;

	return value;
}

void PerlinGenerator::SetNoiseOctaves(int oct) {
	octaves = oct;
}

void PerlinGenerator::SetNoisePersistence(float pers) {
	persistence = pers;
}

void PerlinGenerator::SetAmplitude(float amp) {
	amplitude = amp;
}

float PerlinGenerator::Perlin(float x, float y) {
	float total = 0;
	float frequency = 2;
	float maxValue = 0;  // Used for normalizing result to 0.0 - 1.0

	for (int i = 0; i < octaves; i++) {
		total = total + (generatePerlin(x * frequency, y * frequency) * amplitude);

		maxValue += amplitude;

		amplitude *= persistence;
		frequency *= 2;
	}

	return total / maxValue;
}

float** PerlinGenerator::GenerateMap()
{
	float** map = new float* [mapWidth];

	for (int i = 0; i < mapWidth; i++) {
		map[i] = new float[mapHeight];
		for (int j = 0; j < mapHeight; j++) {
			map[i][j] = 0;
		}
	}

	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			float nx = ((float)i / mapWidth) + 0.5f;
			float ny = ((float)j / mapHeight) + 0.5f;
			auto value = Perlin(nx, ny);
			map[i][j] += value;
		}
	}

	return map;
}
