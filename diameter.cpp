#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <time.h>

using namespace std;

#define index 1 // vai definir se quer indexar os vértices de 0 ou de 1 (deixei 1 padrão)

const int N = 333;

int g[N][N];
int nxt[N][N];

#define INF 1061109567

void path_recovery(int u, int v){ /* func para recuperar e printar o caminho entre os 
                                   vertices diametrais */
  vector<int> path; // funciona como um vetor dinamico (ou uma lista)              
  path.push_back(u); // função pra inserir
  while(u != v){
    u = nxt[u][v];
    path.push_back(u);
  }
  printf("%d\n", (int) path.size());
  for(int i = 0; i < (int) path.size() - 1; i++)
    printf("%d ", path[i]);

  printf("%d\n", path.back()); // printa o ultimo elemento do vetor

}

int main(){

  clock_t start = clock();  // descomenta linha 84 para saber o tempo

  int n, m;

  scanf("%d %d", &n, &m);
  n -= (1 - index); // apenas para tratamento da indexação
  for(int i = index; i <= n; i++){
    for(int j = index; j <= n; j++){
      nxt[i][j] = j;
      g[i][j] = INF;  /*seta tudo como infinito para evitar
                         que o floyd escolha caminhos inválidos */
    }  
  }

  while(m--){
    int u, v, w;
    scanf("%d %d %d",&u, &v, &w);
    g[u][v] = g[v][u] = w; // aresta bidirecional de u <--> v com custo w
  }
  

  // floyd warshall para encontrar o menor caminho entre todos os pares de vértices
  for(int k = index; k <= n; k++)
    for(int i = index; i <= n; i++)
      for(int j = index; j <= n; j++){
        if(g[i][j] > g[i][k] + g[k][j]){
          g[i][j] = g[i][k] + g[k][j];
          nxt[i][j] = nxt[i][k]; // para recuperar o caminho posteriormente
        }
      }

  int v1, v2;
  int mx = 0; 

  // Encontra o caminho mais longo e salva os vertices diametrais (com maior custo)
  for(int i = index; i <= n; i++){
    for(int j = i + 1; j <= n; j++){
      if(g[i][j] > mx){
        mx = g[i][j];
        v1 = i;
        v2 = j;
      }
    }
  }

  printf("%d\n%d %d\n", g[v1][v2], v1, v2); // mostra o custo do caminho e os vertices diametrais
  path_recovery(v1, v2); 

  // printf("\nexecutou em %.3lf segundos\n", ((double) (clock() - start)) / CLOCKS_PER_SEC);

  return 0;
}