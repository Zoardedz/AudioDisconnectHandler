#include <Main.h>
#include <audiopolicy.h>
#include <Windows.h>
#include <mmdeviceapi.h>
#include <Shlwapi.h>
#include "AudioManager.h"
#include <new>

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "ole32.lib")

template <class T> void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

HRESULT AudioManager::CreateInstance(AudioManager** ppAudioManager) {
    AudioManager* pAudioManager = new (std::nothrow) AudioManager();

    if (pAudioManager == NULL)
        return E_OUTOFMEMORY;

    HRESULT hr = pAudioManager->Initialize();

    if (SUCCEEDED(hr))
    {
        *ppAudioManager = pAudioManager;
    }
    else
    {
        pAudioManager->Release();
    }

    return hr;
}

/*std::function<STDMETHODIMP(AudioSessionDisconnectReason)> AudioManager::OnSessionDisconnected(AudioSessionDisconnectReason ass){
    
    std::cout << ass;
    //Main_obj::am.OnSessionDisconnected(ass);
    return ass;
}
*/
//probably never used, just define it nevertheless
STDMETHODIMP AudioManager::QueryInterface(REFIID riid, void** ppv)
{
    static const QITAB qit[] =
    {
        QITABENT(AudioManager, IAudioSessionEvents),
        { 0 },
    };
    return QISearch(this, qit, riid, ppv);
}


STDMETHODIMP_(ULONG) AudioManager::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) AudioManager::Release()
{
    LONG cRef = InterlockedDecrement(&m_cRef);
    if (cRef == 0)
    {
        delete this;
    }
    return cRef;
}

HRESULT AudioManager::Initialize(){
    HRESULT hr = S_OK;
    CoInitialize(NULL);
    IMMDeviceEnumerator* pDeviceEnumerator = NULL;
    IMMDevice* pDevice = NULL;
    IAudioSessionManager* pAudioSessionManager = NULL;

    // Get the enumerator for the audio endpoint devices.
    hr = CoCreateInstance(
        __uuidof(MMDeviceEnumerator),
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&pDeviceEnumerator)
    );

    if (FAILED(hr))
        goto done;

    hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

    if (FAILED(hr))
        goto done;

    // Get the session manager for this device.
    hr = pDevice->Activate(
        __uuidof(IAudioSessionManager),
        CLSCTX_INPROC_SERVER,
        NULL,
        (void**)&pAudioSessionManager
    );
    
    if (FAILED(hr))
        goto done;

    // Get the audio session.
    hr = pAudioSessionManager->GetAudioSessionControl(
        &GUID_NULL,     // Get the default audio session.
        FALSE,          // The session is not cross-process.
        &m_pAudioSession
    );

    if (FAILED(hr))
        goto done;

    m_pAudioSession->RegisterAudioSessionNotification(this);

done:
    SafeRelease(&pDeviceEnumerator);
    SafeRelease(&pDevice);
    SafeRelease(&pAudioSessionManager);
    return hr;
}