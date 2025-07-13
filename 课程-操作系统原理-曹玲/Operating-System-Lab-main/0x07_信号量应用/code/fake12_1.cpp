semaphore waiting_room = 20;  // 候诊室剩余座位
semaphore patients_ready = 0; // 准备就诊的病人数
semaphore mutex = 1;          // 临界区互斥锁
semaphore doctor = 3;         // 医生空闲资源

void patient() {
    wait(waiting_room);       // 等待候诊区有空位
    wait(mutex);              // 进入临界区

    // 病人进入候诊室
    print("Patient entered waiting room");

    signal(patients_ready);   // 通知医生病人准备就诊
    signal(mutex);            // 离开临界区

    wait(doctor);             // 等待医生空闲

    // 病人正在看病
    print("Patient is seeing the doctor");
    signal(waiting_room);     // 离开候诊室

    return;
}

void doctor() {
    while (true) {            // 医生不断工作
        wait(patients_ready); // 等待病人准备
        wait(mutex);          // 进入临界区

        // 医生呼叫病人
        print("Doctor is calling a patient");
        signal(mutex);        // 离开临界区

        // 医生正在看病
        print("Doctor is seeing a patient");
        sleep(1);             // 模拟看病时间

        signal(doctor);       // 医生空闲资源增加
    }

    return;
}


