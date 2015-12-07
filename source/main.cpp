/*
 * Copyright (c) 2015 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "sockets/UDPSocket.h"
#include "EthernetInterface.h"
#include "minar/minar.h"
#include "security.h"
#include "simpleclient.h"
#include "lwipv4_init.h"

using namespace mbed::util;

Serial output(USBTX, USBRX);

EthernetInterface eth;

MbedClient mbed_client; // Instantiate the class which implements LWM2M Client API

// Set up Hardware interrupt button.
InterruptIn obs_button(SW2);
InterruptIn unreg_button(SW3);

void app_start(int /*argc*/, char* /*argv*/[]) {

    //Sets the console baud-rate
    output.baud(115200);

    // This sets up the network interface configuration which will be used
    // by LWM2M Client API to communicate with mbed Device server.
    eth.init();     //Use DHCP
    eth.connect();

    lwipv4_socket_init();
    output.printf("IP address %s\r\n", eth.getIPAddress());

    // Unregister button press will unregister endpoint from connector.mbed.com
    unreg_button.fall(&mbed_client,&MbedClient::test_unregister);

    // Observation Button press will send update of endpoint resource values to connector
    obs_button.fall(&mbed_client,&MbedClient::update_resource);

    // Create endpoint interface to manage register and unregister
    mbed_client.create_interface();

    // Create Objects of varying types, see simpleclient.h for more details on implementation.
    M2MSecurity* register_object = mbed_client.create_register_object(); // server object specifying connector info
    M2MDevice*   device_object   = mbed_client.create_device_object();   // device resources object
    M2MObject*   generic_object  = mbed_client.create_generic_object();  // generic object with custom resources

    // Create list of Objects to register
    M2MObjectList object_list;
    
    // Add objects to list
    object_list.push_back(device_object);
    object_list.push_back(generic_object);

    // Set endpoint registration object 
    mbed_client.set_register_object(register_object);

    // Issue register command.
    FunctionPointer2<void, M2MSecurity*, M2MObjectList> fp(&mbed_client, &MbedClient::test_register);
    minar::Scheduler::postCallback(fp.bind(register_object,object_list));
    minar::Scheduler::postCallback(&mbed_client,&MbedClient::test_update_register).period(minar::milliseconds(25000));
}
