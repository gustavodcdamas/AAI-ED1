/*
 * funcoes.c
 *
 *  Created on: 3 de jun. de 2025
 *      Author: gustavin
 */

#include "biblioteca.h"

// Função para cadastrar nome
void cadastrarNome(char *nome) {
	do {
		printf("Digite o nome (max %d caracteres): ", MAX_NOME);
		fflush(stdin);
		fgets(nome, MAX_NOME + 1, stdin);

// Remover o caractere de nova linha, se existir
		int len = strlen(nome);
		if (len > 0 && nome[len - 1] == '\n') {
			nome[len - 1] = '\0';
		}

		if (strlen(nome) == 0) {
			printf("Nome não pode ser vazio. Tente novamente.\n");
		}
	} while (strlen(nome) == 0);
}

// Função para validar e cadastrar data de nascimento
char* cadastrarNascimento() {
	char data = (char) malloc(11 * sizeof(char));
	int dia, mes, ano, idade;
	int dataValida = 0;
	while (!dataValida) {
		printf("Digite a data de nascimento (DD/MM/AAAA): ");
		fflush(stdin);
		fgets(data, 11, stdin);

		// Remover o caractere de nova linha, se existir
		int len = strlen(data);
		if (len > 0 && data[len - 1] == '\n') {
			data[len - 1] = '\0';
		}

		if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) == 3) {
			// Verificar se a data é válida
			if (dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && ano >= 1900) {
				// Verificar meses com 30 dias
				if ((mes == 4 || mes == 6 || mes == 9 || mes == 11)
						&& dia > 30) {
					printf("Data inválida. Este mês tem apenas 30 dias.\n");
					continue;
				}

				// Verificar fevereiro e anos bissextos
				if (mes == 2) {
					int bissexto = (ano % 4 == 0
							&& (ano % 100 != 0 || ano % 400 == 0));
					if ((bissexto && dia > 29) || (!bissexto && dia > 28)) {
						printf("Data inválida para fevereiro.\n");
						continue;
					}
				}

				// Calcular idade
				idade = calcularIdade(data);

				// Validar idade conforme requisitos
				if (idade >= IDADE_MIN_DEPENDENTE && idade <= IDADE_MAX) {
					dataValida = 1;
				} else {
					printf(
							"Idade fora do intervalo permitido (%d a %d anos).\n",
							IDADE_MIN_DEPENDENTE, IDADE_MAX);
				}
			} else {
				printf("Data inválida. Formato correto: DD/MM/AAAA\n");
			}
		} else {
			printf("Formato inválido. Use DD/MM/AAAA\n");
		}
	}

	return data;
}

// Função para calcular idade a partir da data de nascimento
int calcularIdade(char *dataNascimento) {
	int dia, mes, ano;
	sscanf(dataNascimento, "%d/%d/%d", &dia, &mes, &ano);

// Obter data atual
	time_t t = time(NULL);
	struct tm *dataAtual = localtime(&t);
	int diaAtual = dataAtual->tm_mday;
	int mesAtual = dataAtual->tm_mon + 1;
	int anoAtual = dataAtual->tm_year + 1900;

// Calcular idade
	int idade = anoAtual - ano;
	if (mesAtual < mes || (mesAtual == mes && diaAtual < dia)) {
		idade--;
	}

	return idade;
}

// Função para cadastrar limite de empréstimo
void cadastrarLimite(float *limite, int idade) {
	if (idade >= 18 && idade <= 40) {
		*limite = 10000.0;
	} else if (idade >= 41 && idade <= 60) {
		*limite = 15000.0;
	} else if (idade >= 61 && idade <= 75) {
		*limite = 5000.0;
	} else if (idade > 75) {
		*limite = 2500.0;
	} else {
		*limite = 0.0; // Para dependentes menores de idade
	}
}

