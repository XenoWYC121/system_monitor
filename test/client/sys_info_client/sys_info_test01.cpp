//
// Created by fsy on 24-5-15.
//

#include "client/sys_info_client/sys_info_client.h"
#include "cpu_usage_info.pb.h"
#include "memory_usage.pb.h"
#include <gtest/gtest.h>
#include <grpcpp/grpcpp.h>

#include <iostream>

#include <semaphore.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <unistd.h>


TEST(sys_info_client, test01)
{
    auto newChannel = grpc::CreateChannel("127.0.0.1:25000", grpc::InsecureChannelCredentials());
    system_monitor::client::sys_info_client client(newChannel);
    ASSERT_THROW(client.call(true,true), std::runtime_error);
}

TEST(sys_info_client, test02)
{
    using namespace std;
    const int shm_fd = shm_open("sys_info_test",O_CREAT | O_RDWR, 0644);
    auto sem_object = sem_open("sys_info_sem",O_CREAT | O_RDWR, 0644);
    ASSERT_NE(shm_fd, -1);
    ASSERT_NE(sem_object, nullptr);
    ftruncate(shm_fd, sizeof(int));
    int *const ptr = static_cast<int *>(mmap(nullptr, sizeof(int),PROT_READ | PROT_WRITE,MAP_SHARED, shm_fd, 0));
    ASSERT_NE(ptr, nullptr);
    *ptr = 0;
    const pid_t current_pid = getpid();
    int pipe_fd[2]{};
    int res = pipe(pipe_fd); //1 write,0 read
    ASSERT_NE(res, -1);
    fork();
    fork();
    if (getpid() == current_pid)
    {
        // father read, so close write
        close(pipe_fd[1]);
        // father
        for (int i = 0; i < 3; i++)
        {
            pid_t child_pid{};
            read(pipe_fd[0], &child_pid, sizeof(child_pid));
            cout << "father get child pid : " << child_pid << endl;
        }

        sleep(1);
        auto channel = grpc::CreateChannel("127.0.0.1:25000", grpc::InsecureChannelCredentials());
        system_monitor::client::sys_info_client client(channel);
        ASSERT_NO_THROW(client.call(true,true));
        auto res2 = client.call(true, true);
        ASSERT_TRUE(res2.has_cpu_info() && res2.has_memory_info());
        for (const auto &cpu_info: res2.cpu_info().list())
        {
            cout << cpu_info.cpu_name() << '\t' << cpu_info.total_usage() << '\t' << cpu_info.system_usage() << '\t' <<
                    cpu_info.user_usage() << endl;
        }
        cout << res2.memory_info().total_ram() << '\t' << res2.memory_info().free_ram() << endl;
    }
    else
    {
        //child write, so close read
        close(pipe_fd[0]);
        // child
        const pid_t child_pid = getpid();
        write(pipe_fd[1], &child_pid, sizeof(child_pid));
        sem_wait(sem_object);
        const int current_value = *ptr;
        (*ptr)++;
        sem_post(sem_object);
        cout << "child process " << getpid() << " get current shm : " << current_value << endl;
        if (current_value == 0)
        {
            execl(CPU_SERVICE_PATH, "cpu_service", nullptr);
        }
        else if (current_value == 1)
        {
            execl(MEMORY_SERVICE_PATH, "memory_service", nullptr);
        }
        else if (current_value == 2)
        {
            execl(SERVER_PATH, "grpc_server", nullptr);
        }
    }

    sem_close(sem_object);
    sem_unlink("sys_info_sem");
    close(shm_fd);
    shm_unlink("sys_info_test");
}
