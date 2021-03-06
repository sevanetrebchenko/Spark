
#ifndef SPARK_ENTITY_MANAGER_H
#define SPARK_ENTITY_MANAGER_H

#include <spark/core/core.h>
#include <spark/ecs/entities/entity_callback_type.h>            // CallbackType
#include <spark/ecs/ecs_typedefs.h>                             // EntityID
#include <spark/ecs/components/types/base_component.h>          // BaseComponent
#include <spark/ecs/entities/entity_manager_interface.h>        // IEntityManager
#include <spark/events/event_interactable_interface.h>          // IEventReceivable
#include <spark/ecs/components/all_components.h>                // ALL_COMPONENTS
#include <spark/events/generators/add_component_generator.h>    // GenerateAddComponentsForTypes
#include <spark/events/generators/remove_component_generator.h> // GenerateRemoveComponentsForTypes

namespace Spark {
    namespace ECS {
        namespace Entities {

            class EntityManager : public IEntityManager, public Events::IEventReceivable<EntityManager, Events::GenerateAddComponentsForTypes<ALL_COMPONENTS>::Type, Events::GenerateRemoveComponentsForTypes<ALL_COMPONENTS>::Type> {
                public:
                    static EntityManager* GetInstance();

                    /**
                     * Register a callback function of a given type with the entity manager.
                     * @param callbackType     - Callback function type.
                     * @param callbackFunction - Callback function.
                     */
                    void RegisterCallback(CallbackType callbackType, const std::function<void(EntityID)>& callbackFunction) override;

                    /**
                    * Create an entity. Throws error if the provided entity name matches any of the the bin-in component type
                    * names or any pre-existing entity names. Automatically notifies all fully registered component systems that
                    * a new entity has been created.
                    * @param name - Unique name for the entity to have.
                    */
                    void CreateEntity(std::string name) override;

                    /**
                    * Destroy an entity from the Entity Manager with the provided entity ID, given that it exists. Automatically
                    * notifies all fully registered component systems that an entity has been deleted.
                    * @param ID - ID of the entity to delete.
                    */
                    void DestroyEntity(EntityID ID) override;

                    /**
                    * Destroy an entity from the Entity Manager with the provided entity name, given that it exists. Automatically
                    * notifies all fully registered component systems that an entity has been deleted.
                    * @param name - Name of the entity to delete.
                    */
                    void DestroyEntity(std::string name) override;

                    /**
                     * Convert a given entity name to the relative entity ID.
                     * @param entityName - Name of the entity to get the ID of.
                     * @return ID of the entity with the given name.
                     */
                    _NODISCARD_ EntityID GetEntityIDFromName(const std::string& entityName) const override;

                    /**
                     * Retrieve a map of all entities and their attached components.
                     * @return A map of all entities and their attached components.
                     */
                    _NODISCARD_ const std::unordered_map<EntityID, std::unordered_map<ComponentTypeID, Components::BaseComponent*>>& GetComponentMap() const override;

                    /**
                    * Retrieve the list of components that are attached to an entity with the provided ID, given that such an
                    * entity exists in the Entity Manager.
                    * @param ID - ID of the entity to get the components of.
                    * @return List of attached components to the entity at the provided ID.
                    */
                    _NODISCARD_ const std::unordered_map<ComponentTypeID, Components::BaseComponent*>& GetComponents(EntityID ID) const override;

                    /**
                    * Retrieve the list of components that are attached to an entity with the provided name, given that such an
                    * entity exists in the Entity Manager.
                    * @param name - Name of the entity to get the components of.
                    * @return List of attached components to the entity at the provided name.
                    */
                    _NODISCARD_ const std::unordered_map<ComponentTypeID, Components::BaseComponent*>& GetComponents(std::string name) const override;

                    // Entity manager should not be copied/duplicated.
                    EntityManager(EntityManager const &other) = delete;
                    EntityManager(EntityManager &&other) = delete;
                    void operator=(EntityManager const &other) = delete;

                private:
                    EntityManager();
                    ~EntityManager();
                    static EntityManager* _instance;

                    friend Events::IEventReceivable<EntityManager, Events::GenerateAddComponentsForTypes<ALL_COMPONENTS>::Type, Events::GenerateRemoveComponentsForTypes<ALL_COMPONENTS>::Type>;
                    void OnEvent(Events::AddComponentEvent<Components::TestComponent>* event) override;
                    void OnEvent(Events::RemoveComponentEvent<Components::TestComponent>* event) override;

                    // Storage for EntityManager data, back-end functionality, and helper functions.
                    class EntityManagerData;
                    EntityManagerData* _data;
            };

        }
    }
}

#endif // SPARK_ENTITY_MANAGER_H


