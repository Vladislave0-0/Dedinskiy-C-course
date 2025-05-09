;*************************************************
; SAV_MUS.ASM     Version 2.0     12/20/90 00:17am (c) Ded
;*************************************************
my_program segment
assume cs:my_program, ds:my_program
org 100h
;------------------------------------------------
	port_b       equ  61h         	; ���� ���� � �ணࠬ���㥬���
					; ����਩���� ����䥩�
	command_reg  equ  43h         	; ���� ������ �����奬� 8255
	channel_2    equ  42h         	; ���� ������ 2 �����奬� 8255

	DV      equ 1190000             ; ����⥫� ��� ����� ��㪠
	TACT    equ 3                   ; ���⥫쭮��� ��� � 1/18.2 - ᥪ㭤���
					; ���ࢠ���

	DOd1    equ DV/138              ; ����⥫� ��� ��㪮� ��⠢� (����)
	RE1     equ DV/146              ;
	MI1     equ DV/164              ;
	FAd1    equ DV/185              ;
	SOL1    equ DV/196              ;
	SOLd1   equ DV/207              ;
	LA1     equ DV/220              ;
	SI1     equ DV/247              ;

	DOd2    equ DV/277              ;
	RE2     equ DV/294              ;

	PAUSE   equ 10                  ; �ய�� ⠪� (���砭�� � ���⮩
					; 119 ���)
;================================================
start:					; ��砫� �ணࠬ��
	mov ah, 09h                     ; �뢮��� �� ��࠭ ᮮ�饭�� 1
	lea dx, mess1
	int 21h
 	call set_timer                  ; ��⠭�������� ᢮� ��ࠡ��稪 ⠩���
	call initsound                  ; �����⠢������ �����奬� ��㪠
	cld                             ; SI �㤥� 㢥��稢����� � 室� 横��
	mov cx, NSOUNDS                 ; � CX - �᫮ ���
	lea si, mus_tab                 ; � SI - ���� ⠡���� ���. �ࠧ�
next:	lodsw                           ; ����㦠�� ����
	call sound                      ; ������ ���
	call delay                      ; ���� 1 ⠪�
	loop next                       ; �� ᫥���騩 横�
	call nosound                    ; �� ���� �⧢�砫� - �몫�砥� ���
	call restore_timer              ; ����⠭�������� ��室�� ��ࠡ��稪
					; ⠩���
	mov ah, 09h                     ; ���⠥� �� ��࠭� ᮮ�饭�� 2
	lea dx, mess2
	int 21h
	mov ax, 4c00h                   ; ��室�� � ��� � ����� 0 (�� O.k.)
	int 21h  	                ; ��室��...

	mus_tab dw PAUSE, RE2,RE2,RE2,RE2           ; ��몠�쭠� �ࠧ�
	        dw        DOd2,DOd2,DOd2
		dw        SOLd1
		dw        SI1
		dw PAUSE, LA1
		dw PAUSE, SOL1
		dw PAUSE, MI1
		dw PAUSE, RE1,RE1
		dw        DOd1
		dw        RE1
		dw        FAd1,FAd1
		dw        MI1
		dw        FAd1
		dw        MI1,MI1,MI1,MI1
		dw        RE1,RE1,RE1

	NSOUNDS equ ($-mus_tab)/2         ; ��᫮ ���

	mess1 db 'Copyright (c) Ded, 1990. '
	      db 'Welcome to PC music!', 13,10, '$'
	mess2 db 'Thank you for attention.$'
;================================================
new08 proc far                          ; ��� ��ࠡ��稪 ⠩���. �� ���祭��
					; ��।�������� �६��� ���뢠�� � 0
					; 䫠� ����প� delay_flag (�. ��-
					; 楤��� delay, ����� �� �ࠢ�����)
	inc cs:number_ticks             ; �����稢��� �᫮ ⨪�� (�맮���)
	cmp cs:number_ticks, TACT       ; �६� ����諮?
	jb exit08                       ; ��� - ��室��
	mov cs:delay_flag, 0            ; �� - 1) ����塞 䫠� ����প�
	mov cs:number_ticks, 0          ;      2) ���뢠�� �᫮ ⨪��
exit08:	jmp old08                       ; ��室: ��뢠�� ��室�� ��ࠡ��稪
					; ⠩���

	old08        dd ?               ; ���� ��ண� ��ࠡ��稪� ⠩���
	number_ticks dw 0               ; ���稪 ⨪�� (�맮���)
	delay_flag   dw 0               ; ���� ����砭�� ����প�
new08 endp
;-------------------------------------------------
set_timer proc                          ; ��⠭���� ᮡ�⢥����� ��ࠡ��稪�
					; ���뢠��� ⠩���
	mov ax, 3508h                   ; �㭪�� ��� #35 - ���� ���� �����
					; ���뢠��� #08
	int 21h                         ; ��।��� ���
	mov word ptr old08, bx          ; ���������� ���� ��ண� ��ࠡ��稪�:
	mov word ptr old08+2, es        ; ᭠砫� ᬥ饭��, ��⮬ ᥣ����
	mov ax, 2508h                   ; �㭪�� ��� #25 - ��⠭����� �����
	lea dx, new08                   ; ���� ������ ��ࠡ��稪� ⠩���
	int 21h                         ; ��⠭�������� ᢮� ��ࠡ��稪
	ret                             ;
set_timer endp                          ; (Destroys AX, BX, DX, ES)
;-------------------------------------------------
restore_timer proc                      ; ����⠭�������� ���� ��ࠡ��稪
	push ds                         ; ���࠭塞 DS
	mov ax, 2508h                   ; �㭪�� ��� #25 - ��⠭����� �����
	lds dx, old08                   ; ���� ��ண� ��ࠡ��稪� ⠩���
	int 21h                         ; ��।��� ���
	pop ds                          ; ����⠭�������� DS
	ret                             ;
restore_timer endp                      ; (Destroys AX, DX)
;-------------------------------------------------
initsound proc                          ; �����⮢�� �����奬� 8255
	in al, port_b     		; ��⠥� �� ���� �
   	or al, 3                        ; ��⠭�������� 3 ������ ���
   	out port_b, al                  ; ���뫠�� ���⭮
     	mov al, 10110110b               ; ��⠭�������� ०�� ��饭��
					; � ������� 2 �����奬� 8255
     	out command_reg, al             ; ���뫠�� ��� ०��� ��饭��
	ret                             ;
initsound endp                          ; (Destroys AX)
;-------------------------------------------------
sound proc near                         ; ��⠭�������� ����� ���砭��
   	out channel_2, al               ; ���뫠�� ������ ���� �����
   	mov al, ah                      ; ������� out �ᯮ���� ⮫쪮 AL
   	out channel_2, al               ; ���뫠�� ���孨� ����
	ret                             ;
sound endp                              ; (Destroys AX)
;-------------------------------------------------
nosound proc                            ;
	in   al, port_b     		; ����뢥� 3 ������ ��� � ����� B
   	and  al, 11111100b     		; ����਩���� ����䥩�
   	out  port_b, al                 ;
	ret                             ;
nosound endp                            ; (Destroys AX)
;------------------------------------------------
delay proc                              ; ����, ���� ⠩��� �� ���� delay_flag
delay1:	cmp delay_flag, 0               ; ���� ��襭?
	jne delay1                      ; ��� - ����, ���� ������
	mov delay_flag, 1               ; �� - ᭮�� ��⠭�������� 䫠�
	ret                             ; � �����頥���
delay endp                              ;
;------------------------------------------------
my_program ends
;************************************************
end start