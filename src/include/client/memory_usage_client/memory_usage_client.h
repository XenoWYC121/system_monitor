//
// Created by fsy on 24-5-13.
//

#ifndef MEMORY_USAGE_CLIENT_H
#define MEMORY_USAGE_CLIENT_H

#include "memory_usage.grpc.pb.h"
#include "memory_usage.pb.h"

namespace system_monitor::client
{
    class memory_usage_client
    {
    public:
        explicit memory_usage_client(const std::shared_ptr<grpc::Channel>& channel);

        monitor::memory_usage call();
    private:
        std::unique_ptr<monitor::get_memory_usage::Stub> m_stub;
    };
}

#endif //MEMORY_USAGE_CLIENT_H
