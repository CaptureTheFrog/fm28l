//
// Created by eddie on 13/02/24.
//

#ifndef FM28L_PUSH_PORT_TRAIN_ALERTS_H
#define FM28L_PUSH_PORT_TRAIN_ALERTS_H

/*
 * TrainAlerts is not documented very well in the XSD schema. Most docstrings are "to do", so have been ommitted here.
 * Additionally, many types are unbound strings or unbound arrays of strings. This could be narrowed in future schema revisions.
 */

#include "common_types.h"

typedef struct{
    char** string; ///< Pointer to string. Must be freed after use.
    uint32_t len; ///< Length of string including null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
} AlertServiceLocationString;

typedef struct{
    AlertServiceLocationString* locations; ///< Array of locations. Must be freed after use.
    uint32_t locationCount; ///< Number of locations. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    RIDType rid;
    UIDType uid;
    RTTIDateType ssd;
} AlertService;

/**
 * \enum AlertAudienceType
 */
typedef enum{
    ALERT_AUDIENCE_TYPE_CUSTOMER = 0, ///< Customer
    ALERT_AUDIENCE_TYPE_STAFF, ///< Staff
    ALERT_AUDIENCE_TYPE_OPERATIONS, ///< Operations
} AlertAudienceType;
static const char* darwin_alert_audience_type_strings[] = {"Customer", "Staff", "Operations"};

/**
 * \enum AlertType
 */
typedef enum{
    ALERT_TYPE_NORMAL = 0, ///< Normal
    ALERT_TYPE_FORCED, ///< Forced
} AlertType;
static const char* darwin_alert_type_strings[] = {"Normal", "Forced"};

/**
 * \struct TrainAlert
 * \brief Train Alert
 */
typedef struct{
    char** alertIDString; ///< Pointer to string for the alert ID. Must be freed after use.
    uint32_t alertIDLen; ///< Length of string for the alert ID including null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    AlertService* alertServices; /// Array of services to which the alert applies. Must be freed after use.
    uint32_t alertServicesCount; ///< Number of alert services. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    bool SendAlertBySMS;
    bool SendAlertByEmail;
    bool SendAlertByTwitter;
    char** sourceString; ///< Pointer to string for the source. Must be freed after use.
    uint32_t sourceLen; ///< Length of string for the source including null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    char** alertTextString; ///< Pointer to string for the alert text. Must be freed after use.
    uint32_t alertTextLen; ///< Length of string for the alert text including null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    AlertAudienceType audience;
    AlertType alertType;
    char** copiedFromAlertIDString; ///< Pointer to string for the CopiedFromAlertID. Must be freed after use.
    uint32_t copiedFromAlertIDLen; ///< Length of string for the CopiedFromAlertID including null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    char** copiedFromSourceString; ///< Pointer to string for the CopiedFromSource. Must be freed after use.
    uint32_t copiedFromSourceLen; ///< Length of string for the CopiedFromSource including null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
} TrainAlert;

#endif //FM28L_PUSH_PORT_TRAIN_ALERTS_H
