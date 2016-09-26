#include <stdio.h>
#include "math.h"
#include <stdlib.h>
#include <error.h>
double sin(double x) {
	if(x == 0)
		return 0;	
	int n;
	double sum, term;
	n = 3;
	sum = x;
	term = x;
	while(fabs(term) > 0.00000000000001) {
		term = ((-1) * term * (x * x)) / (n * (n - 1));
		sum += term;
		n = n + 2;		
	}
	return sum;
}
double sinh(double x) {
	/*if(fabs(x) > INT_MAX)
		return inf;*/
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
	/*if(fabs(sum) > INT_MAX)
		return inf;*/
}
double asin(double x) {
	int errno = 0, i;
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
	double sum = 1, term = 1;
	int n = 1;
	while(fabs(term) > 0.00000000000001) {
		term = (-1) * (term * x * x) / (n * (n-1));
		sum += term;
		n = n + 2;
	}
	return sum;
}
double acos(double x) {
	if(x >= -1 && x <= 1)
		return M_PI_2 - asin(x);
	else
		errno = EDOM;	 
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
	//error cases not handled.
	return (sin(x) / cos (x));
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
double power(int x, int y) {
	//error cases not handled.
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
				if(y%2 == 1)
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
	int i= (int)x; 
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
	}
	else {	
		long int n = 3, i;
		long double sum = x-1, term = 1;
		while(fabse(term) > 0.000000001) {
			term = -1 * pow((x - 1), n) / n;
			sum += term;
			n += 2;
		}
		return sum;
	}
}
double log10(double x) {
	int errno;
	if(x < 1) {
		errno = EDOM;
	}
	long double ans;
	else {
		ans = log(x) / M_LN10;
		return ans;
	}		
}	
	
	
	
	
	
	
	
	
	
	
	
	
	
