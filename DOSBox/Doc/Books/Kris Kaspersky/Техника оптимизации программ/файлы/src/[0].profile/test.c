/*----------------------------------------------------------------------------
 *
 *						�������� ����� ��� ���������
 *			�������� ���������� ��������� �������� ������
 *			==============================================
 *
 * Build 0x001 16.08.2002
----------------------------------------------------------------------------*/
#include <DoCPU.h>

main()
{
	int		a;
	int		*p;

	PRINT("= = = ��������� ������� ���������� ��������� �������� ������ = = =\n");
	PRINT_TITLE;

	// ����� test.mod
	p=DoCPU(0);

	// ����� ����������� ������� �� �������
	printf("{ // see test.mod \n");
		for (a = 0; a < 10; a++) printf("\tpass %d, CPU clock %d\n", a, p[a]);
	printf("}\n");
}