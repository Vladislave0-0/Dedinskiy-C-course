		model	small			;������ �����
		.code				;ᥣ���� ����
start:
		mov	ax,seg @data		;"�ਢ離�"
		mov	ds,ax			;ᥣ���� ������
		mov	ax,seg @stack

		mov	bx,z_seg		;��᫥���� ᥣ����
		mov	ax,es			;����塞 ࠧ���
		sub	bx,ax			;�ணࠬ��
		mov	ah,4ah
		int	21h			;�᢮������� ����� ������
		jc	to_exit

		call	main			;������ �����

to_exit:
		mov	ah,4ch
		int	21h

main		proc	near
		lea	dx,example_1
		mov	ah,9
		int	21h	
		ret
main		endp

		.data
example_1	db	'String...',13,10,36

		.stack	100


		.data?

example_2	db	?

z_seg		segment				;��᫥���� ᥣ����,
z_seg		ends				;�.�. ��� ^^^ �ᯮ������ �� ��䠢���

		end	start
