# CSE4001 – Thread Synchronization (`cse4001_sync`)

This program implements four classic synchronization problems using POSIX threads and semaphores, based on solutions from **The Little Book of Semaphores** by Allen B. Downey.

## Problems

1. **No-starve readers–writers (Problem 1)**  
   - 5 reader threads, 5 writer threads  
   - Uses a readers’ lightswitch, a `roomEmpty` semaphore, and a `turnstile` semaphore  
   - Guarantees that neither readers nor writers starve  

2. **Writer-priority readers–writers (Problem 2)**  
   - 5 readers, 5 writers  
   - Uses `readTry`, `roomEmpty`, and counters for readers/writers  
   - When a writer is waiting, new readers are blocked until writers finish  

3. **Dining philosophers #1 – footman / multiplex (Problem 3)**  
   - 5 philosophers  
   - A `footman` semaphore initialized to 4 limits the number of philosophers at the table  
   - Prevents deadlock by ensuring not all philosophers can grab one fork at the same time  

4. **Dining philosophers #2 – lefty/righty (Problem 4)**  
   - 5 philosophers  
   - Breaks circular wait by having philosophers pick up forks in different orders (even vs odd IDs)  
   - No footman needed; still avoids deadlock  

Each thread prints messages such as:

- `"[P1] Reader 0: reading"`  
- `"[P2] Writer 3: writing"`  
- `"[P3] Philosopher 2: eating"`  
- `"[P4] Philosopher 4: thinking"`

so the behavior of the synchronization can be observed.

## Build instructions

From the project directory:

```bash
make
## Screenshots

### Problem 1 – No-starve Readers–Writers

Start:

![Problem 1 start](1%20start.png)

Complete:

![Problem 1 complete](1%20complete.png)

---

### Problem 2 – Writer-Priority Readers–Writers

Start:

![Problem 2 start](2%20start.png)

Complete:

![Problem 2 complete](2%20complete.png)

---

### Problem 3 – Dining Philosophers #1 (Footman)

Start:

![Problem 3 start](3%20start.png)

Complete:

![Problem 3 complete](3%20complete.png)

---

### Problem 4 – Dining Philosophers #2 (Lefty/Righty)

Start:

![Problem 4 start](4%20start.png)

Complete:

![Problem 4 complete](4%20complete.png)
