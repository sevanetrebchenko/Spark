#ifndef SPARK_EVENT_LISTENER_TPP
#define SPARK_EVENT_LISTENER_TPP

namespace Spark::Events {
    //------------------------------------------------------------------------------------------------------------------
    // EVENT LISTENER DATA
    //------------------------------------------------------------------------------------------------------------------
    template <class ...EventTypes>
    class EventListener<EventTypes...>::EventListenerData {
        public:
            EventListenerData(const char* name, std::function<void(std::queue<std::shared_ptr<Event*>>&)> eventProcessingFunction);
            ~EventListenerData();

            _NODISCARD_ bool OnEventReceived(std::shared_ptr<Event*> eventPointer);
            void OnUpdate();

            _NODISCARD_ const char* GetName() const;

            template <class EventType>
            void AppendEventTypeAsString(std::vector<std::string>& eventTypes);

        private:
            /**
             * Check whether this EventListener is registered to receive the given type of event.
             * @param eventType - Type of event.
             * @return True: Events of type 'eventType' are registered with the EventListener.
             *         False: Events of type 'eventType' are not registered with the EventListener.
             */
            template <unsigned INDEX, class CurrentEventType, class ...AdditionalEventTypeArgs>
            _NODISCARD_ bool ManagesEventType(const EventType& eventType);

            template<unsigned>
            _NODISCARD_ bool ManagesEventType(const EventType& eventType);

            const char* _name;
            std::function<void(std::queue<std::shared_ptr<Event*>>&)> _processingFunction;
            std::queue<std::shared_ptr<Event*>> _eventQueue;
    };

    template<class... EventTypes>
    EventListener<EventTypes...>::EventListenerData::EventListenerData(const char* name, std::function<void(std::queue<std::shared_ptr<Event*>>&)> eventProcessingFunction) : _name(name), _processingFunction(std::move(eventProcessingFunction)) {
        // Nothing to do here.
    }

    template<class... EventTypes>
    EventListener<EventTypes...>::EventListenerData::~EventListenerData() {
        while (!_eventQueue.empty()) {
            _eventQueue.pop();
        }
    }

    template<class... EventTypes>
    bool EventListener<EventTypes...>::EventListenerData::OnEventReceived(std::shared_ptr<Event*> eventPointer) {
        const Event* event = *eventPointer;
        if (ManagesEventType<0u, EventTypes...>(event->GetEventType())) {
            _eventQueue.push(eventPointer);
            return true;
        }

        return false;
    }

    template<class... EventTypes>
    void EventListener<EventTypes...>::EventListenerData::OnUpdate() {
        _processingFunction(_eventQueue);
    }

    template<class... EventTypes>
    template<unsigned INDEX, class CurrentEventType, class... AdditionalEventTypeArgs>
    bool EventListener<EventTypes...>::EventListenerData::ManagesEventType(const EventType &eventType) {
        if (eventType == CurrentEventType::StaticEventType) {
            return true;
        }
        else {
            return ManagesEventType<INDEX + 1, AdditionalEventTypeArgs...>(eventType);
        }
    }

    template<class... EventTypes>
    template <unsigned>
    bool EventListener<EventTypes...>::EventListenerData::ManagesEventType(const EventType &eventType) {
        return false;
    }

    template<class... EventTypes>
    template<class EventType>
    void EventListener<EventTypes...>::EventListenerData::AppendEventTypeAsString(std::vector<std::string> &eventTypes) {
        eventTypes.emplace_back(Event::ConvertEventTypeToString(EventType::StaticEventType));
    }

    template<class... EventTypes>
    const char *EventListener<EventTypes...>::EventListenerData::GetName() const {
        return _name;
    }


    //------------------------------------------------------------------------------------------------------------------
    // EVENT LISTENER
    //------------------------------------------------------------------------------------------------------------------
    template<class... EventTypes>
    EventListener<EventTypes...>::EventListener(const char* name, const std::function<void(std::queue<std::shared_ptr<Event*>>&)>& eventProcessingFunction) : _data(new EventListenerData(name, eventProcessingFunction)) {
        static_assert((std::is_base_of_v<Event, EventTypes> && ...), "Invalid template parameter passed to EventListener constructor - provided event type does not derive from 'Event' and is therefore not a valid event.");
    }

    template<class... EventTypes>
    EventListener<EventTypes...>::~EventListener() {
        delete _data;
    }

    template<class... EventTypes>
    bool EventListener<EventTypes...>::OnEventReceived(std::shared_ptr<Event*> eventPointer) {
        return _data->OnEventReceived(eventPointer);
    }

    template<class... EventTypes>
    void EventListener<EventTypes...>::OnUpdate() {
        _data->OnUpdate();
    }

    template<class... EventTypes>
    const std::vector<std::string>& EventListener<EventTypes...>::GetEventTypesAsStrings() {
        static bool initialized = false;
        static std::vector<std::string> eventTypes;

        if (!initialized) {
            PARAMETER_PACK_EXPAND(_data->template AppendEventTypeAsString, EventTypes, eventTypes);
        }

        return eventTypes;
    }

    template<class... EventTypes>
    const char *EventListener<EventTypes...>::GetName() {
        return _data->GetName();
    }
}

#endif // SPARK_EVENT_LISTENER_TPP
