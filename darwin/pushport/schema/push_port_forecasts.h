//
// Created by eddie on 13/02/24.
//

#ifndef FM28L_PUSH_PORT_FORECASTS_H
#define FM28L_PUSH_PORT_FORECASTS_H

#include "common_types.h"
#include <stdbool.h>

#define DARWIN_TSTIMEDATA_ATREMOVED_DEFAULT     false
#define DARWIN_TSTIMEDATA_ETUNKNOWN_DEFAULT     false
#define DARWIN_TSTIMEDATA_DELAYED_DEFAULT     false
/**
 *  \struct TSTimeData
 *  \brief Type describing time-based forecast attributes for a TS arrival/departure/pass
 */
typedef struct{
    RTTITimeType et; ///< Estimated Time. For locations that are public stops, this will be based on the "public schedule". For operational stops and passing locations, it will be based on the "working schedule". It is only published where there is a corresponding "activity" for the service.
    RTTITimeType wet; ///< The estimated time based on the "working schedule". This will only be set for public stops when (i) it also differs from the estimated time based on the "public schedule", or (ii) where there is an operational "activity" but no public "activity".
    RTTITimeType at; ///< Actual Time
    bool atRemoved; ///< If true, indicates that an actual time ("at") value has just been removed and replaced by an estimated time ("et"). Note that this attribute will only be set to "true" once, when the actual time is removed, and will not be set in any snapshot.
    char** atClass; ///< Pointer to string for the class of the actual time. Must be freed after use.
    uint32_t atClassLen; ///< Length of string for the class of the actual time including null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    RTTITimeType etmin; ///< The manually applied lower limit that has been applied to the estimated time at this location. The estimated time will not be set lower than this value, but may be set higher.
    bool etUnknown; ///< Indicates that an unknown delay forecast has been set for the estimated time at this location. Note that this value indicates where a manual unknown delay forecast has been set, whereas it is the "delayed" attribute that indicates that the actual forecast is "unknown delay".
    bool delayed; ///< Indicates that this estimated time is a forecast of "unknown delay". Displayed  as "Delayed" in LDB. Note that this value indicates that this forecast is "unknown delay", whereas it is the "etUnknown" attribute that indicates where the manual unknown delay forecast has been set.
    char** src; ///< Pointer to string for the source of the forecast or actual time. Must be freed after use.
    uint32_t srcLen; ///< Length of string for the source of the forecast or actual time including null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    SourceTypeInst srcInst; ///< The RTTI CIS code of the CIS instance if the src is a CIS.
} TSTimeData;

/**
 *  \enum PlatformSource
 *  \brief The source of the platfom number. P = Planned, A = Automatic, M = Manual.
 */
typedef enum{
    PLATFORMSOURCE_NONE = 0,
    PLATFORMSOURCE_PLANNED = 'P',
    PLATFORMSOURCE_AUTOMATIC = 'A',
    PLATFORMSOURCE_MANUAL = 'M'
}PlatformSource;
typedef uint8_t PlatformSource_t;

#define DARWIN_PLATFORMDATA_PLATSUP_DEFAULT     false
#define DARWIN_PLATFORMDATA_CISPLATSUP_DEFAULT  false
#define DARWIN_PLATFORMDATA_PLATSRC_DEFAULT     PLATFORMSOURCE_PLANNED
#define DARWIN_PLATFORMDATA_CONF_DEFAULT        false
/**
 * \struct PlatformData
 * \brief Platform number with associated flags
 */
typedef struct{
    PlatformType plat;
    bool platsup; ///< Platform number is suppressed and should not be displayed.
    bool cisPlatsup; ///< Whether a CIS, or Darwin Workstation, has set platform suppression at this location.
    PlatformSource_t platsrc; ///< The source of the platfom number. P = Planned, A = Automatic, M = Manual.
    bool conf; ///< True if the platform number is confirmed.
} PlatformData;

#define DARWIN_TSLOCATION_SUPPR_DEFAULT        false
#define DARWIN_TSLOCATION_LENGTH_DEFAULT       ((TrainLengthType)0)
#define DARWIN_TSLOCATION_DETACHFRONT_DEFAULT  false
/**
 * \struct TSLocation
 * \brief Forecast data for an individual location in the service's schedule
 */
typedef struct{
    TIPLOCType tpl; ///< TIPLOC
    CircularTimes circularTimes;
    TSTimeData arr; ///< Forecast data for the arrival at this location
    TSTimeData dep; ///< Forecast data for the departure at this location
    TSTimeData pass; ///< Forecast data for the pass of this location
    PlatformData plat; ///< Current platform number
    bool suppr; ///< The service is suppressed at this location.
    TrainLengthType length; ///< The length of the service at this location on departure (or arrival at destination). The default value of zero indicates that the length is unknown.
    bool detachFront; ///< Indicates from which end of the train stock will be detached. The value is set to “true” if stock will be detached from the front of the train at this location. It will be set at each location where stock will be detached from the front. Darwin will not validate that a stock detachment activity code applies at this location.
} TSLocation;

#define DARWIN_TS_ISREVERSEFORMATION_DEFAULT        false
/**
 * \struct TS
 * \brief Train Status. Update to the "real time" forecast data for a service.
 */
typedef struct{
    RIDType rid; ///< RTTI unique Train Identifier
    UIDType uid; ///< Train UID
    RTTIDateType ssd; ///< Scheduled Start Date
    bool isReverseFormation; ///< Indicates whether a train that divides is working with portions in reverse to their normal formation. The value applies to the whole train. Darwin will not validate that a divide association actually exists for this service.
    DisruptionReasonType lateReason; ///< Late running reason for this service. The reason applies to all locations of this service.
    TSLocation* locations; ///< Array of locations. Must be freed after use.
    uint32_t locationCount; ///< Number of locations. Theoretically infinite but limited to 32-bit unsigned int in this implementation
} TS;

#endif //FM28L_PUSH_PORT_FORECASTS_H
