/* assistant.h
 * define functions for assistance use.
 * for more details please refer to readme.
 */

#define STR_INIT_LEN 100
#define STR_INCR_STEP 10
void flush_stdin(void);         
pNode MakeNode(void);    
pList NewListNode(void);
void ReallocStr(char** s, int len);
void InsertNode(pNode node, pPoly head);
void PrintPoly(pPoly p);
pPoly FindPoly(pList p, int num);
pNode FindNode(pPoly p, int freq);
pNode FindPrevNode(pPoly p, int freq);
int PrintNode(pNode n);
int AllowNeg(pPoly p);
void ClearScreen(void);