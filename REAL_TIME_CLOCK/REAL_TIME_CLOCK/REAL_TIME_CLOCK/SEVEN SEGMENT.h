/*
 * SEVEN_SEGMENT.h
 *
 * Created: 18-Jul-23 8:09:28 PM
 *  Author: MT
 */ 


#ifndef SEVEN SEGMENT_H_
#define SEVEN SEGMENT_H_

void SEVEN_SEGMENT_INT (unsigned char portname);
void SEVEN_SEGMENT_write (unsigned char portname, unsigned char number,unsigned char Comm_Cathode_1_Comm_Anode_2);

void SEVEN_SEGMENT_INT_BCD (unsigned char portname,unsigned char firstpin);
void SEVEN_SEGMENT_write_BCD (unsigned char portname,unsigned char firstpin,unsigned char number);

#endif /* SEVEN SEGMENT_H_ */