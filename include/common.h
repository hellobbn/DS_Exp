/* common.h
 * header for common functions that
 * have basically nothing to do with
 * the program.
 * we put it here so we could test if 
 * it is good in a simple way
 */

#if !defined(COMMON_H)
#define COMMON_H

double atoF(char* s, int len);
int atoI(char* s, int len);
int IsOpr(char c);
double absF(double x);
double PoW(double x, int p);
void GoodBye(int i);
int CmpOpr(char a, char b);
int TransOpr(char c);

#endif // COMMON_H

