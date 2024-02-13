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

/**
 * \struct TrackingID
 * \brief Indicate a corrected Tracking ID (headcode) for a service in a TD berth.
 */
typedef struct {
    FullTDBerthID berth; ///< The TD berth where the incorrectly reported train has been identified to be. Note that this berth is that which was reported to Darwin and there is no guarantee that the train is still in this berth at any subsequent point in time.
    TrainIdType incorrectTrainID; ///< The incorrect Train ID (headcode) that is being reported by TD.NET.
    TrainIdType correctTrainID; ///< The correct Train ID (headcode) that should be reported by TD.NET.
} TrackingID;

#endif //FM28L_PUSH_PORT_TD_DATA_H
