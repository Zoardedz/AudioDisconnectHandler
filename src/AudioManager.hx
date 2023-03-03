package;

typedef LONG = Null<Int>;
typedef HRESULT = LONG;

enum DisconnectReason {
    DisconnectReasonDeviceRemoval; 	
    DisconnectReasonServerShutdown; 
    DisconnectReasonFormatChanged;
    DisconnectReasonSessionLogoff;
    DisconnectReasonSessionDisconnected;
    DisconnectReasonExclusiveModeOverride;
}

@:include("./externs/AudioManager.cpp")
@:include("./externs/AudioManager.h")
@:native("AudioManager*")

extern class AudioManager {
    @:native("AudioManager::CreateInstance") public static function CreateInstance(ppAudioManager:cpp.Star<AudioManager>):HRESULT;
}