// Função para cadastrar tipo do cartão
char cadastrarTipo() {
	char tipo;
	int valido = 0;
	while (!valido) {
		printf(
				"Digite o tipo do cartão (U-Universitário, N-Nacional, I-Internacional): ");
		fflush(stdin);
		scanf(" %c", &tipo);
		tipo = toupper(tipo);

		if (tipo == 'U' || tipo == 'N' || tipo == 'I') {
			valido = 1;
		} else {
			printf("Tipo inválido. Use U, N ou I.\n");
		}
	}

	return tipo;
}

// Função para cadastrar quantidade de dependentes
void cadastrarQtdeDependente(Cliente *cliente) {
	int qtde;
	int valido = 0;
	while (!valido) {
		printf("Digite a quantidade de dependentes do cliente %s (0 a %d): ",
				cliente->nome, MAX_DEPENDENTES);
		fflush(stdin);
		scanf("%d", &qtde);

		if (qtde >= 0 && qtde <= MAX_DEPENDENTES) {
			valido = 1;
			cliente->qtdeDependentes = qtde;
		} else {
			printf("Quantidade inválida. Deve ser entre 0 e %d.\n",
			MAX_DEPENDENTES);
		}
	}
}

// Função para cadastrar tipo de dependente
void cadastrarTipoDependente(char *tipoDependente) {
	int valido = 0;
	while (!valido) {
		printf(
				"Digite o tipo do dependente (C-Cônjuge, F-Filho(a), E-Enteado(a)): ");
		fflush(stdin);
		scanf(" %c", tipoDependente);
		*tipoDependente = toupper(*tipoDependente);

		if (*tipoDependente == 'C' || *tipoDependente == 'F'
				|| *tipoDependente == 'E') {
			valido = 1;
		} else {
			printf("Tipo inválido. Use C, F ou E.\n");
		}
	}
}

// Função principal de menu
void menu() {
	Cliente *listaClientes = NULL;
	char opcao;
	int continuar = 1;

// Inicializar gerador de números aleatórios
	srand(time(NULL));

	while (continuar) {
		printf("\n===== MENU PRINCIPAL =====\n");
		printf("A - Inserir\n");
		printf("B - Excluir\n");
		printf("C - Relatórios\n");
		printf("D - Finalizar\n");
		printf("Escolha uma opção: ");
		fflush(stdin);
		scanf(" %c", &opcao);
		opcao = toupper(opcao);

		switch (opcao) {
		case 'A':
			submenuInserir(&listaClientes);
			break;
		case 'B':
			submenuExcluir(&listaClientes);
			break;
		case 'C':
			submenuRelatorios(listaClientes);
			break;
		case 'D':
			printf("Finalizando o programa...\n");
			continuar = 0;
			liberarClientes(listaClientes);
			break;
		default:
			printf("Opção inválida. Tente novamente.\n");
		}
	}
}

// Submenu para inserção
void submenuInserir(Cliente **listaClientes) {
	int opcao;
	printf("\n===== INSERIR =====\n");
	printf("1 - Efetuar inclusão de cliente\n");
	printf("2 - Efetuar inclusão de dependente\n");
	printf("Escolha uma opção: ");
	fflush(stdin);
	scanf("%d", &opcao);

	switch (opcao) {
	case 1:
		inserirCliente(listaClientes);
		break;
	case 2:
		inserirDependente(listaClientes);
		break;
	default:
		printf("Opção inválida. Voltando ao menu principal.\n");
	}
}

// Submenu para exclusão
void submenuExcluir(Cliente **listaClientes) {
	int opcao;
	printf("\n===== EXCLUIR =====\n");
	printf("1 - Efetuar exclusão de cliente\n");
	printf("2 - Efetuar exclusão de dependente\n");
	printf("Escolha uma opção: ");
	fflush(stdin);
	scanf("%d", &opcao);

	switch (opcao) {
	case 1:
		excluirCliente(listaClientes);
		break;
	case 2:
		excluirDependente(listaClientes);
		break;
	default:
		printf("Opção inválida. Voltando ao menu principal.\n");
	}
}

