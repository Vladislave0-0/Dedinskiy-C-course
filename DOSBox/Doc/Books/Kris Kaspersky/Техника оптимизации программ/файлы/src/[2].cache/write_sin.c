/*----------------------------------------------------------------------------
 *
 *					������, ��������������� �����������
 *				������������� ������� ������ (STORE BUFFERS)
 *
 * Build 0x001 08.08.2002
----------------------------------------------------------------------------*/

// ������������
//#define __WRITE_MISS__
// ����������������� ��� ��� ������������ �������� ������
// � �������� ������ ������  �����  ����������� � ������,
// ��� ����������� � L1-����

#include <DoCPU.h>

main()
{
	int		*p;
	int		a, b, d;
	float	x = 0.666;

	// TITLE
	PRINT("= = = ������������� ������� ������ = = =\n");
	PRINT_TITLE;

	// ��������� ������
	p = malloc(1*M);

	/*------------------------------------------------------------------------
	 *
	 *						������������������ �������
	 *
	------------------------------------------------------------------------*/
	A_BEGIN(0)
		// 192 ������ ���� DWORD ���� � ����� 776 ���� ������,
		// ���  �����  ���������  �������  �������  ������  ��
		// ����������� P-II/P-III.���-�� ���������� ����������
		// ��������� ����� � ���������� �������� ������  �����
		// �����������   �������  ��������, �.�.  ��  ��������
		// ������ ��� ���������� �������� �������
		for(a = 0; a < 192; a += 8)
		{
			// ��� ��������� ��������� �������� ����
			// ������   ����  ���������,  �����  ���
			// ����������� ������ ������������������
			p[a + 0] = (a + 0);
			p[a + 1] = (a + 1);
			p[a + 2] = (a + 2);
			p[a + 3] = (a + 3);
			p[a + 4] = (a + 4);
			p[a + 5] = (a + 5);
			p[a + 6] = (a + 6);
			p[a + 7] = (a + 7);
		}
		
		// ������ ��������� ����������
		for(b = 0; b < 66; b++)
			x += x/cos(x);
		
		#ifdef __WRITE_MISS__
			// ��������� ������ � ������,
			// ������������� � L1-����
			p += 196;
		#else
			// ��������� ������ � ������,
			// �������������� � L1-����
		#endif

	A_END(0)

	/*------------------------------------------------------------------------
	 *
	 *						���������������� �������
	 *
	------------------------------------------------------------------------*/
	A_BEGIN(1)

		// ���������  �����   ���������������   ����������,
		// � ����� ��������, ��� �� ������� ������� �������
		// �� ����� ��  ��������  �����������, ����  ������
		// �� ����,  ��� �� ������ ������ ����������  �����
		// ������ �����
		for(b = 0; b < 33; b++)
			x += x/cos(x);

		// ���������  96  �������  �����  ����  DWORD,  ���
		// ����������� �������  �������  ������; �  �������
		// ���������� ����� �����������  ���  ������  �����
		// ������."�����������" - ������ ��� �����-�� �����
		// �� ��� ��� ������ ����������
		for(a = 0; a < 96; a += 8)
		{
			p[a + 0] = (a + 0);
			p[a + 1] = (a + 1);
			p[a + 2] = (a + 2);
			p[a + 3] = (a + 3);
			p[a + 4] = (a + 4);
			p[a + 5] = (a + 5);
			p[a + 6] = (a + 6);
			p[a + 7] = (a + 7);
		}

		// ���������  ����������   �����  ����������. �����
		// ������ ������������,���� �� ��� ����� ��� ������
		// ������ ������� ����������, - ����� ��  ���������
		// ������� ������������!
		for(b = 0; b < 33; b++)
			x += x/cos(x);

		// ���������  ���������� 96 �������. ���������  ���
		// �   �����   �������  ���  ������������,   ������
		// ��������� ��� ������, ��� ��� ������ ��������
		for(a = 96; a < 192; a += 8)
		{
			p[a + 0] = (a+0);
			p[a + 1] = (a+1);
			p[a + 2] = (a+2);
			p[a + 3] = (a+3);
			p[a + 4] = (a+4);
			p[a + 5] = (a+5);
			p[a + 6] = (a+6);
			p[a + 7] = (a+7);
		}
		#ifdef __WRITE_MISS__
			// ��������� ������ � ������,
			// ������������� � L1-����
			p+=196;
		#else
			// ��������� ������ � ������,
			// �������������� � L1-����
		#endif	
	A_END(1)

	/*------------------------------------------------------------------------
	 *
	 *				���������������� ��������� �������
	 *
	------------------------------------------------------------------------*/
	A_BEGIN(2)

		// �������� ������ ����� ��������� ��������� ������������� ���,
		// ������� ��� ����� ������������ ���������.
		for(d = 0;d<192;d += 96)
		{
			for(b = 0; b < 33; b++)
				x += x/cos(x);

			for(a = d; a < d+96; a += 8)
			{
				p[a + 0] = (a + 0);
				p[a + 1] = (a + 1);
				p[a + 2] = (a + 2);
				p[a + 3] = (a + 3);
				p[a + 4] = (a + 4);
				p[a + 5] = (a + 5);
				p[a + 6] = (a + 6);
				p[a + 7] = (a + 7);
			}
		}

		#ifdef __WRITE_MISS__
			// ��������� ������ � ������,
			// ������������� � L1-����
			p+=196;
		#else
			// ��������� ������ � ������,
			// �������������� � L1-����
		#endif
	A_END(2)

	// ����� ����������� �� �������
	Lx_OUT("OPTIMIZE FOR SPEED        ",Ax_GET(0),Ax_GET(1));
	Lx_OUT("OPTIMIZE FOR SPEED & SPACE",Ax_GET(0),Ax_GET(2));
}


