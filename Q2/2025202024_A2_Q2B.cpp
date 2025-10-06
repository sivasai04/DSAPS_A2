#include <iostream>
// #include "heaps.h"


using namespace std;



class priority_queue{
    private:
        int PqSize;
        int PqCapacity;
        int minheap;
        int * arr;

    public:
        //////............ resizing the array when ever it is full.
        void doublesize(){
            int newCapacity;
            if(PqCapacity == 0){
                newCapacity = 1;
            }
            else{
                newCapacity = 2*PqCapacity;
            }
            int *ReSize = new int[newCapacity];

            for(int i=0; i<PqSize; i++){
                ReSize[i] = arr[i];
            }
            delete[] arr;
            arr = ReSize;
            PqCapacity = newCapacity;
        }

        //////////.............. heapfing from the bottom when new element is inserted in the array
        void InsertHeapify(int ind){
            if(minheap){
                while(ind > 0){
                    int parentInd = (ind-1)/2;
                    if(arr[parentInd] > arr[ind]){
                        int temp = arr[parentInd];
                        arr[parentInd] = arr[ind];
                        arr[ind] = temp;
                        ind = parentInd;
                    }
                    else{
                        break;
                    }
                }
            }
            else{
                while(ind > 0){
                    int parentInd = (ind-1)/2;
                    if(arr[parentInd] < arr[ind]){
                        int temp = arr[parentInd];
                        arr[parentInd] = arr[ind];
                        arr[ind] = temp;
                        ind = parentInd;
                    }
                    else{
                        break;
                    }
                }
            }
        }

        //////////.............. heapfing from the top when max or min element is deleted from the array
        void DeleteHeapify(int ind){
            if(minheap){
                while(true){
                    int minChildind;
                    int Leftind = 2*ind+1;
                    int Rightind = 2*ind+2;

                    if(Leftind >= PqSize){
                        break;
                    }
                    if(Rightind >= PqSize){
                        minChildind = Leftind;
                    }
                    else{
                        if(arr[Leftind] < arr[Rightind]){
                            minChildind = Leftind;
                        }
                        else{
                            minChildind = Rightind;
                        }
                    }
                    if(arr[ind] > arr[minChildind]){
                        int temp = arr[ind];
                        arr[ind] = arr[minChildind];
                        arr[minChildind] = temp;
                        ind = minChildind;
                    }
                    else{
                        break;
                    }
                }
            }
            else{
                while(true){
                    int maxChildind;
                    int Leftind = 2*ind+1;
                    int Rightind = 2*ind+2;

                    if(Leftind >= PqSize){
                        break;
                    }
                    if(Rightind >= PqSize){
                        maxChildind = Leftind;
                    }
                    else{
                        if(arr[Leftind] > arr[Rightind]){
                            maxChildind = Leftind;
                        }
                        else{
                            maxChildind = Rightind;
                        }
                    }
            
                    if(arr[ind] < arr[maxChildind]){
                        int temp = arr[ind];
                        arr[ind] = arr[maxChildind];
                        arr[maxChildind] = temp;
                        ind = maxChildind;
                    }
                    else{
                        break;
                    }
                }
            }
        }

        //////////....... priority queue constructor.
        priority_queue(bool heapProperty){
            arr = nullptr;
            PqSize = 0;
            PqCapacity = 0;
            minheap = heapProperty;
        }

        void push(int val){
            if(PqSize == PqCapacity){
                doublesize();
            }
            arr[PqSize] =  val;
            PqSize++;
            InsertHeapify(PqSize-1);
        }

        void pop(){
            if(PqSize == 0){
                cout << "queue is empty.";
                return;
            }
            arr[0] = arr[PqSize-1];
            PqSize--;
            DeleteHeapify(0);
        }

        int top(){
            if(PqSize == 0){
                cout << "queue is empty";
                return -1;
            }
            return arr[0];
        }

        bool empty(){
            return PqSize == 0;
        }

        int size(){
            return PqSize;
        }
};




///////------ maintaing the global heaps for the previous d days
priority_queue D_maxHeap(false);
priority_queue D_minHeap(true);

int freq[100005] = {0};
int D_maxHeapSize = 0;
int D_minHeapSize = 0;