// Submenu para relatórios
void submenuRelatorios(Cliente *listaClientes) {
	int opcao;
	printf("\n===== RELATÓRIOS =====\n");
	printf("1 - Lista completa\n");
	printf("2 - Lista por código\n");
	printf("3 - Lista por cartão\n");
	printf("Escolha uma opção: ");
	fflush(stdin);
	scanf("%d", &opcao);

	switch (opcao) {
	case 1:
		listaCompleta(listaClientes);
		break;
	case 2:
		listaPorCodigo(listaClientes);
		break;
	case 3:
		listaPorCartao(listaClientes);
		break;
	default:
		printf("Opção inválida. Voltando ao menu principal.\n");
	}
}

// Função para inserir cliente
Cliente* inserirCliente(Cliente **listaClientes) {
	Cliente novoCliente = (Cliente) malloc(sizeof(Cliente));
	if (novoCliente == NULL) {
		printf("Erro de alocação de memória.\n");
		return NULL;
	}
	printf("\n===== CADASTRO DE CLIENTE =====\n");

// Cadastrar nome
	cadastrarNome(novoCliente->nome);

// Gerar código aleatório
	novoCliente->codigo = GERAR_CODIGO_CLIENTE();
	printf("Código gerado: %d\n", novoCliente->codigo);

// Cadastrar data de nascimento
	char *dataNasc = cadastrarNascimento();
	strcpy(novoCliente->dataNascimento, dataNasc);
	free(dataNasc);

	int idade = calcularIdade(novoCliente->dataNascimento);
	if (idade < IDADE_MIN) {
		printf("Cliente deve ter pelo menos %d anos.\n", IDADE_MIN);
		free(novoCliente);
		return NULL;
	}

// Cadastrar limite de empréstimo
	cadastrarLimite(&(novoCliente->limiteEmprestimo), idade);

// Cadastrar tipo do cartão
	novoCliente->tipoCartao = cadastrarTipo();

// Ajustar limite conforme tipo do cartão
	if (novoCliente->tipoCartao == 'N') {
		novoCliente->limiteEmprestimo *= 1.05; // Aumento de 5%
	} else if (novoCliente->tipoCartao == 'I') {
		novoCliente->limiteEmprestimo *= 1.20; // Aumento de 20%
	}

// Cadastrar quantidade de dependentes
	novoCliente->qtdeDependentes = 0;
	cadastrarQtdeDependente(novoCliente);

// Inicializar lista de dependentes
	novoCliente->dependentes = NULL;

// Cadastrar dependentes, se houver
	int i;
	for (i = 0; i < novoCliente->qtdeDependentes; i++) {
		Dependente *novoDependente = (Dependente*) malloc(sizeof(Dependente));
		if (novoDependente == NULL) {
			printf("Erro de alocação de memória para dependente.\n");
			continue;
		}

		printf("\n===== CADASTRO DE DEPENDENTE %d =====\n", i + 1);

		// Cadastrar nome
		cadastrarNome(novoDependente->nome);

		// Gerar código sequencial
		novoDependente->codigo = GERAR_CODIGO_DEPENDENTE(novoCliente->codigo,
				i+1);
		printf("Código gerado: %d\n", novoDependente->codigo);

		// Cadastrar data de nascimento
		char *dataNasc = cadastrarNascimento();
		strcpy(novoDependente->dataNascimento, dataNasc);
		free(dataNasc);

		// Cadastrar tipo de dependente
		cadastrarTipoDependente(&(novoDependente->tipoDependente));

		// Inserir dependente no final da lista
		novoDependente->proximo = NULL;

		if (novoCliente->dependentes == NULL) {
			// Primeiro dependente
			novoDependente->anterior = NULL;
			novoCliente->dependentes = novoDependente;
		} else {
			// Percorrer até o final da lista
			Dependente *atual = novoCliente->dependentes;
			while (atual->proximo != NULL) {
				atual = atual->proximo;
			}

			atual->proximo = novoDependente;
			novoDependente->anterior = atual;
		}
	}

// Inserir cliente no início da lista
	novoCliente->proximo = *listaClientes;
	*listaClientes = novoCliente;

	printf("\nCliente cadastrado com sucesso!\n");
	return novoCliente;
}

