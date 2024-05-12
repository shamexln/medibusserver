#pragma once

#include <Framework/Mdib/Public/Model/LocalizedText.h>

namespace DFL
{
namespace Mdib
{

/** @brief Storage that can hold the data of a @ref LocalizedText.
 *  @details To be used for generated/fixed texts so that these can be defined in header files.
 *  @ingroup Mdib
 */
struct LocalizedTextRaw
{
    /// @brief The text (in UTF-8).
    const char* text;

    /// @brief The language (as a language tag).
    const char* language;

    /// @brief Reference of the text.
    const char* ref;

    /// @brief Version of the text.
    const int version;

    /// @brief A flag to designate whether there is a width for this text.
    const bool hasWidth;

    /// @brief The width of the text.
    /// @details if @ref hasWidth is false then this carries no meaning.
    const DFL::Mdib::LocalizedTextWidth width;
};

}
}
