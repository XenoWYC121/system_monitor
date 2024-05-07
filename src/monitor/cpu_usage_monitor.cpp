//
// Created by 12992 on 24-5-6.
//

#include "../include/monitor/cpu_usage_monitor.h"

#include <iostream>
#include <string>

namespace system_monitor::monitor
{
    unique_ptr<abstract_monitor> cpu_usage_monitor::clone()
    {
        return unique_ptr<abstract_monitor>();
    }

    string cpu_usage_monitor::to_string()
    {
        return {};
    }

    unique_ptr<cpu_usage_monitor> cpu_usage_monitor::get_monitor()
    {
        return make_unique<cpu_usage_monitor>();
    }

    void cpu_usage_monitor::get_info()
    {

    }
} // abstract_monitor
// system_monitor