// Função para inserir dependente
void inserirDependente(Cliente **listaClientes) {
	int codigoCliente;

	if (*listaClientes == NULL) {
		printf("Não há clientes cadastrados.\n");
		return;
	}

	printf("Digite o código do cliente: ");
	fflush(stdin);
	scanf("%d", &codigoCliente);

	Cliente *cliente = buscarClientePorCodigo(*listaClientes, codigoCliente);

	if (cliente == NULL) {
		printf("Cliente não encontrado.\n");
		return;
	}

	if (cliente->qtdeDependentes >= MAX_DEPENDENTES) {
		printf("Cliente já possui o número máximo de dependentes (%d).\n",
		MAX_DEPENDENTES);
		return;
	}

	Dependente *novoDependente = (Dependente*) malloc(sizeof(Dependente));
	if (novoDependente == NULL) {
		printf("Erro de alocação de memória para dependente.\n");
		return;
	}

	printf("\n===== CADASTRO DE DEPENDENTE =====\n");

// Cadastrar nome
	cadastrarNome(novoDependente->nome);

// Gerar código sequencial
	novoDependente->codigo = GERAR_CODIGO_DEPENDENTE(cliente->codigo,
			cliente->qtdeDependentes + 1);
	printf("Código gerado: %d\n", novoDependente->codigo);

// Cadastrar data de nascimento
	char *dataNasc = cadastrarNascimento();
	strcpy(novoDependente->dataNascimento, dataNasc);
	free(dataNasc);

// Cadastrar tipo de dependente
	cadastrarTipoDependente(&(novoDependente->tipoDependente));

// Inserir dependente no final da lista
	novoDependente->proximo = NULL;

	if (cliente->dependentes == NULL) {
		// Primeiro dependente
		novoDependente->anterior = NULL;
		cliente->dependentes = novoDependente;
	} else {
		// Percorrer até o final da lista
		Dependente *atual = cliente->dependentes;
		while (atual->proximo != NULL) {
			atual = atual->proximo;
		}

		atual->proximo = novoDependente;
		novoDependente->anterior = atual;
	}

// Incrementar quantidade de dependentes
	cliente->qtdeDependentes++;

	printf("\nDependente cadastrado com sucesso!\n");
}

// Função para excluir cliente
void excluirCliente(Cliente **listaClientes) {
	int codigoCliente;

	if (*listaClientes == NULL) {
		printf("Não há clientes cadastrados.\n");
		return;
	}

	printf("Digite o código do cliente a ser excluído: ");
	fflush(stdin);
	scanf("%d", &codigoCliente);

	Cliente *anterior = NULL;
	Cliente *atual = *listaClientes;

	while (atual != NULL && atual->codigo != codigoCliente) {
		anterior = atual;
		atual = atual->proximo;
	}

	if (atual == NULL) {
		printf("Cliente não encontrado.\n");
		return;
	}

// Remover da lista
	if (anterior == NULL) {
		// Remover o primeiro da lista
		*listaClientes = atual->proximo;
	} else {
		// Remover do meio ou final
		anterior->proximo = atual->proximo;
	}

// Liberar memória dos dependentes
	liberarDependentes(atual->dependentes);

// Liberar memória do cliente
	free(atual);

	printf("Cliente e seus dependentes excluídos com sucesso!\n");
}

