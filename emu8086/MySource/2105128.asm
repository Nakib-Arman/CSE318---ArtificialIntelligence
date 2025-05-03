
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

.MODEL SMALL
.STACK 100H

.DATA
CR EQU ODH
LF EQU OAH    

PREV DW ?
SEC_PREV DW ?

.CODE 
    MOV AX,@DATA
    MOV DS,AX  
    
    MOV AH,1
    INT 21H
    
    MOV CL,AL 
    SUB CL,'0'
    AND CH,0  
    MOV AX,0
    CALL FIB 
    
    MOV AH,4CH
    INT 21H  

     
FIB:
    PUSH CX
    CMP CX,2
    JLE BASE_CASE 
     
    SUB CX,1 
    CALL FIB
    PUSH AX  
    SUB CX,1
    CALL FIB
    PUSH AX
       
    POP AX
    POP BX
    POP CX 
    ADD AX,BX
    RET
    
BASE_CASE:
    MOV AX,1
    POP CX
    RET
 

        
        

