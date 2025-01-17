#include <stdio.h>
#include <stdlib.h>

#include "../src/MathGeoLib.h"
#include "../src/Math/myassert.h"
#include "TestRunner.h"

Polyhedron RandomPolyhedronContainingPoint(const vec &pt);

RANDOMIZED_TEST(PolyhedronConvexCentroid)
{
	vec pt;
	if (rng.Int(0, 20) == 0)
		pt = POINT_VEC_SCALAR(0.f);
	else
		pt = vec::RandomBox(rng, POINT_VEC_SCALAR(-SCALE), POINT_VEC_SCALAR(SCALE));
	Polyhedron p = RandomPolyhedronContainingPoint(pt);

	vec convexCentroid = p.ConvexCentroid();
	assert2(p.Contains(convexCentroid), p, convexCentroid);

	vec approximateConvexCentroid = p.ApproximateConvexCentroid();
	assert2(p.Contains(approximateConvexCentroid), p, approximateConvexCentroid);
}

// Skipped due to numerical stability reasons.
/*
UNIQUE_TEST(PolyhedronConvexCentroidCase)
{
	OBB Source, Target;
	Source.pos = POINT_VEC(79.4365463f, 9.49199295f, 80.8106842f);
	Source.r = DIR_VEC(0.699999988f, 2.f, 0.850000023f);
	Source.axis[0] = DIR_VEC(0.578298271f, -0.0776693448f, -0.812119781f).Normalized();
	Source.axis[1] = DIR_VEC(0.0360996947f, 0.996811926f, -0.0696268454f).Normalized();
	Source.axis[2] = DIR_VEC(0.823416352f, 0.00980918481f, 0.567352891f).Normalized();
	Target.pos = POINT_VEC(78.0123138f, 9.09825801f, 82.1548614f);
	Target.r = DIR_VEC(0.699999988f, 2.f, 0.850000023f);
	Target.axis[0] = DIR_VEC(-0.311279029f, 0.00630328758f, -0.950297653f).Normalized();
	Target.axis[1] = DIR_VEC(0.0378052816f, 0.999268531f, -0.00575537002f).Normalized();
	Target.axis[2] = DIR_VEC(0.954284727f, -0.0378111079f, -0.296496868f).Normalized();
	PBVolume<12> intersection = Source.ToPBVolume().SetIntersection(Target.ToPBVolume());
	Polyhedron Volume = intersection.ToPolyhedron();
	vec c = Volume.ConvexCentroid();
	assert(Volume.Contains(c));
	assert(Source.Contains(c));
	assert(Target.Contains(c));
}
*/

RANDOMIZED_TEST(Polyhedron_intersects_itself)
{
	vec pt;
	if (rng.Int(0, 20) == 0)
		pt = POINT_VEC_SCALAR(0.f);
	else
		pt = vec::RandomBox(rng, POINT_VEC_SCALAR(-SCALE), POINT_VEC_SCALAR(SCALE));
	Polyhedron p = RandomPolyhedronContainingPoint(pt);
	assert(p.Intersects(p));
}

UNIQUE_TEST(Platonic_solids_contain_zero)
{
	for(int i = 0; i < 5; ++i)
	{
		vec pt = POINT_VEC_SCALAR(0.f);
		Polyhedron p;
		switch(i)
		{
		case 0: p = Polyhedron::Tetrahedron(pt, SCALE); break;
		case 1: p = Polyhedron::Octahedron(pt, SCALE); break;
		case 2: p = Polyhedron::Hexahedron(pt, SCALE); break;
		case 3: p = Polyhedron::Icosahedron(pt, SCALE); break;
		default: p = Polyhedron::Dodecahedron(pt, SCALE); break;
		}
		assert(p.Contains(pt));
	}
}

UNIQUE_TEST(PolyhedronContainsPointCase)
{
	Polyhedron p;
	p.v.push_back(POINT_VEC(-115.40511f, -65.362495f, -102.40900f));
	p.v.push_back(POINT_VEC(-115.40511f, -65.362495f, -39.771103f));
	p.v.push_back(POINT_VEC(-115.40511f, -18.697929f, -102.40900f));
	p.v.push_back(POINT_VEC(-115.40511f, -18.697929f, -39.771103f));
	p.v.push_back(POINT_VEC(-16.392548f, -65.362495f, -102.40900f));
	p.v.push_back(POINT_VEC(-16.392548f, -65.362495f, -39.771103f));
	p.v.push_back(POINT_VEC(-16.392548f, -18.697929f, -102.40900f));
	p.v.push_back(POINT_VEC(-16.392548f, -18.697929f, -39.771103f));
	
	int i0[4] = {0,1,3,2};
	int i1[4] = {4,6,7,5};
	int i2[4] = {0,4,5,1};
	int i3[4] = {7,6,2,3};
	int i4[4] = {0,2,6,4};
	int i5[4] = {1,5,7,3};
	Polyhedron::Face f0; f0.v.insert(f0.v.end(), i0, i0+4); p.f.push_back(f0);
	Polyhedron::Face f1; f1.v.insert(f1.v.end(), i1, i1+4); p.f.push_back(f1);
	Polyhedron::Face f2; f2.v.insert(f2.v.end(), i2, i2+4); p.f.push_back(f2);
	Polyhedron::Face f3; f3.v.insert(f3.v.end(), i3, i3+4); p.f.push_back(f3);
	Polyhedron::Face f4; f4.v.insert(f4.v.end(), i4, i4+4); p.f.push_back(f4);
	Polyhedron::Face f5; f5.v.insert(f5.v.end(), i5, i5+4); p.f.push_back(f5);

	AABB a(POINT_VEC(-115.40511f, -65.362495f, -102.40900f),
		POINT_VEC(-16.392548f,-18.697929f, -39.771103f));

	assert(p.Contains(a.CenterPoint()));
}

