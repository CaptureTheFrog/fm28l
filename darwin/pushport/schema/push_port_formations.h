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

#endif //FM28L_PUSH_PORT_FORMATIONS_H
