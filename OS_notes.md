#  操作系统

## 第一章：操作系统概述

**$\text{OS Kernel}$ 特征**：

- 并发：一段时间内多个程序运行（并行是一个时间点多个程序同时运行），需要进行管理和调度；

- 共享：同时访问或互斥共享；

- 虚拟：多道程序设计技术，每个用户感觉到有一台单独的计算机为其服务；

- 异步：程序分段执行，需要保证相同环境运行结果一致。

**操作系统的结构分类**：

- 单内核：如 $\text{MS-DOS}$ ，高耦合；

- 微内核：内核功能移植到用户空间，性能低；

- 外核：内核分为两部分；

- 虚拟机：位于操作系统之下、硬件之上，抽象出多个操作系统共享硬件资源。

## 第二章：中断、异常和系统调用

**操作系统的启动**：电脑通电时，$\text{POST}$ - $\text{BIOS}$ - $\text{Bootloader}$ - $\text{OS}$ （$\text{DISK} \rightarrow \text{RAM}$）。

**系统调用**：应用程序主动向操作系统发出服务请求（来源于应用程序）。

**异常**：非法指令或者其他坏的处理状态（来源于不良的应用程序）。

**中断**：来自不同的硬件设备的计时器和网络的中断（来源于外设）。

## 第三章：连续内存分配

**物理地址**：与硬件直接对应。

**逻辑地址**：程序所看见的地址空间。

**逻辑地址到物理地址的映射**：操作系统负责建立，内存管理单元（$\text{MMU}$）负责存储。

**外碎片**：分配单元间的未使用内存。

**内碎片**：分配单元内的未使用内存。

**简单的内存动态分配策略**：

- 首次适配（$\text{First Fit}$）：分配第一个可用的内存块。

- 最优适配（$\text{Best Fit}$）：分配最小的可用的内存块。

- 最差适配（$\text{Worst Fit}$）：分配最大的可用的内存块。

**碎片整理**：

- 压缩式碎片整理：重置程序以合并碎片。

- 交换时碎片整理：抢占等待的程序，暂时回收其内存。

## 第四章：非连续内存分配

**分段**：将一个地址分为段号和段内偏移，建立段表，每个表项存储段基址和段长度。

**分页**：将一个地f址分为页号和页内偏移，区别于分段，分页机制的页大小是固定的。

**帧（$\text{Frame}$）**：划分物理地址空间，物理页，由页帧号和页帧内偏移组成。

**页（$\text{Page}$）**：划分逻辑地址空间，逻辑页，由页号和页内偏移组成，页数可能多于页帧数（逻辑地址空间大于物理地址空间）。

**页表**：建立起页号和页帧号的映射关系，通过页号索引对应页帧号，每个页表项还有标志位信息。

**$\text{TLB}$**：缓存机制，利用 $\text{CPU}$ 缓存近期访问的页表项，缓解时间开销。

**多级页表**：间接访问，利用多级索引，减少需要维护的页表项，减小页表大小，缓解空间开销。

**反向页表**：利用页帧号索引，页表大小与逻辑地址空间大小相关，查找方案可用哈希函数 $h(PID, p) = f$ 。

## 第五章：虚拟内存

**手动覆盖技术**：将程序自身划分为若干个功能上相对独立的程序模块，不会同时执行的模块共享同一块内存区域。（程序内覆盖）

**自动交换技术**：将暂时不能运行的程序放到外存以获取空闲内存空间。（程序间交换）

**虚拟内存技术**：综合前两种技术，利用分段/分页机制。

**虚存技术的页表表项**：

- 物理页帧号（$\text{Frame Number}$）：逻辑页号对应的物理页帧号。

- 驻留位（$\text{Resident Bit}$）：$1$ 表示该页在内存中，$0$ 表示该页在外存中。

- 保护位：读、写、执行权限。

- 修改位（$\text{Dirty Bit}$）：$1$ 表示该页在内存中被修改过，需要写回外存，$0$ 表示内存版本与外存中的一致。

- 访问位（$\text{Used Bit}$）：标志被访问的时间/次数等，用于页面置换算法。

**缺页中断**：发生一个页面调用请求时，若找不到对应页帧，则发生一个缺页异常，由操作系统进行缺页中断处理。

## 第六章：页面置换算法

### 局部置换算法

**最佳置换算法（$\text{OPT}$）**：置换未来最久不被访问的页面。理想情况。（无法实现，可作为对比。）

