//
// Created by 12992 on 24-5-7.
//

#ifndef SYSTEM_MONITOR_MEMORY_MONITOR_H
#define SYSTEM_MONITOR_MEMORY_MONITOR_H

#include "abstract_monitor.h"
#include <sys/sysinfo.h>
namespace system_monitor::monitor
{
    class memory_monitor
            : public abstract_monitor
    {
    public:
        static unique_ptr<memory_monitor> get_memory_monitor();

        static struct sysinfo &get_sys_info();

        unique_ptr<abstract_monitor> clone() override;

        string to_string() override;

    public:
        unsigned long get_total_ram();

        unsigned long get_free_ram();

        double get_ram_usage();

    private:
        memory_monitor() = default;

    };

}

#endif //SYSTEM_MONITOR_MEMORY_MONITOR_H
