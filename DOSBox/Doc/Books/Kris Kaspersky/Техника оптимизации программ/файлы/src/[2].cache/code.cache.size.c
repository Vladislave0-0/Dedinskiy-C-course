/*----------------------------------------------------------------------------
 *						
 *						������ ������������� �����������:
 *				������������������ (������ ��������������� ����� ����)
 *				======================================================
 *
 * Build 0x01 31.07.02
--------------------------------------------------------------------------- */

#include "code.cache.size.h"		// h-���� ������������� ������������
									// make-������  �  �������� ��������
									// ������� CODE_SIZE

#include <DoCPU.h>

main()
{
	int		a;

	// ������ ������ ������� ���������� ����� ���� � �������� CODE_SIZE
	A_BEGIN(1);
		// ����� �������, ��������� �� CODE_SIZE �������� ������ NOP
		DoCPU(&a);
	A_END(1);	// ����� ������

	// ����� ������� ���������� �� �������
	printf("%03d\t %d\n", CODE_SIZE, Ax_GET(1));
}