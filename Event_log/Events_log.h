/*
 * Events_log.h
 *
 *  Created on: 09-Mar-2024
 *      Author: SoftwareRND
 */

#ifndef EVENTS_LOG_H_
#define EVENTS_LOG_H_

void event_no_update(uint8_t event_no);
uint8_t event_display();
void events_option_scroll(uint8_t prev_option,uint8_t curr_option,uint8_t page,uint16_t array[20],
		uint16_t array1[20],uint16_t array2[20]);
void event_info_option_frame(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void events_split_screen(void);
void events_option_frame1(uint8_t page,uint8_t start_opt,uint8_t end_opt);
void events_info_scroll(uint8_t prev_option,uint8_t curr_option,uint8_t page,uint16_t array[20],
		uint16_t array1[20], char* array2[35]);
#endif /* EVENTS_LOG_H_ */