**先进先出置换算法（$\text{FIFO}$）**：置换在内存驻留最长时间的页面。（$\text{Belady}$ 现象：页帧数增加，缺页次数也增加。）

**最近最久未使用算法（$\text{LRU}$）**：置换最近最久没有被使用的页面。维护开销较大。

**时钟置换算法（$\text{Clock}$）**：对 $\text{LRU}$ 的近似，仅用 $\text{used bit}$ 来体现最近访问时间，缺页中断时沿着环形链表寻找第一个 $\text{used bit}$ 为 $0$ 的页面进行置换。（指针每次移动将 $\text{used bit}$ 重置为 $0$ 。）

**二次机会置换算法（$\text{Enhanced Clock}$）**：对 $\text{Clock}$ 的改进，区分读写操作，读操作对 $\text{used bit}$ 置 $1$ ，写操作对 $\text{used bit}$ 和 $\text{dirty bit}$ 置 $1$ （$\text{dirty bit}$ 为 $1$ 时页面需要写回外存，开销较大）。缺页中断时沿着环形链表寻找第一个 $\text{used bit}$ 和 $\text{dirty bit}$ 都为 $0$ 的页面进行置换。（指针每次移动将其中一个 $\text{bit}$ 重置为 $0$ ，优先重置 $\text{used bit}$ 。）

**最不常用算法（$\text{LFU}$）**：替换最不频繁访问的页面。

### 全局置换算法

**工作集置换算法**：工作集是在某段时间间隔里，进程实际访问的页面的集合。确定工作集大小后，在每个时间点淘汰不在工作集中的页。

**缺页率置换算法**：根据缺页率动态调整工作集大小。

**抖动**：如果分配给某个进程的物理页面太少，那么会造成很多缺页中断，导致频繁的页面置换，进程的运行速度变得很慢。

平均缺页时间（$\text{MTBF}$） = 页缺失服务时间（$\text{PFST}$）时效率最高。

## 第七章：进程与线程

### 进程

**定义**：一个具有一定独立功能的程序在一个数据集合上的一次动态执行过程。

**组成**：程序的代码、程序处理的数据、程序计数器、一组通用寄存器的当前值、堆、栈、一组系统资源（如打开的文件），等等。

**特点**：动态性（动态创建和结束）、并发性、独立性、制约性（访问共享资源或进程间同步的制约）。

**与程序的区别**：程序是静态的代码，是进程产生的基础；进程是程序的执行，有核心态和用户态，组成包括程序、数据和 $\text{PCB}$ 。

**进程控制块（$\text{PCB}$）**：

- 进程标识信息：本进程标识信息（进程号等）、本进程的产生者标识信息（父进程号等）、用户标识。

- 处理机状态信息保存区：保存进程的运行现场信息。
  - 用户可见寄存器：用户程序可以使用的数据、地址等寄存器。
  - 控制和状态寄存器：如程序计数器（$\text{PC}$），程序状态字（$\text{PSW}$） 。
  - 栈指针：过程调用/系统调用/中断处理和返回时需要使用。
- 进程控制信息：
  - 调度和状态信息。
  - 进程间通信信息。
  - 存储管理信息。
  - 进程所用资源。
  - 有关数据结构连接信息。

**进程的生命周期**：

- 进程创建：
  - 系统初始化时。
  - 用户请求创建一个新进程。
  - 正在运行的进程执行了创建进程的系统调用。
- 进程运行：
  - 内核选择一个就绪的进程，让它占用处理机并执行。
- 进程等待：（由进程阻塞自己）
  - 请求并等待系统服务，无法马上完成。
  - 启动某种操作，无法马上完成。
  - 需要的数据没有到达。
- 进程唤醒：（被别的进程或操作系统唤醒）
  - 被阻塞进程需要的资源可被满足。
  - 被阻塞进程等待的事件到达。
  - 将该进程的 $\text{PCB}$ 插入到就绪队列。
- 进程结束：
  - 正常退出。
  - 错误退出。（自愿）
  - 致命错误。（强制）
  - 被其他进程所杀。

**进程状态变化模型**：

