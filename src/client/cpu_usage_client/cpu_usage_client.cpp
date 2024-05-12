//
// Created by fsy on 24-5-12.
//

#include "client/cpu_usage_client/cpu_usage_client.h"
#include "grpcpp/grpcpp.h"

namespace system_monitor::client
{
    cpu_usage_client::cpu_usage_client(const std::shared_ptr<grpc::Channel> &channel)
        : m_stub(monitor::get_cpu_usage::NewStub(channel))
    {
    }

    monitor::all_cpu_usage cpu_usage_client::call() const
    {
        monitor::cpu_request req{};
        monitor::all_cpu_usage resp{};
        grpc::ClientContext context{};
        grpc::Status status = this->m_stub->get_usage(&context, req, &resp);
        if(status.ok())
        {
            return resp;
        }
        else
        {
            throw runtime_error(status.error_message());
        }
    }
}
