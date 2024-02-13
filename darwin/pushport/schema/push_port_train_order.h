//
// Created by eddie on 13/02/24.
//

#ifndef FM28L_PUSH_PORT_TRAIN_ORDER_H
#define FM28L_PUSH_PORT_TRAIN_ORDER_H

#include "common_types.h"

/**
 * \struct TrainOrderItem
 * \brief A train in the train order.
 */
typedef struct{
    RIDType rid; ///< documentation For trains in the train order where the train is the Darwin timetable, it will be identified by its RID
    CircularTimes circularTimes; ///< only supplied with rid, not with trainID
    TrainIdType trainID; ///< Where a train in the train order is not in the Darwin timetable, a Train ID (headcode) will be supplied
} TrainOrderItem;

#define DARWIN_TRAINORDERDATA_TRAINORDERITEMS_COUNT     3
/**
 * \struct TrainOrderData
 * \brief Defines the sequence of trains making up the train order
 */
typedef struct{
    TrainOrderItem trainOrderItems[DARWIN_TRAINORDERDATA_TRAINORDERITEMS_COUNT];
} TrainOrderData;

/**
 * \enum TrainOrderMessageType
 * \brief Specifies if the train order message is to set or clear the train order.
 */
typedef enum{
    TRAINORDER_MESSAGE_TYPE_CLEAR,
    TRAINORDER_MESSAGE_TYPE_SET,
} TrainOrderMessageType;

/**
 * \struct TrainOrder
 * \brief Defines the expected Train order at a platform
 */
typedef struct{
    TIPLOCType tiploc; ///< The tiploc where the train order applies
    CRSType crs; ///< The CRS code of the station where the train order applies
    PlatformType platform; ///< The platform number where the train order applies
    TrainOrderMessageType messageType; ///< Specifies if the message is a "set" or "clear" message.
    TrainOrderData setTrainOrderData; ///< The train order data of a set message
} TrainOrder;

#endif //FM28L_PUSH_PORT_TRAIN_ORDER_H
