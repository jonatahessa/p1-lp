#include <stdio.h>
#include <math.h>

//definicao de nome e email
#define NOME "Jonata Hessa Marques de Oliveira"
#define EMAIL "jonata.hessa@gmail.com"

int main() {
  //arquivo 'dados' serve para leitura e 'ext' para escrita
  FILE *dados;
  FILE *ext;
  dados = fopen("dados.dat", "rt");
  ext = fopen("ext.txt", "wt");

  //definicoes de variaveis
  int numcat, numitmcat, i, j, itens = 0;
  char namecat[25], descitem[15], medida[5], moeda[2], tipopag;
  double vlunit, pcdesc, vlminparc, numparc, qntde, totalcat, totalparcial, totalfinal = 0.0, vldesconto;

  //inicio de preenchimento do documento de saida com nome e email define
  fprintf(ext, "%s\n%s\n\n", NOME, EMAIL);

  //leitura do numero de categorias que serao utilizadas
  fscanf(dados, "%d", &numcat);

  //repeticao com o numero de categorias, leitura e escrita de cada categoria
  for (i = 0; i < numcat; i++) {
    fscanf(dados, "%s %d", &namecat, &numitmcat);
    fprintf(ext, "%s\n", namecat);
    totalcat = 0.0;

    //repeticao dos itens e seus detalhes, leitura e escrita de cada item e seus atributos
    for(j = 0; j < numitmcat; j++) {
      fscanf(dados, "%s %lf %s %s %lf", &descitem, &qntde, &medida, &moeda, &vlunit);
      totalcat = totalcat + (vlunit * qntde);
      fprintf(ext, "* %s:\t%s\t%.2lf\t(%.1lf %s)\n", descitem, moeda, vlunit, qntde, medida);
      itens++;
    }

    //calculo e escrita dos totais de cada categoria
    totalparcial += totalcat;
    fprintf(ext, "** TOTAL %s:\t%s\t%.2lf\n\n", namecat, moeda, totalcat);
  }

  //leitura da porcentagem de desconto e do tipo de pagamento
  fscanf(dados, "%lf %c", &pcdesc, &tipopag);

  //calculo do valor de desconto
  vldesconto = (totalparcial / 100) * pcdesc;
  //calculo do pagamento final
  totalfinal = totalparcial - vldesconto;

  //impressao das valores totais
  fprintf(ext, "TOTAL DE ITENS:\t%d\n\n", itens);
  fprintf(ext, "VALOR TOTAL:\t%s\t%.2lf\n\n", moeda, totalparcial);
  fprintf(ext, "DESCONTO:\t%.2lf%\n\n", pcdesc);
  fprintf(ext, "VALOR DO DESCONTO:\t%.2lf\n\n", vldesconto);
  fprintf(ext, "VALOR A PAGAR:\t%.2lf\n\n", totalfinal);

  //condicao para o tipo de pagamento
  if (tipopag == 'P') {
    //leitura da moeda e do valor minimo das parcelas
    fscanf(dados, "%s %lf", &moeda, &vlminparc);
    //calculo do numero de parcelas e arredonda para baixo
    numparc = floor(totalfinal / vlminparc);
    //condicao se o valor parcelado é igual ou maior do que o valor minimo da parcela
    if (totalfinal / numparc >= vlminparc && numparc >= 2) {
      fprintf(ext, "PARCELAS:\t%.0lf\n\n", numparc);
      fprintf(ext, "VALOR DA PARCELA:\t%.2lf\n", totalfinal / numparc);
    }
  }

  return 0;
}
