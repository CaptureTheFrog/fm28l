//
// Created by eddie on 09/02/24.
//

#ifndef FM28L_COMMON_TYPES_H
#define FM28L_COMMON_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include "../../utils/type_conversions.h"

#define DARWIN_TIMETABLEIDTYPE_STRING_LENGTH   14
#define DARWIN_TIMETABLEIDTYPE_BYTES_LENGTH   (DARWIN_TIMETABLEIDTYPE_STRING_LENGTH + 1)
typedef struct {
    char string[DARWIN_TIMETABLEIDTYPE_BYTES_LENGTH];
} TimetableIDType;

#define DARWIN_RIDTYPE_MAX_STRING_LENGTH   16
#define DARWIN_RIDTYPE_MAX_BYTES_LENGTH   (DARWIN_RIDTYPE_MAX_STRING_LENGTH + 1)
typedef struct {
    char string[DARWIN_RIDTYPE_MAX_BYTES_LENGTH];
} RIDType;

#define DARWIN_UIDTYPE_STRING_LENGTH   6
#define DARWIN_UIDTYPE_BYTES_LENGTH   (DARWIN_UIDTYPE_STRING_LENGTH + 1)
typedef struct {
    char string[DARWIN_UIDTYPE_BYTES_LENGTH];
} UIDType;

#define DARWIN_TRAINIDTYPE_STRING_LENGTH   4
#define DARWIN_TRAINIDTYPE_BYTES_LENGTH   (DARWIN_TRAINIDTYPE_STRING_LENGTH + 1)
typedef struct {
    char string[DARWIN_TRAINIDTYPE_BYTES_LENGTH];
} TrainIdType;

typedef struct{
    uint16_t year;
    uint8_t month;
    uint8_t day;
} RTTIDateType;

#define DARWIN_TOCTYPE_STRING_LENGTH   2
#define DARWIN_TOCTYPE_BYTES_LENGTH   (DARWIN_TOCTYPE_STRING_LENGTH + 1)
typedef struct {
    char string[DARWIN_TOCTYPE_BYTES_LENGTH];
} TOCType;


typedef enum {
    CIFTRAINSTATUS_NONE = 0,
    BUS_PERMANENT = 'B',
    FREIGHT_PERMANENT_WTT = 'F',
    PASSENGER_AND_PARCELS_PERMANENT_WTT = 'P',
    SHIP_PERMANENT = 'S',
    TRIP_PERMANENT = 'T',
    STP_PASSENGER_AND_PARCELS = '1',
    STP_FREIGHT = '2',
    STP_TRIP = '3',
    STP_SHIP = '4',
    STP_BUS = '5'
} CIFTrainStatusType;
typedef uint8_t CIFTrainStatusType_t;

