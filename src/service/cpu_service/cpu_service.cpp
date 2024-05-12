//
// Created by 12992 on 24-5-10.
//

#include "service/cpu_service/cpu_service.h"
#include "cpu_usage_info.pb.h"
#include "grpcpp/grpcpp.h"

namespace system_monitor::service
{
    grpc::Status
    cpu_service::get_usage(::grpc::ServerContext* context, const ::system_monitor::monitor::cpu_request* request,
                           ::system_monitor::monitor::all_cpu_usage* response)
    {
        for (const auto& [key, value]: this->m_ptr->get_cpu_usage())
        {
            monitor::cpu_usage_info* temp_info = response->add_list();
            temp_info->set_cpu_name(key);
            temp_info->set_system_usage(value.get_system_usage());
            temp_info->set_total_usage(value.get_usage());
            temp_info->set_user_usage(value.get_user_usage());
        }
        return grpc::Status::OK;
    }

    void cpu_service::run_server(const std::string& url)
    {
        using namespace std;
        cpu_service service;
        grpc::ServerBuilder builder;
        builder.AddListeningPort(url, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        auto server(builder.BuildAndStart());
        server->Wait();
    }
}