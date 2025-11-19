# CSE4001 – Thread Synchronization (cse4001_sync)

This program implements four classic synchronization problems using POSIX threads and semaphores, based on solutions from The Little Book of Semaphores by Allen B. Downey.

------------------------------------------------------------

## Problem 1 – No-Starve Readers–Writers

5 readers, 5 writers.
Uses: lightswitch, roomEmpty, turnstile.
Guarantees no starvation.

Problem 1 – Start Screenshot:
![Problem 1 start](1%20start.png)

Problem 1 – Complete Screenshot:
![Problem 1 complete](1%20complete.png)

------------------------------------------------------------

## Problem 2 – Writer-Priority Readers–Writers

5 readers, 5 writers.
Uses: readTry, roomEmpty, rmutex, wmutex.
Writers have priority, readers pause when writer is waiting.

Problem 2 – Start Screenshot:
![Problem 2 start](2%20start.png)

Problem 2 – Complete Screenshot:
![Problem 2 complete](2%20complete.png)

------------------------------------------------------------

## Problem 3 – Dining Philosophers #1 (Footman / Multiplex)

5 philosophers.
Footman semaphore = 4 prevents deadlock.

Problem 3 – Start Screenshot:
![Problem 3 start](3%20start.png)

Problem 3 – Complete Screenshot:
![Problem 3 complete](3%20complete.png)

------------------------------------------------------------

## Problem 4 – Dining Philosophers #2 (Lefty/Righty)

5 philosophers.
Even philosophers pick forks in one order; odd philosophers pick the opposite order.
Breaks circular wait → no deadlock.

Problem 4 – Start Screenshot:
![Problem 4 start](4%20start.png)

Problem 4 – Complete Screenshot:
![Problem 4 complete](4%20complete.png)

------------------------------------------------------------

## Build Instructions

Inside the project directory:

make

------------------------------------------------------------

## Run Instructions

./cse4001_sync 1
./cse4001_sync 2
./cse4001_sync 3
./cse4001_sync 4
