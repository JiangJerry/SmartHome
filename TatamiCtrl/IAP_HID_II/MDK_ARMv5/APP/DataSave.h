#ifndef __DATA_SAVE_H
#define __DATA_SAVE_H

#define StartAddress    (1024 * 50)
#define EndAddress      (1024 * 51)

#define TEST_DATA       (0x12345678)

u32 SaveData(u32 Data);
u32 ReadData(void);



#endif
