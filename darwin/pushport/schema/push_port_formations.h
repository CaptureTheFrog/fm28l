//
// Created by eddie on 12/02/24.
//

#ifndef FM28L_PUSH_PORT_FORMATIONS_H
#define FM28L_PUSH_PORT_FORMATIONS_H

#include "common_types.h"

/**
 * \struct CoachData
 * \brief Data for an individual coach in a formation.
 */
typedef struct{
    CoachNumberType coachNumber; ///< The number/identifier for this coach, e.g. "A".
    CoachClassType coachClass; ///< The class of the coach, e.g. "First" or "Standard".
    ToiletAvailabilityType toiletAvailability;
} CoachData;

/**
 * \struct CoachList
 * \brief A list of coach data for a formation.
 */
typedef struct{
    CoachData* coaches; ///< Array of coaches. Must be freed after use.
    uint32_t coachCount; ///< Number of coaches. Theoretically infinite but limited to 32-bit unsigned int in this implementation
} CoachList;

/**
 * \struct Formation
 * \brief Type describing a Train Formation for a Schedule.
 */
typedef struct{
    CoachList coaches; ///< A list of coaches in this formation.
    FormationIDType fid; ///< The unique identifier of this formation data.
    char** srcString; ///< Pointer to string for the source of the formation data. Must be freed after use.
    uint32_t srcLen; ///< Length of string for the source of the formation data including null terminator. Theoretically infinite but limited to 32-bit unsigned int in this implementation
    SourceTypeInst srcInst; ///< The RTTI instance ID of the src (if any).
} Formation;

#endif //FM28L_PUSH_PORT_FORMATIONS_H
