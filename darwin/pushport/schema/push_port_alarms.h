//
// Created by eddie on 13/02/24.
//

#ifndef FM28L_PUSH_PORT_ALARMS_H
#define FM28L_PUSH_PORT_ALARMS_H

#include "common_types.h"

/**
 * \struct AlarmID
 * \brief Type representing a unique Darwin alarm identifier.
 */
typedef struct{
    char** string; ///< Pointer to string for the alarm ID. Must be freed after use.
    uint32_t len; ///< Length of string for the alarm ID icnluding null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
} AlarmID;

/**
 * \enum AlarmType
 * \brief The type of the alarm.
 */
typedef enum{
    DARWIN_ALARMTYPE_TDAREAFAIL = 0,
    DARWIN_ALARMTYPE_TDFEEDFAIL,
    DARWIN_ALARMTYPE_TYRELLFEEDFAIL
} AlarmType;
static const char* darwin_alarm_type_strings[] = {"tdAreaFail", "tdFeedFail", "tyrellFeedFail"};

/**
 * \struct RTTIAlarmData
 * \brief Type describing each type of alarm that can be set.
 */
typedef struct{
    AlarmID id; ///< Unique identifier for this alarm
    AlarmType alarmType; ///< Type of alarm
    TDAreaIDType areaFail; ///< Alarm for a single TD area failure. Contents identify the failed area code. Valid with DARWIN_ALARMTYPE_TDAREAFAIL only.
} RTTIAlarmData;

/**
 * \struct RTTIAlarm
 * \brief An update to a Darwin alarm.
 */
typedef struct{
    bool set; ///< True if this is a set message, else a clear message
    union{
        RTTIAlarmData setAlarmData; ///< Alarm data for a set message
        AlarmID clearAlarmID; ///< Alarm ID for a clear message
    };
} RTTIAlarm;

#endif //FM28L_PUSH_PORT_ALARMS_H
