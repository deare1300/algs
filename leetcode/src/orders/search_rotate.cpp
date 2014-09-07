#include "include/search_rotate.h"
#include "include/header.h"

search_rotate::search_rotate()
{
    //ctor
}

search_rotate::~search_rotate()
{
    //dtor
}

bool search(int A[], int n, int target) {
        int mid;
        int left = 0, right = n - 1;
        if(n == 0)
            return false;
        while(left <= right) {
            cout<<left<<'\t'<<right<<endl;
            if(A[left] == A[right]) {
                    cout<<"equal"<<endl;
                if(A[left] == target) {
                    return true;
                }
                ++left;
                --right;
                continue;
            }
            mid = left+(right-left)/2;
            if(A[mid] == target) return true;
            if(A[left] > A[right]) {
                //--->
                if(A[mid] >= A[left]){
                        // 4 5 /6/ 0 1 2 3   // 1,/1/,2,0
                    if(A[mid] > target && A[left] <= target) {
                        right = mid-1;
                    }
                    else {
                        left = mid+1;
                    }
                }
                else {
                    // 4 0 /1/ 2 3
                    if(A[mid+1] <= target && A[right] >= target) {
                        left = mid+1;
                    }
                    else {
                        right = mid-1;
                    }
                }
                cout<<left<<'\t'<<right<<endl;
            }
            else {
                    // 1 2 3 4 5 6
                if(A[mid] < target && A[right] >= target) {
                    left = mid+1;
                }
                else {
                    right = mid-1;
                }
            }
        }
        return false;
    }


void test_search_rotate()
{
    int a[] = {0,1,1,2,0,0};
    cout<<search(a, 6, 2)<<endl;
}
