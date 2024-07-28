#ifndef __ENTRYPOINT_H
#define __ENTRYPOINT_H

#ifdef __cplusplus
extern "C" {
#endif

void CORE_Entrypoint(TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim2,
                     TIM_HandleTypeDef *htim3, TIM_HandleTypeDef *htim4);

#ifdef __cplusplus
}
#endif

#endif