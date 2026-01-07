#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* 1. 共享性: 共享的全局数据 */
int shared_counter = 0;
pthread_mutex_t lock;

// 持久性：写入文件
void save_to_file(const char *message) {
    FILE *file = fopen("output.log", "a");
    if (file) {
        fprintf(file, "%s\n", message);
        fclose(file);
    }
}


// 异步性：模拟耗时的任务
void async_task(int id) {
    printf("任务 %d 开始(异步执行)\n", id);

    // 模拟异步延迟
    for (int i = 1; i <= 3; i++) {
        sleep(1);
        printf("任务 %d: 步骤 %d\n", id, i);
    }

    // 访问共享资源
    pthread_mutex_lock(&lock);
    shared_counter++;
    printf("任务 %d 完成，共享计数器：%d\n", id, shared_counter);
    pthread_mutex_unlock(&lock);

    // 待久化结果
    char msg[100];
    sprintf(msg, "任务 %d 完成于计数器值：%d", id, shared_counter);
    save_to_file(msg);
}

// 并发性：线程函数
void *thread_function(void *arg) {
    int id = *(int*)arg;

    free(arg);  // 释放动态分配的内存

    async_task(id);

    return NULL;
}

int main() {
    // 开始
    printf("开始\n");

    pthread_mutex_init(&lock, NULL);

    // 清理旧日志文件
    remove("output.log");

    // 创建多个线程，体现并发性
    pthread_t threads[3];

    printf("启动3个线程...\n");

    for (int i = 0; i < 3; i++) {
        // 动态分配线程id
        int *id = malloc(sizeof(int));

        *id = i + 1;
        
        // 创建线程
        pthread_create(&threads[i], NULL, thread_function, id);

    }

    // 主线程也执行一些工作
    printf("主线程正在执行其他工作...\n");
    sleep(2);  // 模拟主线程工作
    printf("主线程工作完成\n");

    // 等待所有线程完成
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    // 显示最终结果
    printf("\n最终共享计数器值：%d\n", shared_counter);
    printf("检查output.log 文件，查看持久化结果\n");

    // 清理
    pthread_mutex_destroy(&lock);

    return 0;
}
