//
// Created by 12992 on 24-5-6.
//

#ifndef SYSTEM_MONITOR_CPU_USAGE_MONITOR_H
#define SYSTEM_MONITOR_CPU_USAGE_MONITOR_H

#include "abstract_monitor.h"
#include <chrono>

namespace system_monitor::monitor
{
    using namespace std;

    class cpu_usage_monitor
            : public abstract_monitor
    {
    public:
        static unique_ptr<cpu_usage_monitor> get_monitor();

    public:
        unique_ptr<abstract_monitor> clone() override;

        string to_string() override;

    private:
        void get_info();

    private:
        chrono::system_clock::time_point m_tp{chrono::system_clock::now() - 5s};

    };

} // abstract_monitor
// system_monitor

#endif //SYSTEM_MONITOR_CPU_USAGE_MONITOR_H
