#ifndef _ENTRY_H
#define _ENTRY_H

//EL1t Exception 
#define SYNC_INVALID_EL1t		0 
#define IRQ_INVALID_EL1t		1 
#define FIQ_INVALID_EL1t		2 
#define ERROR_INVALID_EL1t		3 

//EL1h Exception
#define SYNC_INVALID_EL1h		4 
#define IRQ_INVALID_EL1h		5 
#define FIQ_INVALID_EL1h		6
#define ERROR_INVALID_EL1h		7 

//EL0_64 Exception
#define SYNC_INVALID_EL0_64	    	8 
#define IRQ_INVALID_EL0_64	    	9 
#define FIQ_INVALID_EL0_64		10 
#define ERROR_INVALID_EL0_64		11 

//EL0_32 Exception
#define SYNC_INVALID_EL0_32		12 
#define IRQ_INVALID_EL0_32		13 
#define FIQ_INVALID_EL0_32		14 
#define ERROR_INVALID_EL0_32		15 
#define SYNC_ERROR			16 
#define SYSCALL_ERROR			17 
#define DATA_ABORT_ERROR		18
#endif

