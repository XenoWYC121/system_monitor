//
// Created by fsy on 24-5-13.
//

#ifndef MEMORY_SERVICE_H
#define MEMORY_SERVICE_H

#include "memory_usage.grpc.pb.h"
#include "monitor/memory_monitor.h"
#include <iostream>
namespace system_monitor::service
{
    class memory_service
        :monitor::get_memory_usage::Service
    {
    public:
        grpc::Status get_usage(grpc::ServerContext *context, const system_monitor::monitor::memory_request *request,
            system_monitor::monitor::memory_usage *response) override;
    public:
        static void run_server(const std::string& url);

    private:
        std::unique_ptr<monitor::memory_monitor> m_monitor{monitor::memory_monitor::get_memory_monitor()};
    };
}

#endif //MEMORY_SERVICE_H
