# CSE4001 – Thread Synchronization (cse4001_sync)

This program implements four classic synchronization problems using POSIX threads and semaphores, based on solutions from The Little Book of Semaphores by Allen B. Downey.

------------------------------------------------------------

## Problem 1 – No-Starve Readers–Writers

5 readers, 5 writers.
Uses: lightswitch, roomEmpty, turnstile.
Guarantees no starvation.

Problem 1 – Start Screenshot:
C:\Users\nevai\OneDrive\Masaüstü\Florida Tech\Junior Year\CSE4001\Assignment 5\1 start.png

Problem 1 – Complete Screenshot:
C:\Users\nevai\OneDrive\Masaüstü\Florida Tech\Junior Year\CSE4001\Assignment 5\1 complete.png

------------------------------------------------------------

## Problem 2 – Writer-Priority Readers–Writers

5 readers, 5 writers.
Uses: readTry, roomEmpty, rmutex, wmutex.
Writers have priority, readers pause when writer is waiting.

Problem 2 – Start Screenshot:
C:\Users\nevai\OneDrive\Masaüstü\Florida Tech\Junior Year\CSE4001\Assignment 5\2 start.png

Problem 2 – Complete Screenshot:
C:\Users\nevai\OneDrive\Masaüstü\Florida Tech\Junior Year\CSE4001\Assignment 5\2 complete.png

------------------------------------------------------------

## Problem 3 – Dining Philosophers #1 (Footman / Multiplex)

5 philosophers.
Footman semaphore = 4 prevents deadlock.

Problem 3 – Start Screenshot:
C:\Users\nevai\OneDrive\Masaüstü\Florida Tech\Junior Year\CSE4001\Assignment 5\3 start.png

Problem 3 – Complete Screenshot:
C:\Users\nevai\OneDrive\Masaüstü\Florida Tech\Junior Year\CSE4001\Assignment 5\3 complete.png

------------------------------------------------------------

## Problem 4 – Dining Philosophers #2 (Lefty/Righty)

5 philosophers.
Even philosophers pick forks in one order; odd philosophers pick the opposite order.
Breaks circular wait → no deadlock.

Problem 4 – Start Screenshot:
C:\Users\nevai\OneDrive\Masaüstü\Florida Tech\Junior Year\CSE4001\Assignment 5\4 start.png

Problem 4 – Complete Screenshot:
C:\Users\nevai\OneDrive\Masaüstü\Florida Tech\Junior Year\CSE4001\Assignment 5\4 complete.png

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
