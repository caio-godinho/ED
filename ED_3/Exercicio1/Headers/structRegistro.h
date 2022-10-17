#ifndef REGISTRO_H
#define REGISTRO_H

#define Tam_Reg 238
#define MaxTam_PN 51
#define MaxTam_UN 51
#define MaxTam_E  81
#define MaxTam_N  51
#define MaxTam_I   1
#define LIXO "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"

typedef struct _Registro {
  char PrimeiroNome[MaxTam_PN];
  char UltimoNome[MaxTam_UN];
  char Email[MaxTam_E];
  char Nacionalidade[MaxTam_N];
  int Idade;
} Registro;

#endif