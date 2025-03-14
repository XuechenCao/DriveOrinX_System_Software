////////////////////////////////////////////////////////////////////////////////
// This code contains NVIDIA Confidential Information and is disclosed
// under the Mutual Non-Disclosure Agreement.
//
// Notice
// ALL NVIDIA DESIGN SPECIFICATIONS AND CODE ("MATERIALS") ARE PROVIDED "AS IS"
// NVIDIA MAKES NO REPRESENTATIONS, WARRANTIES, EXPRESSED, IMPLIED, STATUTORY,
// OR OTHERWISE WITH RESPECT TO THE MATERIALS, AND EXPRESSLY DISCLAIMS ANY
// IMPLIED WARRANTIES OF NONINFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// NVIDIA Corporation assumes no responsibility for the consequences of use of
// such information or for any infringement of patents or other rights of third
// parties that may result from its use. No license is granted by implication or
// otherwise under any patent or patent rights of NVIDIA Corporation. No third
// party distribution is allowed unless expressly authorized by NVIDIA.  Details
// are subject to change without notice. This code supersedes and replaces all
// information previously supplied. NVIDIA Corporation products are not
// authorized for use as critical components in life support devices or systems
// without express written approval of NVIDIA Corporation.
//
// Copyright (c) 2022 NVIDIA Corporation. All rights reserved.
//
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and any
// modifications thereto. Any use, reproduction, disclosure or distribution of
// this software and related documentation without an express license agreement
// from NVIDIA Corporation is strictly prohibited.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef GEOPOINTS_H_
#define GEOPOINTS_H_
// Generated by dwProto from geo_points.proto DO NOT EDIT BY HAND!
// See //3rdparty/shared/dwproto/README.md for more information

#include "BasicTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Location point defined by WGS84 coordinates without elevation
typedef struct dwGeoPoint2dWGS84
{
    float64_t lon; //!< longitude
    float64_t lat; //!< latitude
} dwGeoPoint2dWGS84;

/// @brief Location point defined by WGS84 coordinates.
typedef struct dwGeoPointWGS84
{
    float64_t lon;    //!< longitude. Degree is the unit of measurement of longitude.
    float64_t lat;    //!< latitude. Degree is the unit of measurement of latitude.
    float64_t height; //!< height above WGS84 earth spheroid. Meter is the unit of measurement of height.
} dwGeoPointWGS84;

/// @brief Geographic coordinate bounds
typedef struct dwGeoBounds
{
    float64_t minLon; //!< minimum longitude, west - east [-180.0:180.0)
    float64_t minLat; //!< minimum latitude,  south - north [-90.0:90.0)
    float64_t maxLon; //!< maximum longitude, west - east [-180.0:180.0)
    float64_t maxLat; //!< maximum latitude,  south - north [-90.0:90.0)
} dwGeoBounds;

#ifdef __cplusplus
}
#endif

#endif // GEOPOINTS_H_
