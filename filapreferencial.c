/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Seugndo Semestre de 2020                           **/
/**   <2020204> - Prof. Luciano Antonio Digiampietri                **/
/**                                                                 **/
/**   EP2 - Fila Preferencial                                       **/
/**                                                                 **/
/**   <Augusto Xavier Neto>                   <11367581>            **/
/**                                                                 **/
/*********************************************************************/

#include "filapreferencial.h"

PFILA criarFila()
{
  PFILA res = (PFILA)malloc(sizeof(FILAPREFERENCIAL));
  res->inicioPref = NULL;
  res->fimPref = NULL;
  res->inicioGeral = NULL;
  res->fimGeral = NULL;
  return res;
}

int tamanho(PFILA f)
{
  PONT atual = f->inicioGeral;
  int tam = 0;
  while (atual)
  {
    atual = atual->prox;
    tam++;
  }
  return tam;
}

int tamanhoFilaPreferencial(PFILA f)
{
  PONT atual = f->inicioPref;
  int tam = 0;
  while (atual)
  {
    atual = atual->prox;
    tam++;
  }
  return tam;
}

PONT buscarID(PFILA f, int id)
{
  PONT atual = f->inicioGeral;
  while (atual)
  {
    if (atual->id == id)
      return atual;
    atual = atual->prox;
  }
  return NULL;
}

void exibirLog(PFILA f)
{
  int numElementos = tamanho(f);
  printf("\nLog fila geral [elementos: %i] - Inicio:", numElementos);
  PONT atual = f->inicioGeral;
  while (atual)
  {
    printf(" [%i;%i]", atual->id, atual->ehPreferencial);
    atual = atual->prox;
  }
  printf("\n");
  numElementos = tamanhoFilaPreferencial(f);
  printf("\nLog fila preferencial [elementos: %i] - Inicio:", numElementos);
  atual = f->inicioPref;
  while (atual)
  {
    printf(" [%i;%i]", atual->id, atual->ehPreferencial);
    atual = atual->prox;
  }
  printf("\n\n");
}

// Função para inserir uma pessoa na fila geral, e se for o caso, na preferencial
bool inserirPessoaNaFila(PFILA f, int id, int ehPreferencial)
{
  bool resposta = false;

  PONT i, temp, ip, atual;

  // Verificando se o id é válido
  if (id < 0)
  {
    return resposta;
  }

  // Alocando memória para o elemento e colocando seus atributos
  i = (PONT)malloc(sizeof(ELEMENTO));
  i->id = id;
  i->ehPreferencial = ehPreferencial;

  // Verifica se é o primeiro na fila e caso sim, ajeita os ponteiros
  if (f->inicioGeral == NULL)
  {
    f->inicioGeral = i;
    f->fimGeral = i;
    i->prox = NULL;

    return true;
  }

  // Caso não seja o primeiro na fila, verificar se o id já está em uso, caso sim, retornar false
  atual = f->inicioGeral;
  while (atual != NULL)
  {
    if (atual->id == id)
    {
      return resposta;
    }
    atual = atual->prox;
  }

  // Ajeitando os ponteiros para colocar no final da fila
  temp = f->fimGeral;
  f->fimGeral = i;
  temp->prox = i;
  i->prox = NULL;

  // Caso seja preferencial, criar um elemento de mesmo id na fila preferencial
  if (i->ehPreferencial == true)
  {

    // Alocando memória e colocando os atributos
    ip = (PONT)malloc(sizeof(ELEMENTO));
    ip->id = id;
    ip->ehPreferencial = ehPreferencial;

    // Ajeitando os ponteiros caso seja o primeiro da fila, senão, será colocado no final da fila
    if (f->inicioPref == NULL)
    {
      f->inicioPref = ip;
      f->fimPref = ip;
      ip->prox = NULL;
    }
    else
    {
      temp = f->fimPref;
      f->fimPref = ip;
      temp->prox = ip;
      ip->prox = NULL;
    }
  }
  return true;
}

// Função para atender a primeira pessoa da fila preferencial
bool atenderPrimeiraDaFilaPreferencial(PFILA f, int *id)
{
  bool resposta = false;

  PONT temp, atual, ant;

  // Caso a lista esteja vazia, retornar false
  if (f->inicioGeral == NULL)
  {
    return resposta;
  }

  // Usando um auxiliar para posteriormente liberar a memória, e guardando no endereço de id, o primeiro id da fila
  temp = f->inicioPref;
  *id = f->inicioPref->id;

  // Ajeitando o ponteiro
  f->inicioPref = temp->prox;

  // Procurar na lista geral o elemento com mesmo id, e remover
  atual = f->inicioGeral;
  while (atual != NULL)
  {
    if (atual->id == *id)
    {
      if (atual == f->inicioGeral)
      {
        f->inicioGeral = atual->prox;
        free(atual);
        return true;
      }
      ant->prox = atual->prox;
      free(atual);
      return true;
    }
    ant = atual;
    atual = atual->prox;
  }
  free(temp);
  return true;
}

// Função para atender a primeira pessoa da fila geral, e se for o caso, remover da preferencial
bool atenderPrimeiraDaFilaGeral(PFILA f, int *id)
{
  bool resposta = false;

  PONT temp, atual, ant;

  // Verificando se a lista está vazia
  if (f->inicioGeral == NULL)
  {
    return resposta;
  }

  // Usando um auxiliar para posteriormente liberar a memória, e guardando no endereço de id, o primeiro id da fila
  temp = f->inicioGeral;
  *id = f->inicioGeral->id;

  // Ajeitando o ponteiro
  f->inicioGeral = temp->prox;

  // Procurar se na fila prefencial existe um elemento de mesmo id, caso sim, remove-lo
  atual = f->inicioPref;
  while (atual != NULL)
  {
    if (atual->id == *id)
    {
      if (atual == f->inicioPref)
      {
        f->inicioPref = atual->prox;
        free(atual);
        return true;
      }
      ant->prox = atual->prox;
      free(atual);
      return true;
    }
    ant = atual;
    atual = atual->prox;
  }
  free(temp);
  return true;
}

// Função para remover um id específico de ambas as filas
bool desistirDaFila(PFILA f, int id)
{
  bool resposta = false;

  PONT checarId, atualGeral, atualPref, ant;

  // Primeiro checando na fila geral, se o id não existir, false é retornado
  checarId = f->inicioGeral;
  while (checarId != NULL)
  {
    if (checarId->id == id)
    {
      break;
    }
    if (checarId == f->fimGeral && checarId->id != id)
    {
      return resposta;
    }
    checarId = checarId->prox;
  }

  // Percorrendo toda a lista e ao encontrar o id, ajeitar os ponteiros de seu anterior, e posteriormente liberar a memória
  atualGeral = f->inicioGeral;
  while (atualGeral != NULL)
  {
    if (atualGeral->id == id)
    {
      if (atualGeral == f->inicioGeral)
      {
        f->inicioGeral = atualGeral->prox;
        free(atualGeral);
        break;
      }
      ant->prox = atualGeral->prox;
      free(atualGeral);
      break;
    }
    ant = atualGeral;
    atualGeral = atualGeral->prox;
  }

  // Para a fila preferencial a estratégia é a mesma
  atualPref = f->inicioPref;
  while (atualPref != NULL)
  {
    if (atualPref->id == id)
    {
      if (atualPref == f->inicioPref)
      {
        f->inicioPref = atualPref->prox;
        free(atualPref);
        break;
      }
      ant->prox = atualPref->prox;
      free(atualPref);
      break;
    }
    ant = atualPref;
    atualPref = atualPref->prox;
  }
  return true;
}
