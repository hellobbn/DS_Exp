
#if !defined(NODE_STACK_H)
#define NODE_STACK_H
typedef struct NodeStack nnStack;
typedef struct NodeStack* pnStack;
typedef struct NodeStack* pnStackNode;

pnStack CreatenStack(void);
void MakenEmpty(pnStack S);
void nPush(pPoly elem, pnStack S);
pPoly nShowElem(pnStack S);
pPoly nPop(pnStack S);
void MakenEmpty(pnStack S);
int IsnEmpty(pnStack S);

struct NodeStack {
    pPoly p;
    struct NodeStack* next;
};

#endif // NODE_STACK_H
