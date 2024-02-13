//
// Created by eddie on 13/02/24.
//

#ifndef FM28L_PUSH_PORT_STATION_MESSAGES_H
#define FM28L_PUSH_PORT_STATION_MESSAGES_H

#include "common_types.h"

/**
 * \enum HTMLElementType
 * \brief Enum representing the valid types of HTML element in a station message
 */
typedef enum{
    HTML_ELEMENT_TYPE_TEXT = 0,
    HTML_ELEMENT_TYPE_P,
    HTML_ELEMENT_TYPE_A
} HTMLElementType;

/**
 * \enum HTMLElementInstanceRef
 * \brief Represents the occurrence of an HTML element in a message
 */
typedef struct{
    HTMLElementType elementType; ///< The type of the element
    uint32_t elementIndex; ///< Index of the element in that element type's array
} HTMLElementInstanceRef;

/**
 * \struct HTMLtext
 * \brief Defines HTML content text
 */
typedef struct{
    char** contentString; ///< Pointer to string for the content. Must be freed after use.
    uint32_t contentLen; ///< Length of string for the content including null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
} HTMLtext;

/**
 * \struct HTMLa
 * \brief Defines an HTML anchor
 */
typedef struct{
    char** hrefString; ///< Pointer to string for the href. Must be freed after use.
    uint32_t hrefLen; ///< Length of string for the href including null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    HTMLtext content;
} HTMLa;

/**
 * \struct HTMLp
 * \brief Defines an HTML anchor
 */
typedef struct{
    HTMLa* htmlAs; ///< Array of HTMLas. Must be freed after use.
    uint32_t htmlACount; ///< Number of HTMLas. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    HTMLtext* htmlTexts; ///< Array of HTMLtexts. Must be freed after use.
    uint32_t htmlTextCount; ///< Number of HTMLtexts. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    HTMLElementInstanceRef* htmlElements; ///< Array of HTML elements. Must be freed after use.
    uint32_t htmlElementCount; ///< Number of HTML elements. Theoretically infinite but limited to 32-bit unsigned int in this implementation
} HTMLp;

/**
 * \struct Msg
 * \brief The content of the message
 */
typedef struct{
    HTMLp* htmlPs; ///< Array of HTMLps. Must be freed after use.
    uint32_t htmlPCount; ///< Number of HTMLps. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    HTMLa* htmlAs; ///< Array of HTMLas. Must be freed after use.
    uint32_t htmlACount; ///< Number of HTMLas. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    HTMLtext* htmlTexts; ///< Array of HTMLtexts. Must be freed after use.
    uint32_t htmlTextCount; ///< Number of HTMLtexts. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    HTMLElementInstanceRef* htmlElements; ///< Array of HTML elements. Must be freed after use.
    uint32_t htmlElementCount; ///< Number of HTML elements. Theoretically infinite but limited to 32-bit unsigned int in this implementation
} Msg;

/**
 * \enum MsgCategoryType
 * \brief The category of message
 */
typedef enum{
    MSG_CATEGORY_TYPE_TRAIN = 0, ///< Train
    MSG_CATEGORY_TYPE_STATION, ///< Station
    MSG_CATEGORY_TYPE_CONNECTIONS, ///< Connections
    MSG_CATEGORY_TYPE_SYSTEM, ///< System
    MSG_CATEGORY_TYPE_MISC, ///< Misc
    MSG_CATEGORY_TYPE_PRIORTRAINS, ///< PriorTrains
    MSG_CATEGORY_TYPE_PRIOROTHER, ///< PriorOther
} MsgCategoryType;
static const char* darwin_message_category_type_strings[] = {"Train", "Station", "Connections", "System", "Misc", "PriorTrains", "PriorOther"};

/**
 * \enum MsgSeverityType
 * \brief The category of message as a char
 */
typedef enum{
    MSG_SEVERITY_TYPE_0 = '0',
    MSG_SEVERITY_TYPE_1 = '1',
    MSG_SEVERITY_TYPE_2 = '2',
    MSG_SEVERITY_TYPE_3 = '3',
} MsgSeverityType;
#define DARWIN_MSG_SEVERITY_TYPE_CHAR_TO_NUMBER(x) ((uint8_t)(x - '0'))
#define DARWIN_MSG_SEVERITY_TYPE_NUMBER_TO_CHAR(x) ((char)(x + '0'))

#define DARWIN_STATIONMESSAGE_SUPPRESS_DEFAULT      false
/**
 * \struct StationMessage
 * \brief Darwin Workstation Station Message
 */
typedef struct{
    int32_t id;
    MsgCategoryType cat; ///< The category of message
    MsgSeverityType sev; ///< The severity of the message
    bool suppress; ///< Whether the train running information is suppressed to the public
    CRSType* stations; ///< Array of stations the message is being applied to. Must be freed after use.
    uint32_t stationsCount; ///< Number of stations. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    Msg msg; ///< The content of the message
} StationMessage;

#endif //FM28L_PUSH_PORT_STATION_MESSAGES_H
