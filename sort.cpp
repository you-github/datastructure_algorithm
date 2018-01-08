/*
* @Author: Administrator
* @Date:   2018-01-07 14:04:10
* @Last Modified by:   Administrator
* @Last Modified time: 2018-01-07 21:57:19
*/


/*
我们通常所说的排序算法往往指的是内部排序算法，即数据记录在内存中进行排序。

排序算法大体可分为两种：

　　　　一种是比较排序，时间复杂度O(nlogn) ~ O(n^2)，主要有：冒泡排序，选择排序，插入排序，归并排序(原地归并)，堆排序，快速排序，希尔排序等。

　　　　另一种是非比较排序，时间复杂度可以达到O(n)，主要有：计数排序，基数排序，桶排序等。

 */



/*
1、快速排序

基本思想：采用分而治之的思想，将要排序的数分成左右两部分，其中一部分的数据比key小，另一部分数据比key大。然后将所分得的两部分数据进行同样的划分。重复执行以上的划分操作。
平均时间复杂度O（Nlog2(N)）
最好情况O（Nlog2(N)）
最坏情况O（N^2）
空间复杂度O（Nlog2(N)）
*/

#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <stack>
#include <algorithm>
//快速排序

using namespace std;

//函数声明
int parition(int*, int, int);
int parition_1(int*, int, int);
void quick_sort(int*, int, int);
void quicksort2(int*, int, int);
void insert_sort(int a[], int n);
void swap(int &a, int &b);
void select_sort(int a[], int n);
void shell_sort(int a[], int n);
void merge_sort(int a[],int low, int high, int tmp[]);
void merge(int a[], int low ,int mid, int high,int tmp[]);
bool MergeSort(int a[], int n);



int partition(int arr[], int low, int high)//返回划分的中间值
{
	/*
	以最左边的值为基准点，拿出来后形成第一个坑，从最右边开始遍历，
	找到的第一个比基准点小的元素将左一坑填上，因而右边形成一个坑，
	然后又从左坑右边的第一个元素开始遍历，找到的第一个比基准点大的
	元素填入右坑，同时左边又现坑，继续从右边找一个比基准小的元素填左坑
	周而复始，直到low>=high。
	 */
	int key;
	key = arr[low];//相当于在索引low处挖坑，下一个就要找合适的数据来填坑

	while (low < high)
	{
		while (low < high && arr[high] >= key) {
			high --;
		}
		if (low < high)
			arr[low ++] = arr[high];//找到合适的数据填到了low坑，但是形成了high坑，继续找合适的数据

		while ( low < high && arr[low] <= key)
			low ++;
		if ( low < high)
			arr[high --] =  arr[low];//low又成了坑
	}

	arr[low] = key;//将key填到这个坑
	return low;
}

 int parition_1(int array[], int left,int right)
 {
 	int key = array[right];
 	int i = left -1;
 	int temp;
 	for(int j = left; j < right; j++)
 	{
	 	if(array[j] < key) //把比基准点挪到左边，把比基准点大的挪到右边
	 	{
	 		i++;
	 		temp=array[j];
	 		array[j] = array[i];
	 		array[i] = temp;
	 	}
 	}
 
 	//把基准点放回到分界点
 	temp = array[i+1];
 	array[i+1] = array[right];
 	array[right] = temp;
 	return i+1;
 }

void quick_sort(int num[], int low, int high)
{
	int pos;
	if (low < high) {
		pos = partition(num, low, high);
		quick_sort(num, low, pos - 1);
		quick_sort(num, pos + 1, high);
	}
}

/*

C++ stack(堆栈）是一个容器的改编，它实现了一个先进后出的数据结构（LIFO）
使用该容器时需要包含#include<stack>头文件；
定义stack对象的示例代码如下：
stack<int> s1;
stack<string> s2;
stack的基本操作有：
1.入栈：如s.push(x);
2.出栈:如 s.pop().注意：出栈操作只是删除栈顶的元素，并不返回该元素。
3.访问栈顶：如s.top();
4.判断栈空：如s.empty().当栈空时返回true。
5.访问栈中的元素个数，如s.size（）;
下面举一个简单的例子：

#include <iostream>
#include <stack>
using namespace std;
int main(void)
{
	stack<double> s;//定义一个栈
	for(int i=0;i<10;i++)
		s.push(i);
	while(!s.empty())
	{
		printf("%lf\n",s.top());
		s.pop();
	}
	cout<<"栈内的元素的个数为："<<s.size()<<endl;
	return 0;
}
*/



