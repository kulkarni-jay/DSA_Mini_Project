#include <stdio.h>
#include "math.h"
#include <stdlib.h>
#include <errno.h>
double sin(double x) {
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
		if(fabs(x) > M_PI_2) { /*term reduction*/
			while(fabs(x) > 2 * M_PI) {
				long double y;
				y = fmod(x, 2 * M_PI);
				x = y;
			}
		}
		int n;
		long double sum, term;
		n = 3;
		sum = x;
		term = x;
		while(fabs(term) > 0.0000000000001) {
			term = ((-1) * term * (x * x)) / (n * (n - 1));
			sum += term;
			n = n + 2;		
		}
		if(flag == 1)
			return -sum;
		return sum;
	}
}

double sinh(double x) {
	if(fabs(x) > DBL_MAX)
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
	if(fabs(sum) > DBL_MAX)	{
		errno = ERANGE;
		return INFINITY;
	}
}
double asin(double x) {
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
double cos(double x) {
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
		if(fabs(x) > M_PI_2) { /* term reduction*/
			while(fabs(x) > 2 * M_PI) {
				long double y;
				y = fmod(x, 2 * M_PI);
				x = y;
			}
		}
		double sum = 1, term = 1;
		int n = 1;
		while(fabs(term) > 0.00000000000001) {
			term = (-1) * (term * x * x) / (n * (n-1));
			sum += term;
			n = n + 2;
		}
		return sum;
	}
}
double acos(double x) {
	if(x >= -1 && x <= 1)
		return M_PI_2 - asin(x);
	else {
		errno = EDOM;
		return NAN; 
	}	 
}
double cosh(double x) {
	double sum = 1, term = 1;
	int n = 2;
	while(term > 0.00000000001) {
		term = (term * x * x) / (n * (n - 1));
		sum += term;
		n = n + 2;
	}
	return sum;
}
double tan(double x) {
	if(fmod(x, M_PI) == 0)
		return 0.;
	else if(isnan(x) == 1) {
		return NAN;
	}
	else if(isinf(x) == 1) {
		return INFINITY;
	}
	else if(fmod(fabs(x), M_PI_2) == 0) {           /* domain error */
		errno = EDOM;
		return NAN;
	}
	else if(fmod(x, M_PI_4) == 1 && fmod(fabs(x), M_PI_2) != 0)
		return 1.;
	else {
		int flag = 0;
		if(x < 0) {
			flag = 1;
			x = -x;
		}
		while(fabs(x) > M_PI) {		/* term reduction */
			long double y;
			y = fmod(x, M_PI);
			x = y;
		}
		if(flag == 1)
			return (-1)*(sin(x) / cos (x));
		return (sin(x) / cos (x));
	}
}
double tanh(double x) {
	//error cases not handled.
	return (sinh(x) / cosh(x));
}
double atan(double x) {
	int i;
	long double sum = x, term = x;
	for(i = 1; i < 100 ; i++) {
		term = pow(x, (2*i -1)) / (2*i - 1);
		if(i%2 == 0)
			sum -= term;
		else
			sum += term;	
	}
	return sum;
}
double pow(double x, double y) {
	int sign = 0;
	long term, result;
	if(x==0) 
		if(y == 0) {
			printf("Bad Input \n");
			exit(1);
		}
		else 
			return 	0.0;
	else {
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
}
double exp(double x) {
	int sign, n =1;
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
double floor(double x) {
	int i = (int)x; 
	if (i > x) 
		return (double)(--i);
	else if(i < x)
		return (double)(i);
	else
		return x;			
}
double ceil(double x) {
	int i =(int)x;
	if (i > x) 
		return (double)(i);
	else if(i < x)
		return (double)(++i);
	else
		return x;
}
double fabs(double x) {
	if(x >= 0)
		return x;
	else 
		return -x;
}
double log(double x) {
	int errno;
	if(x < 1) {
		errno = EDOM;
		//return nan;
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
double log10(double x) {
	int errno;
	long double ans;
	if(x < 1) {
		errno = EDOM;
	}
	else if(fmod(x, 10) == 0) {
		return x / 10;
	}
	else {
		ans = log(x) / M_LN10;
		return ans;
	}		
}
double fmod(double x, double y) {
}
