#include <iostream>
#include <stdlib.h>//rand函数需要
#include <math.h>
#include <vector>
using namespace std;
#define N 15 //随机生成个数
#define MAXNUM 100 //随机数生成的范围
/*
1. 将数的个数设为n，取奇数k=n/2，将下标差值为k的书分为一组，构成有序序列。
2. 再取k=k/2 ，将下标差值为k的书分为一组，构成有序序列。
3. 重复第二步，直到k=1执行简单插入排序。
*/
//希尔排序
template <typename T>
void Shell_Sort(T *arrayT, size_t length)
{
    int d  = length;
    while (d!=0)
    {
        d=d/2;
        for (int x = 0; x < d; x++)  //分的组数
        {
            for (int i = x + d; i < length; i += d)  //组中的元素，从第二个数开始
            {
                int j = i - d;//j为有序序列最后一位的位数
                int temp = arrayT[i];//要插入的元素
                while(j >= 0 && temp < arrayT[j])//从后往前遍历。
                {
                    arrayT[j + d] = arrayT[j];//向后移动d位
                    j -= d;
                }
                arrayT[j + d] = temp;
            }
        }
    }
}
/*
鸡尾酒排序等于是冒泡排序的轻微变形。不同的地方在于从低到高然后从高到低，
而冒泡排序则仅从低到高去比较序列里的每个元素。他可以得到比冒泡排序稍微好一点的效能，
原因是冒泡排序只从一个方向进行比对(由低到高)，每次循环只移动一个项目。
     1、依次比较相邻的两个数，将小数放在前面，大数放在后面；
     2、第一趟可得到：将最小数放到第一位。
     3、第二趟可得到：将最大的数放到最后一位。
     4、如此下去，重复以上过程，直至最终完成排序。
    鸡尾酒排序最糟或是平均所花费的次数都是O(n^2)，但如果序列在一开始已经大部分排序过的话，会接近O(n)。
    最差时间复杂度 O(n^2)
最优时间复杂度 O(n)
平均时间复杂度 O(n^2)
*/
//鸡尾酒排序--双向冒泡排序
template <typename T>
void Cocktail_Sort(T *arrayT, size_t length)
{
    int tail=length-1;
    int temp=0;
    for (int i=0; i<tail;)
    {
        for (int j=tail; j>i; --j) //第一轮，先将最小的数据排到前面
        {
            if (arrayT[j]<arrayT[j-1])
            {
                temp=arrayT[j];
                arrayT[j]=arrayT[j-1];
                arrayT[j-1]=temp;
            }
        }
        ++i;                    //原来i处数据已排好序，加1
        for (int j=i; j<tail; ++j)  //第二轮，将最大的数据排到后面
        {
            if (arrayT[j]>arrayT[j+1])
            {
                temp=arrayT[j];
                arrayT[j]=arrayT[j+1];
                arrayT[j+1]=temp;
            }
        }
        tail--;                 //原tail处数据也已排好序，将其减1
    }
}
//------------------------------堆排序
/*返回父节点*/
inline int parent(int i)
{
    return (int)floor((i - 1) / 2);
}
/*返回左孩子节点*/
inline int left(int i)
{
    return (2 * i + 1);
}
/*返回右孩子节点*/
inline int right(int i)
{
    return (2 * i + 2);
}
/*对以某一节点为根的子树做堆调整(保证最大堆性质)*/
template <typename T>
void HeapAdjust(T A[], int i, int heap_size)
{
    int l = left(i);
    int r = right(i);
    int largest;
    int temp;
    //左孩子  层间顺序调动
    if(l < heap_size && A[l] > A[i])
    {
        largest = l;
    }
    else
    {
        largest = i;
    }
    //右孩子  层内顺序调动
    if(r < heap_size && A[r] > A[largest])
    {
        largest = r;
    }
    //是否交换
    if(largest != i)
    {
        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        HeapAdjust(A, largest, heap_size);
    }
}

