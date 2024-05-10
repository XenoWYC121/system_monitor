//
// Created by 12992 on 24-5-6.
//

#ifndef SYSTEM_MONITOR_ABSTRACT_MONITOR_H
#define SYSTEM_MONITOR_ABSTRACT_MONITOR_H

#include <memory>

namespace system_monitor::monitor
{
    using namespace std;

    class abstract_monitor
    {
    public:
        virtual ~abstract_monitor() = default;

    public:
        virtual unique_ptr<abstract_monitor> clone() = 0;

        virtual string to_string() = 0;

    protected:
        abstract_monitor() = default;
    };
}

#endif //SYSTEM_MONITOR_ABSTRACT_MONITOR_H
