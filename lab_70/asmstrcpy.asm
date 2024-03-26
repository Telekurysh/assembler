.686
.MODEL FLAT, C
.STACK

.CODE

strcopy proc dst:DWORD, src:DWORD, len:DWORD
    pushf                       
    mov ECX, len               
    mov ESI, src                
    mov EDI, dst                

    cld

    cmp ESI, EDI               
    je exit                    

    cmp ESI, EDI              
    jg copy                   

   
    mov EAX, ESI               
    sub EAX, EDI               
    cmp EAX, len            
    jge copy                

    add EDI, len               
    dec EDI                   
    add ESI, len              
    dec ESI                    
    std                       

copy:
    rep movsb                  
                              
exit:
    popf                   
    ret
strcopy endp
END