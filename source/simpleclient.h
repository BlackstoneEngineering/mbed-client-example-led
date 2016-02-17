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

#ifndef __SIMPLECLIENT_H__
#define __SIMPLECLIENT_H__

#include "sockets/UDPSocket.h"
#include "EthernetInterface.h"
#include "test_env.h"
#include "mbed-client/m2minterfacefactory.h"
#include "mbed-client/m2mdevice.h"
#include "mbed-client/m2minterfaceobserver.h"
#include "mbed-client/m2minterface.h"
#include "mbed-client/m2mobject.h"
#include "mbed-client/m2mobjectinstance.h"
#include "mbed-client/m2mresource.h"
#include "minar/minar.h"
#include "security.h"
#include <cmath>


//Select binding mode: UDP or TCP
M2MInterface::BindingMode SOCKET_MODE = M2MInterface::UDP;

// This is address to mbed Device Connector
const String &MBED_SERVER_ADDRESS = "coap://api.connector.mbed.com:5684";

// These come from the security.h file copied from connector.mbed.com
const String &MBED_USER_NAME_DOMAIN = MBED_DOMAIN;
const String &ENDPOINT_NAME = MBED_ENDPOINT_NAME;

// These are example resource values for the Device Object
const String &MANUFACTURER = "spiffy";
const String &TYPE = "led";
const String &MODEL_NUMBER = "NCC-74656";
const String &SERIAL_NUMBER = "1701";

#define LED_OFF 1
#define LED_ON 0

/*
* Wrapper for mbed client stack that handles all callbacks, error handling, and
* other schenanigans to make the mbed client stack easier to use.
* 
* The end user should only have to care about configuring the parameters at the
* top of this file and making sure they add the security.h file correctly.
* To add resources you can copy the _TODO__ function and add as many instances as
* you want.
* 
*/
class MbedClient: public M2MInterfaceObserver {
public:

    /*
    *  Callback function to handle POST data, registed below
    *  The argument passed in is a null terminated string representing the POST request payload. 
    */
    void redCallback(void *postData) {
        printf("\r\nred led POST callback!, payload received : '%s'\r\n",postData);
        static DigitalOut ledR(LED1);
        _red = atoi((const char *)postData);
        ledR = _red;
        
        // update mbed client stack value for the resouce accordingly
        if(_led_object) { // verify ObjectID is valid
            M2MObjectInstance* inst = _led_object->object_instance(); // grab ObjectInstance
            if(inst) {// verify ObjectInstance is valid
                    M2MResource* res = inst->resource("red"); // grab ResourceID
                    char buffOut[20];
                    int size;
                    size = sprintf(buffOut,"%d",_red);
                    res->set_value((const uint8_t*)buffOut,         // send new value to connector
                                   (const uint32_t)size);
                    //printf("\r\nres->set_value = '%s', size = '%d'\r\n",buffOut,size);
                }
        }
    }
    
    void greenCallback(void *postData) {
        printf("\r\green led POST callback!, payload received : '%s'\r\n",postData);
        static DigitalOut ledG(LED2);
        _green = atoi((const char *)postData);
        ledG = _green;
        
        // update mbed client stack value for the resouce accordingly
        if(_led_object) { // verify ObjectID is valid
            M2MObjectInstance* inst = _led_object->object_instance(); // grab ObjectInstance
            if(inst) {// verify ObjectInstance is valid
                    M2MResource* res = inst->resource("green"); // grab ResourceID
                    char buffOut[20];
                    int size;
                    size = sprintf(buffOut,"%d",_green);
                    res->set_value((const uint8_t*)buffOut,         // send new value to connector
                                   (const uint32_t)size);
                    //printf("\r\nres->set_value = '%s', size = '%d'\r\n",buffOut,size);
                }
        }
    }
    
