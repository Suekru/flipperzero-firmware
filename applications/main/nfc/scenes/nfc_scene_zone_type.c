#include <stdio.h>
#include "string.h"
#include "../zone_info.h"
#include "../nfc_i.h"
#include "../zone_utilities.h"


enum SubmenuIndex {
    SubmenuIndexAutomatic,
    SubmenuIndexManual,
};

void nfc_scene_zone_type_submenu_callback(void* context, uint32_t index) {
    Nfc* nfc = context;
    automaticZoneCancelled = 0;
    view_dispatcher_send_custom_event(nfc->view_dispatcher, index);
}




void play_zone(){
    const char* file_extension = ".nfc";
    FuriString* path = furi_string_alloc_set("/any/nfc/Zones/");
    furi_string_cat_str(path, zoneName);
    furi_string_cat_str(path, "/");
    FuriString* chip = furi_string_alloc();

    for(int i = 0; i < zoneLengths[zone]; i++){
        if(automaticZoneCancelled) break;
        furi_string_set_str(chip, chipNames[zone][i]);
        furi_string_cat_str(chip, file_extension);

        furi_string_cat(path, chip);

        play_zone_chip(furi_string_get_cstr(path), i+1);
        furi_string_trim(path, furi_string_get_cstr(chip));
    }
    furi_string_free(path);
    furi_string_free(chip);
}

void nfc_scene_zone_type_on_enter(void* context) {
    Nfc* nfc = context;
    Submenu* submenu = nfc->submenu;

    submenu_add_item(submenu, "Automatic", SubmenuIndexAutomatic, nfc_scene_zone_type_submenu_callback, nfc);
    submenu_add_item(submenu, "Manual", SubmenuIndexManual, nfc_scene_zone_type_submenu_callback, nfc);

    submenu_set_selected_item(
            submenu, scene_manager_get_scene_state(nfc->scene_manager, NfcSceneZoneType));

    nfc_device_clear(nfc->dev);
    view_dispatcher_switch_to_view(nfc->view_dispatcher, NfcViewMenu);
}

bool nfc_scene_zone_type_on_event(void* context, SceneManagerEvent event) {
    Nfc* nfc = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == SubmenuIndexAutomatic){
            isAutomatic = 1;
            play_zone();
        }
        else if(event.event == SubmenuIndexManual){
            isAutomatic = 0;
            scene_manager_next_scene(nfc->scene_manager, NfcSceneZoneChipMenu);
            /*if(zone == 2)
                scene_manager_next_scene(nfc->scene_manager, );
            else if(zone == 4)
                scene_manager_next_scene(nfc->scene_manager, NfcSceneZone4);*/
        }
        consumed = true;
        scene_manager_set_scene_state(nfc->scene_manager, NfcSceneZoneType, event.event);
    }
    return consumed;
}

void nfc_scene_zone_type_on_exit(void* context) {
    Nfc* nfc = context;
    submenu_reset(nfc->submenu);
}