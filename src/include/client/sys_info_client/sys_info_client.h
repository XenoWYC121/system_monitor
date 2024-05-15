//
// Created by fsy on 24-5-15.
//

#ifndef GRPC_CLIENT_H
#define GRPC_CLIENT_H

#include "sys_info.grpc.pb.h"
#include "sys_info.pb.h"

namespace system_monitor::client
{
    class sys_info_client
    {
    public:
        explicit sys_info_client(const std::shared_ptr<grpc::Channel> &channel);

        monitor::sys_info_response call(bool get_cpu_info, bool get_mem_info);

    private:
        std::unique_ptr<monitor::sys_info_service::Stub> m_stub;
    };
}

#endif //GRPC_CLIENT_H