/*快速排序非递归版*/
void quicksort2(int num[], int low, int high)
{
	int key = num[low];
	stack<int> s;

	if (low < high) {
		int pos = parition_1(num, low, high);
		if (pos - 1 > low) {
			s.push(pos - 1);
			s.push(low);
		}
		if (pos + 1 < high) {
			s.push(high);
			s.push(pos + 1);
		}
		while (!s.empty()) {
			int l = s.top();
			s.pop();
			int r = s.top();
			s.pop();
			pos = partition(num, l, r);
			if (pos - 1 > l) {
				s.push(pos - 1);
				s.push(l);
			}
			if (pos + 1 < r) {
				s.push(r);
				s.push(pos + 1);
			}
		}
	}
}



/*
2、插入排序

基本思想：将元素逐个添加到已经排好序的数组中去。
平均时间复杂度O(n^2)
最好时间复杂度O(n)
最坏时间复杂度O(n^2)
空间复杂度O(1)
*/
void insert_sort(int a[], int n)
{
	//要进行n-1趟插入
	for (int i = 1; i < n; i++) { //假设第0个已在正确位置，从第一个开始插入
		//第i趟插入需要在【0，i-1】中找到i的合适位置
		int j = 0;
		while ( (j < i) && (a[i] > a[j]) ) {
			j ++;
		}
		//如果找到合适位置i应该！=j，如果i==j，说明i正好在正确的位置
		if ( i != j) {
			//将a[i]插入到合适的位置，即位置j，那么[j, i-1]位置上的数应该后移。先保存a[i],然后后移。
			int tmp = a[i]; //空间复杂度O(1)
			for (int k = i; k > j; k--)
				a[k] = a[k - 1];
			a[j] = tmp;
		}
	}

}


/*
3、选择排序

基本思想：首先，选出最小的数放在第一位，然后选择第二小的数，放在第二位；以此类推，直到所有的数从小到大排列.
那么，对于大小为N的数组需要N-1轮选择过程。第i轮选取第i小的数，请将其放在第i个位置上。
不稳定
平均时间复杂度O（N^2）
最好情况O（N^2）
最坏情况O（N^2）
空间复杂度O（1）
*/

void select_sort(int a[], int n)
{
	for (int i = 0; i < n - 1; i++) { //进行n-1轮选择,也就是i的取值为【0，n-2】
		int min_index = i;
		//记录第i小的数所在的索引
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[min_index])
				min_index = j;
		}
		if (i != min_index) { //根据记录的第i小的数的索引，找到了第i小的数。然后将该数放到其正确位置。也就是第i个位置。
			swap(a[i] , a[min_index]);
		}
	}

}


void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}


/*
4、冒泡排序

基本思想： 不断比较相邻的两个数，让较大的数不断地往后移。经过一番比较，就选出了最大的数。经过第二轮比较，
就选出了次大的数。以此类推。
那么对于大小为N的数组，需要N-1轮比较。
平均时间复杂度O（N^2）
最好情况O（N）
最坏情况O（N^2）
空间复杂度O（1）
*/

void bubble_sort(int a[], int n)
{
	//要进行N-1轮比较
	bool is_sorted = true;
	for (int i = 0; i < n - 1; i++ ) //[0,n-2]恰好n-1轮比较
	{
		for (int j = 0; j < n - i - 1 ; j++) //已经排好序的最后i个不用比较，要比较的数的个数为n-i个，那么需要比较的次数为n-i-1
		{
			if (a[j] > a[j + 1]) {
				is_sorted = false;
				swap(a[j], a[j + 1]);
			}
		}
		if (is_sorted) //如果没有发生交换，说明已经排好序了（只在完全排好序情况下），提前退出循环,所以最好情况下时间复杂度为O（N）
			break;
	}
}



/*
5、希尔排序 

基本思想：将无序数组分成若干个子序列，子序列不是逐段分割的，而是相隔特定增量。对各个子序列进行插入排序。 
然后再选择一个更小的增量，再将数组分割成多个子序列进行排序。最后选择增量为1，即使用直接插入排序，使最终数组成为有序数组。 
平均时间复杂度O(n^1.3) 
最好时间复杂度O(n) 
最坏时间复杂度O(n^2) 
空间复杂度O(1) */

