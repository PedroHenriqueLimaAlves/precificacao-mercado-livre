#include <stdio.h>
#include <math.h>

// 0. Calcular o custo ajustado do produto (com IPI, crédito de PIS/COFINS e crédito de ICMS)
double calcular_custo(double valor_produto, double IPI, double credito_piscofins, double credito_icms){
    double custo_ajustado;
    custo_ajustado = valor_produto + (valor_produto * IPI) - (valor_produto * credito_piscofins) - (valor_produto * credito_icms);
    return custo_ajustado;
}

// 1. Calcular preço de venda para Anúncio Clássico sem Frete Grátis para o comprador
    double calcular_pv_classico(double custo_ajustado, double taxa_classico, double debito_icms, 
                            double debito_piscofins, double margem_lucro_sobre_custo, double frete_entrada, double comissao_perc){
    double coeficiente, pv, custo_fixo, pv_anterior;
    coeficiente = 1.0 - debito_icms - taxa_classico - comissao_perc - debito_piscofins + (debito_icms * debito_piscofins);
    pv = (custo_ajustado + frete_entrada);
    pv_anterior = 0;
        while (fabs(pv - pv_anterior) > 0.01) { 
        pv_anterior = pv;
        if(pv <= 12.50) custo_fixo = 0.5 * pv;
        else if(pv <= 29.0) custo_fixo = 6.25;
        else if(pv <= 50.0) custo_fixo = 6.50;
        else if(pv < 79.0) custo_fixo = 6.75;
        else if(pv >= 79.0) custo_fixo = 6.75; // somente para controlar depois o que for maior que 79
        else custo_fixo = 0.0;
        pv = (custo_ajustado * (1 + margem_lucro_sobre_custo) + frete_entrada + custo_fixo) / coeficiente;
        }
    return pv;
    }

// 2. Calcular preço de venda para Anúncio Premium sem Frete Grátis para o comprador
double calcular_pv_premium(double custo_ajustado, double taxa_premium, double debito_icms, 
                            double debito_piscofins, double margem_lucro_sobre_custo, double frete_entrada, double comissao_perc){
    double coeficiente, pv, custo_fixo, pv_anterior;
    coeficiente = 1.0 - debito_icms - taxa_premium - comissao_perc - debito_piscofins + (debito_icms * debito_piscofins);
    pv = (custo_ajustado + frete_entrada);
    pv_anterior = 0;
        while (fabs(pv - pv_anterior) > 0.01) { 
        pv_anterior = pv;
        if(pv <= 12.50) custo_fixo = 0.5 * pv;
        else if(pv <= 29.0) custo_fixo = 6.25;
        else if(pv <= 50.0) custo_fixo = 6.50;
        else if(pv < 79.0) custo_fixo = 6.75;
        else if(pv >= 79.0) custo_fixo = 6.75; // somente para controlar depois o que for maior que 79
        else custo_fixo = 0.0;
        pv = (custo_ajustado * (1 + margem_lucro_sobre_custo) + frete_entrada + custo_fixo) / coeficiente;
        }
    return pv;
    }


// 3. Calcular preço de venda para Anúncio Clássico com Frete Grátis para o comprador
double calcular_pv_classico_frete_gratis(double custo_ajustado, double taxa_classico, double debito_icms, 
                            double debito_piscofins, double margem_lucro_sobre_custo, double frete_entrada, double comissao_perc){
    double coeficiente, pv, frete_saida, pv_anterior;
    coeficiente = 1.0 - debito_icms - taxa_classico - comissao_perc - debito_piscofins + (debito_icms * debito_piscofins);
    pv = custo_ajustado + frete_entrada;
    pv_anterior = 0;
    while (fabs(pv - pv_anterior) > 0.01) { 
        pv_anterior = pv;
        if(pv < 79.0) frete_saida = 20.0;
        else if(pv <= 99.99) frete_saida = 24.70;
        else if(pv <= 119.99) frete_saida = 26.94;
        else if(pv <= 149.99) frete_saida = 29.19;
        else if(pv <= 199.99) frete_saida = 31.43;
        else frete_saida = 33.68;
        pv = (custo_ajustado * (1 + margem_lucro_sobre_custo) + frete_entrada + frete_saida) / coeficiente;
    }
    return pv;
}


