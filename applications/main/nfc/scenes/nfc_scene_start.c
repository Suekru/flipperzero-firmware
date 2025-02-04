#include "../nfc_i.h"
#include "nfc_worker_i.h"
#include "../zone_info.h"
#include "../zone_utilities.h"
#include <dolphin/dolphin.h>

enum SubmenuIndex {
    SubmenuIndexRead,
    SubmenuIndexDetectReader,
    SubmenuIndexSaved,
    SubmenuIndexExtraAction,
    SubmenuIndexAddManually,
    SubmenuIndexDebug,
    SubmenuIndexZoneEmulator
};

void nfc_scene_start_submenu_callback(void* context, uint32_t index) {
    Nfc* nfc = context;
    zoneName = "Zone 0";
    zone = 0;
    isAutomatic = 0;
    view_dispatcher_send_custom_event(nfc->view_dispatcher, index);
}

void nfc_scene_start_on_enter(void* context) {
    Nfc* nfc = context;
    Submenu* submenu = nfc->submenu;

    submenu_add_item(submenu, "Read", SubmenuIndexRead, nfc_scene_start_submenu_callback, nfc);
    submenu_add_item(
        submenu, "Detect Reader", SubmenuIndexDetectReader, nfc_scene_start_submenu_callback, nfc);
    submenu_add_item(submenu, "Saved", SubmenuIndexSaved, nfc_scene_start_submenu_callback, nfc);
    submenu_add_item(submenu, "Zone Emulator", SubmenuIndexZoneEmulator, nfc_scene_start_submenu_callback, nfc);
    submenu_add_item(
        submenu, "Extra Actions", SubmenuIndexExtraAction, nfc_scene_start_submenu_callback, nfc);
    submenu_add_item(
        submenu, "Add Manually", SubmenuIndexAddManually, nfc_scene_start_submenu_callback, nfc);

    if(furi_hal_rtc_is_flag_set(FuriHalRtcFlagDebug)) {
        submenu_add_item(
            submenu, "Debug", SubmenuIndexDebug, nfc_scene_start_submenu_callback, nfc);
    }

    submenu_set_selected_item(
        submenu, scene_manager_get_scene_state(nfc->scene_manager, NfcSceneStart));

    nfc_device_clear(nfc->dev);
    view_dispatcher_switch_to_view(nfc->view_dispatcher, NfcViewMenu);
}

bool nfc_scene_start_on_event(void* context, SceneManagerEvent event) {
    Nfc* nfc = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == SubmenuIndexRead) {
            nfc->dev->dev_data.read_mode = NfcReadModeAuto;
            scene_manager_next_scene(nfc->scene_manager, NfcSceneRead);
            DOLPHIN_DEED(DolphinDeedNfcRead);
            consumed = true;
        } else if(event.event == SubmenuIndexDetectReader) {
            bool sd_exist = storage_sd_status(nfc->dev->storage) == FSE_OK;
            if(sd_exist) {
                nfc_device_data_clear(&nfc->dev->dev_data);
                scene_manager_next_scene(nfc->scene_manager, NfcSceneDetectReader);
                DOLPHIN_DEED(DolphinDeedNfcDetectReader);
            } else {
                scene_manager_next_scene(nfc->scene_manager, NfcSceneDictNotFound);
            }
            consumed = true;
        } else if(event.event == SubmenuIndexZoneEmulator) {
                scene_manager_next_scene(nfc->scene_manager, NfcSceneZoneList);
                consumed = true;
        } else if(event.event == SubmenuIndexSaved) {
                scene_manager_next_scene(nfc->scene_manager, NfcSceneFileSelect);
                consumed = true;
        } else if(event.event == SubmenuIndexExtraAction) {
            scene_manager_next_scene(nfc->scene_manager, NfcSceneExtraActions);
            consumed = true;
        } else if(event.event == SubmenuIndexAddManually) {
            scene_manager_next_scene(nfc->scene_manager, NfcSceneSetType);
            consumed = true;
        } else if(event.event == SubmenuIndexDebug) {
            scene_manager_next_scene(nfc->scene_manager, NfcSceneDebug);
            consumed = true;
        }
        scene_manager_set_scene_state(nfc->scene_manager, NfcSceneStart, event.event);
    }
    return consumed;
}

void nfc_scene_start_on_exit(void* context) {
    Nfc* nfc = context;

    submenu_reset(nfc->submenu);
}
