#include <stdio.h>

int main (){
    int nPassagens, codigo, seguro, idaVolta, pontos, nBarras, nAguas, multiBarras, multiAguas;
    float valorBasePassagem, valorBaseCompra, totalTaxaIdaVolta, compraDescontoCombo, compraTaxaSeguro, valorFinal, diferencaBaseFinal;
    float DescontoCombo = 0;
    float taxaSeguro = 0;
    float taxaIdaVolta = 1.5;
    char opcaoPontos;

    printf("Nessa ordem por favor informe: \nO numero de passagens a serem compradas \nO codigo de 1 a 5 de destino \nSe deseja "
           "incluir seguro de vida respondendo sim = 1 ou nao = 0  \nE se deseja incluir ida e volta nas passagens respondendo sim = 1 ou nao = 0\n\n");
    scanf("%d %d %d %d", &nPassagens, &codigo, &seguro, &idaVolta);

    switch (codigo){
        case 1: valorBasePassagem = 216.72;
                break;
        case 2: valorBasePassagem = 157.36;
                break;
        case 3: valorBasePassagem = 182.19;
                break;
        case 4: valorBasePassagem = 259.41;
                break;
        case 5: valorBasePassagem = 368.92;
                break;
    }

    valorBaseCompra = nPassagens * valorBasePassagem;

    totalTaxaIdaVolta = nPassagens * taxaIdaVolta;

    if ( idaVolta == 1){
        if ( nPassagens == 1) {
            printf("\n\nO valor base da compra desconsiderando todas as taixas e descontos foi de: %2.f", valorBaseCompra);
            if (seguro == 1) {
                taxaSeguro = nPassagens * (valorBasePassagem * 0.0216);
                compraTaxaSeguro = valorBaseCompra + taxaSeguro;
                printf("\nO valor da compra considerando a taxa do seguro foi de: %2.f", compraTaxaSeguro);
            }
        }
        if ( nPassagens == 2) {
            DescontoCombo = (valorBasePassagem * 0.09);
            compraDescontoCombo = (valorBaseCompra - DescontoCombo);
            printf("\n\nO valor base da compra desconsiderando todas as taixas e descontos foi de: %.2f", valorBaseCompra);
            printf("\nO valor da compra com o desconto do combo foi de: %.2f", compraDescontoCombo);
            printf("\nO valor do desconto do combo de passagens foi de: %.2f", DescontoCombo);
            if (seguro == 1) {
                taxaSeguro = nPassagens * (valorBasePassagem * 0.0216);
                compraTaxaSeguro = valorBaseCompra + taxaSeguro;
                printf("\nO valor da compra considerando a taxa do seguro e o desconto do combo foi de: %.2f", compraTaxaSeguro - DescontoCombo);
                printf("\nO valor da taxa de seguro foi de %.2f", taxaSeguro);
            }
        }
        else if (nPassagens == 3){
            DescontoCombo = (valorBasePassagem * 0.11) + (valorBasePassagem * 0.13);
            compraDescontoCombo = valorBaseCompra - DescontoCombo;
            printf("\n\nO Valor base da compra desconsiderando todas as taixas e descontos foi de: %.2f", valorBaseCompra);
            printf("\nO valor da compra com o desconto do combo foi de: %.2f", compraDescontoCombo);
            printf("\nO valor do desconto do combo de passagens foi de: %.2f", DescontoCombo);
            if (seguro == 1) {
                taxaSeguro = nPassagens * (valorBasePassagem * 0.0216);
                compraTaxaSeguro = valorBaseCompra + taxaSeguro;
                printf("\no Valor da compra considerando a taxa do seguro e o desconto do combo foi de: %.2f", compraTaxaSeguro - DescontoCombo);
                printf("\nO valor da taxa de seguro foi de %.2f", taxaSeguro);
            }
        }
        else if (nPassagens == 4){
            DescontoCombo = (valorBasePassagem * 0.15) * 3;
            compraDescontoCombo = valorBaseCompra - DescontoCombo;
            printf("\n\nO valor base da compra desconsiderando todas as taixas e descontos foi de: %.2f", valorBaseCompra);
            printf("\nO valor da compra com o desconto do combo foi de: %.2f", compraDescontoCombo);
            printf("\nO valor do desconto do combo de passagens foi de: %.2f", DescontoCombo);
            if (seguro == 1) {
                taxaSeguro = nPassagens * (valorBasePassagem * 0.0216);
                compraTaxaSeguro = valorBaseCompra + taxaSeguro;
                printf("\nO valor da compra considerando a taxa do seguro e o desconto do combo foi de: %.2f", compraTaxaSeguro - DescontoCombo);
                printf("\nO valor da taxa de seguro foi de %.2f", taxaSeguro);
            }
        }
        else if (nPassagens >= 5) {
            DescontoCombo = (0.16 * valorBasePassagem) * nPassagens;
            compraDescontoCombo = valorBaseCompra - DescontoCombo;
            printf("\n\nO valor base da compra desconsiderando todas as taixas e descontos foi de: %.2f", valorBaseCompra);
            printf("\nO valor da compra com o desconto do combo foi de: %.2f", compraDescontoCombo);
            printf("\nO valor do desconto do combo de passagens foi de: %.2f", DescontoCombo);
            if (seguro == 1) {
                taxaSeguro = nPassagens * (valorBasePassagem * 0.0216);
                compraTaxaSeguro = valorBaseCompra + taxaSeguro;
                printf("\nO valor da compra considerando a taxa do seguro e o desconto do combo foi de: %.2f", compraTaxaSeguro - DescontoCombo);
                printf("\nO valor da taxa de seguro foi de %.2f", taxaSeguro);
            }
        }
        valorBaseCompra *= 2;
        valorFinal = (taxaSeguro * 2) - (DescontoCombo * 2) + totalTaxaIdaVolta + valorBaseCompra;
        printf("\nO valor final da compra considerando a taxa de volta e a passagem de volta eґ de: %.2f", valorFinal);
    }
    else {
        if (nPassagens == 1) {
            printf("\n\nO valor base da compra desconsiderando todas as taixas e descontos foi de: %.2f", valorBaseCompra);
            if (seguro == 1) {
                taxaSeguro = nPassagens * (valorBasePassagem * 0.0216);
                compraTaxaSeguro = valorBaseCompra + taxaSeguro;
                printf("\nO valor da compra considerando a taxa do foi de: %.2f", compraTaxaSeguro);
                printf("\nO valor da taxa de seguro foi de %.2f", taxaSeguro);
            }
        }
        if (nPassagens == 2) {
            DescontoCombo = valorBasePassagem * 0.09;
            compraDescontoCombo = valorBaseCompra - DescontoCombo;
            printf("\n\nO valor base da compra desconsiderando todas as taixas e descontos foi de: %.2f", valorBaseCompra);
            printf("\nO valor da compra com o desconto do combo foi de: %.2f", compraDescontoCombo);
            printf("\nO valor do desconto do combo de passagens foi de: %.2f", DescontoCombo);
            if (seguro == 1) {
                taxaSeguro = nPassagens * (valorBasePassagem * 0.0216);
                compraTaxaSeguro = valorBaseCompra + taxaSeguro;
                printf("\nO valor da compra considerando a taxa do seguro e o desconto do combo foi de: %.2f", compraTaxaSeguro - DescontoCombo);
                printf("\nO valor da taxa de seguro foi de %.2f", taxaSeguro);
            }
        }
        else if (nPassagens == 3){
            DescontoCombo = (valorBasePassagem * 0.11) + (valorBasePassagem * 0.13);
            compraDescontoCombo = valorBaseCompra - DescontoCombo;
            printf("\n\nO valor base da compra desconsiderando todas as taixas e descontos foi de: %.2f", valorBaseCompra);
            printf("\nO valor da compra com o desconto do combo foi de: %.2f", compraDescontoCombo);
            printf("\nO valor do desconto do combo de passagens foi de: %.2f", DescontoCombo);
            if (seguro == 1) {
                taxaSeguro = nPassagens * (valorBasePassagem * 0.0216);
                compraTaxaSeguro = valorBaseCompra + taxaSeguro;
                printf("\nO valor da compra considerando a taxa do seguro e o desconto do combo foi de: %.2f", compraTaxaSeguro - DescontoCombo);
                printf("\nO valor da taxa de seguro foi de %.2f", taxaSeguro);

            }
        }
        else if (nPassagens == 4){
            DescontoCombo = valorBasePassagem * 0.15 * 3;
            compraDescontoCombo = valorBaseCompra - DescontoCombo;
            printf("\n\nO valor base da compra desconsiderando todas as taixas e descontos foi de: %.2f", valorBaseCompra);
            printf("\nO valor da compra com o desconto do combo foi de: %.2f", compraDescontoCombo);
            printf("\nO valor do desconto do combo de passagens foi de: %.2f", DescontoCombo);
            if (seguro == 1) {
                taxaSeguro = nPassagens * (valorBasePassagem * 0.0216);
                compraTaxaSeguro = valorBaseCompra + taxaSeguro;
                printf("\nO valor da compra considerando a taxa do seguro e o desconto do combo foi de: %.2f", compraTaxaSeguro - DescontoCombo);
                printf("\nO valor da taxa de seguro foi de %.2f", taxaSeguro);
            }
        }
        else if (nPassagens >= 5){
            DescontoCombo = (0.16 * valorBasePassagem) * nPassagens;
            compraDescontoCombo = valorBaseCompra - DescontoCombo;
            printf("\n\nO valor base da compra desconsiderando todas as taixas e descontos foi de: %.2f", valorBaseCompra);
            printf("\nO valor da compra com o desconto do combo foi de: %.2f", compraDescontoCombo);
            printf("\nO valor do desconto do combo de passagens foi de: %.2f", DescontoCombo);
            if (seguro == 1) {
                taxaSeguro = nPassagens * (valorBasePassagem * 0.0216);
                compraTaxaSeguro = valorBaseCompra + taxaSeguro;
                printf("\nO valor da compra considerando a taxa do seguro e o desconto do combo foi de: %.2f", compraTaxaSeguro - DescontoCombo);
                printf("\nO valor da taxa de seguro foi de %.2f", taxaSeguro);
            }
        }
        valorFinal = valorBaseCompra + taxaSeguro - DescontoCombo;
        printf("\nO valor final da compra eґ de: %.2f", valorFinal);
    }

        diferencaBaseFinal = (100 * valorFinal) / valorBaseCompra;
        printf("\nO valor final %2.f representa %2.f%% do valor da compra base %2.f", valorFinal, diferencaBaseFinal, valorBaseCompra);

        pontos = valorFinal / 120;
        printf ("\n\nVoce recebeu %i pontos | Barra de cereal = 2 pontos | Agua = 5 Pontos ", pontos);

    if (pontos <= 1){
        printf ("\nNao e´possivel resgatar nunhuma recompensa com a quantidade atual de pontos\n");
    }
    else if (pontos == 2 ) {
        printf ("\nCom a quantidade de pontos atual e´ possivel resgatar apenas uma barra de cereal\n");
    }
    else if (pontos == 3 ) {
        printf ("\nCom a quantidade de pontos atual e´ possivel resgatar apenas uma barra de cereal\n");
    }
    else if (pontos == 4){
        printf ("\nCom a quantidade de pontos atual e´ possivel resgatar duas barras de cereais\n");
    }
    else {
        printf("\nDigite a opcao correspondente ao que deseja realizar com os pontos: \n1 = usar meus pontos apenas em barras \n2 = usar meus pontos apenas em aguas \n3 = Dividir entre os dois\n");
        scanf("%d", &opcaoPontos);
        if (opcaoPontos == 1){
        nBarras = pontos / 2;
        printf("\n\nVoce pode resgatar: %d\n", nBarras);
        }
        else if (opcaoPontos == 2){
            nAguas = pontos / 5;
            printf("\n\nVoce pode resgatar: %d\n", nAguas);
        }
        else if (opcaoPontos == 3){
            printf("\n\nNessa ordem digite o numero de barras e de aguas que deseja comprar:\n");
            scanf("%d %d", &multiBarras, &multiAguas);
            if ((multiBarras * 2 ) + (multiAguas * 5) <= pontos){
                    printf("\nVoce resgatou %d barras e %d aguas com sucesso\n", multiBarras, multiAguas);
            }
            else {
                printf("\nCombinacao de pontos invalida\n");
            }
        }
        else {
            printf("\n\nOpcao Invalida\n");
        }

    }

    return 0;
}
