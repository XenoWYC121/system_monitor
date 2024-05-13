//
// Created by fsy on 24-5-13.
//

#include "service/memory_service/memory_service.h"

#include <gtest/gtest.h>
#include <grpcpp/grpcpp.h>

#include <iostream>
#include <future>
#include <thread>

#include "client/cpu_usage_client/cpu_usage_client.h"
#include "client/memory_usage_client/memory_usage_client.h"

TEST(memory_client, test01)
{
    using namespace system_monitor::client;
    auto channel = grpc::CreateChannel("127.0.0.1:25001", grpc::InsecureChannelCredentials());
    memory_usage_client client1(channel);
    ASSERT_THROW(client1.call(), runtime_error);
}

TEST(memory_client, test02)
{
    using namespace std;
    pid_t pid = fork();
    ASSERT_NE(pid, -1);
    if (pid == 0)
    {
        // child
        execl(MEMORY_SERVICE_PATH, "memory_service", nullptr);
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
        auto channel = grpc::CreateChannel("127.0.0.1:25002", grpc::InsecureChannelCredentials());
        system_monitor::client::memory_usage_client client1(channel);
        ASSERT_NO_THROW(auto res2 = client1.call());
        auto res3 = client1.call();
        cout << "total : "<<res3.total_ram() << "\tused : "
                << res3.total_ram() - res3.free_ram() << "\tunused : "
                << res3.free_ram() << endl;
        res.get();
    }
}