/*建立最大堆*/
template <typename T>
void BuildHeap(T A[],int heap_size)
{
    //倒着建堆
    for(int i = (heap_size-2)/2; i >= 0; i--)
    {
        HeapAdjust(A, i, heap_size);
    }
}
/*堆排序*/
template <typename T>
void HeapSort(T A[], int heap_size)
{
    BuildHeap(A, heap_size);
    int temp;
    //因为是大根堆，所以A[0]是堆顶元素是最大的，倒着放在最后，这样就是从小到大
    for(int i = heap_size - 1; i >= 0; i--)
    {
        temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        HeapAdjust(A, 0, i);//找到当前的最大值
    }
}
//end------------------------------堆排序
//桶排序
template <typename T>
void Bucket_Sort(T *A, int Max, int Size)
{
    int B[Max+1];//正数的桶
    int M[Max+1];//负数的桶
    int i,j,count = 0;
    //初始化
    for (int k = 0; k <= Max; ++k)
    {
        B[k] = 0;
        M[k] = 0;
    }
    //计数
    for (i = 0; i < Size; ++i)
    {
        j = A[i];
        if(j>=0)
        {
            B[j] += 1;
        }
        else
        {
            j=-j;
            M[j] += 1;
        }
    }
    //排序后的数组
    //负数
    for (i = Max; i >0; --i)
    {
        if (M[i] > 0)
        {
            for (j = 0; j < M[i]; ++j)//输出个数
            {
                A[count] = -i;
                count++;
            }
        }
    }
    //正数
    for (i = 0; i <= Max; ++i)
    {
        if (B[i] > 0)
        {
            for (j = 0; j < B[i]; ++j)
            {
                A[count] = i;
                count++;
            }
        }
    }
}
//end ----------桶排序

//基数排序
template <typename T>
void display1D(vector<T> &result)
{
    typename vector<T>::iterator iter;
    for(iter=result.begin(); iter!=result.end(); ++iter)
    {
        cout<<(*iter)<<"\t";
    }
    cout<<endl;
}
//输出内容
template <typename T>
void display2D(vector<vector<T>> &result)
{
    //使用迭代器
    typename vector<vector<T>>::iterator iterAll;
    typename vector<T>::iterator iter;
    for( iterAll=result.begin(); iterAll!=result.end(); ++iterAll)
    {
        for(iter=(*iterAll).begin(); iter!=(*iterAll).end(); ++iter)
        {
            cout<<(*iter)<<"\t";
        }
        cout<<endl;
    }
    /*   已知数组容量
        for( int i=0; i<result.size(); ++i)
        {
            for(int j=0; j<result.at(i).size(); ++j)
            {
                cout<<result.at(i).at(j)<<"\t";
            }
            cout<<endl;
        }
    */
}
//找到最大的数值
template <typename T>
int findMax(vector<T> &result)
{
    typename vector<T>::iterator iter=result.begin();
    int temp=(*iter);
    for(iter=result.begin(); iter!=result.end(); ++iter)
    {
        if(temp<(*iter))
        {
            temp=(*iter);
        }
    }
    return temp;
}
//排序的次数
int getNumberOfSort(int number,int radix)
{
    int counter=0;//初始化
    while(number/radix)
    {
        counter++;
        number/=radix;
    }
    return counter;
}
//一个二维的向量初始化
template <typename T>
void initialRadixVector(vector<vector<T>> &vectorAll,int radix)
{
    for(int i=0; i<radix; ++i)
    {
        vector<T> temp;
        vectorAll.push_back(temp);
    }
}
//源复制到目的向量中
template <typename T>
void getVector(vector<T> &dest,vector<vector<T>> &source)
{
    dest.clear();//清空源向量
    typename vector<vector<T>>::iterator iterAll;
    typename vector<T>::iterator iter;
    typename vector<T>::reverse_iterator riter;

    //遍历得到新的向量
    for( iterAll=source.begin(); iterAll!=source.end(); ++iterAll)
    {
        vector<int> temp;
        bool isMinus=false;
        for(iter=(*iterAll).begin(); iter!=(*iterAll).end(); ++iter)
        {
            if(*iter>=0)
            {
                dest.push_back(*iter);
            }
            else
            {
                isMinus=true;
                temp.push_back(*iter);
            }
        }
        if(isMinus)//负数需要倒着输出
        {
            for(riter=temp.rbegin(); riter!=temp.rend(); ++riter)
            {
                dest.insert(dest.begin(),*riter);
            }
            temp.clear();
        }
    }
}

