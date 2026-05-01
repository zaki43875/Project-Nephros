//Define to prevent recursive inclusion 
#define __PUMPMOTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

    //INCLUDES
    #include "main.h"

    //Defines
    void StartMotorPWM(void);
    void UpdateFrequency(uint32_t frequency);
    uint32_t GetFrequency(void);
    void StartPump(void);
    void EndPump(void);
    void UpdatePID(int error); //need to update error type

#ifdef __cplusplus
}
#endif
#endif /*__ PUMPMOTOR_H__ */