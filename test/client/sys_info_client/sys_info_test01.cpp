//
// Created by fsy on 24-5-15.
//
#include <iostream>
#include <unistd.h>
#include <gtest/gtest.h>
#include <grpcpp/grpcpp.h>
#include "client/sys_info_client/sys_info_client.h"

TEST(sys_info_client, test01)
{
    auto newChannel = grpc::CreateChannel("127.0.0.1:25000", grpc::InsecureChannelCredentials());
    system_monitor::client::sys_info_client client(newChannel);
    ASSERT_THROW(client.call(true,true), std::runtime_error);
}

TEST(sys_info_client, test02)
{
    using namespace std;
    pid_t current_pid = getpid();
    int fd[2]{};
    pipe(fd);
    fork();
    fork();
    if (getpid() == current_pid)
    {
        // father
        cout << "father pid : " << getpid() << endl;
        close(fd[1]);
        for (int i = 0; i < 3; i++)
        {
            pid_t child{};
            read(fd[0], &child, sizeof(child));
            cout << "father get pid from child : " << child << endl;
        }
    }
    else
    {
        // child
        close(fd[0]);
        pid_t pid = getpid();
        write(fd[1], &pid, sizeof(pid));
        cout << "child pid : " << getpid() << endl;
    }
}
