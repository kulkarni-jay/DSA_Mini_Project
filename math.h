/***************************************************************************** 
 * Declarations for math functions.
 * Copyright (C) Jay Kulkarni
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

# ifndef __MATH_H_
# define __MATH_H_
# define M_E		2.7182818284590452354	/* e */
# define M_LOG2E	1.4426950408889634074	/* log_2 e */
# define M_LOG10E	0.43429448190325182765	/* log_10 e */
# define M_LN2		0.69314718055994530942	/* log_e 2 */
# define M_LN10		2.30258509299404568402	/* log_e 10 */
# define M_PI		3.14159265358979323846	/* pi */
# define M_PI_2		1.57079632679489661923	/* pi/2 */
# define M_PI_4		0.78539816339744830962	/* pi/4 */
# define M_1_PI		0.31830988618379067154	/* 1/pi */
# define M_2_PI		0.63661977236758134308	/* 2/pi */
# define M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
# define M_SQRT2	1.41421356237309504880	/* sqrt(2) */
# define M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */
# define isnan(x) __builtin_isnan (x)
# define isinf(x) __builtin_isinf_sign (x)
# include <float.h>
# define NAN	(__builtin_nanf (""))
# define INFINITY   (__builtin_inff())
# define isgreater(x, y)	__builtin_isgreater(x, y)
# define isless(x, y)		__builtin_isless(x, y)
# define isunordered(u, v)	__builtin_isunordered(u, v)
double acose(double x);
double asine(double x);
double atane(double x);	
double atan2e(double y, double x);
//Returns the arc tangent in radians of y/x based on the signs of both values to determine the correct quadrant.
double cose(double x);
double sine(double x);
double tane(double x);
double coshe(double x);
double sinhe(double x);
double tanhe(double x);
double expe(double x);
double frexpe(double x, int *exponent);
/*The returned value is the mantissa and the integer pointed to by exponent is the exponent. The resultant value is x = mantissa * 2 ^ exponent.*/
double ldexpe(double x, int exponent);
//Returns x multiplied by 2 raised to the power of exponent.
double loge(double x);
double log10e(double x);
double modfe(double x, double *integer);
//The returned value is the fraction component (part after the decimal), and sets integer to the integer component.
double powe(double x, double y);
double sqrte(double x);
double ceile(double x);
//Returns the smallest integer value greater than or equal to x.
double floore(double x);
//Returns the largest integer value less than or equal to x.
double fabse(double x);
double fmode(double x, double y);
//Returns the remainder of x divided by y.
# endif
