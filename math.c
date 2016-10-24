#include <stdio.h>
#include "math.h"
#include <stdlib.h>
#include <errno.h>
double sine(double x) {
	if(x == 0)
		return 0;
	else if(isnan(x) == 1) {
		return NAN;
	}
	else if(isinf(x) == 1) {
		return INFINITY;
	}
	else {
		int flag = 0;
		if(x < 0) {
			flag = 1;
			x = -x;
		}
		if(fabse(x) > M_PI_2) { /* term reduction */
			while(fabse(x) > 2 * M_PI) {
				long double y;
				y = fmode(x, 2 * M_PI);
				x = y;
			}
		}
		int n;
		long double sum, term;
		n = 3;
		sum = x;
		term = x;
		while(fabse(term) > 0.0000000000001) {
			term = ((-1) * term * (x * x)) / (n * (n - 1));
			sum += term;
			n = n + 2;		
		}
		if(flag == 1)
			return -sum;
		return sum;
	}
}

double sinhe(double x) {
	if(fabse(x) > DBL_MAX)
		return INFINITY;
	if(isnan(x) == 1 || isinf(x) == 1) {
		if(isnan(x))
			return NAN;
		if(isinf(x))
			return INFINITY;
	}
	if(x == 0)
		return 0;	
	double term = x, sum = x;
	int n = 1000000, i;
	for(i = 3; i < n;) {
		term = term * x * x / (i * (i - 1));
		sum += term;
		i = i + 2;
	}
	return sum;
	if(fabse(sum) > DBL_MAX)	{
		errno = ERANGE;
		return INFINITY;
	}
}
double asine(double x) {
	int errno, i;
	long double num, deno, term, sum;
	if(x > 1. || x < -1.) {
		errno = EDOM;
	}
	else if(x == 1)
		return M_PI_2;
	else if(x == -1)
		return -M_PI_2;	
	else {
		num = 1;
		deno = 2;
		sum = x;
		for(i = 2; i < 100 ;i++) {
			if(i == 2)
				num = num * (2*i - 1) * x * x * x;
			else
				num = num * (2*i - 1) * x * x;	
			deno = deno * (2*i);
			term = num / deno;
			sum += term;
		}
		return sum;
	}
}	
double cose(double x) {
	if(x == 0)
		return 1;
	else if(isnan(x) == 1) {
		return NAN;
	}
	else if(isinf(x) == 1) {
		return INFINITY;
	}
	else {
		int flag = 0;
		if(x < 0)
			x = -x;		/* cos(-x) = cos(x) */ 
		if(fabse(x) > M_PI_2) { /* term reduction*/
			while(fabse(x) > 2 * M_PI) {
				long double y;
				y = fmode(x, 2 * M_PI);
				x = y;
			}
		}
		double sum = 1, term = 1;
		int n = 1;
		while(fabse(term) > 0.00000000000001) {
			term = (-1) * (term * x * x) / (n * (n-1));
			sum += term;
			n = n + 2;
		}
		return sum;
	}
}
double acose(double x) {
	if(x >= -1 && x <= 1)
		return M_PI_2 - asine(x);
	else {
		errno = EDOM;
		return NAN; 
	}	 
}
double coshe(double x) {
	double sum = 1, term = 1;
	int n = 2;
	while(term > 0.00000000001) {
		term = (term * x * x) / (n * (n - 1));
		sum += term;
		n = n + 2;
	}
	return sum;
}
double tane(double x) {
	if(fmode(x, M_PI) == 0)
		return 0.;
	else if(isnan(x) == 1) {
		return NAN;
	}
	else if(isinf(x) == 1) {
		return INFINITY;
	}
	else if(fmode(fabse(x), M_PI_2) == 0) {           /* domain error */
		errno = EDOM;
		return NAN;
	}
	else if(fmode(x, M_PI_4) == 1 && fmode(fabse(x), M_PI_2) != 0)
		return 1.;
	else {
		int flag = 0;
		if(x < 0) {
			flag = 1;
			x = -x;
		}
		while(fabse(x) > M_PI) {		/* term reduction */
			long double y;
			y = fmode(x, M_PI);
			x = y;
		}
		if(flag == 1)
			return (-1)*(sine(x) / cose(x));
		return (sine(x) / cose(x));
	}
}
double tanhe(double x) {
	//error cases not handled.
	return (sinhe(x) / coshe(x));
}
double atane(double x) {
	int i;
	long double sum = x, term = x;
	for(i = 1; i < 100 ; i++) {
		term = powe(x, (2*i -1)) / (2*i - 1);
		if(i%2 == 0)
			sum -= term;
		else
			sum += term;	
	}
	return sum;
}
double atan2e(double y, double x) {
	if(x == 0)
		return NAN;
	else if(y == 0)
		return 0;
	/*
	else if(part)
	*/
	else {
		long double term = (fabse(y) / fabse(x));
		if(x > 0 && y > 0) {		/*first quadrant*/
			return atane(term);
		}
		else if(y < 0 && x > 0) {	/*second quadrant*/
			return -(atane(term));
		}
		else if(y < 0 && x < 0) {	/*third quadrant*/
			return -(M_PI - atane(term));
		}
		return	(M_PI - atane(term));			/*fourth quadrant*/
	}
}

