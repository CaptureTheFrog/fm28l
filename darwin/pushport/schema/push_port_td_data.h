//
// Created by eddie on 13/02/24.
//

#ifndef FM28L_PUSH_PORT_TD_DATA_H
#define FM28L_PUSH_PORT_TD_DATA_H

#include "common_types.h"

/**
 * \struct FullTDBerthID
 * \brief A TD berth identifier.
 */
typedef struct {
    TDAreaIDType area;
    TDBerthIDType berth;
} FullTDBerthID;

#endif //FM28L_PUSH_PORT_TD_DATA_H
