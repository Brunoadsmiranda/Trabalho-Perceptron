#include <stdio.h>
#include <stdlib.h>

int main()
{
    float w0, w1, taxaDeAprendizagem, taxaDeErro, entrada, expectativaDeResultado=0, saida=0;

    //inicio aleatorio

    w0 = 0.0;
    w1 = 0.8;
    taxaDeAprendizagem = 0.05;
    entrada = 1.0;


       for(float i = taxaDeAprendizagem; i > 0; i -= 0.01)
       {
            expectativaDeResultado = entrada * 2; // 1+1 = 2
            saida = (w0 * entrada) + (w1 * entrada); // 0 + 0.8 = 0.8
            taxaDeErro = expectativaDeResultado - saida; // 2 - 0.8 = 1.2
            printf ("\nErro =%f", taxaDeErro);

            w0 =w0 + taxaDeErro* taxaDeAprendizagem  * entrada ;
            w1 =w1 + taxaDeErro* taxaDeAprendizagem  * entrada ;
            printf ("\nW0 = %f", w0);
            printf ("\nw1 = %f", w1);

            entrada++;

        }

        printf ("\nDigite um numero:");
        scanf ("%f", &entrada);

            expectativaDeResultado = entrada + entrada;
            saida = (w0 * entrada) + (w1 * entrada);
            printf ("\nExpectativa de resultado: %f",expectativaDeResultado );
            printf("\n%f", saida );


    return 0;
}

.data
			mensagem: 			.asciiz "Digite um numero\n"
			mensagemdesaida: 		.asciiz "Valor encontrado:\n"
			w0:           			.float 0.000
			w1:          			.float 0.800
			taxaDeAprendizagem:  		.float 0.05
			entrada:           		.float 1.000
			taxaDeErro:      		.float 0.000
			expectativaDeResultado: 	.float 0.000	
			saida: 				.float 0.000
			maisum:				.float 1.000
			
.text
			
			lwc1 $f1, w0				#carrega a variável no registrador escolhido
			lwc1 $f2, w1				#carrega a variável no registrador escolhido
			lwc1 $f3, taxaDeAprendizagem		#carrega a variável no registrador escolhido
			lwc1 $f4, entrada			#carrega a variável no registrador escolhido
			lwc1 $f5, taxaDeErro			#carrega a variável no registrador escolhido
			lwc1 $f6, expectativaDeResultado	#carrega a variável no registrador escolhido
			lwc1 $f7, saida				#carrega a variável no registrador escolhido
			li $t0, 0				#inteiro temporário = 0 para interação(loop)
			li $t1, 5				#inteiro temporário limite da interação(loop)
			lwc1 $f8, maisum			#incremento +1
			
		loop: 	slt  $t3, $t0, $t1
			beq  $t3, $zero, done	 
			
			add.s $f6, $f4, $f4             # atualizando a expectativa do resultado "entrada + entrada"
			mul.s $f9, $f1, $f4             # multiplica entrada por w0 e guarda em $f9
			mul.s $f10, $f2, $f4  		# multiplica entrada por w1 e guarda em $f10
			add.s $f7, $f9, $f10		# saida
			sub.s $f5, $f6, $f7		#taxa de erro
			
			mul.s $f11, $f5, $f3             #taxaDeErro* taxaDeAprendizagem salvo no $f11
			mul.s $f12, $f11, $f4		#(taxaDeErro* taxaDeAprendizagem) * entrada
			add.s $f1, $f1, $f12		# w0 pronto
			add.s $f2, $f2, $f12		# w1 pronto
			
			add.s $f4, $f4, $f8		#entrada++
			
			addi $t0, $t0, 1		#incremento
			
			j loop
			
			
			# imprime mensagem
		done:	li $v0, 4 
			la $a0, mensagem
			syscall
			
			# le float
			li $v0, 6 			#valor do tipo float é lido e guardado em $f0 = entrada
			syscall
			
			add.s $f6, $f0, $f0             # atualizando a expectativa do resultado "entrada + entrada"
			mul.s $f11, $f1, $f0             # multiplica entrada por w0 e guarda em $f1
			mul.s $f12, $f2, $f0  		# multiplica entrada por w1 e guarda em $f2
			add.s $f7, $f11, $f12		# saida
			
				
			# imprime mensagem
			li $v0, 4 
			la $a0, mensagemdesaida
			syscall
			
			# imprime float
			li $v0, 2
			mov.s $f12, $f7 
			syscall
			
			#finalizando o programa
			li $v0, 10
			syscall