void push_number(int val){
    if(D_maxHeap.empty() || val <= D_maxHeap.top()){
        D_maxHeap.push(val);
        D_maxHeapSize++;
    }
    else{
        D_minHeap.push(val);
        D_minHeapSize++;
    }
}

void pop_number(int val){
    freq[val]++;
    if (D_maxHeap.empty() || val > D_maxHeap.top()){
        D_minHeapSize--;
    }
    else{
        D_maxHeapSize--;
    }
}

////////------- this function deletes the invalid entries in the min and maxheaps;

void delete_elemets(bool minflag, bool maxFlag){
    if(maxFlag){
        while(!D_maxHeap.empty() && freq[D_maxHeap.top()] > 0){
            freq[D_maxHeap.top()]--;
            D_maxHeap.pop();
        }
    }

    if(minflag){
        while(!D_minHeap.empty() && freq[D_minHeap.top()] > 0){
            freq[D_minHeap.top()]--;
            D_minHeap.pop();
        }
    }
}

////////////----------- this is to balance the min and maxheaps so that median is always int the top of eother of both heaps
void balance(){
    
    delete_elemets(true, true);
    while(abs(D_maxHeapSize- D_minHeapSize) > 1){
        if(D_maxHeapSize > D_minHeapSize){
            D_minHeap.push(D_maxHeap.top());
            D_maxHeap.pop();
            D_minHeapSize++;
            D_maxHeapSize--;

            delete_elemets(false, true);
        }
        else{
            D_maxHeap.push(D_minHeap.top());
            D_minHeap.pop();
            D_maxHeapSize++;
            D_minHeapSize--;

            delete_elemets(true, false);
        }
    }
}

double D_Median(){
    balance();

    if(D_maxHeapSize == D_minHeapSize){
        if(D_maxHeapSize == 0){
            return 0;
        }
        int n1 = D_maxHeap.top();
        int n2 = D_minHeap.top();
        return (n1+n2)/2.0;
    }
    if(D_maxHeapSize > D_minHeapSize){
        return D_maxHeap.top();
    }
    else{
        return D_minHeap.top();
    }
}

int main(){
    int n,d;
    cin >> n >> d;
    
    int arr[n];
    for(int i=0; i<n; i++){
        cin >> arr[i];

    }
    priority_queue T_maxheap(false);
    priority_queue T_minheap(true);
    int ans =0;
    for(int i=0; i<d; i++){
        push_number(arr[i]);

        if(T_maxheap.empty() || arr[i] <= T_maxheap.top()){
            T_maxheap.push(arr[i]);
        }
        else{
            T_minheap.push(arr[i]);
        }

        while(abs(T_maxheap.size() - T_minheap.size()) > 1){
            if(T_maxheap.size() > T_minheap.size()){
                T_minheap.push(T_maxheap.top());
                T_maxheap.pop();
            }
            else{
                T_maxheap.push(T_minheap.top());
                T_minheap.pop();
            }
        }
    }

    for(int i=d; i<n; i++){
        double D_median_val = D_Median();

        double T_median_val;
        if(T_maxheap.size() == T_minheap.size()){
            int n1 = T_maxheap.top();
            int n2 = T_minheap.top();

            T_median_val = (n1 + n2)/ 2.0;
        }
        else if(T_maxheap.size() > T_minheap.size()){
            T_median_val = T_maxheap.top();
        }
        else{
            T_median_val = T_minheap.top();
        }

        if( arr[i] >= T_median_val+D_median_val){
            ans++;
        }

        int prev_day_sale = arr[i];
        if(T_maxheap.empty() || prev_day_sale <= T_maxheap.top()){
            T_maxheap.push(prev_day_sale);
        }
        else{
            T_minheap.push(prev_day_sale);
        }

        while(abs(T_maxheap.size() - T_minheap.size()) > 1){
            if(T_maxheap.size() > T_minheap.size()){
                T_minheap.push(T_maxheap.top());
                T_maxheap.pop();
            }
            else{
                T_maxheap.push(T_minheap.top());
                T_minheap.pop();
            }
        }

        pop_number(arr[i-d]);
        push_number(prev_day_sale);

    }

    cout << ans << endl;
    return 0;
}