- 运行状态（$\text{Running}$）：当一个进程正在处理机上运行时。
- 就绪状态（$\text{Ready}$）：一个进程获得除了处理机外的一切所需资源，一旦得到处理机即可运行。
- 等待状态（$\text{Blocked}$）：一个进程正在等待某一事件而暂停运行，如等待资源、等待输入输出完成。
- 创建状态（$\text{New}$）：一个进程正在被创建，还没转到就绪状态之前的状态。
- 结束状态（$\text{Exit}$）：一个进程正在从系统中消失时的状态。
- 挂起状态（$\text{Suspend}$）：将进程从内存转到外存。（不占用内存空间）
  - 阻塞挂起状态（$\text{Blocked-suspend}$）：进程在外存并等待某事件的出现。
  - 就绪挂起状态（$\text{Ready-suspend}$）：进程在外存，但只要进入内存即可运行。

### 线程

**定义**：进程当中的一条执行流程。

**与进程的区别**：进程是资源分配单位，线程是调度的最小单位；进程拥有一个完整资源平台，线程独享必不可少的资源如栈和寄存器。

**线程的实现**：用户线程（用户空间使用线程库实现）、内核线程（内核中实现）、轻量级进程（在内核汇总实现，支持用户线程）。

## 第八章：CPU调度

**调度评价指标**： $\text{CPU}$ 利用率；吞吐量；周转时间；等待时间；响应时间；公平性。

**先来先服务（$\text{First Come First Served}$）**：顾名思义。

**短作业优先（$\text{Shortest Job First}$）**：非抢占式。

**短剩余时间优先（$\text{Shortest Remaining Time}$）**：抢占式，新来一个进程，若所需执行时间比当前执行的进程的短，则抢占。

**最高响应比优先（$\text{Highest Response Ratio Next}$）**：响应比 $R = \frac{w + s}{s}$ ，其中 $w$ 是等待时间，$s$ 是执行时间，等待越久越优先。

**轮询（$\text{Round Robin}$）**：设置时间片。时间片过小，上下文切换开销大；时间片过大，退化成 $\text{FCFS}$ 。

**多级反馈队列（$\text{Multilevel Feedback Queues}$）**：设置多个不同优先级的队列，分层使用 $\text{RR}$ ，高优先级时间片长，进程在高优先级队列中没有完成执行，则降到下一优先级。动态调整优先级，$\text{CPU}$ 密集型任务优先级逐次下降，优先执行 $\text{IO}$ 密集型任务。

**公平共享调度（$\text{Fair Share Scheduling}$）**：控制用户对系统资源的访问。

**优先级反转现象**：高优先级任务由于资源被低优先级任务占用，无法得到执行。（解决方法：优先级继承）

## 第九章：同步互斥问题

**临界区**（$\text{Critical Section}$）：进程中一段需要访问共享资源的代码段。

**互斥（$\text{Mutual Exclusion}$）**：当一个进程处于临界区访问共享资源时，没有其他进程会处于临界区访问该共享资源。

**同步（$\text{Synchronization}$）**：互斥基础上，对共享资源需要有序访问。

**死锁（$\text{Dead Lock}$）**：两个或以上的进程，在互相等待完成特定任务。

**饥饿（$\text{Starvation}$）**：一个可执行的进程，被调度器持续忽略，以至于处于可执行状态却不被执行。

**临界区实现方法**：

- 禁用硬件中断（只适用于单处理器）。

- 基于软件的解决方法（实现复杂），如 $\text{Peterson}$ 算法。

- 更高级的抽象方法，硬件提供一些原子操作，如 $\text{Test-and-set}$ 和 $\text{exchange}$ 指令，可以实现锁机制、信号量和管程等。

**锁机制**：用于互斥问题。包含一个二进制变量（锁定/解锁） ```value``` ，两个操作 ```Lock::Acquire()```  和 ```Lock::Release()``` 。

```cpp
// 无忙等待实现，有上下文切换开销，适用于临界区执行时间长的情况。
class Lock {
    int value = 0;
    WaitQueue q;
};
Lock::Acquire() {
    while (test-and-set(value)) {
        add this TCB to wait queue q;
        schedule();
    }
}
Lock::Release() {
    value = 0;
    remove one thread t from q;
    wakeup(t);
}
// 有忙等待实现，适用于临界区执行时间短的情况。
Lock::Acquire() {
    while (test-and-set(value)) {
        // 
    }
}
Lock::Release() {
    value = 0;
}

// 使用exchange指令也可实现互斥
int lock = 0;
{
    int key = 0;
    do {
        key = 1;
        while (key == 1)
            exchange(lock, key);
        // critical section
        lock = 0;
        // remainder section
    }
}
```

## 第十章：信号量与管程

### 信号量

同步问题和互斥问题双用途。类似于无忙等待的锁机制实现。两个原子操作 ```P()``` 和 ```V()``` 。

