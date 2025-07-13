auto items = 0, space = 10, mutex = 1;
var in = 0, out = 0;
item buf[10] = { NULL };

producer {
    while(true) {
        wait(sapce); // 等待缓冲区有空闲位置，在使用 PV 操作时，条件变量需要在互斥锁之前
        wait(mutex); // 保证不会有其他线程访问缓冲区

        /* 生产 */
        buf[in] = item; // 将新资源放到buf[in]位置 
        in = (in + 1) % 10;

        signal(mutex); // 唤醒的顺序可以不同
        signal(items); // 通知consumer缓冲区有资源可以取走
    }
}

consumer {
    while(true) {
        wait(items); // 等待缓冲区资源
        wait(mutex);

        /* 消费 */
        item get_ = buf[out];
        out = (out + 1) % 10;

        signal(mutex);
        signal(space);
    }
}

