//
// Created by eddie on 09/02/24.
//

#ifndef FM28L_PUSH_PORT_H
#define FM28L_PUSH_PORT_H

#include "common_types.h"
#include "push_port_status.h"
#include "xml_timetable.h"
#include "push_port_schedules.h"
#include "push_port_formations.h"
#include "push_port_forecasts.h"
#include "push_port_station_messages.h"
#include "push_port_train_alerts.h"
#include "push_port_train_order.h"
#include "push_port_td_data.h"
#include "push_port_alarms.h"

/*
 * Note: SuffixType is not implemented here as it does not appear to be used in v16 of the schema
 */

typedef enum{
    QueryTimetableMessage, ///< Query for the current timetable ID
    TimeTableIdMessage, ///< Response for the current timetable ID
    GetSnapshotReqMessage, ///< Request a standard snapshot of current database
    GetFullSnapshotReqMessage, ///< Request a full snapshot of current database
    SnapshotIdMessage, ///< Defines an ID for recovering snapshot data via FTP
    StartUpdateReqMessage, ///< Start sending available updates.
    StopUpdateReqMessage, ///< Stop sending available updates.
    FailureRespMessage, ///< Failure Response
    uRMessage, ///< Update Response
    sRMessage, ///< Snapshot Response
} MessageType;

/**
 * \struct Pport
 * \brief Push Ports Schema
 */
typedef struct{
    RTTIDateTimeType ts; ///< Local Timestamp
    char* version; ///< Version string. Must be freed after use.
    MessageType messageType; ///< Type of the Pport message
    void* data; ///< Pointer to data struct according to messageType
} Pport;

/**
 * \struct PportTimetableId
 * \brief Response for the current timetable ID
 */
typedef struct{
    TimetableIDType timetableId;
    TimetableFilenameType ttfile;
    TimetableFilenameType ttreffile;
} PportTimeTableId;

#define DARWIN_GETSNAPSHOTREQ_VIAFTP_DEFAULT            FALSE
/**
 * \struct GetSnapshotReq
 * \brief Request a standard snapshot of current database
 */
typedef struct{
    bool viaftp; ///< If true, then resulting snapshot data is fetched by the client via FTP
} GetSnapshotReq;

#define DARWIN_GETFULLSNAPSHOTREQ_VIAFTP_DEFAULT            FALSE
/**
 * \struct GetFullSnapshotReq
 * \brief Request a full snapshot of current database
 */
typedef struct{
    bool viaftp; ///< If true, then resulting snapshot data is fetched by the client via FTP
} GetFullSnapshotReq;

/**
 * \struct SnapshotId
 * \brief Defines an ID for recovering snapshot data via FTP
 */
typedef struct{
    SnapshotIDType snapshotId; ///< Defines an ID for recovering snapshot data via FTP
} SnapshotId;

/**
 * \struct FailureResp
 * \brief Defines an ID for recovering snapshot data via FTP
 */
typedef struct{
    StatusType status;
    SourceTypeInst requestSource; ///< The DCIS source that generated this update
    DCISRequestID requestID; ///< The DCISRequestID value provided by the originator of this update. Used in conjunction with the updateSource attribute to ensure uniqueness
} FailureResp;

/**
 * \struct DataResponse
 * \brief Update Response
 */
typedef struct{
    Schedule* schedules; ///< Array of schedules in this response. Must be freed after use.
    uint32_t scheduleCount; ///< Number of schedules in this response. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    DeactivatedSchedule* deactivateds; ///< Array of deactivated schedules in this response. Must be freed after use.
    uint32_t deactivatedCount; ///< Number of deactivated schedules in this response. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    Association* associations; ///< Array of associations in this response. Must be freed after use.
    uint32_t associationCount; ///< Number of associations in this response. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    ScheduleFormations* scheduleFormations; ///< Array of schedule formations in this response. Must be freed after use.
    uint32_t scheduleFormationCount; ///< Number of schedule formations in this response. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    TS* tses; ///< Array of TSes in this response. Must be freed after use.
    uint32_t tsCount; ///< Number of TSes in this response. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    Loading* formationLoadings; ///< Array of formation loadings in this response. Must be freed after use.
    uint32_t formationLoadingCount; ///< Number of formation loadings in this response. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    StationMessage* ows; ///< Array of darwin workstation messages in this response. Must be freed after use.
    uint32_t owCount; ///< Number of darwin workstation messages in this response. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    TrainAlert* trainAlerts; ///< Array of train alerts in this response. Must be freed after use.
    uint32_t trainAlertCount; ///< Number of train alerts in this response. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    TrainOrder* trainOrders; ///< Array of train orders in this response. Must be freed after use.
    uint32_t trainOrderCount; ///< Number of train orders in this response. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    TrackingID* trackingIDs; ///< Array of tracking IDs in this response. Must be freed after use.
    uint32_t trackingIDCount; ///< Number of tracking IDs in this response. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    RTTIAlarm* alarms; ///< Array of alarms in this response. Must be freed after use.
    uint32_t alarmCount; ///< Number of alarms in this response. Theoretically infinite but limited to 32-bit unsigned int in this implementation
} DataResponse;

/**
 * \struct uR
 * \brief Update Response
 */
typedef struct{
    DataResponse dataResponse;
    char** updateOriginString; ///< Pointer to string for a string describing the type of system that originated this update, e.g. "CIS" or "Darwin". Must be freed after use.
    uint32_t updateOriginLen; ///< Length of string for the update origin including null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    SourceTypeInst requestSource; ///< The source instance that generated this update, usually a CIS instance.
    DCISRequestID requestID; ///< The DCISRequestID value provided by the originator of this update. Used in conjunction with the requestSource attribute to ensure uniqueness
} uR;

/**
 * \struct sR
 * \brief Snapshot Response
 */
typedef struct{
    DataResponse dataResponse;
} sR;

#endif //FM28L_PUSH_PORT_H
