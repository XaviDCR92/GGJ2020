#ifndef SFX_HEADER__
#define SFX_HEADER__

#include <stdbool.h>
#include <psxspu.h>

/* *************************************
 *  Includes
 * *************************************/

/* *************************************
 *  Defines
 * *************************************/

#define MAX_VOLUME SPU_MAXVOL

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

 /* *************************************
 *  Structs and enums
 * *************************************/

/* *************************************
 *  Global prototypes
 * *************************************/
void SfxPlaySound(SsVag* sound);
void SfxStopSound(SsVag* sound);
void SfxPlaySoundVolVoice(SsVag* sound, const unsigned char voice, const unsigned short vol);
bool SfxUploadSound(const char* const file_path, SsVag* const vag);
void SfxVoiceVol(const unsigned char voice, const unsigned short volume);

#ifdef __cplusplus
}
#endif

#endif //SFX_HEADER__
