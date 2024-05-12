//
// Created by 12992 on 24-5-10.
//

#ifndef SYSTEM_MONITOR_CPU_SERVICE_H
#define SYSTEM_MONITOR_CPU_SERVICE_H

#include "cpu_usage_info.grpc.pb.h"
#include "monitor/cpu_usage_monitor.h"

namespace system_monitor::service
{

    class cpu_service final
            : public monitor::get_cpu_usage::Service
    {
    public:
        grpc::Status get_usage(::grpc::ServerContext* context, const ::system_monitor::monitor::cpu_request* request,
                               ::system_monitor::monitor::all_cpu_usage* response) override;

    private:
        std::unique_ptr<monitor::cpu_usage_monitor> m_ptr{monitor::cpu_usage_monitor::get_monitor()};
    };
}

#endif //SYSTEM_MONITOR_CPU_SERVICE_H