// 4. Calcular preço de venda para Anúncio Premium com Frete Grátis para o comprador
double calcular_pv_premium_frete_gratis(double custo_ajustado, double taxa_premium, double debito_icms, 
                            double debito_piscofins, double margem_lucro_sobre_custo, double frete_entrada, double comissao_perc){
    double coeficiente, pv, frete_saida, pv_anterior;
    coeficiente = 1.0 - debito_icms - taxa_premium - comissao_perc - debito_piscofins + (debito_icms * debito_piscofins);
    pv = custo_ajustado + frete_entrada;
    pv_anterior = 0;
        while (fabs(pv - pv_anterior) > 0.01) { 
        pv_anterior = pv;
        if(pv < 79.0) frete_saida = 20.0;
        else if(pv <= 99.99) frete_saida = 24.70;
        else if(pv <= 119.99) frete_saida = 26.94;
        else if(pv <= 149.99) frete_saida = 29.19;
        else if(pv <= 199.99) frete_saida = 31.43;
        else frete_saida = 33.68;
        pv = (custo_ajustado * (1 + margem_lucro_sobre_custo) + frete_entrada + frete_saida) / coeficiente;
    }
    return pv;
}

int main() {

 FILE *in = fopen("entrada.csv", "r");
if (!in) {
    FILE *log = fopen("erro.log", "a");
    if (log) {
        fprintf(log, "Erro ao abrir entrada.csv\n");
        fclose(log);
    }
    return 1;
}

FILE *out = fopen("saida.csv", "w");
if (!out) {
    FILE *log = fopen("erro.log", "a");
    if (log) {
        fprintf(log, "Erro ao gerar saida.csv\n");
        fclose(log);
    }
    fclose(in); // fecha o que já abriu
    return 2;
}

    // Cabeçalho de saída
    fprintf(out, "Preco; PV_classico; PV_premium; PV_classico_fgratis; PV_premium_fgratis;; Cred_ICMS; Margem; Cred_PIS/COFINS; Deb_ICMS; Deb_PIS/COFINS; taxa_classico; taxa_premium; comissao\n");

    double valor_produto, IPI_perc, frete_entrada_perc, custo_ajustado, frete_entrada_valor;
    double pv_classico, pv_premium, pv_classico_frete_gratis, pv_premium_frete_gratis;
    double taxa_classico_perc = 0.12; // 12% taxa clássico Mercado Livre
    double taxa_premium_perc = 0.17; // 17% taxa premium Mercado Livre
    double credito_piscofins_perc = 0.0925; // 9,25% crédito PIS/COFINS
    double debito_piscofins_perc = 0.0925; // 9,25% débito PIS/COFINS
    double debito_icms_perc = 0.18; // 18% imposto saída ICMS
    double credito_icms_perc = 0.04; // 4% crédito ICMS
    double margem_lucro_sobre_custo_perc = 0.10; // 10% margem de lucro sobre o preço de custo do produto
    double comissao_perc = 0.01; // 1% comissão para o responsável pelas vendas do Mercado Livre

    char linha[512];
    fgets(linha, sizeof(linha), in); // pula cabeçalho

    while (fscanf(in,
        "%lf;%lf;%lf;%lf;%lf;%lf;%lf;%lf;%lf;%lf;%lf\n",
        &valor_produto,
        &IPI_perc,
        &frete_entrada_perc,
        &credito_icms_perc,
        &margem_lucro_sobre_custo_perc,
        &credito_piscofins_perc,
        &debito_icms_perc,
        &debito_piscofins_perc,
        &taxa_classico_perc,
        &taxa_premium_perc,
        &comissao_perc
    )
         == 11) {

        //Conversoes para decimal    

        IPI_perc = IPI_perc / 100;
        frete_entrada_perc = frete_entrada_perc/100;
        margem_lucro_sobre_custo_perc = margem_lucro_sobre_custo_perc/100;
        credito_icms_perc = credito_icms_perc/100;
        credito_piscofins_perc = credito_piscofins_perc/100;
        debito_icms_perc = debito_icms_perc/100;
        debito_piscofins_perc = debito_piscofins_perc/100;
        taxa_classico_perc = taxa_classico_perc/100;
        taxa_premium_perc = taxa_premium_perc/100;
        comissao_perc = comissao_perc/100;

        // Calculando VALOR EM REAIS DO FRETE baseado no valor do produto e do percentual de frete informado
            frete_entrada_valor = (valor_produto + (valor_produto * IPI_perc)) * frete_entrada_perc;

        // Calcular o CUSTO AJUSTADO DO PRODUTO (com IPI, crédito de PIS/COFINS e crédito de ICMS)
            custo_ajustado =            calcular_custo(valor_produto, IPI_perc, credito_piscofins_perc, credito_icms_perc);

        // Calcular PREÇO DE VENDA PARA ANÚNCIO CLÁSSICO SEM Frete Grátis para o comprador
            pv_classico =               calcular_pv_classico(custo_ajustado, taxa_classico_perc, debito_icms_perc, 
                                        debito_piscofins_perc, margem_lucro_sobre_custo_perc, frete_entrada_valor, comissao_perc);        
                       
        // Calcular PREÇO DE VENDA PARA ANÚNCIO CLÁSSICO COM Frete Grátis para o comprador
            pv_classico_frete_gratis =  calcular_pv_classico_frete_gratis(custo_ajustado, taxa_classico_perc, debito_icms_perc, debito_piscofins_perc, 
                                        margem_lucro_sobre_custo_perc, frete_entrada_valor, comissao_perc);

        // Calcular PREÇO DE VENDA PARA ANÚNCIO PREMIUM SEM Frete Grátis para o comprador
            pv_premium =                calcular_pv_premium(custo_ajustado, taxa_premium_perc, debito_icms_perc, 
                                        debito_piscofins_perc, margem_lucro_sobre_custo_perc, frete_entrada_valor, comissao_perc);

        // Calcular PREÇO DE VENDA PARA ANÚNCIO PREMIUM COM Frete Grátis para o comprador
            pv_premium_frete_gratis =   calcular_pv_premium_frete_gratis(custo_ajustado, taxa_premium_perc, debito_icms_perc, debito_piscofins_perc, 
                                        margem_lucro_sobre_custo_perc, frete_entrada_valor, comissao_perc);

             if(pv_classico < 79 && pv_premium < 79){
                                pv_classico_frete_gratis = 0;
                                }
                                    if(pv_classico >= 79){
                                    pv_classico = 0;
                                    }
                                        if(pv_premium < 79 || pv_classico_frete_gratis != 0){
                                            if(pv_classico != 0){
                                        pv_premium_frete_gratis = 0;
                                            }
                                        }    
                                            if(pv_premium >= 79){
                                            pv_premium = 0;
                                            }
                                    
            fprintf(out,
"%.2lf;%.2lf;%.2lf;%.2lf;%.2lf;;%.2lf%%;%.2lf%%;%.2lf%%;%.2lf%%;%.2lf%%;%.2lf%%;%.2lf%%;%.2lf%%\n",
valor_produto,
pv_classico,
pv_premium,
pv_classico_frete_gratis,
pv_premium_frete_gratis,
credito_icms_perc*100,
margem_lucro_sobre_custo_perc*100,
credito_piscofins_perc*100,
debito_icms_perc*100,
debito_piscofins_perc*100,
taxa_classico_perc*100,
taxa_premium_perc*100,
comissao_perc*100
);
    }

    fclose(in);
    fclose(out);

    return 0;
}
