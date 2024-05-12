//
// Created by fsy on 24-5-12.
//

#ifndef CPU_USAGE_CLIENT_H
#define CPU_USAGE_CLIENT_H

#include "cpu_usage_info.grpc.pb.h"
#include "cpu_usage_info.pb.h"

#include <memory>

namespace system_monitor::client
{
    using namespace std;

    class cpu_usage_client final
    {
    public:
        explicit cpu_usage_client(const std::shared_ptr<grpc::Channel>& channel);

        monitor::all_cpu_usage call() const;

    private:
        unique_ptr<monitor::get_cpu_usage::Stub> m_stub;
    };
}

#endif //CPU_USAGE_CLIENT_H
