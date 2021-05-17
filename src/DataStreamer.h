/* This source file is part of the ATMEL QTouch Library 5.0.1 */
/* Software provided by Microchip under the license agreement 
   “Microchip Touch Library License Agreement - Arduino 082420 
   (part of this downloaded package) */

/**
 *
 * \file
 *
 * \brief  This file contains the SAMD QTouch library initialization,
 * sensor configuration and measurement routines.
 *
 * - Userguide:          QTouch Library Peripheral Touch Controller User Guide.
 * - Support: https://www.microchip.com/support/
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#ifndef __DATASTREAMER_H_
#define __DATASTREAMER_H_

/*----------------------------------------------------------------------------
 *     include files
 *----------------------------------------------------------------------------*/
#include "Arduino.h"
#include "touch_config_samd.h"



//#if (DEF_TOUCH_DATA_STREAMER_ENABLE == 1u)

/*----------------------------------------------------------------------------
 *     defines
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *   prototypes
 *----------------------------------------------------------------------------*/

class DataStreamer {
  public:
    void datastreamerOutput(void);
};
//extern
//#endif

#endif