// Função para excluir dependente
void excluirDependente(Cliente **listaClientes) {
	int codigoCliente, codigoDependente;

	if (*listaClientes == NULL) {
		printf("Não há clientes cadastrados.\n");
		return;
	}

	printf("Digite o código do cliente: ");
	fflush(stdin);
	scanf("%d", &codigoCliente);

	Cliente *cliente = buscarClientePorCodigo(*listaClientes, codigoCliente);

	if (cliente == NULL) {
		printf("Cliente não encontrado.\n");
		return;
	}

	if (cliente->dependentes == NULL) {
		printf("Este cliente não possui dependentes.\n");
		return;
	}

	printf("Digite o código do dependente a ser excluído: ");
	fflush(stdin);
	scanf("%d", &codigoDependente);

	Dependente *anterior = NULL;
	Dependente *atual = cliente->dependentes;

	while (atual != NULL && atual->codigo != codigoDependente) {
		anterior = atual;
		atual = atual->proximo;
	}

	if (atual == NULL) {
		printf("Dependente não encontrado.\n");
		return;
	}

// Remover da lista
	if (anterior == NULL) {
		// Remover o primeiro da lista
		cliente->dependentes = atual->proximo;
		if (atual->proximo != NULL) {
			atual->proximo->anterior = NULL;
		}
	} else {
		// Remover do meio ou final
		anterior->proximo = atual->proximo;
		if (atual->proximo != NULL) {
			atual->proximo->anterior = anterior;
		}
	}

// Liberar memória do dependente
	free(atual);

// Decrementar quantidade de dependentes
	cliente->qtdeDependentes--;

	printf("Dependente excluído com sucesso!\n");
}

// Função para listar todos os clientes
void listaCompleta(Cliente *listaClientes) {
	if (listaClientes == NULL) {
		printf("Não há clientes cadastrados.\n");
		return;
	}

	printf("\n===== LISTA COMPLETA DE CLIENTES =====\n");

	float somaLimites = 0;
	int qtdeClientes = 0;

	imprimirClientesRecursivo(listaClientes, &somaLimites, &qtdeClientes);

	if (qtdeClientes > 0) {
		printf("\nMédia dos limites: R$ %.2f\n", somaLimites / qtdeClientes);
	}
}

// Função recursiva para imprimir clientes
void imprimirClientesRecursivo(Cliente *cliente, float *somaLimites,
		int *qtdeClientes) {
	if (cliente == NULL) {
		return;
	}

	imprimirCliente(cliente);
	*somaLimites += cliente->limiteEmprestimo;
	(*qtdeClientes)++;

	imprimirClientesRecursivo(cliente->proximo, somaLimites, qtdeClientes);
}

// Função para listar cliente por código
void listaPorCodigo(Cliente *listaClientes) {
	int codigo;

	if (listaClientes == NULL) {
		printf("Não há clientes cadastrados.\n");
		return;
	}

	printf("Digite o código do cliente: ");
	fflush(stdin);
	scanf("%d", &codigo);

	Cliente *cliente = buscarClientePorCodigo(listaClientes, codigo);

	if (cliente == NULL) {
		printf("Cliente não encontrado.\n");
		return;
	}

	printf("\n===== CLIENTE ENCONTRADO =====\n");
	imprimirCliente(cliente);
}

// Função para listar clientes por tipo de cartão
void listaPorCartao(Cliente *listaClientes) {
	char tipoCartao;

	if (listaClientes == NULL) {
		printf("Não há clientes cadastrados.\n");
		return;
	}

	printf(
			"Digite o tipo de cartão (U-Universitário, N-Nacional, I-Internacional): ");
	fflush(stdin);
	scanf(" %c", &tipoCartao);
	tipoCartao = toupper(tipoCartao);

	if (tipoCartao != 'U' && tipoCartao != 'N' && tipoCartao != 'I') {
		printf("Tipo de cartão inválido.\n");
		return;
	}

	printf("\n===== CLIENTES COM CARTÃO TIPO %c =====\n", tipoCartao);
	imprimirClientesPorCartaoRecursivo(listaClientes, tipoCartao);
}

