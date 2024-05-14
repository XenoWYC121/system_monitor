//
// Created by fsy on 24-5-14.
//

#include "server/sync_grpc_server.h"
#include <grpcpp/grpcpp.h>

namespace system_monitor::server
{
    sync_grpc_server::sync_grpc_server()
        : cpu_client(CreateChannel("127.0.0.1:25001", grpc::InsecureChannelCredentials())),
          memory_client(CreateChannel("127.0.0.1:25002", grpc::InsecureChannelCredentials()))
    {
    }

    grpc::Status sync_grpc_server::get_sys_info(
        grpc::ServerContext *context,
        const system_monitor::monitor::sys_info_request *request,
        system_monitor::monitor::sys_info_response *response)
    {
        if (request->get_cpu_info())
        {
            response->mutable_cpu_info()->CopyFrom(this->cpu_client.call());
        }
        if (request->get_memory_info())
        {
            response->mutable_memory_info()->CopyFrom(this->memory_client.call());
        }
        return grpc::Status::OK;
    }

    void sync_grpc_server::run_server(const std::string &url)
    {
        using namespace std;
        sync_grpc_server service;
        grpc::ServerBuilder builder;
        builder.AddListeningPort(url, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        auto server(builder.BuildAndStart());
        server->Wait();
    }
}
