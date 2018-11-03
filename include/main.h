/* main.h
 * Used to define main processing function.
 * For detail please refer to readme.
 */

#if !defined(POLY_CAL)
#define POLY_CAL

// #define DEBUG_MAKE_POLY
#define DEBUG

#define INIT_POLYARR_SIZE 100
#define EACH_INCR_SIZE 10
#define EXPR_INIT_LEN 10

typedef struct polyNode node;           // A node
typedef struct polyNode* pNode;         // A pointer to a node
typedef struct polyNode* poly;          // A polynomial
typedef struct polyList* pList;         // A list of polynomial
typedef struct polyList* pPoly;         // A head of a poly node


pList NewListNode(void);            // Make a new node for the polyList
void MakePoly(pList);               // Make a new polynomial
void ShowList(pList, int);          // Display all polynomials
pPoly AddPoly(pPoly, pPoly);        // Add two polynomials
pPoly SubPoly(pPoly, pPoly);        // Sub two polynomials
void SolvePoly(pList);              // Solve the polynomial
void DelPoly(pList);                // Delete the whole polynomial
void EmptyPoly(pList);              // Make one polynomial empty
void ChangePoly(pList);             // Make change to one node of one polynomial

void PolyDiF(pList p);              // Nth order differential function
void PolyInfI(pList p);             // indefinite integral
void PolyDefI(pList p);             // Definite Integral
pPoly PolyMultip(pPoly polyA, pPoly polyB);     // Multiply 2 polys
void PolyPow(pList p);
pPoly PolyDiv(pPoly polyA, pPoly polyB);        // Devide 2 polys
void PolyExpr(pList list);                      // Resolve poly expr


/* Basic Definition of the data structure of a polynomial*/
struct polyNode {
    double coff;
    int freq;
    struct polyNode* next;
};

/* Basic Definition of the data structure of a list*/
struct polyList {
    poly head;
    double coffLn;                     // Ln's Coff
    struct polyList* next;
};
#endif // POLY_CAL
