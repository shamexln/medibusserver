#pragma once

#include <S31/S31CoreExImp.h>

#include <string>
#include <vector>

namespace S31
{

/**
 * \brief A wrapper class for command line options. Different options are held in a list.
 *
 * \details
 * Options can be added and retrieved as a string. System properties (start with "-D"
 * are handled explicitly).
 *
 * \ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP CommandLineOptions
{
    public:
        /*!
         * \brief Constructs empty command line options.
         */
        CommandLineOptions() = default;

        /*!
         * \brief Constructs command line options with one initial entry.
         *
         * \param arg initial entry (this may be a space-separated list of arguments)
         */
        explicit CommandLineOptions(const std::string& arg);

        /*!
         * \brief Constructs command line options given several arguments as retrieved from a main function.
         *
         * \param argc number of arguments
         * \param argv list of arguments
         */
        CommandLineOptions(int argc, const char* const argv[]);
        CommandLineOptions(std::size_t argc, const char* const argv[]);

        /*!
         * \brief Retrieves a given system property.
         *
         * \param name the system property to retrieve
         * \return value of the system property, empty string if the property was not set
         */
        [[nodiscard]] std::string getSystemProperty(std::string_view name) const;

        /*!
         * \brief Returns the number of command line arguments.
         *
         * \return number of arguments
         */
        [[nodiscard]] std::size_t size() const;

        /*!
         * \brief Returns all command line arguments.
         *
         * \return list of arguments
         */
        [[nodiscard]] const std::vector<std::string>& entries() const;

        /*!
         * \brief Adds and entry to the command line options.
         *
         * \param name entry to be added
         */
        void addEntry(const char* name);

        /*!
         * \brief Adds and entry to the command line options.
         *
         * \param name entry to be added
         */
        void addEntry(const std::string& name);

        /**
         * returns all options in one string, so they can be used as command line parameters again.
         */
        [[nodiscard]] std::string asString() const;

        /**
         * @brief Adds 'key=value' if there is no such pair in the already existing entries.
         * \returns true if the key value pair was added.
         * \returns false if the key and it's value is already defined.
         */
        bool addSystemPropertyIfNotExists(const char* key, const char* value);

        /**
         * @brief Adds all options from another CommandLineOptions instance.
         *
         * @param additionalOptions options to be added
         */
        void addOptions(const CommandLineOptions& additionalOptions);

    private:

        std::vector<std::string> m_entries;
};

} /* namespace S31 */
