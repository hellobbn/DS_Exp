#if !defined(POLY_CAL)
#define POLY_CAL

typedef struct polyNode node;           // A node
typedef struct polyNode* pNode;         // A pointer to a node
typedef struct polyNode* poly;          // A polynomial
typedef struct polyList* pList;         // A list of polynomial

int DoSomeOprs(poly (*), int type);

pList InitList(void);           // Initialize a list of polys
void MakePoly(pList);           // Make a new polynomial
void ShowList(pList);           // Display all polynomials
poly AddPoly(poly, poly);       // Add two polynomials
poly SubPoly(poly, poly);       // Sub two polynomials
int SolvePoly(pList, int);      // Solve the polynomial
void DelPoly(pList);            // Delete the whole polynomial
poly EmptyPoly(poly);           // Make one polynomial empty
void ChangePoly(poly);          // Make change to one node of one polynomial

#endif // POLY_CAL
