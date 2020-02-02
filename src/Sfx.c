/* *************************************
 *  Includes
 * *************************************/
#include "Sfx.h"
#include "Serial.h"
#include "IO.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* *************************************
 *  Defines
 * *************************************/

#define NUMBER_OF_VOICES 24

/* *************************************
 *  Local Prototypes
 * *************************************/

/* *************************************
 *  Local Variables
 * *************************************/
static bool usedVoices[NUMBER_OF_VOICES];

void SfxPlaySoundVolVoice(SsVag* sound, const unsigned char voice, const unsigned short vol)
{
    if (sound->data_size)
    {
        SsPlayVag(sound, voice, vol, vol);
    }
}

void SfxPlaySound(SsVag* const sound)
{
    SfxPlaySoundVolVoice(sound, sound->cur_voice, MAX_VOLUME);
}

void SfxVoiceVol(const unsigned char voice, const unsigned short volume)
{
    SsVoiceVol(voice, volume, volume);
}

void SfxStopSound(SsVag* sound)
{
    SsStopVag(sound);
}

bool SfxUploadSound_Ex(const char* file_path, SsVag* vag, uint8_t voiceIndex)
{
#ifdef PSXSDK_DEBUG
    static size_t SPUBytesUsed;
#endif // PSXSDK_DEBUG

    if (voiceIndex >= NUMBER_OF_VOICES)
    {
        printf(  "Invalid input voice index %d. Only indexes [%d-%d] are allowed.\n",
                        voiceIndex,
                        0,
                        NUMBER_OF_VOICES - 1    );
        return false;
    }

    if (usedVoices[voiceIndex])
    {
        printf("Voice number %d is already being used.\n", voiceIndex);
        return false;
    }

    const uint8_t *buffer;
    size_t fileSize;

    if ((buffer = IOLoadFile(file_path, &fileSize)))
    {
        if (fileSize)
        {
            SsReadVag(vag, buffer);

            SsUploadVag(vag);

            vag->cur_voice = voiceIndex;

            usedVoices[voiceIndex] = true;

#ifdef PSXSDK_DEBUG

            SPUBytesUsed += vag->data_size;

            if (SPUBytesUsed != 0)
            {
                enum
                {
                    SPU_MAX_ALLOWED_BYTES = 512 * 1024 // 512 KBytes
                };

                uint16_t percentage = SPUBytesUsed * 100 / SPU_MAX_ALLOWED_BYTES;

                dprintf("SPU usage: %d%%\n", percentage);
            }

#endif // PSXSDK_DEBUG

            return true;
        }
    }

    return false;
}

bool SfxUploadSound(const char* file_path, SsVag* vag)
{
    bool success = false;
    uint8_t i;

    for (i = 0; i < NUMBER_OF_VOICES; i++)
    {
        if (usedVoices[i] == false)
        {
            success = true;
            break;
        }
    }

    if (success == false)
    {
        printf("Could not find any free SPU slot.\n");
        return false;
    }

    return SfxUploadSound_Ex(file_path, vag, i);
}
