// exercise 1.12~1.14
#include <iostream>
using namespace std;

// T1: 23/11/19
template <class T>
void make2dArray(T ** &x, int rows, int rowSizes[])   
{
    // 创建行指针
    x = new T * [rows];

    // 为每一行分配空间
    for (int i = 0; i < rows; i++)
        x[i] = new T [rowSizes[i]];
}

// T2: 23/11/19
template <typename T>                              
T * changeLength1D(T * &a, size_t oldLength, size_t newLength)
{
    size_t minLength = min(oldLength,newLength);
    T *x = new T [newLength];
    for (size_t i = 0; i < minLength; i++)
        x[i] = a[i];
    
    delete [] a;
    x[newLength - 1] = -1;      // 设一个标志位
    return x;
}

// T3: 23/11/19
// 使用程序1-11的make2dArray函数重载
template <class T>
void make2dArray(T ** &x, int rows, int cols)   
{
    x = new T * [rows];

    for (int i = 0; i < rows; i++)
        x[i] = new T [cols];
}

template <typename T>                              
T ** changeLength2D(T ** &a, size_t oldRowLength, size_t newRowLength,
                    size_t oldColLength, size_t newColLength)
{
    T **x ;
    make2dArray(x,newRowLength,newColLength); 
    size_t minColLength = min(oldColLength,newColLength);
    size_t minRowLength = min(oldRowLength,newRowLength);

    for (size_t i = 0; i < minRowLength; i++)
        for (size_t j = 0; j < minColLength; j++)
            x[i][j] = a[i][j];
    
    for (size_t i = 0; i < oldRowLength; i++)
        delete [] a[i];

    delete [] a;

    x[newRowLength-1][newColLength-1] = -1; // 设置标志位
    return x;        
}

void test1()
{
    int ** x;
    int rowSize[] = {2,3,4};
    try { make2dArray(x,3,rowSize);}
    catch (const bad_alloc& e)
    {
        cerr << "could not create x\n";
        exit(1);
    }
    for (int i = 0; i < 3; i++)                 // 查看是否分配了相应内存
    {
        for (int j = 0; j < rowSize[i]; j++)
        {
            cout << sizeof(x[i][j]) << ' ';
        }
        cout << '\n';
    }
}

/** 
 * 注意不能使用sizeof获取new分配的动态数组的长度
 * 设置标志符检查是否分配了空间
 * 这利用了new默认初始化的特性
*/
void test2()        
{
    size_t oldLength;
    size_t newLength;
    cout << "input old and new length:\n";
    cin >> oldLength;
    cin >> newLength;
    int *a = new int [oldLength];
    a[oldLength - 1] = -1;                  
    cout << a[oldLength - 1] << '\n';               
    a = changeLength1D(a,oldLength,newLength);
    cout << a[newLength - 1] << '\n';
}

void test3()        
{
    size_t newRowLength,newColLength;
    cout << "input new row and col length:\n";
    cin >> newRowLength;
    cin >> newColLength;
    
    int ** a;
    make2dArray(a,3,3);   // 创建3行3列的二维数组
    a[2][2] = -1;                  
    cout << a[2][2] << '\n';  

    a = changeLength2D(a,3,newRowLength,3,newColLength);
    cout << a[newRowLength-1][newColLength-1] << '\n';
}

int main()
{
    int i;
    cin >> i;
    switch (i)
    {
    case 1:
        test1();
        break;
    case 2:
        test2();
        break;
    case 3:
        test3();
        break;
    default:
        break;
    }
    
    return 0;
}