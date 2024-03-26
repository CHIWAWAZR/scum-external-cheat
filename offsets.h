// offsets.h
#pragma once

namespace Offsets {
    namespace UWorld {
        const int PersistentLevel = 0x30;
        const int OwningGameInstance = 0x180;
    }
    namespace UGameInstance {
        const int LocalPlayers = 0x38;
    }
    namespace UPlayer {
        const int PlayerController = 0x30;
    }
    namespace UPlayerController {
        const int PlayerCameraManager = 0x2b8;
        const int Pawn = 0x2A0;
    }
    namespace UPlayerCameraManager {
        const int FOV = 0x2a8; 
    }
    namespace APawn {
        const int PlayerState = 0x240;
    }
    namespace APlayerState {
        //const int PlayerName = 0x318;
        //const int Ping = 0x238;
        //const int PlayerId = 0x234;
    }

    namespace USkinnedMeshComponent {
        //const int CachedWorldSpaceBounds = 0x6c4;
    }
    namespace ACharacter {
       // const int CharacterMovement = 0x2a0;
        //const int Mesh = 0x298;
    }

}