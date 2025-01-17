module;

#include "sys/platform.h"

#ifdef MACOS_X
// for FLT_MIN
#include <float.h>
#endif

export module Math;

export class idMath;

/*
===============================================================================

  Math

===============================================================================
*/

// XML: utility defines changed to constexpr and moved to bottom of file.

export constexpr auto FLOATSIGNBITSET(float f) { return ((*(const unsigned int*)&(f)) >> 31); }
export constexpr auto FLOATSIGNBITNOTSET(float  f) { return ((~(*(const unsigned int*)&(f))) >> 31); }

export constexpr auto FLOATNOTZERO(float f) { return ((*(const unsigned int*)&(f)) & ~(1 << 31)); }

export constexpr auto INTSIGNBITSET(int i) { return (((const unsigned int)i) >> 31); }
export constexpr auto INTSIGNBITNOTSET(int i) { return ((~((const unsigned int)i)) >> 31); }

export constexpr auto FLOAT_IS_NAN(float  x) { return (((*(const unsigned int*)&x) & 0x7f800000) == 0x7f800000); }
export constexpr auto FLOAT_IS_INF(float x) { return (((*(const unsigned int*)&x) & 0x7fffffff) == 0x7f800000); }
export constexpr auto FLOAT_IS_IND(float x) { return ((*(const unsigned int*)&x) == 0xffc00000); }
export constexpr auto FLOAT_IS_DENORMAL(float x) { return (((*(const unsigned int*)&x) & 0x7f800000) == 0x00000000 && ((*(const unsigned int*)&x) & 0x007fffff) != 0x00000000); }

constexpr auto IEEE_FLT_MANTISSA_BITS = 23;
constexpr auto IEEE_FLT_EXPONENT_BITS = 8;
constexpr auto IEEE_FLT_EXPONENT_BIAS = 127;
constexpr auto IEEE_FLT_SIGN_BIT = 31;

constexpr auto IEEE_DBL_MANTISSA_BITS = 52;
constexpr auto IEEE_DBL_EXPONENT_BITS = 11;
constexpr auto IEEE_DBL_EXPONENT_BIAS = 1023;
constexpr auto IEEE_DBL_SIGN_BIT = 63;

constexpr auto IEEE_DBLE_MANTISSA_BITS = 63;
constexpr auto IEEE_DBLE_EXPONENT_BITS = 15;
constexpr auto IEEE_DBLE_EXPONENT_BIAS = 0;
constexpr auto IEEE_DBLE_SIGN_BIT = 79;

export template<class T> ID_INLINE int	MaxIndex(T x, T y) { return  (x > y) ? 0 : 1; }
export template<class T> ID_INLINE int	MinIndex(T x, T y) { return (x < y) ? 0 : 1; }

export template<class T> ID_INLINE T	Max3(T x, T y, T z) { return (x > y) ? ((x > z) ? x : z) : ((y > z) ? y : z); }
export template<class T> ID_INLINE T	Min3(T x, T y, T z) { return (x < y) ? ((x < z) ? x : z) : ((y < z) ? y : z); }
export template<class T> ID_INLINE int	Max3Index(T x, T y, T z) { return (x > y) ? ((x > z) ? 0 : 2) : ((y > z) ? 1 : 2); }
export template<class T> ID_INLINE int	Min3Index(T x, T y, T z) { return (x < y) ? ((x < z) ? 0 : 2) : ((y < z) ? 1 : 2); }

export template<class T> ID_INLINE T	Sign(T f) { return (f > 0) ? 1 : ((f < 0) ? -1 : 0); }
export template<class T> ID_INLINE T	Square(T x) { return x * x; }
export template<class T> ID_INLINE T	Cube(T x) { return x * x * x; }

constexpr auto C_FLOAT_TO_INT(float x) { return (int)(x); }

class idMath {
public:

	static void					Init(void);

	static float				RSqrt(float x);			// reciprocal square root, returns huge number when x == 0.0

	static float				InvSqrt(float x);			// inverse square root with 32 bits precision, returns huge number when x == 0.0
	static float				InvSqrt16(float x);		// inverse square root with 16 bits precision, returns huge number when x == 0.0
	static double				InvSqrt64(float x);		// inverse square root with 64 bits precision, returns huge number when x == 0.0

	static float				Sqrt(float x);			// square root with 32 bits precision
	static float				Sqrt16(float x);			// square root with 16 bits precision
	static double				Sqrt64(float x);			// square root with 64 bits precision

	static float				Sin(float a);				// sine with 32 bits precision
	static float				Sin16(float a);			// sine with 16 bits precision, maximum absolute error is 2.3082e-09
	static double				Sin64(float a);			// sine with 64 bits precision

	static float				Cos(float a);				// cosine with 32 bits precision
	static float				Cos16(float a);			// cosine with 16 bits precision, maximum absolute error is 2.3082e-09
	static double				Cos64(float a);			// cosine with 64 bits precision

