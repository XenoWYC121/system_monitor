//
// Created by 12992 on 24-5-6.
//

#include "monitor/utils/cpu_info.h"
#include <sstream>

namespace system_monitor::monitor::utils
{
    cpu_info::cpu_info(const string &cpu_info_line)
    {
        this->init(cpu_info_line);
    }

    const string &cpu_info::get_m_cpu_name() const
    {
        return m_cpu_name;
    }

    int cpu_info::get_nice() const
    {
        return nice;
    }

    int cpu_info::get_system() const
    {
        return system;
    }

    int cpu_info::get_idle() const
    {
        return idle;
    }

    int cpu_info::get_iowait() const
    {
        return iowait;
    }

    int cpu_info::get_irq() const
    {
        return irq;
    }

    int cpu_info::get_softirq() const
    {
        return softirq;
    }

    int cpu_info::get_steal() const
    {
        return steal;
    }

    int cpu_info::get_guest() const
    {
        return guest;
    }

    int cpu_info::get_guest_nice() const
    {
        return guest_nice;
    }

    int cpu_info::get_user() const
    {
        return user;
    }

    void cpu_info::init(const string &cpu_info_line)
    {
        stringstream ss;
        ss << cpu_info_line;
        ss >> m_cpu_name >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
    }

    int cpu_info::get_total_time() const
    {
        if (this->total_time == 0)
        {
            this->total_time = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
        }
        return this->total_time;
    }


} // utils
// monitor
// system_monitor