#include "../nfc_i.h"
#include "../zone_info.h"
#include "../zone_utilities.h"

#define NFC_MF_UL_DATA_NOT_CHANGED (0UL)
#define NFC_MF_UL_DATA_CHANGED (1UL)

bool nfc_mf_ultralight_emulate_worker_callback(NfcWorkerEvent event, void* context) {
    UNUSED(event);
    Nfc* nfc = context;

    scene_manager_set_scene_state(
        nfc->scene_manager, NfcSceneMfUltralightEmulate, NFC_MF_UL_DATA_CHANGED);
    return true;
}

void automatic_chip(Nfc* nfc){
    //furi_delay_ms(3000);

    int max = 2 + 10;
    int min = 2 - 10;

    int time = rand() % (max + 1 - min) + min;
    time = 5;

    while(time > 0 && !automaticZoneCancelled) {
        for(int x = 1000; x > 1; x--){
            furi_delay_ms(1);
            if(automaticZoneCancelled) break;
        }
        nfc_text_store_set(nfc, "Next Chip:\n%d seconds\n(%d/%d)", time, *nfc->chipNum, zoneLengths[zone]);
        time--;
    }

    nfc_worker_stop(nfc->worker);
    nfc_blink_stop(nfc);

    view_dispatcher_stop(nfc->view_dispatcher);
}

void nfc_scene_mf_ultralight_emulate_on_enter(void* context) {
    Nfc* nfc = context;
    // Setup view
    MfUltralightType type = nfc->dev->dev_data.mf_ul_data.type;
    bool is_ultralight = (type == MfUltralightTypeUL11) || (type == MfUltralightTypeUL21) ||
                         (type == MfUltralightTypeUnknown);
    Popup* popup = nfc->popup;

    if(zone > 0) {
        popup_set_header(popup, zoneName, 55, 13, AlignLeft, AlignTop);
    }
    else popup_set_header(popup, "Emulating", 67, 13, AlignRight, AlignTop);

    if(zone > 0){
        nfc_text_store_set(nfc, "%s\n(%d/%d)",nfc->dev->dev_name, submenuIndex+1, zoneLengths[zone]);
    } else if(strcmp(nfc->dev->dev_name, "") != 0) {
        nfc_text_store_set(nfc, "%s", nfc->dev->dev_name);
    } else if(is_ultralight) {
        nfc_text_store_set(nfc, "MIFARE\nUltralight");
    } else {
        nfc_text_store_set(nfc, "MIFARE\nNTAG");
    }
    popup_set_icon(popup, 0, 3, &I_NFC_dolphin_emulation_47x61);

    if(zone > 0) popup_set_text(popup, nfc->text_store, 55, 28, AlignLeft, AlignTop);
    else popup_set_text(popup, nfc->text_store, 67, 28, AlignLeft, AlignTop);


    // Setup and start worker
    view_dispatcher_switch_to_view(nfc->view_dispatcher, NfcViewPopup);
    nfc_worker_start(
        nfc->worker,
        NfcWorkerStateMfUltralightEmulate,
        &nfc->dev->dev_data,
        nfc_mf_ultralight_emulate_worker_callback,
        nfc);
    nfc_blink_emulate_start(nfc);

    //if(zone > 0 && isAutomatic) automatic_chip(nfc, popup);
}

bool nfc_scene_mf_ultralight_emulate_on_event(void* context, SceneManagerEvent event) {
    Nfc* nfc = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeBack) {
        if(zone > 0 && isAutomatic){
            automaticZoneCancelled = 1;
        }
        // Stop worker
        nfc_worker_stop(nfc->worker);
        // Check if data changed and save in shadow file
        if(scene_manager_get_scene_state(nfc->scene_manager, NfcSceneMfUltralightEmulate) ==
           NFC_MF_UL_DATA_CHANGED) {
            scene_manager_set_scene_state(
                nfc->scene_manager, NfcSceneMfUltralightEmulate, NFC_MF_UL_DATA_NOT_CHANGED);
            // Save shadow file
            if(furi_string_size(nfc->dev->load_path)) {
                nfc_device_save_shadow(nfc->dev, furi_string_get_cstr(nfc->dev->load_path));
            }
        }
        consumed = false;
    }
    return consumed;
}

void nfc_scene_mf_ultralight_emulate_on_exit(void* context) {
    Nfc* nfc = context;

    // Clear view
    popup_reset(nfc->popup);

    nfc_blink_stop(nfc);
}
