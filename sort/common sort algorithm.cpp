#include <iostream>
#include <stdlib.h>//rand函数需要
using namespace std;
#define N 15 //随机生成个数
#define MAXNUM 100 //随机数生成的范围

//插入排序
//size_t是std命名空间下的 unsigned int
template <typename T>
void Insertion_Sorting(T *arrayT, size_t length)
{
    for (unsigned int i = 1; i < length; i++)
    {
        int j = i - 1;//有序数组的最后一个元素
        T key = arrayT[i];//待排序元素
        while (j >= 0 && arrayT[j] > key)//保证不越界
        {
            arrayT[j + 1] = arrayT[j];//如果小于则大数向后移动
            j--;//因为j-- 所以循环结束不满足条件的时候  j可能<0 或者 arrayT[j] < key
        }
        arrayT[j + 1] = key; //这里需要+1 原因是while 里面的j--
    }
}
//冒泡排序
template <typename T>
void Bubble_Sort(T *arrayT, size_t length)
{
    for (unsigned int i = 0; i != length - 1; i++)
    {
        for (unsigned int j = 0; j + i != length - 1; j++)
        {
            if (arrayT[j] > arrayT[j + 1])//如果大于后面的数就交换位置，否则从后一个数接着比较
            {
                T temp = arrayT[j];
                arrayT[j] = arrayT[j + 1];
                arrayT[j + 1] = temp;
            }
        }
    }
}
//选择排序
template <typename T>
void Selection_Sort(T *arrayT, size_t length)
{
    for (unsigned int i = 0; i < length; i++)
    {
        int min = i;
        for ( unsigned int j = i + 1; j < length; j++)
        {
            if (arrayT[min] > arrayT[j])
            {
                min = j;//记录最小值
            }
        }
        T temp = arrayT[i];
        arrayT[i] = arrayT[min];
        arrayT[min] = temp;
    }
}
//归并排序
template <typename T>
void Merge(T *sourceArray, T *temp, int Start_Index, int Mid_Index, int End_Index)
{
    int i = Start_Index, j = Mid_Index + 1, k = Start_Index;
    while (i != Mid_Index + 1 && j != End_Index + 1)//数组 前半部分和后半部分合并
    {
        if (sourceArray[i] > sourceArray[j])
        {
            temp[k++] = sourceArray[j++];
        }
        else
        {
            temp[k++] = sourceArray[i++];
        }
    }
    while (i != Mid_Index + 1)//剩余的元素
    {
        temp[k++] = sourceArray[i++];
    }
    while (j != End_Index + 1)//剩余的元素
    {
        temp[k++] = sourceArray[j++];
    }
    for (int i = Start_Index; i != End_Index + 1; i++)//拷贝回去
    {
        sourceArray[i] = temp[i];
    }
}

template <typename T>
void Merge_Sort(T *sourceArray, T *temp, int Start_Index, int End_Index)
{
    if (Start_Index < End_Index)
    {
        int Mid_Index = (Start_Index + End_Index) / 2;
        Merge_Sort(sourceArray, temp, Start_Index, Mid_Index);//尾巴一直除以2
        Merge_Sort(sourceArray, temp, Mid_Index + 1, End_Index);//头一直除以2
        Merge(sourceArray, temp, Start_Index, Mid_Index, End_Index);
    }
}
//快速排序
template <typename T>
void Quick_Sort(T *arrayT, int Start_Index, int End_Index)
{
    if (Start_Index < End_Index)//注意这里是小于！！！！！！！
    {
        int first = Start_Index;//左边界
        int last = End_Index;//右边界
        T key = arrayT[first];//枢轴值
        while (first < last)//左右边界  相遇的地方
        {
            while (first < last && arrayT[last] >= key)//从右边找比枢轴值所小的下标
            {
                last--;
            }
            arrayT[first] = arrayT[last];//将小值放在小位置
            while (first < last && arrayT[first] <= key)//从左边选择比枢轴值大的下标
            {
                first++;
            }
            arrayT[last] = arrayT[first];//将大值放在大位置
        }
        arrayT[first] = key;//枢轴值的位置
        Quick_Sort(arrayT, Start_Index, first - 1);//左边再排序
        Quick_Sort(arrayT, first + 1, End_Index);//右边再排序
    }
}
template <typename T>
void displayArray(T &myArray)
{
    for (auto m :myArray)
    {
        cout<<m<<"  ";
    }
}
int main()
{
    //初始化
    int myArray_Isert[N];
    int myArray_Bubble[N];
    int myArray_select[N];
    int myArray_merge[N];
    int myArray_quick[N];
    int myArray_temp[N];
    int temp=0;
    int sign=1;
    for(int i=0; i<N; ++i)
    {
        temp= rand()%MAXNUM;
        sign=(i%2==0)?1:-1;
        myArray_Isert[i]=temp*sign;
        myArray_Bubble[i]=temp*sign;
        myArray_select[i]=temp*sign;
        myArray_merge[i]=temp*sign;
        myArray_quick[i]=temp*sign;
        myArray_temp[i]=temp*sign;
    }
    //输出初始化结果
    cout<<"待排序随机数组"<<endl;
    displayArray(myArray_Isert);
    cout<<endl;
    //插入排序
    cout<<"插入排序"<<endl;
    Insertion_Sorting(myArray_Isert,N);
    displayArray(myArray_Isert);
    cout<<endl;
    //冒泡排序
    cout<<"冒泡排序"<<endl;
    Bubble_Sort(myArray_Bubble,N);
    displayArray(myArray_Bubble);
    cout<<endl;
    //选择排序
    cout<<"选择排序"<<endl;
    Selection_Sort(myArray_select,N);
    displayArray(myArray_select);
    cout<<endl;
    //归并排序
    cout<<"归并排序"<<endl;
    Merge_Sort(myArray_merge,myArray_temp,0,N-1);
    displayArray(myArray_merge);
    cout<<endl;
    //快速排序
    cout<<"快速排序"<<endl;
    Quick_Sort(myArray_quick,0,N-1);
    displayArray(myArray_quick);
    cout<<endl;
    return 0;
}
