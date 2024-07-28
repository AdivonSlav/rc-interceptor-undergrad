#include "main.h"

#include "application.h"
#include "data_processing.h"
#include "entrypoint.h"

void CORE_Entrypoint(TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim2,
                     TIM_HandleTypeDef *htim3, TIM_HandleTypeDef *htim4) {
  Core::Application app;
  Core::Timers::SetTimers(htim1, htim2, htim3, htim4);

  app.Run();
}