//
// Created by 12992 on 24-5-7.
//

#include "monitor/utils/cpu_usage.h"
#include "monitor/utils/cpu_info.h"

namespace system_monitor::monitor::utils
{
    using namespace std;

    cpu_usage operator-(const cpu_info& info1, const cpu_info& info2)
    {
        if (info1.get_total_time() - info2.get_total_time() < 0)
        {
            throw logic_error("cpu usage can not be negative");
        };
        cpu_usage temp_usage;
        int duration = info1.get_total_time() - info2.get_total_time();
        temp_usage.m_cpu_usage = 1.0 - (static_cast<double>(info1.get_idle()) - info2.get_idle()) / duration;
        temp_usage.m_system_usage = (static_cast<double>(info1.get_system()) - info2.get_system()) / duration;
        temp_usage.m_user_usage = (static_cast<double>(info1.get_user()) - info2.get_user()) / duration;
        return temp_usage;
    }
}