	static void					SinCos(float a, float& s, float& c);		// sine and cosine with 32 bits precision
	static void					SinCos16(float a, float& s, float& c);	// sine and cosine with 16 bits precision
	static void					SinCos64(float a, double& s, double& c);	// sine and cosine with 64 bits precision

	static float				Tan(float a);				// tangent with 32 bits precision
	static float				Tan16(float a);			// tangent with 16 bits precision, maximum absolute error is 1.8897e-08
	static double				Tan64(float a);			// tangent with 64 bits precision

	static float				ASin(float a);			// arc sine with 32 bits precision, input is clamped to [-1, 1] to avoid a silent NaN
	static float				ASin16(float a);			// arc sine with 16 bits precision, maximum absolute error is 6.7626e-05
	static double				ASin64(float a);			// arc sine with 64 bits precision

	static float				ACos(float a);			// arc cosine with 32 bits precision, input is clamped to [-1, 1] to avoid a silent NaN
	static float				ACos16(float a);			// arc cosine with 16 bits precision, maximum absolute error is 6.7626e-05
	static double				ACos64(float a);			// arc cosine with 64 bits precision

	static float				ATan(float a);			// arc tangent with 32 bits precision
	static float				ATan16(float a);			// arc tangent with 16 bits precision, maximum absolute error is 1.3593e-08
	static double				ATan64(float a);			// arc tangent with 64 bits precision

	static float				ATan(float y, float x);	// arc tangent with 32 bits precision
	static float				ATan16(float y, float x);	// arc tangent with 16 bits precision, maximum absolute error is 1.3593e-08
	static double				ATan64(float y, float x);	// arc tangent with 64 bits precision

	static float				Pow(float x, float y);	// x raised to the power y with 32 bits precision
	static float				Pow16(float x, float y);	// x raised to the power y with 16 bits precision
	static double				Pow64(float x, float y);	// x raised to the power y with 64 bits precision

	static float				Exp(float f);				// e raised to the power f with 32 bits precision
	static float				Exp16(float f);			// e raised to the power f with 16 bits precision
	static double				Exp64(float f);			// e raised to the power f with 64 bits precision

	static float				Log(float f);				// natural logarithm with 32 bits precision
	static float				Log16(float f);			// natural logarithm with 16 bits precision
	static double				Log64(float f);			// natural logarithm with 64 bits precision

	static int					IPow(int x, int y);		// integral x raised to the power y
	static int					ILog2(float f);			// integral base-2 logarithm of the floating point value
	static int					ILog2(int i);				// integral base-2 logarithm of the integer value

	static int					BitsForFloat(float f);	// minumum number of bits required to represent ceil( f )
	static int					BitsForInteger(int i);	// minumum number of bits required to represent i
	static int					MaskForFloatSign(float f);// returns 0x00000000 if x >= 0.0f and returns 0xFFFFFFFF if x <= -0.0f
	static int					MaskForIntegerSign(int i);// returns 0x00000000 if x >= 0 and returns 0xFFFFFFFF if x < 0
	static int					FloorPowerOfTwo(int x);	// round x down to the nearest power of 2
	static int					CeilPowerOfTwo(int x);	// round x up to the nearest power of 2
	static bool					IsPowerOfTwo(int x);		// returns true if x is a power of 2
	static int					BitCount(int x);			// returns the number of 1 bits in x
	static int					BitReverse(int x);		// returns the bit reverse of x

	static int					Abs(int x);				// returns the absolute value of the integer value (for reference only)
	static float				Fabs(float f);			// returns the absolute value of the floating point value
	static float				Floor(float f);			// returns the largest integer that is less than or equal to the given value
	static float				Ceil(float f);			// returns the smallest integer that is greater than or equal to the given value
	static float				Rint(float f);			// returns the nearest integer
	static int					Ftoi(float f);			// float to int conversion
	static constexpr int		FtoiFast(float f);		// fast float to int conversion but uses current FPU round mode (default round nearest)
	static unsigned int			Ftol(float f);			// float to int conversion
	static unsigned int			FtolFast(float);			// fast float to int conversion but uses current FPU round mode (default round nearest)

	static signed char			ClampChar(int i);
	static signed short			ClampShort(int i);
	static int					ClampInt(int min, int max, int value);
	static float				ClampFloat(float min, float max, float value);

	static float				AngleNormalize360(float angle);
	static float				AngleNormalize180(float angle);
	static float				AngleDelta(float angle1, float angle2);

	static int					FloatToBits(float f, int exponentBits, int mantissaBits);
	static float				BitsToFloat(int i, int exponentBits, int mantissaBits);

	static int					FloatHash(const float* array, const int numFloats);

