#include<stdio.h> 
#include<math.h>
using namespace std;
int *constructST(int *input,int n);		//input array and length of input array to be passed.
int constructSTUtil(int *input,int ss, int se, int *st,int si);		//input array, start index, end index, segment_tree array, current node
int getSum(int *st,int n,int l, int r);
int getSumUtil(int *st,int ss,int se, int qs,int qe, int current);	//segment tree array,start index, end index, query start, query end, current node
void updateValue(int *input, int *st, int i, int new_value);		//input array, segment_tree array, index i is being updated to new_value
void updateValueUtil(int *st,int ss, int se, int i, int diff, int current);
int main()
{
	int n;
	scanf("%d",&n);
	int *input = new int[n];
	for(int i=0;i<n;i++)
	{
		scanf("%d",&input[i]);
	}	
	int *st = constructST(input,n);	
	return 0;
}

void updateValueUtil(int *st, int ss, int se, int i, int diff, int current)
{
	if(i < ss || i > se)
	{
		return ;
	}
	st[current] +=  diff;
	if(se!=ss)
	{	
		int mid = ss + (se - ss)/2;
		updateValueUtil(st,ss,mid,i,diff,2*current+1);
		updateValueUtil(st,mid+1,se,i,diff,2*current+2);
	}
}

void updateValue(int *input,int *st, int i, int new_value)
{
	int diff = new_value - input[i];
	input[i] = new_value;
	updateValueUtil(st,0,sizeof(input)/sizeof(input[0])-1,i,diff,0);
}	

int getSumUtil(int *st, int ss, int se, int qs, int qe, int current)
{
	//if the range of the node lies between the query then return the value at node
	if(ss >= qs && se <= qe)
	{
		return st[current];
	}
	//if the range is completely outside the current node then return 0
	if(qs > se || qe < ss)
	{
		return 0;
	}
	//else if the query is within some range, divide the range and find to the left and right and then sum up
	int mid = ss + (se - ss)/2;
	return getSumUtil(st,ss,mid,qs,qe,2*current+1) + getSumUtil(st,mid+1,se,qs,qe,2*current+2);
}

int getSum(int *st,int n,int l,int r)
{
	return getSumUtil(st,0,n,l,r,0);
}

int *constructST(int *input,int n)
{
	int height = (int)(ceil(log2(n)));
	int max_size = 2*(int)pow(2,height) - 1;
	int *st = new int[max_size];
	constructSTUtil(input,0,n-1,st,0);
}


int constructSTUtil(int *input,int ss, int se, int *st, int si)
{
	// If start index is equal to the end index, then put value in the st array and return the same value.
	if(ss == se)
	{
		st[si] = input[ss];
		return input[ss];
	}
	//else build left subtree and right subtree and add value of both and then return that value
	int mid = ss + (se - ss)/2;
	st[si] = constructSTUtil(input,ss,mid,st,2*si+1) + constructSTUtil(input,mid+1,se,st,2*si+2);
	return st[si];
}
