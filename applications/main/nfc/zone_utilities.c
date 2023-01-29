//
// Created by Suekru on 1/21/2023.
//

#include "zone_utilities.h"
#include "nfc_i.h"
#include "nfc.h"

int zone = 0;
int isAutomatic = 0;
int submenuIndex = 0;
int automaticZoneCancelled = 0;

void play_zone_chip(const char* chip, int chipNum){
    Nfc* nfc = nfc_alloc();
    *nfc->chipNum = chipNum;
    // Check argument and run corresponding scene
    view_dispatcher_attach_to_gui(nfc->view_dispatcher, nfc->gui, ViewDispatcherTypeFullscreen);
    if(nfc_device_load(nfc->dev, chip, true)) {
        if(nfc->dev->format == NfcDeviceSaveFormatMifareUl) {
            scene_manager_next_scene(nfc->scene_manager, NfcSceneMfUltralightEmulate);
        } else if(nfc->dev->format == NfcDeviceSaveFormatMifareClassic) {
            scene_manager_next_scene(nfc->scene_manager, NfcSceneMfClassicEmulate);
        } else if(nfc->dev->format == NfcDeviceSaveFormatBankCard) {
            scene_manager_next_scene(nfc->scene_manager, NfcSceneDeviceInfo);
        } else {
            scene_manager_next_scene(nfc->scene_manager, NfcSceneEmulateUid);
        }
    } else {
        // Exit app
        view_dispatcher_stop(nfc->view_dispatcher);
    }
    view_dispatcher_run(nfc->view_dispatcher);

    nfc_free(nfc);
}

