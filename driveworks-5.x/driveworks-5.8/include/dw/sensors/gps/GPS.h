/////////////////////////////////////////////////////////////////////////////////////////
//
// Notice
// ALL NVIDIA DESIGN SPECIFICATIONS AND CODE ("MATERIALS") ARE PROVIDED "AS IS" NVIDIA MAKES
// NO REPRESENTATIONS, WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ANY IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
//
// NVIDIA CORPORATION & AFFILIATES assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA CORPORATION & AFFILIATES. No third party distribution is allowed unless
// expressly authorized by NVIDIA. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA CORPORATION & AFFILIATES products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA CORPORATION & AFFILIATES.
//
// SPDX-FileCopyrightText: Copyright (c) 2016-2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: LicenseRef-NvidiaProprietary
//
// NVIDIA CORPORATION, its affiliates and licensors retain all intellectual
// property and proprietary rights in and to this material, related
// documentation and any modifications thereto. Any use, reproduction,
// disclosure or distribution of this material and related documentation
// without an express license agreement from NVIDIA CORPORATION or
// its affiliates is strictly prohibited.
//
/////////////////////////////////////////////////////////////////////////////////////////

/**
 * @file
 * <b>NVIDIA DriveWorks API: GPS</b>
 *
 * @b Description: This file defines methods to access GPS sensor.
 */

/**
 * @defgroup gps_group GPS Sensor
 * @ingroup sensors_group
 *
 * @brief Defines the GPS sensor.
 *
 * @{
 */

#ifndef DW_SENSORS_GPS_GPS_H_
#define DW_SENSORS_GPS_GPS_H_

#include <dw/core/base/Config.h>
#include <dw/core/base/Exports.h>
#include <dw/core/base/Types.h>

#include <dw/sensors/Sensors.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Each flag shows if that value is valid in this GPS frame. **/
typedef enum dwGPSFlags {
    DW_GPS_LAT    = 1 << 0,  //!< Value of dwGPSFrame.latitude is valid.
    DW_GPS_LON    = 1 << 1,  //!< Value of dwGPSFrame.longitude is valid.
    DW_GPS_ALT    = 1 << 2,  //!< Value of dwGPSFrame.altitude is valid.
    DW_GPS_COURSE = 1 << 3,  //!< Value of dwGPSFrame.course is valid.
    DW_GPS_SPEED  = 1 << 4,  //!< Value of dwGPSFrame.speed is valid.
    DW_GPS_CLIMB  = 1 << 5,  //!< Value of dwGPSFrame.climb is valid.
    DW_GPS_HDOP   = 1 << 6,  //!< Value of dwGPSFrame.hdop is valid.
    DW_GPS_VDOP   = 1 << 7,  //!< Value of dwGPSFrame.vdop is valid.
    DW_GPS_HACC   = 1 << 8,  //!< Value of dwGPSFrame.hacc is valid.
    DW_GPS_VACC   = 1 << 9,  //!< Value of dwGPSFrame.vacc is valid.
    DW_GPS_MODE   = 1 << 10, //!< Value of dwGPSFrame.gpsMode is valid.
} dwGPSFlags;

/**
* The GPS mode gives the status of the GNSS data. Note that modes 1-7 are
* increasing in accuracy. Modes 8 and 9 are not quite as good as 6 and 7, respectively.
*/
typedef enum dwGPSMode {
    /// GPS mode unknown. The device cannot or has not reported the mode.
    DW_GPS_MODE_UNKNOWN = 0,
    /// GPS mode invalid. This GPS data cannot be used.
    DW_GPS_MODE_INVALID_GPS = 1,
    /// GPS mode dead reckoning. Device relying on IMU alone for updates.
    DW_GPS_MODE_DEAD_RECKONING = 2,
    /// GPS mode stand alone. No RTK or PPP correction.
    DW_GPS_MODE_STAND_ALONE = 3,
    /// GPS mode precise point. No RTK or PPP correction.
    DW_GPS_MODE_PRECISE_POINT = 4,
    /// GPS mode code differential. No RTK or PPP correction.
    DW_GPS_MODE_CODE_DIFFERENTIAL = 5,
    /// GPS mode RTK float
    DW_GPS_MODE_RTK_FLOAT = 6,
    /// GPS mode RTK fixed. This is the highest accuracy mode.
    DW_GPS_MODE_RTK_FIXED = 7,
    /// GPS mode PPP converging. Using PPP, but solution has not finished converging, so the data is not yet as accurate as it can be.
    DW_GPS_MODE_PPP_CONVERGING = 8,
    /// GPS mode PPP converged. Most accurate mode for using PPP.
    DW_GPS_MODE_PPP_CONVERGED = 9,
    DW_GPS_MODE_FORCE32       = 0x7FFFFFFF
} dwGPSMode;

