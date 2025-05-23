;*************************************************
; SAV_STR.ASM (c) Ded
;*************************************************
my_program segment                      ; ������� �ᯮ��塞��� ���� �ணࠬ��
assume cs: my_program, ds: my_program   ; CS, DS 㪠�뢠�� �� my_program
org 100h                                ; ��砫� �ᯮ��塞��� ���� � CS:100h
;-------------------------------------------------
	new_line equ 13,10
	beep     equ 7
	BUF_SIZE equ 20
;=================================================
start:	mov ah, 09h               ; ��� �㭪�� #09 - �뢥�� �� ��࠭ ��ப�
	lea dx, start_mess        ; ���� ��ப� ��� �뢮��
	int 21h                   ; ��ᨬ ��� �뢥�� ��ப�
	mov ah, 0ah               ; � AH - ����� �㭪樨 ����� ��ப� ���
	lea dx, string            ; ���� ����
	int 21h                   ; ��।��� �ࠢ����� ���
	mov bx, dx                ; ��४��뢠��
	cmp byte ptr [bx+1], 0    ; �ࠢ������ �᫮ ��������� ���� � 0
	je error                  ; ��ப� ���� - ���室�� �� error
	push dx                   ; ��࠭塞 ���� ���� � �⥪�
	mov ah, 09h               ; �㭪�� 09 ��� - �뢮� ��ப�
	lea dx, message           ; ���� ��ப� ��� �뢮��
	                          ; ᮮ�饭�� "You have typed:"
	int 21h                   ; ��।��� �ࠢ����� ���
	pop dx                    ; ����⠭�������� DS - ⥯��� ⠬ �����
	                          ; ���� ����
	inc dx                    ; ⥯��� DX 㪠�뢠�� �� 1-� ����
				  ; - �ய�᪠�� ࠧ��� ����
	inc dx                    ; ⥯��� DX 㪠�뢠�� �� 2-� ����
				  ; - �ய�᪠�� �᫮ ��������� ᨬ�����
				  ; ������ DX 㪠�뢠�� �� ᠬ� ��ப�
	int 21h                   ; �뢮��� ��ப� (���� ��������� ᨬ�����)
	jmp exit                  ; ���室�� �� ����� (��...)


error:	mov ah, 09h               ; �訡��: ����� ��ப�. �뢮��� ᮮ⢥�-
				  ; ����饥 ᮮ�饭�� � ��騬 1 ᥪ.
	lea dx, mess_noth         ; ���� ��ப� ��� �뢮��
	int 21h                   ; ��ᨬ ��� �뢥�� ��ப�

exit:	mov ax, 4c00h             ; ��室�� �� �ணࠬ�� � ����� ��室� 0
	int 21h                   ; ��室��...

	string  db BUF_SIZE,0, BUF_SIZE+2 dup ('$')   ; ���� ��� �����.
						      ; 0-� ���� - ࠧ���
						      ; 1-� ���� - ��������
						      ; ��� (�᫮ ����⢨-
						      ; ⥫쭮 ��������� ᨬ-
						      ; �����).
	message db 10, 'You have typed:',new_line,'$' ; ����饭�� ��� �뢮��
						      ; �� ��࠭ ('$' - �ਧ���
	start_mess db 'Copyright (c) Ded, 1990. '     ; ���� (��...) ��ப�
		   db 'Welcome to DOS input!', new_line
		   db 'Type some letters and press ENTER.'
		   db new_line, '$'
	mess_noth  db beep, 'You typed nothing!', '$'
;==================================================
my_program ends                   ; ����� (��...) ᥣ����
;**************************************************
end start                         ; �ᯮ��塞� ��� ��稭����� � ��⪨ start

