#ifndef __TTL_USB_H
#define __TTL_USB_H


void TTL_USB_Init(void);

void TTL_USB_SendByte(uint8_t Byte);

void TTL_USB_SendArray(uint8_t *Array, uint16_t Length);

void TTL_USB_SendString(char *String);

//void TTL_USB_Printf(char *format, ...);

#endif
