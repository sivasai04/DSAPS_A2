#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>

using namespace std;


template <class T>

class deque{
    private:
        int FrontInd;
        int BackInd;
        int Qsize;
        int Qcapacity;
        T* arr;

    public:

        void doublesize(){
            int newCapacity;
            if(Qcapacity == 0){
                newCapacity = 1;
            }
            else{
                newCapacity = 2*Qcapacity;
            }
            T* ReSize = new T[newCapacity];

            for(int i=0; i<Qsize; i++){
                int ind = (FrontInd+i)%Qcapacity;
                ReSize[i] = arr[ind];
            }
            delete[] arr;
            arr = ReSize;
            FrontInd = 0;
            BackInd = Qsize-1;
            Qcapacity = newCapacity;
        }
        
        ////////............ operation 1 initialing the deque.
        deque(){
            arr = nullptr;
            FrontInd = BackInd = -1;
            Qsize = 0;
            Qcapacity = 0;
        }

        ///////////........... operation 2 initializing the deque fo size n with all the values as defaut valus T.
        deque(int n){
            arr = new T[n];
            Qcapacity = n;
            for(int i=0; i<n; i++){
                arr[i] = T();
            }
            Qsize = n;
            FrontInd = 0;
            BackInd = n-1;
        }

        ////////......... operation 3 initializing a deque of size n with all values as user inputed values.
        deque(int n, T& val){
            arr = new T[n];
            Qcapacity = n;
            for(int i=0; i<n; i++){
                arr[i] = val;
            }
            Qsize = n;
            FrontInd = 0;
            BackInd = n-1;
        }

        /////////.......... operation 4 push_BackInd(val) that is append data at the end.
        void push_back(T& val){
            if(Qsize == Qcapacity){
                doublesize();
            }
            if((FrontInd == BackInd) && (FrontInd == -1)){
                FrontInd++;
                BackInd++;
                arr[BackInd] = val;
            }
            else{
                BackInd = (BackInd+1)%Qcapacity;
                arr[BackInd] = val;
            }
            Qsize++;
        }

        //////////...........operation 5 pop_BackInd() remove the last element in the deque.
        void pop_back(){
            if(FrontInd == BackInd){
                //// means there is only one element.
                FrontInd = BackInd = -1;
                Qsize = 0;
            }
            else{
                BackInd = (BackInd-1+Qcapacity)%Qcapacity; 
                Qsize--;
            }
        }

        /////.......... operation 6 push_FrontInd(val) that is append data at the begin.
        void push_front(T& val){
            if(Qsize == Qcapacity){
                doublesize();
            }
            if((FrontInd == BackInd) && (FrontInd == -1)){
                FrontInd++;
                BackInd++;
                arr[BackInd] = val;
            }
            else{
                FrontInd = (FrontInd-1 + Qcapacity)%Qcapacity;
                arr[FrontInd] = val;
            }
            Qsize++;
        }

        /////////..........operation 7 pop_FrontInd() remove the first element in the deque.
        void pop_front(){
            if((FrontInd == BackInd) && (FrontInd == -1)){
                cout << "deque is empty. this is operation is invalid";
            }
            else if(FrontInd == BackInd){
                //// means there is only one element.
                FrontInd = BackInd = -1;
                Qsize = 0;
                return;
            }
            else{
                FrontInd = (FrontInd+1)%Qcapacity;
                Qsize--;
            }
        }

        /////////..........operation 8 returns the front element.
        T front(){
            if(Qsize == 0){
                return T();
            }
            return arr[FrontInd];
        }

        /////////..........operation 9 returns the back element.
        T back(){
            if(Qsize == 0){
                return T();
            }
            return arr[BackInd];
        }

        /////////..........operation 10 pop_FrontInd() remove the first element in the deque.
        T& operator[](int ind){
            if(ind < 0){
                ind =  Qsize + ind;
            }
            if(ind < 0 || ind >= Qsize){
                static T dummy_variable;
                return dummy_variable;
            }
            int returnInd = (FrontInd+ind)%Qcapacity;
            return arr[returnInd];
        }

        /////////..........operation 11 checks wheather queue is emoty or not.
        bool empty(){
            return Qsize == 0;
        }

        /////////..........operation 12 return the size of the queue.
        int size(){
            return Qsize;
        }

        /////////..........operation 13 changing the size dynamically to new size n with defaut values if n > Qcapacity. and shrinking it when n < Qcapacity
        void resize(int n){
            T defaultVal = T();
            resize(n, defaultVal);   
        }

        /////////..........operation 14 changing the size dynamically to new size n with values if n > Qcapacity. and shrinking it when n < Qcapacity
        void resize(int n, T& val){
            if(n > Qsize){
                int rem = n-Qsize;
                for(int i=0; i<rem; i++){
                    push_Back(val);
                }
            }
            else if(n < Qsize){
                if(n == 0){
                    clear();
                }
                T* ResizeArr = new T[n];
                for(int i=0; i<n; i++){
                    int ind = (FrontInd+i)%Qcapacity;
                    ResizeArr[i] = arr[ind];
                }
                delete[] arr;
                arr = ResizeArr;
                Qcapacity = Qsize = n;
                FrontInd = 0;
                BackInd = n-1;
            }
        }

        /////////..........operation 15 changing the Qcapacity of deque to n, if n > current capacity
        void reserve(int n){
            if(n <= Qcapacity){
                return ;
            }
            else{
                T* ResizeArr = new T[n];
                for(int i=0; i<Qsize; i++){
                    int ind = (FrontInd+i)%Qcapacity;
                    ResizeArr[i] = arr[ind];
                }
                delete[] arr;
                arr = ResizeArr;
                Qcapacity = n;
                FrontInd = 0;
                BackInd = Qsize-1;
            }
        }

        /////////..........operation 15 reducing the Qcapacity of the deque to current Qsize.
        void shrink_to_fit(){
            if(Qsize == Qcapacity){
                return;
            }
            T* ResizeArr = new T[Qsize];
            for(int i=0; i<Qsize; i++){
                int ind = (FrontInd+i)%Qcapacity;
                ResizeArr[i] = arr[ind];
            }
            delete[] arr;
            arr = ResizeArr;
            Qcapacity = Qsize;
            FrontInd = 0;
            BackInd = Qsize-1;
        }
        
        /////////..........operation 17 remove all elements of deque.
        void clear(){
            if(arr != nullptr){
                delete[] arr;
            }
            arr = nullptr;
            FrontInd = -1;
            BackInd = -1;
            Qsize = 0;
            Qcapacity = 0;
        }

        /////////..........operation 18 returning the capacity of the queue.
        int capacity(){
            return Qcapacity;
        }
};

#endif