    void blueCallback(void *postData) {
        printf("\r\nblue led POST callback!, payload received : '%s'\r\n",postData);
        static DigitalOut ledB(LED3);
        _blue = atoi((const char *)postData);
        ledB = _blue;
        
        // update mbed client stack value for the resouce accordingly
        if(_led_object) { // verify ObjectID is valid
            M2MObjectInstance* inst = _led_object->object_instance(); // grab ObjectInstance
            if(inst) {// verify ObjectInstance is valid
                    M2MResource* res = inst->resource("blue"); // grab ResourceID
                    char buffOut[20];
                    int size;
                    size = sprintf(buffOut,"%d",_blue);
                    res->set_value((const uint8_t*)buffOut,         // send new value to connector
                                   (const uint32_t)size);
                    //printf("\r\nres->set_value = '%s', size = '%d'\r\n",buffOut,size);
                }
        }
    }
    
    M2MObject* create_led_object() {// create ObjectID with metadata tag of 'Test'
        _led_object = M2MInterfaceFactory::create_object("led");
        if(_led_object) { // verify ObjectID was created
            // create ObjectInstance
            M2MObjectInstance* inst = _led_object->create_object_instance();
            if(inst) {// verify ObjectInstance was created
                    // create dynamic (changeable) ResourceID /Test/0/D, assign resource value seperately
                    M2MResource* redResource = inst->create_dynamic_resource("red","LED-red-type",M2MResourceInstance::BOOLEAN,true);
                    char buffer[20];
                    int size;
                    size = sprintf(buffer,"%d",_red);
                    redResource->set_operation(M2MBase::GET_POST_ALLOWED);
                    redResource->set_value((const uint8_t*)buffer,(const uint32_t)size);
                    redResource->set_execute_function(execute_callback(this,&MbedClient::redCallback));
                    
                    M2MResource* greenResource = inst->create_dynamic_resource("green","LED-green-type",M2MResourceInstance::BOOLEAN,true);
                    size = sprintf(buffer,"%d",_green);
                    greenResource->set_operation(M2MBase::GET_POST_ALLOWED);
                    greenResource->set_value((const uint8_t*)buffer,(const uint32_t)size);
                    greenResource->set_execute_function(execute_callback(this,&MbedClient::greenCallback));
                    
                    M2MResource* blueResource = inst->create_dynamic_resource("blue","LED-blue-type",M2MResourceInstance::BOOLEAN,true);
                    size = sprintf(buffer,"%d",_blue);
                    blueResource->set_operation(M2MBase::GET_POST_ALLOWED);
                    blueResource->set_value((const uint8_t*)buffer,(const uint32_t)size);
                    blueResource->set_execute_function(execute_callback(this,&MbedClient::blueCallback));
                    
                    
            }
        }
        return _led_object;
    }
    

    /*
    * Update the resource /Test/0/D value, in this case by one each time
    *  This code will read the last value from connector, then incriment it by 1
    *  try pressing the button, then put to the /Test/0/D resource from connector
    *   you should see the value update next time the button is pressed.
    */
    void update_resource() {
        if(_object) { // verify ObjectID is valid
            M2MObjectInstance* inst = _object->object_instance(); // grab ObjectInstance
            if(inst) {// verify ObjectInstance is valid
                    M2MResource* res = inst->resource("D"); // grab ResourceID

                    uint8_t * buffInPtr;
                    char buffOut[20];
                    uint32_t sizeIn;
                    int size;
                    res->get_value(buffInPtr,sizeIn);               // read the value from connector
                    printf("\r\nres->get_value = '%s'",buffInPtr);
                    _value = atoi((const char *)buffInPtr);
                    _value++;                                       // update the value
                    size = sprintf(buffOut,"%d",_value);
                    res->set_value((const uint8_t*)buffOut,         // send new value to connector
                                   (const uint32_t)size);
                    printf("\r\nres->set_value = '%s', size = '%d'\r\n",buffOut,size);
                }
        }
    }
 
/*****************************************************************************
 * Everything below here is just standard implementation of the class.
 * The important part for the end user is above, namely how to set up a
 * Generic object and its ObjectID/ObjectInstance/ResourceID and how to update 
 * that resources' value. 
 *****************************************************************************/

