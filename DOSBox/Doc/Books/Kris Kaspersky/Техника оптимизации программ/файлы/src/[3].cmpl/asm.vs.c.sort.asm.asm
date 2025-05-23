; /*--------------------------------------------------------------------------
;  *
;  *		������������ ���������� ��������� ����������� ����������
;  *
; ------------------------------------------------------------------------- */
.386
.MODEL FLAT
.CODE

_asm_sort	proc
	MOV	EDX,[ESP+8]				; ������� n

	CMP	EDX,2					; ���� �� ���� ��� ����� ��� ����������?
	JB	@exit					; ����� ��� ����������� �����

	PUSH	ESI					; \
	PUSH	EBP					;  |- ��������� ��������
	PUSH	EBX					; /
	
@while:							; do{
	MOV	ESI, [ESP+4+4*3]		;		������� src
	MOV	EDX, [ESP+8+4*3]		;		������� n

	XOR	EBP,EBP					;		���������� ���� ���������

	NOP							;		��� ��� ������������...
	NOP							;						...���������� �����

@for:							;		do{
	MOV	EAX, [ESI]				;			����� ��������� �����
	MOV	EBX, [ESI+4]			;			����� ����� ��������� �� ���������

	CMP	EAX, EBX				;			���� ����� ������� � ������ ���
	JAE	@next_for				;			�������, �� ��� ��, � ���������
								;			������...
	MOV	EBP, EBX				;					...�� ������ �� �������
	MOV	[ESI+4], EAX			;			��������� ���������� �������
	MOV	[ESI],EBX				;			�� ����������
	
@next_for:
	ADD	ESI, 4					;			���������� ��������� �� ����.
								;			����������� �����

	DEC	EDX						;			��������� ���-�� ������������
								;			(�� ���������������!) � ����
								;			������� ����� �� �������
	JNZ	@for					;		} while (�����_���_����);

	OR	EBP,EBP					;		����� ����������� ���������?
	JNZ	@while					; } while(�����_��_�����_���������_�����������);

	POP	EBX						; \
	POP	EBP						;  |- ��������������� ��������
	POP	ESI						; /

@exit:
	ret							; ������������ �� ���������
_asm_sort endp

END

