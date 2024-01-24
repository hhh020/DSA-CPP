// exercise 5.3
#include <iostream>

using std::cerr;
using std::cout;

template<class T>
void changeLength2D(T **&a, int oldRowLength, int oldColLength,
                           int newRowLength,int newColLength)
{
    if (newColLength < 0 || newRowLength < 0)
        cerr << "new Col and Row length must be > 0\n";
    
    T** temp = new T*[newRowLength];        // 创建行指针数组
    for (int i = 0; i < newRowLength; i++)  // 创建列指针数组
        temp[i] = new T[newColLength];
    
    // 深拷贝
    int sum = 0;
    for (int i = 0; i < newRowLength; i++)
    {
        for (int j = 0; j < newColLength; j++)
        {
            temp[i][j] = a[sum/oldColLength][sum%oldColLength];
            sum++;
        }
    }

    for (int i = 0; i < oldRowLength; i++)  // 删除每行的列数组
        delete[] a[i];
    
    delete[] a;                             // 删除行指针数组
    a = temp;
}

template<class T>
void print2DArray(T **a, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            cout << a[i][j] << " ";
        cout << '\n';
    }
}

void test3()
{
    int **arr = new int*[3];
    for (int i = 0; i < 3; i++)
        arr[i] = new int[4];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            arr[i][j] = i * 4 + j;

    cout << "old array:\n";
    print2DArray(arr,3,4);
    changeLength2D(arr,3,4,4,3);
    cout << "new array:\n";
    print2DArray(arr,4,3);
}