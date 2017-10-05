	.386p

.model tiny

code	segment use16
	assume cs:code
	org  100h  ;delka PSP

;zacatek programu

begin:
  ;zajistime, ze mame spravny rezim obrazovky 
  mov ax, 3h
  int 10h

  mov dx,cs
  mov ds,dx
  mov es, dx
	
  ;zacneme s desifrovanim

  xor eax, eax
  xor ecx, ecx
  xor ebx, ebx
  xor edx, edx
  xor esi, esi
  
  mov bx, offset key1
  mov si, offset key2
  mov dx, offset key3

  ;nasledujuci kod nastavi eax na 1
  ; je to jmp -1 nasledovany inc eax, ktery je ted 0
  db 0ebh, 0ffh, 0c0h

  add si, ax

  ;nasleduje for cyklus 
  mov cl, byte ptr ds:[keylen]
decrypt:

  mov al, byte ptr ds:[edx]
  mov al, byte ptr es:[esi+eax]
  add byte ptr ds:[bx], al

  inc ebx
  inc edx

  dec cx
  cmp cx, 0
  jnz decrypt
	  
  ;napiseme dekodovany retezec
  mov dx, offset key1
  mov ah, 09
  int 21h

  ;a na zaver jeste napiseme logo do praveho horniho rohu
  mov ax, 0b800h
  mov ds, ax
  mov di, 0
                                                      
  mov word ptr [di+146], 794Bh   ;K
  mov word ptr [di+148], 7949h   ;I
  mov word ptr [di+150], 7956h   ;V
  mov word ptr [di+152], 792Fh   ;/
  mov word ptr [di+154], 794Fh   ;O
  mov word ptr [di+156], 7953h   ;S
  mov word ptr [di+158], 7921h   ;!

  int 20h			;normalni konec
	
;VB08 sifrovaci klice

;inicializovana data
keylen db 13
key1 db 20h, 3ah, 23h, 32h, 0bh, 3dh, 1fh, 13h, 4ch, 19h, 05h, 07h, 07h, 00h
key2 db 00h, 0ah, 11h, 08h, 03h, 1dh, 1ah, 08h, 04h, 2ch, 3fh, 33h, 1ah, 41h
key3 db 01h, 00h, 08h, 0bh, 0ch, 07h, 0ah, 05h, 02h, 09h, 06h, 03h, 04h, 00h


code	ends
	end begin