//
// Created by fsy on 24-5-12.
//
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <future>
#include <thread>
#include "cpu_usage_info.grpc.pb.h"
#include "cpu_usage_info.pb.h"
#include "gtest/gtest.h"
#include "client/cpu_usage_client/cpu_usage_client.h"

TEST(client, cpu_usage_test01)
{
    auto channel = grpc::CreateChannel("127.0.0.1:25001", grpc::InsecureChannelCredentials());
    system_monitor::client::cpu_usage_client client1(channel);
    ASSERT_THROW(auto res = client1.call(), std::runtime_error);
}

TEST(client, cpu_usage_test02)
{
    using namespace std;
    //cout << CPU_SERVICE_PATH << endl;
    pid_t pid = fork();
    ASSERT_NE(pid, -1);
    if (pid == 0)
    {
        // child
        execl(CPU_SERVICE_PATH, "cpu_service", nullptr);
    }
    else
    {
        // father
        auto res = std::async(launch::async, [pid]()
        {
            this_thread::sleep_for(2s);
            kill(pid,SIGKILL);
        });
        this_thread::sleep_for(500ms);
        auto channel = grpc::CreateChannel("127.0.0.1:25001", grpc::InsecureChannelCredentials());
        system_monitor::client::cpu_usage_client client1(channel);
        ASSERT_NO_THROW(auto res2 = client1.call());
        auto res3 = client1.call();
        for (int i = 0; i < res3.list_size(); i++)
        {
            decltype(auto) obj = res3.list(i);
            cout << obj.cpu_name() << '\t'
                    << obj.total_usage() << '\t'
                    << obj.system_usage() << '\t'
                    << obj.user_usage() << endl;
        }
        res.get();
    }
}
