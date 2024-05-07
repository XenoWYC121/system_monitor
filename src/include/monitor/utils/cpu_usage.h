//
// Created by 12992 on 24-5-7.
//

#ifndef SYSTEM_MONITOR_CPU_USAGE_H
#define SYSTEM_MONITOR_CPU_USAGE_H

namespace system_monitor::monitor::utils
{
    class cpu_info;

    class cpu_usage;

    cpu_usage operator-(const cpu_info& info1, const cpu_info& info2);

    class cpu_usage
    {
    public:
        friend cpu_usage operator-(const cpu_info& info1, const cpu_info& info2);

        double get_usage() const { return this->m_user_usage; }

        double get_user_usage() const { return this->m_cpu_usage; }

        double get_system_usage() const { return this->m_system_usage; }

    private:
        cpu_usage() = default;

    private:
        double m_cpu_usage{};
        double m_system_usage{};
        double m_user_usage{};
    };
}

#endif //SYSTEM_MONITOR_CPU_USAGE_H
