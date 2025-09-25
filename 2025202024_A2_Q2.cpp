#include <iostream>

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

int main(){

}