	static const float			PI;							// pi
	static const float			TWO_PI;						// pi * 2
	static const float			HALF_PI;					// pi / 2
	static const float			ONEFOURTH_PI;				// pi / 4
	static const float			E;							// e
	static const float			SQRT_TWO;					// sqrt( 2 )
	static const float			SQRT_THREE;					// sqrt( 3 )
	static const float			SQRT_1OVER2;				// sqrt( 1 / 2 )
	static const float			SQRT_1OVER3;				// sqrt( 1 / 3 )
	static const float			M_DEG2RAD;					// degrees to radians multiplier
	static const float			M_RAD2DEG;					// radians to degrees multiplier
	static const float			M_SEC2MS;					// seconds to milliseconds multiplier
	static const float			M_MS2SEC;					// milliseconds to seconds multiplier
	static const float			INFINITUM;					// huge number which should be larger than any valid number used
	static const float			FLOAT_EPSILON;				// smallest positive number such that 1.0+FLT_EPSILON != 1.0

private:
	enum {
		LOOKUP_BITS = 8,
		EXP_POS = 23,
		EXP_BIAS = 127,
		LOOKUP_POS = (EXP_POS - LOOKUP_BITS),
		SEED_POS = (EXP_POS - 8),
		SQRT_TABLE_SIZE = (2 << LOOKUP_BITS),
		LOOKUP_MASK = (SQRT_TABLE_SIZE - 1)
	};

	union _flint {
		dword					i;
		float					f;
	};

	static dword				iSqrt[SQRT_TABLE_SIZE];
	static bool					initialized;
};

ID_INLINE float idMath::RSqrt(float x) {

	int i;
	float y, r;

	y = x * 0.5f;
	i = *reinterpret_cast<int*>(&x);
	i = 0x5f3759df - (i >> 1);
	r = *reinterpret_cast<float*>(&i);
	r = r * (1.5f - r * r * y);
	return r;
}

ID_INLINE float idMath::InvSqrt16(float x) {

	dword a = ((union _flint*)(&x))->i;
	union _flint seed;

	assert(initialized);

	double y = x * 0.5f;
	seed.i = ((((3 * EXP_BIAS - 1) - ((a >> EXP_POS) & 0xFF)) >> 1) << EXP_POS) | iSqrt[(a >> (EXP_POS - LOOKUP_BITS)) & LOOKUP_MASK];
	double r = seed.f;
	r = r * (1.5f - r * r * y);
	return (float)r;
}

ID_INLINE float idMath::InvSqrt(float x) {

	dword a = ((union _flint*)(&x))->i;
	union _flint seed;

	assert(initialized);

	double y = x * 0.5f;
	seed.i = ((((3 * EXP_BIAS - 1) - ((a >> EXP_POS) & 0xFF)) >> 1) << EXP_POS) | iSqrt[(a >> (EXP_POS - LOOKUP_BITS)) & LOOKUP_MASK];
	double r = seed.f;
	r = r * (1.5f - r * r * y);
	r = r * (1.5f - r * r * y);
	return (float)r;
}

ID_INLINE double idMath::InvSqrt64(float x) {
	dword a = ((union _flint*)(&x))->i;
	union _flint seed;

	assert(initialized);

	double y = x * 0.5f;
	seed.i = ((((3 * EXP_BIAS - 1) - ((a >> EXP_POS) & 0xFF)) >> 1) << EXP_POS) | iSqrt[(a >> (EXP_POS - LOOKUP_BITS)) & LOOKUP_MASK];
	double r = seed.f;
	r = r * (1.5f - r * r * y);
	r = r * (1.5f - r * r * y);
	r = r * (1.5f - r * r * y);
	return r;
}

ID_INLINE float idMath::Sqrt16(float x) {
	return x * InvSqrt16(x);
}

ID_INLINE float idMath::Sqrt(float x) {
	return x * InvSqrt(x);
}

ID_INLINE double idMath::Sqrt64(float x) {
	return x * InvSqrt64(x);
}

ID_INLINE float idMath::Sin(float a) {
	return sinf(a);
}

ID_INLINE float idMath::Sin16(float a) {
	float s;

	if ((a < 0.0f) || (a >= TWO_PI)) {
		a -= floorf(a / TWO_PI) * TWO_PI;
	}
#if 1
	if (a < PI) {
		if (a > HALF_PI) {
			a = PI - a;
		}
	}
	else {
		if (a > PI + HALF_PI) {
			a = a - TWO_PI;
		}
		else {
			a = PI - a;
		}
	}
#else
	a = PI - a;
	if (fabs(a) >= HALF_PI) {
		a = ((a < 0.0f) ? -PI : PI) - a;
	}
#endif
	s = a * a;
	return a * (((((-2.39e-08f * s + 2.7526e-06f) * s - 1.98409e-04f) * s + 8.3333315e-03f) * s - 1.666666664e-01f) * s + 1.0f);
}

ID_INLINE double idMath::Sin64(float a) {
	return sin(a);
}

ID_INLINE float idMath::Cos(float a) {
	return cosf(a);
}