// Função recursiva para imprimir clientes por tipo de cartão
void imprimirClientesPorCartaoRecursivo(Cliente *cliente, char tipoCartao) {
	if (cliente == NULL) {
		return;
	}

	if (cliente->tipoCartao == tipoCartao) {
		imprimirCliente(cliente);
	}

	imprimirClientesPorCartaoRecursivo(cliente->proximo, tipoCartao);
}

// Função para imprimir dados de um cliente
void imprimirCliente(Cliente *cliente) {
	printf("\nCódigo: %d\n", cliente->codigo);
	printf("Nome: %s\n", cliente->nome);
	printf("Data de nascimento: %s\n", cliente->dataNascimento);
	printf("Limite de empréstimo: R$ %.2f\n", cliente->limiteEmprestimo);

	char tipoCartaoDescricao[20];
	switch (cliente->tipoCartao) {
	case 'U':
		strcpy(tipoCartaoDescricao, "Universitário");
		break;
	case 'N':
		strcpy(tipoCartaoDescricao, "Nacional");
		break;
	case 'I':
		strcpy(tipoCartaoDescricao, "Internacional");
		break;
	default:
		strcpy(tipoCartaoDescricao, "Desconhecido");
	}

	printf("Tipo de cartão: %s (%c)\n", tipoCartaoDescricao,
			cliente->tipoCartao);
	printf("Quantidade de dependentes: %d\n", cliente->qtdeDependentes);

	if (cliente->qtdeDependentes > 0) {
		printf("\nDependentes:\n");
		imprimirDependentesRecursivo(cliente->dependentes);
	}

	printf("------------------------------\n");
}

// Função recursiva para imprimir dependentes
void imprimirDependentesRecursivo(Dependente *dependente) {
	if (dependente == NULL) {
		return;
	}

	printf("  Código: %d\n", dependente->codigo);
	printf("  Nome: %s\n", dependente->nome);
	printf("  Data de nascimento: %s\n", dependente->dataNascimento);

	char tipoDescricao[20];
	switch (dependente->tipoDependente) {
	case 'C':
		strcpy(tipoDescricao, "Cônjuge");
		break;
	case 'F':
		strcpy(tipoDescricao, "Filho(a)");
		break;
	case 'E':
		strcpy(tipoDescricao, "Enteado(a)");
		break;
	default:
		strcpy(tipoDescricao, "Desconhecido");
	}

	printf("  Tipo: %s (%c)\n", tipoDescricao, dependente->tipoDependente);
	printf("  -----\n");

	imprimirDependentesRecursivo(dependente->proximo);
}

// Função para buscar cliente por código
Cliente* buscarClientePorCodigo(Cliente *listaClientes, int codigo) {
	Cliente *atual = listaClientes;

	while (atual != NULL) {
		if (atual->codigo == codigo) {
			return atual;
		}
		atual = atual->proximo;
	}

	return NULL;
}

// Função para liberar memória dos dependentes
void liberarDependentes(Dependente *dependentes) {
	Dependente *atual = dependentes;
	Dependente *proximo;

	while (atual != NULL) {
		proximo = atual->proximo;
		free(atual);
		atual = proximo;
	}
}

// Função para liberar memória dos clientes
void liberarClientes(Cliente *listaClientes) {
	Cliente *atual = listaClientes;
	Cliente *proximo;

	while (atual != NULL) {
		proximo = atual->proximo;
		liberarDependentes(atual->dependentes);
		free(atual);
		atual = proximo;
	}
}

// Função para liberar memória dos clientes
void liberarClientes(Cliente *listaClientes) {
	Cliente *atual = listaClientes;
	Cliente *proximo;

	while (atual != NULL) {
		proximo = atual->proximo;
		liberarDependentes(atual->dependentes);
		free(atual);
		atual = proximo;
	}
}
