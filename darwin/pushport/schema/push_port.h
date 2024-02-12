//
// Created by eddie on 09/02/24.
//

#ifndef FM28L_PUSH_PORT_H
#define FM28L_PUSH_PORT_H

#include "common_types.h"
#include "push_port_status.h"

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

#endif //FM28L_PUSH_PORT_H
