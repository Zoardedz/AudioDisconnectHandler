#include <hxcpp.h>
#include <audiopolicy.h>
#include <Windows.h>
#include <mmdeviceapi.h>
#include <Main.h>
#include <iostream>

class AudioManager : public IAudioSessionEvents
{
public:
    // Static method to create an instance of the object.
    static HRESULT CreateInstance(
        AudioManager **ppAudioManager
    );

    // IUnknown methods.
    STDMETHODIMP QueryInterface(REFIID iid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IAudioSessionEvents methods.
    STDMETHODIMP OnDisplayNameChanged(LPCWSTR, LPCGUID)
    {
        return S_OK;
    }
    
    STDMETHODIMP OnIconPathChanged(LPCWSTR, LPCGUID)
    {
        return S_OK;
    }

    STDMETHODIMP OnChannelVolumeChanged(DWORD, float[], DWORD, LPCGUID)
    {
        return S_OK;
    }

    STDMETHODIMP OnGroupingParamChanged(LPCGUID, LPCGUID)
    {
        return S_OK;
    }

    STDMETHODIMP OnStateChanged(AudioSessionState)
    {
        return S_OK;
    }

    STDMETHODIMP OnSimpleVolumeChanged(
        float NewVolume,
        BOOL NewMute,
        LPCGUID EventContext
    ) {
        return S_OK;
    };

    void disconnected(AudioSessionDisconnectReason ass){
        ::Main_obj::imhavingsex(ass);
    }

    //i DO NOT care.
    STDMETHODIMP OnSessionDisconnected(AudioSessionDisconnectReason ass) {
        int base = 99;
        hx::SetTopOfStack(&base, true);
        const_cast<AudioManager*>(this)->disconnected(ass);
        hx::SetTopOfStack((int*)0, true);
        return ass;
    }

    //AudioManager();
    //~AudioManager();

protected:
    HRESULT Initialize();

private:
    LONG m_cRef;                        // Reference count.
    //UINT m_uNotificationMessage;        // Window message to send when an audio event occurs.
    //HWND m_hwndNotification;            // Window to receives messages.
    //BOOL m_bNotificationsEnabled;       // Are audio notifications enabled?

    IAudioSessionControl *m_pAudioSession;
};