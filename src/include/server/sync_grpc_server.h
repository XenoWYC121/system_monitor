//
// Created by fsy on 24-5-14.
//

#ifndef SYNC_GRPC_SERVER_H
#define SYNC_GRPC_SERVER_H

#include "client/cpu_usage_client/cpu_usage_client.h"
#include "client/memory_usage_client/memory_usage_client.h"

#include "sys_info.grpc.pb.h"
#include "sys_info.pb.h"

namespace system_monitor::server
{
    class sync_grpc_server final
            : public monitor::sys_info_service::Service
    {
    public:
        sync_grpc_server();

        grpc::Status get_sys_info(grpc::ServerContext *context,
                                  const system_monitor::monitor::sys_info_request *request,
                                  system_monitor::monitor::sys_info_response *response) override;

        static void run_server(const std::string &url);

    private:
        client::cpu_usage_client cpu_client;
        client::memory_usage_client memory_client;
    };
}

#endif
