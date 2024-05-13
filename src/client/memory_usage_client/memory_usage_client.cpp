//
// Created by fsy on 24-5-13.
//

#include "client/memory_usage_client/memory_usage_client.h"
#include <grpcpp/grpcpp.h>

namespace system_monitor::client
{
    memory_usage_client::memory_usage_client(const std::shared_ptr<grpc::Channel> &channel)
        : m_stub(monitor::get_memory_usage::NewStub(channel))
    {
    }

    monitor::memory_usage memory_usage_client::call()
    {
        monitor::memory_request req{};
        monitor::memory_usage resp{};
        grpc::ClientContext context{};
        grpc::Status status = this->m_stub->get_usage(&context, req, &resp);
        if (status.ok())
        {
            return resp;
        }
        else
        {
            throw std::runtime_error(status.error_message());
        }
    }
}