    // constructor for MbedClient object, initialize private variables
    MbedClient(){
        _interface = NULL;
        _bootstrapped = false;
        _error = false;
        _registered = false;
        _unregistered = false;
        _register_security = NULL;
        _value = 0;
        _red = LED_OFF;
        _blue = LED_OFF;
        _green = LED_OFF;
        _object = NULL;
        _led_object = NULL;
    }

    // de-constructor for MbedClient object, you can ignore this
    ~MbedClient() {
        if(_interface) {
            delete _interface;
        }
        if(_register_security){
            delete _register_security;
        }
    }

    // debug printf function
    void trace_printer(const char* str) {
        printf("\r\n%s\r\n", str);
    }

    /* 
    *  Creates M2MInterface using which endpoint can
    *  setup its name, resource type, life time, connection mode,
    *  Currently only LwIPv4 is supported.
    */
    void create_interface() {
	// Randomizing listening port for Certificate mode connectivity
	srand(time(NULL));
	uint16_t port = rand() % 65535 + 12345;

    // create mDS interface object, this is the base object everything else attaches to
    _interface = M2MInterfaceFactory::create_interface(*this,
                                                      ENDPOINT_NAME,            // endpoint name string
                                                      "test",                   // endpoint type string
                                                      3600,                     // lifetime
                                                      port,                     // listen port
                                                      MBED_USER_NAME_DOMAIN,    // domain string
                                                      SOCKET_MODE,              // binding mode
                                                      M2MInterface::LwIP_IPv4,  // network stack
                                                      "");                      // context address string
    }

    /*
    *  check private variable to see if the registration was sucessful or not
    */
    bool register_successful() {
        return _registered;
    }

    /*
    *  check private variable to see if un-registration was sucessful or not
    */
    bool unregister_successful() {
        return _unregistered;
    }

    /*
    *  Creates register server object with mbed device server address and other parameters
    *  required for client to connect to mbed device server.
    */
    M2MSecurity* create_register_object() {
        // create security object using the interface factory.
        // this will generate a security ObjectID and ObjectInstance
        M2MSecurity *security = M2MInterfaceFactory::create_security(M2MSecurity::M2MServer);
        
        // make sure security ObjectID/ObjectInstance was created successfully
        if(security) {
            // Add ResourceID's and values to the security ObjectID/ObjectInstance
            security->set_resource_value(M2MSecurity::M2MServerUri, MBED_SERVER_ADDRESS);
            security->set_resource_value(M2MSecurity::SecurityMode, M2MSecurity::Certificate);
            security->set_resource_value(M2MSecurity::ServerPublicKey,SERVER_CERT,sizeof(SERVER_CERT));
            security->set_resource_value(M2MSecurity::PublicKey,CERT,sizeof(CERT));
            security->set_resource_value(M2MSecurity::Secretkey,KEY,sizeof(KEY));
        }
        return security;
    }

    /*
    * Creates device object which contains mandatory resources linked with
    * device endpoint.
    */
    M2MDevice* create_device_object() {
        // create device objectID/ObjectInstance
        M2MDevice *device = M2MInterfaceFactory::create_device();
        // make sure device object was created successfully
        if(device) {
            // add resourceID's to device objectID/ObjectInstance
            device->create_resource(M2MDevice::Manufacturer,MANUFACTURER);
            device->create_resource(M2MDevice::DeviceType,TYPE);
            device->create_resource(M2MDevice::ModelNumber,MODEL_NUMBER);
            device->create_resource(M2MDevice::SerialNumber,SERIAL_NUMBER);
        }
        return device;
    }

    /*
    * register an object
    */
    void test_register(M2MSecurity *register_object, M2MObjectList object_list){
        if(_interface) {
            // Register function
            _interface->register_object(register_object, object_list);
        }
    }

    /*
    * unregister all objects
    */
    void test_unregister() {
        if(_interface) {
            // Unregister function
            _interface->unregister_object(NULL); // NULL will unregister all objects
        }
    }

    //Callback from mbed client stack when the bootstrap
    // is successful, it returns the mbed Device Server object
    // which will be used for registering the resources to
    // mbed Device server.
    void bootstrap_done(M2MSecurity *server_object){
        if(server_object) {
            _bootstrapped = true;
            _error = false;
            trace_printer("Bootstrapped");
        }
    }

