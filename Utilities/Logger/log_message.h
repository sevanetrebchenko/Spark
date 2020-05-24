#ifndef DATASTRUCTURES_LOG_MESSAGE_H
#define DATASTRUCTURES_LOG_MESSAGE_H

#include <memory>
#include <vector>
#include "timestamp.h"

#define DEBUG_MESSAGES

namespace UtilityBox {
    namespace Logger {

        enum class LogMessageSeverity {
            DEBUG,
            WARNING,
            SEVERE
        };

        class LogMessage {
            public:
                class LogRecord {
                    public:
                        LogRecord(std::string&& message, Timing::TimeStamp&& timestamp);
                        std::string&& GetMessage();
                        Timing::TimeStamp&& GetTimestamp();

                    private:
                        std::string _message;
                        Timing::TimeStamp _timestamp;
                };

                explicit LogMessage(LogMessageSeverity messageSeverity = LogMessageSeverity::DEBUG);
                ~LogMessage();
                void Supply(const char *formatString, ...);

                const std::vector<LogRecord>* GetLogMessages();
                LogMessageSeverity GetMessageSeverity();

            private:
                // Opaque pointer to abstract data - this data is not available
                class LogMessageBackEnd;
                std::unique_ptr<LogMessageBackEnd> _data;

                std::vector<LogRecord> _logMessages;
                LogMessageSeverity _messageSeverity;

        };

#ifdef DEBUG_MESSAGES
        // Class captures caller and records debug information
        class DBG_LOG_MESSAGE {
            private:
                // Opaque pointer to abstract data - this data is not available
                class LogMessageBackEnd;
                std::unique_ptr<LogMessageBackEnd> _data;

                struct DebugLogRecord {
                    DebugLogRecord(std::string&& filename, std::string&& functionName, int lineNumber);
                    std::string _fileName;
                    std::string _functionName;
                    int _lineNumber;
                };

                struct LogRecord {
                    LogRecord(std::string&& message, Timing::TimeStamp&& timestamp, DebugLogRecord&& calleeInformation);
                    std::string _message;
                    Timing::TimeStamp _timestamp;
                    DebugLogRecord _calleeInformation;
                };

                std::vector<LogRecord> _logMessages;
                LogMessageSeverity _messageSeverity;

            public:
                class LogRecord {
                    public:
                        LogRecord(std::string&& message, Timing::TimeStamp&& timestamp);
                        std::string&& GetMessage();
                        Timing::TimeStamp&& GetTimestamp();

                    private:
                        std::string _message;
                        Timing::TimeStamp _timestamp;
                };

                explicit DBG_LOG_MESSAGE(LogMessageSeverity messageSeverity = DEBUG);
                ~DBG_LOG_MESSAGE();
                void SUPPLY_DBG(std::string&& callingFunction, std::string&& fileName, int lineNumber, const char* formatString, ...);

                const std::vector<LogRecord>* GetLogMessages();
                LogMessageSeverity GetMessageSeverity();
        };

        // shorten file name - get the last occurrence of the '/' character to only get the file name
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#undef LogMessage
#define LogMessage DBG_LOG_MESSAGE
#undef Supply
#define Supply(formatString, ...) SUPPLY_DBG(__PRETTY_FUNCTION__, __FILENAME__, __LINE__, formatString, ##__VA_ARGS__)
#endif
    }
}

#endif //DATASTRUCTURES_LOG_MESSAGE_H