//向量放在各个基数内
template <typename T>
void SetRadix(vector<vector<T>> &vectorAll,vector<T> &vect,int number,int radix)
{
    int location=0;//记录位置
    typename vector<vector<T>>::iterator iterAll;
    typename vector<T>::iterator iter;
    for(iter=vect.begin(); iter!=vect.end(); ++iter)
    {
        location = abs(static_cast<int>(abs(*iter))/pow(radix,number))%(radix);
        vectorAll.at(location).push_back(*iter);
    }
}
//基数排序  ---   一次排序的过程
template <typename T>
void radixSortOnce(vector<T> &vect, int number,int radix)
{
    //初始化向量
    vector<vector<T>> vectorAll;//基数排序的基
    //初始化向量表
    initialRadixVector(vectorAll,radix);
    //将向量放在各个基数内
    SetRadix(vectorAll,vect,number,radix);
    //复制到临时变量中
    getVector(vect,vectorAll);
    //显示每次排序的过程
    //display1D(vect);
    //cout<<endl;
}
//基数排序
template <typename T>
void radixSort(vector<T> &vect, int number,int radix)
{
    if(0<=number)
    {
        radixSort(vect,number-1,radix);
        radixSortOnce(vect,number,radix);
    }// end of if
}
//end  基数排序

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
    int myArray_Shell[N];
    int myArray_Cocktail[N];
    int myArray_Heap[N];
    int myArray_Bucket[N];
    vector<int> myArray_Radix;

    int temp=0;
    int sign=1;//符号
    for(int i=0; i<N; ++i)
    {
        temp= rand()%MAXNUM;
        sign=(i%2==0)?1:-1;
        myArray_Shell[i]=temp*sign;
        myArray_Cocktail[i]=temp*sign;
        myArray_Heap[i]=temp*sign;
        myArray_Bucket[i]=temp*sign;
        myArray_Radix.push_back(temp*sign);
    }
    //输出初始化结果
    cout<<"待排序随机数组"<<endl;
    displayArray(myArray_Shell);
    cout<<endl;
    //插入排序
    cout<<"希尔排序"<<endl;
    Shell_Sort(myArray_Shell,N);
    displayArray(myArray_Shell);
    cout<<endl;
    //鸡尾酒排序  双向冒泡排序
    cout<<"鸡尾酒排序"<<endl;
    Cocktail_Sort(myArray_Cocktail,N);
    displayArray(myArray_Cocktail);
    cout<<endl;
    //堆排序
    cout<<"堆排序"<<endl;
    HeapSort(myArray_Heap,N);
    displayArray(myArray_Heap);
    cout<<endl;
    //堆排序
    cout<<"桶排序"<<endl;
    Bucket_Sort(myArray_Bucket, MAXNUM, N);
    displayArray(myArray_Bucket);
    cout<<endl;
    //基数排序
    cout<<"基数排序"<<endl;
    int radix = 10;//基数
    int maxNumber = findMax(myArray_Radix);//数组中最大的元素
    int numberOfSort=getNumberOfSort(maxNumber,radix);//需要排序的次数
    //cout<<"Max value:\t"<<maxNumber<<"\nNeed:\t"<<numberOfSort<<endl;
    //cout<<"After radix sort: \n";
    //排序
    radixSort(myArray_Radix,numberOfSort,radix);
    displayArray(myArray_Radix);
    cout<<endl;

    return 0;
}
