#ifndef PLTYPES_H_
#define PLTYPES_H_

///////////////////////////////////////////////////////////////////////////////
#include <limits.h>
#include <cstring>

///////////////////////////////////////////////////////////////////////////////

// **************************************************************
// *					 Scalar types							*
// **************************************************************
typedef size_t PLIndex;
typedef int PLInteger;

typedef bool PLBOOL;
typedef float PLFLOAT;
typedef char PLCharacter;
typedef double PLDOUBLE;

// **************************************************************
// *					 Composite types						*
// **************************************************************

// ----------
// *** Ranges
typedef struct
{
	PLIndex begin;
	PLIndex count;
} PLRange;

// ------------
// *** Geometry
typedef struct
{
	double x;
	double y;
} PLPoint;

typedef struct
{
	double width;
	double height;
} PLSize;

typedef struct
{
	PLPoint position;
	PLSize size;
} PLRectange;

///////////////////////////////////////////////////////////////////////////////
// *** CONSTANTS
///////////////////////////////////////////////////////////////////////////////
const PLCharacter MAX_CHARACTER = 255;

///////////////////////////////////////////////////////////////////////////////
// *** FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
PLPoint PLCreatePoint(double inX, double inY);
PLSize PLCreateSize(double inWidth, double inHeight);
PLRectange PLCreateRectangle(double inX, double inY, double inWidth,
		double inHeight);

PLCharacter *charactersFromCharBuffer(const char *inCharBuffer,
		size_t inSize);

#endif /* PLTYPES_H_ */
