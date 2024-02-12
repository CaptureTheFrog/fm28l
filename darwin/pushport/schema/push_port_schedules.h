//
// Created by eddie on 12/02/24.
//

#ifndef FM28L_PUSH_PORT_SCHEDULES_H
#define FM28L_PUSH_PORT_SCHEDULES_H

#include "common_types.h"

/**
 * \struct DeactivatedSchedule
 * \brief Notification that a Train Schedule is now deactivated in Darwin.
 */
typedef struct{
    RIDType rid; ///< RTTI unique Train ID
} DeactivatedSchedule;

#endif //FM28L_PUSH_PORT_SCHEDULES_H
