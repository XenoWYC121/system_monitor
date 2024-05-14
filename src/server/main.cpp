//
// Created by fsy on 24-5-14.
//
#include "server/sync_grpc_server.h"

int main()
{
    system_monitor::server::sync_grpc_server::run_server("0.0.0.0:25000");
}