ID_INLINE float idMath::Cos16(float a) {
	float s, d;

	if ((a < 0.0f) || (a >= TWO_PI)) {
		a -= floorf(a / TWO_PI) * TWO_PI;
	}
#if 1
	if (a < PI) {
		if (a > HALF_PI) {
			a = PI - a;
			d = -1.0f;
		}
		else {
			d = 1.0f;
		}
	}
	else {
		if (a > PI + HALF_PI) {
			a = a - TWO_PI;
			d = 1.0f;
		}
		else {
			a = PI - a;
			d = -1.0f;
		}
	}
#else
	a = PI - a;
	if (fabs(a) >= HALF_PI) {
		a = ((a < 0.0f) ? -PI : PI) - a;
		d = 1.0f;
	}
	else {
		d = -1.0f;
	}
#endif
	s = a * a;
	return d * (((((-2.605e-07f * s + 2.47609e-05f) * s - 1.3888397e-03f) * s + 4.16666418e-02f) * s - 4.999999963e-01f) * s + 1.0f);
}

ID_INLINE double idMath::Cos64(float a) {
	return cos(a);
}

ID_INLINE void idMath::SinCos(float a, float& s, float& c) {
#if defined(_MSC_VER) && defined(_M_IX86)
	_asm {
		fld		a
		fsincos
		mov		ecx, c
		mov		edx, s
		fstp	dword ptr[ecx]
		fstp	dword ptr[edx]
	}
#else
	s = sinf(a);
	c = cosf(a);
#endif
}

ID_INLINE void idMath::SinCos16(float a, float& s, float& c) {
	float t, d;

	if ((a < 0.0f) || (a >= idMath::TWO_PI)) {
		a -= floorf(a / idMath::TWO_PI) * idMath::TWO_PI;
	}
#if 1
	if (a < PI) {
		if (a > HALF_PI) {
			a = PI - a;
			d = -1.0f;
		}
		else {
			d = 1.0f;
		}
	}
	else {
		if (a > PI + HALF_PI) {
			a = a - TWO_PI;
			d = 1.0f;
		}
		else {
			a = PI - a;
			d = -1.0f;
		}
	}
#else
	a = PI - a;
	if (fabs(a) >= HALF_PI) {
		a = ((a < 0.0f) ? -PI : PI) - a;
		d = 1.0f;
	}
	else {
		d = -1.0f;
	}
#endif
	t = a * a;
	s = a * (((((-2.39e-08f * t + 2.7526e-06f) * t - 1.98409e-04f) * t + 8.3333315e-03f) * t - 1.666666664e-01f) * t + 1.0f);
	c = d * (((((-2.605e-07f * t + 2.47609e-05f) * t - 1.3888397e-03f) * t + 4.16666418e-02f) * t - 4.999999963e-01f) * t + 1.0f);
}

ID_INLINE void idMath::SinCos64(float a, double& s, double& c) {
#if defined(_MSC_VER) && defined(_M_IX86)
	_asm {
		fld		a
		fsincos
		mov		ecx, c
		mov		edx, s
		fstp	qword ptr[ecx]
		fstp	qword ptr[edx]
	}
#else
	s = sin(a);
	c = cos(a);
#endif
}

ID_INLINE float idMath::Tan(float a) {
	return tanf(a);
}

ID_INLINE float idMath::Tan16(float a) {
	float s;
	bool reciprocal;

	if ((a < 0.0f) || (a >= PI)) {
		a -= floorf(a / PI) * PI;
	}
#if 1
	if (a < HALF_PI) {
		if (a > ONEFOURTH_PI) {
			a = HALF_PI - a;
			reciprocal = true;
		}
		else {
			reciprocal = false;
		}
	}
	else {
		if (a > HALF_PI + ONEFOURTH_PI) {
			a = a - PI;
			reciprocal = false;
		}
		else {
			a = HALF_PI - a;
			reciprocal = true;
		}
	}
#else
	a = HALF_PI - a;
	if (fabs(a) >= ONEFOURTH_PI) {
		a = ((a < 0.0f) ? -HALF_PI : HALF_PI) - a;
		reciprocal = false;
	}
	else {
		reciprocal = true;
	}
#endif
	s = a * a;
	s = a * ((((((9.5168091e-03f * s + 2.900525e-03f) * s + 2.45650893e-02f) * s + 5.33740603e-02f) * s + 1.333923995e-01f) * s + 3.333314036e-01f) * s + 1.0f);
	if (reciprocal) {
		return 1.0f / s;
	}
	else {
		return s;
	}
}

ID_INLINE double idMath::Tan64(float a) {
	return tan(a);
}

ID_INLINE float idMath::ASin(float a) {
	if (a <= -1.0f) {
		return -HALF_PI;
	}
	if (a >= 1.0f) {
		return HALF_PI;
	}
	return asinf(a);
}

