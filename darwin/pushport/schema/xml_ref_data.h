//
// Created by eddie on 09/02/24.
//

#ifndef FM28L_XML_REF_DATA_H
#define FM28L_XML_REF_DATA_H

#include "common_types.h"

#define DARWIN_CISSOURCECODE_STRING_LENGTH   4
#define DARWIN_CISSOURCECODE_BYTES_LENGTH   (DARWIN_CISSOURCECODE_STRING_LENGTH + 1)
/**
 * \struct CISSourceCode
 * \brief A CIS source code
 */
typedef struct {
    char string[DARWIN_CISSOURCECODE_BYTES_LENGTH];
} CISSourceCode;

#define DARWIN_CISSOURCENAME_MIN_STRING_LENGTH   0
#define DARWIN_CISSOURCENAME_MAX_STRING_LENGTH   4
#define DARWIN_CISSOURCENAME_MAX_BYTES_LENGTH   (DARWIN_CISSOURCENAME_MAX_STRING_LENGTH + 1)
/**
 * \struct CISSourceName
 * \brief A CIS source name
 */
typedef struct {
    char string[DARWIN_CISSOURCENAME_MAX_BYTES_LENGTH];
} CISSourceName;

/**
 * \struct CISSource
 * \brief Defines the mapping between 4 letter CIS codes and the CIS name
 */
typedef struct{
    CISSourceCode code; ///< This is the 4 letter CIS code
    CISSourceName name; ///< The CIS name
} CISSource;

#define DARWIN_CRSTYPE_STRING_LENGTH   4
#define DARWIN_CRSTYPE_BYTES_LENGTH   (DARWIN_CRSTYPE_STRING_LENGTH + 1)
/**
 * \struct CrsType
 * \brief CRS Code Type
 */
typedef struct {
    char string[DARWIN_CRSTYPE_BYTES_LENGTH];
} CrsType;

#define DARWIN_LOCATIONNAMETYPE_MIN_STRING_LENGTH   1
#define DARWIN_LOCATIONNAMETYPE_MAX_STRING_LENGTH   30
#define DARWIN_LOCATIONNAMETYPE_MAX_BYTES_LENGTH   (DARWIN_LOCATIONNAMETYPE_MAX_STRING_LENGTH + 1)
/**
 * \struct LocationNameType
 * \brief English name of the location
 */
typedef struct {
    char string[DARWIN_LOCATIONNAMETYPE_MAX_BYTES_LENGTH];
} LocationNameType;

/**
 * \struct LocationRef
 * \brief Defines a location
 */
typedef struct{
    TIPLOCType tpl; ///< TIPLOC code
    CrsType crs; ///< CRS code
    TOCType toc; ///< Train Operating Company that manages the station (may be non-TOC code, e.g. Network Rail).
    LocationNameType locname; ///< English name of location
} LocationRef;

#define DARWIN_TOCNAMETYPE_MIN_STRING_LENGTH   1
#define DARWIN_TOCNAMETYPE_MAX_STRING_LENGTH   256
#define DARWIN_TOCNAMETYPE_MAX_BYTES_LENGTH   (DARWIN_TOCNAMETYPE_MAX_STRING_LENGTH + 1)
/**
 * \struct TOCNameType
 * \brief The name of the TOC
 */
typedef struct {
    char string[DARWIN_TOCNAMETYPE_MAX_BYTES_LENGTH];
} TOCNameType;

#define DARWIN_URLTYPE_MIN_STRING_LENGTH   0
#define DARWIN_URLTYPE_MAX_STRING_LENGTH   512
#define DARWIN_URLTYPE_MAX_BYTES_LENGTH   (DARWIN_URLTYPE_MAX_STRING_LENGTH + 1)
/**
 * \struct URLType
 * \brief A URL
 */
typedef struct {
    char string[DARWIN_URLTYPE_MAX_BYTES_LENGTH];
} URLType;

/**
 * \struct TocRef
 * \brief Defines a mapping between a TOC and a displayable name
 */
typedef struct{
    TOCType toc; ///< The TOC code
    TOCNameType tocname; ///< The name of the TOC
    URLType url;
} TocRef;

typedef int32_t RefReasonCodeType;

#define DARWIN_REASONTEXTTYPE_MIN_STRING_LENGTH   1
#define DARWIN_REASONTEXTTYPE_MAX_STRING_LENGTH   256
#define DARWIN_REASONTEXTTYPE_MAX_BYTES_LENGTH   (DARWIN_REASONTEXTTYPE_MAX_STRING_LENGTH + 1)
/**
 * \struct ReasonTextType
 * \brief Reason as text
 */
typedef struct {
    char string[DARWIN_REASONTEXTTYPE_MAX_BYTES_LENGTH];
} ReasonTextType;

/**
 * \struct Reason
 * \brief Defines a mapping bewteen a reason code and the corresponding text
 */
typedef struct {
    RefReasonCodeType code;
    ReasonTextType reasontext;
} Reason;

#define DARWIN_VIATEXTTYPE_MIN_STRING_LENGTH   1
#define DARWIN_VIATEXTTYPE_MAX_STRING_LENGTH   256
#define DARWIN_VIATEXTTYPE_MAX_BYTES_LENGTH   (DARWIN_VIATEXTTYPE_MAX_STRING_LENGTH + 1)
/**
 * \struct ViaTextType
 * \brief The text displayed for a via
 */
typedef struct {
    char string[DARWIN_VIATEXTTYPE_MAX_BYTES_LENGTH];
} ViaTextType;

/**
 * \struct Via
 * \brief Defines the locations a journey must be viewed from, go to and pass through for the corresponding via text to be displayed
 */
typedef struct {
    CrsType at; ///< This is the station for which the via is defined
    TIPLOCType dest; ///< The destination of the journey must match this before the via text is valid
    TIPLOCType loc1; ///< The journey must call at this station before the via text is valid.
    TIPLOCType loc2; ///< The journey must call at this station (after the call at loc1) before the via text is valid.
    ViaTextType viatext; ///< The via text to display if a journey matches the previous attributes
} Via;

/**
 * \struct PportTimetableRef
 * \brief Push Port Timetable Reference Schema
 */
typedef struct{
    TimetableIDType timetableId;
    LocationRef* locationRefs; ///< Array of LocationRefs. Must be freed after use.
    uint32_t locationRefCount; ///< Number of LocationRefs. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    TocRef* tocRefs; ///< Array of TocRefs. Must be freed after use.
    uint32_t tocRefCount; ///< Number of TocRefs. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    Reason* lateRunningReasons; ///< Array of LateRunningReasons. Must be freed after use.
    uint32_t lateRunningReasonCount; ///< Number of LateRunningReasons. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    Reason* cancellationReasons; ///< Array of CancellationReasons. Must be freed after use.
    uint32_t cancellationReasonCount; ///< Number of CancellationReasons. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    Via* vias; ///< Array of Vias. Must be freed after use.
    uint32_t viaCount; ///< Number of Vias. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    CISSource* CISSources; ///< Array of CISSources. Must be freed after use.
    uint32_t CISSourceCount; ///< Number of CISSources. Theoretically infinite but limited to 32-bit unsigned int in this implementation
} PportTimetableRef;

#endif //FM28L_XML_REF_DATA_H