```cpp
class Semaphore {
    int sem;
    WaitQueue q;
};
// P操作，减小信号量
Semaphore::P() {
    --sem;
    if (sem < 0) {
        add this thread t to q;
        block(p);
    }
}
// V操作，增加信号量
Senmaphore::V() {
    ++sem;
    if (sem <= 0) { // 此前sem < 0，可唤醒某个线程
        remove a thread t from q;
        wakeup(t);
    }
}
```

**生产者-消费者模型**：

```cpp
class BoundedBuffer {
    mutex = new Semaphore(1);
    fullBuffers = new Semaphore(0);
    emptyBuffers = new Semaphore(n);
};
BoundedBuffer::Deposit(c) {
    emptyBuffers->P();
    mutex->P();
    add c to the buffer;
    mutex->V();
    fullBuffers->V();
}
BoundedBuffer::Remove(c) {
    fullBuffers->P();
    mutex->P();
    remove c from buffer;
    mutex->V();
    emptyBuffers->V();
}
```

**读者优先的读者写者问题**：

```cpp
Database::Write() {
    sem_wait(WriteMutex);
    write database;
    sem_post(WriteMutex);
}
Database::Read() {
    sem_wait(CountMutex); // 写者信号量，只能有一个读者来判定
    if (Rcount == 0) // 第一个读者阻塞所有写者
        sem_wait(WriteMutex);
    ++Rcount;
    sem_post(CountMutex);
    
    read database; // 允许多读者同时读取
    
    sem_wait(CountMutex);
    --Rcount;
    if (Rcount == 0) // 最后一个读者唤醒写者
        sem_post(WriteMutex);
    sem_post(CountMutex);
}
```

**哲学家就餐问题**：

```cpp
void philosopher(int i) {
    while (true) {
        think();
        take_forks(i);
        eat();
        put_forks(i);
    }
}
void take_forks(int i) {
    P(mutex); // state状态修改需要互斥锁
    state[i] = HUNGRY;
    test_take_left_right_forks(i);
    V(mutex);
    P(s[i]); // 若test失败，则挂起
}
void test_take_left_right_forks(int i) {
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        V(s[i]); // test成功，增加信号量
    }
}
void put_forks(int i) {
    P(mutex);
    state[i] = THINKING;
    test_take_left_right_forks(LEFT); // 尝试唤醒左右挂起的哲学家
    test_take_left_right_forks(RIGHT);
    V(mutex);
}
```

### 管程

由一个锁（控制管程代码的互斥访问）和多个条件变量组成，每个条件变量表示一种等待原因，对应一个等待队列，两种操作 ```Wait(&lock)``` 和 ```Signal()``` 。

```cpp
class Condition {
    int numWaiting = 0;
    WaitQueue q;
}
Condition::Wait(lock) {
    ++numWaiting;
    add this thread t to q;
    release(lock); // 释放互斥锁，使得其他管程代码可以访问
    shcedule(); // 调度其他线程执行
    require(lock); // 被调度时重新获得互斥锁
}
Condition::Signal() {
    if (numWaiting > 0) { // 若存在被阻塞线程
        remove a thread t from q;
        wakeup(t);
        --numWaiting;
    }
}
// 两种条件变量释放处理方式
// 1. Hansen管程唤醒线程时继续执行当前线程，容易实现。
// 2. Horare管程被唤醒的线程优先级更高，立即被调度执行，不易于实现。
```

**生产者-消费者模型**：

```cpp
class BoundedBuffer {
    Lock lock;
    int count = 0;
    Condition notFull, notEmpty;
};
BoundedBuffer::Deposit(c) {
    lock->Acquire(); // 访问管程代码需要互斥锁
    while (count == n) // Hansen管程此处需要while
        notFull.Wait(&lock);
    add c to the buffer;
    ++count;
    notEmpty.Signal();
    lock->Release();
}
BoundedBuffer::Remove(c) {
    lock->Acquire();
    while (count == 0) 
        notEmpty.Wait(&lock);
    remove c from buffer;
    --count;
    notFull.Signal();
    lock->Release();
}
```

**写者优先的读者写者问题**：