// source: Network Rail Common Interface File (CIF) End User Specification Version 29 Appendix A (page 38)
#define DARWIN_CIFTRAINCATEGORY_DEFAULT                             CHAR_PAIR_TO_UINT16_T('O', 'O')
typedef enum{
    CIFTRAINCATEGORY_NONE = 0,
    ORDINARY_PASSENGER_LONDON_UNDERGROUND_OR_METRO =                CHAR_PAIR_TO_UINT16_T('O', 'L'),
    ORDINARY_PASSENGER_UNADVERTISED =                               CHAR_PAIR_TO_UINT16_T('O', 'U'),
    ORDINARY_PASSENGER =                                            CHAR_PAIR_TO_UINT16_T('O', 'O'),
    ORDINARY_PASSENGER_STAFF_TRAIN =                                CHAR_PAIR_TO_UINT16_T('O', 'S'),
    ORDINARY_PASSENGER_MIXED =                                      CHAR_PAIR_TO_UINT16_T('O', 'W'),
    EXPRESS_PASSENGER_CHANNEL_TUNNEL =                              CHAR_PAIR_TO_UINT16_T('X', 'C'),
    EXPRESS_PASSENGER_SLEEPER_EUROPE_NIGHT_SERVICES =               CHAR_PAIR_TO_UINT16_T('X', 'D'),
    EXPRESS_PASSENGER_INTERNATIONAL =                               CHAR_PAIR_TO_UINT16_T('X', 'I'),
    EXPRESS_PASSENGER_MOTORAIL =                                    CHAR_PAIR_TO_UINT16_T('X', 'R'),
    EXPRESS_PASSENGER_UNADVERTISED =                                CHAR_PAIR_TO_UINT16_T('X', 'U'),
    EXPRESS_PASSENGER =                                             CHAR_PAIR_TO_UINT16_T('X', 'X'),
    EXPRESS_PASSENGER_SLEEPER_DOMESTIC =                            CHAR_PAIR_TO_UINT16_T('X', 'Z'),
    BUS_REPLACEMENT_DUE_TO_ENGINEERING_WORK =                       CHAR_PAIR_TO_UINT16_T('B', 'R'),
    BUS_REPLACEMENT_WTT_SERVICE =                                   CHAR_PAIR_TO_UINT16_T('B', 'S'),
    SHIP =                                                          CHAR_PAIR_TO_UINT16_T('S', 'S'),
    ECS =                                                           CHAR_PAIR_TO_UINT16_T('E', 'E'),
    ECS_LONDON_UNDERGROUND_OR_METRO =                               CHAR_PAIR_TO_UINT16_T('E', 'L'),
    ECS_AND_STAFF =                                                 CHAR_PAIR_TO_UINT16_T('E', 'S'),
    POSTAL =                                                        CHAR_PAIR_TO_UINT16_T('J', 'J'),
    POST_OFFICE_CONTROLLED_PARCELS =                                CHAR_PAIR_TO_UINT16_T('P', 'M'),
    PARCELS =                                                       CHAR_PAIR_TO_UINT16_T('P', 'P'),
    EMPTY_NPCCS =                                                   CHAR_PAIR_TO_UINT16_T('P', 'V'),
    DEPARTMENTAL =                                                  CHAR_PAIR_TO_UINT16_T('D', 'D'),
    DEPARTMENTAL_CIVIL_ENGINEER =                                   CHAR_PAIR_TO_UINT16_T('D', 'H'),
    DEPARTMENTAL_MECHANICAL_AND_ELECTRICAL_ENGINEER =               CHAR_PAIR_TO_UINT16_T('D', 'I'),
    DEPARTMENTAL_STORES =                                           CHAR_PAIR_TO_UINT16_T('D', 'Q'),
    DEPARTMENTAL_TEST =                                             CHAR_PAIR_TO_UINT16_T('D', 'T'),
    DEPARTMENTAL_SIGNAL_AND_TELECOMMUNICATIONS_ENGINEER =           CHAR_PAIR_TO_UINT16_T('E', 'S'),
    LIGHT_LOCOMOTIVE_AND_BRAKE_VAN =                                CHAR_PAIR_TO_UINT16_T('Z', 'B'),
    LIGHT_LOCOMOTIVE =                                              CHAR_PAIR_TO_UINT16_T('Z', 'Z'),
    RAILFREIGHT_DISTRIBUTION_AUTOMOTIVE_COMPONENTS =                CHAR_PAIR_TO_UINT16_T('J', '2'),
    RAILFREIGHT_DISTRIBUTION_AUTOMOTIVE_VEHICLES =                  CHAR_PAIR_TO_UINT16_T('H', '2'),
    RAILFREIGHT_DISTRIBUTION_BUILDING_MATERIALS_UK_CONTRACTS =      CHAR_PAIR_TO_UINT16_T('J', '6'),
    RAILFREIGHT_DISTRIBUTION_CHEMICALS_UK_CONTRACTS =               CHAR_PAIR_TO_UINT16_T('J', '5'),
    RAILFREIGHT_DISTRIBUTION_EDIBLE_PRODUCTS_UK_CONTRACTS =         CHAR_PAIR_TO_UINT16_T('J', '3'),
    RAILFREIGHT_DISTRIBUTION_FREIGHTLINER_CONTRACTS =               CHAR_PAIR_TO_UINT16_T('J', '9'),
    RAILFREIGHT_DISTRIBUTION_FREIGHTLINER_OTHER =                   CHAR_PAIR_TO_UINT16_T('H', '9'),
    RAILFREIGHT_DISTRIBUTION_EUROPEAN =                             CHAR_PAIR_TO_UINT16_T('H', '8'),
    RAILFREIGHT_DISTRIBUTION_GENERAL_MERCHANDISE_UK_CONTRACTS =     CHAR_PAIR_TO_UINT16_T('J', '8'),
    RAILFREIGHT_DISTRIBUTION_INDUSTRIAL_MINERALS_UK_CONTRACTS =     CHAR_PAIR_TO_UINT16_T('J', '4'),
    TRAINLOAD_FREIGHT_COAL_DISTRIBUTIVE =                           CHAR_PAIR_TO_UINT16_T('A', '0'),
    TRAINLOAD_FREIGHT_COAL_ELECTRICITY_MGR =                        CHAR_PAIR_TO_UINT16_T('E', '0'),
    TRAINLOAD_FREIGHT_COAL_OTHER_AND_NUCLEAR =                      CHAR_PAIR_TO_UINT16_T('B', '0'),
    TRAINLOAD_FREIGHT_METALS =                                      CHAR_PAIR_TO_UINT16_T('B', '1'),
    TRAINLOAD_FREIGHT_AGGREGATES =                                  CHAR_PAIR_TO_UINT16_T('B', '4'),
    TRAINLOAD_FREIGHT_DOMESTIC_AND_INDUSTRIAL_WASTE =               CHAR_PAIR_TO_UINT16_T('B', '5'),
    TRAINLOAD_FREIGHT_BUILDING_MATERIALS_TLF =                      CHAR_PAIR_TO_UINT16_T('B', '6'),
    TRAINLOAD_FREIGHT_PETROLEUM_PRODUCTS =                          CHAR_PAIR_TO_UINT16_T('B', '7'),
    RAILFREIGHT_DISTRIBUTION_CHANNEL_TUNNEL_MIXED_BUSINESS =        CHAR_PAIR_TO_UINT16_T('H', '0'),
    RAILFREIGHT_DISTRIBUTION_CHANNEL_TUNNEL_INTERMODAL =            CHAR_PAIR_TO_UINT16_T('H', '1'),
    RAILFREIGHT_DISTRIBUTION_CHANNEL_TUNNEL_AUTOMOTIVE =            CHAR_PAIR_TO_UINT16_T('H', '3'),
    RAILFREIGHT_DISTRIBUTION_CHANNEL_TUNNEL_CONTRACT_SERVICES =     CHAR_PAIR_TO_UINT16_T('H', '4'),
    RAILFREIGHT_DISTRIBUTION_CHANNEL_TUNNEL_HAULMARK =              CHAR_PAIR_TO_UINT16_T('H', '5'),
    RAILFREIGHT_DISTRIBUTION_CHANNEL_TUNNEL_JOINT_VENTURE =         CHAR_PAIR_TO_UINT16_T('H', '6')
} CIFTrainCategoryType;

