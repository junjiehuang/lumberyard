#pragma once

/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#include <AzCore/RTTI/RTTI.h>

namespace AZ
{
    namespace SceneAPI
    {
        namespace DataTypes
        {
            class IManifestObject
            {
            public:
                AZ_RTTI(IManifestObject, "{3B839407-1884-4FF4-ABEA-CA9D347E83F7}");

                virtual ~IManifestObject() = 0;
            };

            inline IManifestObject::~IManifestObject()
            {
            }
        }  //namespace DataTypes
    }  //namespace SceneAPI
}  //namespace AZ
