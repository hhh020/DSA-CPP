/* program 7.1 */

#include <iostream>

using std::cout;

int main(void)
{
    int numberOfRows = 5;

    // length of each row
    int length[5] = {6, 3, 4, 2, 7};

    // 声明一个二维数组变量
    // 且分配所需要的行数
    int **irregularArray = new int* [numberOfRows];

    // 分配每一行的空间
    for (auto i = 0; i < numberOfRows; i++)
        irregularArray[i] = new int [length[i]];
    
    // set
    irregularArray[2][3] = 5;
    irregularArray[4][6] = irregularArray[2][3] + 2;
    irregularArray[1][1] = 3;

    // get
    cout << irregularArray[2][3] << '\n';
    cout << irregularArray[4][6] << '\n';
    cout << irregularArray[1][1] << '\n';
    
    return 0;
}