typedef uint16_t CIFTrainCategoryType_t;

#define DARWIN_SCHEDULE_ISPASSENGERSVC_DEFAULT      TRUE
#define DARWIN_SCHEDULE_DELETED_DEFAULT             FALSE
#define DARWIN_SCHEDULE_ISCHARTER_DEFAULT           FALSE
#define DARWIN_SCHEDULE_QTRAIN_DEFAULT              FALSE
#define DARWIN_SCHEDULE_CAN_DEFAULT                 FALSE

#define DARWIN_TIPLOCTYPE_MIN_STRING_LENGTH   1
#define DARWIN_TIPLOCTYPE_MAX_STRING_LENGTH   7
#define DARWIN_TIPLOCTYPE_MAX_BYTES_LENGTH   (DARWIN_TIPLOCTYPE_MAX_STRING_LENGTH + 1)
/**
 * \struct TIPLOCType
 * \brief Tiploc Type (This is the short version of a TIPLOC - without spaces)
 */
typedef struct {
    char string[DARWIN_TIPLOCTYPE_MAX_BYTES_LENGTH];
} TIPLOCType;

typedef int16_t ReasonCodeType;
#define DARWIN_DISRUPTIONREASONTYPE_NEAR_DEFAULT          FALSE
/**
 * \struct DisruptionReasonType
 * \brief Type used to represent a cancellation or late running reason
 */
typedef struct {
    ReasonCodeType reasonCode;
    TIPLOCType tiploc; ///< Optional TIPLOC where the reason refers to, e.g. "signalling failure at Cheadle Hulme".
    bool near; ///< If true, the tiploc attribute should be interpreted as "near", e.g. "signalling failure near Cheadle Hulme".
} DisruptionReasonType;

