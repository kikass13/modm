/*
 * Copyright 2020 (c) Sierra Wireless
 * Copyright 2021 ACRIOS Systems s.r.o.
 * Copyright 2021 DroidDrive GmbH
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "erpc_manually_constructed.h"
#include "erpc_modm_device_transport.h"
#include "erpc_transport_setup.h"

using namespace erpc;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

static ManuallyConstructed<ModmDeviceTransport> transportA;
static ManuallyConstructed<ModmDeviceTransport> transportB;
static bool i = true;
////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
erpc_transport_t erpc_transport_modm_device_init(Device* device)
{
    erpc_transport_t transport;
    if(i){
        transportA.construct(device);
        transport = reinterpret_cast<erpc_transport_t>(transportA.get());
    }
    else{
        transportB.construct(device);
        transport = reinterpret_cast<erpc_transport_t>(transportB.get());

    }
    i = !i;
    return transport;
}

