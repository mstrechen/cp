#include <iostream>

using namespace std;
int hash[1000001];
int a[500000];
int main(){
	ios::sync_with_stdio(false);
	int left = 0, right = 0,
		l=0,r=0, 
		n,k,
		numOfDifferent = 0;
	cin >> n >>k;
	for(int i = 0; i<n; i++)
	{
		cin >> a[i];
	}
	for(r = 0; r<n; r++)
	{
		hash[a[r]]++;
		numOfDifferent+=(hash[a[r]]==1);
		while(numOfDifferent>k)
		{
			hash[a[l]]--;
			numOfDifferent-=(hash[a[l]] == 0);
			l++;
		}
		if(r-l>right-left)
		{
			right = r;
			left = l;
		}
	}
	
	cout << left+1 << ' ' << right+1;
	return 0;
}