// source: Network Rail Common Interface File (CIF) End User Specification Version 29 Appendix A (page 35)
#define DARWIN_ACTIVITY_CODES_COUNT_MAX            6
typedef enum{
    NONE = 0,
    STOPS_OR_SHUNTS_FOR_OTHER_TRAINS_TO_PASS =              CHAR_PAIR_TO_UINT16_T('A', ' '),
    ATTACH_DETACH_ASSISTING_LOCOMOTIVE =                    CHAR_PAIR_TO_UINT16_T('A', 'E'),
    SHOWS_AS_X_ON_ARRIVAL =                                 CHAR_PAIR_TO_UINT16_T('A', 'X'),
    STOPS_FOR_BANKING_LOCOMOTIVE =                          CHAR_PAIR_TO_UINT16_T('B', 'L'),
    STOPS_TO_CHANGE_TRAINMEN =                              CHAR_PAIR_TO_UINT16_T('C', ' '),
    STOPS_TO_SET_DOWN_PASSENGERS =                          CHAR_PAIR_TO_UINT16_T('D', ' '),
    STOPS_TO_DETACH_VEHICLES =                              CHAR_PAIR_TO_UINT16_T('-', 'D'),
    STOPS_FOR_EXAMINATION =                                 CHAR_PAIR_TO_UINT16_T('E', ' '),
    NATIONAL_RAIL_TIMETABLE_DATA_TO_ADD =                   CHAR_PAIR_TO_UINT16_T('G', ' '),
    NOTIONAL_ACTIVITY_TO_PREVENT_COLUMN_MERGE =             CHAR_PAIR_TO_UINT16_T('H', ' '),
    NOTIONAL_ACTIVITY_TO_PREVENT_COLUMN_MERGE_2 =           CHAR_PAIR_TO_UINT16_T('H', 'H'),
    PASSENGER_COUNT_POINT =                                 CHAR_PAIR_TO_UINT16_T('K', ' '),
    TICKET_COLLECTION_AND_EXAMINATION_POINT =               CHAR_PAIR_TO_UINT16_T('K', 'C'),
    TICKET_EXAMINATION_POINT =                              CHAR_PAIR_TO_UINT16_T('K', 'E'),
    TICKET_EXAMINATION_POINT_FIRST_CLASS_ONLY =             CHAR_PAIR_TO_UINT16_T('K', 'F'),
    SELECTIVE_TICKET_EXAMINATION_POINT =                    CHAR_PAIR_TO_UINT16_T('K', 'S'),
    STOPS_TO_CHANGE_LOCOMOTIVES =                           CHAR_PAIR_TO_UINT16_T('L', ' '),
    STOP_NOT_ADVERTISED =                                   CHAR_PAIR_TO_UINT16_T('N', ' '),
    STOPS_FOR_OTHER_OPERATING_REASONS =                     CHAR_PAIR_TO_UINT16_T('O', 'P'),
    TRAIN_LOCOMOTIVE_ON_REAR =                              CHAR_PAIR_TO_UINT16_T('O', 'R'),
    PROPELLING_BETWEEN_POINTS_SHOWN =                       CHAR_PAIR_TO_UINT16_T('P', 'R'),
    STOPS_WHEN_REQUIRED =                                   CHAR_PAIR_TO_UINT16_T('R', ' '),
    REVERSING_MOVEMENT_OR_DRIVER_CHANGES_ENDS =             CHAR_PAIR_TO_UINT16_T('R', 'M'),
    STOPS_FOR_LOCOMOTIVE_TO_RUN_ROUND_TRAIN =               CHAR_PAIR_TO_UINT16_T('R', 'R'),
    STOPS_FOR_RAILWAY_PERSONNEL_ONLY =                      CHAR_PAIR_TO_UINT16_T('S', ' '),
    STOPS_TO_TAKE_UP_AND_SET_DOWN_PASSENGERS =              CHAR_PAIR_TO_UINT16_T('T', ' '),
    STOPS_TO_ATTACH_AND_DETACH_VEHICLES =                   CHAR_PAIR_TO_UINT16_T('-', 'T'),
    TRAIN_BEGINS_ORIGIN =                                   CHAR_PAIR_TO_UINT16_T('T', 'B'),
    TRAIN_FINISHES_DESTINATION =                            CHAR_PAIR_TO_UINT16_T('T', 'F'),
    DETAIL_CONSIST_FOR_TOPS_DIRECT =                        CHAR_PAIR_TO_UINT16_T('T', 'S'),
    STOPS_OR_AT_PASS_FOR_TABLET_STAFF_OR_TOKEN =            CHAR_PAIR_TO_UINT16_T('T', 'W'),
    STOPS_TO_TAKE_UP_PASSENGERS =                           CHAR_PAIR_TO_UINT16_T('U', ' '),
    STOPS_TO_ATTACH_VEHICLES =                              CHAR_PAIR_TO_UINT16_T('-', 'U'),
    STOPS_FOR_WATERING_OF_COACHES =                         CHAR_PAIR_TO_UINT16_T('W', ' '),
    PASSES_ANOTHER_TRAIN_AT_CROSSING_POINT_ON_SINGLE_LINE = CHAR_PAIR_TO_UINT16_T('X', ' ')
} ActivityCode;

