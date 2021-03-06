
#ifndef SPARK_ADAPTER_CONFIG_H
#define SPARK_ADAPTER_CONFIG_H

#include <spark/core/core.h>
#include <spark/utilitybox/logger/log_message_severity.h> // LogMessageSeverity

namespace Spark {
    namespace UtilityBox {
        namespace Logger {

            class AdapterConfiguration {
                public:
                    explicit AdapterConfiguration(const char* adapterName);
                    ~AdapterConfiguration();

                    _NODISCARD_ const char* GetAdapterName() const;
                    _NODISCARD_ int GetMessageWrapLimit() const;
                    _NODISCARD_ LogMessageSeverity GetMessageSeverityCutoff() const;
                    _NODISCARD_ const char* GetFormattingString() const;
                    _NODISCARD_ const char* GetCalendarFormatString() const;
                    _NODISCARD_ const char* GetTimestampFormattingString() const;


                    void SetAdapterName(const char* adapterName);
                    void SetMessageWrapLimit(int newLimit);
                    void SetMessageSeverityCutoff(LogMessageSeverity newCutoff);
                    void SetFormattingString(const char* formattingString);
                    void SetCalendarFormatString(const char* newFormat);
                    void SetTimestampFormattingString(const char* timestampFormat);

                private:
                    // Storage for AdapterConfiguration data, back-end functionality, and helper functions.
                    class AdapterConfigurationData;
                    AdapterConfigurationData* _data;
            };

        }
    }
}

#endif // SPARK_ADAPTER_CONFIG_H
