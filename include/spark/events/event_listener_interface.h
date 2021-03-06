
#ifndef SPARK_EVENT_LISTENER_INTERFACE_H
#define SPARK_EVENT_LISTENER_INTERFACE_H

#include <spark/core/core.h>

namespace Spark {
    namespace Events {

        class IEventListener {
            public:
                /**
                 * Send an event to this function. Function adequately handles if the given eventType is not handled by
                 * the attached EventListener.
                 * @param eventPointer - Shared pointer to the dispatched event.
                 * @return True  - this event was received by this event listener
                 *         False - this event was not received by this event listener.
                 */
                _NODISCARD_ virtual bool OnEventReceived(std::shared_ptr<Event*> eventPointer) = 0;
                _NODISCARD_ virtual const char* GetName() = 0;
                _NODISCARD_ virtual const std::vector<std::string>& GetEventTypesAsStrings() = 0;

                virtual void OnUpdate() = 0;
        };

    }
}

#endif //SPARK_EVENT_LISTENER_INTERFACE_H
