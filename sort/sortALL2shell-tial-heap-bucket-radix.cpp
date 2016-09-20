#include <math.h>
#include <vector>
using namespace std;
/*
*/
template <typename T>
void Shell_Sort(T *arrayT, size_t length)
{
    int d  = length;
    while (d!=0)
    {
        d=d/2;
        {
            {
                {
                    j -= d;
                }
                arrayT[j + d] = temp;
            }
        }
    }
}
/*
*/
template <typename T>
void Cocktail_Sort(T *arrayT, size_t length)
{
    int tail=length-1;
    int temp=0;
    for (int i=0; i<tail;)
    {
        {
            if (arrayT[j]<arrayT[j-1])
            {
                temp=arrayT[j];
                arrayT[j]=arrayT[j-1];
                arrayT[j-1]=temp;
            }
        }
        {
            if (arrayT[j]>arrayT[j+1])
            {
                temp=arrayT[j];
                arrayT[j]=arrayT[j+1];
                arrayT[j+1]=temp;
            }
        }
    }
}
inline int parent(int i)
{
    return (int)floor((i - 1) / 2);
}
inline int left(int i)
{
    return (2 * i + 1);
}
inline int right(int i)
{
    return (2 * i + 2);
}
template <typename T>
void HeapAdjust(T A[], int i, int heap_size)
{
    int l = left(i);
    int r = right(i);
    int largest;
    int temp;
    if(l < heap_size && A[l] > A[i])
    {
        largest = l;
    }
    else
    {
        largest = i;
    }
    if(r < heap_size && A[r] > A[largest])
    {
        largest = r;
    }
    if(largest != i)
    {
        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        HeapAdjust(A, largest, heap_size);
    }
}

template <typename T>
void BuildHeap(T A[],int heap_size)
{
    for(int i = (heap_size-2)/2; i >= 0; i--)
    {
        HeapAdjust(A, i, heap_size);
    }
}
template <typename T>
void HeapSort(T A[], int heap_size)
{
    BuildHeap(A, heap_size);
    int temp;
    for(int i = heap_size - 1; i >= 0; i--)
    {
        temp = A[0];
        A[0] = A[i];
        A[i] = temp;
    }
}
template <typename T>
void Bucket_Sort(T *A, int Max, int Size)
{
    int i,j,count = 0;
    for (int k = 0; k <= Max; ++k)
    {
        B[k] = 0;
        M[k] = 0;
    }
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
    for (i = Max; i >0; --i)
    {
        if (M[i] > 0)
        {
            {
                A[count] = -i;
                count++;
            }
        }
    }
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
template <typename T>
void display2D(vector<vector<T>> &result)
{
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
int getNumberOfSort(int number,int radix)
{
    while(number/radix)
    {
        counter++;
        number/=radix;
    }
    return counter;
}
template <typename T>
void initialRadixVector(vector<vector<T>> &vectorAll,int radix)
{
    for(int i=0; i<radix; ++i)
    {
        vector<T> temp;
        vectorAll.push_back(temp);
    }
}
template <typename T>
void getVector(vector<T> &dest,vector<vector<T>> &source)
{
    typename vector<vector<T>>::iterator iterAll;
    typename vector<T>::iterator iter;
    typename vector<T>::reverse_iterator riter;

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
        {
            for(riter=temp.rbegin(); riter!=temp.rend(); ++riter)
            {
                dest.insert(dest.begin(),*riter);
            }
            temp.clear();
        }
    }
}

template <typename T>
void SetRadix(vector<vector<T>> &vectorAll,vector<T> &vect,int number,int radix)
{
    typename vector<vector<T>>::iterator iterAll;
    typename vector<T>::iterator iter;
    for(iter=vect.begin(); iter!=vect.end(); ++iter)
    {
        location = abs(static_cast<int>(abs(*iter))/pow(radix,number))%(radix);
        vectorAll.at(location).push_back(*iter);
    }
}
template <typename T>
void radixSortOnce(vector<T> &vect, int number,int radix)
{
    initialRadixVector(vectorAll,radix);
    SetRadix(vectorAll,vect,number,radix);
    getVector(vect,vectorAll);
    //display1D(vect);
    //cout<<endl;
}
template <typename T>
void radixSort(vector<T> &vect, int number,int radix)
{
    if(0<=number)
    {
        radixSort(vect,number-1,radix);
        radixSortOnce(vect,number,radix);
    }// end of if
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
    int myArray_Shell[N];
    int myArray_Cocktail[N];
    int myArray_Heap[N];
    int myArray_Bucket[N];
    vector<int> myArray_Radix;

    int temp=0;
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
    displayArray(myArray_Shell);
    cout<<endl;
    Shell_Sort(myArray_Shell,N);
    displayArray(myArray_Shell);
    cout<<endl;
    Cocktail_Sort(myArray_Cocktail,N);
    displayArray(myArray_Cocktail);
    cout<<endl;
    HeapSort(myArray_Heap,N);
    displayArray(myArray_Heap);
    cout<<endl;
    Bucket_Sort(myArray_Bucket, MAXNUM, N);
    displayArray(myArray_Bucket);
    cout<<endl;
    //cout<<"Max value:\t"<<maxNumber<<"\nNeed:\t"<<numberOfSort<<endl;
    //cout<<"After radix sort: \n";
    radixSort(myArray_Radix,numberOfSort,radix);
    displayArray(myArray_Radix);
    cout<<endl;

    return 0;
}
