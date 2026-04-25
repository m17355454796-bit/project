今天继续学习 Linux 多线程中的条件变量，重点完成了生产者消费者模型。

一开始先用一个消费者线程测试 pthread_cond_wait。当 size == 0 时，消费者进入等待状态，并且程序卡住，说明消费者确实在等待 not_empty 条件。随后加入生产者线程，让生产者修改 size 并调用 pthread_cond_signal 唤醒消费者，验证了 wait 会释放锁、被唤醒后重新抢锁再继续执行。

后面把简单的 size 变化升级成 queue 数组，封装了 push 和 pop，并加入 head、tail 和取模操作，实现了循环队列。随后加入 not_full 条件变量，让生产者在队列满时等待，消费者消费数据后通过 pthread_cond_signal(&not_full) 唤醒生产者。

今天最重要的理解是：mutex 负责保护共享资源，condition variable 负责线程在条件不满足时等待和被唤醒。pthread_cond_wait 必须配合 mutex 使用，并且判断条件要用 while，不能用 if。生产者每次 push 前都要检查队列是否满，消费者每次 pop 前都要检查队列是否空，不能只在循环外检查一次。