void shell_sort(int a[], int n)  
{  
    int gap;  
    for( gap = n/2; gap > 0; gap /= 2){  
        for(int i = gap; i < n; i ++){  
            for(int j = i - gap; j >= 0 && a[j] > a[j + gap]; j-=gap){//每个元素与自己组内的元素进行插入排序  
                swap(a[j], a[j + gap]);  
            }  
        }  
    }  
}  



/* 
6、归并排序

基本思想：将待排序序列【0，n-1】看成是n个长度为1的有序序列，将相邻的有序表成对归并，
得到n/2个长度为2的有序表。再次归并，得到n/4个长度为4的有序表。 
依次类推，最后得到长度为n的1个有序表。 
所以归并排序其实要做两件事： 
1、先递归的分解数列， 
2、再合并数列就完成了归并排序。 
 
先来考虑如何合并？ 
每次合并过程中都要对两个有序的序列段进行合并，然后排序 
待合并的两个有序序列段分别为 R[low, mid] 和 R[mid+1, high] 
先将它们合并到一个暂存数组R2，合并完再将R2复制回R1中。 
这样一次合并排序就完成了。 
 
最好、最坏和平均时间复杂度都是O(nlogn)， 
空间复杂度是O(n) 
*/  


void merge(int a[], int low ,int mid, int high,int tmp[])  
{  
    int i,j,k;  
    i = low;  
    j = mid + 1;  
    k = 0;//k是存放临时合并数组的下表  
  
    while( i <= mid && j <= high){  
        if( a[i] <= a[j])  
            tmp[k++] = a[i++];  
        else   
            tmp[k++] = a[j++];  
    }  

  //处理子数组中剩余的元素
    while( i <= mid)  
        tmp[k++] = a[i++];  
    while( j <= high)  
        tmp[k++] = a[j++];  
  
    //最后再复制回a  
    for(i = 0; i < k; i++ )  
        a[low+i] = tmp[i];//!!!!此处a是从low开始，tmp是从0开始。  
} 


void merge_sort(int a[],int low, int high, int tmp[])  
{  
    if(low < high){  
        int mid = (high + low)/2;  
        merge_sort(a,low, mid, tmp);  
        merge_sort(a, mid+1, high, tmp);  
        merge(a, low, mid, high, tmp);  
    }  
}  
  

bool MergeSort(int a[], int n)  
{  
    int *p = new int[n];  
    if (p == NULL)  
        return false;  
    merge_sort(a, 0, n-1, p);  
    delete[] p;  
    return true;  
}  




/*
7、原地归并排序

所利用的核心思想便是“反转内存”的变体,即“交换两段相邻内存块。
 */

template <typename T>
void swap_1(T a[],int first,int second)
{
	T temp;
	temp = a[first];
	a[first] = a[second];
	a[second] = temp;
}

template <typename T>
void reverse(T a[],int begin,int end)
{
	while(begin < end){
		swap_1(a,begin++,end--);
	}
}


template <typename T>
void exchange(T a[],int begin,int mid,int end)
{
	reverse(a,begin,mid);
	reverse(a,mid+1,end);
	reverse(a,begin,end);
}


template <typename T>
void merge_1(T a[],int begin,int mid,int end)
{
	int i = begin;
	int j = mid + 1;
	while( i < j && j <= end){
		while(i < j && a[i] <= a[j]){
		i++;
	}
	int old_j = j;
	while(j <= end && a[j] < a[i]){
		j++;
	}
	exchange(a,i,old_j-1,j-1);
	i += (j - old_j);
	}
	
}


template <typename T>
void merge_sort_1(T a[],int begin,int end)
{
	if(begin < end){
		int mid = begin + (end - begin)/2;
		merge_sort_1(a,begin,mid);
		merge_sort_1(a,mid+1,end);
		merge_1(a,begin,mid,end);
	}
}

