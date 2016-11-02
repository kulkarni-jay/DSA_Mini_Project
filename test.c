/***************************************************************************** 
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

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "math.h"

double epsilon = 0.00001;
int pass = 1, fail = 1;
int usage(int err) {
	printf("usage : ./project -h : for help\nusage : ./project inputfile : to test inputfile\n");
	return err;
}

int readline(FILE *fp, char *line, int count) {
	int i = 0, ch;
	while((i < count) && ((ch = fgetc(fp)) != '\n') && (ch != EOF))
		line[i++] = ch;
	line[i] = '\0';
	return i;	
}

int nan_inf(char *arg, char *answ) {	//to check nan and inf arguements. 
	if(strcmp(arg, "nan") == 0 || strcmp(arg, "-nan") == 0) {
		if(strcmp(answ, "nan") == 0) 
			printf("%3d.CASE PASS\n", pass++);
		else
			printf("%3d.CASE FAIL\n", fail++);
		return 1;
	}
	if(strcmp(arg, "inf") == 0 || strcmp(arg, "-inf") == 0) {
		if(strcmp(answ, "nan") == 0 || strcmp(answ, "inf") == 0)
			printf("%3d.CASE PASS\n", pass++);
		else
			printf("%3d.CASE FAIL\n", fail++);
		return 1;
	}
	return 0;
}

int less_zero(char *arg, char *answ, double val) {	//check if sqrte, loge, log10e take negative arguements.
	if(val < 0) {
		if(strcmp(answ, "nan") == 0)
			printf("%3d.CASE PASS\n", pass++);
		else 
			printf("%3d.CASE FAIL\n", fail++);
		return 1;	
	}
	return 0;
}

int dom_check(double val, char *answ) {			//domain check for asine and acose.
	if(fabse(val) > 1) {
		if(strcmp(answ, "nan") == 0)
			printf("%3d.CASE PASS\n", pass++);
		else 
			printf("%3d.CASE FAIL\n", fail++);
		return 1;	
	}
	return 0;

}

int equals(double a, double b) {
	if(fabse(a - b) < epsilon)
		return 1;
	return 0;
}

int main(int argc, char *argv[]) {
	
	if(argc < 2)
		return usage(EINVAL);
	if(strcmp(argv[1],"-h") == 0) {
		printf("HELP:\nusage : ./project inputfile\n"\
		"inputfile is the name of the file to be tested.\n"\
		"inputfile contains tab separated data.\nfirst coloumn contains name of the function.\n"\
		"second/third coloumn contains the arguement(s) to be given to the function.\n"\
		"for functions like:powe, atan2e, ldexpe ,frexpe, fmode, modfe there are 2 arguements to be given.\n"\
		"for functions requiring 2 arguements correct order of arguements must be given.\n"\
		"the third coloumn of these functions also contain arguements.\n"\
		"third/fourth coloumn contains the expected value of the function for the given arguement(s).\n"\
		"inputfile requires correct answers to arguements.\n");
		exit(0);
	}
	
	int count, flag, flag0, v, invalid = 1;
	char line[128], *arg, *answ, *arg1, *func;
	double val, val1, ans;
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL) {
		perror("fopen failed ");
		return usage(errno);
	}
	while(!feof(fp)) {
		count = readline(fp, line, 128);
		if(count == 0)
			break;
		func = strtok(line, " \t");
		if(strcmp(func, "sine") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			val = atof(arg);
			ans = atof(answ);
			if(equals(ans, sine(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "cose") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			val = atof(arg);
			ans = atof(answ);
			if(equals(ans, cose(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "tane") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			val = atof(arg);
			ans = atof(answ);
			if(fmode(val, M_PI_2) == 0 && val != 0) {
				if(strcmp(answ, "inf") == 0)
					printf("%3d.CASE PASS\n", pass++);
				else 
					printf("%3d.CASE FAIL\n", fail++);
				continue;
			}
			if(equals(ans, tane(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "asine") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			val = atof(arg);
			ans = atof(answ);
			flag0 = dom_check(val, answ);
			if(flag0 == 1)
				continue;
			if(equals(ans, asine(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "acose") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			val = atof(arg);
			flag0 = dom_check(val, answ);
			if(flag0 == 1)
				continue;
			ans = atof(answ);
			if(equals(ans, acose(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "atane") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			val = atof(arg);
			ans = atof(answ);
			if(strcmp(arg, "inf") == 0 || strcmp(arg, "-inf") == 0) {
				if(equals(ans, M_PI_2) == 1 || equals(ans, -M_PI_2) == 1)
					printf("%3d.CASE PASS\n", pass++);
				else
					printf("%3d.CASE FAIL\n", fail++);
				continue;						
			}
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;			
			if(equals(ans, atane(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "sinhe") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			val = atof(arg);
			ans = atof(answ);
			if(equals(ans, sinhe(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "coshe") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			val = atof(arg);
			ans = atof(answ);
			if(equals(ans, coshe(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "tanhe") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			val = atof(arg);
			ans = atof(answ);
			if(strcmp(arg, "inf") == 0) {
				if(equals(ans, 1.) == 1)
					printf("%3d.CASE PASS\n", pass++);
				else
					printf("%3d.CASE FAIL\n", fail++);
				continue;						
			}
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			if(equals(ans, tanhe(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "atan2e") == 0) {
			arg = strtok(NULL, " \t");
			arg1 = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			ans = atof(answ);
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			if(strcmp(arg, "inf") == 0) {
				if(strcmp(arg1, "inf") == 0) {
					if(equals(ans, M_PI_2 / 2) == 1)
						printf("%3d.CASE PASS\n", pass++);
					else 
						printf("%3d.CASE FAIL\n", fail++);
					continue;	
				}
				else {
					if(strcmp(answ, "nan") == 0)
						printf("%3d.CASE PASS\n", pass++);
					else 
						printf("%3d.CASE FAIL\n", fail++);
					continue;
				}
			}
			val = atof(arg);
			val1 = atof(arg1);
			if(equals(val, 0.0) == 1) {
				if(strcmp(answ, "nan") == 0)
					printf("%3d.CASE PASS\n", pass++);
				else
					printf("%3d.CASE FAIL\n", fail++);
				continue;
			}
			if(equals(ans, atan2e(val1, val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "powe") == 0) {
			arg = strtok(NULL, " \t");
			arg1 = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			ans = atof(answ);
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			flag0 = nan_inf(arg1, answ);
			if(flag0 == 1)
				continue;
			val = atof(arg);
			val1 = atof(arg1);
			if(equals(ans, powe(val, val1)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "expe") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			val = atof(arg);
			ans = atof(answ);
			if(equals(ans, expe(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "floore") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			val = atof(arg);
			ans = atof(answ);
			if(equals(ans, floore(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "ceile") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			val = atof(arg);
			ans = atof(answ);
			if(equals(ans, ceile(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "fabse") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			val = atof(arg);
			ans = atof(answ);
			if(equals(ans, fabse(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "loge") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			val = atof(arg);
			ans = atof(answ);
			flag0 = less_zero(arg, answ, val);
			if(flag0 == 1)
				continue;
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			if(val == 0) {
				if(strcmp(answ, "inf") == 0)
					printf("%3d.CASE PASS\n", pass++);
				else 
					printf("%3d.CASE FAIL\n", fail++);
				continue;
			}
			if(equals(ans, loge(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "log10e") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			val = atof(arg);
			ans = atof(answ);
			flag0 = less_zero(arg, answ, val);
			if(flag0 == 1)
				continue;
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			if(val == 0) {
				if(strcmp(answ, "inf") == 0)
					printf("%3d.CASE PASS\n", pass++);
				else 
					printf("%3d.CASE FAIL\n", fail++);
				continue;	
			}
			if(equals(ans, log10e(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "fmode") == 0) {
			arg = strtok(NULL, " \t");
			arg1 = strtok(NULL, " \t");			
			answ = strtok(NULL, " \t");
			val = atof(arg);
			val1 = atof(arg1);
			ans = atof(answ);
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			if(strcmp(arg1, "inf") == 0) {
				if(strcmp(arg, "inf") != 0) {
					if(equals(ans, val) == 1)
						printf("%3d.CASE PASS\n", pass++);
				else 
						printf("%3d.CASE FAIL\n", fail++);
					continue;
				}
			}
			flag = nan_inf(arg1, answ);
			if(flag == 1)
				continue;
			if(equals(val1, 0.0) == 1) {
				if(strcmp(answ, "nan") == 0) 
						printf("%3d.CASE PASS\n", pass++);
					else 
						printf("%3d.CASE FAIL\n", fail++);
					continue;
			}
			if(equals(ans, fmode(val, val1)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "sqrte") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			val = atof(arg);
			ans = atof(answ);
			flag0 = less_zero(arg, answ, val);
			if(flag0 == 1)
				continue;
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			if(equals(ans, sqrte(val)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "ldexpe") == 0) {
			arg = strtok(NULL, " \t");
			arg1 = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			val = atof(arg);
			v = atoi(arg1);
			ans = atof(answ);
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			flag0 = nan_inf(arg1, answ);
			if(flag0 == 1)
				continue;
			if(strcmp(arg1, "nan") == 0 || strcmp(arg1, "inf") == 0) {
			 	if(equals(ans, 0.0) == 1)
			 		printf("%3d.CASE PASS\n", pass++);
				else 
					printf("%3d.CASE FAIL\n", fail++);
				continue;
			}
			if(equals(ans, ldexpe(val, v)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "frexpe") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			int pt;
			val = atof(arg);
			ans = atof(answ);
			if(equals(ans, frexpe(val, &pt)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else
				printf("%3d.CASE FAIL\n", fail++);
		}
		else if(strcmp(func, "modfe") == 0) {
			arg = strtok(NULL, " \t");
			answ = strtok(NULL, " \t");
			flag = nan_inf(arg, answ);
			if(flag == 1)
				continue;
			val = atof(arg);
			ans = atof(answ);
			double ptr;
			if(equals(ans, modfe(val, &ptr)) == 1)
				printf("%3d.CASE PASS\n", pass++);
			else 
				printf("%3d.CASE FAIL\n", fail++);
		}
		else {
			printf("%3d.NOT A VALID FUNCTION NAME\n", invalid++);
		}
	}
	return 0;
}