/**
 * A GPS packet containing localization information.
 * Flags are used to define information available in this frame.
 */
typedef struct dwGPSFrame
{
    /// Timestamp of the message when first received [usec].
    dwTime_t timestamp_us;

    /// Latitude [degree].
    float64_t latitude;

    /// Longitude [degree].
    float64_t longitude;

    /// Altitude over WGS84 ellipsoid [m].
    float64_t altitude;

    /// Course relative to true north [degree].
    float64_t course;

    /// Horizontal speed [m/s].
    float64_t speed;

    /// Vertical speed [m/s].
    float64_t climb;

    /// UTC time as provided in the GPS package [hhmmss.sss] (null terminated).
    char utcTime[16];

    /// UTC date as provided in the GPS package [ddmmyy] (null terminated).
    char utcDate[16];

    /// Horizontal dilution of precision (HDOP).
    float64_t hdop;

    /// Vertical dilution of precision (VDOP).
    float64_t vdop;

    /// Horizontal accuracy [m].
    float64_t hacc;

    /// Vertical accuracy [m].
    float64_t vacc;

    /// The flags to show which values are valid in this GPS frame.
    uint32_t flags;

    /// GPS mode
    dwGPSMode gpsMode;
} dwGPSFrame;

/** GPS satellite fix status. **/
typedef enum dwGPSFixStatus {
    /// No fix
    DW_GPS_FIX_STATUS_NO_FIX = 0,
    /// 2D fix
    DW_GPS_FIX_STATUS_2D_FIX = 1,
    /// 3D fix
    DW_GPS_FIX_STATUS_3D_FIX  = 2,
    DW_GPS_FIX_STATUS_FORCE32 = 0x7FFFFFFF
} dwGPSFixStatus;

typedef enum dwGPSTimestampQuality {
    /// Not Initialized. still initializing
    DW_GPS_TIMESTAMP_QUALITY_NOT_INIT = 0,
    /// Normal Operation. Functional and Electrical Checks Passed
    DW_GPS_TIMESTAMP_QUALITY_OK = 1,
    /// Synchronization lost.
    DW_GPS_TIMESTAMP_QUALITY_SYNC_LOST = 2,
    DW_GPS_TIMESTAMP_QUALITY_FORCE32   = 0x7FFFFFFF
} dwGPSTimestampQuality;

