#pragma once

/*#if defined REG_SIZE8

#elif defined REG_SIZE16
#define REG_SIZE 16 printf("Hello");
#endif
*/
#define REG_SIZE 8
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))
#define CLEAR_BIT(REG,BIT) (REG&=~(1<<BIT))
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))
#define READ_BIT(REG,BIT) ((REG&(1u<<BIT))>>BIT)
#define ROTATE_LEFT(REG,NUMBER) (REG=((REG<<NUMBER)|(REG>>REG_SIZE-NUMBER)))
#define ROTATE_RIGHT(REG,NUMBER) (REG=((REG>>NUMBER)|(REG<<REG_SIZE-NUMBER)))
