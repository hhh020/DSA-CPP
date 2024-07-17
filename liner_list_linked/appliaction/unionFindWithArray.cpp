/* program 6-19 */
int *equivclass, n;

void initialize(int numberOfElements)
{
    n = numberOfElements;
    equivclass = new int [n + 1];
    for (int e = 1; e <= n; e++)
        equivclass[e] = e;
}

/* 合并类classA和classB */
void unite(int classA, int classB)
{
    for (int k = 1; k <= n; k++)
        if (equivclass[k] == classB)
            equivclass[k] = classA;
}

/* 查找具有元素theElement的类 */
int find(int theElement)
{
    return equivclass[theElement];
}
