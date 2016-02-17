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
#ifndef __SECURITY_H__
#define __SECURITY_H__
 
#include <inttypes.h>
 
#define MBED_DOMAIN "546a9140-9fa3-4113-b56a-883da2941d91"
#define MBED_ENDPOINT_NAME "145da9b5-a76a-486f-b25a-3a190effb596"
 
const uint8_t SERVER_CERT[] = "-----BEGIN CERTIFICATE-----\r\n"
"MIIBmDCCAT6gAwIBAgIEVUCA0jAKBggqhkjOPQQDAjBLMQswCQYDVQQGEwJGSTEN\r\n"
"MAsGA1UEBwwET3VsdTEMMAoGA1UECgwDQVJNMQwwCgYDVQQLDANJb1QxETAPBgNV\r\n"
"BAMMCEFSTSBtYmVkMB4XDTE1MDQyOTA2NTc0OFoXDTE4MDQyOTA2NTc0OFowSzEL\r\n"
"MAkGA1UEBhMCRkkxDTALBgNVBAcMBE91bHUxDDAKBgNVBAoMA0FSTTEMMAoGA1UE\r\n"
"CwwDSW9UMREwDwYDVQQDDAhBUk0gbWJlZDBZMBMGByqGSM49AgEGCCqGSM49AwEH\r\n"
"A0IABLuAyLSk0mA3awgFR5mw2RHth47tRUO44q/RdzFZnLsAsd18Esxd5LCpcT9w\r\n"
"0tvNfBv4xJxGw0wcYrPDDb8/rjujEDAOMAwGA1UdEwQFMAMBAf8wCgYIKoZIzj0E\r\n"
"AwIDSAAwRQIhAPAonEAkwixlJiyYRQQWpXtkMZax+VlEiS201BG0PpAzAiBh2RsD\r\n"
"NxLKWwf4O7D6JasGBYf9+ZLwl0iaRjTjytO+Kw==\r\n"
"-----END CERTIFICATE-----\r\n";
 
const uint8_t CERT[] = "-----BEGIN CERTIFICATE-----\r\n"
"MIIB0DCCAXOgAwIBAgIEVBzHoDAMBggqhkjOPQQDAgUAMDkxCzAJBgNVBAYTAkZ\r\n"
"JMQwwCgYDVQQKDANBUk0xHDAaBgNVBAMME21iZWQtY29ubmVjdG9yLTIwMTYwHh\r\n"
"cNMTYwMjE3MjIwODA2WhcNMTYxMjMxMDYwMDAwWjCBoTFSMFAGA1UEAxNJNTQ2Y\r\n"
"TkxNDAtOWZhMy00MTEzLWI1NmEtODgzZGEyOTQxZDkxLzE0NWRhOWI1LWE3NmEt\r\n"
"NDg2Zi1iMjVhLTNhMTkwZWZmYjU5NjEMMAoGA1UECxMDQVJNMRIwEAYDVQQKEwl\r\n"
"tYmVkIHVzZXIxDTALBgNVBAcTBE91bHUxDTALBgNVBAgTBE91bHUxCzAJBgNVBA\r\n"
"YTAkZJMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAE6zwt/vqWYF4yAwewmcQqj\r\n"
"qQg6ct/gG1uyY8OWcLFYyH/LYV6+zyuj+JVaUpgi8rNfqIu9eUIIec45WrDz7F7\r\n"
"PjAMBggqhkjOPQQDAgUAA0kAMEYCIQCYtEfho33nR0JE8MbY5LBAMp4RFjkk73D\r\n"
"mWNDy41ZmBwIhAPg6wWba5Lr736BWdPgoWRY7gY69wu1ydzPKkNBcystM\r\n"
"-----END CERTIFICATE-----\r\n";
 
const uint8_t KEY[] = "-----BEGIN PRIVATE KEY-----\r\n"
"MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgMm9LkKv2i5c8tvpf\r\n"
"e0ovSf2rRDAhoLHCtn6P9yM0q1ihRANCAATrPC3++pZgXjIDB7CZxCqOpCDpy3+A\r\n"
"bW7Jjw5ZwsVjIf8thXr7PK6P4lVpSmCLys1+oi715Qgh5zjlasPPsXs+\r\n"
"-----END PRIVATE KEY-----\r\n";
 
#endif //__SECURITY_H__