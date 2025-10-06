# Assignment 2

---

## Question 1: Deque and Randomized Queue

### Data Structures Used

1. **Deque (Double-Ended Queue)**
   - Implemented using a **circular array** to allow O(1) amortized operations at both ends
   - Dynamic resizing with capacity doubling when full
   - Supports negative indexing (e.g., `D[-1]` for last element)

2. **Randomized Queue**
   - Built on top of the custom deque implementation
   - Uses random index generation for uniform selection probability


### Algorithm

#### Deque Implementation
- **Circular Array Structure**: Uses `FrontInd` and `BackInd` pointers to track the beginning and end of the queue

- **Dynamic Resizing**: When `size == capacity`, the array is doubled. Elements are rearranged linearly starting from index 0

- **Operations**:
  - `push_back()` / `push_front()`: Add elements at rear/front with circular indexing
  - `pop_back()` / `pop_front()`: Remove elements from rear/front
  - `operator[]`: Supports both positive and negative indexing using modulo arithmetic
  - `resize()`, `reserve()`, `shrink_to_fit()`: Memory management operations

#### Randomized Queue Implementation
- **Enqueue**: Simply calls `push_back()` on the underlying deque - O(1) amortized time.

- **Dequeue**: 
  - Generate random index using `rand() % size`
  - Swap element at random index with last element
  - Pop the last element using `pop_back()`
  - This ensures O(1) amortized time and maintains uniform randomness
- **Sample**: Return element at random index without removal - O(1)

### Key Optimizations
- Circular array prevents need for shifting elements
- Swap-with-last technique in dequeue maintains constant time complexity
- Amortized O(1) for all operations through capacity doubling strategy

### Compilation and Execution

```bash
# Compile
g++ -o Q1 2025202024_A2_Q1A.cpp
g++ -o Q1 2025202024_A2_Q1B.cpp
```

---

## Question 2: Priority Queue and David's Bakery Problem

### Data Structures created

1. **Priority Queue (Min/Max Heap)**
   - Implemented using **binary heap** stored in a dynamic array
   - Supports both min-heap and max-heap based on constructor parameter
   - All operations maintain heap property through heapify operations
   - **NOTE** `  you should pass ``true`` if you want to implement minhead and ``false`` to implement maxheap`

2. **Two Heap Approach for Median Finding**
   - **Max-Heap**: Stores smaller half of elements
   - **Min-Heap**: Stores larger half of elements
   - Median is always at the top of one or both heaps

### Algorithm and Approach

#### Priority Queue Implementation
- **Binary Heap Structure**: Parent at index `i`, children at `2*i+1` and `2*i+2`
- **Insert Heapify**: Bubbles up newly inserted element to maintain heap property - O(log n)
- **Delete Heapify**: Bubbles down root element after deletion - O(log n)
- **Operations**:
  - `push()`: Add element at end, then heapify up
  - `pop()`: Replace root with last element, then heapify down
  - `top()`: Return root element - O(1)

## Q2-part-B
**Approach**:
1. **Maintain Four Heaps**:
   - `D_maxHeap`, `D_minHeap`: For last d days (trailing window)
   - `T_maxHeap`, `T_minHeap`: For all days from start (total window)

2. **Sliding Window for Trailing d Days**:
   - Use lazy deletion technique with frequency array
   - Mark elements for deletion but don't remove immediately
   - Clean up invalid elements during balance operation
   - When element leaves the d-day window, increment `freq[val]`

3. **Median Calculation**:
   - If both heaps have equal size: `median = (max_heap.top() + min_heap.top()) / 2.0`
   - Otherwise: `median = larger_heap.top()`

4. **Balancing Heaps**:
   - Maintain invariant: `|maxHeap.size() - minHeap.size()| <= 1`
   - Transfer elements between heaps when imbalance occurs
   - Remove invalid (deleted) elements during balancing

5. **For Each Day i (from d to n-1)**:
   - Calculate `D_median` (last d days)
   - Calculate `T_median` (all days so far)
   - Check condition: `sales[i] >= D_median + T_median`
   - Update heaps: add current day, remove day `i-d` from trailing window

### Key Optimizations
- **Lazy Deletion**: O(1) marking instead of O(log n) actual deletion
- **Two-Heap Median**: O(1) median access instead of O(n) sorting
- **Amortized Complexity**: Overall O(n log n) for n days

### Time Complexity Analysis
- Each insertion/deletion: O(log n)
- Total for n days: O(n log n)
- Space Complexity: O(n)

### Compilation and Execution

```bash
# Compile
g++ -o Q2 2025202024_A2_Q2A.cpp  
g++ -o Q2 2025202024_A2_Q2B.cpp

```

---

## Question 3: The Lost Library of IIIT Hyderabad

### Data Structures Used

1. **2D/3D Dynamic Programming Tables**
   - `dp[i][j]`: Minimum cost for searching bins in range [i, j]
   - Additional dimensions for tracking direction and position in Part 3

### Algorithm and Approach

#### Part 1: Ideal Search Plan (Logical Cost Only)

**Approach**: Classic **Optimal Binary Search Tree (OBST)** problem
- **State**: `dp[i][j]` = minimum cost to search bins i to j
- **Recurrence**: 
  ```
  dp[i][j] = min(sum[i][j] + dp[i][k-1] + dp[k+1][j]) for all k in [i,j]
  ```
  where `sum[i][j]` = sum of frequencies from i to j
- **Intuition**: Cost of a node = (depth + 1) × frequency. Try each bin as root and pick minimum.
- **Time Complexity**: O(n³)
- **Space Complexity**: O(n²)

#### Part 2: Basic Robot Costs

**Approach**: Modified OBST with movement costs
- **State**: `dp[i][j]` = minimum cost including movement from position 0
- **Recurrence**: 
  ```
  dp[i][j] = min(root*F[root] + sum[i][j] + dp[i][k-1] + dp[k+1][j])
  ```
- **Key Insight**: 
  - Cost to reach root k from 0: `k * F[k]`
  - All elements in range require at least 1 unit of movement: `sum[i][j]`
  - Subproblems already account for internal movements
- **Time Complexity**: O(n³)
- **Space Complexity**: O(n²)

#### Part 3: Full Realistic Model

**Approach**: OBST with direction tracking for reversal penalty
- **State**: `dp[i][j][dir]` where `dir` tracks last movement direction
  - `dir = 0`: arrived from left (moving right)
  - `dir = 1`: arrived from right (moving left)
- **Cost Components**:
  - Movement: `α * distance`
  - Scanning: `β` per scan
  - Return: `α * position` to get back to 0
  - Reversal: `γ` penalty when changing direction
- **Recurrence**: For each root k in [i, j], try two orderings:
  1. Visit left subtree first, then right (incurs reversal for right subtree)
  2. Visit right subtree first, then left (incurs reversal for left subtree)
- **Reversal Penalty Application**: When robot goes left then right (or vice versa), apply γ to all subsequent movements in the new direction
- **Time Complexity**: O(n⁴) with direction tracking
- **Space Complexity**: O(n³)



### Compilation and Execution

```bash
# Compile
g++ -o Q3 2025202024_A2_Q3.cpp