ID_INLINE float idMath::ASin16(float a) {
	if (FLOATSIGNBITSET(a)) {
		if (a <= -1.0f) {
			return -HALF_PI;
		}
		a = fabs(a);
		return (((-0.0187293f * a + 0.0742610f) * a - 0.2121144f) * a + 1.5707288f) * sqrt(1.0f - a) - HALF_PI;
	}
	else {
		if (a >= 1.0f) {
			return HALF_PI;
		}
		return HALF_PI - (((-0.0187293f * a + 0.0742610f) * a - 0.2121144f) * a + 1.5707288f) * sqrt(1.0f - a);
	}
}

ID_INLINE double idMath::ASin64(float a) {
	if (a <= -1.0f) {
		return -HALF_PI;
	}
	if (a >= 1.0f) {
		return HALF_PI;
	}
	return asin(a);
}

ID_INLINE float idMath::ACos(float a) {
	if (a <= -1.0f) {
		return PI;
	}
	if (a >= 1.0f) {
		return 0.0f;
	}
	return acosf(a);
}

ID_INLINE float idMath::ACos16(float a) {
	if (FLOATSIGNBITSET(a)) {
		if (a <= -1.0f) {
			return PI;
		}
		a = fabs(a);
		return PI - (((-0.0187293f * a + 0.0742610f) * a - 0.2121144f) * a + 1.5707288f) * sqrt(1.0f - a);
	}
	else {
		if (a >= 1.0f) {
			return 0.0f;
		}
		return (((-0.0187293f * a + 0.0742610f) * a - 0.2121144f) * a + 1.5707288f) * sqrt(1.0f - a);
	}
}

ID_INLINE double idMath::ACos64(float a) {
	if (a <= -1.0f) {
		return PI;
	}
	if (a >= 1.0f) {
		return 0.0f;
	}
	return acos(a);
}

ID_INLINE float idMath::ATan(float a) {
	return atanf(a);
}

ID_INLINE float idMath::ATan16(float a) {
	float s;

	if (fabs(a) > 1.0f) {
		a = 1.0f / a;
		s = a * a;
		s = -(((((((((0.0028662257f * s - 0.0161657367f) * s + 0.0429096138f) * s - 0.0752896400f)
			* s + 0.1065626393f) * s - 0.1420889944f) * s + 0.1999355085f) * s - 0.3333314528f) * s) + 1.0f) * a;
		if (FLOATSIGNBITSET(a)) {
			return s - HALF_PI;
		}
		else {
			return s + HALF_PI;
		}
	}
	else {
		s = a * a;
		return (((((((((0.0028662257f * s - 0.0161657367f) * s + 0.0429096138f) * s - 0.0752896400f)
			* s + 0.1065626393f) * s - 0.1420889944f) * s + 0.1999355085f) * s - 0.3333314528f) * s) + 1.0f) * a;
	}
}

ID_INLINE double idMath::ATan64(float a) {
	return atan(a);
}

ID_INLINE float idMath::ATan(float y, float x) {
	return atan2f(y, x);
}

ID_INLINE float idMath::ATan16(float y, float x) {
	float a, s;

	if (fabs(y) > fabs(x)) {
		a = x / y;
		s = a * a;
		s = -(((((((((0.0028662257f * s - 0.0161657367f) * s + 0.0429096138f) * s - 0.0752896400f)
			* s + 0.1065626393f) * s - 0.1420889944f) * s + 0.1999355085f) * s - 0.3333314528f) * s) + 1.0f) * a;
		if (FLOATSIGNBITSET(a)) {
			return s - HALF_PI;
		}
		else {
			return s + HALF_PI;
		}
	}
	else {
		a = y / x;
		s = a * a;
		return (((((((((0.0028662257f * s - 0.0161657367f) * s + 0.0429096138f) * s - 0.0752896400f)
			* s + 0.1065626393f) * s - 0.1420889944f) * s + 0.1999355085f) * s - 0.3333314528f) * s) + 1.0f) * a;
	}
}

ID_INLINE double idMath::ATan64(float y, float x) {
	return atan2(y, x);
}

ID_INLINE float idMath::Pow(float x, float y) {
	return powf(x, y);
}

ID_INLINE float idMath::Pow16(float x, float y) {
	return Exp16(y * Log16(x));
}

ID_INLINE double idMath::Pow64(float x, float y) {
	return pow(x, y);
}

ID_INLINE float idMath::Exp(float f) {
	return expf(f);
}

