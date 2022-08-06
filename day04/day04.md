###1.What is the difference between a Task, Process and thread?

#Thread:
* Thread has its own program area and memory area .
* A thread is a basic unit of CPU utilization , consisting of a program counter, a stack, and a set of registers.
* A thread of execution is the smallest sequence of programmed instructions that can be managed independently by a scheduler.

#Task:
* A task is something you want done. It is a set of program instructions that are loaded in memory .
* When program instruction is loaded into memory people do call as process or task.

#Process:
* Process-based multitasking enables you to run the Java compiler at the same time that you are using a text editor. 
* In employing multiple processes with a single CPU,context switching between various memory context is used. 
* Each process has a complete set of its own variables.
* A process is an instance of a computer program that is being executed. 
* It contains the program code and its current activity. 
* Depending on the operating system (OS), a process may be made up of multiple threads of execution that execute instruct   ions concurrently. 




###2.How threads communicate with each other?

* Inter-thread communication involves the communication of threads with each other. 
* The three methods that are used to implement inter-thread communication in Java
    * wait().
    * notify().
    * notifyAll().

# wait():
* This method causes the current thread to release the lock. 
* This is done until a specific amount of time has passed or another thread calls the notify() or notifyAll() method for    this object.

#notify():
* This method wakes a single thread out of multiple threads on the current object’s monitor. The choice of thread is arbi   trary.

#notifyAll():
* This method wakes up all the threads that are on the current object’s monitor.




### 4. What is Critical section, deadlocks, race around condition are problems that happen in thread synchronization?

#Critical Section:
* The critical section in a code segment where the shared variables can be accessed.
* Atomic action is required in a critical section i.e. only one process can execute in its critical section at a time. 
* All the other processes have to wait to execute in their critical sections.

* The critical section problem needs a solution to synchronise the different processes. 
* The solution to the critical section problem must satisfy the following conditions −

#Mutual Exclusion:
* Mutual exclusion implies that only one process can be inside the critical section at any time. 
* If any other processes require the critical section, they must wait until it is free.Progresss:
* Progress means that if a process is not using the critical section, then it should not stop any other process from accessing it. 
* In other words, any process can enter a critical section if it is free.
    
#Bounded Waitings:
* Bounded waiting means that each process must have a limited waiting time. 
* It should not wait endlessly to access the critical section.

#Deadlock:
* A deadlock occurs when two threads each lock a different variable at the same time and then try to lock the variable th   at the other thread already locked. 
* As a result, each thread stops executing and waits for the other thread to release the variable. 
* Because each thread is holding the variable that the other thread wants, nothing occurs, and the threads remain deadlocked.



#Race Condition:
* A race condition is a situation that may occur inside a critical section. 
* This happens when the result of multiple thread execution in critical section differs according to the order in which 
* the threads execute.

* Race conditions in critical sections can be avoided if the critical section is treated as an atomic instruction. 
* Also, proper thread synchronization using locks or atomic variables can prevent race conditions.

