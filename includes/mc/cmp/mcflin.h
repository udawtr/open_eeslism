#pragma once



// --------------------------------------------
// ���E�����ݒ�p���z�@��
// --------------------------------------------

///@brief ���E�����ݒ�p���z�@��
//@sa Flinint, flindat,  Flinprt
typedef struct flin
{
	char* name;

	//! �ϐ���(���x�A���M�j
	char* namet;   /*  */

	//! �ϐ���(���x�A���M�j
	char* namex;

	//! 'W':�P�ϐ��̂Ƃ�(namet�̕ϐ����̂ݎg�p�j
	//! 'A':�Q�ϐ��̂Ƃ�(namex�̕ϐ����g�p�j
	char  awtype;

	//! namet�Ŏ����ꂽ�ϐ��̒l
	double* vart;

	//! namex�Ŏ����ꂽ�ϐ��̒l
	double* varx;

	struct compnt* cmp;
} FLIN;


void flindat(FLIN *Flin);
void Flinint(int Nflin, FLIN *Flin, 
	     SIMCONTL *Simc, int Ncompnt, COMPNT *Compnt, WDAT *Wdat);
void	Flinprt ( int N, FLIN *Fl ) ;
