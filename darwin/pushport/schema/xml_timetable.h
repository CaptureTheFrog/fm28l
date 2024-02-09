//
// Created by eddie on 09/02/24.
//

#ifndef FM28L_XML_TIMETABLE_H
#define FM28L_XML_TIMETABLE_H

#include "common_types.h"

typedef enum{
    OR = CHAR_QUAD_TO_UINT32_T('O', 'R', '\0', '\0'), ///< Origin location
    OPOR = CHAR_QUAD_TO_UINT32_T('O', 'P', 'O', 'R'), ///< Operational origin location
    IP = CHAR_QUAD_TO_UINT32_T('I', 'P', '\0', '\0'), ///< Intermediate calling location
    OPIP = CHAR_QUAD_TO_UINT32_T('O', 'P', 'I', 'P'), ///< Intermediate operational calling location
    PP = CHAR_QUAD_TO_UINT32_T('P', 'P', '\0', '\0'), ///< Passing location
    DT = CHAR_QUAD_TO_UINT32_T('D', 'T', '\0', '\0'), ///< Destination location
    OPDT = CHAR_QUAD_TO_UINT32_T('O', 'P', 'D', 'T'), ///< Operational destination location
} ScheduleEventTypeType;

typedef uint32_t ScheduleEventTypeType_t;

#define DARWIN_RDELAY_DEFAULT           ((DelayValueType)0)
typedef struct{
    ScheduleEventTypeType_t scheduleEventType; ///< Type of schedule event (OR, OPOR, IP, OPIP, PP, DT, OPDT)
    TIPLOCType tpl; ///< TIPLOC
    ActivityType act; ///< Current Activity Codes
    ActivityType planAct; ///< Planned Activity Codes (if different to current activities)
    bool can; ///< Cancelled
    PlatformType plat; ///< Platform number
    RTTITimeType pta; ///< Public Scheduled Time of Arrival
    RTTITimeType ptd; ///< Public Scheduled Time of Departure
    WTimeType wta; ///< Working Scheduled Time of Arrival
    WTimeType wtd; ///< Working Scheduled Time of Departure
    DelayValueType rdelay; ///< A delay value that is implied by a change to the service's route.
    TIPLOCType fd; ///< TIPLOC of False Destination to be used at this location
} ScheduleEventType;

#define DARWIN_SCHEDULE_MIN_SCHEDULE_EVENTS   2
/**
 * \struct Schedule
 * \brief Schedule of a service that exists in Darwin
 */
typedef struct {
    RIDType rid; ///< RTTI unique Train ID
    UIDType uid; ///< Train UID
    TrainIdType trainId; ///< Train ID (Headcode)
    RTTIDateType ssd; ///< Scheduled Start Date
    TOCType toc; ///< ATOC Code
    CIFTrainStatusType status; ///< Type of service, i.e. Train/Bus/Ship.
    CIFTrainCategoryType trainCat; ///< Category of service.
    bool isPassengerSvc; ///< True if Darwin classifies the train category as a passenger service.
    bool deleted; ///< Service has been deleted and should not be used/displayed.
    bool isCharter; ///< Indicates if this service is a charter service.
    bool qtrain; ///< True if this is a Q Train (runs as required) that has not yet been activated. Note that a Q Train that has been activated before the XML Timetable file has been built will not have this attribute set true.
    bool can;
    ScheduleEventType* scheduleEvents; ///< Array of schedule events for this schedule. Must be freed after use.
    uint32_t scheduleEventsCount; ///< Number of schedule events for this schedule. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    DisruptionReasonType cancelReason; ///< Reason for cancellation of service/location
} Schedule;

typedef enum{
    JOIN = CHAR_PAIR_TO_UINT16_T('J', 'J'), ///< Join
    SPLIT = CHAR_PAIR_TO_UINT16_T('V', 'V'), ///< Split
    LINKED = CHAR_PAIR_TO_UINT16_T('L', 'K'), ///< Linked
    NEXT_WORKING = CHAR_PAIR_TO_UINT16_T('N', 'P'), ///< Next Working
} CategoryType;

typedef uint16_t CategoryType_t;

/**
 * \struct Association
 * \brief An association between two schedules
 */
typedef struct{
    TIPLOCType tiploc; ///< The TIPLOC of the location where the association occurs.
    CategoryType_t category; ///< Association category
    bool isCancelled; ///< True if this association is cancelled, i.e. the association exists but will no longer happen.
    bool isDeleted; ///< True if this association is deleted, i.e. the association no longer exists.
} Association;

#define DARWIN_PPORTTIMETABLE_ELEMENT_NAME_JOURNEY              "Journey"
#define DARWIN_PPORTTIMETABLE_ELEMENT_NAME_ASSOCIATION          "Association"
/**
 * \struct PportTimetable
 * \brief Push Port Timetable Schema
 */
 typedef struct{
     TimetableIDType timetableID; ///< The ID of the RTTI timetable from which this XML timetable was generated.
     Schedule* journeys; ///< Array of journeys in this timetable. Must be freed after use.
     uint32_t journeyCount; ///< Number of journeys in this timetable. Theoretically infinite but limited to 32-bit unsigned int in this implementation
     Association* associations; ///< Array of associations in this timetable. Must be freed after use.
     uint32_t associationCount; ///< Number of associations in this timetable. Theoretically infinite but limited to 32-bit unsigned int in this implementation
 } PportTimetable;

#endif //FM28L_XML_TIMETABLE_H
