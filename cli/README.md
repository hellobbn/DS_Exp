# Data Structure Exp 1

稀疏一元多项式运算器

## 实验内容

- 基本功能（必做）：

1. 输入并创建多项式（按指数升序或降序排列，系数浮点型，指数整型）
2. 输出多项式，项数+每项系数指数（按指数升序或降序排列）
3. 求和：多项式相加
4. 求差：多项式相减
5. 求值
6. 销毁
7. 清空
8. 修改（①插入新的结点、②删除已有结点、③修改已有结点的系数和指数）

- 拓展功能（选做3个）：

1. 微分（N阶导数）
2. 不定积分
3. 定积分
4. 乘法和乘方
5. 除法
6. 多项式的四则运算（如 “(1+2*3)/4”）
7. 计算器的仿真界面

## 预计设计

- Init:

1. Initialize a header pointer list using `InitList()`
2. Display a list of avaliable operations
3. Call each function to achieve each operation
4. On each return, refresh the screen and that's it.

- Function 1: `MakePoly()`

1. `NewNode()` makes a new poly node
2. Reads the `coefficient` and `freq`
3. `InsertNode()` inserts new node to appropriate position.

- Function 2: `ShowList()`

1. From the first element revise each list poly using `ShowPoly()`.
2. Show Poly uses `ShowElement()` to revise and output each element.

- Function 3: `AddPoly()`
1. through `DisAndCall()` type 2
2. Sort them out and add them together.
3. Generate a new poly and asks if you want to save it.
4. If true, just append it to the list.
5. If false, free it and let it go.

- Function 4: `SubPoly()`
1. through `DisAndCall()` type 2
2. Almost the same as `AddPoly()`

- Function 5: `SolvePoly()`
1. Through `DisAndCall()` type 1
2. Need a number to solve
3. Use `sum` var and calculate each node.

- Function 6: `DelPoly()`
1. `ShowList()`, ask which to del
2. del it

- Function 7: `EmptyPoly()`
1. through `DisAndCall()` type 1
2. The same as Function 6

- Function 8: `ChangePoly()`
1. `ShowList()`, ask which to change
2. ask a way to change

    Add Node:
        Just call `MakePoly()`

    Del Node: `DelNode()`
        1. Call `FindNode()` to find the node
        2. Del it.

    Change Node: `ChNode()`
        1. Call `FindNode()` to find the node
        2. Change it.

- Additional Note:
1. I'm using a universal function to implement some options: `DisAndCall()`
2. It uses a function pointer and at first, it will use `ShowList()` to display all lists and let the user choose the poly(s) to operate on
3. The `type` parameter in the `DisAndCall()` indicates how many input is required by the function pointer.

## Function Summery

### For Operation Use

1. `MakePoly()`: Make a new poly
2. `ShowList()`: Showing a complete list
3. `AddPoly()`: Add two polys together
4. `SubPoly()`: Sub two polys
5. `SolvePoly`: A simple f(x)
6. `DelPoly()`: Delete a Poly
7. `EmptyPoly()`: Empty a existing poly
8. `ChangePoly()`: Make changes to a poly

### For assistance use

1. `NewNode()`: Generate a new node
2. `InsertNode()`: Insert a node to the position
3. `ShowPoly()`: Display a Poly
4. `ShowElement()`: Display each node in the poly
5. `FindNode()`: Find the requested node