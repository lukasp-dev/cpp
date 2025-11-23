## Process vs Thread

### **Process**
- An independent program in execution.
- Has its **own memory space** (Code, Data, Heap, Stack).
- Processes **do not share memory** with each other by default.
- Context switching is **expensive**.
- A crash in one process **does not affect** others.

### **Thread**
- A single flow of execution within a process.
- Threads **share the same memory** of the parent process (Code, Data, Heap).
- Each thread has its **own Stack**.
- Context switching is **lightweight**.
- A crash in one thread can **affect the entire process**.

### **Key Differences**

| Category | Process | Thread |
|----------|---------|--------|
| Memory | Independent | Shared within process |
| Stack | One per process | One per thread |
| Creation Cost | High | Low |
| Context Switch | Heavy | Light |
| Failure Impact | Isolated | Affects entire process |

### **Quick Analogy**
- **Process = a house**
- **Thread = people inside the same house**  
  They share the house (memory), but each has their own room (stack).

## User-level threads
![Image](https://img.notionusercontent.com/s3/prod-files-secure%2F47d0f1a5-2bc8-4793-8739-b93c68e8d157%2F42d5b86a-370d-431d-800d-1b7393481816%2Fimage.png/size/w=2000?exp=1763873341&sig=Oy34PFx7NWosaKt8E2qnvA3RAWxJHKvZ2M94y7dHFQI&id=2b4a96ff-12e6-80c0-bfbd-c0e79f5be2ad&table=block&userId=da23ca2d-c48f-4dec-bf37-0ac08848eb83)
- OS independent, Thread library part of application runtime, Thread switching is cheap.
- Each process has its own threads library in user space.
- The kernel only schedules processes, not individual threads.
- If one thread performs I/O, the kernel blocks the whole process. As a result, all threads in that process stop running.
- User-level threads can't run in parallel even on multi-core CPUs because the OS only schedules the whole process. They're mainly useful as a structuring tool inside user programs.
- yield control voluntarily, or use timer interrupts to switch automatically.

### OS support for user-level threads blocking calls
![image](https://img.notionusercontent.com/s3/prod-files-secure%2F47d0f1a5-2bc8-4793-8739-b93c68e8d157%2Fdbf26ff2-6c2b-4754-8ccd-e17c63ff57ec%2Fimage.png/size/w=2000?exp=1763874639&sig=0xCmgXCvODZB_M7mIbXunzcGmHxLz77a5b3PwolhUG0&id=2b4a96ff-12e6-8084-a705-e8cc412efa87&table=block&userId=da23ca2d-c48f-4dec-bf37-0ac08848eb83)
- 스레드가 블로킹 호출을 하면 OS가 upcall 핸들러를 호출해 작업이 완료되면 알려주겠다고 알림.

### Kernel-level threads
- The norm in most modern operating systems