/*
8、堆排序

是指利用[堆]这种数据结构所设计的一种[排序算法]。
堆积是一个近似[完全二叉树]的结构，并同时满足堆积的性质：
即子结点的键值或索引总是小于（或者大于）它的父节点。

通常堆是通过一维数组来实现的。在数组起始位置为 1 的情形中：
	父节点 i 的左子节点在位置 (2*i)
	父节点 i 的右子节点在位置 (2*i+1)
	子节点 i 的父节点在位置 floor(i/2)

大根堆排序算法的基本操作：

1、建堆，建堆是不断调整堆的过程，从len/2处开始调整，
一直到第一个节点，此处len是堆中元素的个数。建堆的过程是线性的过程，
从len/2到0处一直调用调整堆的过程，相当于o(h1)+o(h2)…+o(hlen/2) 其中h表示节点的深度，len/2表示节点的个数，
这是一个求和的过程，结果是线性的O(n)。

2、调整堆：调整堆在构建堆的过程中会用到，而且在堆排序过程中也会用到。
利用的思想是比较节点i和它的孩子节点left(i),right(i)，选出三者最大(或者最小)者，
如果最大（小）值不是节点i而是它的一个孩子节点，那边交互节点i和该节点，然后再调用调整堆过程，
这是一个递归的过程。调整堆的过程时间复杂度与堆的深度有关系，是lgn的操作，因为是沿着深度方向进行调整的。

3、堆排序：堆排序是利用上面的两个过程来进行的。首先是根据元素构建堆。
然后将堆的根节点取出(一般是与最后一个节点进行交换)，将前面len-1个节点继续进行堆调整的过程，
然后再将根节点取出，这样一直到所有节点都取出。堆排序过程的时间复杂度是O(nlgn)。因为建堆的时间复杂度是O(n)（调用一次）；
调整堆的时间复杂度是lgn，调用了n-1次，所以堆排序的时间复杂度是O(nlgn)[2] 


 */


void HeapAdjust(int *a,int i,int size)  //调整堆 
{
    int lchild=2*i;       //i的左孩子节点序号 
    int rchild=2*i+1;     //i的右孩子节点序号 
    int max=i;            //临时变量 
    if(i<=size/2)          //如果i是叶节点就不用进行调整 
    {
        if(lchild<=size&&a[lchild]>a[max])
        {
            max=lchild;
        }    
        if(rchild<=size&&a[rchild]>a[max])
        {
            max=rchild;
        }
        if(max!=i)
        {
            swap(a[i],a[max]);
            HeapAdjust(a,max,size);    //避免调整之后以max为父节点的子树不是堆 
        }
    }        
}


void BuildHeap(int *a,int size)    //建立堆 
{
    int i;
    for(i=size/2;i>=1;i--)    //非叶节点最大序号值为size/2 
    {
        HeapAdjust(a,i,size);    
    }    
} 


void HeapSort(int *a,int size)    //堆排序 
{
    int i;
    BuildHeap(a,size);
    for(i=size;i>=1;i--)
    {
        // cout<<a[1]<<" ";
        swap(a[1],a[i]);           //交换堆顶和最后一个元素，即每次将剩余元素中的最大者放到最后面 
          // BuildHeap(a,i-1);        //将余下元素重新建立为大顶堆 
          HeapAdjust(a,1,i-1);      //重新调整堆顶节点成为大顶堆
    }
} 



int main()
{
	int num[] = {9, 4, 5, 2, 1, 3, 7, 8, 6};

/*	quick_sort(num, 0, 8);
	for (int i = 0; i < 9; i++)
	{
		printf("%d\n", num[i]);
	}

	quicksort2(num, 0, 8);
	for (int i = 0; i < 9; i++)
	{
		printf("%d\n", num[i]);
	}

	insert_sort(num, 9);
	for (int i = 0; i < 9; i++)
	{
		printf("%d\n", num[i]);
	}

	select_sort(num, 9);
	for (int i = 0; i < 9; i++)
	{
		printf("%d\n", num[i]);
	}

	bubble_sort(num, 9);
	for (int i = 0; i < 9; i++)
	{
		printf("%d\n", num[i]);
	}

    MergeSort(num, 9);
    for (int i = 0; i < 9; i++)
    {
    	printf("%d\n", num[i]);
    }

    shell_sort(num, 9);
    for (int i = 0; i < 9; i++)
    {
    	printf("%d\n", num[i]);
    }


	int len = sizeof(num)/sizeof(int);
    merge_sort_1(num, 0, len-1);
    int i;
    for (i = 0; i < len; ++i)
        cout << num[i] << " ";
    cout << endl;*/



	/*int a[100];
	int size;
	while(scanf("%d",&size)==1&&size>0)
	{
	    int i;
	    for(i=1;i<=size;i++)
	        cin>>a[i];
	    HeapSort(a,size);
	    for(i=1;i<=size;i++)
	        cout<<a[i]<<"";
	    cout<<endl;
	}*/

	HeapSort(num,9);
	for (int i = 1; i <= 9; i++)
	{
		printf("%d\n", num[i]);
	}

    return 0;

}