/**
* This structure contains one frame of data from an GPS/GNSS sensor.
*/
typedef struct dwGPSFrameNew
{
    struct
    {
        dwSignalValidity timestamp_us;
        dwSignalValidity latitude;
        dwSignalValidity longitude;
        dwSignalValidity altitude;
        dwSignalValidity course;
        dwSignalValidity speed;
        dwSignalValidity climb;
        dwSignalValidity hdop;
        dwSignalValidity vdop;
        dwSignalValidity pdop;
        dwSignalValidity hacc;
        dwSignalValidity vacc;
        dwSignalValidity utcTime;
        dwSignalValidity satelliteCount;
        dwSignalValidity fixStatus;
        dwSignalValidity timestampQuality;
        dwSignalValidity gpsMode;
        dwSignalValidity reserved[63];
    } validityInfo;

    /// @note ID VS-91010
    /// @note description Timestamp of the message when first received.
    /// @note min nan    max nan
    /// @note freq 4    unit us
    dwTime_t timestamp_us;

    /// @note ID VS-91020
    /// @note description Latitude in WGS-84.
    /// @note min nan    max nan
    /// @note freq 4    unit deg
    float64_t latitude;

    /// @note ID VS-91030
    /// @note description Longitude in WGS-84.
    /// @note min nan    max nan
    /// @note freq 4    unit deg
    float64_t longitude;

    /// @note ID VS-91040
    /// @note description Altitude over WGS-84 ellipsoid.
    /// @note min nan    max nan
    /// @note freq 4    unit m
    float64_t altitude;

    /// @note ID VS-91050
    /// @note description Course relative to true north.
    /// @note min nan    max nan
    /// @note freq 4    unit deg
    float64_t course;

    /// @note ID VS-91060
    /// @note description Horizontal speed.
    /// @note min nan    max nan
    /// @note freq 4    unit m/s
    float64_t speed;

    /// @note ID VS-91070
    /// @note description Vertical speed.
    /// @note min nan    max nan
    /// @note freq 4    unit m/s
    float64_t climb;

    /// @note ID VS-91080
    /// @note description Horizontal Dilution of Precision.
    /// @note min nan    max nan
    /// @note freq 4    unit unitless
    float64_t hdop;

    /// @note ID VS-91090
    /// @note description Vertical Dilution of Precision.
    /// @note min nan    max nan
    /// @note freq 4    unit unitless
    float64_t vdop;

    /// @note ID VS-91100
    /// @note description Position Dilution of Precision.
    /// @note min nan    max nan
    /// @note freq 4    unit unitless
    float64_t pdop;

    /// @note ID VS-91110
    /// @note description Horizontal Accuracy of Solution.
    /// @note min nan    max nan
    /// @note freq 4    unit m
    float64_t hacc;

    /// @note ID VS-91120
    /// @note description Vertical Accuracy of Solution.
    /// @note min nan    max nan
    /// @note freq 4    unit m
    float64_t vacc;

    /// @note ID VS-91130
    /// @note description UTC time.
    /// @note min nan    max nan
    /// @note freq 4    unit us
    dwTime_t utcTime;

    /// @note ID VS-91140
    /// @note description Number of satellites in view.
    /// @note TODO: Backend not yet implemented
    /// @note min nan    max nan
    /// @note freq 4    unit unitless
    uint8_t satelliteCount;

    /// @note ID VS-91150
    /// @note description 2D or 3D fix.
    /// @note TODO: Backend not yet implemented
    /// @note min nan    max nan
    /// @note freq 4    unit  -
    /// @note *** valid values**: {
    ///                DW_GPS_FIX_STATUS_NO_FIX,
    ///                DW_GPS_FIX_STATUS_2D_FIX,
    ///                DW_GPS_FIX_STATUS_3D_FIX
    ///        }
    dwGPSFixStatus fixStatus;

    /// @note ID VS-91170
    /// @note description GNSS Timestamp Quality.
    /// @note TODO: Backend not yet implemented
    /// @note min nan    max nan
    /// @note freq 4    unit  -
    /// @note *** valid values**: {
    ///                DW_GPS_TIMESTAMP_QUALITY_NOT_INIT,
    ///                DW_GPS_TIMESTAMP_QUALITY_OK,
    ///                DW_GPS_TIMESTAMP_QUALITY_SYNC_LOST,
    ///        }
    dwGPSTimestampQuality timestampQuality;

    /// GPS mode
    dwGPSMode gpsMode;

    uint8_t reserved[508];
} dwGPSFrameNew;

/**
 * Reads the next GPS packet with a given timeout. The method blocks until
 * either a new valid frame is received from the sensor or the given timeout exceeds.
 *
 * @param[out] frame A pointer to a GPS frame structure to be filled with new localization data.
 * @param[in] timeoutUs Specifies the timeout in us to wait for a new message. Special values: DW_TIMEOUT_INFINITE - to wait infinitly.  Zero - means polling of internal queue.
 * @param[in] sensor Specifies the sensor handle of the GPS sensor previously created with 'dwSAL_createSensor()'.
 *
 * @return DW_INVALID_HANDLE - if given sensor handle is invalid. <br>
 *         DW_INVALID_ARGUMENTS - if given arguments are invalid. <br>
 *         DW_TIME_OUT - if operation has timeout. <br>
 *         DW_NOT_AVAILABLE    - if sensor has not been started or data is not available in polling mode. <br>
 *         DW_END_OF_STREAM    - if end of stream reached (virtual sensor only). <br>
 *         DW_SAL_SENSOR_ERROR - if there was an i/o or bus error. <br>
 *         DW_SUCCESS
 *
 */
DW_API_PUBLIC
dwStatus dwSensorGPS_readFrame(dwGPSFrame* const frame, dwTime_t const timeoutUs, dwSensorHandle_t const sensor);