double powe(double x, double y) {
	int sign = 0;
	long term, result;
	if(x==0) 
		if(y == 0)
			return 1;
		else 
			return 	0.0;
	else if((int)y == y){
		if(y == 0)
			return 1.0;
		else {
			if(y < 0) {
				sign = 1;
				y = -y;
			}	
			term = x; 
			result = 1;
			while(y) {
				if((int)y%2 == 1)
					result = result * term;
				y /= 2;
				term = term * term;
			}
			if(sign) 
				return (1.0)/result;	
			else 
				return (double)result;	
		}	
	}
	else {
		long double ln = loge(x), exp = y * ln;
		return (expe(exp));
	}
}
double expe(double x) {
	int sign = 0, n =1;
	double term, sum;
	if(x == 0)
		return 1;
	else {
		if(x < 0) {
			sign = 1;
			x = -x;
		}
		term = 1;
		sum = 1;
		for(int i = 1; i < 1000; i++) {
			term = (term * x) / n;
			sum += term;
			n++;
		}	
	}
	if(sign)
		return (1.0)/sum;
	else 
		return sum;	
}
double floore(double x) {
	int i = (int)x; 
	if (i > x) 
		return (double)(--i);
	else if(i < x)
		return (double)(i);
	else
		return x;			
}
double ceile(double x) {
	int i =(int)x;
	if (i > x) 
		return (double)(i);
	else if(i < x)
		return (double)(++i);
	else
		return x;
}
double fabse(double x) {
	if(x >= 0)
		return x;
	else 
		return -x;
}
double loge(double x) {
	int errno;
	if(x < 1) {
		errno = EDOM;
		return NAN;
	}
	else {	
		long int i = 1;
		long double sum = 0, term = 1;
		while(term > 0.00000000001) {
			term *= (1-(1/x));
			sum += term/i;
			i++;
		}
		return sum;
	}
}
double log10e(double x) {
	int errno;
	long double ans;
	if(x < 1) {
		errno = EDOM;
		return NAN;
	}
	else if(fmode(x, 10) == 0) {
		double count = 0;
		while(x > 1 ) {
			x = x / 10;
			count++;
		}
		return count;
	}
	else {
		ans = loge(x) / M_LN10;
		return ans;
	}		
}
double fmode(double x, double y) {
	if(y == 0)
		return NAN;
	else if(x == 0)
		return 0;
	else{
		int quo = x / y;
		return (x - quo * y); 
	}
}
double sqrte(double x) {
	if(x < 0)
		return NAN;
	else if(x == 0)
		return 0.;
	else {
		
	}
}
double ldexpe(double x, int exponent) {
	long double ans, exp;
	exp = powe(2, exponent);
	ans = x * exp;
	return ans;
}
double modfe(double x, double *integer) {
	double in = (int)x;
	*integer = in;
	return (x - *integer);
}
double frexpe(double x, int *exponent){
	if(x == 0) {
		*exponent = 0;
		return 0;
	}
	/*
	else if part
	*/
	else {
		int i = 1, sign = 0;
		if(x < 0) {
			x = -x;
			sign = 1;
		}
		if(x < 1 && x > 0) {
			i = -1;
			while(powe(2, i) > x) {
				i--;
			}
			i++;
		}
		else {
			while(x >= powe(2, i))
				i++;
		}
		*exponent = i;
		if(sign == 1)
			return -(x / powe(2, *exponent));
		return (x / powe(2, *exponent)); 
	}
}
