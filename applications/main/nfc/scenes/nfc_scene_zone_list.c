#include <stdio.h>
#include "string.h"
#include "../nfc_i.h"
#include "../zone_info.h"


enum SubmenuIndex {
    SubmenuIndexZone1,
    SubmenuIndexZone2,
    SubmenuIndexZone3,
    SubmenuIndexZone4,
    SubmenuIndexZone5,
    SubmenuIndexZone10,
};

void nfc_scene_zone_list_submenu_callback(void* context, uint32_t index) {
    Nfc* nfc = context;

    view_dispatcher_send_custom_event(nfc->view_dispatcher, index);
}

void nfc_scene_zone_list_on_enter(void* context) {
    Nfc* nfc = context;
    Submenu* submenu = nfc->submenu;

    submenu_add_item(submenu, "Zone 1", SubmenuIndexZone1, nfc_scene_zone_list_submenu_callback, nfc);
    submenu_add_item(submenu, "Zone 2", SubmenuIndexZone2, nfc_scene_zone_list_submenu_callback, nfc);
    submenu_add_item(submenu, "Zone 3", SubmenuIndexZone3, nfc_scene_zone_list_submenu_callback, nfc);
    submenu_add_item(submenu, "Zone 4", SubmenuIndexZone4, nfc_scene_zone_list_submenu_callback, nfc);
    submenu_add_item(submenu, "Zone 5", SubmenuIndexZone5, nfc_scene_zone_list_submenu_callback, nfc);
    submenu_add_item(submenu, "Zone 10", SubmenuIndexZone10, nfc_scene_zone_list_submenu_callback, nfc);


    submenu_set_selected_item(
            submenu, scene_manager_get_scene_state(nfc->scene_manager, NfcSceneZoneList));

    nfc_device_clear(nfc->dev);
    view_dispatcher_switch_to_view(nfc->view_dispatcher, NfcViewMenu);
}

bool nfc_scene_zone_list_on_event(void* context, SceneManagerEvent event) {
    Nfc* nfc = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == SubmenuIndexZone1) {
            //set_zone("Zone 1");
            consumed = true;
        } else if(event.event == SubmenuIndexZone2) {
            //set_zone("Zone 2");
            consumed = true;
        } else if(event.event == SubmenuIndexZone3) {
            //set_zone("Zone 3");
            consumed = true;
        } else if(event.event == SubmenuIndexZone4) {
            zone = 4;
            consumed = true;
        } else if(event.event == SubmenuIndexZone5) {
            //set_zone("Zone 5", 21);
            consumed = true;
        } else if(event.event == SubmenuIndexZone10){
            //set_zone("Zone 10", 30);
            consumed = true;
        }
        scene_manager_next_scene(nfc->scene_manager, NfcSceneZoneType);
        scene_manager_set_scene_state(nfc->scene_manager, NfcSceneZoneList, event.event);
    }
    return consumed;
}

void nfc_scene_zone_list_on_exit(void* context) {
    Nfc* nfc = context;

    submenu_reset(nfc->submenu);
}