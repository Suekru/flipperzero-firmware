#include <stdio.h>
#include "string.h"
#include "../nfc_i.h"
#include "../zone_info.h"
#include "../zone_utilities.h"


enum SubmenuIndex {
    SubmenuIndexButton,
};

void nfc_scene_zone_2_submenu_callback(void* context, uint32_t index) {
    Nfc* nfc = context;
    index = 0;
    view_dispatcher_send_custom_event(nfc->view_dispatcher, index);
}

void nfc_scene_zone_2_on_enter(void* context) {
    Nfc* nfc = context;
    Submenu* submenu = nfc->submenu;

    for(int i = 0; i < zoneLengths[2]; i++)
        submenu_add_item(submenu, chipNames[2][i], SubmenuIndexButton, nfc_scene_zone_2_submenu_callback, nfc);


    submenu_set_selected_item(
            submenu, scene_manager_get_scene_state(nfc->scene_manager, NfcSceneZoneList));

    nfc_device_clear(nfc->dev);
    view_dispatcher_switch_to_view(nfc->view_dispatcher, NfcViewMenu);
}

bool nfc_scene_zone_2_on_event(void* context, SceneManagerEvent event) {
    Nfc* nfc = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        consumed = true;
        FuriString* path = furi_string_alloc_set("/any/nfc/Zones/Zone 2/");
        furi_string_cat_str(path, chipNames[2][submenuIndex]);
        furi_string_cat_str(path, ".nfc");
        play_zone_chip(furi_string_get_cstr(path), submenuIndex+1);

        scene_manager_set_scene_state(nfc->scene_manager, NfcSceneZone4, event.event);
    }
    return consumed;
}

void nfc_scene_zone_2_on_exit(void* context) {
    Nfc* nfc = context;
    submenu_reset(nfc->submenu);
}