ID_INLINE float idMath::Exp16(float f) {
	int i, s, e, m, exponent;
	float x, x2, y, p, q;

	x = f * 1.44269504088896340f;		// multiply with ( 1 / log( 2 ) )
#if 1
	i = *reinterpret_cast<int*>(&x);
	s = (i >> IEEE_FLT_SIGN_BIT);
	e = ((i >> IEEE_FLT_MANTISSA_BITS) & ((1 << IEEE_FLT_EXPONENT_BITS) - 1)) - IEEE_FLT_EXPONENT_BIAS;
	m = (i & ((1 << IEEE_FLT_MANTISSA_BITS) - 1)) | (1 << IEEE_FLT_MANTISSA_BITS);
	i = ((m >> (IEEE_FLT_MANTISSA_BITS - e)) & ~(e >> 31)) ^ s;
#else
	i = (int)x;
	if (x < 0.0f) {
		i--;
	}
#endif
	exponent = (i + IEEE_FLT_EXPONENT_BIAS) << IEEE_FLT_MANTISSA_BITS;
	y = *reinterpret_cast<float*>(&exponent);
	x -= (float)i;
	if (x >= 0.5f) {
		x -= 0.5f;
		y *= 1.4142135623730950488f;	// multiply with sqrt( 2 )
	}
	x2 = x * x;
	p = x * (7.2152891511493f + x2 * 0.0576900723731f);
	q = 20.8189237930062f + x2;
	x = y * (q + p) / (q - p);
	return x;
}

ID_INLINE double idMath::Exp64(float f) {
	return exp(f);
}

ID_INLINE float idMath::Log(float f) {
	return logf(f);
}

ID_INLINE float idMath::Log16(float f) {
	int i, exponent;
	float y, y2;

	i = *reinterpret_cast<int*>(&f);
	exponent = ((i >> IEEE_FLT_MANTISSA_BITS) & ((1 << IEEE_FLT_EXPONENT_BITS) - 1)) - IEEE_FLT_EXPONENT_BIAS;
	i -= (exponent + 1) << IEEE_FLT_MANTISSA_BITS;	// get value in the range [.5, 1>
	y = *reinterpret_cast<float*>(&i);
	y *= 1.4142135623730950488f;						// multiply with sqrt( 2 )
	y = (y - 1.0f) / (y + 1.0f);
	y2 = y * y;
	y = y * (2.000000000046727f + y2 * (0.666666635059382f + y2 * (0.4000059794795f + y2 * (0.28525381498f + y2 * 0.2376245609f))));
	y += 0.693147180559945f * ((float)exponent + 0.5f);
	return y;
}

ID_INLINE double idMath::Log64(float f) {
	return log(f);
}

ID_INLINE int idMath::IPow(int x, int y) {
	int r; for (r = x; y > 1; y--) { r *= x; } return r;
}

ID_INLINE int idMath::ILog2(float f) {
	return (((*reinterpret_cast<int*>(&f)) >> IEEE_FLT_MANTISSA_BITS) & ((1 << IEEE_FLT_EXPONENT_BITS) - 1)) - IEEE_FLT_EXPONENT_BIAS;
}

ID_INLINE int idMath::ILog2(int i) {
	return ILog2((float)i);
}

ID_INLINE int idMath::BitsForFloat(float f) {
	return ILog2(f) + 1;
}

ID_INLINE int idMath::BitsForInteger(int i) {
	return ILog2((float)i) + 1;
}

ID_INLINE int idMath::MaskForFloatSign(float f) {
	return ((*reinterpret_cast<int*>(&f)) >> 31);
}

ID_INLINE int idMath::MaskForIntegerSign(int i) {
	return (i >> 31);
}

ID_INLINE int idMath::FloorPowerOfTwo(int x) {
	return CeilPowerOfTwo(x) >> 1;
}

ID_INLINE int idMath::CeilPowerOfTwo(int x) {
	x--;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x++;
	return x;
}

ID_INLINE bool idMath::IsPowerOfTwo(int x) {
	return (x & (x - 1)) == 0 && x > 0;
}

ID_INLINE int idMath::BitCount(int x) {
	x -= ((x >> 1) & 0x55555555);
	x = (((x >> 2) & 0x33333333) + (x & 0x33333333));
	x = (((x >> 4) + x) & 0x0f0f0f0f);
	x += (x >> 8);
	return ((x + (x >> 16)) & 0x0000003f);
}

