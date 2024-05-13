//
// Created by fsy on 24-5-13.
//

#include "service/memory_service/memory_service.h"
#include <grpcpp/grpcpp.h>

namespace system_monitor::service
{
    grpc::Status memory_service::get_usage(grpc::ServerContext *context,
                                           const system_monitor::monitor::memory_request *request,
                                           system_monitor::monitor::memory_usage *response)
    {
        response->set_free_ram(static_cast<int>(this->m_monitor->get_free_ram()));
        response->set_total_ram(static_cast<int>(this->m_monitor->get_total_ram()));
        return grpc::OK();
    }

    void memory_service::run_server(const std::string& url)
    {
        using namespace std;
        memory_service service;
        grpc::ServerBuilder builder;
        builder.AddListeningPort(url, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        auto server(builder.BuildAndStart());
        server->Wait();
    }
}
