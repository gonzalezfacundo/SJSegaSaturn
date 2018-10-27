Uint32 SDL_GetTicks(void)
{
previouscount += TIM_FRT_CNT_TO_MCR(TIM_FRT_GET_16()) / 1000; 
	TIM_FRT_SET_16(0); 
	return previouscount;
}