ID_INLINE int idMath::BitReverse(int x) {
	x = (((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1));
	x = (((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2));
	x = (((x >> 4) & 0x0f0f0f0f) | ((x & 0x0f0f0f0f) << 4));
	x = (((x >> 8) & 0x00ff00ff) | ((x & 0x00ff00ff) << 8));
	return ((x >> 16) | (x << 16));
}

ID_INLINE int idMath::Abs(int x) {
	int y = x >> 31;
	return ((x ^ y) - y);
}

ID_INLINE float idMath::Fabs(float f) {
	int tmp = *reinterpret_cast<int*>(&f);
	tmp &= 0x7FFFFFFF;
	return *reinterpret_cast<float*>(&tmp);
}

ID_INLINE float idMath::Floor(float f) {
	return floorf(f);
}

ID_INLINE float idMath::Ceil(float f) {
	return ceilf(f);
}

ID_INLINE float idMath::Rint(float f) {
	return floorf(f + 0.5f);
}

ID_INLINE int idMath::Ftoi(float f) {
	return (int)f;
}

ID_INLINE constexpr int idMath::FtoiFast(float f) {
#if defined(_MSC_VER) && defined(_M_IX86)
	int i;
	__asm fld		f
	__asm fistp		i		// use default rouding mode (round nearest)
	return i;
#elif 0						// round chop (C/C++ standard)
	int i, s, e, m, shift;
	i = *reinterpret_cast<int*>(&f);
	s = i >> IEEE_FLT_SIGN_BIT;
	e = ((i >> IEEE_FLT_MANTISSA_BITS) & ((1 << IEEE_FLT_EXPONENT_BITS) - 1)) - IEEE_FLT_EXPONENT_BIAS;
	m = (i & ((1 << IEEE_FLT_MANTISSA_BITS) - 1)) | (1 << IEEE_FLT_MANTISSA_BITS);
	shift = e - IEEE_FLT_MANTISSA_BITS;
	return ((((m >> -shift) | (m << shift)) & ~(e >> 31)) ^ s) - s;
	//#elif defined( __i386__ )
#elif 0
	int i = 0;
	__asm__ __volatile__(
		"fld %1\n" \
		"fistp %0\n" \
		: "=m" (i) \
		: "m" (f));
	return i;
#else
	return (int)f;
#endif
}

ID_INLINE unsigned int idMath::Ftol(float f) {
	return (unsigned int)f;
}

ID_INLINE unsigned int idMath::FtolFast(float f) {
#if defined(_MSC_VER) && defined(_M_IX86)
	// FIXME: this overflows on 31bits still .. same as FtoiFast
	unsigned int i;
	__asm fld		f
	__asm fistp		i		// use default rouding mode (round nearest)
	return i;
#elif 0						// round chop (C/C++ standard)
	int i, s, e, m, shift;
	i = *reinterpret_cast<int*>(&f);
	s = i >> IEEE_FLT_SIGN_BIT;
	e = ((i >> IEEE_FLT_MANTISSA_BITS) & ((1 << IEEE_FLT_EXPONENT_BITS) - 1)) - IEEE_FLT_EXPONENT_BIAS;
	m = (i & ((1 << IEEE_FLT_MANTISSA_BITS) - 1)) | (1 << IEEE_FLT_MANTISSA_BITS);
	shift = e - IEEE_FLT_MANTISSA_BITS;
	return ((((m >> -shift) | (m << shift)) & ~(e >> 31)) ^ s) - s;
	//#elif defined( __i386__ )
#elif 0
	// for some reason, on gcc I need to make sure i == 0 before performing a fistp
	int i = 0;
	__asm__ __volatile__(
		"fld %1\n" \
		"fistp %0\n" \
		: "=m" (i) \
		: "m" (f));
	return i;
#else
	return (unsigned int)f;
#endif
}

ID_INLINE signed char idMath::ClampChar(int i) {
	if (i < -128) {
		return -128;
	}
	if (i > 127) {
		return 127;
	}
	return i;
}

ID_INLINE signed short idMath::ClampShort(int i) {
	if (i < -32768) {
		return -32768;
	}
	if (i > 32767) {
		return 32767;
	}
	return i;
}

ID_INLINE int idMath::ClampInt(int min, int max, int value) {
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}

ID_INLINE float idMath::ClampFloat(float min, float max, float value) {
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}

ID_INLINE float idMath::AngleNormalize360(float angle) {
	if ((angle >= 360.0f) || (angle < 0.0f)) {
		angle -= floor(angle / 360.0f) * 360.0f;
	}
	return angle;
}

ID_INLINE float idMath::AngleNormalize180(float angle) {
	angle = AngleNormalize360(angle);
	if (angle > 180.0f) {
		angle -= 360.0f;
	}
	return angle;
}

ID_INLINE float idMath::AngleDelta(float angle1, float angle2) {
	return AngleNormalize180(angle1 - angle2);
}

ID_INLINE int idMath::FloatHash(const float* array, const int numFloats) {
	int i, hash = 0;
	const int* ptr;

	ptr = reinterpret_cast<const int*>(array);
	for (i = 0; i < numFloats; i++) {
		hash ^= ptr[i];
	}
	return hash;
}

constexpr float	idMath::PI = 3.14159265358979323846f;
constexpr float	idMath::TWO_PI = 2.0f * PI;
constexpr float	idMath::HALF_PI = 0.5f * PI;
constexpr float	idMath::ONEFOURTH_PI = 0.25f * PI;
constexpr float idMath::E = 2.71828182845904523536f;
constexpr float idMath::SQRT_TWO = 1.41421356237309504880f;
constexpr float idMath::SQRT_THREE = 1.73205080756887729352f;
constexpr float	idMath::SQRT_1OVER2 = 0.70710678118654752440f;
constexpr float	idMath::SQRT_1OVER3 = 0.57735026918962576450f;
constexpr float	idMath::M_DEG2RAD = PI / 180.0f;
constexpr float	idMath::M_RAD2DEG = 180.0f / PI;
constexpr float	idMath::M_SEC2MS = 1000.0f;
constexpr float	idMath::M_MS2SEC = 0.001f;
constexpr float	idMath::INFINITUM = 1e30f;
constexpr float idMath::FLOAT_EPSILON = 1.192092896e-07f;

bool		idMath::initialized = false;
dword		idMath::iSqrt[SQRT_TABLE_SIZE];		// inverse square root lookup table

/*
===============
idMath::Init
===============
*/
void idMath::Init(void) {
	union _flint fi, fo;

	for (int i = 0; i < SQRT_TABLE_SIZE; i++) {
		fi.i = ((EXP_BIAS - 1) << EXP_POS) | (i << LOOKUP_POS);
		fo.f = (float)(1.0 / sqrt(fi.f));
		iSqrt[i] = ((dword)(((fo.i + (1 << (SEED_POS - 2))) >> SEED_POS) & 0xFF)) << SEED_POS;
	}

	iSqrt[SQRT_TABLE_SIZE / 2] = ((dword)(0xFF)) << (SEED_POS);

	initialized = true;
}

/*
================
idMath::FloatToBits
================
*/
int idMath::FloatToBits(float f, int exponentBits, int mantissaBits) {
	int i, sign, exponent, mantissa, value;

	assert(exponentBits >= 2 && exponentBits <= 8);
	assert(mantissaBits >= 2 && mantissaBits <= 23);

	int maxBits = (((1 << (exponentBits - 1)) - 1) << mantissaBits) | ((1 << mantissaBits) - 1);
	int minBits = (((1 << exponentBits) - 2) << mantissaBits) | 1;

	float max = BitsToFloat(maxBits, exponentBits, mantissaBits);
	float min = BitsToFloat(minBits, exponentBits, mantissaBits);

	if (f >= 0.0f) {
		if (f >= max) {
			return maxBits;
		}
		else if (f <= min) {
			return minBits;
		}
	}
	else {
		if (f <= -max) {
			return (maxBits | (1 << (exponentBits + mantissaBits)));
		}
		else if (f >= -min) {
			return (minBits | (1 << (exponentBits + mantissaBits)));
		}
	}

	exponentBits--;
	i = *reinterpret_cast<int*>(&f);
	sign = (i >> IEEE_FLT_SIGN_BIT) & 1;
	exponent = ((i >> IEEE_FLT_MANTISSA_BITS) & ((1 << IEEE_FLT_EXPONENT_BITS) - 1)) - IEEE_FLT_EXPONENT_BIAS;
	mantissa = i & ((1 << IEEE_FLT_MANTISSA_BITS) - 1);
	value = sign << (1 + exponentBits + mantissaBits);
	value |= ((INTSIGNBITSET(exponent) << exponentBits) | (abs(exponent) & ((1 << exponentBits) - 1))) << mantissaBits;
	value |= mantissa >> (IEEE_FLT_MANTISSA_BITS - mantissaBits);
	return value;
}

/*
================
idMath::BitsToFloat
================
*/
float idMath::BitsToFloat(int i, int exponentBits, int mantissaBits) {
	static int exponentSign[2] = { 1, -1 };
	int sign, exponent, mantissa, value;

	assert(exponentBits >= 2 && exponentBits <= 8);
	assert(mantissaBits >= 2 && mantissaBits <= 23);

	exponentBits--;
	sign = i >> (1 + exponentBits + mantissaBits);
	exponent = ((i >> mantissaBits) & ((1 << exponentBits) - 1)) * exponentSign[(i >> (exponentBits + mantissaBits)) & 1];
	mantissa = (i & ((1 << mantissaBits) - 1)) << (IEEE_FLT_MANTISSA_BITS - mantissaBits);
	value = sign << IEEE_FLT_SIGN_BIT | (exponent + IEEE_FLT_EXPONENT_BIAS) << IEEE_FLT_MANTISSA_BITS | mantissa;
	return *reinterpret_cast<float*>(&value);
}



export constexpr auto DEG2RAD(float a) { return (a * idMath::PI / 180.0f);}
export constexpr auto RAD2DEG(float a) { return (a * 180.0f / idMath::PI); }

export constexpr auto ANGLE2BYTE(float x) { return (idMath::FtoiFast( x * 256.0f / 360.0f) & 255); }
export constexpr auto BYTE2ANGLE(byte x) { return ( x * 360.0f / 256.0f ); }

export template<typename T> constexpr auto SEC2MS(T t) { return (idMath::FtoiFast((t) * idMath::M_SEC2MS)); }
export template<typename T> constexpr auto MS2SEC(T t) { return ((t)*idMath::M_MS2SEC); }

export template<typename T> constexpr auto ANGLE2SHORT(T x) { return (idMath::FtoiFast((x) * 65536.0f / 360.0f) & 65535); }
export template<typename T> constexpr auto SHORT2ANGLE(T x) { return ((x) * (360.0f / 65536.0f)); }