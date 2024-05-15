//
// Created by fsy on 24-5-15.
//

#include "client/sys_info_client/sys_info_client.h"
#include "grpcpp/grpcpp.h"

namespace system_monitor::client
{
    sys_info_client::sys_info_client(const std::shared_ptr<grpc::Channel> &channel)
        : m_stub(monitor::sys_info_service::NewStub(channel))
    {
    }

    monitor::sys_info_response sys_info_client::call(bool get_cpu_info, bool get_mem_info)
    {
        if (!get_cpu_info && !get_mem_info)
        {
            return {};
        }
        grpc::ClientContext context{};
        monitor::sys_info_request req{};
        monitor::sys_info_response resp{};
        if (get_cpu_info)
        {
            req.set_get_cpu_info(true);
        }
        if (get_mem_info)
        {
            req.set_get_memory_info(true);
        }
        auto res = this->m_stub->get_sys_info(&context, req, &resp);
        if (!res.ok())
        {
            throw std::runtime_error(res.error_message());
        }
        return resp;
    }
}
