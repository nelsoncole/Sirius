/*
 * File Name: rtc.c
 *
 *
 * BSD 3-Clause License
 * 
 * Copyright (c) 2019, nelsoncole
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
#include <os.h>

// convert BCD para Decimal
#define convert_bcd(val)  ((val / 16) * 10 + (val & 0xf))

UINT8 *clock = NULL;

VOID disable_NMI(){

	char val = inportb(0x70);
	val |= 0x80;
    	outportb(0x70,val);

}

VOID enable_NMI(){

	char val = inportb(0x70);
	val &=~0x80;
    	outportb(0x70,val);
}
 


UINTN rtc_install(){

	clock = (UINT8*) rtc;


	disable_NMI();

    	UINT8 status;

    	// registro status B e desabilita NMI
    	outportb(0x70,0x8B);
    	// ler actual valor de status B  
    	status = inportb(0x71);
	
    	// registro status B 
    	outportb(0x70,0x8B);
	
    	//bit 6: Hablita interrupções periódica IRQ8,
    	//bit 5 : hablita interrupção de alarme ,
    	//bit 2 : caledário em formato binário,
    	//bit 1 : formato 24h
    	outportb(0x71, status |/* 0x66*/ 0x62); 


    	enable_NMI();
	

	return 0;
}



// código c para o manipulador IRQ8 offset no IDT vetor 40
VOID rtc_handler(VOID){
	static unsigned char status;
	outportb(0x70,0x0C);
	// é importante ler do registro status C 
 	status = inportb(0x71);


	if(status);

	outportb(0x70,0);
	clock[0] = convert_bcd(inportb(0x71)) &0x3f;

	outportb(0x70,2);
	clock[1] = convert_bcd(inportb(0x71)) &0x3f;


	outportb(0x70,4);
	clock[2] = convert_bcd(inportb(0x71)) &0x1f;

}





UINT8 read_time(UINTN type){
	/*
	|------|-----------|
	| type | descricao |
	|------------------|
	| 0    | segunddos |
	| 2    | minutos   |
	| 4    | hora      |
	| 6    | dia       |
	| 7    | dia de mes|
	| 8    | mes       |
	| 9    | ano       |
	|------|-----------|
	
	
	*/
	disable_NMI();
	outportb(0x70,type);
	UINT8 val =inportb(0x71);
	enable_NMI();
	return val;
}