```cpp
class Database {
    int AR = 0; // active readers
    int AW = 0; // active writers
    int WR = 0; // waiting readers
    int WW = 0; // waiting writers
    Condition okToRead;
    Condition okToWrite;
    Lock lock;
};
Database::StartRead() {
    lock.Acquire();
    while (AW + WW > 0) { // 只要有写者，就block
        ++WR;
        okToRead.Wait(&lock);
        --WR;
    }
    ++AR;
    lock.Release();
}
Database::DoneRead() {
    lock.Acquire();
    --AR;
    if (AR == 0 && WW > 0) // 最后一个acitive reader结束访问并且还有写者等待，就唤醒
        okToWrite.Signal();
    lock.Release();
}
Database::Read() {
    StartRead();
    read database;
    DoneRead();
}

Database::StartWrite() {
    lock.Acquire();
    while (AW + AR > 0) {
        ++WW;
        okToWrite.Wait(&lock);
        --WW;
    }
    ++AW;
    lock.Release();
}
Database::DoneWrite() {
    lock.Acquire();
    if (WW > 0) // 写者优先唤醒
        okToWrite.Signal();
    else if (WR > 0)
        okToRead.broadcast(); // broadcast唤醒所有等待队列的线程
    lock.Release();
}
Database::Write() {
    StartWrite();
    write database;
    DoneWrite();
}
```

## 第十一章：死锁与进程通信

**死锁的四个必要条件**：

- 互斥：在一个时间只能有一个进程使用资源。
- 持有并等待：进程保持至少一个资源，正在等待获取其他进程持有的资源。
- 无抢占：一个资源只能被进程完成任务后自愿释放。
- 循环等待：一组进程循环等待资源。

**死锁处理**：确保不会发生死锁；允许发生死锁，然后恢复；鸵鸟算法，忽略死锁问题（常用）。

- 死锁预防：打破死锁的四个条件之一，确保不会发生死锁。
  - 互斥：让资源不互斥。
  - 持有并等待：分配资源时，给进程分配最大数量的资源，使其不需要等待。
  - 无抢占：进程需要资源时进行抢占。
  - 循环等待：资源按进程申请顺序依次分配。
- 死锁避免：条件放松，在分配资源时动态判断是否可能出现死锁，若分配后进入非安全状态则拒绝分配。
  - 安全状态（$\text{Safe State}$）：针对所有进程，存在一种执行序列使得不出现死锁。
  - 非安全状态（$\text{Unsafe State}$）：处于非安全状态不一定发生死锁，但发生死锁时一定处于非安全状态。
  - 银行家算法（$\text{Banker's Algorithm}$）：判断当前是否处于安全状态，贪心执行进程并回收资源，若全部执行完则为安全状态。
- 死锁检测：相对于死锁避免，死锁检测仅判断当前是否出现死锁，若是则启动恢复机制，定期检测。
  - 资源单一的死锁检测：基于资源分配图，查找环，有环则可能存在死锁。
  - 死锁检测算法：类似银行家算法，判断当前是否处于非安全状态，若是则可能存在死锁。
- 死锁恢复：
  - 终止所有死锁进程。
  - 按某种顺序终止进程直到死锁消除。

**进程间通信（$\text{IPC}$）**：直接/间接通信，同步/异步通信。

- 信号：通过软件中断通知事件，接收方收到信号后执行指定的信号处理函数，由操作系统修改栈指针实现。
- 管道：重定向进程输入输出，实现数据交换，但只是字节流数据，并且需要父进程为子进程间通信建立管道。
- 消息队列：通过一个消息队列传输结构化数据，可以在多个互不相关的进程间进行。
- 共享内存：直接通信，设置共享内存段，最高效，但需要程序员自己进行实现同步机制。

## 第十二章：文件系统

**卷控制块（$\text{superblock}$）**：每个文件系统都有一个总控制块。

**文件控制块（$\text{vnode/inode}$）**：每个具体的文件都有一个文件控制块，存储元数据。

**目录节点（$\text{dentry}$）**：每个目录项一个，指向文件控制块。

**多级索引**：文件控制块不存放具体内容，而是存放具体文件内容所在的 $\text{block}$ 的一级或多级索引。

**多磁盘管理 - $\text{RAID}$** ：多个磁盘阵列提高磁盘访问效率（并行）。

**磁盘调度**：寻道时间是瓶颈，需要调度不同磁道的 $\text{IO}$ 请求：

- $\text{FIFO}$ ：先来先处理。
- $\text{SCAN}$ ：类似电梯，双向扫描处理。
- $\text{CSCAN}$ ：每次重置磁臂，单向扫描。
- $\text{FSCAN}$ ：双队列，扫描处理现有 $\text{IO}$ 请求时，新的 $\text{IO}$ 请求放到另一队列下次处理，避免磁臂粘着（$\text{arm stickness}$） 。