typedef uint16_t ActivityCode_t;

#define DARWIN_ACT
/**
 * \struct ActivityType
 * \brief Activity Type (a set of 6 x 2 character strings).  Full details are provided in Common Interface File End User Specification.
 */
typedef struct {
    ActivityCode_t activities[DARWIN_ACTIVITY_CODES_COUNT_MAX]; ///< Up to 6 activity codes
    uint8_t null_terminator; ///< Null terminator for c-string compatibility
} ActivityType;

#define DARWIN_PLATFORMTYPE_MIN_STRING_LENGTH   1
#define DARWIN_PLATFORMTYPE_MAX_STRING_LENGTH   3
#define DARWIN_PLATFORMTYPE_MAX_BYTES_LENGTH   (DARWIN_PLATFORMTYPE_MAX_STRING_LENGTH + 1)
/**
 * \struct PlatformType
 * \brief Platform number
 */
typedef struct {
    char string[DARWIN_PLATFORMTYPE_MAX_BYTES_LENGTH];
} PlatformType;

/**
 * \struct WTimeType
 * \brief Working scheduled time as HH:MM[:SS]
 */
typedef struct {
    uint8_t hour; ///< Hour (0-23)
    uint8_t minute; ///< Minute (0-59)
    uint8_t second; ///< Second (0-59, optional)
    bool secondValid; ///< True if second field is populated
} WTimeType;

/**
 * \struct RTTITimeType
 * \brief Time as HH:MM
 */
typedef struct {
    uint8_t hour; ///< Hour (0-23)
    uint8_t minute; ///< Minute (0-59)
} RTTITimeType;

typedef int16_t DelayValueType; ///< A signed delay value as a number of minutes

/**
 * \struct CircularTimes
 * \brief A scheduled time used to distinguish a location on circular routes.
 *
 * Note that all scheduled time attributes are marked as optional, but at least one must always be supplied.
 * Only one value is required, and typically this should be the wtd value. However, for locations that have no wtd,
 * or for clients that deal exclusively with public times, another value that is valid for the location may be supplied.
 */
typedef struct{
    WTimeType wta; ///< Working time of arrival.
    WTimeType wtd; ///< Working time of departure.
    WTimeType wtp; ///< Working time of pass.
    RTTITimeType pta; ///< Public time of arrival.
    RTTITimeType ptd; ///< Public time of departure.
} CircularTimes;

/**
 * \struct RTTIDateTimeType
 * \brief RTTI DateTime Type (basic XML date/time)
 */
typedef struct {
    RTTIDateType date;
    RTTITimeType time;
} RTTIDateTimeType;

#define DARWIN_TIMETABLEFILENAMETYPE_MIN_STRING_LENGTH   1
#define DARWIN_TIMETABLEFILENAMETYPE_MAX_STRING_LENGTH   128
#define DARWIN_TIMETABLEFILENAMETYPE_MAX_BYTES_LENGTH   (DARWIN_TIMETABLEFILENAMETYPE_MAX_STRING_LENGTH + 1)
/**
 * \struct TimetableFilenameType
 * \brief The name of a timetable file that can be downloaded via FTP.
 */
typedef struct {
    char string[DARWIN_TIMETABLEFILENAMETYPE_MAX_BYTES_LENGTH];
} TimetableFilenameType;



#define DARWIN_SNAPSHOTIDTYPE_MAX_STRING_LENGTH   40
#define DARWIN_SNAPSHOTIDTYPE_MAX_BYTES_LENGTH   (DARWIN_SNAPSHOTIDTYPE_MAX_STRING_LENGTH + 1)
/**
 * \struct SnapshotIDType
 * \brief Defines the ID for a snapshot file to be recovered via FTP
 */
typedef struct {
    char string[DARWIN_SNAPSHOTIDTYPE_MAX_BYTES_LENGTH];
} SnapshotIDType;

#define DARWIN_DCISREQUESTID_MIN_STRING_LENGTH   1
#define DARWIN_DCISREQUESTID_MAX_STRING_LENGTH   16
#define DARWIN_DCISREQUESTID_MAX_BYTES_LENGTH   (DARWIN_DCISREQUESTID_MAX_STRING_LENGTH + 1)
/**
 * \struct DCISRequestID
 * \brief A DCIS client request identifier
 */
