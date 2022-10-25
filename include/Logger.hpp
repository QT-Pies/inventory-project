#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

enum class LogLevel {TRACE, DEBUG, INFO, WARN, ERROR, FATAL};

std::string logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::TRACE:
            return "TRACE";
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARN:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::FATAL:
            return "FATAL";
        default:
            throw std::invalid_argument("This is unreachable.");
    }
}

LogLevel stringToLogLevel(std::string str) {
    if (str == "TRACE") {
        return LogLevel::TRACE;
    } else if (str == "DEBUG") {
        return LogLevel::DEBUG;
    } else if (str == "INFO") {
        return LogLevel::INFO;
    } else if (str == "WARN") {
        return LogLevel::WARN;
    } else if (str == "ERROR") {
        return LogLevel::ERROR;
    } else if (str == "FATAL") {
        return LogLevel::FATAL;
    } else {
        throw std::invalid_argument("Bad LogLevel value");
    }
}

class LogConfiguration {
public:
    /* 
     * @brief LogConfiguration constructor -- reads in logging configuration file if it exists, otherwise sets defaults.
    */
    LogConfiguration() {
        FILE *config_file;
        char buffer[128];
        config_file = NULL;

        /* Attempt to open file */
        config_file = fopen(config_filepath.c_str(), "r");

        /* Try to read in config from file */
        try {
            fscanf(config_file, "CLIDisplay=%s", buffer);
            updateLevel("cli", stringToLogLevel(buffer));
            fscanf(config_file, "FileDisplay=%s", buffer);
            updateLevel("file", stringToLogLevel(buffer));
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            fclose(config_file);
            config_file = NULL;
        }
        /* Failed to find configuration; create it. */
        if (config_file == NULL) {
            updateLevel("cli", LogLevel::WARN);
            updateLevel("file", LogLevel::TRACE);
            writeConfigToFile();
        }

        /* Close file if open */
        if (config_file != NULL) {
            fclose(config_file);
        }
    }

    /*
     * @brief Update the given display mode (cli | file) to the given LogLevel.
     * @brief Logs >= LogLevel will now be written to this display.
     * @param std::string Log area to update (cli | file).
     * @param LogLevel New LogLevel.
    */
    void updateLevel(std::string display, LogLevel level) {
        if (display == "cli") {
            cli_display = level;
        } else if (display == "file") {
            file_display = level;
        } else {
            std::string tmp = "Failed to set log level " + logLevelToString(level) + " for display " + display;
            throw std::runtime_error(tmp);
        }
    }

    /*
     * @brief Write the config to disk
    */
    void writeConfigToFile() {
        std::ofstream config_file;

        /* enum class LogLevel {TRACE, DEBUG, INFO, WARN, ERROR, FATAL}; */

        /* Open file */
        config_file.open(config_filepath);

        /* Throw exception if we failed to open the file for saving. */
        if (!config_file.is_open())
            throw std::runtime_error("Failed to open configuration file for saving.");

        /* Too lazy to support a proper config format like JSON, so we're making up our own! */
        config_file << "CLIDisplay=" << logLevelToString(cli_display) << std::endl;
        config_file << "FileDisplay=" << logLevelToString(file_display) << std::endl;

        config_file.close();
    }

    const std::string config_filepath = "logging.cfg";
    LogLevel cli_display;
    LogLevel file_display;
};

class Logger {
public:
    /*
     * @brief Construct a Logger object to handle logging.
    */
   Logger() = default;

    template<typename... Args>
    void logTrace(const std::string& str, Args... args) {
        log(LogLevel::TRACE, str, args...);
    }

    template<typename... Args>
    void logDebug(const std::string& str, Args... args) {
        log(LogLevel::DEBUG, str, args...);
    }

    template<typename... Args>
    void logInfo(const std::string& str, Args... args) {
        log(LogLevel::INFO, str, args...);
    }

    template<typename... Args>
    void logWarn(const std::string& str, Args... args) {
        log(LogLevel::WARN, str, args...);
    }

    template<typename... Args>
    void logError(const std::string& str, Args... args) {
        log(LogLevel::ERROR, str, args...);
    }

    template<typename... Args>
    void logFatal(const std::string& str, Args... args) {
        log(LogLevel::FATAL, str, args...);
    }

    template<typename... Args>
    void log(LogLevel level, const std::string& str, Args... args) {
        std::string tmp;
        time_t unix_time;
        struct tm *local_time;
        char buffer[128];

        time(&unix_time);
        local_time = localtime(&unix_time);

        strftime(buffer, 128, "%D %r", local_time);

        auto logMessage = [&](FILE* output) {
            if (output == NULL) throw std::invalid_argument("Null FILE*");
            fprintf(output, "[ %-5s @ %s ] ", logLevelToString(level).c_str(), buffer);
            fprintf(output, str.c_str(), args...);
            fprintf(output, "\n");
        };

        try {
            /* Log to stderr if level >= config. CLI level */
            if (level >= config.cli_display) {
                logMessage(stderr);
            }

            /* Log to file if level >= config file level*/
            if (level >= config.file_display) {
                logMessage(Logger::logfile);
            }
        } catch (std::exception& e) {
            std::cerr << "failed to log -- reason: " << e.what() << std::endl;
        }
    }

    inline static LogConfiguration config;
    inline static FILE* logfile = fopen("logs.txt", "a");
};

#endif