/**
* Decodes RAW data previously read. Any processed messages can be picked up using
* the dwSensorGPS_popMessage() method. This happens on the CPU thread where the function is called,
* incurring on additional load on that thread.
*
* @param[in] data Undecoded gps data.
* @param[in] size Size in bytes of the raw data.
* @param[in] sensor Sensor handle of the sensor previously created with 'dwSAL_createSensor()'.
*
* @return DW_INVALID_HANDLE - if given sensor handle is invalid, <br>
*         DW_INVALID_ARGUMENTS - if given arguments are invalid, <br>
*         DW_NOT_READY - if more data needs to be passed in (loop while it returns 'DW_NOT_READY'). <br>
*         DW_SUCCESS
**/
DW_API_PUBLIC
dwStatus dwSensorGPS_processRawData(uint8_t const* const data, size_t const size, dwSensorHandle_t const sensor);

/**
* Returns any GPS frame previously processed through RAW data stream.
* This happens on the CPU thread where the function is called, incurring an additional load on that thread.
*
* @param[out] frame Pointer to an GPS frame structure to be filled with new data.
* @param[in] sensor Sensor handle of the sensor previously created with 'dwSAL_createSensor()'.
*
* @return DW_INVALID_HANDLE - if given sensor handle is invalid. <br>
*         DW_INVALID_ARGUMENTS - if given arguments are invalid. <br>
*         DW_NOT_AVAILABLE - if no more data is available <br>
*         DW_SUCCESS
**/
DW_API_PUBLIC
dwStatus dwSensorGPS_popFrame(dwGPSFrame* const frame, dwSensorHandle_t const sensor);

/**
 * Reads the next GPS packet with a given timeout. The method blocks until
 * either a new valid frame is received from the sensor or the given timeout exceeds.
 *
 * @param[out] frame A pointer to a GPS frame New structure to be filled with new localization data.
 * @param[in] timeoutUs Specifies the timeout in us to wait for a new message. Special values: DW_TIMEOUT_INFINITE - to wait infinitly.  Zero - means polling of internal queue.
 * @param[in] sensor Specifies the sensor handle of the GPS sensor previously created with 'dwSAL_createSensor()'.
 *
 * @return DW_INVALID_HANDLE - if given sensor handle is invalid. <br>
 *         DW_INVALID_ARGUMENTS - if given arguments are invalid. <br>
 *         DW_TIME_OUT - if operation has timeout. <br>
 *         DW_NOT_AVAILABLE    - if sensor has not been started or data is not available in polling mode. <br>
 *         DW_END_OF_STREAM    - if end of stream reached (virtual sensor only). <br>
 *         DW_SAL_SENSOR_ERROR - if there was an i/o or bus error. <br>
 *         DW_SUCCESS
 *
 */
DW_API_PUBLIC
dwStatus dwSensorGPS_readFrameNew(dwGPSFrameNew* const frame, dwTime_t const timeoutUs, dwSensorHandle_t const sensor);

/**
* Decodes RAW data previously read. Any processed messages can be picked up using
* the dwSensorGPS_popMessageNew() method. This happens on the CPU thread where the function is called,
* incurring on additional load on that thread.
*
* @param[in] data Undecoded gps data.
* @param[in] size Size in bytes of the raw data.
* @param[in] sensor Sensor handle of the sensor previously created with 'dwSAL_createSensor()'.
*
* @return DW_INVALID_HANDLE - if given sensor handle is invalid, <br>
*         DW_INVALID_ARGUMENTS - if given arguments are invalid, <br>
*         DW_NOT_READY - if more data needs to be passed in (loop while it returns 'DW_NOT_READY'). <br>
*         DW_SUCCESS
**/
DW_API_PUBLIC
dwStatus dwSensorGPS_processRawDataNew(uint8_t const* const data, size_t const size, dwSensorHandle_t const sensor);

/**
* Returns any GPS frame New previously processed through RAW data stream.
* This happens on the CPU thread where the function is called, incurring an additional load on that thread.
*
* @param[out] frame Pointer to an GPS frame New structure to be filled with new data.
* @param[in] sensor Sensor handle of the sensor previously created with 'dwSAL_createSensor()'.
*
* @return DW_INVALID_HANDLE - if given sensor handle is invalid. <br>
*         DW_INVALID_ARGUMENTS - if given arguments are invalid. <br>
*         DW_NOT_AVAILABLE - if no more data is available <br>
*         DW_SUCCESS
**/
DW_API_PUBLIC
dwStatus dwSensorGPS_popFrameNew(dwGPSFrameNew* const frame, dwSensorHandle_t const sensor);

#ifdef __cplusplus
}
#endif
/** @} */
#endif // DW_SENSORS_GPS_GPS_H_
