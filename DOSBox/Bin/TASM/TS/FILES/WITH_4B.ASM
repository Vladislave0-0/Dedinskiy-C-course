;�ਬ�� ����᪠ �ணࠬ�
;� ������� �㭪樨 DOS

	model	tiny
	.code
	org	100h
start:
	lea	bx,heep+300h	;����� �ணࠬ��+
	mov	dx,bx		;300-20 ���� ��� �⥪
	mov	cl,4		;
	shr	bx,cl		;
	mov	ah,4ah		;�����।�����
	int	21h		;������
	jnc	ok_mem
	ret
ok_mem:
	sub	dx,20		;�����, �⮡ ��
	cli			;������ MCB
	pop	ax		;������� �� ��ண� �⥪�...
	mov	sp,dx		;��४��祭�� �⥪�
	push	ax		;... � ������ � ����


	mov	_ss,ss		;���������
	mov	_sp,sp		;SS � SP
	sti
	
	lea	ax,com_line	;����ᥭ��
	lea	bx,param	;����
	mov	[bx]+2,ax	;��ࠬ��஢
	mov	ax,cs		;���������
	mov	[bx]+4,ax	;��ப�


	lea	bx,param	;��ࠬ����
	lea	dx,filename	;��� 䠩��
	mov	ax,4b00h	;����㧪� � �����
	int	21h		;

	mov	ax,cs		;����⠭�������
	mov	ds,ax		;����������
	mov	es,ax		;ॣ���஢
	cli			;
	mov	ss,_ss		;
	mov	sp,_sp		;
	sti
	ret

;			� �����! ��ப� ��ࠬ��஢
com_line	db	7,'c: /u' ,13
filename	db	'c:\dos\format.com',0
param		dw	7 dup(0)
_ss		dw	0
_sp		dw	0

heep		db	''
	end	start
