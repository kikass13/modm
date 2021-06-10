/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * Copyright 2021 DroidDrive GmbH
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _EMBEDDED_RPC__MODM_DEVICE_TRANSPORT_H_
#define _EMBEDDED_RPC__MODM_DEVICE_TRANSPORT_H_

#include "erpc_framed_transport.h"

#include <modm/architecture/utils.hpp>
#include <modm/processing/timer.hpp>
#include <modm/processing/resumable.hpp>


namespace erpc {

class Device
{
public:
	virtual bool hasReceived() = 0;

    virtual erpc_status_t connect() = 0;

	virtual erpc_status_t write(const uint8_t* data, uint32_t size) = 0;

	virtual erpc_status_t read(uint8_t* data, uint32_t size) = 0;
};


class ModmDeviceTransport : public FramedTransport
{
public:
    /*!
     * @brief Constructor.
     *
     * This function initializes object attributes.
     *
     * @param[in] Device
     */
    ModmDeviceTransport(Device* device);

    /*!
     * @brief ModmDeviceTransport destructor
     */
    virtual ~ModmDeviceTransport(void);

protected:
    Device* device_;

    /*!
     * @brief This function connect client to the server.
     *
     * @retval kErpcStatus_Success When client connected successfully.
     * @retval kErpcStatus_Fail When client doesn't connected successfully.
     */
    virtual erpc_status_t connectClient(void);

    /*!
     * @brief This function read data.
     *
     * @param[inout] data Preallocated buffer for receiving data.
     * @param[in] size Size of data to read.
     *
     * @retval #kErpcStatus_Success When data was read successfully.
     * @retval #kErpcStatus_ReceiveFailed When reading data ends with error.
     * @retval #kErpcStatus_ConnectionClosed Peer closed the connection.
     */

    virtual bool hasMessage(void) override;

    virtual erpc_status_t underlyingReceive(uint8_t *data, uint32_t size);

    /*!
     * @brief This function writes data.
     *
     * @param[in] data Buffer to send.
     * @param[in] size Size of data to send.
     *
     * @retval #kErpcStatus_Success When data was written successfully.
     * @retval #kErpcStatus_SendFailed When writing data ends with error.
     * @retval #kErpcStatus_ConnectionClosed Peer closed the connection.
     */
    virtual erpc_status_t underlyingSend(const uint8_t *data, uint32_t size);

private:
    erpc_status_t send__(const uint8_t* data, uint32_t size);
    erpc_status_t receive__(uint8_t* data, uint32_t size);
};

} // namespace erpc

/*! @} */

#endif // _EMBEDDED_RPC__MODM_DEVICE_TRANSPORT_H_
