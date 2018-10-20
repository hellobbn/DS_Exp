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


pList NewListNode(void);        // Make a new node for the polyList
void MakePoly(pList);           // Make a new polynomial
void ShowList(pList, int);           // Display all polynomials
pPoly AddPoly(pPoly, pPoly);       // Add two polynomials
pPoly SubPoly(pPoly, pPoly);       // Sub two polynomials
double SolvePoly(pList);      // Solve the polynomial
void DelPoly(pList);            // Delete the whole polynomial
void EmptyPoly(pList);           // Make one polynomial empty
void ChangePoly(pList);          // Make change to one node of one polynomial

/* Basic Definition of the data structure of a polynomial*/
struct polyNode {
    double coff;
    int freq;
    struct polyNode* next;
};

/* Basic Definition of the data structure of a list*/
struct polyList {
    poly head;
    struct polyList* next;
};
#endif // POLY_CAL
