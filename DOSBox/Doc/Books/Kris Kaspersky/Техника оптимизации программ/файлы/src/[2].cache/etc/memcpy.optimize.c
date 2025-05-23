/*
	������, ��������������� ������� ����������� ������������ ������
	����� ��������������� �����������
*/

// ������������
#define BLOCK_SIZE (1*M)					// ������ ����������� ����� ������
											// ��������: �������������� ������
											// ���������� ������  �����  �����
											// 6*BLOCK_SIZE*A_NITER
											// ��� ��� ������ ��������� ;-)
											// ��,   ����,     ���  ����������
											// ��������,   ��...  ����   �����
											// ������ ������...
											// �� ����� ���� ���  �������  ���
											// ����,  �����  ���  ������������
											// ��������� ������  ������  �����
											// ��������, ��� ��� �������������
											// ��������� � ����, � �� � ������

#define _PAGE_SIZE (4*K)					// ������ ����� ��������

#include <DoCPU.h>
#include <DoCPU.cmd.h>


/* ---------------------------------------------------------------------------

							������������������ �������

--------------------------------------------------------------------------- */
normal_memcpy(char *dst, char *src, int len)
{
	memcpy(dst, src, len);		// �������� ������ ������ �������� memcpy
}


/* ---------------------------------------------------------------------------

						���������������� �������
										(� �������������� �����������)

--------------------------------------------------------------------------- */
prefetch_memcpy(char *dst, char *src, int len)
{
	int a, b, temp;

	// �������� ������ �� ���������, ����� ������ �� ����������
	for (a = 0; a < len; a += _PAGE_SIZE)
	{
		// ������������
		temp = *(int *)((char *) src + a + _PAGE_SIZE);
		for (b = a; b < (a + _PAGE_SIZE); b += L1_CACHE_LINE_SIZE)
			_prefetchnta(src + b);

		// �������� ������������� ������� ������ ������ �������� memcpy
		memcpy(dst + a, src + a, _PAGE_SIZE);
	}
	return temp;
}


	/* -----------------------------------------------------------------------

						����������������� �������
							(� �������������� ������������ ���������� ������)

	----------------------------------------------------------------------- */
_turbo_memcpy(char *dst, char *src, int len)
{
	int a, b, temp;
	
	for (a = 0; a < len; a += _PAGE_SIZE)
	{

		// ������������
		temp = *(int *)((char *) src + a + _PAGE_SIZE);
		for (b = a; b < a + _PAGE_SIZE; b += L1_CACHE_LINE_SIZE)
			__prefetchnta(src + b);


		// �������� ������ ����������� ������������ ������
		for (b = a; b < a + _PAGE_SIZE; b += 16*8)
		{
			__stream_cpy(dst + b + 16*0, src + b + 16*0);
			__stream_cpy(dst + b + 16*1, src + b + 16*1);

			__stream_cpy(dst + b + 16*2, src + b + 16*2);
			__stream_cpy(dst + b + 16*3, src + b + 16*3);

			__stream_cpy(dst + b + 16*4, src + b + 16*4);
			__stream_cpy(dst + b + 16*5, src + b + 16*5);

			__stream_cpy(dst + b + 16*6, src + b + 16*6);
			__stream_cpy(dst + b + 16*7, src + b + 16*7);
		}

	}
	return temp;
}


main()
{

	char *src, *dst;

	// �������� ������
	src = (char *) _malloc32(BLOCK_SIZE*3*A_NITER);
	dst = (char *) _malloc32(BLOCK_SIZE*3*A_NITER);

	PRINT("= = = memcpy optimization using prefetch = = =\n");
	PRINT_TITLE;

	AL_BEGIN;
		L_BEGIN(0)
			normal_memcpy(dst, src, BLOCK_SIZE);
			dst += BLOCK_SIZE;
			src += BLOCK_SIZE;
		L_END(0)
	AL_END;
	// ��������: ��������� dst � src �� ������������������ _����������_, ����� �����
	// ��������, ��� ��� ����������� ��������� ������  ������  ����������  ���������
	// �� ������������� ����� ��������� ��������� ������ �� ������, � �� ����

	AL_BEGIN;
		L_BEGIN(1)
			prefetch_memcpy(dst, src, BLOCK_SIZE);
			dst += BLOCK_SIZE;
			src += BLOCK_SIZE;
		L_END(1)
	AL_END;

	AL_BEGIN;
		L_BEGIN(2)
			_turbo_memcpy(dst, src, BLOCK_SIZE);
			dst += BLOCK_SIZE;
			src += BLOCK_SIZE;
		L_END(2)
	AL_END;


	Ax_OUT("prefetch ", 0, 1);
	Ax_OUT("strem cpy", 0, 2);


}