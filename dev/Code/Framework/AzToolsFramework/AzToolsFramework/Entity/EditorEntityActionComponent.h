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
#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/Entity.h>
#include <AzToolsFramework/API/EntityCompositionRequestBus.h>
#include <AzToolsFramework/Entity/EditorEntityContextBus.h>

namespace AzToolsFramework
{
    namespace Components
    {
        /**
        * A system component for handling component-related actions on entities
        *
        * Used to perform things such as add/remove components, cut/copy/paste, etc.
        */
        class EditorEntityActionComponent
            : public AZ::Component
            , public EntityCompositionRequestBus::Handler
            , public EditorEntityContextNotificationBus::Handler
        {
        public:
            AZ_COMPONENT(EditorEntityActionComponent, "{2E26C7DF-544E-4A2A-8D0D-D7A6595C8BBD}");

            EditorEntityActionComponent() = default;
            virtual ~EditorEntityActionComponent() = default;

            //////////////////////////////////////////////////////////////////////////
            // AZ::Component overrides
            void Init() override;
            void Activate() override;
            void Deactivate() override;
            //////////////////////////////////////////////////////////////////////////

            //////////////////////////////////////////////////////////////////////////
            // EntityCompositionRequestBus::Handler
            AddComponentsOutcome AddComponentsToEntities(const EntityIdList& entityIds, const AZ::ComponentTypeList& componentsToAdd) override;
            AddExistingComponentsOutcome AddExistingComponentsToEntity(AZ::Entity* entity, const AZStd::vector<AZ::Component*>& componentsToAdd) override;
            RemoveComponentsOutcome RemoveComponents(const AZStd::vector<AZ::Component*>& componentsToRemove) override;

            void CutComponents(const AZStd::vector<AZ::Component*>& components) override;
            void CopyComponents(const AZStd::vector<AZ::Component*>& components) override;
            void PasteComponentsToEntity(AZ::EntityId entityId) override;
            bool HasComponentsToPaste() override;

            void EnableComponents(const AZStd::vector<AZ::Component*>& components) override;
            void DisableComponents(const AZStd::vector<AZ::Component*>& components) override;

            PendingComponentInfo GetPendingComponentInfo(const AZ::Component* component) override;

            AZStd::string GetComponentName(const AZ::Component* component) override;

        private:

            bool RemoveComponentFromEntityAndContainers(AZ::Entity* entity, AZ::Component* componentToRemove);

            //////////////////////////////////////////////////////////////////////////
            // EditorEntityContextNotificationBus::Handler
            void OnEntityStreamLoadSuccess() override;
            //////////////////////////////////////////////////////////////////////////

            using ScrubEntityResult = RemoveComponentsResults;
            ScrubEntityResult ScrubEntity(AZ::Entity* entity);

            /*!
            * Result of add component operations
            * Can either succeed and return a vector of the new components added
            * or fail with a string containing the reason for failure
            */
            using AddPendingComponentsOutcome = AZ::Outcome<AZ::Entity::ComponentArrayType, AZStd::string>;
            AddPendingComponentsOutcome AddPendingComponentsToEntity(AZ::Entity* entity);

            static void Reflect(AZ::ReflectContext* context);
            static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
            static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
            static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        };

    } // namespace Components
} // namespace AzToolsFramework