    //Callback from mbed client stack when the registration
    // is successful, it returns the mbed Device Server object
    // to which the resources are registered and registered objects.
    void object_registered(M2MSecurity */*security_object*/, const M2MServer &/*server_object*/){
        _registered = true;
        _unregistered = false;
        trace_printer("Registered object Successfully!");
    }

    //Callback from mbed client stack when the unregistration
    // is successful, it returns the mbed Device Server object
    // to which the resources were unregistered.
    void object_unregistered(M2MSecurity */*server_object*/){
        _unregistered = true;
        _registered = false;
        notify_completion(_unregistered);
        minar::Scheduler::stop();
        trace_printer("Unregistered Object Successfully");
    }
    
    /*
    * Callback from mbed client stack when registration is updated
    */
    void registration_updated(M2MSecurity */*security_object*/, const M2MServer & /*server_object*/){
        /* The registration is updated automatically and frequently by the 
        *  mbed client stack. This print statement is turned off because it 
        *  tends to happen alot.
        */
        //trace_printer("\r\nRegistration Updated\r\n");
    }

    // Callback from mbed client stack if any error is encountered
    // during any of the LWM2M operations. Error type is passed in
    // the callback.
    void error(M2MInterface::Error error){
        _error = true;
        switch(error){
            case M2MInterface::AlreadyExists:
                trace_printer("[ERROR:] M2MInterface::AlreadyExist");
                break;
            case M2MInterface::BootstrapFailed:
                trace_printer("[ERROR:] M2MInterface::BootstrapFailed");
                break;
            case M2MInterface::InvalidParameters:
                trace_printer("[ERROR:] M2MInterface::InvalidParameters");
                break;
            case M2MInterface::NotRegistered:
                trace_printer("[ERROR:] M2MInterface::NotRegistered");
                break;
            case M2MInterface::Timeout:
                trace_printer("[ERROR:] M2MInterface::Timeout");
                break;
            case M2MInterface::NetworkError:
                trace_printer("[ERROR:] M2MInterface::NetworkError");
                break;
            case M2MInterface::ResponseParseFailed:
                trace_printer("[ERROR:] M2MInterface::ResponseParseFailed");
                break;
            case M2MInterface::UnknownError:
                trace_printer("[ERROR:] M2MInterface::UnknownError");
                break;
            case M2MInterface::MemoryFail:
                trace_printer("[ERROR:] M2MInterface::MemoryFail");
                break;
            case M2MInterface::NotAllowed:
                trace_printer("[ERROR:] M2MInterface::NotAllowed");
                break;
            default:
                break;
        }
    }

    /* Callback from mbed client stack if any value has changed
    *  during PUT operation. Object and its type is passed in
    *  the callback.
    *  BaseType enum from m2mbase.h
    *       Object = 0x0, Resource = 0x1, ObjectInstance = 0x2, ResourceInstance = 0x3
    */
    void value_updated(M2MBase *base, M2MBase::BaseType type) {
        printf("\r\nPUT Request Received!");
        printf("\r\nName :'%s', \r\nType : '%d' (0 for Object, 1 for Resource), \r\nType : '%s'\r\n",
               base->name().c_str(), 
               type,
               base->resource_type().c_str()
               );
    }

    /*
    * update the registration period
    */
    void test_update_register() {
        if (_registered) {
            _interface->update_registration(_register_security, 3600);
        }
    }

    /*
    * manually configure the security object private variable
    */
   void set_register_object(M2MSecurity *register_object) {
        if (_register_security == NULL) {
            _register_security = register_object;
        }
    }

private:

    /*
    *  Private variables used in class
    */
    M2MInterface    	*_interface;
    M2MSecurity         *_register_security;
    M2MObject           *_object;
    M2MObject           *_led_object;
    volatile bool       _bootstrapped;
    volatile bool       _error;
    volatile bool       _registered;
    volatile bool       _unregistered;
    int                 _value;
    int                 _red;
    int                 _green;
    int                 _blue;
};

#endif // __SIMPLECLIENT_H__
