/*
 * biblioteca.h
 *
 *  Created on: 3 de jun. de 2025
 *      Author: gustavin
 */

#ifndef BIBLIOTECA_H_
#define BIBLIOTECA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// constantes
#define MAX_NOME 50
#define IDADE_MIN 18
#define IDADE_MAX 100
#define IDADE_MIN_DEPENDENTE 0
#define MAX_DEPENDENTES 2

// Macro codigo cliente
#define GERAR_CODIGO_CLIENTE() (rand() % 1001)

// Macro codigo dependente
#define GERAR_CODIGO_DEPENDENTE(codigoCliente, sequencial) (codigoCliente * 10 + sequencial)

// struct dependentes
typedef struct Dependente {
	char nome[MAX_NOME + 1];
	int codigo;
	char dataNascimento[11];
	char tipoDependente;
	struct Dependente *anterior;
	struct Dependente *proximo;
} Dependente;

// struct clientes
typedef struct Cliente {
	char nome[MAX_NOME + 1];
	int codigo;
	char dataNascimento[11];
	float limiteEmprestimo;
	char tipoCartao;
	int qtdeDependentes;
	Dependente *dependentes;
	struct Cliente *proximo;
} Cliente;

// funcoes de cadastro
void cadastrarNome(char *nome);
char* cadastrarNascimento();
void cadastrarLimite(float *limite, int idade);
char cadastrarTipo();
void cadastrarQtdeDependente(Cliente *cliente);
void cadastrarTipoDependente(char *tipoDependente);

// funcoes de menu
void menu();
void submenuInserir(Cliente **listaClientes);
void submenuExcluir(Cliente **listaClientes);
void submenuRelatorios(Cliente *listaClientes);

// funcoes de inserção
Cliente* inserirCliente(Cliente **listaClientes);
void inserirDependente(Cliente **listaClientes);

// funcoes de exclusão
void excluirCliente(Cliente **listaClientes);
void excluirDependente(Cliente **listaClientes);

// funcoes de relatorio
void listaCompleta(Cliente *listaClientes);
void listaPorCodigo(Cliente *listaClientes);
void listaPorCartao(Cliente *listaClientes);

// funcoes extras
int calcularIdade(char *dataNascimento);
Cliente* buscarClientePorCodigo(Cliente *listaClientes, int codigo);
void liberarDependentes(Dependente *dependentes);
void liberarClientes(Cliente *listaClientes);
void imprimirCliente(Cliente *cliente);
void imprimirDependentesRecursivo(Dependente *dependente);
void imprimirClientesRecursivo(Cliente *cliente, float *somaLimites,
		int *qtdeClientes);
void imprimirClientesPorCartaoRecursivo(Cliente *cliente, char tipoCartao);

#endif /* BIBLIOTECA_H_ */
