//
// Created by 12992 on 24-5-6.
//

#ifndef SYSTEM_MONITOR_MONITOR_H
#define SYSTEM_MONITOR_MONITOR_H

#include <memory>

namespace system_monitor::monitor
{
    using namespace std;

    class monitor
    {
    public:
        virtual ~monitor() = default;

        monitor(const monitor &) = delete;

        monitor(monitor &&) = delete;

        monitor &operator=(const monitor &) = delete;

        monitor &operator=(monitor &&) = delete;

    public:
        virtual unique_ptr<monitor> clone() = 0;

        virtual string to_string() = 0;

    protected:
        monitor() = default;
    };
}

#endif //SYSTEM_MONITOR_MONITOR_H
