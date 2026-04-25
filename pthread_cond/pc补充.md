学习日志 — 线程池雏形（2026-04-25）

今日目标：
从生产者消费者模型升级到简单线程池，理解任务封装、worker 执行逻辑和线程退出机制。

核心内容
Task 结构体：打包任务函数 + 参数
add_task：提交任务，队列满则等待，队列不满则 push 并唤醒 worker
worker：队列空就等，有任务就 pop 执行，shutdown 后队列空退出
shutdown：控制线程池关闭，main 提交完任务后设置并唤醒所有 worker
main 流程
创建 worker 线程
循环提交任务 add_task(print_task, num)
提交完任务后设置 shutdown=1，pthread_cond_broadcast(&not_empty)
join 所有 worker
学习收获
完成了生产者消费者到线程池的迁移
理解函数指针 + void* 参数任务封装
理解锁和条件变量在任务提交和执行中的作用
初步掌握线程池 shutdown 控制逻辑