typedef struct {
    char string[DARWIN_DCISREQUESTID_MAX_BYTES_LENGTH];
} DCISRequestID;

#define DARWIN_SOURCETYPEINST_STRING_LENGTH   4
#define DARWIN_SOURCETYPEINST_BYTES_LENGTH   (DARWIN_SOURCETYPEINST_STRING_LENGTH + 1)
/**
 * \struct SourceTypeInst
 * \brief A RTTI CIS code, provided if forecast or actual source type is CIS
 */
typedef struct {
    char string[DARWIN_SOURCETYPEINST_BYTES_LENGTH];
} SourceTypeInst;

/**
 * \enum ToiletStatus
 * \brief The service status of a toilet in coach formation data.
 */
typedef enum{
    TOILET_STATUS_UNKNOWN = 0,
    TOILET_STATUS_IN_SERVICE = 1,
    TOILET_STATUS_NOT_IN_SERVICE = 2
} ToiletStatus;
#define DARWIN_TOILET_STATUS_DEFAULT    TOILET_STATUS_IN_SERVICE
static const char* darwin_toilet_status_strings[] = {"Unknown", "InService","NotInService"};

#define DARWIN_TOILET_TYPE_UNKNOWN      "Unknown"
#define DARWIN_TOILET_TYPE_NONE         "None"
#define DARWIN_TOILET_TYPE_STANDARD     "Standard"
#define DARWIN_TOILET_TYPE_ACCESSIBLE   "Accessible"

/**
 * \struct ToiletType
 * \brief An indication of the availability of a toilet in a coach in a train formation. E.g. "Unknown", "None" , "Standard" or "Accessible". Note that other values may be supplied in the future without a schema change.
 */
typedef struct {
    char** string; ///< Pointer to string. Must be freed after use.
    uint32_t len; ///< Length of string including null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
} ToiletType;

/**
 * \struct ToiletAvailabilityType
 * \brief The availability of a toilet in coach formation data. If no availability is supplied, it should be assumed to have the value "Unknown".
 */
typedef struct {
    ToiletType type;
    ToiletStatus status; ///< The service status of this toilet. E.g. "Unknown", "InService" or "NotInService".
} ToiletAvailabilityType;

#define DARWIN_COACHNUMBERTYPE_MIN_STRING_LENGTH   1
#define DARWIN_COACHNUMBERTYPE_MAX_STRING_LENGTH   2
#define DARWIN_COACHNUMBERTYPE_MAX_BYTES_LENGTH   (DARWIN_COACHNUMBERTYPE_MAX_STRING_LENGTH + 1)
/**
 * \struct CoachNumberType
 * \brief A Coach number/identifier in a train formation. E.g. "A" or "12".
 */
typedef struct {
    char string[DARWIN_COACHNUMBERTYPE_MAX_BYTES_LENGTH];
} CoachNumberType;

#define DARWIN_COACHCLASSTYPE_FIRST     "First"
#define DARWIN_COACHCLASSTYPE_STANDARD  "Standard"
#define DARWIN_COACHCLASSTYPE_MIXED     "Mixed"
/**
 * \struct CoachClassType
 * \brief An indication of the class of a coach in a train formation. E.g. "First", "Standard" or "Mixed".
 */
typedef struct {
    char** string; ///< Pointer to string. Must be freed after use.
    uint32_t len; ///< Length of string including null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
} CoachClassType;

#define DARWIN_FORMATIONIDTYPE_MIN_STRING_LENGTH   1
#define DARWIN_FORMATIONIDTYPE_MAX_STRING_LENGTH   20
#define DARWIN_FORMATIONIDTYPE_MAX_BYTES_LENGTH   (DARWIN_FORMATIONIDTYPE_MAX_STRING_LENGTH + 1)
/**
 * \struct FormationIDType
 * \brief A unique identifier for a train formation.
 */
typedef struct {
    char string[DARWIN_FORMATIONIDTYPE_MAX_BYTES_LENGTH];
} FormationIDType;

#define DARWIN_TRAINLENGTHTYPE_MAX_INCLUSIVE        99
// schema says unsigned short, but if our max is 99 then uchar is fine
typedef uint8_t TrainLengthType; ///< Defines the length of a train

#define DARWIN_LOADINGVALUE_MAX_INCLUSIVE        100
// schema says unsigned int, but if our max is 100 then uchar is fine
typedef uint8_t LoadingValue; ///< A value representing the loading of a train coach as a percentage (0-100%).

#endif //FM28L_COMMON_TYPES_H
